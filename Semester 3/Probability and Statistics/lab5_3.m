% pkg load statistics;

x1 = [22.4 21.7 24.5 23.4 21.6 23.3 22.4 21.6 24.8 20.0];
x2 = [17.7 14.8 19.6 19.6 12.1 14.8 15.4 12.6 14.0 12.2];

x1bar = mean(x1);
n1 = length(x1);

x2bar = mean(x2);
n2 = length(x2);

oneMinusAlpha = input("Give confidence level from (0, 1): "); % confidence level
alpha = 1-oneMinusAlpha; % significance level

v1 = var(x1);
v2 = var(x2);

% a) conf_int.pdf 3. σ1 = σ2, unknown, done like in lab5_2.m (done at home, idk if it's good)
sp = sqrt(((n1-1)*v1 + (n2-1)*v2)/(n1+n2-2));

m1 = x1bar - x2bar - tinv(1-alpha/2, n1+n2-2)*sp*sqrt(1/n1+1/n2); % student distribution T(n1 + n2 − 2)
m2 = x1bar - x2bar + tinv(1-alpha/2, n1+n2-2)*sp*sqrt(1/n1+1/n2);

printf("Confidence interval for the difference of the population means when we have the standard deviations equal and unknown: (%4.3f;%4.3f)\n", m1, m2)

% b) conf_int.pdf 3. σ1 != σ2, unknown

c = (v1/n1)/(v1/n1+v2/n2);
n = 1/((c^2/(n1-1) + (1-c)^2/(n2-1)));

% compute the limits of the confidence interval
limit1 = x1bar - x2bar - tinv(1-alpha/2, n)*sqrt((v1/n1)+(v2/n2));
limit2 = x1bar - x2bar + tinv(1-alpha/2, n)*sqrt((v1/n1)+(v2/n2));

fprintf('Confidence interval for the difference of the population means when we have the standard deviations UNequal and unknown: (%6.3f;%6.3f)\n', limit1, limit2);



% c) conf_int.pdf 4. (f (finv) for fisher)

ci1 = 1 / finv(1-alpha/2, n1-1, n2-1) * v1 / v2;
ci2 = 1 / finv(alpha/2, n1-1, n2-1) * v1 / v2;
printf("Confidence interval for the ratio of the population variances: (%d, %d)\n", ci1, ci2);





