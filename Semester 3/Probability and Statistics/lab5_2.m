x = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];
xbar = mean(x);
n = length(x);

oneMinusAlpha = input("Give confidence level from (0, 1): "); % confidence level
alpha = 1-oneMinusAlpha; % significance level

% a)
sigma = 5;

m1 = xbar - (sigma/sqrt(n)) * norminv(1-alpha/2, 0, 1); % norminv(-, 0, 1) because N(0, 1)
m2 = xbar - (sigma/sqrt(n)) * norminv(alpha/2, 0, 1);

printf("The confidence interval for the population mean when sigma=5 is (%4.3f; %4.3f)\n", m1, m2);


% b)
s = std(x); % standard deviation
m1b = xbar - (s/sqrt(n)) * tinv(1-alpha/2, n-1); % student law
m2b = xbar - (s/sqrt(n)) * tinv(alpha/2, n-1);

printf("The confidence interval for the population mean when sigma is unknown is (%4.3f; %4.3f)\n", m1b, m2b);


% c)
v = var(x); % v = s^2 % variance = standard deviation  ^ 2
v1 = ((n-1)*v) / chi2inv(1-alpha/2, n-1);
v2 = ((n-1)*v) / chi2inv(alpha/2, n-1);

printf("The confidence interval for the variance is (%4.3f; %4.3f)\n", v1, v2);


s1 = sqrt(v1);
s2 = sqrt(v2);

printf("The confidence interval for the standard deviation is (%4.3f; %4.3f)\n", s1, s2);





