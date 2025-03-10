addInList(List,E,Result):-
	addInList(List,E,1,1,Result).
	

addInList([],_,_,_,[]).

addInList([H|T],E,Current,NextGood,[H,E|R]):-
	Current =:= NextGood,
    !,
	Current1 is Current +1,
	NextGood1 = NextGood * 2 +1,
	addInList(T,E,Current1,NextGood1,R).

addInList([H|T],E,Current,NextGood,[H|R]):-
	Current =\= NextGood,
    !,
	Current1 is Current +1,
	addInList(T,E,Current1,NextGood,R).




addPrevInSublist([H|T],[H|R]):-
    addPrevInSublist(T,H,R).

addPrevInSublist([],_, []).




addPrevInSublist([H|T] ,_, [H | R]) :-
    number(H), 
    !,
    addPrevInSublist(T, H, R).    


addPrevInSublist([H|T], Prev, [Sublist | R]) :-
    is_list(H), 
    !,
    addInList(H, Prev,	Sublist), 
    addPrevInSublist(T, Prev, R).

tests:-addInList([1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4],13,[1, 13, 1, 1, 13, 1, 2, 2, 2, 13, 2, 3, 3, 3, 3, 4, 4, 4, 13, 4]),
    addInList([4,5,8,1,5],e,[4,e,5,8,e,1,5]),
    addInList([],8,[]),
    addPrevInSublist([1, [2, 3], 7, [4, 1, 4], 3, 6, [7, 5, 1, 3, 9, 8, 2, 7], 5],[1, [2, 1, 3], 7, [4, 7, 1, 4, 7], 3, 6, [7, 6, 5, 1, 6, 3, 9, 8, 2, 6, 7], 5]).






