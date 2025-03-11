pkg load statistics;
%exercise 1
clear all;

alpha = input("Give value for the significance level (between 0 and 1)\n: ");
X = [ 7,7,4,5,9,9, ...
    4, 12, 8,1,8,7, ...
    3, 13, 2, 1,17,7,...
    12, 5,6,2,1,13,...
    14, 10, 2, 4, 9,11,...
    3, 5, 12, 6, 10, 7];

n = length(X);
printf("%d\n", n);

% a)

%the null hypothesis
%H0:mu = 8.5 (mu > 8.5)
%H1 - the alternative hypothesis
% H1: mu < 8.5 - standard is not met

%left tailed test for mu when sigma is known

printf("left-tailed test for mu when sigma is known\n");

sigma = 5;
0.7
mu0= 8.5;
[h,p,ci,z] = ztest(X, mu0,sigma,"alpha", alpha, "tail", "left");
%h- 1 if H0 is rejected 0 otherwise
%p -the P-value of the test, the probability of observing a test statistic as extreme as
% or more extreme than the observed value under the null hypothesis
% ci - the confidence interval for the ratio of population variances
% z - the value of the test statistic


%for each statisical test we build the rejection region

zalpha = norminv(alpha,0,1); %quantile for the rejection region

RR = [-inf zalpha]; %rejection region for the left-tailed test

printf("The value of h is %d\n",h);

if h == 1 % h = 0, h0 is not rejected, if h = 1, h0 is rejected
  printf("The null hypothesis is rejected\n");
  printf("The data suggests that the standard is not met\n");

  else
  printf("The null hypothesis is not rejected\n");
  printf("The data suggests that the standard is met\n");

endif

printf("The rejection region is (%4.3f, %4.3f).\n",RR);

printf("The value of the test statistic is %4.3f. \n", z);

printf("The P-value of the test is %4.3f. \n", p);


%b
%the null hypothesis is H0: populastion mean (miu) = 5.5
%the alternative hypothesis is H1: population mean (miu) > 5.5
%We will do a right-tailed test (we don't know sigma but we have a large sample)

m0 = 5.5;
[h, p, ci, stats] = ttest(X, m0, "alpha", alpha, "tail", "right");
%h - 1 if H0 is rejected, 0 if H0 is not rejected
% p - the P-value of the test, the probability of observing a test statistic as extre as or more extreme than the observed value under the null hypothesis
% ci - the confidence interval for the ratio of population variances
% stats - a structure containing
%         - tstat - the value of the test statistic,
%         - df - degrees of freedom for the test
%         - sd - estimated population standard deviation

rejection_region = [ norminv(1- alpha,0,1), inf];

  if h == 1
    printf("The null hypothesies is rejected\n");
    printf("The data suggests that on average the number of files stored exceeds 5.5\n");

 else
     printf("The null hypothesies is not rejected\n");
    printf("The data suggests that on average the number of files stored does not exceed 5.5\n");
  endif

printf("The rejection region is (%4.3f, %4.3f).\n",rejection_region);

printf("The value of the test statistic is %4.3f. \n", stats.tstat);

printf("The P-value of the test is %4.3f. \n", p);


