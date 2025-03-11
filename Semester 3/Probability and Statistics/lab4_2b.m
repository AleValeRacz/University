
n = input("Give number of trials: \n");
p = input("Give prob of success (between 0,1): \n");
N = input("Give number of simulations: \n");
U = rand(n,N);
X = sum(U < p);
printf("%1.6f \n", X);

k = 0:n;
pk = binopdf(k,n,p);
U_X = unique(X);
n_X = hist(X, length(U_X));
rel_freq = n_X / N;
clf
plot(U_X,rel_freq,"*",k,pk,"ro");
legend("simulation", "binomial");


