Unit network;

Interface

procedure findRoute (N, x, y : integer);

Implementation

uses graderlib;

procedure findRoute (N, x, y : integer);
var
    i : integer;
begin
    {
        Obviously, this is not a good solution.
        Replace it with your own code.
    }
    for i := 1 to ping (x, y) do
        travelTo (i);
end;

End.
