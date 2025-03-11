pkg load statistics

p = input("Enter value for p (between 0 and 1): \n");
N = input("Enter value for N (number of simulations(10,100,1000,etc):  \n");
X  = zeros(1,N);
for i = 1 : N
  U = rand;
  X(i) = (U < p);
endfor

U_X = [0 1];
n_X = hist(X, length(U_X));
rel_freq = n_X / N;
printf("%1.6f\n",rel_freq(1));
printf("%1.6f\n",rel_freq(2));


