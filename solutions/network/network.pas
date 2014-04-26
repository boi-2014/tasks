Unit network;

Interface

procedure findRoute (N, a, b : integer);

Implementation

uses graderlib;

procedure findRoute (N, a, b : integer);
const MAX_N = 1000;
var
    i, x : integer;
    db: array[1..MAX_N] of Integer;
begin
    for i := 1 to N do
        if i = b then db[i] := 0 else db[i] := ping(i, b) + 1;
    x := a;
    while (db[x] > 0) do
        for i := 1 to N do
            if ((db[i] = db[x] - 1) and (ping(x, i) = 0)) then begin
                x := i;
                travelTo (i);
                break;
            end;
end;

End.
