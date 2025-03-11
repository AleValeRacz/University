pkg load statistics


%Bernulli Distribution Bern(p)
p = input("Enter value for p (between 0 and 1): \n");
N = input("Enter value for N (number of simulations(10,100,1000,etc):  \n");
X  = zeros(1,N); %to store outcomes, initialised to 0 at first
for i = 1 : N
  U = rand; %Generate a random number U in [0,1)
  X(i) = (U < p); % assign 1 (true) if U<p meaning it was a success, it will remain 0 otherwise
endfor

U_X = [0 1];
n_X = hist(X, length(U_X)); %the histogram of X, counting how many times each unique value (0 and 1) appears->return a vector n_X
rel_freq = n_X / N; %convers the counts into relative frequencies
printf("%1.6f\n",rel_freq(1)); %relative freq of 0 (fail)
printf("%1.6f\n",rel_freq(2)); %relative freq of 1 (success)


