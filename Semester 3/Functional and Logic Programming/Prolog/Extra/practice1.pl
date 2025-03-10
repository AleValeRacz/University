%removeEven(List,Result).

removeEven([],[]).

removeEven([H|T],R):-
	number(H),
	H mod 2 =:= 0,
	removeEven(T,R).

removeEven([H|T],[H|R]):-
	\+ number(H),
	removeEven(T,R).

removeEven([H|T],[H|R]):-
	number(H),
	H mod 2 =:= 1,
	removeEven(T,R).

test1:-removeEven([ a, m, 10, 5, 6, 2, 3, 10, n, z ],[ a, m, 5, 3, n, z ]).
test2:-removeEven([2],[]).
cmmdc(A,0,A):- A > 0.

cmmdc(A,B,Res):-
    B>0,
    Rest is A mod B,
    cmmdc(B,Rest,Res).

%dupElem(List,R).
dupElem([],[]).
dupElem([H|T],[H,H|R]):-
	number(H),
	dupElem(T,R).

dupElem([H|T],[H|R]):-
	\+ number(H),
	dupElem(T,R).

%cmmdcList(List,Cmmdc).

cmmdcList([],false).
cmmdcList([H],H).
cmmdcList([H|T],Res):-
	number(H),
	cmmdcList(T,CmmdcT),
	cmmdc(H,CmmdcT,Res).

cmmdcList([H|T],Res):-
	\+number(H),
	cmmdcList(T,Res).


%separateNr(List,N,P).
separateNr([],[],[]).
separateNr([H|T],[H|N],P):-
	H < 0,
	separateNr(T,N,P).
separateNr([H|T],N,[H|P]):-
	H > 0,
	separateNr(T,N,P).

%findMin(List,Min).
findMin([H],H).
findMin([H|T],MinT):-
	findMin(T,MinT),
	MinT < H.
findMin([H|T],H):-
	findMin(T,MinT),
	MinT > H.
	
findMins(N,P,Min_n,Min_p):-
	findMin(N,Min_n),
	findMin(P,Min_p).


%findMax(List,Max).
findMax([H],H).
findMax([H|T],MaxT):-
	findMax(T,MaxT),
	MaxT > H.
findMax([H|T],H):-
	findMax(T,MaxT),
	MaxT < H.

doubleNr([],[]).

doubleNr([H|T],[New|R]):-
	New is H *2,
	doubleNr(T,R).
wrapper(A,B,Nl):-
	findMax(A,Max_a),
	findMax(B,Max_b),
	doubleNr([Max_a,Max_b],Nl).


%Sa vad dintr o lista care numere is prime și sa fac o lista care sa le conțină doar pe ele

isPrime(X):-
	X >1,
	isPrime(X,2).

isPrime(X,D):- D >=X.
isPrime(X,D):-
	X mod D =\= 0,
	D1 is D+1,
	isPrime(X,D1).

filterPrimes([],[]).
filterPrimes([H|T],[H|R]):-
	isPrime(H),
	filterPrimes(T,R).
filterPrimes([H|T],R):-
	\+ isPrime(H),
	filterPrimes(T,R).


%countOcc(List,Elem,Count).
countOcc([],_,0).

countOcc([H|T],Elem,Count):-
	H=:= Elem,
	countOcc(T,Elem,Count1),
	Count is Count1+1.
countOcc([H|T],Elem,Count):-
	H=\= Elem,
	countOcc(T,Elem,Count).

removeAtom([],_,[]).

removeAtom([H|T],Atom,R):-
    H = Atom,
    removeAtom(T,Atom,R).

removeAtom([H|T],Atom,[H|R]):-
    \+ H = Atom,
    removeAtom(T,Atom,R).

removeMultiples([],[]).
removeMultiples([H|T],[H|R]):-
	countOcc(T,H,Count),
	Count =< 2,
	removeAtom(T,H,Res),
	removeMultiples(Res,R).

removeMultiples([H|T],R):-
	countOcc(T,H,Count),
	Count > 2,
	removeAtom(T,H,Res),
	removeMultiples(Res,R).

deletePos([],_,_,[]).

deletePos([_|T],Pos,NextPos,R):-
	Pos =:=NextPos,
	Pos1 is Pos +1,
	NextPos1 is NextPos * 2+1,
	deletePos(T,Pos1,NextPos1,R).

deletePos([H|T],Pos,NextPos,[H|R]):-
	Pos =\=NextPos,
	Pos1 is Pos +1,
	deletePos(T,Pos1,NextPos,R).

addDivisors(Nr,D,[]):- D > Nr.
addDivisors(Nr,D,[D|R]):-
	D =< Nr,
	Nr mod D =:= 0,
	D1 is D+1,
	addDivisors(Nr,D1,R).
addDivisors(Nr,D,R):-
	D =< Nr,
	Nr mod D =\= 0,
	D1 is D+1,
	addDivisors(Nr,D1,R).

insertDivisors([],[]).
insertDivisors([H|T],[Divs,H|R]):-
	\+ isPrime(H),
	addDivisors(H,1,Divs),
	insertDivisors(T,R).

insertDivisors([H|T],[H|R]):-
	 isPrime(H),
	insertDivisors(T,R).

%interclasare(L1,L2,R).

interclasare(L,[],L).
interclasare([],L,L).
interclasare([H1|T1],[H2|T2],[H1|R]):-
	H1 < H2,
	interclasare(T1,[H2|T2],R).

interclasare([H1|T1],[H2|T2],[H2|R]):-
	H1 > H2,
	interclasare([H1|T1],T2,R).

interclasare([H|T1],[H|T2],[H|R]):-
	interclasare(T1,T2,R).
	
	
		


	



	
		



	
	