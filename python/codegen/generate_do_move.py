# Code generation for shashki-ai
#
# Generates the do_move() function as declared in board.h
import os

from shared import CPP_OUT_DIR, format_cc, linear_index_lookup


def _clear_mask(loc1, loc2):
    """
    Returns a mask m, with all bits set except those which are in between loc1 and loc2
    two on the board
    """
    # find all bit indices to clear (store in ray), excluding loc1 and loc2
    ray = None
    for i in range(4):
        if loc2 in linear_index_lookup[loc1][i]:
            ix = linear_index_lookup[loc1][i].index(loc2)
            ray = linear_index_lookup[loc1][i][:ix]
            break
    else:
        raise RuntimeError("Invalid move (or lookup buggy)")

    # create and-bitmask that clears the bits in quesiton
    value = 0xFFFFFFFFFFFFFFFF
    for i in ray:
        value ^= (1 << i) | (1 << (i + 32))

    return value


def _gen_single_move_func_cc(from_, to):
    # crown a king if required
    set_bit_ix = None
    if (to >> 2) == 0:  # move ended on black's (top) baseline
        set_bit_ix = f"{to} + 32 * (!blacks_turn || GET_64(s1, {from_ + 32}))"
    elif (to >> 2) == 7:  # move ended on whites's (top) baseline
        set_bit_ix = f"{to} + 32 * (blacks_turn || GET_64(s1, {from_ + 32}))"
    else:
        set_bit_ix = f"{to} + 32 * GET_64(s1, {from_ + 32})"

    clear_mask = _clear_mask(from_, to)
    not_clear_mask = clear_mask ^ 0xFFFFFFFFFFFFFFFF

    return "\n".join(
        [
            f"// map entry {to << 8 | from_} (= {from_} -> {to}); note that",
            f"// `s1` must be the active player",
            f"static inline bool _do_move_{from_}_{to}(Slice &s1, Slice &s2, const bool blacks_turn) {{",
            f"  // set the `to` bit",
            f"  SET_64(s1, {set_bit_ix});",
            f"  ",
            f"  // clear `from` bit",
            f"  s1 &= {0xFFFFFFFFFFFFFFFF ^ (1 << from_) ^ (1 << (from_ + 32))}UL;",
            f"  ",
            f"  // clear any token in between (zero or one for a valid move)",
            f"  assert((s1 & {not_clear_mask}UL) == 0);",
            f"  const bool capture = s2 & {not_clear_mask}UL;",
            f"  s2 &= {clear_mask}UL;",
            f"  ",
            f"  return capture;",
            f"}}",
        ]
    )


def _gen_move_func_lookup():
    pass


def _main():
    def generate__do_move_cc():
        all_move_funcs = ""
        map_pairs = []
        for from_, directions in enumerate(linear_index_lookup):
            for ray in directions:
                for to in ray:
                    all_move_funcs += _gen_single_move_func_cc(from_, to) + "\n\n"
                    map_pairs.append(f"{{{to << 8 | from_}, _do_move_{from_}_{to}}},")
        map_pairs = "\n".join(map_pairs)

        in_file = (os.path.dirname(__file__) or ".") + "/templates/do_move.cc.in"
        assert os.path.exists(in_file), "File not found: " + in_file
        with open(in_file, "r") as hf:
            code = "\n".join(l.strip() for l in hf.readlines())
        code = code.replace("/**{generating_script}**/", os.path.basename(__file__))
        code = code.replace("/**{all_move_funcs}**/", all_move_funcs)
        code = code.replace("/**{map_pairs}**/", map_pairs)

        out_file = CPP_OUT_DIR + "/do_move.cc"
        with open(out_file, "w") as hf:
            hf.write(code)
        print(f"Wrote '{out_file}'")
        format_cc(out_file)

    # do it
    generate__do_move_cc()
    print("")


if __name__ == "__main__":
    _main()
