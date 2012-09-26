{$A+,B-,D+,E-,F-,G-,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+} 
{M 65520,0,655360}

program recovery; 
const 
  maxLength = 80; 
  lenMax = 100; 
  pow = 10000; 
type 
  tNumber = record 
              len : integer; 
              num : array[1..lenMax] of word; 
            end; 
var 
  balance, old : array[0..maxLength+10] of tNumber; 
  i, j : integer; 
  s : string; 
 
procedure add(var a : tNumber; const b : tNumber); 
var 
  r : word; 
  i : integer; 
begin 
  r := 0; 
  if a.len < b.len then 
    a.len := b.len; 
  for i := 1 to a.len do begin 
    inc(r, a.num[i]+b.num[i]); 
    a.num[i] := r mod pow; 
    r := r div pow; 
  end; 
 
  if r > 0 then begin 
    inc(a.len); 
    a.num[a.len] := 1; 
  end; 
end; 
 
procedure print(const a : tNumber); 
var 
  i : integer; 
  j : longint; 
begin 
  if a.len = 0 then 
    write(0) 
  else begin 
    write(a.num[a.len]); 
    for i := a.len-1 downto 1 do begin 
      j := a.num[i]+ord(a.num[i]=0); 
      while j*10 < pow do begin 
        write(0); 
        j := j*10; 
      end; 
      write(a.num[i]); 
    end; 
  end; 
 
  writeLn; 
end; 
 
Begin 
  assign(input, 'input.txt'); 
  reSet(input); 
  assign(output, 'output.txt'); 
  reWrite(output); 
 
  readLn(s); 
  fillChar(balance, sizeOf(balance), 0); 
  balance[0].len := 1; balance[0].num[1] := 1; 
  for i := 1 to length(s) do begin 
    old := balance; 
    fillChar(balance, sizeOf(balance), 0); 
 
    if (old[0].num[1] > 0) and ((s[i] = '(') or (s[i] = '?')) then 
      balance[1] := old[0]; 
 
    for j := 1 to length(s)+1 do begin 
      if (s[i] = '(') or (s[i] = '?') then 
        add(balance[j+1], old[j]); 
      if (s[i] = ')') or (s[i] = '?') then 
        add(balance[j-1], old[j]); 
    end; 
  end; 
 
  print(balance[0]); 
 
  close(input);close(output) 
End.
