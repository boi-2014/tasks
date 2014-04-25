Unit graderlib;

Interface

function ping (i, j : integer) : integer;
procedure travelTo (k : integer);

Implementation

uses network;

const
    MAX_N = 1010;

var
    N, x, y : integer;
    M, pingCount : longint;
    distance : array [1..MAX_N, 1..MAX_N] of integer;
    routeLength : integer;
    u, v, current : integer;

procedure raiseError (message : string);
begin
    writeln ('ERROR');
    writeln (message);
    halt;
end;

function ping (i, j : integer) : integer;
begin
    if (i < 1) or (j < 1) or (i > N) or (j > N) or (i = j) then
        raiseError ('ping called with invalid arguments');

    pingCount := pingCount + 1;
    if pingCount > M then
        raiseError ('Too many calls to ping');

    ping := distance[i, j];
end;

procedure travelTo (k : integer);
begin
    if (k < 1) or (k > N) then
        raiseError ('travelTo called with invalid argument');

    if (k = current) or (distance[current, k] > 0) then
        raiseError ('Travelling to nonadjacent computer');

    routeLength := routeLength + 1;
    if (routeLength > distance[x, y] + 1) then
        raiseError ('Route is too long');

    current := k;
end;

Begin
    readln (N, x, y, M);

    for u := 1 to N do
        for v := 1 to N do
            read (distance[u, v]);

    pingCount := 0;
    routeLength := 0;
    current := x;

    findRoute (N, x, y);

    if (current <> y) then
        raiseError ('Message has not reached its target');

    if (routeLength < distance[x, y] + 1) then
        raiseError ('Unexpected: route is too short');

    writeln ('OK');
End.
