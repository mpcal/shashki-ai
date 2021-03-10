# Code generation for shashki-ai
#
# Prerequisite: the top player is up to make the move
#
# Every move belongs to one of three levels
# * level 1: regular moves of a man or a king without a capture, lowest prio
# * level 2: immediate captures: moves where a man or a king capture an enemy token; in
#            case of a king, he has *no* subsequent capturing options
# * level 3: moves where a king makes a capture and has at least one subsequent
#            mandatory capture (top prio)
import os
from collections import defaultdict, namedtuple
from typing import Counter

from shared import format_cc, NE, NW, SE, SW, linear_index_lookup, CPP_OUT_DIR


def _ones_at(*bits):
    """Number with all bits zero except at the given positions ones"""
    assert len(bits) == len(set(bits))
    value = 0
    for b in bits:
        value += 1 << b
    return value


def _zeros_at(*bits, length=64):
    """`length`-bit number with all bits ones except at the given positions zeros"""
    assert len(bits) == len(set(bits))
    value = (1 << length) - 1
    for b in bits:
        value -= 1 << b
    return value


# Holds the index of the end point of the move and a condition
#
# The index will be a valid endpoint for capture iff the bit mask, "binary and-ed" with
# the 64-bit `bace` is equal to the value of the bitmask itself. In other words, all the
# bits that the mask prescribes must best set while all other bits are ignored. Define
# `bace` as the concatentation of `bottom_any` and `empty` (each 32 bits):
#
#            (----------------------------- bace ----------------------------)
#            (--------- bottom_any ----------)(----------- empty ------------)
#  if mask & 1000001010000010100111010010010110110100101011100010000010010011 == mask:
#    index_is_a_valid_endpoint = True
#
# Note that both bit masks only 32 bits in length
Condition = namedtuple("Condition", "ix,mask")


def _king_captures_along_ray(ixs):
    """
    Returns a list of `Condition`s

    Args:
        ixs (list or tuple): indices along which to compute the conditions; they are
            assumed to be in order, i.e. on a line originating at the starting point
            of the move (not in `ixs`), extending out to the edge of the board
    """
    value = []
    for i in range(0, len(ixs) - 1):
        for j in range(i + 1, len(ixs)):
            # all empty up to captured token
            empty = _ones_at(*[ixs[k] for k in range(0, i)])

            # captured token at index i
            bottom_any = 1 << ixs[i]

            # empty after captured token up to and including touchdown square
            empty |= _ones_at(*[ixs[k] for k in range(i + 1, j + 1)])

            # create mask following our convention
            value.append(Condition(ix=ixs[j], mask=(bottom_any << 32) | empty))

    return value


def _men_captures_along_ray(ixs):
    """Returns a list of `Condition`s with 0 or 1 elements

    Finds the condition for the top player to perform a non-capturing move with a man
    where the top player's going from lower to higher indices

    Args:
        ixs (list or tuple): cf. _king_captures_along_ray()
    """
    if len(ixs) < 2:
        return []

    empty = 1 << ixs[1]
    bottom_any = 1 << ixs[0]

    return [Condition(ix=ixs[1], mask=(bottom_any << 32) | empty)]


def _level_3_conditions(from_):
    def all_cond_for_direction(main_dir, ortho_dir):
        value = []
        for c1 in _king_captures_along_ray(linear_index_lookup[from_][main_dir]):
            for dir_ in (linear_index_lookup[c1.ix][d] for d in ortho_dir):
                for c2 in _king_captures_along_ray(dir_):
                    value.append(Condition(ix=c1.ix, mask=c1.mask | c2.mask))
        return value

    value = []
    value.extend(all_cond_for_direction(NE, (SE, NE, NW)))
    value.extend(all_cond_for_direction(NW, (NE, NW, SW)))
    value.extend(all_cond_for_direction(SW, (NW, SW, SE)))
    value.extend(all_cond_for_direction(SE, (SW, SE, NE)))

    return value


