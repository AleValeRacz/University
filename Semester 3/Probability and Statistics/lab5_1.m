
% A. Correlation and regression
% frequency distribution of X and Y are

X = [20 20 21 22 22 22 23 23 23 23 23 23 24 24 24 24 24 25 25 25 25 25 25 25 25 26 26 27 27]
% 20 21 22 23 24 25 26 27
% 2 1 3 6 5 9 2 2

Y = [75 75 75 76 76 77 77 78 78 78 78 78 79 79 79 79 79 79 79 79 80 80 80 80 80 80 80 80 81 82]
% 75 76 77 78 79 80 81 82
% 3  2  2  5  8  8  1  1


% a. find the means of X and Y

meanX = mean(X);
meanY = mean(Y);

fprintf("The mean of X = %3.4f \n",meanX);
fprintf("The mean of Y = %3.4f \n",meanY);

%b. the variances sigma^2_X and sigma^2_Y

varX = var(X);
varY = var(Y);

fprintf("The variance of X = %3.4f \n",varX);
fprintf("The variance of Y = %3.4f \n",varY);

%c. the covariance cov(X,Y)

fprintf("The covariance of X and Y: ");
covXY = cov(X,Y)
fprintf("\n");

%d. the correlation coefficient ro_{XY}
% corcoeff(x,y) = cov(x,y)/sqrt(varx*vary)

fprintf("The correlation coefficient of X and Y is: ");
correlation_coefficient = corrcoef(X,Y)













