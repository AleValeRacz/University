

%gunpowder tested in 12 shells;


X = [1001.7 975.0 978.3 988.3 978.7 988.8 1000.3 979.2 968.9 983.5 999.2 985.6];

 alpha = 0.05;

 miu = 995;

n = length(X);
 %%right hand
 [H, P, ci, stats] = ttest(X, miu, "alpha", alpha, "tail", "right");


 % Interpret the result
if H == 1
    fprintf('H = 1: H0 is rejected. The data suggests that the nickel particles are faster than 995 m/s.\n');
else
    fprintf('H = 0: H0 is not rejected. There is insufficient evidence to suggest the nickel particles are faster than 995 m/s.\n');
end


% Compute rejection region

tt_alpha = tinv(1-alpha, n-1);
RR = [tt_alpha, Inf];

% Output results
fprintf('Rejection region: (%4.4f, Inf)\n', tt_alpha);
fprintf('Value of the test statistic: %4.4f\n', stats.tstat);
fprintf('P-value: %4.4f\n', P);

%find the 99% conf interval for the standard deviation of the velocity of shells.

alpha = 0.01;

v = var(X); % is S^2
q1 = chi2inv(1-alpha/2, n-1); % quantilees
q2 = chi2inv(alpha/2, n-1);
v1 = (n-1) * v/q1;
v2 = (n-1) * v/q2;
s1 = sqrt(v1);
s2 = sqrt(v2);


%printf( "Conf interval for variance (v1,v2) = (%4.3f, %4.3f)\n",v1,v2);
printf( "Conf interval for st. deviation (s1,s2) = (%4.3f, %4.3f)\n",s1,s2);



