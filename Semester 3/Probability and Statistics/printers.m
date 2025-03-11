pkg load statistics
% A study is conducted to compare the total printing time in seconds of two
% brands of laser printers on various tasks. Data below are for the
% printing of charts (normality of the two populations is assumed):
% Brand A: [21.8,22.6,21.0,19.7,21.9,21.6,22.5,23.1,22.2,20.1,21.4,20.5]
% Brand B: [36.5,35.2,36.2,34.0,36.4,36.1,37.5,38.0,36.3,35.9,35.7,34.9]
% a. At 5% significance level, do the population variances seem to differ?
% b. Find a 95% confidence interval for the differencec of the average
% printing times.

alpha = 0.05;

A = [21.8,22.6,21.0,19.7,21.9,21.6,22.5,23.1,22.2,20.1,21.4,20.5];
B = [36.5,35.2,36.2,34.0,36.4,36.1,37.5,38.0,36.3,35.9,35.7,34.9];

n1 = length(A);
n2 = length(B);

%the null hypothesis
%H0: The population variances don't seem to differ
%H1: The population variances seem to differ

%we perform a two tailed test
% we want to perform a test for the ratio of two population variances
% => vartest2 as TT in F(n_1-1, n_2-1)

% vartest2 -> test for the ratio of two population variances
% INPUT : x1 = the first data sample
%         x2 = the second data sample
%         alpha = the significance level
% OUTPUT: H = indicator which tells us if we reject or do not reject H_0
%         P = critical value of the test (p-value)
%         CI = confidence interval


[H, P, CI, stats] = vartest2(A, B,"alpha", alpha);

if H == 1
  fprintf("The null hypothesis is rejected, \n");
  printf("The data suggests that the variances of the two populations seem to differ!");
else
  printf("So the null hypothesis is not rejected,\n")
  printf("The data suggests that the variances of the two populations don't seem to differ!\n");
endif

tt_alpha1 = finv(alpha/2, n1-1, n2-1);
tt_alpha2 = finv(1-alpha/2, n1-1, n2-1);
fprintf('\nThe rejection region is (-inf, %1.4f) U (%1.4f, inf)\n', tt_alpha1, tt_alpha2);
fprintf('The value of the test statistic z is %4.4f\n', stats.fstat);
fprintf('The P-value of the test is %4.4f\n\n', P);

%b) they seem to be the same -> T(n1+n2-2).

t=tinv(1-alpha/2,n1+n2-2);
v1= var(A);
v2 = var(B);
m1 = mean(A);
m2 = mean(B);
sp = sqrt(((n1-1)*v1+(n2-1)*v2)/(n1+n2-2));
sqroot = sqrt(1/n1 + 1/n2);

ci_left = m1 - m2 -t*sp*sqroot;
ci_right = m1 - m2 +t*sp*sqroot;
printf("The 95% confidence interval for the difference of the average printing times is: (%4.4f,%4.4f)\n",ci_left,ci_right);



