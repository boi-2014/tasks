program grader;
  uses coprobber;
  { Is it safe to use types defined in coprobber unit? }
  var
    N: Integer;
    A: Matrix;
    CopCanWin: Boolean;
    RobberStrategy: array [0..MAX_N-1, 0..MAX_N] of Integer;
    VisitedPositions: Matrix;
    
    c, r, t, copCorner, robberCorner, nextCopCorner: Integer;
    fin, fout : text;
    
procedure OutputResult(status, msg: string);
begin
  //assign (fout, SECRET_OUT);
  rewrite (fout);
  WriteLn(fout, status);
  if (msg <> '') then
    WriteLn(fout, msg);
  close (fout);
  Halt;
end;

begin
  assign (fin, 'oprobber-i3hfiehflasil.in');
  assign (fout, 'oprobber-i3hfiehflasil.out');
  rewrite (fout);
  close (fout);
  reset(fin);
  Read(fin, N);
  for c := 0 to N-1 do
    for r := 0 to N-1 do
    begin
      Read(fin, t);
      A[c, r] := t = 1;
    end;
  Read(fin, t);
  CopCanWin := t = 1;
  if CopCanWin then
    for c := 0 to N-1 do
      for r := 0 to N do
        Read(fin, RobberStrategy[c, r]);
  close(fin);
  for c := 0 to N-1 do
    for r := 0 to N-1 do
      VisitedPositions[c, r] := False;
  
  copCorner := Start(N, A);
  
  if (copCorner <> -1) and not CopCanWin then
    OutputResult('FAIL', 'Cop cannot catch the robber, but start() did not return -1');
  
  if (copCorner = -1) and CopCanWin then
    OutputResult('FAIL', 'Cop can catch the robber, but start() returned -1');
  
  if not CopCanWin then
    OutputResult('OK', '');
  
  if (copCorner < 0) or (copCorner >= N) then
    OutputResult('FAIL', 'start() returned a value that is outside the 0..N-1 range');
  
  robberCorner := RobberStrategy[copCorner, N];
  
  if robberCorner = copCorner then
    OutputResult('OK', '');
  
  while True do
  begin
    nextCopCorner := NextMove(robberCorner);
    
    if (nextCopCorner < 0) or (nextCopCorner >= N)
      or not ((copCorner = nextCopCorner) or A[copCorner, nextCopCorner]) then
        OutputResult('PARTFAIL', 'nextMove() returned a value that is either outside 0..N-1 ' +
               'or the new cop position is not a neighbour to the previous one');
    
    copCorner := nextCopCorner;
    
    if VisitedPositions[copCorner, robberCorner] then
      OutputResult('PARTFAIL', 'the situation repeated');
    
    VisitedPositions[copCorner, robberCorner] := True;
    
    if copCorner = robberCorner then
      OutputResult('OK', '');
    
    robberCorner := RobberStrategy[copCorner, robberCorner];
    
    if copCorner = robberCorner then
      OutputResult('OK', '');
  end;
end.