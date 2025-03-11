

p = input("Give prob of success (between 0,1): \n");
N = input("Give number of simulations: \n");

X = zeros(1,N); %count the failures with 1st success
for i = 1: N
  X(i) = 0;
  while rand >= p
    X(i) = X(i) + 1;
    endwhile
endfor
printf("%d  ",X);
k= 0:20; %k goes from 0 to unfinity - nr of failures
pk =geopdf(k,p);
U_X = unique(X);
n_X = hist(X, length(U_X));
clf
plot(U_X,n_X/N,"*",k,pk,"ro");
legend("simulation", "geom");

