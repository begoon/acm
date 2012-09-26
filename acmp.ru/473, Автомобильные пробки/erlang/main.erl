#!/usr/bin/env escript

main(_) ->
  A0 = 6, A = A0 - 1,
  io:format("~w\n", [traf(A, 1) + traf(A, 2) + traf(A, 3) + traf(A, 4)]).

traf(1, _) -> 1;

traf(N, 1) -> traf(N-1, 1) + traf(N-1, 2) + traf(N-1, 3) + traf(N-1, 4);
traf(N, 2) -> traf(N-1, 1) + traf(N-1, 3);
traf(N, 3) -> traf(N-1, 1) + traf(N-1, 2);
traf(N, 4) -> traf(N-1, 1).
