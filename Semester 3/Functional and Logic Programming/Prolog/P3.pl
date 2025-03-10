
%(i)
%mountain(List).


mountain([H1 ,H2|T]) :-
    H1 <H2,               
    increasing([H2|T]).

%increasing(List)
%(i)
increasing([H1,H2|T]):-
	H1 < H2,
	increasing([H2|T]).

increasing([H1,H2|T]):-
    H1>H2,
    decreasing([H2|T]).

%decreasing
%(i)
decreasing([_]).
decreasing([H1,H2|T]):- 
	H1 > H2,
    	decreasing([H2|T]).

%(i,0)
%subset(List,temporaryResultList)
subset([],[]).
subset([H|T],[H|R]) :-
    subset(T,R).

subset([_|T],R) :-
    subset(T,R).

%(i,0)
%m_subsets(List,Result)
m_subsets(L,M):-
	findall(S,(subset(L,S), mountain(S)),M).

tests:-
	m_subsets([1,2,3],[]),
	m_subsets([2,4,5,1],[[2, 4, 5, 1], [2, 4, 1], [2, 5, 1], [4, 5, 1]]).