def _level_2_conditions(from_, is_king):
    value = []

    move_fun = _king_captures_along_ray if is_king else _men_captures_along_ray

    value.extend(move_fun(linear_index_lookup[from_][NE]))
    value.extend(move_fun(linear_index_lookup[from_][NW]))
    value.extend(move_fun(linear_index_lookup[from_][SW]))
    value.extend(move_fun(linear_index_lookup[from_][SE]))

    return value


def _king_no_capture_along_ray(ixs):
    """
    Returns a list of `Condition`s

    Args:
        ixs (list or tuple): cf. _king_captures_along_ray()
    """
    value = []
    for j in range(0, len(ixs)):
        # all empty up to and including touchdown square
        empty = _ones_at(*[ixs[k] for k in range(0, j + 1)])

        bottom_any = 0

        # create mask following our convention
        value.append(Condition(ix=ixs[j], mask=(bottom_any << 32) | empty))

    return value


def _men_no_capture_along_ray(ixs):
    """Returns a list of `Condition`s with 0 or 1 elements

    Finds the condition for the top player to perform a capture using a man where top
    player's going from lower to higher indices

    Args:
        ixs (list or tuple): cf. _king_captures_along_ray()
    """
    if len(ixs) < 1:
        return []

    empty = 1 << ixs[0]
    bottom_any = 0

    return [Condition(ix=ixs[0], mask=(bottom_any << 32) | empty)]


def _level_1_conditions(from_, is_king):
    value = []

    move_fun = _king_no_capture_along_ray if is_king else _men_no_capture_along_ray

    if is_king:
        value.extend(move_fun(linear_index_lookup[from_][NE]))
        value.extend(move_fun(linear_index_lookup[from_][NW]))
    value.extend(move_fun(linear_index_lookup[from_][SW]))
    value.extend(move_fun(linear_index_lookup[from_][SE]))

    return value


def _bin_string(i, indent="", min_bits=32):
    value = []
    header = []

    block = 0
    while i > 0 or block <= min_bits / 4:
        header.append(f"  {4*block:2d}")
        value.append(f"{i & 0xf:04b}")
        i >>= 4
        block += 1

    return " ".join(header[::-1]) + "\n" + indent + " ".join(value[::-1])


def _decode_mask(mask):
    """splits a mask into its bottom_any and empty parts"""
    empty = []
    bottom_any = []

    for i in range(32):
        if (mask >> i) & 1 == 1:
            empty.append(i)
        if (mask >> (i + 32)) & 1 == 1:
            bottom_any.append(i)

    return bottom_any, empty


def _describe_condition(cond):
    bottom_any, empty = _decode_mask(cond.mask)

    return (
        f"Conditions for ix={cond.ix:2d}: "
        f"bottom_any={','.join(map(str,bottom_any))}, empty={','.join(map(str,empty))}"
    )


def _dev_level3():
    """Trying out level 3 matching"""

    from_ = 5
    whites = [0, 9, 23]

    bottom_any = _ones_at(*whites) & 0xFFFFFFFF
    empty = _zeros_at(from_, *whites) & 0xFFFFFFFF
    bace = (bottom_any << 32) | empty
    assert bace <= 0xFFFFFFFFFFFFFFFF

    l3 = _level_3_conditions(from_)
    l3_matches = [c for c in l3 if c.mask & bace == c.mask]
    print(f"Total {len(l3_matches)}/{len(l3)} matching L3 condition(s)")
    for c in l3_matches:
        print(">", _describe_condition(c))


def _dev_level2():
    """Trying out level 2 matching"""

    from_ = 14
    whites = [5, 21, 3, 18]

    bottom_any = _ones_at(*whites) & 0xFFFFFFFF
    empty = _zeros_at(from_, *whites) & 0xFFFFFFFF
    bace = (bottom_any << 32) | empty
    assert bace <= 0xFFFFFFFFFFFFFFFF

    l2 = _level_2_conditions(from_, is_king=False)
    l2_matches = [c for c in l2 if c.mask & bace == c.mask]
    print(f"Total {len(l2_matches)}/{len(l2)} matching L2 condition(s)")
    for c in l2_matches:
        print(">", _describe_condition(c))


