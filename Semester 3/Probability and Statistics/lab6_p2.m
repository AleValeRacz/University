% for 2nd exercise a), use vartest2 to decide if variances are equal or not
%                  b), the test here depends on a) variances equal -> version 1 / variances not equal -> version 2 (different formulas)


pkg load statistics
% data sets
x_premium = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
x_regular = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];

n1 = length(x_premium);
n2 = length(x_regular);

% the significance level is 5% => alpha = 0.05
alpha = 0.05;

%a

% H0 - the null hypothesis
% H0: the variances of the two populations are equal
% H0: sigma_premium^2 = sigma_regular^2
% H1 - the research hypothesis
% H1: the variances of the two populations are not equal
% H1: sigma_premium^2 != sigma_regular^2
% => we perform a two-tailed test
fprintf("We perform a two-tailed test for the ratio of two population variances\n");

% we want to perform a test for the ratio of two population variances
% => vartest2 as TT in F(n_1-1, n_2-1)


% vartest2 -> test for the ratio of two population variances
% INPUT : x1 = the first data sample
%         x2 = the second data sample
%         alpha = the significance level
% OUTPUT: H = indicator which tells us if we reject or do not reject H_0
%         P = critical value of the test (p-value)
%         CI = confidence interval
%         statistics = TS_0 TS when theta = theta0. If TS_0 is in RR => reject H0.

[H, P, CI, stats] = vartest2(x_premium, x_regular,"alpha", alpha);


% result of the test, h = 0, if H0 is NOT rejected,
% h = 1, if H0 IS rejected
fprintf('\n H is %d', H)
if H == 1
  fprintf('\n So the null hypothesis is rejected, \n')
  fprintf('i.e the data suggests that the variances of the two populations are not equal')
else
  fprintf('\nSo the null hypothesis is not rejected,\n')
  fprintf('i.e. the data suggests that the variances of the two populations are equal.\n')
end

% building the rejection region
% RR = (-inf, tt_{alpha/2}) U (tt_{1-alpha/2},inf) since it's a two-tailed test
% tt_alpha is the quantile for the F(n_1-1, n2_-1) distribution

tt_alpha1 = finv(alpha/2, n1-1, n2-1);
tt_alpha2 = finv(1-alpha/2, n1-1, n2-1);
RR1 = [-inf, tt_alpha1];
RR2 = [tt_alpha2, inf]; % vector with 2 positions

% print ZVAL, P and RR on the screen
fprintf('\nThe rejection region is (%4.4f, %4.4f) U (%4.4f, %4.4f)\n', RR1, RR2);
fprintf('The value of the test statistic z is %4.4f\n', stats.fstat);
fprintf('The P-value of the test is %4.4f\n\n', P);




% b
% The null hypothesis is H0: miu1 = miu2 (the means are equal)
% The alternative hypothesis is H1: miu1 > miu2 (the mean of the premium mileage is higher than the mean of the regular mileage)
% We will do a right-tailed test

fprintf("\n\n\n");
fprintf("We are solving the second part of the problem\n");
fprintf("We are using a right tailed test for the equality of means when the variances are unequal\n");

[h, pval, ci, stats] = ttest2(premium, regular, "alpha", alpha, "tail", "right", "vartype", "unequal"); % ALSO CHANGE THIS IF EQUAL VARIANCES

% h - 1 if H0 is rejected, 0 if H0 is not rejected
% pval - the P-value of the test, the probability of observing a test statistic as extreme as
% or more extreme than the observed value under the null hypothesis
% ci - the confidence interval for the ratio of population variances
% stats - a structure containing
%         - tstat - the value of the test statistic
if(h == 0)
  fprintf("H0 is not rejected, gas mileage does not seem higher on average for premium gasoline\n");
else
  fprintf("H0 is rejected, gas mileage seems higher on average for premium gasoline\n");
endif

% if variances equal:
q1 = tinv(1-alpha, n1 + n2 - 2);

% if variances unequal:
v1 = var(x1);
v2 = var(x2);
c = (v1/n1) / ((v1/n1) + (v2/n2));
oneOverN = (c*c)/(n1-1) + ((1-c)*(1-c))/(n2-1);
n = 1/oneOverN;

q2 = tinv(1-alpha, n);


fprintf("The rejection region is (%3.4f, inf)\n", q1);
fprintf("The value of the test statistic is: %1.4f\n", stats.tstat);
fprintf("The p-value of the test is %1.4f\n", pval);
