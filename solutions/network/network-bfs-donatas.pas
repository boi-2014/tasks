Unit network;

Interface

procedure findRoute (N, x, y : integer);

Implementation

uses graderlib;

const
	MAX_N = 1000;
	INF = 2*MAX_N;

procedure findRoute (N, x, y : integer);
var
    i, j: integer;
	eNr: array[1..MAX_N] of integer;
	e: array[1..MAX_N, 0..MAX_N-1] of integer;

	now: integer;
	next, newDist: integer;

	dist: array[1..MAX_N] of integer;
	back: array[1..MAX_N] of integer;
	visited: array[1..MAX_N] of boolean;

	path: array[0..MAX_N-1] of integer;
	pathLength: integer;
begin
	for i := 1 to N do
	begin
		eNr[i] := 0;
		dist[i] := INF;
		visited[i] := false;
	end;
	dist[x] := 0;
	for i := 1 to N do
		for j := i+1 to N do
			if ping(i, j) = 0 then
			begin
				e[i, eNr[i]] := j;
				e[j, eNr[j]] := i;
				eNr[i] := eNr[i] + 1;
				eNr[j] := eNr[j] + 1;
			end;
	
	now := x;
	while now <> -1 do
	begin
		{WriteLn(now);}
		for i := 0 to eNr[now]-1 do
		begin
			next := e[now, i];
			{WriteLn('next:', next);}
			newDist := dist[now] + 1;
			if newDist < dist[next] then
			begin
				dist[next] := newDist;
				back[next] := now;
			end;
		end;
		{WriteLn('bfs: ', now);}
		visited[now] := true;
		now := -1;
		for i := 1 to N do
			if (not visited[i]) and (dist[i] <> INF) and ((now = -1) or (dist[i] < dist[now])) then
				now := i;
	end;

	pathLength := 0;
	now := y;
	while now <> x do
	begin
		path[pathLength] := now;
		pathLength := pathLength + 1;
		{WriteLn(now);}
		now := back[now];
	end;
	for i := pathLength-1 downto 0 do
		travelTo(path[i]);
end;

End.