def _dev_level1():
    """Trying out level 2 matching"""

    from_ = 14
    whites = [10, 5, 24, 27]

    bottom_any = _ones_at(*whites) & 0xFFFFFFFF
    empty = _zeros_at(from_, *whites) & 0xFFFFFFFF
    bace = (bottom_any << 32) | empty
    assert bace <= 0xFFFFFFFFFFFFFFFF

    def run_it(is_king):
        l1 = _level_1_conditions(from_, is_king=is_king)
        l1_matches = [c for c in l1 if c.mask & bace == c.mask]
        print(f"Total {len(l1_matches)}/{len(l1)} matching L1 condition(s)", end="")
        print(f", token type: {'king' if is_king else 'man'}")
        for c in l1_matches:
            print(">", _describe_condition(c))

    run_it(is_king=False)
    run_it(is_king=True)


def _dev_levelx():
    """Trying out level 2 matching"""
    top = 17197698064
    bace = 18086283355075211

    for from_ in range(32):
        is_man, is_king = top & (1 << from_), top & (1 << (from_ + 32))
        if is_king:
            conds = _level_3_conditions(from_)
            matches = [c for c in conds if c.mask & bace == c.mask]
            for c in matches:
                print(
                    f"> ({'man' if is_man else 'king'}) from={from_}: ",
                    _describe_condition(c),
                )


def _dev_num_required_conditions(get_conditions):
    """
    Assessment of the number of required conditions to test for matching a given level

    Pass in e.g. get_conditions == _level_3_conditions
    """
    conds = []
    for i in range(32):
        conds.append(len(get_conditions(i)))

    counts = sorted([(n, cnt) for n, cnt in Counter(conds).items()])
    print(counts)

    print("Mean:         ", sum(n for n, _ in counts) / len(counts))
    print(
        "Weighted mean:",
        sum(n * cnt for n, cnt in counts) / sum(cnt for _, cnt in counts),
    )


# vars in scope: top (64-bit), bottom (64-bit), make_move
#
# handle levels separately, from 3 down to 1, only proceeding to next level if
# previous didn't yield any matches
def generate_blocks(from_ixs, capture_only):
    def cpp_loc_block(
        loc_ix,
        l3_king_if_block,
        l2_man_if_block,
        l2_king_if_block,
        l1_king_if_block,
        l1_man_if_block,
    ):
        return "\n".join(
            [
                f"// ---------- loc == {loc_ix} ----------",
                f"if (GET_64(top, {loc_ix})) {{  // it's a man",
                f"    // check for L2 man moves (capturing)",
                f"    {l2_man_if_block}",
                f"",
                f"    // check for L1 man moves (non-capturing)",
                f"    {l1_man_if_block}",
                f"}}",
                f"else if (GET_64(top, {loc_ix + 32})) {{  // it's a king",
                f"    // check for L3 king moves (multiple captures)",
                f"    {l3_king_if_block}",
                f"",
                f"    // check for L2 king moves (single captures)",
                f"    {l2_king_if_block}",
                f"",
                f"    // check for L1 king moves (non-capturing)",
                f"    {l1_king_if_block}",
                f"}}",
                f"",
                f"// ---- end of loc {loc_ix}\n\n",
            ]
        )

    def cpp_if_block(from_, grouped_masks, level):
        append_to = {3: "l3_moves", 2: "l2_moves", 1: "l1_moves"}[level]

        if True:
            # compact version (with OR connecting related conditions)
            def join_with_or(masks):
                return "||".join(f"((bace & {m}UL) == {m}UL)" for m in masks)

            value = []
            for tgt_ix, masks in grouped_masks.items():
                value.append(f"if ({join_with_or(masks)})")
                value.append(f"  {append_to}.push_back(make_move({from_}, {tgt_ix}));")
            return "\n".join(value)

        else:  ## debug version, one "if" per condition with console output
            value = []
            for tgt_ix, masks in grouped_masks.items():
                for m in masks:
                    value.append(f"if ((bace & {m}UL) == {m}UL) {{\n")
                    value.append(
                        f"  {append_to}.push_back(make_move({from_}, {tgt_ix}));"
                    )
                    bottom_any, empty = _decode_mask(m)
                    value.append(
                        f'  printf("match: make_move({from_}, {tgt_ix}), level={level}, mask(m={m}, '
                        f'bottom_any={bottom_any}, empty={empty})\\n");'
                    )
                    value.append(f"}}")
            return "\n".join(value)

    def group_by_target_ix(cond):
        """group by target index, ix -> (mask_1, mask_2, ..., mask_k)"""
        value = defaultdict(list)
        for c in cond:
            value[c.ix].append(c.mask)

        return dict(value)

    # generate code for valid_moves() and
    value = ""
    for from_ in from_ixs:
        l3_masks = group_by_target_ix(_level_3_conditions(from_))
        l2_man_masks = group_by_target_ix(_level_2_conditions(from_, is_king=False))
        l2_king_masks = group_by_target_ix(_level_2_conditions(from_, is_king=True))
        l1_man_masks = group_by_target_ix(_level_1_conditions(from_, is_king=False))
        l1_king_masks = group_by_target_ix(_level_1_conditions(from_, is_king=True))

        l3_king_if_block = cpp_if_block(from_, l3_masks, 3)
        l2_man_if_block = cpp_if_block(from_, l2_man_masks, 2)
        l2_king_if_block = cpp_if_block(from_, l2_king_masks, 2)
        l1_man_if_block = "" if capture_only else cpp_if_block(from_, l1_man_masks, 1)
        l1_king_if_block = "" if capture_only else cpp_if_block(from_, l1_king_masks, 1)

        value += cpp_loc_block(
            loc_ix=from_,
            l3_king_if_block=l3_king_if_block,
            l2_man_if_block=l2_man_if_block,
            l2_king_if_block=l2_king_if_block,
            l1_man_if_block=l1_man_if_block,
            l1_king_if_block=l1_king_if_block,
        )

    return value


