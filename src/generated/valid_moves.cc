//
// Purpose: Implements valid_moves(), declared in board.h
//
// ------------------------- WARNING - DO NOT MODIFY! --------------------------
//   This file has been generated automatically.  Modifications will be lost!
// -----------------------------------------------------------------------------
//
#include "board.h"
#include <algorithm>
#include <unordered_set>
#include <vector>

namespace shashki {

static std::vector<Move> _valid_moves_top_down(const Slice &top,
                                               const Slice &bottom) {
  std::vector<Move> l3_moves, l2_moves, l1_moves;

  // bit i set if player has a token at i (using 32 lowest bits only)
  const Slice top_any = ((top >> 32) | top) & 0xffffffff;
  const Slice bottom_any = ((bottom >> 32) | bottom) & 0xffffffff;

  // slice with bit i set if the board location has no token
  const Slice empty = ~(top_any | bottom_any) & 0xffffffff;

  // helper slice made up of bottom_any in upper 32 bits, empty in lower 32:
  //   (-----------------------------bace----------------------------)
  //   (----------bottom_any-----------)(-----------empty------------)
  const Slice bace = (bottom_any << 32) | empty;

  // ---------- loc == 0 ----------
  if (GET_64(top, 0)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 137438953984UL) == 137438953984UL))
      l2_moves.push_back(make_move(0, 9));

    // check for L1 man moves (non-capturing)
    if (((bace & 16UL) == 16UL))
      l1_moves.push_back(make_move(0, 4));
    if (((bace & 32UL) == 32UL))
      l1_moves.push_back(make_move(0, 5));
  } else if (GET_64(top, 32)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 35321811108352UL) == 35321811108352UL) ||
        ((bace & 35321812156928UL) == 35321812156928UL) ||
        ((bace & 281612416721408UL) == 281612416721408UL) ||
        ((bace & 70506183393792UL) == 70506183393792UL) ||
        ((bace & 70506191782400UL) == 70506191782400UL) ||
        ((bace & 70506326000128UL) == 70506326000128UL) ||
        ((bace & 1126037354201600UL) == 1126037354201600UL) ||
        ((bace & 1126037488419328UL) == 1126037488419328UL) ||
        ((bace & 36028934592414208UL) == 36028934592414208UL) ||
        ((bace & 412316860932UL) == 412316860932UL))
      l3_moves.push_back(make_move(0, 9));
    if (((bace & 563087394488832UL) == 563087394488832UL) ||
        ((bace & 563087411266048UL) == 563087411266048UL) ||
        ((bace & 563087679701504UL) == 563087679701504UL) ||
        ((bace & 9007336710619648UL) == 9007336710619648UL) ||
        ((bace & 9007336979055104UL) == 9007336979055104UL) ||
        ((bace & 72057731747561984UL) == 72057731747561984UL) ||
        ((bace & 1126037354201600UL) == 1126037354201600UL) ||
        ((bace & 1126037488419328UL) == 1126037488419328UL) ||
        ((bace & 36028934592414208UL) == 36028934592414208UL) ||
        ((bace & 4535485481600UL) == 4535485481600UL) ||
        ((bace & 4535485481608UL) == 4535485481608UL) ||
        ((bace & 687194785288UL) == 687194785288UL) ||
        ((bace & 565148978790432UL) == 565148978790432UL) ||
        ((bace & 565148995567648UL) == 565148995567648UL) ||
        ((bace & 565149264003104UL) == 565149264003104UL) ||
        ((bace & 9009398294921248UL) == 9009398294921248UL) ||
        ((bace & 9009398563356704UL) == 9009398563356704UL) ||
        ((bace & 72059793331863584UL) == 72059793331863584UL) ||
        ((bace & 1128098938503200UL) == 1128098938503200UL) ||
        ((bace & 1128099072720928UL) == 1128099072720928UL) ||
        ((bace & 36030996176715808UL) == 36030996176715808UL) ||
        ((bace & 6597069783200UL) == 6597069783200UL) ||
        ((bace & 6597069783208UL) == 6597069783208UL) ||
        ((bace & 2748779086888UL) == 2748779086888UL))
      l3_moves.push_back(make_move(0, 14));
    if (((bace & 18014535982268928UL) == 18014535982268928UL) ||
        ((bace & 18014536519139840UL) == 18014536519139840UL) ||
        ((bace & 144115326056153600UL) == 144115326056153600UL) ||
        ((bace & 36028934592414208UL) == 36028934592414208UL) ||
        ((bace & 140874927589888UL) == 140874927589888UL) ||
        ((bace & 18016597566570528UL) == 18016597566570528UL) ||
        ((bace & 18016598103441440UL) == 18016598103441440UL) ||
        ((bace & 144117387640455200UL) == 144117387640455200UL) ||
        ((bace & 36030996176715808UL) == 36030996176715808UL) ||
        ((bace & 142936511891488UL) == 142936511891488UL) ||
        ((bace & 18084767287476768UL) == 18084767287476768UL) ||
        ((bace & 18084767824347680UL) == 18084767824347680UL) ||
        ((bace & 144185557361361440UL) == 144185557361361440UL) ||
        ((bace & 36099165897622048UL) == 36099165897622048UL) ||
        ((bace & 211106232797728UL) == 211106232797728UL))
      l3_moves.push_back(make_move(0, 18));
    if (((bace & 288230514673074688UL) == 288230514673074688UL) ||
        ((bace & 288232576257376288UL) == 288232576257376288UL) ||
        ((bace & 288300745978282528UL) == 288300745978282528UL) ||
        ((bace & 289356277140701728UL) == 289356277140701728UL))
      l3_moves.push_back(make_move(0, 23));

    // check for L2 king moves (single captures)
    if (((bace & 137438953984UL) == 137438953984UL))
      l2_moves.push_back(make_move(0, 9));
    if (((bace & 137438970368UL) == 137438970368UL) ||
        ((bace & 2199023271968UL) == 2199023271968UL))
      l2_moves.push_back(make_move(0, 14));
    if (((bace & 137439232512UL) == 137439232512UL) ||
        ((bace & 2199023534112UL) == 2199023534112UL) ||
        ((bace & 70368744440352UL) == 70368744440352UL))
      l2_moves.push_back(make_move(0, 18));
    if (((bace & 137447621120UL) == 137447621120UL) ||
        ((bace & 2199031922720UL) == 2199031922720UL) ||
        ((bace & 70368752828960UL) == 70368752828960UL) ||
        ((bace & 1125899915248160UL) == 1125899915248160UL))
      l2_moves.push_back(make_move(0, 23));
    if (((bace & 137581838848UL) == 137581838848UL) ||
        ((bace & 2199166140448UL) == 2199166140448UL) ||
        ((bace & 70368887046688UL) == 70368887046688UL) ||
        ((bace & 1125900049465888UL) == 1125900049465888UL) ||
        ((bace & 36028797153460768UL) == 36028797153460768UL))
      l2_moves.push_back(make_move(0, 27));

    // check for L1 king moves (non-capturing)
    if (((bace & 16UL) == 16UL))
      l1_moves.push_back(make_move(0, 4));
    if (((bace & 32UL) == 32UL))
      l1_moves.push_back(make_move(0, 5));
    if (((bace & 544UL) == 544UL))
      l1_moves.push_back(make_move(0, 9));
    if (((bace & 16928UL) == 16928UL))
      l1_moves.push_back(make_move(0, 14));
    if (((bace & 279072UL) == 279072UL))
      l1_moves.push_back(make_move(0, 18));
    if (((bace & 8667680UL) == 8667680UL))
      l1_moves.push_back(make_move(0, 23));
    if (((bace & 142885408UL) == 142885408UL))
      l1_moves.push_back(make_move(0, 27));
  }

  // ---- end of loc 0

  // ---------- loc == 1 ----------
  if (GET_64(top, 1)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 137438953728UL) == 137438953728UL))
      l2_moves.push_back(make_move(1, 8));
    if (((bace & 274877907968UL) == 274877907968UL))
      l2_moves.push_back(make_move(1, 10));

    // check for L1 man moves (non-capturing)
    if (((bace & 32UL) == 32UL))
      l1_moves.push_back(make_move(1, 5));
    if (((bace & 64UL) == 64UL))
      l1_moves.push_back(make_move(1, 6));
  } else if (GET_64(top, 33)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 35321811173632UL) == 35321811173632UL) ||
        ((bace & 35321815367936UL) == 35321815367936UL) ||
        ((bace & 35321882476800UL) == 35321882476800UL) ||
        ((bace & 35324029960448UL) == 35324029960448UL) ||
        ((bace & 563087396577536UL) == 563087396577536UL) ||
        ((bace & 563087463686400UL) == 563087463686400UL) ||
        ((bace & 563089611170048UL) == 563089611170048UL) ||
        ((bace & 18014536015683840UL) == 18014536015683840UL) ||
        ((bace & 18014538163167488UL) == 18014538163167488UL) ||
        ((bace & 288230515742482688UL) == 288230515742482688UL))
      l3_moves.push_back(make_move(1, 8));
    if (((bace & 281612417765632UL) == 281612417765632UL) ||
        ((bace & 281612451320064UL) == 281612451320064UL) ||
        ((bace & 281613525061888UL) == 281613525061888UL) ||
        ((bace & 9007336727318784UL) == 9007336727318784UL) ||
        ((bace & 9007337801060608UL) == 9007337801060608UL) ||
        ((bace & 144115326590718208UL) == 144115326590718208UL) ||
        ((bace & 282574490439712UL) == 282574490439712UL) ||
        ((bace & 282574523994144UL) == 282574523994144UL) ||
        ((bace & 282575597735968UL) == 282575597735968UL) ||
        ((bace & 9008298799992864UL) == 9008298799992864UL) ||
        ((bace & 9008299873734688UL) == 9008299873734688UL) ||
        ((bace & 144116288663392288UL) == 144116288663392288UL))
      l3_moves.push_back(make_move(1, 12));
    if (((bace & 70643622216704UL) == 70643622216704UL) ||
        ((bace & 70643624313856UL) == 70643624313856UL) ||
        ((bace & 70643641091072UL) == 70643641091072UL) ||
        ((bace & 70643909526528UL) == 70643909526528UL) ||
        ((bace & 563224833442816UL) == 563224833442816UL) ||
        ((bace & 563224850220032UL) == 563224850220032UL) ||
        ((bace & 563225118655488UL) == 563225118655488UL) ||
        ((bace & 9007474149573632UL) == 9007474149573632UL) ||
        ((bace & 9007474418009088UL) == 9007474418009088UL) ||
        ((bace & 72057869186515968UL) == 72057869186515968UL) ||
        ((bace & 141012366787584UL) == 141012366787584UL) ||
        ((bace & 824633721864UL) == 824633721864UL))
      l3_moves.push_back(make_move(1, 10));
    if (((bace & 1126174788977664UL) == 1126174788977664UL) ||
        ((bace & 1126174822532096UL) == 1126174822532096UL) ||
        ((bace & 1126175359403008UL) == 1126175359403008UL) ||
        ((bace & 18014673421239296UL) == 18014673421239296UL) ||
        ((bace & 18014673958110208UL) == 18014673958110208UL) ||
        ((bace & 144115463495123968UL) == 144115463495123968UL) ||
        ((bace & 1130297957580864UL) == 1130297957580864UL) ||
        ((bace & 1130297991135296UL) == 1130297991135296UL) ||
        ((bace & 1130298528006208UL) == 1130298528006208UL) ||
        ((bace & 18018796589842496UL) == 18018796589842496UL) ||
        ((bace & 18018797126713408UL) == 18018797126713408UL) ||
        ((bace & 144119586663727168UL) == 144119586663727168UL))
      l3_moves.push_back(make_move(1, 15));
    if (((bace & 36029071964537856UL) == 36029071964537856UL) ||
        ((bace & 36029073038279680UL) == 36029073038279680UL) ||
        ((bace & 288230652112307200UL) == 288230652112307200UL) ||
        ((bace & 36033195133141056UL) == 36033195133141056UL) ||
        ((bace & 36033196206882880UL) == 36033196206882880UL) ||
        ((bace & 288234775280910400UL) == 288234775280910400UL) ||
        ((bace & 36169534574953536UL) == 36169534574953536UL) ||
        ((bace & 36169535648695360UL) == 36169535648695360UL) ||
        ((bace & 288371114722722880UL) == 288371114722722880UL))
      l3_moves.push_back(make_move(1, 19));

    // check for L2 king moves (single captures)
    if (((bace & 137438953728UL) == 137438953728UL))
      l2_moves.push_back(make_move(1, 8));
    if (((bace & 137438957824UL) == 137438957824UL) ||
        ((bace & 1099511631904UL) == 1099511631904UL))
      l2_moves.push_back(make_move(1, 12));
    if (((bace & 274877907968UL) == 274877907968UL))
      l2_moves.push_back(make_move(1, 10));
    if (((bace & 274877940736UL) == 274877940736UL) ||
        ((bace & 4398046543936UL) == 4398046543936UL))
      l2_moves.push_back(make_move(1, 15));
    if (((bace & 274878465024UL) == 274878465024UL) ||
        ((bace & 4398047068224UL) == 4398047068224UL) ||
        ((bace & 140737488880704UL) == 140737488880704UL))
      l2_moves.push_back(make_move(1, 19));

    // check for L1 king moves (non-capturing)
    if (((bace & 32UL) == 32UL))
      l1_moves.push_back(make_move(1, 5));
    if (((bace & 288UL) == 288UL))
      l1_moves.push_back(make_move(1, 8));
    if (((bace & 4384UL) == 4384UL))
      l1_moves.push_back(make_move(1, 12));
    if (((bace & 64UL) == 64UL))
      l1_moves.push_back(make_move(1, 6));
    if (((bace & 1088UL) == 1088UL))
      l1_moves.push_back(make_move(1, 10));
    if (((bace & 33856UL) == 33856UL))
      l1_moves.push_back(make_move(1, 15));
    if (((bace & 558144UL) == 558144UL))
      l1_moves.push_back(make_move(1, 19));
  }

  // ---- end of loc 1

  // ---------- loc == 2 ----------
  if (GET_64(top, 2)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 274877907456UL) == 274877907456UL))
      l2_moves.push_back(make_move(2, 9));
    if (((bace & 549755815936UL) == 549755815936UL))
      l2_moves.push_back(make_move(2, 11));

    // check for L1 man moves (non-capturing)
    if (((bace & 64UL) == 64UL))
      l1_moves.push_back(make_move(2, 6));
    if (((bace & 128UL) == 128UL))
      l1_moves.push_back(make_move(2, 7));
  } else if (GET_64(top, 34)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 412316860929UL) == 412316860929UL) ||
        ((bace & 35459250061824UL) == 35459250061824UL) ||
        ((bace & 35459251110400UL) == 35459251110400UL) ||
        ((bace & 281749855674880UL) == 281749855674880UL) ||
        ((bace & 70643622347264UL) == 70643622347264UL) ||
        ((bace & 70643630735872UL) == 70643630735872UL) ||
        ((bace & 70643764953600UL) == 70643764953600UL) ||
        ((bace & 1126174793155072UL) == 1126174793155072UL) ||
        ((bace & 1126174927372800UL) == 1126174927372800UL) ||
        ((bace & 36029072031367680UL) == 36029072031367680UL))
      l3_moves.push_back(make_move(2, 9));
    if (((bace & 1374389543440UL) == 1374389543440UL) ||
        ((bace & 281749855674880UL) == 281749855674880UL) ||
        ((bace & 563224835531264UL) == 563224835531264UL) ||
        ((bace & 563224902640128UL) == 563224902640128UL) ||
        ((bace & 563227050123776UL) == 563227050123776UL) ||
        ((bace & 18014673454637568UL) == 18014673454637568UL) ||
        ((bace & 18014675602121216UL) == 18014675602121216UL) ||
        ((bace & 288230653181436416UL) == 288230653181436416UL) ||
        ((bace & 3298534891600UL) == 3298534891600UL) ||
        ((bace & 283674001023040UL) == 283674001023040UL) ||
        ((bace & 565148980879424UL) == 565148980879424UL) ||
        ((bace & 565149047988288UL) == 565149047988288UL) ||
        ((bace & 565151195471936UL) == 565151195471936UL) ||
        ((bace & 18016597599985728UL) == 18016597599985728UL) ||
        ((bace & 18016599747469376UL) == 18016599747469376UL) ||
        ((bace & 288232577326784576UL) == 288232577326784576UL))
      l3_moves.push_back(make_move(2, 13));
    if (((bace & 9007474166276608UL) == 9007474166276608UL) ||
        ((bace & 9007475240018432UL) == 9007475240018432UL) ||
        ((bace & 144115464029676032UL) == 144115464029676032UL) ||
        ((bace & 9009398311624768UL) == 9009398311624768UL) ||
        ((bace & 9009399385366592UL) == 9009399385366592UL) ||
        ((bace & 144117388175024192UL) == 144117388175024192UL) ||
        ((bace & 9042383660450368UL) == 9042383660450368UL) ||
        ((bace & 9042384734192192UL) == 9042384734192192UL) ||
        ((bace & 144150373523849792UL) == 144150373523849792UL))
      l3_moves.push_back(make_move(2, 16));
    if (((bace & 72057869453828608UL) == 72057869453828608UL) ||
        ((bace & 72059793599176768UL) == 72059793599176768UL) ||
        ((bace & 72092778948002368UL) == 72092778948002368UL) ||
        ((bace & 72339069552566848UL) == 72339069552566848UL))
      l3_moves.push_back(make_move(2, 20));
    if (((bace & 141287244433408UL) == 141287244433408UL) ||
        ((bace & 141287248627712UL) == 141287248627712UL) ||
        ((bace & 141287282182144UL) == 141287282182144UL) ||
        ((bace & 141287819053056UL) == 141287819053056UL) ||
        ((bace & 1126449666885632UL) == 1126449666885632UL) ||
        ((bace & 1126449700440064UL) == 1126449700440064UL) ||
        ((bace & 1126450237310976UL) == 1126450237310976UL) ||
        ((bace & 18014948299147264UL) == 18014948299147264UL) ||
        ((bace & 18014948836018176UL) == 18014948836018176UL) ||
        ((bace & 144115738373031936UL) == 144115738373031936UL))
      l3_moves.push_back(make_move(2, 11));

    // check for L2 king moves (single captures)
    if (((bace & 274877907456UL) == 274877907456UL))
      l2_moves.push_back(make_move(2, 9));
    if (((bace & 274877915648UL) == 274877915648UL) ||
        ((bace & 2199023263808UL) == 2199023263808UL))
      l2_moves.push_back(make_move(2, 13));
    if (((bace & 274877981184UL) == 274877981184UL) ||
        ((bace & 2199023329344UL) == 2199023329344UL) ||
        ((bace & 35184372154944UL) == 35184372154944UL))
      l2_moves.push_back(make_move(2, 16));
    if (((bace & 274879029760UL) == 274879029760UL) ||
        ((bace & 2199024377920UL) == 2199024377920UL) ||
        ((bace & 35184373203520UL) == 35184373203520UL) ||
        ((bace & 281474977768000UL) == 281474977768000UL))
      l2_moves.push_back(make_move(2, 20));
    if (((bace & 549755815936UL) == 549755815936UL))
      l2_moves.push_back(make_move(2, 11));

    // check for L1 king moves (non-capturing)
    if (((bace & 64UL) == 64UL))
      l1_moves.push_back(make_move(2, 6));
    if (((bace & 576UL) == 576UL))
      l1_moves.push_back(make_move(2, 9));
    if (((bace & 8768UL) == 8768UL))
      l1_moves.push_back(make_move(2, 13));
    if (((bace & 74304UL) == 74304UL))
      l1_moves.push_back(make_move(2, 16));
    if (((bace & 1122880UL) == 1122880UL))
      l1_moves.push_back(make_move(2, 20));
    if (((bace & 128UL) == 128UL))
      l1_moves.push_back(make_move(2, 7));
    if (((bace & 2176UL) == 2176UL))
      l1_moves.push_back(make_move(2, 11));
  }

  // ---- end of loc 2

  // ---------- loc == 3 ----------
  if (GET_64(top, 3)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 549755814912UL) == 549755814912UL))
      l2_moves.push_back(make_move(3, 10));

    // check for L1 man moves (non-capturing)
    if (((bace & 128UL) == 128UL))
      l1_moves.push_back(make_move(3, 7));
  } else if (GET_64(top, 35)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 824633721858UL) == 824633721858UL) ||
        ((bace & 70918500123648UL) == 70918500123648UL) ||
        ((bace & 70918502220800UL) == 70918502220800UL) ||
        ((bace & 70918518998016UL) == 70918518998016UL) ||
        ((bace & 70918787433472UL) == 70918787433472UL) ||
        ((bace & 563499711349760UL) == 563499711349760UL) ||
        ((bace & 563499728126976UL) == 563499728126976UL) ||
        ((bace & 563499996562432UL) == 563499996562432UL) ||
        ((bace & 9007749027480576UL) == 9007749027480576UL) ||
        ((bace & 9007749295916032UL) == 9007749295916032UL) ||
        ((bace & 72058144064422912UL) == 72058144064422912UL) ||
        ((bace & 141287244694528UL) == 141287244694528UL))
      l3_moves.push_back(make_move(3, 10));
    if (((bace & 2748779086880UL) == 2748779086880UL) ||
        ((bace & 2748779086881UL) == 2748779086881UL) ||
        ((bace & 687194785281UL) == 687194785281UL) ||
        ((bace & 563499711349760UL) == 563499711349760UL) ||
        ((bace & 563499728126976UL) == 563499728126976UL) ||
        ((bace & 563499996562432UL) == 563499996562432UL) ||
        ((bace & 9007749027480576UL) == 9007749027480576UL) ||
        ((bace & 9007749295916032UL) == 9007749295916032UL) ||
        ((bace & 72058144064422912UL) == 72058144064422912UL) ||
        ((bace & 1126449671062528UL) == 1126449671062528UL) ||
        ((bace & 1126449805280256UL) == 1126449805280256UL) ||
        ((bace & 36029346909275136UL) == 36029346909275136UL) ||
        ((bace & 6597069783200UL) == 6597069783200UL) ||
        ((bace & 6597069783201UL) == 6597069783201UL) ||
        ((bace & 4535485481601UL) == 4535485481601UL) ||
        ((bace & 567348002046080UL) == 567348002046080UL) ||
        ((bace & 567348018823296UL) == 567348018823296UL) ||
        ((bace & 567348287258752UL) == 567348287258752UL) ||
        ((bace & 9011597318176896UL) == 9011597318176896UL) ||
        ((bace & 9011597586612352UL) == 9011597586612352UL) ||
        ((bace & 72061992355119232UL) == 72061992355119232UL) ||
        ((bace & 1130297961758848UL) == 1130297961758848UL) ||
        ((bace & 1130298095976576UL) == 1130298095976576UL) ||
        ((bace & 36033195199971456UL) == 36033195199971456UL))
      l3_moves.push_back(make_move(3, 14));
    if (((bace & 35734128051456UL) == 35734128051456UL) ||
        ((bace & 35734128051472UL) == 35734128051472UL) ||
        ((bace & 1649267598352UL) == 1649267598352UL) ||
        ((bace & 9007749027480576UL) == 9007749027480576UL) ||
        ((bace & 9007749295916032UL) == 9007749295916032UL) ||
        ((bace & 72058144064422912UL) == 72058144064422912UL) ||
        ((bace & 18014948332553216UL) == 18014948332553216UL) ||
        ((bace & 18014950480036864UL) == 18014950480036864UL) ||
        ((bace & 288230928059352064UL) == 288230928059352064UL) ||
        ((bace & 39582418747776UL) == 39582418747776UL) ||
        ((bace & 39582418747792UL) == 39582418747792UL) ||
        ((bace & 5497558294672UL) == 5497558294672UL) ||
        ((bace & 9011597318176896UL) == 9011597318176896UL) ||
        ((bace & 9011597586612352UL) == 9011597586612352UL) ||
        ((bace & 72061992355119232UL) == 72061992355119232UL) ||
        ((bace & 18018796623249536UL) == 18018796623249536UL) ||
        ((bace & 18018798770733184UL) == 18018798770733184UL) ||
        ((bace & 288234776350048384UL) == 288234776350048384UL) ||
        ((bace & 105553116398976UL) == 105553116398976UL) ||
        ((bace & 105553116398992UL) == 105553116398992UL) ||
        ((bace & 71468255945872UL) == 71468255945872UL) ||
        ((bace & 9077568015828096UL) == 9077568015828096UL) ||
        ((bace & 9077568284263552UL) == 9077568284263552UL) ||
        ((bace & 72127963052770432UL) == 72127963052770432UL) ||
        ((bace & 18084767320900736UL) == 18084767320900736UL) ||
        ((bace & 18084769468384384UL) == 18084769468384384UL) ||
        ((bace & 288300747047699584UL) == 288300747047699584UL))
      l3_moves.push_back(make_move(3, 17));
    if (((bace & 282024734774272UL) == 282024734774272UL) ||
        ((bace & 72058144064422912UL) == 72058144064422912UL) ||
        ((bace & 144115738907657216UL) == 144115738907657216UL) ||
        ((bace & 285873025470592UL) == 285873025470592UL) ||
        ((bace & 72061992355119232UL) == 72061992355119232UL) ||
        ((bace & 144119587198353536UL) == 144119587198353536UL) ||
        ((bace & 351843723121792UL) == 351843723121792UL) ||
        ((bace & 72127963052770432UL) == 72127963052770432UL) ||
        ((bace & 144185557896004736UL) == 144185557896004736UL) ||
        ((bace & 844424932250752UL) == 844424932250752UL) ||
        ((bace & 72620544261899392UL) == 72620544261899392UL) ||
        ((bace & 144678139105133696UL) == 144678139105133696UL))
      l3_moves.push_back(make_move(3, 21));

    // check for L2 king moves (single captures)
    if (((bace & 549755814912UL) == 549755814912UL))
      l2_moves.push_back(make_move(3, 10));
    if (((bace & 549755831296UL) == 549755831296UL) ||
        ((bace & 4398046527616UL) == 4398046527616UL))
      l2_moves.push_back(make_move(3, 14));
    if (((bace & 549755962368UL) == 549755962368UL) ||
        ((bace & 4398046658688UL) == 4398046658688UL) ||
        ((bace & 70368744309888UL) == 70368744309888UL))
      l2_moves.push_back(make_move(3, 17));
    if (((bace & 549758059520UL) == 549758059520UL) ||
        ((bace & 4398048755840UL) == 4398048755840UL) ||
        ((bace & 70368746407040UL) == 70368746407040UL) ||
        ((bace & 562949955536000UL) == 562949955536000UL))
      l2_moves.push_back(make_move(3, 21));
    if (((bace & 549774836736UL) == 549774836736UL) ||
        ((bace & 4398065533056UL) == 4398065533056UL) ||
        ((bace & 70368763184256UL) == 70368763184256UL) ||
        ((bace & 562949972313216UL) == 562949972313216UL) ||
        ((bace & 9007199271666816UL) == 9007199271666816UL))
      l2_moves.push_back(make_move(3, 24));
    if (((bace & 550043272192UL) == 550043272192UL) ||
        ((bace & 4398333968512UL) == 4398333968512UL) ||
        ((bace & 70369031619712UL) == 70369031619712UL) ||
        ((bace & 562950240748672UL) == 562950240748672UL) ||
        ((bace & 9007199540102272UL) == 9007199540102272UL) ||
        ((bace & 72057594308609152UL) == 72057594308609152UL))
      l2_moves.push_back(make_move(3, 28));

    // check for L1 king moves (non-capturing)
    if (((bace & 128UL) == 128UL))
      l1_moves.push_back(make_move(3, 7));
    if (((bace & 1152UL) == 1152UL))
      l1_moves.push_back(make_move(3, 10));
    if (((bace & 17536UL) == 17536UL))
      l1_moves.push_back(make_move(3, 14));
    if (((bace & 148608UL) == 148608UL))
      l1_moves.push_back(make_move(3, 17));
    if (((bace & 2245760UL) == 2245760UL))
      l1_moves.push_back(make_move(3, 21));
    if (((bace & 19022976UL) == 19022976UL))
      l1_moves.push_back(make_move(3, 24));
    if (((bace & 287458432UL) == 287458432UL))
      l1_moves.push_back(make_move(3, 28));
  }

  // ---- end of loc 3

  // ---------- loc == 4 ----------
  if (GET_64(top, 4)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 1099511635968UL) == 1099511635968UL))
      l2_moves.push_back(make_move(4, 13));

    // check for L1 man moves (non-capturing)
    if (((bace & 256UL) == 256UL))
      l1_moves.push_back(make_move(4, 8));
  } else if (GET_64(top, 36)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 282574489395200UL) == 282574489395200UL) ||
        ((bace & 564049469251584UL) == 564049469251584UL) ||
        ((bace & 564049536360448UL) == 564049536360448UL) ||
        ((bace & 564051683844096UL) == 564051683844096UL) ||
        ((bace & 18015498088357888UL) == 18015498088357888UL) ||
        ((bace & 18015500235841536UL) == 18015500235841536UL) ||
        ((bace & 288231477815156736UL) == 288231477815156736UL) ||
        ((bace & 3298534891584UL) == 3298534891584UL) ||
        ((bace & 3298534891588UL) == 3298534891588UL) ||
        ((bace & 1374389543428UL) == 1374389543428UL))
      l3_moves.push_back(make_move(4, 13));
    if (((bace & 9008298783285248UL) == 9008298783285248UL) ||
        ((bace & 9008299051720704UL) == 9008299051720704UL) ||
        ((bace & 72058693820227584UL) == 72058693820227584UL) ||
        ((bace & 18015498088357888UL) == 18015498088357888UL) ||
        ((bace & 18015500235841536UL) == 18015500235841536UL) ||
        ((bace & 288231477815156736UL) == 288231477815156736UL) ||
        ((bace & 71468255945728UL) == 71468255945728UL) ||
        ((bace & 71468255945856UL) == 71468255945856UL) ||
        ((bace & 71468255945864UL) == 71468255945864UL) ||
        ((bace & 5497558294656UL) == 5497558294656UL) ||
        ((bace & 5497558294664UL) == 5497558294664UL) ||
        ((bace & 1649267598344UL) == 1649267598344UL) ||
        ((bace & 9042383643738368UL) == 9042383643738368UL) ||
        ((bace & 9042383912173824UL) == 9042383912173824UL) ||
        ((bace & 72092778680680704UL) == 72092778680680704UL) ||
        ((bace & 18049582948811008UL) == 18049582948811008UL) ||
        ((bace & 18049585096294656UL) == 18049585096294656UL) ||
        ((bace & 288265562675609856UL) == 288265562675609856UL) ||
        ((bace & 105553116398848UL) == 105553116398848UL) ||
        ((bace & 105553116398976UL) == 105553116398976UL) ||
        ((bace & 105553116398984UL) == 105553116398984UL) ||
        ((bace & 39582418747776UL) == 39582418747776UL) ||
        ((bace & 39582418747784UL) == 39582418747784UL) ||
        ((bace & 35734128051464UL) == 35734128051464UL))
      l3_moves.push_back(make_move(4, 17));
    if (((bace & 144116288128688128UL) == 144116288128688128UL) ||
        ((bace & 288231477815156736UL) == 288231477815156736UL) ||
        ((bace & 1126999422836736UL) == 1126999422836736UL) ||
        ((bace & 1126999422838784UL) == 1126999422838784UL) ||
        ((bace & 141837004580864UL) == 141837004580864UL) ||
        ((bace & 144150372989141248UL) == 144150372989141248UL) ||
        ((bace & 288265562675609856UL) == 288265562675609856UL) ||
        ((bace & 1161084283289856UL) == 1161084283289856UL) ||
        ((bace & 1161084283291904UL) == 1161084283291904UL) ||
        ((bace & 175921865033984UL) == 175921865033984UL) ||
        ((bace & 144678138570350848UL) == 144678138570350848UL) ||
        ((bace & 288793328256819456UL) == 288793328256819456UL) ||
        ((bace & 1688849864499456UL) == 1688849864499456UL) ||
        ((bace & 1688849864501504UL) == 1688849864501504UL) ||
        ((bace & 703687446243584UL) == 703687446243584UL))
      l3_moves.push_back(make_move(4, 22));
    if (((bace & 36029896602558464UL) == 36029896602558464UL) ||
        ((bace & 36063981463011584UL) == 36063981463011584UL) ||
        ((bace & 36591747044221184UL) == 36591747044221184UL) ||
        ((bace & 54043195596218624UL) == 54043195596218624UL))
      l3_moves.push_back(make_move(4, 26));

    // check for L2 king moves (single captures)
    if (((bace & 1099511635968UL) == 1099511635968UL))
      l2_moves.push_back(make_move(4, 13));
    if (((bace & 1099511767040UL) == 1099511767040UL) ||
        ((bace & 35184372220160UL) == 35184372220160UL))
      l2_moves.push_back(make_move(4, 17));
    if (((bace & 1099515961344UL) == 1099515961344UL) ||
        ((bace & 35184376414464UL) == 35184376414464UL) ||
        ((bace & 562949957624064UL) == 562949957624064UL))
      l2_moves.push_back(make_move(4, 22));
    if (((bace & 1099583070208UL) == 1099583070208UL) ||
        ((bace & 35184443523328UL) == 35184443523328UL) ||
        ((bace & 562950024732928UL) == 562950024732928UL) ||
        ((bace & 18014398576730368UL) == 18014398576730368UL))
      l2_moves.push_back(make_move(4, 26));
    if (((bace & 1101730553856UL) == 1101730553856UL) ||
        ((bace & 35186591006976UL) == 35186591006976UL) ||
        ((bace & 562952172216576UL) == 562952172216576UL) ||
        ((bace & 18014400724214016UL) == 18014400724214016UL) ||
        ((bace & 288230378303529216UL) == 288230378303529216UL))
      l2_moves.push_back(make_move(4, 31));

    // check for L1 king moves (non-capturing)
    if (((bace & 1UL) == 1UL))
      l1_moves.push_back(make_move(4, 0));
    if (((bace & 256UL) == 256UL))
      l1_moves.push_back(make_move(4, 8));
    if (((bace & 8448UL) == 8448UL))
      l1_moves.push_back(make_move(4, 13));
    if (((bace & 139520UL) == 139520UL))
      l1_moves.push_back(make_move(4, 17));
    if (((bace & 4333824UL) == 4333824UL))
      l1_moves.push_back(make_move(4, 22));
    if (((bace & 71442688UL) == 71442688UL))
      l1_moves.push_back(make_move(4, 26));
    if (((bace & 2218926336UL) == 2218926336UL))
      l1_moves.push_back(make_move(4, 31));
  }

  // ---- end of loc 4

  // ---------- loc == 5 ----------
  if (GET_64(top, 5)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 1099511631872UL) == 1099511631872UL))
      l2_moves.push_back(make_move(5, 12));
    if (((bace & 2199023271936UL) == 2199023271936UL))
      l2_moves.push_back(make_move(5, 14));

    // check for L1 man moves (non-capturing)
    if (((bace & 256UL) == 256UL))
      l1_moves.push_back(make_move(5, 8));
    if (((bace & 512UL) == 512UL))
      l1_moves.push_back(make_move(5, 9));
  } else if (GET_64(top, 37)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 282574490439680UL) == 282574490439680UL) ||
        ((bace & 282574523994112UL) == 282574523994112UL) ||
        ((bace & 282575597735936UL) == 282575597735936UL) ||
        ((bace & 9008298799992832UL) == 9008298799992832UL) ||
        ((bace & 9008299873734656UL) == 9008299873734656UL) ||
        ((bace & 144116288663392256UL) == 144116288663392256UL))
      l3_moves.push_back(make_move(5, 12));
    if (((bace & 565148978790400UL) == 565148978790400UL) ||
        ((bace & 565148995567616UL) == 565148995567616UL) ||
        ((bace & 565149264003072UL) == 565149264003072UL) ||
        ((bace & 9009398294921216UL) == 9009398294921216UL) ||
        ((bace & 9009398563356672UL) == 9009398563356672UL) ||
        ((bace & 72059793331863552UL) == 72059793331863552UL) ||
        ((bace & 1128098938503168UL) == 1128098938503168UL) ||
        ((bace & 1128099072720896UL) == 1128099072720896UL) ||
        ((bace & 36030996176715776UL) == 36030996176715776UL) ||
        ((bace & 6597069783168UL) == 6597069783168UL) ||
        ((bace & 6597069783176UL) == 6597069783176UL) ||
        ((bace & 2748779086856UL) == 2748779086856UL))
      l3_moves.push_back(make_move(5, 14));
    if (((bace & 18016597566570496UL) == 18016597566570496UL) ||
        ((bace & 18016598103441408UL) == 18016598103441408UL) ||
        ((bace & 144117387640455168UL) == 144117387640455168UL) ||
        ((bace & 36030996176715776UL) == 36030996176715776UL) ||
        ((bace & 142936511891456UL) == 142936511891456UL) ||
        ((bace & 18084767287476736UL) == 18084767287476736UL) ||
        ((bace & 18084767824347648UL) == 18084767824347648UL) ||
        ((bace & 144185557361361408UL) == 144185557361361408UL) ||
        ((bace & 36099165897622016UL) == 36099165897622016UL) ||
        ((bace & 211106232797696UL) == 211106232797696UL))
      l3_moves.push_back(make_move(5, 18));
    if (((bace & 288232576257376256UL) == 288232576257376256UL) ||
        ((bace & 288300745978282496UL) == 288300745978282496UL) ||
        ((bace & 289356277140701696UL) == 289356277140701696UL))
      l3_moves.push_back(make_move(5, 23));

    // check for L2 king moves (single captures)
    if (((bace & 1099511631872UL) == 1099511631872UL))
      l2_moves.push_back(make_move(5, 12));
    if (((bace & 2199023271936UL) == 2199023271936UL))
      l2_moves.push_back(make_move(5, 14));
    if (((bace & 2199023534080UL) == 2199023534080UL) ||
        ((bace & 70368744440320UL) == 70368744440320UL))
      l2_moves.push_back(make_move(5, 18));
    if (((bace & 2199031922688UL) == 2199031922688UL) ||
        ((bace & 70368752828928UL) == 70368752828928UL) ||
        ((bace & 1125899915248128UL) == 1125899915248128UL))
      l2_moves.push_back(make_move(5, 23));
    if (((bace & 2199166140416UL) == 2199166140416UL) ||
        ((bace & 70368887046656UL) == 70368887046656UL) ||
        ((bace & 1125900049465856UL) == 1125900049465856UL) ||
        ((bace & 36028797153460736UL) == 36028797153460736UL))
      l2_moves.push_back(make_move(5, 27));

    // check for L1 king moves (non-capturing)
    if (((bace & 2UL) == 2UL))
      l1_moves.push_back(make_move(5, 1));
    if (((bace & 1UL) == 1UL))
      l1_moves.push_back(make_move(5, 0));
    if (((bace & 256UL) == 256UL))
      l1_moves.push_back(make_move(5, 8));
    if (((bace & 4352UL) == 4352UL))
      l1_moves.push_back(make_move(5, 12));
    if (((bace & 512UL) == 512UL))
      l1_moves.push_back(make_move(5, 9));
    if (((bace & 16896UL) == 16896UL))
      l1_moves.push_back(make_move(5, 14));
    if (((bace & 279040UL) == 279040UL))
      l1_moves.push_back(make_move(5, 18));
    if (((bace & 8667648UL) == 8667648UL))
      l1_moves.push_back(make_move(5, 23));
    if (((bace & 142885376UL) == 142885376UL))
      l1_moves.push_back(make_move(5, 27));
  }

  // ---- end of loc 5

  // ---------- loc == 6 ----------
  if (GET_64(top, 6)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 2199023263744UL) == 2199023263744UL))
      l2_moves.push_back(make_move(6, 13));
    if (((bace & 4398046543872UL) == 4398046543872UL))
      l2_moves.push_back(make_move(6, 15));

    // check for L1 man moves (non-capturing)
    if (((bace & 512UL) == 512UL))
      l1_moves.push_back(make_move(6, 9));
    if (((bace & 1024UL) == 1024UL))
      l1_moves.push_back(make_move(6, 10));
  } else if (GET_64(top, 38)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 3298534891536UL) == 3298534891536UL) ||
        ((bace & 283674001022976UL) == 283674001022976UL) ||
        ((bace & 565148980879360UL) == 565148980879360UL) ||
        ((bace & 565149047988224UL) == 565149047988224UL) ||
        ((bace & 565151195471872UL) == 565151195471872UL) ||
        ((bace & 18016597599985664UL) == 18016597599985664UL) ||
        ((bace & 18016599747469312UL) == 18016599747469312UL) ||
        ((bace & 288232577326784512UL) == 288232577326784512UL))
      l3_moves.push_back(make_move(6, 13));
    if (((bace & 9009398311624704UL) == 9009398311624704UL) ||
        ((bace & 9009399385366528UL) == 9009399385366528UL) ||
        ((bace & 144117388175024128UL) == 144117388175024128UL) ||
        ((bace & 9042383660450304UL) == 9042383660450304UL) ||
        ((bace & 9042384734192128UL) == 9042384734192128UL) ||
        ((bace & 144150373523849728UL) == 144150373523849728UL))
      l3_moves.push_back(make_move(6, 16));
    if (((bace & 72059793599176704UL) == 72059793599176704UL) ||
        ((bace & 72092778948002304UL) == 72092778948002304UL) ||
        ((bace & 72339069552566784UL) == 72339069552566784UL))
      l3_moves.push_back(make_move(6, 20));
    if (((bace & 1130297957580800UL) == 1130297957580800UL) ||
        ((bace & 1130297991135232UL) == 1130297991135232UL) ||
        ((bace & 1130298528006144UL) == 1130298528006144UL) ||
        ((bace & 18018796589842432UL) == 18018796589842432UL) ||
        ((bace & 18018797126713344UL) == 18018797126713344UL) ||
        ((bace & 144119586663727104UL) == 144119586663727104UL))
      l3_moves.push_back(make_move(6, 15));
    if (((bace & 36033195133140992UL) == 36033195133140992UL) ||
        ((bace & 36033196206882816UL) == 36033196206882816UL) ||
        ((bace & 288234775280910336UL) == 288234775280910336UL) ||
        ((bace & 36169534574953472UL) == 36169534574953472UL) ||
        ((bace & 36169535648695296UL) == 36169535648695296UL) ||
        ((bace & 288371114722722816UL) == 288371114722722816UL))
      l3_moves.push_back(make_move(6, 19));

    // check for L2 king moves (single captures)
    if (((bace & 2199023263744UL) == 2199023263744UL))
      l2_moves.push_back(make_move(6, 13));
    if (((bace & 2199023329280UL) == 2199023329280UL) ||
        ((bace & 35184372154880UL) == 35184372154880UL))
      l2_moves.push_back(make_move(6, 16));
    if (((bace & 2199024377856UL) == 2199024377856UL) ||
        ((bace & 35184373203456UL) == 35184373203456UL) ||
        ((bace & 281474977767936UL) == 281474977767936UL))
      l2_moves.push_back(make_move(6, 20));
    if (((bace & 4398046543872UL) == 4398046543872UL))
      l2_moves.push_back(make_move(6, 15));
    if (((bace & 4398047068160UL) == 4398047068160UL) ||
        ((bace & 140737488880640UL) == 140737488880640UL))
      l2_moves.push_back(make_move(6, 19));

    // check for L1 king moves (non-capturing)
    if (((bace & 4UL) == 4UL))
      l1_moves.push_back(make_move(6, 2));
    if (((bace & 2UL) == 2UL))
      l1_moves.push_back(make_move(6, 1));
    if (((bace & 512UL) == 512UL))
      l1_moves.push_back(make_move(6, 9));
    if (((bace & 8704UL) == 8704UL))
      l1_moves.push_back(make_move(6, 13));
    if (((bace & 74240UL) == 74240UL))
      l1_moves.push_back(make_move(6, 16));
    if (((bace & 1122816UL) == 1122816UL))
      l1_moves.push_back(make_move(6, 20));
    if (((bace & 1024UL) == 1024UL))
      l1_moves.push_back(make_move(6, 10));
    if (((bace & 33792UL) == 33792UL))
      l1_moves.push_back(make_move(6, 15));
    if (((bace & 558080UL) == 558080UL))
      l1_moves.push_back(make_move(6, 19));
  }

  // ---- end of loc 6

  // ---------- loc == 7 ----------
  if (GET_64(top, 7)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 4398046527488UL) == 4398046527488UL))
      l2_moves.push_back(make_move(7, 14));

    // check for L1 man moves (non-capturing)
    if (((bace & 1024UL) == 1024UL))
      l1_moves.push_back(make_move(7, 10));
    if (((bace & 2048UL) == 2048UL))
      l1_moves.push_back(make_move(7, 11));
  } else if (GET_64(top, 39)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 6597069783072UL) == 6597069783072UL) ||
        ((bace & 6597069783073UL) == 6597069783073UL) ||
        ((bace & 4535485481473UL) == 4535485481473UL) ||
        ((bace & 567348002045952UL) == 567348002045952UL) ||
        ((bace & 567348018823168UL) == 567348018823168UL) ||
        ((bace & 567348287258624UL) == 567348287258624UL) ||
        ((bace & 9011597318176768UL) == 9011597318176768UL) ||
        ((bace & 9011597586612224UL) == 9011597586612224UL) ||
        ((bace & 72061992355119104UL) == 72061992355119104UL) ||
        ((bace & 1130297961758720UL) == 1130297961758720UL) ||
        ((bace & 1130298095976448UL) == 1130298095976448UL) ||
        ((bace & 36033195199971328UL) == 36033195199971328UL))
      l3_moves.push_back(make_move(7, 14));
    if (((bace & 39582418747648UL) == 39582418747648UL) ||
        ((bace & 39582418747664UL) == 39582418747664UL) ||
        ((bace & 5497558294544UL) == 5497558294544UL) ||
        ((bace & 9011597318176768UL) == 9011597318176768UL) ||
        ((bace & 9011597586612224UL) == 9011597586612224UL) ||
        ((bace & 72061992355119104UL) == 72061992355119104UL) ||
        ((bace & 18018796623249408UL) == 18018796623249408UL) ||
        ((bace & 18018798770733056UL) == 18018798770733056UL) ||
        ((bace & 288234776350048256UL) == 288234776350048256UL) ||
        ((bace & 105553116398848UL) == 105553116398848UL) ||
        ((bace & 105553116398864UL) == 105553116398864UL) ||
        ((bace & 71468255945744UL) == 71468255945744UL) ||
        ((bace & 9077568015827968UL) == 9077568015827968UL) ||
        ((bace & 9077568284263424UL) == 9077568284263424UL) ||
        ((bace & 72127963052770304UL) == 72127963052770304UL) ||
        ((bace & 18084767320900608UL) == 18084767320900608UL) ||
        ((bace & 18084769468384256UL) == 18084769468384256UL) ||
        ((bace & 288300747047699456UL) == 288300747047699456UL))
      l3_moves.push_back(make_move(7, 17));
    if (((bace & 285873025470464UL) == 285873025470464UL) ||
        ((bace & 72061992355119104UL) == 72061992355119104UL) ||
        ((bace & 144119587198353408UL) == 144119587198353408UL) ||
        ((bace & 351843723121664UL) == 351843723121664UL) ||
        ((bace & 72127963052770304UL) == 72127963052770304UL) ||
        ((bace & 144185557896004608UL) == 144185557896004608UL) ||
        ((bace & 844424932250624UL) == 844424932250624UL) ||
        ((bace & 72620544261899264UL) == 72620544261899264UL) ||
        ((bace & 144678139105133568UL) == 144678139105133568UL))
      l3_moves.push_back(make_move(7, 21));

    // check for L2 king moves (single captures)
    if (((bace & 4398046527488UL) == 4398046527488UL))
      l2_moves.push_back(make_move(7, 14));
    if (((bace & 4398046658560UL) == 4398046658560UL) ||
        ((bace & 70368744309760UL) == 70368744309760UL))
      l2_moves.push_back(make_move(7, 17));
    if (((bace & 4398048755712UL) == 4398048755712UL) ||
        ((bace & 70368746406912UL) == 70368746406912UL) ||
        ((bace & 562949955535872UL) == 562949955535872UL))
      l2_moves.push_back(make_move(7, 21));
    if (((bace & 4398065532928UL) == 4398065532928UL) ||
        ((bace & 70368763184128UL) == 70368763184128UL) ||
        ((bace & 562949972313088UL) == 562949972313088UL) ||
        ((bace & 9007199271666688UL) == 9007199271666688UL))
      l2_moves.push_back(make_move(7, 24));
    if (((bace & 4398333968384UL) == 4398333968384UL) ||
        ((bace & 70369031619584UL) == 70369031619584UL) ||
        ((bace & 562950240748544UL) == 562950240748544UL) ||
        ((bace & 9007199540102144UL) == 9007199540102144UL) ||
        ((bace & 72057594308609024UL) == 72057594308609024UL))
      l2_moves.push_back(make_move(7, 28));

    // check for L1 king moves (non-capturing)
    if (((bace & 8UL) == 8UL))
      l1_moves.push_back(make_move(7, 3));
    if (((bace & 4UL) == 4UL))
      l1_moves.push_back(make_move(7, 2));
    if (((bace & 1024UL) == 1024UL))
      l1_moves.push_back(make_move(7, 10));
    if (((bace & 17408UL) == 17408UL))
      l1_moves.push_back(make_move(7, 14));
    if (((bace & 148480UL) == 148480UL))
      l1_moves.push_back(make_move(7, 17));
    if (((bace & 2245632UL) == 2245632UL))
      l1_moves.push_back(make_move(7, 21));
    if (((bace & 19022848UL) == 19022848UL))
      l1_moves.push_back(make_move(7, 24));
    if (((bace & 287458304UL) == 287458304UL))
      l1_moves.push_back(make_move(7, 28));
    if (((bace & 2048UL) == 2048UL))
      l1_moves.push_back(make_move(7, 11));
  }

  // ---- end of loc 7

  // ---------- loc == 8 ----------
  if (GET_64(top, 8)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 137438953474UL) == 137438953474UL))
      l2_moves.push_back(make_move(8, 1));
    if (((bace & 35184372219904UL) == 35184372219904UL))
      l2_moves.push_back(make_move(8, 17));

    // check for L1 man moves (non-capturing)
    if (((bace & 4096UL) == 4096UL))
      l1_moves.push_back(make_move(8, 12));
    if (((bace & 8192UL) == 8192UL))
      l1_moves.push_back(make_move(8, 13));
  } else if (GET_64(top, 40)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 412316861442UL) == 412316861442UL) ||
        ((bace & 412316894210UL) == 412316894210UL) ||
        ((bace & 412317418498UL) == 412317418498UL) ||
        ((bace & 4535485497410UL) == 4535485497410UL) ||
        ((bace & 4535486021698UL) == 4535486021698UL) ||
        ((bace & 140874927834178UL) == 140874927834178UL))
      l3_moves.push_back(make_move(8, 1));
    if (((bace & 9042383643738112UL) == 9042383643738112UL) ||
        ((bace & 9042383912173568UL) == 9042383912173568UL) ||
        ((bace & 72092778680680448UL) == 72092778680680448UL) ||
        ((bace & 18049582948810752UL) == 18049582948810752UL) ||
        ((bace & 18049585096294400UL) == 18049585096294400UL) ||
        ((bace & 288265562675609600UL) == 288265562675609600UL) ||
        ((bace & 105553116398592UL) == 105553116398592UL) ||
        ((bace & 105553116398720UL) == 105553116398720UL) ||
        ((bace & 105553116398728UL) == 105553116398728UL) ||
        ((bace & 39582418747520UL) == 39582418747520UL) ||
        ((bace & 39582418747528UL) == 39582418747528UL) ||
        ((bace & 35734128051208UL) == 35734128051208UL))
      l3_moves.push_back(make_move(8, 17));
    if (((bace & 144150372989140992UL) == 144150372989140992UL) ||
        ((bace & 288265562675609600UL) == 288265562675609600UL) ||
        ((bace & 1161084283289600UL) == 1161084283289600UL) ||
        ((bace & 1161084283291648UL) == 1161084283291648UL) ||
        ((bace & 175921865033728UL) == 175921865033728UL) ||
        ((bace & 144678138570350592UL) == 144678138570350592UL) ||
        ((bace & 288793328256819200UL) == 288793328256819200UL) ||
        ((bace & 1688849864499200UL) == 1688849864499200UL) ||
        ((bace & 1688849864501248UL) == 1688849864501248UL) ||
        ((bace & 703687446243328UL) == 703687446243328UL))
      l3_moves.push_back(make_move(8, 22));
    if (((bace & 36063981463011328UL) == 36063981463011328UL) ||
        ((bace & 36591747044220928UL) == 36591747044220928UL) ||
        ((bace & 54043195596218368UL) == 54043195596218368UL))
      l3_moves.push_back(make_move(8, 26));

    // check for L2 king moves (single captures)
    if (((bace & 137438953474UL) == 137438953474UL))
      l2_moves.push_back(make_move(8, 1));
    if (((bace & 35184372219904UL) == 35184372219904UL))
      l2_moves.push_back(make_move(8, 17));
    if (((bace & 35184376414208UL) == 35184376414208UL) ||
        ((bace & 562949957623808UL) == 562949957623808UL))
      l2_moves.push_back(make_move(8, 22));
    if (((bace & 35184443523072UL) == 35184443523072UL) ||
        ((bace & 562950024732672UL) == 562950024732672UL) ||
        ((bace & 18014398576730112UL) == 18014398576730112UL))
      l2_moves.push_back(make_move(8, 26));
    if (((bace & 35186591006720UL) == 35186591006720UL) ||
        ((bace & 562952172216320UL) == 562952172216320UL) ||
        ((bace & 18014400724213760UL) == 18014400724213760UL) ||
        ((bace & 288230378303528960UL) == 288230378303528960UL))
      l2_moves.push_back(make_move(8, 31));

    // check for L1 king moves (non-capturing)
    if (((bace & 32UL) == 32UL))
      l1_moves.push_back(make_move(8, 5));
    if (((bace & 34UL) == 34UL))
      l1_moves.push_back(make_move(8, 1));
    if (((bace & 16UL) == 16UL))
      l1_moves.push_back(make_move(8, 4));
    if (((bace & 4096UL) == 4096UL))
      l1_moves.push_back(make_move(8, 12));
    if (((bace & 8192UL) == 8192UL))
      l1_moves.push_back(make_move(8, 13));
    if (((bace & 139264UL) == 139264UL))
      l1_moves.push_back(make_move(8, 17));
    if (((bace & 4333568UL) == 4333568UL))
      l1_moves.push_back(make_move(8, 22));
    if (((bace & 71442432UL) == 71442432UL))
      l1_moves.push_back(make_move(8, 26));
    if (((bace & 2218926080UL) == 2218926080UL))
      l1_moves.push_back(make_move(8, 31));
  }

  // ---- end of loc 8

  // ---------- loc == 9 ----------
  if (GET_64(top, 9)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 274877906948UL) == 274877906948UL))
      l2_moves.push_back(make_move(9, 2));
    if (((bace & 137438953473UL) == 137438953473UL))
      l2_moves.push_back(make_move(9, 0));
    if (((bace & 35184372154368UL) == 35184372154368UL))
      l2_moves.push_back(make_move(9, 16));
    if (((bace & 70368744439808UL) == 70368744439808UL))
      l2_moves.push_back(make_move(9, 18));

    // check for L1 man moves (non-capturing)
    if (((bace & 8192UL) == 8192UL))
      l1_moves.push_back(make_move(9, 13));
    if (((bace & 16384UL) == 16384UL))
      l1_moves.push_back(make_move(9, 14));
  } else if (GET_64(top, 41)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 824633722884UL) == 824633722884UL))
      l3_moves.push_back(make_move(9, 2));
    if (((bace & 9042383660449792UL) == 9042383660449792UL) ||
        ((bace & 9042384734191616UL) == 9042384734191616UL) ||
        ((bace & 144150373523849216UL) == 144150373523849216UL))
      l3_moves.push_back(make_move(9, 16));
    if (((bace & 72092778948001792UL) == 72092778948001792UL) ||
        ((bace & 72339069552566272UL) == 72339069552566272UL))
      l3_moves.push_back(make_move(9, 20));
    if (((bace & 18084767287476224UL) == 18084767287476224UL) ||
        ((bace & 18084767824347136UL) == 18084767824347136UL) ||
        ((bace & 144185557361360896UL) == 144185557361360896UL) ||
        ((bace & 36099165897621504UL) == 36099165897621504UL) ||
        ((bace & 211106232797184UL) == 211106232797184UL))
      l3_moves.push_back(make_move(9, 18));
    if (((bace & 288300745978281984UL) == 288300745978281984UL) ||
        ((bace & 289356277140701184UL) == 289356277140701184UL))
      l3_moves.push_back(make_move(9, 23));

    // check for L2 king moves (single captures)
    if (((bace & 274877906948UL) == 274877906948UL))
      l2_moves.push_back(make_move(9, 2));
    if (((bace & 137438953473UL) == 137438953473UL))
      l2_moves.push_back(make_move(9, 0));
    if (((bace & 35184372154368UL) == 35184372154368UL))
      l2_moves.push_back(make_move(9, 16));
    if (((bace & 35184373202944UL) == 35184373202944UL) ||
        ((bace & 281474977767424UL) == 281474977767424UL))
      l2_moves.push_back(make_move(9, 20));
    if (((bace & 70368744439808UL) == 70368744439808UL))
      l2_moves.push_back(make_move(9, 18));
    if (((bace & 70368752828416UL) == 70368752828416UL) ||
        ((bace & 1125899915247616UL) == 1125899915247616UL))
      l2_moves.push_back(make_move(9, 23));
    if (((bace & 70368887046144UL) == 70368887046144UL) ||
        ((bace & 1125900049465344UL) == 1125900049465344UL) ||
        ((bace & 36028797153460224UL) == 36028797153460224UL))
      l2_moves.push_back(make_move(9, 27));

    // check for L1 king moves (non-capturing)
    if (((bace & 64UL) == 64UL))
      l1_moves.push_back(make_move(9, 6));
    if (((bace & 68UL) == 68UL))
      l1_moves.push_back(make_move(9, 2));
    if (((bace & 32UL) == 32UL))
      l1_moves.push_back(make_move(9, 5));
    if (((bace & 33UL) == 33UL))
      l1_moves.push_back(make_move(9, 0));
    if (((bace & 8192UL) == 8192UL))
      l1_moves.push_back(make_move(9, 13));
    if (((bace & 73728UL) == 73728UL))
      l1_moves.push_back(make_move(9, 16));
    if (((bace & 1122304UL) == 1122304UL))
      l1_moves.push_back(make_move(9, 20));
    if (((bace & 16384UL) == 16384UL))
      l1_moves.push_back(make_move(9, 14));
    if (((bace & 278528UL) == 278528UL))
      l1_moves.push_back(make_move(9, 18));
    if (((bace & 8667136UL) == 8667136UL))
      l1_moves.push_back(make_move(9, 23));
    if (((bace & 142884864UL) == 142884864UL))
      l1_moves.push_back(make_move(9, 27));
  }

  // ---- end of loc 9

  // ---------- loc == 10 ----------
  if (GET_64(top, 10)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 549755813896UL) == 549755813896UL))
      l2_moves.push_back(make_move(10, 3));
    if (((bace & 274877906946UL) == 274877906946UL))
      l2_moves.push_back(make_move(10, 1));
    if (((bace & 70368744308736UL) == 70368744308736UL))
      l2_moves.push_back(make_move(10, 17));
    if (((bace & 140737488879616UL) == 140737488879616UL))
      l2_moves.push_back(make_move(10, 19));

    // check for L1 man moves (non-capturing)
    if (((bace & 16384UL) == 16384UL))
      l1_moves.push_back(make_move(10, 14));
    if (((bace & 32768UL) == 32768UL))
      l1_moves.push_back(make_move(10, 15));
  } else if (GET_64(top, 42)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 412316860674UL) == 412316860674UL) ||
        ((bace & 412316864770UL) == 412316864770UL) ||
        ((bace & 1374389538850UL) == 1374389538850UL))
      l3_moves.push_back(make_move(10, 1));
    if (((bace & 105553116397824UL) == 105553116397824UL) ||
        ((bace & 105553116397840UL) == 105553116397840UL) ||
        ((bace & 71468255944720UL) == 71468255944720UL) ||
        ((bace & 9077568015826944UL) == 9077568015826944UL) ||
        ((bace & 9077568284262400UL) == 9077568284262400UL) ||
        ((bace & 72127963052769280UL) == 72127963052769280UL) ||
        ((bace & 18084767320899584UL) == 18084767320899584UL) ||
        ((bace & 18084769468383232UL) == 18084769468383232UL) ||
        ((bace & 288300747047698432UL) == 288300747047698432UL))
      l3_moves.push_back(make_move(10, 17));
    if (((bace & 351843723120640UL) == 351843723120640UL) ||
        ((bace & 72127963052769280UL) == 72127963052769280UL) ||
        ((bace & 144185557896003584UL) == 144185557896003584UL) ||
        ((bace & 844424932249600UL) == 844424932249600UL) ||
        ((bace & 72620544261898240UL) == 72620544261898240UL) ||
        ((bace & 144678139105132544UL) == 144678139105132544UL))
      l3_moves.push_back(make_move(10, 21));
    if (((bace & 36169534574952448UL) == 36169534574952448UL) ||
        ((bace & 36169535648694272UL) == 36169535648694272UL) ||
        ((bace & 288371114722721792UL) == 288371114722721792UL))
      l3_moves.push_back(make_move(10, 19));

    // check for L2 king moves (single captures)
    if (((bace & 549755813896UL) == 549755813896UL))
      l2_moves.push_back(make_move(10, 3));
    if (((bace & 274877906946UL) == 274877906946UL))
      l2_moves.push_back(make_move(10, 1));
    if (((bace & 70368744308736UL) == 70368744308736UL))
      l2_moves.push_back(make_move(10, 17));
    if (((bace & 70368746405888UL) == 70368746405888UL) ||
        ((bace & 562949955534848UL) == 562949955534848UL))
      l2_moves.push_back(make_move(10, 21));
    if (((bace & 70368763183104UL) == 70368763183104UL) ||
        ((bace & 562949972312064UL) == 562949972312064UL) ||
        ((bace & 9007199271665664UL) == 9007199271665664UL))
      l2_moves.push_back(make_move(10, 24));
    if (((bace & 70369031618560UL) == 70369031618560UL) ||
        ((bace & 562950240747520UL) == 562950240747520UL) ||
        ((bace & 9007199540101120UL) == 9007199540101120UL) ||
        ((bace & 72057594308608000UL) == 72057594308608000UL))
      l2_moves.push_back(make_move(10, 28));
    if (((bace & 140737488879616UL) == 140737488879616UL))
      l2_moves.push_back(make_move(10, 19));

    // check for L1 king moves (non-capturing)
    if (((bace & 128UL) == 128UL))
      l1_moves.push_back(make_move(10, 7));
    if (((bace & 136UL) == 136UL))
      l1_moves.push_back(make_move(10, 3));
    if (((bace & 64UL) == 64UL))
      l1_moves.push_back(make_move(10, 6));
    if (((bace & 66UL) == 66UL))
      l1_moves.push_back(make_move(10, 1));
    if (((bace & 16384UL) == 16384UL))
      l1_moves.push_back(make_move(10, 14));
    if (((bace & 147456UL) == 147456UL))
      l1_moves.push_back(make_move(10, 17));
    if (((bace & 2244608UL) == 2244608UL))
      l1_moves.push_back(make_move(10, 21));
    if (((bace & 19021824UL) == 19021824UL))
      l1_moves.push_back(make_move(10, 24));
    if (((bace & 287457280UL) == 287457280UL))
      l1_moves.push_back(make_move(10, 28));
    if (((bace & 32768UL) == 32768UL))
      l1_moves.push_back(make_move(10, 15));
    if (((bace & 557056UL) == 557056UL))
      l1_moves.push_back(make_move(10, 19));
  }

  // ---- end of loc 10

  // ---------- loc == 11 ----------
  if (GET_64(top, 11)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 549755813892UL) == 549755813892UL))
      l2_moves.push_back(make_move(11, 2));
    if (((bace & 140737488617472UL) == 140737488617472UL))
      l2_moves.push_back(make_move(11, 18));

    // check for L1 man moves (non-capturing)
    if (((bace & 32768UL) == 32768UL))
      l1_moves.push_back(make_move(11, 15));
  } else if (GET_64(top, 43)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 824633721348UL) == 824633721348UL) ||
        ((bace & 824633729540UL) == 824633729540UL) ||
        ((bace & 824633795076UL) == 824633795076UL) ||
        ((bace & 824634843652UL) == 824634843652UL) ||
        ((bace & 2748779077700UL) == 2748779077700UL) ||
        ((bace & 2748779143236UL) == 2748779143236UL) ||
        ((bace & 2748780191812UL) == 2748780191812UL) ||
        ((bace & 35734127968836UL) == 35734127968836UL) ||
        ((bace & 35734129017412UL) == 35734129017412UL) ||
        ((bace & 282024733581892UL) == 282024733581892UL))
      l3_moves.push_back(make_move(11, 2));
    if (((bace & 211106232795648UL) == 211106232795648UL) ||
        ((bace & 211106232795680UL) == 211106232795680UL) ||
        ((bace & 211106232795681UL) == 211106232795681UL) ||
        ((bace & 142936511889440UL) == 142936511889440UL) ||
        ((bace & 142936511889441UL) == 142936511889441UL) ||
        ((bace & 140874927587841UL) == 140874927587841UL) ||
        ((bace & 18155136031653888UL) == 18155136031653888UL) ||
        ((bace & 18155136568524800UL) == 18155136568524800UL) ||
        ((bace & 144255926105538560UL) == 144255926105538560UL) ||
        ((bace & 36169534641799168UL) == 36169534641799168UL))
      l3_moves.push_back(make_move(11, 18));
    if (((bace & 703687446241280UL) == 703687446241280UL) ||
        ((bace & 703687446241536UL) == 703687446241536UL) ||
        ((bace & 703687446241552UL) == 703687446241552UL) ||
        ((bace & 175921865031936UL) == 175921865031936UL) ||
        ((bace & 175921865031952UL) == 175921865031952UL) ||
        ((bace & 141837004578832UL) == 141837004578832UL) ||
        ((bace & 144255926105538560UL) == 144255926105538560UL) ||
        ((bace & 288371115792007168UL) == 288371115792007168UL) ||
        ((bace & 1688849864499200UL) == 1688849864499200UL) ||
        ((bace & 1688849864499456UL) == 1688849864499456UL) ||
        ((bace & 1688849864499472UL) == 1688849864499472UL) ||
        ((bace & 1161084283289856UL) == 1161084283289856UL) ||
        ((bace & 1161084283289872UL) == 1161084283289872UL) ||
        ((bace & 1126999422836752UL) == 1126999422836752UL) ||
        ((bace & 145241088523796480UL) == 145241088523796480UL) ||
        ((bace & 289356278210265088UL) == 289356278210265088UL))
      l3_moves.push_back(make_move(11, 22));
    if (((bace & 9147936781172736UL) == 9147936781172736UL) ||
        ((bace & 9147936781176832UL) == 9147936781176832UL) ||
        ((bace & 422212505178112UL) == 422212505178112UL) ||
        ((bace & 10133099199430656UL) == 10133099199430656UL) ||
        ((bace & 10133099199434752UL) == 10133099199434752UL) ||
        ((bace & 1407374923436032UL) == 1407374923436032UL) ||
        ((bace & 27021597798137856UL) == 27021597798137856UL) ||
        ((bace & 27021597798141952UL) == 27021597798141952UL) ||
        ((bace & 18295873522143232UL) == 18295873522143232UL))
      l3_moves.push_back(make_move(11, 25));
    if (((bace & 72198332102213632UL) == 72198332102213632UL) ||
        ((bace & 73183494520471552UL) == 73183494520471552UL) ||
        ((bace & 90071993119178752UL) == 90071993119178752UL) ||
        ((bace & 216172782656192512UL) == 216172782656192512UL))
      l3_moves.push_back(make_move(11, 29));

    // check for L2 king moves (single captures)
    if (((bace & 549755813892UL) == 549755813892UL))
      l2_moves.push_back(make_move(11, 2));
    if (((bace & 140737488617472UL) == 140737488617472UL))
      l2_moves.push_back(make_move(11, 18));
    if (((bace & 140737492811776UL) == 140737492811776UL) ||
        ((bace & 1125899911069696UL) == 1125899911069696UL))
      l2_moves.push_back(make_move(11, 22));
    if (((bace & 140737526366208UL) == 140737526366208UL) ||
        ((bace & 1125899944624128UL) == 1125899944624128UL) ||
        ((bace & 18014398543331328UL) == 18014398543331328UL))
      l2_moves.push_back(make_move(11, 25));
    if (((bace & 140738063237120UL) == 140738063237120UL) ||
        ((bace & 1125900481495040UL) == 1125900481495040UL) ||
        ((bace & 18014399080202240UL) == 18014399080202240UL) ||
        ((bace & 144115188617216000UL) == 144115188617216000UL))
      l2_moves.push_back(make_move(11, 29));

    // check for L1 king moves (non-capturing)
    if (((bace & 128UL) == 128UL))
      l1_moves.push_back(make_move(11, 7));
    if (((bace & 132UL) == 132UL))
      l1_moves.push_back(make_move(11, 2));
    if (((bace & 32768UL) == 32768UL))
      l1_moves.push_back(make_move(11, 15));
    if (((bace & 294912UL) == 294912UL))
      l1_moves.push_back(make_move(11, 18));
    if (((bace & 4489216UL) == 4489216UL))
      l1_moves.push_back(make_move(11, 22));
    if (((bace & 38043648UL) == 38043648UL))
      l1_moves.push_back(make_move(11, 25));
    if (((bace & 574914560UL) == 574914560UL))
      l1_moves.push_back(make_move(11, 29));
  }

  // ---- end of loc 11

  // ---------- loc == 12 ----------
  if (GET_64(top, 12)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 1099511627808UL) == 1099511627808UL))
      l2_moves.push_back(make_move(12, 5));
    if (((bace & 281474978807808UL) == 281474978807808UL))
      l2_moves.push_back(make_move(12, 21));

    // check for L1 man moves (non-capturing)
    if (((bace & 65536UL) == 65536UL))
      l1_moves.push_back(make_move(12, 16));
  } else if (GET_64(top, 44)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 3298534899744UL) == 3298534899744UL) ||
        ((bace & 3298535161888UL) == 3298535161888UL) ||
        ((bace & 3298543550496UL) == 3298543550496UL) ||
        ((bace & 3298677768224UL) == 3298677768224UL) ||
        ((bace & 71468256068128UL) == 71468256068128UL) ||
        ((bace & 71468264456736UL) == 71468264456736UL) ||
        ((bace & 71468398674464UL) == 71468398674464UL) ||
        ((bace & 1126999426875936UL) == 1126999426875936UL) ||
        ((bace & 1126999561093664UL) == 1126999561093664UL) ||
        ((bace & 36029896665088544UL) == 36029896665088544UL))
      l3_moves.push_back(make_move(12, 5));
    if (((bace & 1374389535778UL) == 1374389535778UL) ||
        ((bace & 1374389568546UL) == 1374389568546UL) ||
        ((bace & 1374390092834UL) == 1374390092834UL) ||
        ((bace & 5497558171746UL) == 5497558171746UL) ||
        ((bace & 5497558696034UL) == 5497558696034UL) ||
        ((bace & 141837000508514UL) == 141837000508514UL) ||
        ((bace & 412316861698UL) == 412316861698UL) ||
        ((bace & 412316894466UL) == 412316894466UL) ||
        ((bace & 412317418754UL) == 412317418754UL) ||
        ((bace & 4535485497666UL) == 4535485497666UL) ||
        ((bace & 4535486021954UL) == 4535486021954UL) ||
        ((bace & 140874927834434UL) == 140874927834434UL))
      l3_moves.push_back(make_move(12, 1));
    if (((bace & 72339069285171200UL) == 72339069285171200UL) ||
        ((bace & 144396664128405504UL) == 144396664128405504UL) ||
        ((bace & 844424932245504UL) == 844424932245504UL) ||
        ((bace & 844424932246528UL) == 844424932246528UL) ||
        ((bace & 844424932246656UL) == 844424932246656UL) ||
        ((bace & 844424932246664UL) == 844424932246664UL) ||
        ((bace & 351843723117568UL) == 351843723117568UL) ||
        ((bace & 351843723117696UL) == 351843723117696UL) ||
        ((bace & 351843723117704UL) == 351843723117704UL) ||
        ((bace & 285873025466496UL) == 285873025466496UL) ||
        ((bace & 285873025466504UL) == 285873025466504UL) ||
        ((bace & 282024734770184UL) == 282024734770184UL))
      l3_moves.push_back(make_move(12, 21));
    if (((bace & 18295873522106368UL) == 18295873522106368UL) ||
        ((bace & 18295873522139136UL) == 18295873522139136UL) ||
        ((bace & 18295873522141184UL) == 18295873522141184UL) ||
        ((bace & 1407374923431936UL) == 1407374923431936UL) ||
        ((bace & 1407374923433984UL) == 1407374923433984UL) ||
        ((bace & 422212505176064UL) == 422212505176064UL) ||
        ((bace & 27021597798105088UL) == 27021597798105088UL) ||
        ((bace & 27021597798137856UL) == 27021597798137856UL) ||
        ((bace & 27021597798139904UL) == 27021597798139904UL) ||
        ((bace & 10133099199430656UL) == 10133099199430656UL) ||
        ((bace & 10133099199432704UL) == 10133099199432704UL) ||
        ((bace & 9147936781174784UL) == 9147936781174784UL))
      l3_moves.push_back(make_move(12, 25));
    if (((bace & 288511852246204416UL) == 288511852246204416UL) ||
        ((bace & 288511852246728704UL) == 288511852246728704UL) ||
        ((bace & 36310273172701184UL) == 36310273172701184UL) ||
        ((bace & 297237576522203136UL) == 297237576522203136UL) ||
        ((bace & 297237576522727424UL) == 297237576522727424UL) ||
        ((bace & 45035997448699904UL) == 45035997448699904UL) ||
        ((bace & 432345565311860736UL) == 432345565311860736UL) ||
        ((bace & 432345565312385024UL) == 432345565312385024UL) ||
        ((bace & 180143986238357504UL) == 180143986238357504UL))
      l3_moves.push_back(make_move(12, 30));

    // check for L2 king moves (single captures)
    if (((bace & 1099511627808UL) == 1099511627808UL))
      l2_moves.push_back(make_move(12, 5));
    if (((bace & 1099511627810UL) == 1099511627810UL) ||
        ((bace & 137438953730UL) == 137438953730UL))
      l2_moves.push_back(make_move(12, 1));
    if (((bace & 281474978807808UL) == 281474978807808UL))
      l2_moves.push_back(make_move(12, 21));
    if (((bace & 281475012362240UL) == 281475012362240UL) ||
        ((bace & 9007199288360960UL) == 9007199288360960UL))
      l2_moves.push_back(make_move(12, 25));
    if (((bace & 281476086104064UL) == 281476086104064UL) ||
        ((bace & 9007200362102784UL) == 9007200362102784UL) ||
        ((bace & 144115189151760384UL) == 144115189151760384UL))
      l2_moves.push_back(make_move(12, 30));

    // check for L1 king moves (non-capturing)
    if (((bace & 256UL) == 256UL))
      l1_moves.push_back(make_move(12, 8));
    if (((bace & 288UL) == 288UL))
      l1_moves.push_back(make_move(12, 5));
    if (((bace & 290UL) == 290UL))
      l1_moves.push_back(make_move(12, 1));
    if (((bace & 65536UL) == 65536UL))
      l1_moves.push_back(make_move(12, 16));
    if (((bace & 2162688UL) == 2162688UL))
      l1_moves.push_back(make_move(12, 21));
    if (((bace & 35717120UL) == 35717120UL))
      l1_moves.push_back(make_move(12, 25));
    if (((bace & 1109458944UL) == 1109458944UL))
      l1_moves.push_back(make_move(12, 30));
  }

  // ---- end of loc 12

  // ---------- loc == 13 ----------
  if (GET_64(top, 13)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 2199023255616UL) == 2199023255616UL))
      l2_moves.push_back(make_move(13, 6));
    if (((bace & 1099511627792UL) == 1099511627792UL))
      l2_moves.push_back(make_move(13, 4));
    if (((bace & 281474977759232UL) == 281474977759232UL))
      l2_moves.push_back(make_move(13, 20));
    if (((bace & 562949957615616UL) == 562949957615616UL))
      l2_moves.push_back(make_move(13, 22));

    // check for L1 man moves (non-capturing)
    if (((bace & 65536UL) == 65536UL))
      l1_moves.push_back(make_move(13, 16));
    if (((bace & 131072UL) == 131072UL))
      l1_moves.push_back(make_move(13, 17));
  } else if (GET_64(top, 45)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 6597069799488UL) == 6597069799488UL) ||
        ((bace & 6597070323776UL) == 6597070323776UL) ||
        ((bace & 142936512136256UL) == 142936512136256UL))
      l3_moves.push_back(make_move(13, 6));
    if (((bace & 2748779071556UL) == 2748779071556UL) ||
        ((bace & 824633723396UL) == 824633723396UL))
      l3_moves.push_back(make_move(13, 2));
    if (((bace & 72339069552558080UL) == 72339069552558080UL))
      l3_moves.push_back(make_move(13, 20));
    if (((bace & 144678138570342400UL) == 144678138570342400UL) ||
        ((bace & 288793328256811008UL) == 288793328256811008UL) ||
        ((bace & 1688849864491008UL) == 1688849864491008UL) ||
        ((bace & 1688849864493056UL) == 1688849864493056UL) ||
        ((bace & 703687446235136UL) == 703687446235136UL))
      l3_moves.push_back(make_move(13, 22));
    if (((bace & 36591747044212736UL) == 36591747044212736UL) ||
        ((bace & 54043195596210176UL) == 54043195596210176UL))
      l3_moves.push_back(make_move(13, 26));

    // check for L2 king moves (single captures)
    if (((bace & 2199023255616UL) == 2199023255616UL))
      l2_moves.push_back(make_move(13, 6));
    if (((bace & 2199023255620UL) == 2199023255620UL) ||
        ((bace & 274877907460UL) == 274877907460UL))
      l2_moves.push_back(make_move(13, 2));
    if (((bace & 1099511627792UL) == 1099511627792UL))
      l2_moves.push_back(make_move(13, 4));
    if (((bace & 281474977759232UL) == 281474977759232UL))
      l2_moves.push_back(make_move(13, 20));
    if (((bace & 562949957615616UL) == 562949957615616UL))
      l2_moves.push_back(make_move(13, 22));
    if (((bace & 562950024724480UL) == 562950024724480UL) ||
        ((bace & 18014398576721920UL) == 18014398576721920UL))
      l2_moves.push_back(make_move(13, 26));
    if (((bace & 562952172208128UL) == 562952172208128UL) ||
        ((bace & 18014400724205568UL) == 18014400724205568UL) ||
        ((bace & 288230378303520768UL) == 288230378303520768UL))
      l2_moves.push_back(make_move(13, 31));

    // check for L1 king moves (non-capturing)
    if (((bace & 512UL) == 512UL))
      l1_moves.push_back(make_move(13, 9));
    if (((bace & 576UL) == 576UL))
      l1_moves.push_back(make_move(13, 6));
    if (((bace & 580UL) == 580UL))
      l1_moves.push_back(make_move(13, 2));
    if (((bace & 256UL) == 256UL))
      l1_moves.push_back(make_move(13, 8));
    if (((bace & 272UL) == 272UL))
      l1_moves.push_back(make_move(13, 4));
    if (((bace & 65536UL) == 65536UL))
      l1_moves.push_back(make_move(13, 16));
    if (((bace & 1114112UL) == 1114112UL))
      l1_moves.push_back(make_move(13, 20));
    if (((bace & 131072UL) == 131072UL))
      l1_moves.push_back(make_move(13, 17));
    if (((bace & 4325376UL) == 4325376UL))
      l1_moves.push_back(make_move(13, 22));
    if (((bace & 71434240UL) == 71434240UL))
      l1_moves.push_back(make_move(13, 26));
    if (((bace & 2218917888UL) == 2218917888UL))
      l1_moves.push_back(make_move(13, 31));
  }

  // ---- end of loc 13

  // ---------- loc == 14 ----------
  if (GET_64(top, 14)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 4398046511232UL) == 4398046511232UL))
      l2_moves.push_back(make_move(14, 7));
    if (((bace & 2199023255584UL) == 2199023255584UL))
      l2_moves.push_back(make_move(14, 5));
    if (((bace & 562949955518464UL) == 562949955518464UL))
      l2_moves.push_back(make_move(14, 21));
    if (((bace & 1125899915231232UL) == 1125899915231232UL))
      l2_moves.push_back(make_move(14, 23));

    // check for L1 man moves (non-capturing)
    if (((bace & 131072UL) == 131072UL))
      l1_moves.push_back(make_move(14, 17));
    if (((bace & 262144UL) == 262144UL))
      l1_moves.push_back(make_move(14, 18));
  } else if (GET_64(top, 46)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 3298534887456UL) == 3298534887456UL))
      l3_moves.push_back(make_move(14, 5));
    if (((bace & 844424932233216UL) == 844424932233216UL) ||
        ((bace & 72620544261881856UL) == 72620544261881856UL) ||
        ((bace & 144678139105116160UL) == 144678139105116160UL))
      l3_moves.push_back(make_move(14, 21));
    if (((bace & 289356277140684800UL) == 289356277140684800UL))
      l3_moves.push_back(make_move(14, 23));

    // check for L2 king moves (single captures)
    if (((bace & 4398046511232UL) == 4398046511232UL))
      l2_moves.push_back(make_move(14, 7));
    if (((bace & 4398046511240UL) == 4398046511240UL) ||
        ((bace & 549755814920UL) == 549755814920UL))
      l2_moves.push_back(make_move(14, 3));
    if (((bace & 2199023255584UL) == 2199023255584UL))
      l2_moves.push_back(make_move(14, 5));
    if (((bace & 2199023255585UL) == 2199023255585UL) ||
        ((bace & 137438953985UL) == 137438953985UL))
      l2_moves.push_back(make_move(14, 0));
    if (((bace & 562949955518464UL) == 562949955518464UL))
      l2_moves.push_back(make_move(14, 21));
    if (((bace & 562949972295680UL) == 562949972295680UL) ||
        ((bace & 9007199271649280UL) == 9007199271649280UL))
      l2_moves.push_back(make_move(14, 24));
    if (((bace & 562950240731136UL) == 562950240731136UL) ||
        ((bace & 9007199540084736UL) == 9007199540084736UL) ||
        ((bace & 72057594308591616UL) == 72057594308591616UL))
      l2_moves.push_back(make_move(14, 28));
    if (((bace & 1125899915231232UL) == 1125899915231232UL))
      l2_moves.push_back(make_move(14, 23));
    if (((bace & 1125900049448960UL) == 1125900049448960UL) ||
        ((bace & 36028797153443840UL) == 36028797153443840UL))
      l2_moves.push_back(make_move(14, 27));

    // check for L1 king moves (non-capturing)
    if (((bace & 1024UL) == 1024UL))
      l1_moves.push_back(make_move(14, 10));
    if (((bace & 1152UL) == 1152UL))
      l1_moves.push_back(make_move(14, 7));
    if (((bace & 1160UL) == 1160UL))
      l1_moves.push_back(make_move(14, 3));
    if (((bace & 512UL) == 512UL))
      l1_moves.push_back(make_move(14, 9));
    if (((bace & 544UL) == 544UL))
      l1_moves.push_back(make_move(14, 5));
    if (((bace & 545UL) == 545UL))
      l1_moves.push_back(make_move(14, 0));
    if (((bace & 131072UL) == 131072UL))
      l1_moves.push_back(make_move(14, 17));
    if (((bace & 2228224UL) == 2228224UL))
      l1_moves.push_back(make_move(14, 21));
    if (((bace & 19005440UL) == 19005440UL))
      l1_moves.push_back(make_move(14, 24));
    if (((bace & 287440896UL) == 287440896UL))
      l1_moves.push_back(make_move(14, 28));
    if (((bace & 262144UL) == 262144UL))
      l1_moves.push_back(make_move(14, 18));
    if (((bace & 8650752UL) == 8650752UL))
      l1_moves.push_back(make_move(14, 23));
    if (((bace & 142868480UL) == 142868480UL))
      l1_moves.push_back(make_move(14, 27));
  }

  // ---- end of loc 14

  // ---------- loc == 15 ----------
  if (GET_64(top, 15)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 4398046511168UL) == 4398046511168UL))
      l2_moves.push_back(make_move(15, 6));
    if (((bace & 1125899911036928UL) == 1125899911036928UL))
      l2_moves.push_back(make_move(15, 22));

    // check for L1 man moves (non-capturing)
    if (((bace & 262144UL) == 262144UL))
      l1_moves.push_back(make_move(15, 18));
    if (((bace & 524288UL) == 524288UL))
      l1_moves.push_back(make_move(15, 19));
  } else if (GET_64(top, 47)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 6597069774912UL) == 6597069774912UL) ||
        ((bace & 6597069840448UL) == 6597069840448UL) ||
        ((bace & 6597070889024UL) == 6597070889024UL) ||
        ((bace & 39582418666048UL) == 39582418666048UL) ||
        ((bace & 39582419714624UL) == 39582419714624UL) ||
        ((bace & 285873024279104UL) == 285873024279104UL))
      l3_moves.push_back(make_move(15, 6));
    if (((bace & 4535485464898UL) == 4535485464898UL) ||
        ((bace & 4535485468994UL) == 4535485468994UL) ||
        ((bace & 5497558143074UL) == 5497558143074UL) ||
        ((bace & 412316861698UL) == 412316861698UL) ||
        ((bace & 412316865794UL) == 412316865794UL) ||
        ((bace & 1374389539874UL) == 1374389539874UL))
      l3_moves.push_back(make_move(15, 1));
    if (((bace & 1688849864466432UL) == 1688849864466432UL) ||
        ((bace & 1688849864466688UL) == 1688849864466688UL) ||
        ((bace & 1688849864466704UL) == 1688849864466704UL) ||
        ((bace & 1161084283257088UL) == 1161084283257088UL) ||
        ((bace & 1161084283257104UL) == 1161084283257104UL) ||
        ((bace & 1126999422803984UL) == 1126999422803984UL) ||
        ((bace & 145241088523763712UL) == 145241088523763712UL) ||
        ((bace & 289356278210232320UL) == 289356278210232320UL))
      l3_moves.push_back(make_move(15, 22));
    if (((bace & 10133099199397888UL) == 10133099199397888UL) ||
        ((bace & 10133099199401984UL) == 10133099199401984UL) ||
        ((bace & 1407374923403264UL) == 1407374923403264UL) ||
        ((bace & 27021597798105088UL) == 27021597798105088UL) ||
        ((bace & 27021597798109184UL) == 27021597798109184UL) ||
        ((bace & 18295873522110464UL) == 18295873522110464UL))
      l3_moves.push_back(make_move(15, 25));
    if (((bace & 73183494520438784UL) == 73183494520438784UL) ||
        ((bace & 90071993119145984UL) == 90071993119145984UL) ||
        ((bace & 216172782656159744UL) == 216172782656159744UL))
      l3_moves.push_back(make_move(15, 29));

    // check for L2 king moves (single captures)
    if (((bace & 4398046511168UL) == 4398046511168UL))
      l2_moves.push_back(make_move(15, 6));
    if (((bace & 4398046511170UL) == 4398046511170UL) ||
        ((bace & 274877907970UL) == 274877907970UL))
      l2_moves.push_back(make_move(15, 1));
    if (((bace & 1125899911036928UL) == 1125899911036928UL))
      l2_moves.push_back(make_move(15, 22));
    if (((bace & 1125899944591360UL) == 1125899944591360UL) ||
        ((bace & 18014398543298560UL) == 18014398543298560UL))
      l2_moves.push_back(make_move(15, 25));
    if (((bace & 1125900481462272UL) == 1125900481462272UL) ||
        ((bace & 18014399080169472UL) == 18014399080169472UL) ||
        ((bace & 144115188617183232UL) == 144115188617183232UL))
      l2_moves.push_back(make_move(15, 29));

    // check for L1 king moves (non-capturing)
    if (((bace & 2048UL) == 2048UL))
      l1_moves.push_back(make_move(15, 11));
    if (((bace & 1024UL) == 1024UL))
      l1_moves.push_back(make_move(15, 10));
    if (((bace & 1088UL) == 1088UL))
      l1_moves.push_back(make_move(15, 6));
    if (((bace & 1090UL) == 1090UL))
      l1_moves.push_back(make_move(15, 1));
    if (((bace & 262144UL) == 262144UL))
      l1_moves.push_back(make_move(15, 18));
    if (((bace & 4456448UL) == 4456448UL))
      l1_moves.push_back(make_move(15, 22));
    if (((bace & 38010880UL) == 38010880UL))
      l1_moves.push_back(make_move(15, 25));
    if (((bace & 574881792UL) == 574881792UL))
      l1_moves.push_back(make_move(15, 29));
    if (((bace & 524288UL) == 524288UL))
      l1_moves.push_back(make_move(15, 19));
  }

  // ---- end of loc 15

  // ---------- loc == 16 ----------
  if (GET_64(top, 16)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 35184372089344UL) == 35184372089344UL))
      l2_moves.push_back(make_move(16, 9));
    if (((bace & 9007199288295424UL) == 9007199288295424UL))
      l2_moves.push_back(make_move(16, 25));

    // check for L1 man moves (non-capturing)
    if (((bace & 1048576UL) == 1048576UL))
      l1_moves.push_back(make_move(16, 20));
    if (((bace & 2097152UL) == 2097152UL))
      l1_moves.push_back(make_move(16, 21));
  } else if (GET_64(top, 48)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 105553116529152UL) == 105553116529152UL) ||
        ((bace & 105553124917760UL) == 105553124917760UL) ||
        ((bace & 105553259135488UL) == 105553259135488UL) ||
        ((bace & 1161084287336960UL) == 1161084287336960UL) ||
        ((bace & 1161084421554688UL) == 1161084421554688UL) ||
        ((bace & 36063981525549568UL) == 36063981525549568UL) ||
        ((bace & 35459249996292UL) == 35459249996292UL) ||
        ((bace & 35321811042817UL) == 35321811042817UL))
      l3_moves.push_back(make_move(16, 9));
    if (((bace & 39582418633280UL) == 39582418633280UL) ||
        ((bace & 39582419157568UL) == 39582419157568UL) ||
        ((bace & 175921860970048UL) == 175921860970048UL) ||
        ((bace & 6597069807680UL) == 6597069807680UL) ||
        ((bace & 6597070331968UL) == 6597070331968UL) ||
        ((bace & 142936512144448UL) == 142936512144448UL))
      l3_moves.push_back(make_move(16, 6));
    if (((bace & 35734127905348UL) == 35734127905348UL) ||
        ((bace & 2748779079748UL) == 2748779079748UL) ||
        ((bace & 824633731588UL) == 824633731588UL))
      l3_moves.push_back(make_move(16, 2));
    if (((bace & 27021597798039552UL) == 27021597798039552UL) ||
        ((bace & 27021597798072320UL) == 27021597798072320UL) ||
        ((bace & 27021597798074368UL) == 27021597798074368UL) ||
        ((bace & 10133099199365120UL) == 10133099199365120UL) ||
        ((bace & 10133099199367168UL) == 10133099199367168UL) ||
        ((bace & 9147936781109248UL) == 9147936781109248UL))
      l3_moves.push_back(make_move(16, 25));
    if (((bace & 297237576522137600UL) == 297237576522137600UL) ||
        ((bace & 297237576522661888UL) == 297237576522661888UL) ||
        ((bace & 45035997448634368UL) == 45035997448634368UL) ||
        ((bace & 432345565311795200UL) == 432345565311795200UL) ||
        ((bace & 432345565312319488UL) == 432345565312319488UL) ||
        ((bace & 180143986238291968UL) == 180143986238291968UL))
      l3_moves.push_back(make_move(16, 30));

    // check for L2 king moves (single captures)
    if (((bace & 35184372089344UL) == 35184372089344UL))
      l2_moves.push_back(make_move(16, 9));
    if (((bace & 35184372089408UL) == 35184372089408UL) ||
        ((bace & 2199023263808UL) == 2199023263808UL))
      l2_moves.push_back(make_move(16, 6));
    if (((bace & 35184372089412UL) == 35184372089412UL) ||
        ((bace & 2199023263812UL) == 2199023263812UL) ||
        ((bace & 274877915652UL) == 274877915652UL))
      l2_moves.push_back(make_move(16, 2));
    if (((bace & 9007199288295424UL) == 9007199288295424UL))
      l2_moves.push_back(make_move(16, 25));
    if (((bace & 9007200362037248UL) == 9007200362037248UL) ||
        ((bace & 144115189151694848UL) == 144115189151694848UL))
      l2_moves.push_back(make_move(16, 30));

    // check for L1 king moves (non-capturing)
    if (((bace & 8192UL) == 8192UL))
      l1_moves.push_back(make_move(16, 13));
    if (((bace & 8704UL) == 8704UL))
      l1_moves.push_back(make_move(16, 9));
    if (((bace & 8768UL) == 8768UL))
      l1_moves.push_back(make_move(16, 6));
    if (((bace & 8772UL) == 8772UL))
      l1_moves.push_back(make_move(16, 2));
    if (((bace & 4096UL) == 4096UL))
      l1_moves.push_back(make_move(16, 12));
    if (((bace & 1048576UL) == 1048576UL))
      l1_moves.push_back(make_move(16, 20));
    if (((bace & 2097152UL) == 2097152UL))
      l1_moves.push_back(make_move(16, 21));
    if (((bace & 35651584UL) == 35651584UL))
      l1_moves.push_back(make_move(16, 25));
    if (((bace & 1109393408UL) == 1109393408UL))
      l1_moves.push_back(make_move(16, 30));
  }

  // ---- end of loc 16

  // ---------- loc == 17 ----------
  if (GET_64(top, 17)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 70368744178688UL) == 70368744178688UL))
      l2_moves.push_back(make_move(17, 10));
    if (((bace & 35184372089088UL) == 35184372089088UL))
      l2_moves.push_back(make_move(17, 8));
    if (((bace & 9007199271518208UL) == 9007199271518208UL))
      l2_moves.push_back(make_move(17, 24));
    if (((bace & 18014398576590848UL) == 18014398576590848UL))
      l2_moves.push_back(make_move(17, 26));

    // check for L1 man moves (non-capturing)
    if (((bace & 2097152UL) == 2097152UL))
      l1_moves.push_back(make_move(17, 21));
    if (((bace & 4194304UL) == 4194304UL))
      l1_moves.push_back(make_move(17, 22));
  } else if (GET_64(top, 49)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 211106233058304UL) == 211106233058304UL) ||
        ((bace & 70918499992584UL) == 70918499992584UL) ||
        ((bace & 70643622085634UL) == 70643622085634UL))
      l3_moves.push_back(make_move(17, 10));
    if (((bace & 35321811042562UL) == 35321811042562UL))
      l3_moves.push_back(make_move(17, 8));
    if (((bace & 54043195596079104UL) == 54043195596079104UL))
      l3_moves.push_back(make_move(17, 26));

    // check for L2 king moves (single captures)
    if (((bace & 70368744178688UL) == 70368744178688UL))
      l2_moves.push_back(make_move(17, 10));
    if (((bace & 70368744178816UL) == 70368744178816UL) ||
        ((bace & 4398046527616UL) == 4398046527616UL))
      l2_moves.push_back(make_move(17, 7));
    if (((bace & 70368744178824UL) == 70368744178824UL) ||
        ((bace & 4398046527624UL) == 4398046527624UL) ||
        ((bace & 549755831304UL) == 549755831304UL))
      l2_moves.push_back(make_move(17, 3));
    if (((bace & 35184372089088UL) == 35184372089088UL))
      l2_moves.push_back(make_move(17, 8));
    if (((bace & 35184372089104UL) == 35184372089104UL) ||
        ((bace & 1099511635984UL) == 1099511635984UL))
      l2_moves.push_back(make_move(17, 4));
    if (((bace & 9007199271518208UL) == 9007199271518208UL))
      l2_moves.push_back(make_move(17, 24));
    if (((bace & 9007199539953664UL) == 9007199539953664UL) ||
        ((bace & 72057594308460544UL) == 72057594308460544UL))
      l2_moves.push_back(make_move(17, 28));
    if (((bace & 18014398576590848UL) == 18014398576590848UL))
      l2_moves.push_back(make_move(17, 26));
    if (((bace & 18014400724074496UL) == 18014400724074496UL) ||
        ((bace & 288230378303389696UL) == 288230378303389696UL))
      l2_moves.push_back(make_move(17, 31));

    // check for L1 king moves (non-capturing)
    if (((bace & 16384UL) == 16384UL))
      l1_moves.push_back(make_move(17, 14));
    if (((bace & 17408UL) == 17408UL))
      l1_moves.push_back(make_move(17, 10));
    if (((bace & 17536UL) == 17536UL))
      l1_moves.push_back(make_move(17, 7));
    if (((bace & 17544UL) == 17544UL))
      l1_moves.push_back(make_move(17, 3));
    if (((bace & 8192UL) == 8192UL))
      l1_moves.push_back(make_move(17, 13));
    if (((bace & 8448UL) == 8448UL))
      l1_moves.push_back(make_move(17, 8));
    if (((bace & 8464UL) == 8464UL))
      l1_moves.push_back(make_move(17, 4));
    if (((bace & 2097152UL) == 2097152UL))
      l1_moves.push_back(make_move(17, 21));
    if (((bace & 18874368UL) == 18874368UL))
      l1_moves.push_back(make_move(17, 24));
    if (((bace & 287309824UL) == 287309824UL))
      l1_moves.push_back(make_move(17, 28));
    if (((bace & 4194304UL) == 4194304UL))
      l1_moves.push_back(make_move(17, 22));
    if (((bace & 71303168UL) == 71303168UL))
      l1_moves.push_back(make_move(17, 26));
    if (((bace & 2218786816UL) == 2218786816UL))
      l1_moves.push_back(make_move(17, 31));
  }

  // ---- end of loc 17

  // ---------- loc == 18 ----------
  if (GET_64(top, 18)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 140737488357376UL) == 140737488357376UL))
      l2_moves.push_back(make_move(18, 11));
    if (((bace & 70368744178176UL) == 70368744178176UL))
      l2_moves.push_back(make_move(18, 9));
    if (((bace & 18014398543036416UL) == 18014398543036416UL))
      l2_moves.push_back(make_move(18, 25));
    if (((bace & 36028797153181696UL) == 36028797153181696UL))
      l2_moves.push_back(make_move(18, 27));

    // check for L1 man moves (non-capturing)
    if (((bace & 4194304UL) == 4194304UL))
      l1_moves.push_back(make_move(18, 22));
    if (((bace & 8388608UL) == 8388608UL))
      l1_moves.push_back(make_move(18, 23));
  } else if (GET_64(top, 50)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 141287244171268UL) == 141287244171268UL))
      l3_moves.push_back(make_move(18, 11));
    if (((bace & 70643622085124UL) == 70643622085124UL) ||
        ((bace & 70506183131649UL) == 70506183131649UL) ||
        ((bace & 105553116332544UL) == 105553116332544UL) ||
        ((bace & 105553117381120UL) == 105553117381120UL) ||
        ((bace & 351843721945600UL) == 351843721945600UL))
      l3_moves.push_back(make_move(18, 9));
    if (((bace & 71468255810080UL) == 71468255810080UL) ||
        ((bace & 3298534903840UL) == 3298534903840UL))
      l3_moves.push_back(make_move(18, 5));
    if (((bace & 27021597797842944UL) == 27021597797842944UL) ||
        ((bace & 27021597797847040UL) == 27021597797847040UL) ||
        ((bace & 18295873521848320UL) == 18295873521848320UL))
      l3_moves.push_back(make_move(18, 25));
    if (((bace & 90071993118883840UL) == 90071993118883840UL) ||
        ((bace & 216172782655897600UL) == 216172782655897600UL))
      l3_moves.push_back(make_move(18, 29));

    // check for L2 king moves (single captures)
    if (((bace & 140737488357376UL) == 140737488357376UL))
      l2_moves.push_back(make_move(18, 11));
    if (((bace & 70368744178176UL) == 70368744178176UL))
      l2_moves.push_back(make_move(18, 9));
    if (((bace & 70368744178208UL) == 70368744178208UL) ||
        ((bace & 2199023271968UL) == 2199023271968UL))
      l2_moves.push_back(make_move(18, 5));
    if (((bace & 70368744178209UL) == 70368744178209UL) ||
        ((bace & 2199023271969UL) == 2199023271969UL) ||
        ((bace & 137438970369UL) == 137438970369UL))
      l2_moves.push_back(make_move(18, 0));
    if (((bace & 18014398543036416UL) == 18014398543036416UL))
      l2_moves.push_back(make_move(18, 25));
    if (((bace & 18014399079907328UL) == 18014399079907328UL) ||
        ((bace & 144115188616921088UL) == 144115188616921088UL))
      l2_moves.push_back(make_move(18, 29));
    if (((bace & 36028797153181696UL) == 36028797153181696UL))
      l2_moves.push_back(make_move(18, 27));

    // check for L1 king moves (non-capturing)
    if (((bace & 32768UL) == 32768UL))
      l1_moves.push_back(make_move(18, 15));
    if (((bace & 34816UL) == 34816UL))
      l1_moves.push_back(make_move(18, 11));
    if (((bace & 16384UL) == 16384UL))
      l1_moves.push_back(make_move(18, 14));
    if (((bace & 16896UL) == 16896UL))
      l1_moves.push_back(make_move(18, 9));
    if (((bace & 16928UL) == 16928UL))
      l1_moves.push_back(make_move(18, 5));
    if (((bace & 16929UL) == 16929UL))
      l1_moves.push_back(make_move(18, 0));
    if (((bace & 4194304UL) == 4194304UL))
      l1_moves.push_back(make_move(18, 22));
    if (((bace & 37748736UL) == 37748736UL))
      l1_moves.push_back(make_move(18, 25));
    if (((bace & 574619648UL) == 574619648UL))
      l1_moves.push_back(make_move(18, 29));
    if (((bace & 8388608UL) == 8388608UL))
      l1_moves.push_back(make_move(18, 23));
    if (((bace & 142606336UL) == 142606336UL))
      l1_moves.push_back(make_move(18, 27));
  }

  // ---- end of loc 18

  // ---------- loc == 19 ----------
  if (GET_64(top, 19)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 140737488356352UL) == 140737488356352UL))
      l2_moves.push_back(make_move(19, 10));
    if (((bace & 36028797086072832UL) == 36028797086072832UL))
      l2_moves.push_back(make_move(19, 26));

    // check for L1 man moves (non-capturing)
    if (((bace & 8388608UL) == 8388608UL))
      l1_moves.push_back(make_move(19, 23));
  } else if (GET_64(top, 51)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 141287244170248UL) == 141287244170248UL) ||
        ((bace & 141012366263298UL) == 141012366263298UL) ||
        ((bace & 211106232665088UL) == 211106232665088UL) ||
        ((bace & 211106234762240UL) == 211106234762240UL) ||
        ((bace & 211106251539456UL) == 211106251539456UL) ||
        ((bace & 211106519974912UL) == 211106519974912UL) ||
        ((bace & 703687443891200UL) == 703687443891200UL) ||
        ((bace & 703687460668416UL) == 703687460668416UL) ||
        ((bace & 703687729103872UL) == 703687729103872UL) ||
        ((bace & 9147936760022016UL) == 9147936760022016UL) ||
        ((bace & 9147937028457472UL) == 9147937028457472UL) ||
        ((bace & 72198331796964352UL) == 72198331796964352UL))
      l3_moves.push_back(make_move(19, 10));
    if (((bace & 142936511620160UL) == 142936511620160UL) ||
        ((bace & 142936511685696UL) == 142936511685696UL) ||
        ((bace & 142936512734272UL) == 142936512734272UL) ||
        ((bace & 175921860511296UL) == 175921860511296UL) ||
        ((bace & 175921861559872UL) == 175921861559872UL) ||
        ((bace & 422212466124352UL) == 422212466124352UL) ||
        ((bace & 6597069807680UL) == 6597069807680UL) ||
        ((bace & 6597069873216UL) == 6597069873216UL) ||
        ((bace & 6597070921792UL) == 6597070921792UL) ||
        ((bace & 39582418698816UL) == 39582418698816UL) ||
        ((bace & 39582419747392UL) == 39582419747392UL) ||
        ((bace & 285873024311872UL) == 285873024311872UL))
      l3_moves.push_back(make_move(19, 6));
    if (((bace & 140874927310146UL) == 140874927310146UL) ||
        ((bace & 140874927314242UL) == 140874927314242UL) ||
        ((bace & 141836999988322UL) == 141836999988322UL) ||
        ((bace & 4535485497666UL) == 4535485497666UL) ||
        ((bace & 4535485501762UL) == 4535485501762UL) ||
        ((bace & 5497558175842UL) == 5497558175842UL) ||
        ((bace & 412316894466UL) == 412316894466UL) ||
        ((bace & 412316898562UL) == 412316898562UL) ||
        ((bace & 1374389572642UL) == 1374389572642UL))
      l3_moves.push_back(make_move(19, 1));
    if (((bace & 54043195595685888UL) == 54043195595685888UL) ||
        ((bace & 54043195595694080UL) == 54043195595694080UL) ||
        ((bace & 54043195595694336UL) == 54043195595694336UL) ||
        ((bace & 54043195595694352UL) == 54043195595694352UL) ||
        ((bace & 36591747043696640UL) == 36591747043696640UL) ||
        ((bace & 36591747043696896UL) == 36591747043696896UL) ||
        ((bace & 36591747043696912UL) == 36591747043696912UL) ||
        ((bace & 36063981462487296UL) == 36063981462487296UL) ||
        ((bace & 36063981462487312UL) == 36063981462487312UL) ||
        ((bace & 36029896602034192UL) == 36029896602034192UL))
      l3_moves.push_back(make_move(19, 26));
    if (((bace & 180143986237767680UL) == 180143986237767680UL) ||
        ((bace & 180143986237833216UL) == 180143986237833216UL) ||
        ((bace & 180143986237837312UL) == 180143986237837312UL) ||
        ((bace & 45035997448175616UL) == 45035997448175616UL) ||
        ((bace & 45035997448179712UL) == 45035997448179712UL) ||
        ((bace & 36310273172180992UL) == 36310273172180992UL) ||
        ((bace & 432345565311795200UL) == 432345565311795200UL) ||
        ((bace & 432345565311860736UL) == 432345565311860736UL) ||
        ((bace & 432345565311864832UL) == 432345565311864832UL) ||
        ((bace & 297237576522203136UL) == 297237576522203136UL) ||
        ((bace & 297237576522207232UL) == 297237576522207232UL) ||
        ((bace & 288511852246208512UL) == 288511852246208512UL))
      l3_moves.push_back(make_move(19, 30));

    // check for L2 king moves (single captures)
    if (((bace & 140737488356352UL) == 140737488356352UL))
      l2_moves.push_back(make_move(19, 10));
    if (((bace & 140737488356416UL) == 140737488356416UL) ||
        ((bace & 4398046543936UL) == 4398046543936UL))
      l2_moves.push_back(make_move(19, 6));
    if (((bace & 140737488356418UL) == 140737488356418UL) ||
        ((bace & 4398046543938UL) == 4398046543938UL) ||
        ((bace & 274877940738UL) == 274877940738UL))
      l2_moves.push_back(make_move(19, 1));
    if (((bace & 36028797086072832UL) == 36028797086072832UL))
      l2_moves.push_back(make_move(19, 26));
    if (((bace & 36028798159814656UL) == 36028798159814656UL) ||
        ((bace & 288230377233842176UL) == 288230377233842176UL))
      l2_moves.push_back(make_move(19, 30));

    // check for L1 king moves (non-capturing)
    if (((bace & 32768UL) == 32768UL))
      l1_moves.push_back(make_move(19, 15));
    if (((bace & 33792UL) == 33792UL))
      l1_moves.push_back(make_move(19, 10));
    if (((bace & 33856UL) == 33856UL))
      l1_moves.push_back(make_move(19, 6));
    if (((bace & 33858UL) == 33858UL))
      l1_moves.push_back(make_move(19, 1));
    if (((bace & 8388608UL) == 8388608UL))
      l1_moves.push_back(make_move(19, 23));
    if (((bace & 75497472UL) == 75497472UL))
      l1_moves.push_back(make_move(19, 26));
    if (((bace & 1149239296UL) == 1149239296UL))
      l1_moves.push_back(make_move(19, 30));
  }

  // ---- end of loc 19

  // ---------- loc == 20 ----------
  if (GET_64(top, 20)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 281474976718848UL) == 281474976718848UL))
      l2_moves.push_back(make_move(20, 13));
    if (((bace & 72057594574798848UL) == 72057594574798848UL))
      l2_moves.push_back(make_move(20, 29));

    // check for L1 man moves (non-capturing)
    if (((bace & 16777216UL) == 16777216UL))
      l1_moves.push_back(make_move(20, 24));
  } else if (GET_64(top, 52)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 844424934334464UL) == 844424934334464UL) ||
        ((bace & 844425001443328UL) == 844425001443328UL) ||
        ((bace & 844427148926976UL) == 844427148926976UL) ||
        ((bace & 18295873553440768UL) == 18295873553440768UL) ||
        ((bace & 18295875700924416UL) == 18295875700924416UL) ||
        ((bace & 288511853280239616UL) == 288511853280239616UL) ||
        ((bace & 283673999974464UL) == 283673999974464UL) ||
        ((bace & 283673999974468UL) == 283673999974468UL) ||
        ((bace & 281749854626308UL) == 281749854626308UL) ||
        ((bace & 282574488346640UL) == 282574488346640UL))
      l3_moves.push_back(make_move(20, 13));
    if (((bace & 351843721159168UL) == 351843721159168UL) ||
        ((bace & 351843729547776UL) == 351843729547776UL) ||
        ((bace & 351843863765504UL) == 351843863765504UL) ||
        ((bace & 1407374891966976UL) == 1407374891966976UL) ||
        ((bace & 1407375026184704UL) == 1407375026184704UL) ||
        ((bace & 36310272130179584UL) == 36310272130179584UL) ||
        ((bace & 281749854626308UL) == 281749854626308UL) ||
        ((bace & 281612415672833UL) == 281612415672833UL) ||
        ((bace & 105553116594688UL) == 105553116594688UL) ||
        ((bace & 105553124983296UL) == 105553124983296UL) ||
        ((bace & 105553259201024UL) == 105553259201024UL) ||
        ((bace & 1161084287402496UL) == 1161084287402496UL) ||
        ((bace & 1161084421620224UL) == 1161084421620224UL) ||
        ((bace & 36063981525615104UL) == 36063981525615104UL) ||
        ((bace & 35459250061828UL) == 35459250061828UL) ||
        ((bace & 35321811108353UL) == 35321811108353UL))
      l3_moves.push_back(make_move(20, 9));
    if (((bace & 285873023263296UL) == 285873023263296UL) ||
        ((bace & 285873023787584UL) == 285873023787584UL) ||
        ((bace & 422212465600064UL) == 422212465600064UL) ||
        ((bace & 39582418698816UL) == 39582418698816UL) ||
        ((bace & 39582419223104UL) == 39582419223104UL) ||
        ((bace & 175921861035584UL) == 175921861035584UL) ||
        ((bace & 6597069873216UL) == 6597069873216UL) ||
        ((bace & 6597070397504UL) == 6597070397504UL) ||
        ((bace & 142936512209984UL) == 142936512209984UL))
      l3_moves.push_back(make_move(20, 6));
    if (((bace & 282024732535364UL) == 282024732535364UL) ||
        ((bace & 35734127970884UL) == 35734127970884UL) ||
        ((bace & 2748779145284UL) == 2748779145284UL) ||
        ((bace & 824633797124UL) == 824633797124UL))
      l3_moves.push_back(make_move(20, 2));
    if (((bace & 216172782654849024UL) == 216172782654849024UL) ||
        ((bace & 216172782655111168UL) == 216172782655111168UL) ||
        ((bace & 216172782655143936UL) == 216172782655143936UL) ||
        ((bace & 216172782655145984UL) == 216172782655145984UL) ||
        ((bace & 90071993118097408UL) == 90071993118097408UL) ||
        ((bace & 90071993118130176UL) == 90071993118130176UL) ||
        ((bace & 90071993118132224UL) == 90071993118132224UL) ||
        ((bace & 73183494519422976UL) == 73183494519422976UL) ||
        ((bace & 73183494519425024UL) == 73183494519425024UL) ||
        ((bace & 72198332101167104UL) == 72198332101167104UL))
      l3_moves.push_back(make_move(20, 29));

    // check for L2 king moves (single captures)
    if (((bace & 281474976718848UL) == 281474976718848UL))
      l2_moves.push_back(make_move(20, 13));
    if (((bace & 281474976719360UL) == 281474976719360UL) ||
        ((bace & 35184372154880UL) == 35184372154880UL))
      l2_moves.push_back(make_move(20, 9));
    if (((bace & 281474976719424UL) == 281474976719424UL) ||
        ((bace & 35184372154944UL) == 35184372154944UL) ||
        ((bace & 2199023329344UL) == 2199023329344UL))
      l2_moves.push_back(make_move(20, 6));
    if (((bace & 281474976719428UL) == 281474976719428UL) ||
        ((bace & 35184372154948UL) == 35184372154948UL) ||
        ((bace & 2199023329348UL) == 2199023329348UL) ||
        ((bace & 274877981188UL) == 274877981188UL))
      l2_moves.push_back(make_move(20, 2));
    if (((bace & 72057594574798848UL) == 72057594574798848UL))
      l2_moves.push_back(make_move(20, 29));

    // check for L1 king moves (non-capturing)
    if (((bace & 65536UL) == 65536UL))
      l1_moves.push_back(make_move(20, 16));
    if (((bace & 73728UL) == 73728UL))
      l1_moves.push_back(make_move(20, 13));
    if (((bace & 74240UL) == 74240UL))
      l1_moves.push_back(make_move(20, 9));
    if (((bace & 74304UL) == 74304UL))
      l1_moves.push_back(make_move(20, 6));
    if (((bace & 74308UL) == 74308UL))
      l1_moves.push_back(make_move(20, 2));
    if (((bace & 16777216UL) == 16777216UL))
      l1_moves.push_back(make_move(20, 24));
    if (((bace & 553648128UL) == 553648128UL))
      l1_moves.push_back(make_move(20, 29));
  }

  // ---- end of loc 20

  // ---------- loc == 21 ----------
  if (GET_64(top, 21)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 562949953437696UL) == 562949953437696UL))
      l2_moves.push_back(make_move(21, 14));
    if (((bace & 281474976714752UL) == 281474976714752UL))
      l2_moves.push_back(make_move(21, 12));
    if (((bace & 72057594306363392UL) == 72057594306363392UL))
      l2_moves.push_back(make_move(21, 28));
    if (((bace & 144115189149597696UL) == 144115189149597696UL))
      l2_moves.push_back(make_move(21, 30));

    // check for L1 man moves (non-capturing)
    if (((bace & 16777216UL) == 16777216UL))
      l1_moves.push_back(make_move(21, 24));
    if (((bace & 33554432UL) == 33554432UL))
      l1_moves.push_back(make_move(21, 25));
  } else if (GET_64(top, 53)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 1688849868668928UL) == 1688849868668928UL) ||
        ((bace & 1688850002886656UL) == 1688850002886656UL) ||
        ((bace & 36591747106881536UL) == 36591747106881536UL) ||
        ((bace & 567347999948928UL) == 567347999948928UL) ||
        ((bace & 567347999948936UL) == 567347999948936UL) ||
        ((bace & 563499709252616UL) == 563499709252616UL) ||
        ((bace & 565148976693280UL) == 565148976693280UL) ||
        ((bace & 565148976693281UL) == 565148976693281UL) ||
        ((bace & 563087392391681UL) == 563087392391681UL))
      l3_moves.push_back(make_move(21, 14));
    if (((bace & 703687442318336UL) == 703687442318336UL) ||
        ((bace & 563499709252616UL) == 563499709252616UL) ||
        ((bace & 563224831345666UL) == 563224831345666UL) ||
        ((bace & 211106233189376UL) == 211106233189376UL) ||
        ((bace & 70918500123656UL) == 70918500123656UL) ||
        ((bace & 70643622216706UL) == 70643622216706UL))
      l3_moves.push_back(make_move(21, 10));
    if (((bace & 282574488342560UL) == 282574488342560UL) ||
        ((bace & 282574488342562UL) == 282574488342562UL) ||
        ((bace & 281612415668482UL) == 281612415668482UL))
      l3_moves.push_back(make_move(21, 12));
    if (((bace & 432345565309698048UL) == 432345565309698048UL) ||
        ((bace & 432345565310222336UL) == 432345565310222336UL) ||
        ((bace & 180143986236194816UL) == 180143986236194816UL))
      l3_moves.push_back(make_move(21, 30));

    // check for L2 king moves (single captures)
    if (((bace & 562949953437696UL) == 562949953437696UL))
      l2_moves.push_back(make_move(21, 14));
    if (((bace & 562949953438720UL) == 562949953438720UL) ||
        ((bace & 70368744309760UL) == 70368744309760UL))
      l2_moves.push_back(make_move(21, 10));
    if (((bace & 562949953438848UL) == 562949953438848UL) ||
        ((bace & 70368744309888UL) == 70368744309888UL) ||
        ((bace & 4398046658688UL) == 4398046658688UL))
      l2_moves.push_back(make_move(21, 7));
    if (((bace & 562949953438856UL) == 562949953438856UL) ||
        ((bace & 70368744309896UL) == 70368744309896UL) ||
        ((bace & 4398046658696UL) == 4398046658696UL) ||
        ((bace & 549755962376UL) == 549755962376UL))
      l2_moves.push_back(make_move(21, 3));
    if (((bace & 281474976714752UL) == 281474976714752UL))
      l2_moves.push_back(make_move(21, 12));
    if (((bace & 72057594306363392UL) == 72057594306363392UL))
      l2_moves.push_back(make_move(21, 28));
    if (((bace & 144115189149597696UL) == 144115189149597696UL))
      l2_moves.push_back(make_move(21, 30));

    // check for L1 king moves (non-capturing)
    if (((bace & 131072UL) == 131072UL))
      l1_moves.push_back(make_move(21, 17));
    if (((bace & 147456UL) == 147456UL))
      l1_moves.push_back(make_move(21, 14));
    if (((bace & 148480UL) == 148480UL))
      l1_moves.push_back(make_move(21, 10));
    if (((bace & 148608UL) == 148608UL))
      l1_moves.push_back(make_move(21, 7));
    if (((bace & 148616UL) == 148616UL))
      l1_moves.push_back(make_move(21, 3));
    if (((bace & 65536UL) == 65536UL))
      l1_moves.push_back(make_move(21, 16));
    if (((bace & 69632UL) == 69632UL))
      l1_moves.push_back(make_move(21, 12));
    if (((bace & 16777216UL) == 16777216UL))
      l1_moves.push_back(make_move(21, 24));
    if (((bace & 285212672UL) == 285212672UL))
      l1_moves.push_back(make_move(21, 28));
    if (((bace & 33554432UL) == 33554432UL))
      l1_moves.push_back(make_move(21, 25));
    if (((bace & 1107296256UL) == 1107296256UL))
      l1_moves.push_back(make_move(21, 30));
  }

  // ---- end of loc 21

  // ---------- loc == 22 ----------
  if (GET_64(top, 22)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 1125899906875392UL) == 1125899906875392UL))
      l2_moves.push_back(make_move(22, 15));
    if (((bace & 562949953429504UL) == 562949953429504UL))
      l2_moves.push_back(make_move(22, 13));
    if (((bace & 144115188612726784UL) == 144115188612726784UL))
      l2_moves.push_back(make_move(22, 29));
    if (((bace & 288230378299195392UL) == 288230378299195392UL))
      l2_moves.push_back(make_move(22, 31));

    // check for L1 man moves (non-capturing)
    if (((bace & 33554432UL) == 33554432UL))
      l1_moves.push_back(make_move(22, 25));
    if (((bace & 67108864UL) == 67108864UL))
      l1_moves.push_back(make_move(22, 26));
  } else if (GET_64(top, 54)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 1130297953386560UL) == 1130297953386560UL) ||
        ((bace & 1130297953386562UL) == 1130297953386562UL) ||
        ((bace & 1126174784783362UL) == 1126174784783362UL))
      l3_moves.push_back(make_move(22, 15));
    if (((bace & 1126449662691332UL) == 1126449662691332UL) ||
        ((bace & 141287244433412UL) == 141287244433412UL))
      l3_moves.push_back(make_move(22, 11));
    if (((bace & 565148976685120UL) == 565148976685120UL) ||
        ((bace & 565148976685124UL) == 565148976685124UL) ||
        ((bace & 563224831336964UL) == 563224831336964UL) ||
        ((bace & 564049465057296UL) == 564049465057296UL) ||
        ((bace & 844424931188736UL) == 844424931188736UL))
      l3_moves.push_back(make_move(22, 13));
    if (((bace & 563087392383234UL) == 563087392383234UL) ||
        ((bace & 35321811173634UL) == 35321811173634UL))
      l3_moves.push_back(make_move(22, 8));
    if (((bace & 216172782651703296UL) == 216172782651703296UL))
      l3_moves.push_back(make_move(22, 29));

    // check for L2 king moves (single captures)
    if (((bace & 1125899906875392UL) == 1125899906875392UL))
      l2_moves.push_back(make_move(22, 15));
    if (((bace & 1125899906877440UL) == 1125899906877440UL) ||
        ((bace & 140737488619520UL) == 140737488619520UL))
      l2_moves.push_back(make_move(22, 11));
    if (((bace & 562949953429504UL) == 562949953429504UL))
      l2_moves.push_back(make_move(22, 13));
    if (((bace & 562949953429760UL) == 562949953429760UL) ||
        ((bace & 35184372220160UL) == 35184372220160UL))
      l2_moves.push_back(make_move(22, 8));
    if (((bace & 562949953429776UL) == 562949953429776UL) ||
        ((bace & 35184372220176UL) == 35184372220176UL) ||
        ((bace & 1099511767056UL) == 1099511767056UL))
      l2_moves.push_back(make_move(22, 4));
    if (((bace & 144115188612726784UL) == 144115188612726784UL))
      l2_moves.push_back(make_move(22, 29));
    if (((bace & 288230378299195392UL) == 288230378299195392UL))
      l2_moves.push_back(make_move(22, 31));

    // check for L1 king moves (non-capturing)
    if (((bace & 262144UL) == 262144UL))
      l1_moves.push_back(make_move(22, 18));
    if (((bace & 294912UL) == 294912UL))
      l1_moves.push_back(make_move(22, 15));
    if (((bace & 296960UL) == 296960UL))
      l1_moves.push_back(make_move(22, 11));
    if (((bace & 131072UL) == 131072UL))
      l1_moves.push_back(make_move(22, 17));
    if (((bace & 139264UL) == 139264UL))
      l1_moves.push_back(make_move(22, 13));
    if (((bace & 139520UL) == 139520UL))
      l1_moves.push_back(make_move(22, 8));
    if (((bace & 139536UL) == 139536UL))
      l1_moves.push_back(make_move(22, 4));
    if (((bace & 33554432UL) == 33554432UL))
      l1_moves.push_back(make_move(22, 25));
    if (((bace & 570425344UL) == 570425344UL))
      l1_moves.push_back(make_move(22, 29));
    if (((bace & 67108864UL) == 67108864UL))
      l1_moves.push_back(make_move(22, 26));
    if (((bace & 2214592512UL) == 2214592512UL))
      l1_moves.push_back(make_move(22, 31));
  }

  // ---- end of loc 22

  // ---------- loc == 23 ----------
  if (GET_64(top, 23)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 1125899906859008UL) == 1125899906859008UL))
      l2_moves.push_back(make_move(23, 14));
    if (((bace & 288230377225453568UL) == 288230377225453568UL))
      l2_moves.push_back(make_move(23, 30));

    // check for L1 man moves (non-capturing)
    if (((bace & 67108864UL) == 67108864UL))
      l1_moves.push_back(make_move(23, 26));
    if (((bace & 134217728UL) == 134217728UL))
      l1_moves.push_back(make_move(23, 27));
  } else if (GET_64(top, 55)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 1130297953370240UL) == 1130297953370240UL) ||
        ((bace & 1130297953370248UL) == 1130297953370248UL) ||
        ((bace & 1126449662673928UL) == 1126449662673928UL) ||
        ((bace & 1128098930114592UL) == 1128098930114592UL) ||
        ((bace & 1128098930114593UL) == 1128098930114593UL) ||
        ((bace & 1126037345812993UL) == 1126037345812993UL) ||
        ((bace & 1688849862377472UL) == 1688849862377472UL) ||
        ((bace & 1688849879154688UL) == 1688849879154688UL) ||
        ((bace & 1688850147590144UL) == 1688850147590144UL) ||
        ((bace & 10133099178508288UL) == 10133099178508288UL) ||
        ((bace & 10133099446943744UL) == 10133099446943744UL) ||
        ((bace & 73183494215450624UL) == 73183494215450624UL))
      l3_moves.push_back(make_move(23, 14));
    if (((bace & 1126174784766468UL) == 1126174784766468UL) ||
        ((bace & 1126037345812993UL) == 1126037345812993UL) ||
        ((bace & 1161084279013888UL) == 1161084279013888UL) ||
        ((bace & 1161084280062464UL) == 1161084280062464UL) ||
        ((bace & 1407374884626944UL) == 1407374884626944UL) ||
        ((bace & 70643622347268UL) == 70643622347268UL) ||
        ((bace & 70506183393793UL) == 70506183393793UL) ||
        ((bace & 105553116594688UL) == 105553116594688UL) ||
        ((bace & 105553117643264UL) == 105553117643264UL) ||
        ((bace & 351843722207744UL) == 351843722207744UL))
      l3_moves.push_back(make_move(23, 9));
    if (((bace & 1126999418491424UL) == 1126999418491424UL) ||
        ((bace & 71468256072224UL) == 71468256072224UL) ||
        ((bace & 3298535165984UL) == 3298535165984UL))
      l3_moves.push_back(make_move(23, 5));
    if (((bace & 432345565303406592UL) == 432345565303406592UL) ||
        ((bace & 432345565303472128UL) == 432345565303472128UL) ||
        ((bace & 432345565303476224UL) == 432345565303476224UL) ||
        ((bace & 297237576513814528UL) == 297237576513814528UL) ||
        ((bace & 297237576513818624UL) == 297237576513818624UL) ||
        ((bace & 288511852237819904UL) == 288511852237819904UL))
      l3_moves.push_back(make_move(23, 30));

    // check for L2 king moves (single captures)
    if (((bace & 1125899906859008UL) == 1125899906859008UL))
      l2_moves.push_back(make_move(23, 14));
    if (((bace & 1125899906859520UL) == 1125899906859520UL) ||
        ((bace & 70368744440320UL) == 70368744440320UL))
      l2_moves.push_back(make_move(23, 9));
    if (((bace & 1125899906859552UL) == 1125899906859552UL) ||
        ((bace & 70368744440352UL) == 70368744440352UL) ||
        ((bace & 2199023534112UL) == 2199023534112UL))
      l2_moves.push_back(make_move(23, 5));
    if (((bace & 1125899906859553UL) == 1125899906859553UL) ||
        ((bace & 70368744440353UL) == 70368744440353UL) ||
        ((bace & 2199023534113UL) == 2199023534113UL) ||
        ((bace & 137439232513UL) == 137439232513UL))
      l2_moves.push_back(make_move(23, 0));
    if (((bace & 288230377225453568UL) == 288230377225453568UL))
      l2_moves.push_back(make_move(23, 30));

    // check for L1 king moves (non-capturing)
    if (((bace & 524288UL) == 524288UL))
      l1_moves.push_back(make_move(23, 19));
    if (((bace & 262144UL) == 262144UL))
      l1_moves.push_back(make_move(23, 18));
    if (((bace & 278528UL) == 278528UL))
      l1_moves.push_back(make_move(23, 14));
    if (((bace & 279040UL) == 279040UL))
      l1_moves.push_back(make_move(23, 9));
    if (((bace & 279072UL) == 279072UL))
      l1_moves.push_back(make_move(23, 5));
    if (((bace & 279073UL) == 279073UL))
      l1_moves.push_back(make_move(23, 0));
    if (((bace & 67108864UL) == 67108864UL))
      l1_moves.push_back(make_move(23, 26));
    if (((bace & 1140850688UL) == 1140850688UL))
      l1_moves.push_back(make_move(23, 30));
    if (((bace & 134217728UL) == 134217728UL))
      l1_moves.push_back(make_move(23, 27));
  }

  // ---- end of loc 23

  // ---------- loc == 24 ----------
  if (GET_64(top, 24)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 9007199254872064UL) == 9007199254872064UL))
      l2_moves.push_back(make_move(24, 17));

    // check for L1 man moves (non-capturing)
    if (((bace & 268435456UL) == 268435456UL))
      l1_moves.push_back(make_move(24, 28));
    if (((bace & 536870912UL) == 536870912UL))
      l1_moves.push_back(make_move(24, 29));
  } else if (GET_64(top, 56)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 27021597831462912UL) == 27021597831462912UL) ||
        ((bace & 27021599978946560UL) == 27021599978946560UL) ||
        ((bace & 297237577558261760UL) == 297237577558261760UL) ||
        ((bace & 9077567999050752UL) == 9077567999050752UL) ||
        ((bace & 9077567999050880UL) == 9077567999050880UL) ||
        ((bace & 9077567999050888UL) == 9077567999050888UL) ||
        ((bace & 9011597301399680UL) == 9011597301399680UL) ||
        ((bace & 9011597301399688UL) == 9011597301399688UL) ||
        ((bace & 9007749010703368UL) == 9007749010703368UL) ||
        ((bace & 9042383626961152UL) == 9042383626961152UL) ||
        ((bace & 9042383626961168UL) == 9042383626961168UL) ||
        ((bace & 9008298766508048UL) == 9008298766508048UL))
      l3_moves.push_back(make_move(24, 17));
    if (((bace & 10133099170119680UL) == 10133099170119680UL) ||
        ((bace & 10133099304337408UL) == 10133099304337408UL) ||
        ((bace & 45035996408332288UL) == 45035996408332288UL) ||
        ((bace & 9011597301399680UL) == 9011597301399680UL) ||
        ((bace & 9011597301399688UL) == 9011597301399688UL) ||
        ((bace & 9007749010703368UL) == 9007749010703368UL) ||
        ((bace & 9009398278144032UL) == 9009398278144032UL) ||
        ((bace & 9009398278144033UL) == 9009398278144033UL) ||
        ((bace & 9007336693842433UL) == 9007336693842433UL) ||
        ((bace & 1688849870766080UL) == 1688849870766080UL) ||
        ((bace & 1688850004983808UL) == 1688850004983808UL) ||
        ((bace & 36591747108978688UL) == 36591747108978688UL) ||
        ((bace & 567348002046080UL) == 567348002046080UL) ||
        ((bace & 567348002046088UL) == 567348002046088UL) ||
        ((bace & 563499711349768UL) == 563499711349768UL) ||
        ((bace & 565148978790432UL) == 565148978790432UL) ||
        ((bace & 565148978790433UL) == 565148978790433UL) ||
        ((bace & 563087394488833UL) == 563087394488833UL))
      l3_moves.push_back(make_move(24, 14));
    if (((bace & 9147936743769088UL) == 9147936743769088UL) ||
        ((bace & 9007749010703368UL) == 9007749010703368UL) ||
        ((bace & 9007474132796418UL) == 9007474132796418UL) ||
        ((bace & 703687444415488UL) == 703687444415488UL) ||
        ((bace & 563499711349768UL) == 563499711349768UL) ||
        ((bace & 563224833442818UL) == 563224833442818UL) ||
        ((bace & 211106235286528UL) == 211106235286528UL) ||
        ((bace & 70918502220808UL) == 70918502220808UL) ||
        ((bace & 70643624313858UL) == 70643624313858UL))
      l3_moves.push_back(make_move(24, 10));

    // check for L2 king moves (single captures)
    if (((bace & 9007199254872064UL) == 9007199254872064UL))
      l2_moves.push_back(make_move(24, 17));
    if (((bace & 9007199254888448UL) == 9007199254888448UL) ||
        ((bace & 562949955534848UL) == 562949955534848UL))
      l2_moves.push_back(make_move(24, 14));
    if (((bace & 9007199254889472UL) == 9007199254889472UL) ||
        ((bace & 562949955535872UL) == 562949955535872UL) ||
        ((bace & 70368746406912UL) == 70368746406912UL))
      l2_moves.push_back(make_move(24, 10));
    if (((bace & 9007199254889600UL) == 9007199254889600UL) ||
        ((bace & 562949955536000UL) == 562949955536000UL) ||
        ((bace & 70368746407040UL) == 70368746407040UL) ||
        ((bace & 4398048755840UL) == 4398048755840UL))
      l2_moves.push_back(make_move(24, 7));
    if (((bace & 9007199254889608UL) == 9007199254889608UL) ||
        ((bace & 562949955536008UL) == 562949955536008UL) ||
        ((bace & 70368746407048UL) == 70368746407048UL) ||
        ((bace & 4398048755848UL) == 4398048755848UL) ||
        ((bace & 549758059528UL) == 549758059528UL))
      l2_moves.push_back(make_move(24, 3));

    // check for L1 king moves (non-capturing)
    if (((bace & 2097152UL) == 2097152UL))
      l1_moves.push_back(make_move(24, 21));
    if (((bace & 2228224UL) == 2228224UL))
      l1_moves.push_back(make_move(24, 17));
    if (((bace & 2244608UL) == 2244608UL))
      l1_moves.push_back(make_move(24, 14));
    if (((bace & 2245632UL) == 2245632UL))
      l1_moves.push_back(make_move(24, 10));
    if (((bace & 2245760UL) == 2245760UL))
      l1_moves.push_back(make_move(24, 7));
    if (((bace & 2245768UL) == 2245768UL))
      l1_moves.push_back(make_move(24, 3));
    if (((bace & 1048576UL) == 1048576UL))
      l1_moves.push_back(make_move(24, 20));
    if (((bace & 268435456UL) == 268435456UL))
      l1_moves.push_back(make_move(24, 28));
    if (((bace & 536870912UL) == 536870912UL))
      l1_moves.push_back(make_move(24, 29));
  }

  // ---- end of loc 24

  // ---------- loc == 25 ----------
  if (GET_64(top, 25)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 18014398509744128UL) == 18014398509744128UL))
      l2_moves.push_back(make_move(25, 18));
    if (((bace & 9007199254806528UL) == 9007199254806528UL))
      l2_moves.push_back(make_move(25, 16));

    // check for L1 man moves (non-capturing)
    if (((bace & 536870912UL) == 536870912UL))
      l1_moves.push_back(make_move(25, 29));
    if (((bace & 1073741824UL) == 1073741824UL))
      l1_moves.push_back(make_move(25, 30));
  } else if (GET_64(top, 57)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 54043195662925824UL) == 54043195662925824UL) ||
        ((bace & 18155135998101504UL) == 18155135998101504UL) ||
        ((bace & 18084767253922304UL) == 18084767253922304UL) ||
        ((bace & 18084767253922336UL) == 18084767253922336UL) ||
        ((bace & 18084767253922337UL) == 18084767253922337UL) ||
        ((bace & 18016597533016096UL) == 18016597533016096UL) ||
        ((bace & 18016597533016097UL) == 18016597533016097UL) ||
        ((bace & 18014535948714497UL) == 18014535948714497UL))
      l3_moves.push_back(make_move(25, 18));
    if (((bace & 18018796556288064UL) == 18018796556288064UL) ||
        ((bace & 18018796556288066UL) == 18018796556288066UL) ||
        ((bace & 18014673387684866UL) == 18014673387684866UL) ||
        ((bace & 1130297957580864UL) == 1130297957580864UL) ||
        ((bace & 1130297957580866UL) == 1130297957580866UL) ||
        ((bace & 1126174788977666UL) == 1126174788977666UL))
      l3_moves.push_back(make_move(25, 15));
    if (((bace & 18014948265592836UL) == 18014948265592836UL) ||
        ((bace & 1126449666885636UL) == 1126449666885636UL) ||
        ((bace & 141287248627716UL) == 141287248627716UL))
      l3_moves.push_back(make_move(25, 11));
    if (((bace & 9042383626895872UL) == 9042383626895872UL) ||
        ((bace & 9042383626895936UL) == 9042383626895936UL) ||
        ((bace & 9042383626895940UL) == 9042383626895940UL) ||
        ((bace & 9009398278070336UL) == 9009398278070336UL) ||
        ((bace & 9009398278070340UL) == 9009398278070340UL) ||
        ((bace & 9007474132722180UL) == 9007474132722180UL))
      l3_moves.push_back(make_move(25, 16));
    if (((bace & 9008298766438432UL) == 9008298766438432UL) ||
        ((bace & 9008298766438434UL) == 9008298766438434UL) ||
        ((bace & 9007336693764354UL) == 9007336693764354UL) ||
        ((bace & 282574490439712UL) == 282574490439712UL) ||
        ((bace & 282574490439714UL) == 282574490439714UL) ||
        ((bace & 281612417765634UL) == 281612417765634UL))
      l3_moves.push_back(make_move(25, 12));

    // check for L2 king moves (single captures)
    if (((bace & 18014398509744128UL) == 18014398509744128UL))
      l2_moves.push_back(make_move(25, 18));
    if (((bace & 18014398509776896UL) == 18014398509776896UL) ||
        ((bace & 1125899911069696UL) == 1125899911069696UL))
      l2_moves.push_back(make_move(25, 15));
    if (((bace & 18014398509778944UL) == 18014398509778944UL) ||
        ((bace & 1125899911071744UL) == 1125899911071744UL) ||
        ((bace & 140737492813824UL) == 140737492813824UL))
      l2_moves.push_back(make_move(25, 11));
    if (((bace & 9007199254806528UL) == 9007199254806528UL))
      l2_moves.push_back(make_move(25, 16));
    if (((bace & 9007199254810624UL) == 9007199254810624UL) ||
        ((bace & 281474978811904UL) == 281474978811904UL))
      l2_moves.push_back(make_move(25, 12));

    // check for L1 king moves (non-capturing)
    if (((bace & 4194304UL) == 4194304UL))
      l1_moves.push_back(make_move(25, 22));
    if (((bace & 4456448UL) == 4456448UL))
      l1_moves.push_back(make_move(25, 18));
    if (((bace & 4489216UL) == 4489216UL))
      l1_moves.push_back(make_move(25, 15));
    if (((bace & 4491264UL) == 4491264UL))
      l1_moves.push_back(make_move(25, 11));
    if (((bace & 2097152UL) == 2097152UL))
      l1_moves.push_back(make_move(25, 21));
    if (((bace & 2162688UL) == 2162688UL))
      l1_moves.push_back(make_move(25, 16));
    if (((bace & 2166784UL) == 2166784UL))
      l1_moves.push_back(make_move(25, 12));
    if (((bace & 536870912UL) == 536870912UL))
      l1_moves.push_back(make_move(25, 29));
    if (((bace & 1073741824UL) == 1073741824UL))
      l1_moves.push_back(make_move(25, 30));
  }

  // ---- end of loc 25

  // ---------- loc == 26 ----------
  if (GET_64(top, 26)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 36028797019488256UL) == 36028797019488256UL))
      l2_moves.push_back(make_move(26, 19));
    if (((bace & 18014398509613056UL) == 18014398509613056UL))
      l2_moves.push_back(make_move(26, 17));

    // check for L1 man moves (non-capturing)
    if (((bace & 1073741824UL) == 1073741824UL))
      l1_moves.push_back(make_move(26, 30));
    if (((bace & 2147483648UL) == 2147483648UL))
      l1_moves.push_back(make_move(26, 31));
  } else if (GET_64(top, 58)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 36169534507844608UL) == 36169534507844608UL) ||
        ((bace & 36169534507844672UL) == 36169534507844672UL) ||
        ((bace & 36169534507844674UL) == 36169534507844674UL) ||
        ((bace & 36033195066032192UL) == 36033195066032192UL) ||
        ((bace & 36033195066032194UL) == 36033195066032194UL) ||
        ((bace & 36029071897428994UL) == 36029071897428994UL))
      l3_moves.push_back(make_move(26, 19));
    if (((bace & 18084767253791744UL) == 18084767253791744UL) ||
        ((bace & 18084767253791872UL) == 18084767253791872UL) ||
        ((bace & 18084767253791880UL) == 18084767253791880UL) ||
        ((bace & 18018796556140672UL) == 18018796556140672UL) ||
        ((bace & 18018796556140680UL) == 18018796556140680UL) ||
        ((bace & 18014948265444360UL) == 18014948265444360UL) ||
        ((bace & 18049582881702144UL) == 18049582881702144UL) ||
        ((bace & 18049582881702160UL) == 18049582881702160UL) ||
        ((bace & 18015498021249040UL) == 18015498021249040UL) ||
        ((bace & 27021597781131264UL) == 27021597781131264UL) ||
        ((bace & 27021598049566720UL) == 27021598049566720UL) ||
        ((bace & 90071992818073600UL) == 90071992818073600UL))
      l3_moves.push_back(make_move(26, 17));
    if (((bace & 18016597532876864UL) == 18016597532876864UL) ||
        ((bace & 18016597532876868UL) == 18016597532876868UL) ||
        ((bace & 18014673387528708UL) == 18014673387528708UL) ||
        ((bace & 18015498021249040UL) == 18015498021249040UL) ||
        ((bace & 18295873487380480UL) == 18295873487380480UL) ||
        ((bace & 565148980879424UL) == 565148980879424UL) ||
        ((bace & 565148980879428UL) == 565148980879428UL) ||
        ((bace & 563224835531268UL) == 563224835531268UL) ||
        ((bace & 564049469251600UL) == 564049469251600UL) ||
        ((bace & 844424935383040UL) == 844424935383040UL))
      l3_moves.push_back(make_move(26, 13));
    if (((bace & 18014535948574978UL) == 18014535948574978UL) ||
        ((bace & 563087396577538UL) == 563087396577538UL) ||
        ((bace & 35321815367938UL) == 35321815367938UL))
      l3_moves.push_back(make_move(26, 8));

    // check for L2 king moves (single captures)
    if (((bace & 36028797019488256UL) == 36028797019488256UL))
      l2_moves.push_back(make_move(26, 19));
    if (((bace & 18014398509613056UL) == 18014398509613056UL))
      l2_moves.push_back(make_move(26, 17));
    if (((bace & 18014398509621248UL) == 18014398509621248UL) ||
        ((bace & 562949957623808UL) == 562949957623808UL))
      l2_moves.push_back(make_move(26, 13));
    if (((bace & 18014398509621504UL) == 18014398509621504UL) ||
        ((bace & 562949957624064UL) == 562949957624064UL) ||
        ((bace & 35184376414464UL) == 35184376414464UL))
      l2_moves.push_back(make_move(26, 8));
    if (((bace & 18014398509621520UL) == 18014398509621520UL) ||
        ((bace & 562949957624080UL) == 562949957624080UL) ||
        ((bace & 35184376414480UL) == 35184376414480UL) ||
        ((bace & 1099515961360UL) == 1099515961360UL))
      l2_moves.push_back(make_move(26, 4));

    // check for L1 king moves (non-capturing)
    if (((bace & 8388608UL) == 8388608UL))
      l1_moves.push_back(make_move(26, 23));
    if (((bace & 8912896UL) == 8912896UL))
      l1_moves.push_back(make_move(26, 19));
    if (((bace & 4194304UL) == 4194304UL))
      l1_moves.push_back(make_move(26, 22));
    if (((bace & 4325376UL) == 4325376UL))
      l1_moves.push_back(make_move(26, 17));
    if (((bace & 4333568UL) == 4333568UL))
      l1_moves.push_back(make_move(26, 13));
    if (((bace & 4333824UL) == 4333824UL))
      l1_moves.push_back(make_move(26, 8));
    if (((bace & 4333840UL) == 4333840UL))
      l1_moves.push_back(make_move(26, 4));
    if (((bace & 1073741824UL) == 1073741824UL))
      l1_moves.push_back(make_move(26, 30));
    if (((bace & 2147483648UL) == 2147483648UL))
      l1_moves.push_back(make_move(26, 31));
  }

  // ---- end of loc 26

  // ---------- loc == 27 ----------
  if (GET_64(top, 27)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 36028797019226112UL) == 36028797019226112UL))
      l2_moves.push_back(make_move(27, 18));

    // check for L1 man moves (non-capturing)
    if (((bace & 2147483648UL) == 2147483648UL))
      l1_moves.push_back(make_move(27, 31));
  } else if (GET_64(top, 59)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 36169534507583488UL) == 36169534507583488UL) ||
        ((bace & 36099165763404288UL) == 36099165763404288UL) ||
        ((bace & 36099165763404320UL) == 36099165763404320UL) ||
        ((bace & 36099165763404321UL) == 36099165763404321UL) ||
        ((bace & 36030996042498080UL) == 36030996042498080UL) ||
        ((bace & 36030996042498081UL) == 36030996042498081UL) ||
        ((bace & 36028934458196481UL) == 36028934458196481UL) ||
        ((bace & 54043195562262528UL) == 54043195562262528UL) ||
        ((bace & 54043196099133440UL) == 54043196099133440UL) ||
        ((bace & 180143985636147200UL) == 180143985636147200UL))
      l3_moves.push_back(make_move(27, 18));
    if (((bace & 36033195065753728UL) == 36033195065753728UL) ||
        ((bace & 36033195065753736UL) == 36033195065753736UL) ||
        ((bace & 36029346775057416UL) == 36029346775057416UL) ||
        ((bace & 36030996042498080UL) == 36030996042498080UL) ||
        ((bace & 36030996042498081UL) == 36030996042498081UL) ||
        ((bace & 36028934458196481UL) == 36028934458196481UL) ||
        ((bace & 36591746974760960UL) == 36591746974760960UL) ||
        ((bace & 36591746991538176UL) == 36591746991538176UL) ||
        ((bace & 36591747259973632UL) == 36591747259973632UL) ||
        ((bace & 45035996290891776UL) == 45035996290891776UL) ||
        ((bace & 45035996559327232UL) == 45035996559327232UL) ||
        ((bace & 108086391327834112UL) == 108086391327834112UL) ||
        ((bace & 1130297961758848UL) == 1130297961758848UL) ||
        ((bace & 1130297961758856UL) == 1130297961758856UL) ||
        ((bace & 1126449671062536UL) == 1126449671062536UL) ||
        ((bace & 1128098938503200UL) == 1128098938503200UL) ||
        ((bace & 1128098938503201UL) == 1128098938503201UL) ||
        ((bace & 1126037354201601UL) == 1126037354201601UL) ||
        ((bace & 1688849870766080UL) == 1688849870766080UL) ||
        ((bace & 1688849887543296UL) == 1688849887543296UL) ||
        ((bace & 1688850155978752UL) == 1688850155978752UL) ||
        ((bace & 10133099186896896UL) == 10133099186896896UL) ||
        ((bace & 10133099455332352UL) == 10133099455332352UL) ||
        ((bace & 73183494223839232UL) == 73183494223839232UL))
      l3_moves.push_back(make_move(27, 14));
    if (((bace & 36029071897149956UL) == 36029071897149956UL) ||
        ((bace & 36028934458196481UL) == 36028934458196481UL) ||
        ((bace & 36063981391397376UL) == 36063981391397376UL) ||
        ((bace & 36063981392445952UL) == 36063981392445952UL) ||
        ((bace & 36310271997010432UL) == 36310271997010432UL) ||
        ((bace & 1126174793155076UL) == 1126174793155076UL) ||
        ((bace & 1126037354201601UL) == 1126037354201601UL) ||
        ((bace & 1161084287402496UL) == 1161084287402496UL) ||
        ((bace & 1161084288451072UL) == 1161084288451072UL) ||
        ((bace & 1407374893015552UL) == 1407374893015552UL) ||
        ((bace & 70643630735876UL) == 70643630735876UL) ||
        ((bace & 70506191782401UL) == 70506191782401UL) ||
        ((bace & 105553124983296UL) == 105553124983296UL) ||
        ((bace & 105553126031872UL) == 105553126031872UL) ||
        ((bace & 351843730596352UL) == 351843730596352UL))
      l3_moves.push_back(make_move(27, 9));
    if (((bace & 36029896530874912UL) == 36029896530874912UL) ||
        ((bace & 1126999426880032UL) == 1126999426880032UL) ||
        ((bace & 71468264460832UL) == 71468264460832UL) ||
        ((bace & 3298543554592UL) == 3298543554592UL))
      l3_moves.push_back(make_move(27, 5));

    // check for L2 king moves (single captures)
    if (((bace & 36028797019226112UL) == 36028797019226112UL))
      l2_moves.push_back(make_move(27, 18));
    if (((bace & 36028797019242496UL) == 36028797019242496UL) ||
        ((bace & 1125899915247616UL) == 1125899915247616UL))
      l2_moves.push_back(make_move(27, 14));
    if (((bace & 36028797019243008UL) == 36028797019243008UL) ||
        ((bace & 1125899915248128UL) == 1125899915248128UL) ||
        ((bace & 70368752828928UL) == 70368752828928UL))
      l2_moves.push_back(make_move(27, 9));
    if (((bace & 36028797019243040UL) == 36028797019243040UL) ||
        ((bace & 1125899915248160UL) == 1125899915248160UL) ||
        ((bace & 70368752828960UL) == 70368752828960UL) ||
        ((bace & 2199031922720UL) == 2199031922720UL))
      l2_moves.push_back(make_move(27, 5));
    if (((bace & 36028797019243041UL) == 36028797019243041UL) ||
        ((bace & 1125899915248161UL) == 1125899915248161UL) ||
        ((bace & 70368752828961UL) == 70368752828961UL) ||
        ((bace & 2199031922721UL) == 2199031922721UL) ||
        ((bace & 137447621121UL) == 137447621121UL))
      l2_moves.push_back(make_move(27, 0));

    // check for L1 king moves (non-capturing)
    if (((bace & 8388608UL) == 8388608UL))
      l1_moves.push_back(make_move(27, 23));
    if (((bace & 8650752UL) == 8650752UL))
      l1_moves.push_back(make_move(27, 18));
    if (((bace & 8667136UL) == 8667136UL))
      l1_moves.push_back(make_move(27, 14));
    if (((bace & 8667648UL) == 8667648UL))
      l1_moves.push_back(make_move(27, 9));
    if (((bace & 8667680UL) == 8667680UL))
      l1_moves.push_back(make_move(27, 5));
    if (((bace & 8667681UL) == 8667681UL))
      l1_moves.push_back(make_move(27, 0));
    if (((bace & 2147483648UL) == 2147483648UL))
      l1_moves.push_back(make_move(27, 31));
  }

  // ---- end of loc 27

  // ---------- loc == 28 ----------
  if (GET_64(top, 28)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 72057594040025088UL) == 72057594040025088UL))
      l2_moves.push_back(make_move(28, 21));

    // check for L1 man moves (non-capturing)

  } else if (GET_64(top, 60)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 216172783189622784UL) == 216172783189622784UL) ||
        ((bace & 72620543993462784UL) == 72620543993462784UL) ||
        ((bace & 72620543993463808UL) == 72620543993463808UL) ||
        ((bace & 72620543993463936UL) == 72620543993463936UL) ||
        ((bace & 72620543993463944UL) == 72620543993463944UL) ||
        ((bace & 72127962784334848UL) == 72127962784334848UL) ||
        ((bace & 72127962784334976UL) == 72127962784334976UL) ||
        ((bace & 72127962784334984UL) == 72127962784334984UL) ||
        ((bace & 72061992086683776UL) == 72061992086683776UL) ||
        ((bace & 72061992086683784UL) == 72061992086683784UL) ||
        ((bace & 72058143795987464UL) == 72058143795987464UL) ||
        ((bace & 72339069016739840UL) == 72339069016739840UL))
      l3_moves.push_back(make_move(28, 21));
    if (((bace & 90071992616747008UL) == 90071992616747008UL) ||
        ((bace & 90071994764230656UL) == 90071994764230656UL) ||
        ((bace & 360287972343545856UL) == 360287972343545856UL) ||
        ((bace & 72127962784334848UL) == 72127962784334848UL) ||
        ((bace & 72127962784334976UL) == 72127962784334976UL) ||
        ((bace & 72127962784334984UL) == 72127962784334984UL) ||
        ((bace & 72061992086683776UL) == 72061992086683776UL) ||
        ((bace & 72061992086683784UL) == 72061992086683784UL) ||
        ((bace & 72058143795987464UL) == 72058143795987464UL) ||
        ((bace & 72092778412245248UL) == 72092778412245248UL) ||
        ((bace & 72092778412245264UL) == 72092778412245264UL) ||
        ((bace & 72058693551792144UL) == 72058693551792144UL) ||
        ((bace & 27021597848240128UL) == 27021597848240128UL) ||
        ((bace & 27021599995723776UL) == 27021599995723776UL) ||
        ((bace & 297237577575038976UL) == 297237577575038976UL) ||
        ((bace & 9077568015827968UL) == 9077568015827968UL) ||
        ((bace & 9077568015828096UL) == 9077568015828096UL) ||
        ((bace & 9077568015828104UL) == 9077568015828104UL) ||
        ((bace & 9011597318176896UL) == 9011597318176896UL) ||
        ((bace & 9011597318176904UL) == 9011597318176904UL) ||
        ((bace & 9007749027480584UL) == 9007749027480584UL) ||
        ((bace & 9042383643738368UL) == 9042383643738368UL) ||
        ((bace & 9042383643738384UL) == 9042383643738384UL) ||
        ((bace & 9008298783285264UL) == 9008298783285264UL))
      l3_moves.push_back(make_move(28, 17));
    if (((bace & 73183493955403776UL) == 73183493955403776UL) ||
        ((bace & 73183494089621504UL) == 73183494089621504UL) ||
        ((bace & 108086391193616384UL) == 108086391193616384UL) ||
        ((bace & 72061992086683776UL) == 72061992086683776UL) ||
        ((bace & 72061992086683784UL) == 72061992086683784UL) ||
        ((bace & 72058143795987464UL) == 72058143795987464UL) ||
        ((bace & 72059793063428128UL) == 72059793063428128UL) ||
        ((bace & 72059793063428129UL) == 72059793063428129UL) ||
        ((bace & 72057731479126529UL) == 72057731479126529UL) ||
        ((bace & 10133099186896896UL) == 10133099186896896UL) ||
        ((bace & 10133099321114624UL) == 10133099321114624UL) ||
        ((bace & 45035996425109504UL) == 45035996425109504UL) ||
        ((bace & 9011597318176896UL) == 9011597318176896UL) ||
        ((bace & 9011597318176904UL) == 9011597318176904UL) ||
        ((bace & 9007749027480584UL) == 9007749027480584UL) ||
        ((bace & 9009398294921248UL) == 9009398294921248UL) ||
        ((bace & 9009398294921249UL) == 9009398294921249UL) ||
        ((bace & 9007336710619649UL) == 9007336710619649UL) ||
        ((bace & 1688849887543296UL) == 1688849887543296UL) ||
        ((bace & 1688850021761024UL) == 1688850021761024UL) ||
        ((bace & 36591747125755904UL) == 36591747125755904UL) ||
        ((bace & 567348018823296UL) == 567348018823296UL) ||
        ((bace & 567348018823304UL) == 567348018823304UL) ||
        ((bace & 563499728126984UL) == 563499728126984UL) ||
        ((bace & 565148995567648UL) == 565148995567648UL) ||
        ((bace & 565148995567649UL) == 565148995567649UL) ||
        ((bace & 563087411266049UL) == 563087411266049UL))
      l3_moves.push_back(make_move(28, 14));
    if (((bace & 72198331529053184UL) == 72198331529053184UL) ||
        ((bace & 72058143795987464UL) == 72058143795987464UL) ||
        ((bace & 72057868918080514UL) == 72057868918080514UL) ||
        ((bace & 9147936760546304UL) == 9147936760546304UL) ||
        ((bace & 9007749027480584UL) == 9007749027480584UL) ||
        ((bace & 9007474149573634UL) == 9007474149573634UL) ||
        ((bace & 703687461192704UL) == 703687461192704UL) ||
        ((bace & 563499728126984UL) == 563499728126984UL) ||
        ((bace & 563224850220034UL) == 563224850220034UL) ||
        ((bace & 211106252063744UL) == 211106252063744UL) ||
        ((bace & 70918518998024UL) == 70918518998024UL) ||
        ((bace & 70643641091074UL) == 70643641091074UL))
      l3_moves.push_back(make_move(28, 10));

    // check for L2 king moves (single captures)
    if (((bace & 72057594040025088UL) == 72057594040025088UL))
      l2_moves.push_back(make_move(28, 21));
    if (((bace & 72057594040156160UL) == 72057594040156160UL) ||
        ((bace & 9007199271649280UL) == 9007199271649280UL))
      l2_moves.push_back(make_move(28, 17));
    if (((bace & 72057594040172544UL) == 72057594040172544UL) ||
        ((bace & 9007199271665664UL) == 9007199271665664UL) ||
        ((bace & 562949972312064UL) == 562949972312064UL))
      l2_moves.push_back(make_move(28, 14));
    if (((bace & 72057594040173568UL) == 72057594040173568UL) ||
        ((bace & 9007199271666688UL) == 9007199271666688UL) ||
        ((bace & 562949972313088UL) == 562949972313088UL) ||
        ((bace & 70368763184128UL) == 70368763184128UL))
      l2_moves.push_back(make_move(28, 10));
    if (((bace & 72057594040173696UL) == 72057594040173696UL) ||
        ((bace & 9007199271666816UL) == 9007199271666816UL) ||
        ((bace & 562949972313216UL) == 562949972313216UL) ||
        ((bace & 70368763184256UL) == 70368763184256UL) ||
        ((bace & 4398065533056UL) == 4398065533056UL))
      l2_moves.push_back(make_move(28, 7));
    if (((bace & 72057594040173704UL) == 72057594040173704UL) ||
        ((bace & 9007199271666824UL) == 9007199271666824UL) ||
        ((bace & 562949972313224UL) == 562949972313224UL) ||
        ((bace & 70368763184264UL) == 70368763184264UL) ||
        ((bace & 4398065533064UL) == 4398065533064UL) ||
        ((bace & 549774836744UL) == 549774836744UL))
      l2_moves.push_back(make_move(28, 3));

    // check for L1 king moves (non-capturing)
    if (((bace & 16777216UL) == 16777216UL))
      l1_moves.push_back(make_move(28, 24));
    if (((bace & 18874368UL) == 18874368UL))
      l1_moves.push_back(make_move(28, 21));
    if (((bace & 19005440UL) == 19005440UL))
      l1_moves.push_back(make_move(28, 17));
    if (((bace & 19021824UL) == 19021824UL))
      l1_moves.push_back(make_move(28, 14));
    if (((bace & 19022848UL) == 19022848UL))
      l1_moves.push_back(make_move(28, 10));
    if (((bace & 19022976UL) == 19022976UL))
      l1_moves.push_back(make_move(28, 7));
    if (((bace & 19022984UL) == 19022984UL))
      l1_moves.push_back(make_move(28, 3));
  }

  // ---- end of loc 28

  // ---------- loc == 29 ----------
  if (GET_64(top, 29)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 144115188080050176UL) == 144115188080050176UL))
      l2_moves.push_back(make_move(29, 22));
    if (((bace & 72057594038976512UL) == 72057594038976512UL))
      l2_moves.push_back(make_move(29, 20));

    // check for L1 man moves (non-capturing)

  } else if (GET_64(top, 61)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 432345566379245568UL) == 432345566379245568UL) ||
        ((bace & 145241087986925568UL) == 145241087986925568UL) ||
        ((bace & 145241087986927616UL) == 145241087986927616UL) ||
        ((bace & 144255925568669696UL) == 144255925568669696UL) ||
        ((bace & 144678138033479680UL) == 144678138033479680UL) ||
        ((bace & 144678138033479936UL) == 144678138033479936UL) ||
        ((bace & 144678138033479952UL) == 144678138033479952UL) ||
        ((bace & 144150372452270336UL) == 144150372452270336UL) ||
        ((bace & 144150372452270352UL) == 144150372452270352UL) ||
        ((bace & 144116287591817232UL) == 144116287591817232UL))
      l3_moves.push_back(make_move(29, 22));
    if (((bace & 180143985233494016UL) == 180143985233494016UL) ||
        ((bace & 144255925568669696UL) == 144255925568669696UL) ||
        ((bace & 144185556824490496UL) == 144185556824490496UL) ||
        ((bace & 144185556824490528UL) == 144185556824490528UL) ||
        ((bace & 144185556824490529UL) == 144185556824490529UL) ||
        ((bace & 144117387103584288UL) == 144117387103584288UL) ||
        ((bace & 144117387103584289UL) == 144117387103584289UL) ||
        ((bace & 144115325519282689UL) == 144115325519282689UL) ||
        ((bace & 54043195696480256UL) == 54043195696480256UL) ||
        ((bace & 18155136031655936UL) == 18155136031655936UL) ||
        ((bace & 18084767287476736UL) == 18084767287476736UL) ||
        ((bace & 18084767287476768UL) == 18084767287476768UL) ||
        ((bace & 18084767287476769UL) == 18084767287476769UL) ||
        ((bace & 18016597566570528UL) == 18016597566570528UL) ||
        ((bace & 18016597566570529UL) == 18016597566570529UL) ||
        ((bace & 18014535982268929UL) == 18014535982268929UL))
      l3_moves.push_back(make_move(29, 18));
    if (((bace & 144119586126856256UL) == 144119586126856256UL) ||
        ((bace & 144119586126856258UL) == 144119586126856258UL) ||
        ((bace & 144115462958253058UL) == 144115462958253058UL) ||
        ((bace & 18018796589842496UL) == 18018796589842496UL) ||
        ((bace & 18018796589842498UL) == 18018796589842498UL) ||
        ((bace & 18014673421239298UL) == 18014673421239298UL) ||
        ((bace & 1130297991135296UL) == 1130297991135296UL) ||
        ((bace & 1130297991135298UL) == 1130297991135298UL) ||
        ((bace & 1126174822532098UL) == 1126174822532098UL))
      l3_moves.push_back(make_move(29, 15));
    if (((bace & 144115737836161028UL) == 144115737836161028UL) ||
        ((bace & 18014948299147268UL) == 18014948299147268UL) ||
        ((bace & 1126449700440068UL) == 1126449700440068UL) ||
        ((bace & 141287282182148UL) == 141287282182148UL))
      l3_moves.push_back(make_move(29, 11));
    if (((bace & 72339069015695360UL) == 72339069015695360UL) ||
        ((bace & 72339069015695872UL) == 72339069015695872UL) ||
        ((bace & 72339069015695936UL) == 72339069015695936UL) ||
        ((bace & 72339069015695940UL) == 72339069015695940UL) ||
        ((bace & 72092778411131392UL) == 72092778411131392UL) ||
        ((bace & 72092778411131456UL) == 72092778411131456UL) ||
        ((bace & 72092778411131460UL) == 72092778411131460UL) ||
        ((bace & 72059793062305856UL) == 72059793062305856UL) ||
        ((bace & 72059793062305860UL) == 72059793062305860UL) ||
        ((bace & 72057868916957700UL) == 72057868916957700UL))
      l3_moves.push_back(make_move(29, 20));

    // check for L2 king moves (single captures)
    if (((bace & 144115188080050176UL) == 144115188080050176UL))
      l2_moves.push_back(make_move(29, 22));
    if (((bace & 144115188080312320UL) == 144115188080312320UL) ||
        ((bace & 18014398543298560UL) == 18014398543298560UL))
      l2_moves.push_back(make_move(29, 18));
    if (((bace & 144115188080345088UL) == 144115188080345088UL) ||
        ((bace & 18014398543331328UL) == 18014398543331328UL) ||
        ((bace & 1125899944624128UL) == 1125899944624128UL))
      l2_moves.push_back(make_move(29, 15));
    if (((bace & 144115188080347136UL) == 144115188080347136UL) ||
        ((bace & 18014398543333376UL) == 18014398543333376UL) ||
        ((bace & 1125899944626176UL) == 1125899944626176UL) ||
        ((bace & 140737526368256UL) == 140737526368256UL))
      l2_moves.push_back(make_move(29, 11));
    if (((bace & 72057594038976512UL) == 72057594038976512UL))
      l2_moves.push_back(make_move(29, 20));

    // check for L1 king moves (non-capturing)
    if (((bace & 33554432UL) == 33554432UL))
      l1_moves.push_back(make_move(29, 25));
    if (((bace & 37748736UL) == 37748736UL))
      l1_moves.push_back(make_move(29, 22));
    if (((bace & 38010880UL) == 38010880UL))
      l1_moves.push_back(make_move(29, 18));
    if (((bace & 38043648UL) == 38043648UL))
      l1_moves.push_back(make_move(29, 15));
    if (((bace & 38045696UL) == 38045696UL))
      l1_moves.push_back(make_move(29, 11));
    if (((bace & 16777216UL) == 16777216UL))
      l1_moves.push_back(make_move(29, 24));
    if (((bace & 17825792UL) == 17825792UL))
      l1_moves.push_back(make_move(29, 20));
  }

  // ---- end of loc 29

  // ---------- loc == 30 ----------
  if (GET_64(top, 30)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 288230376160100352UL) == 288230376160100352UL))
      l2_moves.push_back(make_move(30, 23));
    if (((bace & 144115188077953024UL) == 144115188077953024UL))
      l2_moves.push_back(make_move(30, 21));

    // check for L1 man moves (non-capturing)

  } else if (GET_64(top, 62)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 289356276066959360UL) == 289356276066959360UL) ||
        ((bace & 289356276066959872UL) == 289356276066959872UL) ||
        ((bace & 289356276066959904UL) == 289356276066959904UL) ||
        ((bace & 289356276066959905UL) == 289356276066959905UL) ||
        ((bace & 288300744904540672UL) == 288300744904540672UL) ||
        ((bace & 288300744904540704UL) == 288300744904540704UL) ||
        ((bace & 288300744904540705UL) == 288300744904540705UL) ||
        ((bace & 288232575183634464UL) == 288232575183634464UL) ||
        ((bace & 288232575183634465UL) == 288232575183634465UL) ||
        ((bace & 288230513599332865UL) == 288230513599332865UL))
      l3_moves.push_back(make_move(30, 23));
    if (((bace & 288371113648980992UL) == 288371113648980992UL) ||
        ((bace & 288371113648981056UL) == 288371113648981056UL) ||
        ((bace & 288371113648981058UL) == 288371113648981058UL) ||
        ((bace & 288234774207168576UL) == 288234774207168576UL) ||
        ((bace & 288234774207168578UL) == 288234774207168578UL) ||
        ((bace & 288230651038565378UL) == 288230651038565378UL) ||
        ((bace & 36169534574953472UL) == 36169534574953472UL) ||
        ((bace & 36169534574953536UL) == 36169534574953536UL) ||
        ((bace & 36169534574953538UL) == 36169534574953538UL) ||
        ((bace & 36033195133141056UL) == 36033195133141056UL) ||
        ((bace & 36033195133141058UL) == 36033195133141058UL) ||
        ((bace & 36029071964537858UL) == 36029071964537858UL))
      l3_moves.push_back(make_move(30, 19));
    if (((bace & 144678138031390720UL) == 144678138031390720UL) ||
        ((bace & 144678138031391744UL) == 144678138031391744UL) ||
        ((bace & 144678138031391872UL) == 144678138031391872UL) ||
        ((bace & 144678138031391880UL) == 144678138031391880UL) ||
        ((bace & 144185556822262784UL) == 144185556822262784UL) ||
        ((bace & 144185556822262912UL) == 144185556822262912UL) ||
        ((bace & 144185556822262920UL) == 144185556822262920UL) ||
        ((bace & 144119586124611712UL) == 144119586124611712UL) ||
        ((bace & 144119586124611720UL) == 144119586124611720UL) ||
        ((bace & 144115737833915400UL) == 144115737833915400UL) ||
        ((bace & 144396663054667776UL) == 144396663054667776UL) ||
        ((bace & 216172782384316416UL) == 216172782384316416UL))
      l3_moves.push_back(make_move(30, 21));
    if (((bace & 144150372450107904UL) == 144150372450107904UL) ||
        ((bace & 144150372450107968UL) == 144150372450107968UL) ||
        ((bace & 144150372450107972UL) == 144150372450107972UL) ||
        ((bace & 144117387101282368UL) == 144117387101282368UL) ||
        ((bace & 144117387101282372UL) == 144117387101282372UL) ||
        ((bace & 144115462955934212UL) == 144115462955934212UL) ||
        ((bace & 9042383660450304UL) == 9042383660450304UL) ||
        ((bace & 9042383660450368UL) == 9042383660450368UL) ||
        ((bace & 9042383660450372UL) == 9042383660450372UL) ||
        ((bace & 9009398311624768UL) == 9009398311624768UL) ||
        ((bace & 9009398311624772UL) == 9009398311624772UL) ||
        ((bace & 9007474166276612UL) == 9007474166276612UL))
      l3_moves.push_back(make_move(30, 16));
    if (((bace & 144116287589650464UL) == 144116287589650464UL) ||
        ((bace & 144116287589650466UL) == 144116287589650466UL) ||
        ((bace & 144115325516976386UL) == 144115325516976386UL) ||
        ((bace & 9008298799992864UL) == 9008298799992864UL) ||
        ((bace & 9008298799992866UL) == 9008298799992866UL) ||
        ((bace & 9007336727318786UL) == 9007336727318786UL) ||
        ((bace & 282574523994144UL) == 282574523994144UL) ||
        ((bace & 282574523994146UL) == 282574523994146UL) ||
        ((bace & 281612451320066UL) == 281612451320066UL))
      l3_moves.push_back(make_move(30, 12));

    // check for L2 king moves (single captures)
    if (((bace & 288230376160100352UL) == 288230376160100352UL))
      l2_moves.push_back(make_move(30, 23));
    if (((bace & 288230376160624640UL) == 288230376160624640UL) ||
        ((bace & 36028797086597120UL) == 36028797086597120UL))
      l2_moves.push_back(make_move(30, 19));
    if (((bace & 144115188077953024UL) == 144115188077953024UL))
      l2_moves.push_back(make_move(30, 21));
    if (((bace & 144115188078018560UL) == 144115188078018560UL) ||
        ((bace & 9007199288360960UL) == 9007199288360960UL))
      l2_moves.push_back(make_move(30, 16));
    if (((bace & 144115188078022656UL) == 144115188078022656UL) ||
        ((bace & 9007199288365056UL) == 9007199288365056UL) ||
        ((bace & 281475012366336UL) == 281475012366336UL))
      l2_moves.push_back(make_move(30, 12));

    // check for L1 king moves (non-capturing)
    if (((bace & 67108864UL) == 67108864UL))
      l1_moves.push_back(make_move(30, 26));
    if (((bace & 75497472UL) == 75497472UL))
      l1_moves.push_back(make_move(30, 23));
    if (((bace & 76021760UL) == 76021760UL))
      l1_moves.push_back(make_move(30, 19));
    if (((bace & 33554432UL) == 33554432UL))
      l1_moves.push_back(make_move(30, 25));
    if (((bace & 35651584UL) == 35651584UL))
      l1_moves.push_back(make_move(30, 21));
    if (((bace & 35717120UL) == 35717120UL))
      l1_moves.push_back(make_move(30, 16));
    if (((bace & 35721216UL) == 35721216UL))
      l1_moves.push_back(make_move(30, 12));
  }

  // ---- end of loc 30

  // ---------- loc == 31 ----------
  if (GET_64(top, 31)) { // it's a man
    // check for L2 man moves (capturing)
    if (((bace & 288230376155906048UL) == 288230376155906048UL))
      l2_moves.push_back(make_move(31, 22));

    // check for L1 man moves (non-capturing)

  } else if (GET_64(top, 63)) { // it's a king
    // check for L3 king moves (multiple captures)
    if (((bace & 289356276062781440UL) == 289356276062781440UL) ||
        ((bace & 289356276062783488UL) == 289356276062783488UL) ||
        ((bace & 288371113644525568UL) == 288371113644525568UL) ||
        ((bace & 288793326109335552UL) == 288793326109335552UL) ||
        ((bace & 288793326109335808UL) == 288793326109335808UL) ||
        ((bace & 288793326109335824UL) == 288793326109335824UL) ||
        ((bace & 288265560528126208UL) == 288265560528126208UL) ||
        ((bace & 288265560528126224UL) == 288265560528126224UL) ||
        ((bace & 288231475667673104UL) == 288231475667673104UL) ||
        ((bace & 432345564768632832UL) == 432345564768632832UL))
      l3_moves.push_back(make_move(31, 22));
    if (((bace & 288300744900215808UL) == 288300744900215808UL) ||
        ((bace & 288300744900215936UL) == 288300744900215936UL) ||
        ((bace & 288300744900215944UL) == 288300744900215944UL) ||
        ((bace & 288234774202564736UL) == 288234774202564736UL) ||
        ((bace & 288234774202564744UL) == 288234774202564744UL) ||
        ((bace & 288230925911868424UL) == 288230925911868424UL) ||
        ((bace & 288265560528126208UL) == 288265560528126208UL) ||
        ((bace & 288265560528126224UL) == 288265560528126224UL) ||
        ((bace & 288231475667673104UL) == 288231475667673104UL) ||
        ((bace & 297237575427555328UL) == 297237575427555328UL) ||
        ((bace & 297237575695990784UL) == 297237575695990784UL) ||
        ((bace & 360287970464497664UL) == 360287970464497664UL) ||
        ((bace & 18084767320900608UL) == 18084767320900608UL) ||
        ((bace & 18084767320900736UL) == 18084767320900736UL) ||
        ((bace & 18084767320900744UL) == 18084767320900744UL) ||
        ((bace & 18018796623249536UL) == 18018796623249536UL) ||
        ((bace & 18018796623249544UL) == 18018796623249544UL) ||
        ((bace & 18014948332553224UL) == 18014948332553224UL) ||
        ((bace & 18049582948811008UL) == 18049582948811008UL) ||
        ((bace & 18049582948811024UL) == 18049582948811024UL) ||
        ((bace & 18015498088357904UL) == 18015498088357904UL) ||
        ((bace & 27021597848240128UL) == 27021597848240128UL) ||
        ((bace & 27021598116675584UL) == 27021598116675584UL) ||
        ((bace & 90071992885182464UL) == 90071992885182464UL))
      l3_moves.push_back(make_move(31, 17));
    if (((bace & 288232575179300928UL) == 288232575179300928UL) ||
        ((bace & 288232575179300932UL) == 288232575179300932UL) ||
        ((bace & 288230651033952772UL) == 288230651033952772UL) ||
        ((bace & 288231475667673104UL) == 288231475667673104UL) ||
        ((bace & 288511851133804544UL) == 288511851133804544UL) ||
        ((bace & 18016597599985728UL) == 18016597599985728UL) ||
        ((bace & 18016597599985732UL) == 18016597599985732UL) ||
        ((bace & 18014673454637572UL) == 18014673454637572UL) ||
        ((bace & 18015498088357904UL) == 18015498088357904UL) ||
        ((bace & 18295873554489344UL) == 18295873554489344UL) ||
        ((bace & 565149047988288UL) == 565149047988288UL) ||
        ((bace & 565149047988292UL) == 565149047988292UL) ||
        ((bace & 563224902640132UL) == 563224902640132UL) ||
        ((bace & 564049536360464UL) == 564049536360464UL) ||
        ((bace & 844425002491904UL) == 844425002491904UL))
      l3_moves.push_back(make_move(31, 13));
    if (((bace & 288230513594999042UL) == 288230513594999042UL) ||
        ((bace & 18014536015683842UL) == 18014536015683842UL) ||
        ((bace & 563087463686402UL) == 563087463686402UL) ||
        ((bace & 35321882476802UL) == 35321882476802UL))
      l3_moves.push_back(make_move(31, 8));

    // check for L2 king moves (single captures)
    if (((bace & 288230376155906048UL) == 288230376155906048UL))
      l2_moves.push_back(make_move(31, 22));
    if (((bace & 288230376156037120UL) == 288230376156037120UL) ||
        ((bace & 18014398576721920UL) == 18014398576721920UL))
      l2_moves.push_back(make_move(31, 17));
    if (((bace & 288230376156045312UL) == 288230376156045312UL) ||
        ((bace & 18014398576730112UL) == 18014398576730112UL) ||
        ((bace & 562950024732672UL) == 562950024732672UL))
      l2_moves.push_back(make_move(31, 13));
    if (((bace & 288230376156045568UL) == 288230376156045568UL) ||
        ((bace & 18014398576730368UL) == 18014398576730368UL) ||
        ((bace & 562950024732928UL) == 562950024732928UL) ||
        ((bace & 35184443523328UL) == 35184443523328UL))
      l2_moves.push_back(make_move(31, 8));
    if (((bace & 288230376156045584UL) == 288230376156045584UL) ||
        ((bace & 18014398576730384UL) == 18014398576730384UL) ||
        ((bace & 562950024732944UL) == 562950024732944UL) ||
        ((bace & 35184443523344UL) == 35184443523344UL) ||
        ((bace & 1099583070224UL) == 1099583070224UL))
      l2_moves.push_back(make_move(31, 4));

    // check for L1 king moves (non-capturing)
    if (((bace & 134217728UL) == 134217728UL))
      l1_moves.push_back(make_move(31, 27));
    if (((bace & 67108864UL) == 67108864UL))
      l1_moves.push_back(make_move(31, 26));
    if (((bace & 71303168UL) == 71303168UL))
      l1_moves.push_back(make_move(31, 22));
    if (((bace & 71434240UL) == 71434240UL))
      l1_moves.push_back(make_move(31, 17));
    if (((bace & 71442432UL) == 71442432UL))
      l1_moves.push_back(make_move(31, 13));
    if (((bace & 71442688UL) == 71442688UL))
      l1_moves.push_back(make_move(31, 8));
    if (((bace & 71442704UL) == 71442704UL))
      l1_moves.push_back(make_move(31, 4));
  }

  // ---- end of loc 31

  // remove l2 moves which share the origin with any l3 move but keep the other
  // mandatory moves
  std::unordered_set<Loc> hot_fields;
  std::transform(l3_moves.begin(), l3_moves.end(),
                 std::inserter(hot_fields, hot_fields.end()), get_from);
  std::copy_if(l2_moves.begin(), l2_moves.end(), std::back_inserter(l3_moves),
               [&hot_fields](const Move &m) {
                 return hot_fields.find(get_from(m)) == hot_fields.end();
               });

  return !l3_moves.empty() ? l3_moves : l1_moves;
}

std::vector<Move> valid_moves(const Slice &bk, const Slice &wt,
                              bool blacks_turn) {
  std::vector<Move> moves;

  if (blacks_turn) {
    moves = _valid_moves_top_down(bk, wt);
  } else {
    // flip board upside down
    const Slice &bk_rot = rotate_slice(bk);
    const Slice &wt_rot = rotate_slice(wt);

    // play usual top-down
    moves = _valid_moves_top_down(wt_rot, bk_rot);

    // translate moves back: m --> 31 - m, i.e. take their one-complement (or
    // simply binary "not"); uses above condition that the two times three
    // superfluous bits of each move may have arbitrary values
    for (Move &m : moves)
      m = ~m;
  }

  return moves;
}

} // namespace shashki