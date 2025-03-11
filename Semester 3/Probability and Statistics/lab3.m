pkg load statistics

%1 a) with normal distribution

printf("Normal\n")
miu = input("Give value for miu: \n");

sigma = input("Give value for sigma: \n");

alpha = input("Give value for alpha: \n");

beta = input("Give value for beta: \n");


p1 = normcdf(0,miu,sigma);
printf("P(x <=0) = %1.6f \n",p1);

p2 = 1 - p1;
printf("P(x >=0) = %1.6f \n",p2);
%1 b) normal distribution

p3 = normcdf(1,miu,sigma);
p4 = normcdf(-1,miu, sigma);

printf("P(-1<=x<=1)= %1.6f \n", p3 - p4);

printf("x <= -1 or x >= 1)= %1.6f \n", 1 -(p3-p4));

%1 c) normal distribution

p5 = norminv(alpha,miu, sigma);
printf("For P(x < Xaplha) =P(X<= Xaplha) = alpha, Xalpha is: %1.6f \n", p5);

%1 d) normal

p6 = norminv(1- beta, miu, sigma);
printf("For P(x > Xbeta) =P(X >= Xbeta) = beta, Xbeta is: %1.6f \n", p6);



%1 a) with student
printf("Student\n")
n = input("Give value for n: \n");
alpha = input("Give value for alpha: \n");
beta = input("Give value for beta: \n");


p7 = tcdf(0,n);
printf("P(x <=0) = %1.6f \n",p7);

p8 = 1 - p7;
printf("P(x >=0) = %1.6f \n",p8);
%1 b)

p9 = tcdf(1,n);
p10 = tcdf(-1,n);

printf("P(-1<=x<=1)= %1.6f \n", p9 - p10);

printf("x <= -1 or x >= 1)= %1.6f \n", 1 -(p9 - p10));

%1 c)

p11 = tinv(alpha,n);
printf("For P(x < Xaplha) =P(X<= Xaplha) = alpha, Xalpha is: %1.6f \n", p11);

%1 d)
p12 = tinv(1- beta,n);
printf("For P(x > Xbeta) =P(X >= Xbeta) = beta, Xbeta is: %1.6f \n", p12);


%1 a) with chi squared
printf("Chi squared\n")
n = input("Give value for n: \n");
alpha = input("Give value for alpha: \n");
beta = input("Give value for beta: \n");


p7 = chi2cdf(0,n);
printf("P(x <=0) = %1.6f \n",p7);

p8 = 1 - p7;
printf("P(x >=0) = %1.6f \n",p8);
%1 b)

p9 = chi2cdf(1,n);
p10 = chi2cdf(-1,n);

printf("P(-1<=x<=1)= %1.6f \n", p9 - p10);

printf("x <= -1 or x >= 1)= %1.6f \n", 1 -(p9 - p10));

%1 c)

p11 = chi2inv(alpha,n);
printf("For P(x < Xaplha) =P(X<= Xaplha) = alpha, Xalpha is: %1.6f \n", p11);

%1 d)
p12 = chi2inv(1- beta,n);
printf("For P(x > Xbeta) =P(X >= Xbeta) = beta, Xbeta is: %1.6f \n", p12);


% with fisher
printf("Fisher\n");
n = input("Give value for n: \n");
m = input("Give value for m: \n");
alpha = input("Give value for alpha: \n");
beta = input("Give value for beta: \n");


p7 = fcdf(0,n,m);
printf("P(x <=0) = %1.6f \n",p7);

p8 = 1 - p7;
printf("P(x >=0) = %1.6f \n",p8);
%1 b)

p9 = fcdf(1,n,m);
p10 = fcdf(-1,n,m);

printf("P(-1<=x<=1)= %1.6f \n", p9 - p10);

printf("x <= -1 or x >= 1)= %1.6f \n", 1 -(p9 - p10));

%1 c)

p11 = finv(alpha,n,m);
printf("For P(x < Xaplha) =P(X<= Xaplha) = alpha, Xalpha is: %1.6f \n", p11);

%1 d)
p12 = finv(1- beta,n,m);
printf("For P(x > Xbeta) =P(X >= Xbeta) = beta, Xbeta is: %1.6f \n", p12);


n = input("Enter value for n: \n");
p = input("Enter value for p: \n");

x  = 0:n;
px = binopdf(x,n,p);
clf;
plot(x,b,'b*');
hold on;
lamda = n * p;
poiss = poisspdf(x,lambda);
plot(x,poiss, '--');
legend('bino','poison');