def _main():
    def generate__valid_moves_cc():
        all_loc_blocks = generate_blocks(from_ixs=list(range(32)), capture_only=False)

        in_file = (os.path.dirname(__file__) or ".") + "/templates/valid_moves.cc.in"
        assert os.path.exists(in_file), "File not found: " + in_file
        with open(in_file, "r") as hf:
            code = "\n".join(l.strip() for l in hf.readlines())
        code = code.replace("/**{all_loc_blocks}**/", all_loc_blocks)
        code = code.replace("/**{generating_script}**/", os.path.basename(__file__))

        out_file = CPP_OUT_DIR + "/valid_moves.cc"
        with open(out_file, "w") as hf:
            hf.write(code)
        print(f"Wrote '{out_file}'")
        format_cc(out_file)

    def generate__valid_capturing_moves_from_cc():
        def make_collector(ix, blocks):
            return "\n".join(
                [
                    f"inline static void _collect_{ix}(",
                    f"  std::vector<Move> &l3_moves,",
                    f"  std::vector<Move> &l2_moves,",
                    f"  std::vector<Move> &l1_moves,",
                    f"  const Slice &top,",
                    f"  const Slice &bace) {{",
                    f"  {blocks}",
                    f"}}",
                ]
            )

        all_collectors = ""
        for ix in range(32):
            blocks = generate_blocks(from_ixs=[ix], capture_only=True)
            all_collectors += make_collector(ix, blocks) + "\n"

        in_file = (
            os.path.dirname(__file__) or "."
        ) + "/templates/valid_capturing_moves_from.cc.in"
        assert os.path.exists(in_file)
        with open(in_file, "r") as hf:
            code = "\n".join(l.strip() for l in hf.readlines())
        code = code.replace("/**{all_collectors}**/", all_collectors)
        code = code.replace("/**{generating_script}**/", os.path.basename(__file__))

        out_file = CPP_OUT_DIR + "/valid_capturing_moves_from.cc"
        with open(out_file, "w") as hf:
            hf.write(code)
        print(f"Wrote '{out_file}'")
        format_cc(out_file)

    # do it
    generate__valid_moves_cc()
    generate__valid_capturing_moves_from_cc()
    print("")


if __name__ == "__main__":
    _main()
