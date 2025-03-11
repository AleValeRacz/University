

pkg load statistics;


X = [ 3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];

alpha = 0.05;
n = length(X);
 miu = 3;

%H0: the nickel particles are not smaller than 3
%H1: the nickel particles are smaller than 3
%%we compare with a number, sigma unknown-> we do ttest with left tail (H1: the population mean is < 3)
[H, P, ci, stats] = ttest(X, miu, "alpha", alpha, "tail", "left");

%H0: the nickel particles are not smaller than 3
%H1: the nickel particles are smaller than 3

 % Interpret the result
if H == 1
    printf("H = 1: The null hypothesis is rejected. The data suggests that the nickel particles seem to be smaller than 3\n");
else
    printf("H = 0: The null hypothesis is not rejected. It seems like the nickel particals are not smaller thann 3\n");
end


% Compute rejection region
%second case of the 1. from test.pdf because the underlying population is normal
tt_alpha = tinv(alpha, n-1);


% Output results
printf("Rejection region: (-Inf, %4.4f)\n", tt_alpha);
printf("The value of the test statistic is %4.4f\n", stats.tstat);
printf("P-value: %4.4f\n", P);

%b)

alpha2 = 0.01;

v = var(X); % is S^2
q1 = chi2inv(1-alpha2/2, n-1); % quantilees
q2 = chi2inv(alpha2/2, n-1);
v1 = (n-1) * v/q1;  %for the population variance
v2 = (n-1) * v/q2;
s1 = sqrt(v1);
s2 = sqrt(v2);

printf( " 99% Confidence  interval for st. deviation (s1,s2) = (%4.3f, %4.3f)\n",s1,s2);






