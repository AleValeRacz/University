pkg load statistics;

X = [ 7,7,4,5,9,9, ...
    4, 12, 8,1,8,7, ...
    3, 13, 2, 1,17,7,...
    12, 5,6,2,1,13,...
    14, 10, 2, 4, 9,11,...
    3, 5, 12, 6, 10, 7];

n = length(X);
printf("%d\n", n);

confLevel = input("Give value for confidence level: \n");
alpha = 1 - confLevel;


% best conf level is 99

sigma = 5;
xbar = mean(X);

printf("%1.4f\n", xbar);

% subpunct a)

m1 = xbar - sigma / sqrt(n)* norminv(1-alpha/2, 0,1);
m2 = xbar - sigma / sqrt(n)* norminv(alpha/2, 0,1);

printf("the ci for the pop mean when sigma is known is (%4.3f, %4.3f)\n", m1, m2);

% subpunct b)

s = std(X);
m1b = xbar - s / sqrt(n)* tinv(1 - alpha/2, n-1);
m2b = xbar - s / sqrt(n)* tinv(alpha/2, n-1);

printf("the ci for the popuation mean when sigma is unknown is (%4.3f, %4.3f)\n", m1b, m2b);

%subpunct c)
v = var(X); % is S^2
v1= (n-1) * v /chi2inv(1-alpha/2,n-1);
v2= (n-1) * v/chi2inv(alpha/2, n -1);

printf("the ci for the variance is: (%4.3f, %4.3f)\n", v1, v2);
s1= sqrt(v1);
s2 = sqrt(v2);

printf("the ci for the population standard deviation : (%4.3f, %4.3f)\n", s1,s2);

