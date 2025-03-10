P1 
1.a)
cmmdc(A,0,A):- A > 0.

cmmdc(A,B,Res):-
    B>0,
    Rest is A mod B,
    cmmdc(B,Rest,Res).

cmmmc(A,B,Res):-
    cmmdc(A,B,Nr),
    Res is(A*B)//Nr.

cmmmc_list([],false).
cmmmc_list([A],A).

cmmmc_list([H|T],Res):-
    cmmmc_list(T,Rest),
    cmmmc(H,Rest,Res).

1. b)

insertDouble([],_,_,_,[]).

%insertDouble(List,V,Pos,NextPos,Result).

insertDouble([H|T],V,Pos,Pos,[H,V|R]):-
	Pos1 is Pos +1,
	NextPos1 is Pos *2,
	insertDouble(T,V,Pos1,NextPos1,R).

insertDouble([H|T],V,Pos,NextPos,[H|R]):-
	Pos =\= NextPos,
	Pos1 is Pos +1,
	insertDouble(T,V,Pos1,NextPos,R).

2 a)
%removeAtom(List,Atom,Result).
removeAtom([],_,[]).

removeAtom([H|T],Atom,R):-
    H = Atom,
    removeAtom(T,Atom,R).

removeAtom([H|T],Atom,[H|R]):-
    \+ H = Atom,
    removeAtom(T,Atom,R).

b) 
countOcc([],_,0).

countOcc([X|T],X,Count):-
    countOcc(T,X,Count1),
	Count is Count1 +1.

    
countOcc([H|T],X,Count):-
	H \= X,
    countOcc(T,X,Count). 

numberAtom([],[]).

numberAtom([H|T],[[H,Count]|R]):-
    countOcc([H|T],H,Count),
    removeAtom(T,H,Res),
    numberAtom(Res,R).

3 a)removeRepetitives([],[]).

removeRepetitives([H|T],R):-
    countOcc(T,H,Count),
    Count > 0,
    removeAtom(T,H,Res),
    removeRepetitives(Res,R).

removeRepetitives([H|T],[H|R]):-
    countOcc(T,H,Count),
    Count == 0,
    removeRepetitives(T,R).

b)findMax([X],X).

findMax([H|T],H):-
    findMax(T,MaxTail),
    H> MaxTail.
findMax([H|T],MaxTail):-
    findMax(T,MaxTail),
    H =< MaxTail.

removeAllMax([],[]).

removeAllMax(List,Res):-
    findMax(List,Max),
    removeAtom(List,Max,Res).



removeSortedDoubles([],[]).

removeSortedDoubles([H|T],[H|R]):-
    countOcc(T,H,Count),
    Count > 0,
    removeAtom(T,H,Res),
    removeSortedDoubles(Res,R).

removeSortedDoubles([H|T],[H|R]):-
    countOcc(T,H,Count),
    Count =:= 0,
    removeSortedDoubles(T,R).

wrapper_f(List,R):-
    removeSortedDoubles(List,Rez1),
    insertion_sort(Rez1,R).

insertion_sort([], []).
insertion_sort([H|T], Sorted) :-
    insertion_sort(T, SortedT),      
    insert_in_order(H, SortedT, Sorted).  

insert_in_order(X, [], [X]). 
insert_in_order(X, [H|T], [X, H|T]) :- 
    X =< H.  
insert_in_order(X, [H|T], [H|SortedT]) :-
    X > H, 
    insert_in_order(X, T, SortedT).




