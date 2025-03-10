merge2Lists([],L,L).
merge2Lists(L,[],L).


merge2Lists([H1|T1],[H2|T2],[H1|R]):-
	H1 < H2,
	merge2Lists(T1,[H2|T2],R).

merge2Lists([H1|T1],[H2|T2],[H2|R]):-
	H1 > H2,
	merge2Lists([H1|T1],T2,R).
	
merge2Lists([H|T1],[H|T2],[H|R]):-
	merge2Lists(T1,T2,R).


tests:-
	merge2Lists([1,2,3,5,7],[2,4,6,8],[1,2,3,4,5,6,7,8]).
	merge2Lists([3,4],[],[3,4]).
	 