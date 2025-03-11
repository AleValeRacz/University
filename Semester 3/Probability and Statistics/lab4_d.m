

%Pascal distrubution, negative binomial distribution
%Models the nr of failures (k) before n successes occur in a sequence of independent Bernoulli trials

n = input("Give the number of successes (n ∈ IN): \n");
p = input("Give the probability of success (p ∈ (0,1)): \n");
N = input("Give the number of simulations: \n");

X = zeros(1, N); % Vector to store number of failures before n successes
for i = 1:N
  successes = 0; % Track the number of successes
  failures = 0;  % Track the number of failures
  while successes < n
    if rand < p
      successes = successes + 1; % Increment successes if trial succeeds
    else
      failures = failures + 1;  % Increment failures if trial fails
    endif
  endwhile
  X(i) = failures; % Store the number of failures for this simulation
endfor

% Display the simulated failures
printf("Simulated number of failures: \n");
printf("%d  ", X);

% Theoretical Pascal (negative binomial) probabilities
k = 0:20; % Possible values for the number of failures
pk = nbinpdf(k, n, p); % Theoretical negative binomial probabilities

% Analyze simulation results
U_X = unique(X); % Unique values in the simulated results
n_X = hist(X, length(U_X)); % Histogram of simulated results
rel_freq = n_X / N; % Relative frequencies

% Plot the results
clf
plot(U_X, rel_freq, "*", k, pk, "ro");
legend("simulation", "Pascal (NB)");
title("Simulation vs Pascal Distribution");
xlabel("Number of Failures (k)");
ylabel("Probability");
