

candidate([E|_],E).
candidate([_|T],E):-
    candidate(T,E).

%arrangements(lista,k,v,col,result).

arrangements_prod(_,0,V,Col,Col,P):-
    P < V.

arrangements_prod(L,K,V,Col,R,P):-
    candidate(L,E),
    \+ candidate(Col,E),
    P1 is P*E,
    K1 is K-1,
    arrangements_prod(L,K1,V,[E|Col], R, P1). 
    
wrapper(L,K,V,R):-
    findall(X, arrangements_prod(L,K,V,[],X,1), R).


%combinations_sum(list,k,v,col,S,result).

combinations_sum(_,0,V,Col,S,Col):-
    S =:= V.

combinations_sum(L,K,V,[],S,R):-
    candidate(L,E),
    K1 is K -1,
    combinations_sum(L,K1,V,[E],S,R).

combinations_sum(L,K,V, [H|T],S,R):-
    K > 0,
    candidate(L,E),
    \+ candidate([H|T],E),
    E < H,
    S1 is S + E,
    S1 =< V,
    write(S1),
    K1 is K -1,
    combinations_sum(L,K1,V, [E,H|T],S1,R).

all_combinations(L,K,V,R):-
    findall(X, combinations_sum(L,K,V,[],0,X), R).



%subsets_sumDiv(l,n,s,col,r).

candidate([E|_],E).
candidate([_|T],E):-
    candidate(T,E).

subsets_sumDiv(_,N,S,Col,Col):-
    N =:= 0,
    S  =:= 15.

subsets_sumDiv(L,N,S,[],Res):-
    candidate(L,E),
    S1 is S + E,
    N1 is N - 1,
    subsets_sumDiv(L,N1,S1,[E],Res).

subsets_sumDiv(L,N,S,[H|T],Res):-
   candidate(L,E),
    \+ candidate([H|T],E),
    S1 is S + E,
    N1 is N - 1,
    subsets_sumDiv(L,N1,S1,[E,H|T],Res).


allSubsets(L,N,R):-
    findall(X, subsets_sumDiv(L,N,0,[],X), R).


candidate([E|_],E).
candidate([_|T],E):-
    candidate(T,E).


construct_list(N,N,[]).

construct_list(N,Nr,[N|R]):-
	N1 is N +1,
	construct_list(N1,Nr,R).

permutations(_,0,Col,Col).

permutations(L,N,[],Res):-
    candidate(L,E),
    N1 is N -1,
    permutations(L,N1,[E],Res).


permutations(L,N,[H|T],Res):-
    candidate(L,E),
    \+candidate([H|T],E),
    abs(E - H) =< 2,
    N1 is N - 1,
    permutations(L,N1,[E,H|T], Res).

all_perm(N,Res):-
    N2 is N*2,
    construct_list(N,N2,L),
    findall(X, permutations(L,N,[],X),Res).


%Subsets of at least n elements, having the sum of the elems divisible with 3
                
%subsets_sumDiv(l,n,s,col,r).


subsets_sumDiv(_,N,S,Col,Col):-
    N =< 0,
    S  mod 3 =:=0 .

subsets_sumDiv(L,N,S,[],Res):-
    candidate(L,E),
    S1 is S + E,
    N1 is N - 1,
    subsets_sumDiv(L,N1,S1,[E],Res).

subsets_sumDiv(L,N,S,[H|T],Res):-
   candidate(L,E),
    \+ candidate([H|T],E),
    E < H,
    S1 is S + E,
    N1 is N - 1,
    subsets_sumDiv(L,N1,S1,[E,H|T],Res).


allSubsets(L,N,R):-
    findall(X, subsets_sumDiv(L,N,0,[],X), R).



%subsets with sum S and an even nr of even elems

candidate([E|_],E).
candidate([_|T],E):-
    candidate(T,E).

%subsets_sum(l,n,s,nrEv,col,r).
subsets_sum(_,N,0,NrEv,Col,Col):-
    N >= 0,
    NrEv mod 2 =:=0.

subsets_sum(L,N,S,NrEv,[],Res):-
    candidate(L,E),
    E mod 2 =:= 0,
    NrEv1 is NrEv + 1,
    S1 is S - E,
    N1 is N - 1,
    subsets_sum(L,N1,S1,NrEv1,[E],Res).

subsets_sum(L,N,S,NrEv,[],Res):-
    candidate(L,E),
    E mod 2 =:= 1,
    S1 is S - E,
    N1 is N - 1,
	subsets_sum(L,N1,S1,NrEv,[E],Res).

subsets_sum(L,N,S,NrEv,[H|T],Res):-
    candidate(L,E),
    \+ candidate([H|T],E),
    E < H,
    E mod 2 =:= 1,
    S1 is S - E,
    N1 is N - 1,
	subsets_sum(L,N1,S1,NrEv,[E,H|T],Res).

