{$I+,S+,Q+,R+}
Const
  MaxDepth=40;
Type
  TLex=(_Number,_LeftP,_RightP,_Op,_EOS);
Var
  Expr:String;
  A:LongInt;
  NeedVal:LongInt;
  Err:Integer;
Function Evaluate(What:String):LongInt;
Var
  CRes:Array[0..MaxDepth]Of LongInt;
  LastOp:Array[0..MaxDepth]Of Char;
  CDepth:LongInt;
  Pos:LongInt;
  CLex:TLex;
  Num:LongInt;
  Op:Char;
Procedure NextLexem;
Begin
  If Pos>Length(What) Then Begin
    CLex:=_EOS;
    Exit;
  End;
  Repeat
    Inc(Pos);
    If Pos>Length(What) Then Begin
      CLex:=_EOS;
      Exit;
    End;
  Until What[Pos]>' ';
  Case What[Pos] Of
    '(':CLex:=_LeftP;
    ')':CLex:=_RightP;
    '0'..'9':Begin
      CLex:=_Number;
      Num:=0;
      While (What[Pos]>='0') And (What[Pos]<='9') Do Begin
        Num:=Num*10+Ord(What[Pos])-Ord('0');
        Inc(Pos);
        If Pos>Length(What) Then Break;
      End;
      Dec(Pos);
    End;
    '+','-','*','=':Begin
      CLex:=_Op;
      Op:=What[Pos];
    End;
  End;
End;
Begin
  CDepth:=0;
  Pos:=0;
  CRes[0]:=0;
  LastOp[0]:='+';
  Evaluate:=0;
  Repeat
    NextLexem;
    Case CLex Of
      _LeftP:Begin
        Inc(CDepth);
        CRes[CDepth]:=0;
        LastOp[CDepth]:='+';
      End;
      _RightP:Begin
        Dec(CDepth);
        Case LastOp[CDepth] Of
          '+':Inc(CRes[CDepth],CRes[CDepth+1]);
          '-':Dec(CRes[CDepth],CRes[CDepth+1]);
          '*':CRes[CDepth]:=CRes[CDepth]*CRes[CDepth+1];
        End;
        LastOp[CDepth]:=' ';
      End;
      _Number:Begin
        Case LastOp[CDepth] Of
          '+':Inc(CRes[CDepth],Num);
          '-':Dec(CRes[CDepth],Num);
          '*':CRes[CDepth]:=CRes[CDepth]*Num;
        End;
        LastOp[CDepth]:=' ';
      End;
      _Op:Begin
        LastOp[CDepth]:=Op;
      End;
    End;
  Until CLex=_EOS;
  Evaluate:=CRes[0];
End;
Function Rec(Start:LongInt):Boolean;
Begin
  Rec:=True;
  Repeat
    Inc(Start);
    If Start>Length(Expr) Then Begin
      If Evaluate(Expr)=NeedVal Then
        Exit;
      Rec:=False;
      Exit;
    End;
  Until Expr[Start]='^';
  Expr[Start]:='*';
  If Rec(Start) Then Exit;
  Expr[Start]:='+';
  If Rec(Start) Then Exit;
  Expr[Start]:='-';
  If Rec(Start) Then Exit;
  Expr[Start]:='^';
  Rec:=False;
End;
Begin
  Assign(Input,'input.txt');
  ReSet(Input);
  ReadLn(Expr);
  Close(Input);
  While Pos(' ',Expr)>0 Do Begin
    A:=Pos(' ',Expr);
    If (A=1) Or (A=Length(Expr)) Then
      Delete(Expr,A,1)
    Else If (Expr[A-1] In ['0'..'9',')']) And (Expr[A+1] In ['0'..'9','(']) Then
      Expr[A]:='^'
    Else
      Delete(Expr,A,1);
  End;
  A:=1;
  While A<Length(Expr) Do Begin
    If ((Expr[A]=')') And (Expr[A+1] In ['0'..'9','('])) Or
       ((Expr[A] In ['0'..'9',')']) And (Expr[A+1]='(')) Then
      Insert('^',Expr,A+1)
    Else Inc(A);
  End;
  Val(Copy(Expr,1,Pos('=',Expr)-1),NeedVal,Err);
  Delete(Expr,1,Pos('=',Expr));
  Assign(Output,'output.txt');
  ReWrite(Output);
  If Rec(0) Then
    WriteLn(NeedVal,'=',Expr)
  Else
    WriteLn(-1);
  Close(Output);
End.

