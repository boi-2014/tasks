Unit network;

Interface

procedure findRoute (N, a, b : integer);

Implementation

uses graderlib;

procedure findRoute (N, a, b : integer);
var
    i : integer;
begin
    {
        Obviously, this is not a good solution.
        Replace it with your own code.
    }
    for i := 1 to ping (a, b) do
        travelTo (i);
end;

End.