subsets_sum(L,N,S,NrEv,[H|T],Res):-
    candidate(L,E),
    \+ candidate([H|T],E),
    E < H,
    E mod 2 =:= 0,
    NrEv1 is NrEv +1,
    S1 is S - E,
    N1 is N - 1,
    subsets_sum(L,N1,S1,NrEv1,[E,H|T],Res).

mylen([], 0).
mylen([_|T], Len) :-
   	mylen(T, TLen),
    Len is TLen+ 1.



allSubsets(L,S,R):-
    mylen(L,N),
    findall(X, subsets_sum(L,N,S,0,[],X), R).



candidate([E|_],E).
candidate([_|T],E):-
    candidate(T,E).

subsetsProg(_,K,_,Col,Col):-
    K =:=0.

subsetsProg(L,K,Diff,[],R):-
    candidate(L,E),
    E mod 2 =:= 1,
    K1 is K - 1,
    subsetsProg(L,K1,Diff,[E], R).

subsetsProg(L,K,_,[H],R):-
    candidate(L,E),
    E =\= H,
    E mod 2 =:= 1,
    Diff is abs(E - H),
    E < H,
    K1 is K - 1,
    subsetsProg(L,K1,Diff,[E,H],R).

subsetsProg(L,K,Diff,[H|T],R):-
    candidate(L,E),
    \+ candidate([H|T], E),
    E mod 2 =:= 1,
    abs(E - H) =:= Diff,
    E < H,
    K1 is K - 1,
    subsetsProg(L,K1,Diff,[E,H|T],R).

allSubsets(L,K,R):-
    findall(X, 	subsetsProg(L,K,0,[],X), R).


candidate([E|_],E).
candidate([_|T],E):-
    candidate(T,E).

%subsets_sum(l,n,s,nrEv,col,r).
subsets_sum(_,N,S,NrOdd,Col,Col):-
    N >= 0,
    NrOdd mod 2 =:= 1,
    S mod 2 =:= 1.


subsets_sum(L,N,S,NrOdd,[],Res):-
    candidate(L,E),
    E mod 2 =:= 1,
    NrOdd1 is NrOdd + 1,
    S1 is S + E,
    N1 is N + 1,
    subsets_sum(L,N1,S1,NrOdd1,[E],Res).

subsets_sum(L,N,S,NrEv,[],Res):-
    candidate(L,E),
    E mod 2 =:= 0,
    S1 is S + E,
    N1 is N + 1,
	subsets_sum(L,N1,S1,NrEv,[E],Res).

subsets_sum(L,N,S,NrOdd,[H|T],Res):-
    candidate(L,E),
    \+ candidate([H|T],E),
    E < H,
    E mod 2 =:= 0,
    S1 is S + E,
    N1 is N + 1,
	subsets_sum(L,N1,S1,NrOdd,[E,H|T],Res).


subsets_sum(L,N,S,NrOdd,[H|T],Res):-
    candidate(L,E),
    \+ candidate([H|T],E),
    E < H,
    E mod 2 =:= 1,
    NrOdd1 is NrOdd +1,
    S1 is S + E,
    N1 is N + 1,
    subsets_sum(L,N1,S1,NrOdd1,[E,H|T],Res).

    

allSubsets(L,R):-
    findall(X, subsets_sum(L,0,0,0,[],X), R).




candidate([E|_],E).
candidate([_|T], E):-
    candidate(T,E).

subsets_increasing(_,N,Col,Col):-
    N >= 0.

subsets_increasing(L,N,[],R):-
    candidate(L,E),
    N1 is N +1,
    subsets_increasing(L,N1,[E],R).

subsets_increasing(L,N,[H|T],R):-
    candidate(L,E),
    \+ candidate([H|T], E),
    E < H,
    N1 is N+1,
    subsets_increasing(L,N1,[E,H|T],R).

myLen([],0).
myLen([_|T], Len):-
    myLen(T, TLen),
    Len is TLen + 1.

allsubsets(L,R):-
    %myLen(L,N),
    findall(X, subsets_increasing(L,0,[],X), R ).

    


% flow model (i, i, o)
% chairs(list, number, list)
% chairs(l1l2..ln, Count) = { [], n=0
%                            { 'Y' U chairs(l2..ln, Count-1)
%               
%                                         { l1 U chairs(l2..ln, Count)
chairs([], _, []).
chairs([_|T], Count, ['Y'|R]):-
    Count > 0,
    NewC is Count-1,
    chairs(T, NewC, R).

 
chairs([H|T], Count, [H|R]):-
    chairs(T, Count, R).
    
% flow model (o)
% main(list)
% main() = U(i=0, i<=n) chairs(['R', 'R', 'R', 'R', 'R'], 3)
main(R):-
    findall(X, chairs(['R', 'R', 'R', 'R', 'R'], 3, X), R).




    

