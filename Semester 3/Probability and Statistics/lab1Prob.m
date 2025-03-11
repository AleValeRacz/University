pkg load statistics


%Plot the graphs of the pdf and the cdf of a random variable X having Binomial distribution of parameters n and p (giveb by the user)

%Binomial distribution ->
%Binomial model - class of problems in statistics, where the solution resembles the binomials
%		- used when there is an expected succes/failure
%		- what is the probability of K successes in N repetitions (N tries)
%


%P(X = k) = (N choose K) * (p ^ K) * ((1-p)  ^ (n-k))

%To type the probability density
%Discrete probability laws = GRAPH OF POINTS
%Continuous probability laws = not necessarily points

%cdf - always a continuous function
%	- cdf is depedent on the values of X
%	- we create the impression of continuity, by lowering the step to a very small one

n=input("Give number of trials n=");
%natural nuber

p=input("Give the probability of success p=");
%p in the interval [0,1]

x=0:n; %nr of succeses in n trials
%number of success, values for the pdf

px = binopdf(x,n,p);

clf;

plot(x,px,'r*');
hold on; %for keeping the previous graph

xx=0:0.01:n;

fx=binocdf(xx,n,p);
plot(xx,fx,'b');
legend('pdf','cdf');



pkg load statistics;

%Coin is tossed 3 times. X- nr of heads that appear
%Application a) The probability distribution function of X. What type of distribution does X have?


%binomial distribution trials = 3, prob
%success p = 0.5, that is Bino(3,0.5);
%its probability distribution function is
%(values)
%(prob) -> those 2 lines form a matrix
%(0 1 2 3)
%(1/8,3/8, 3/8, 1/8)
x = 0:1:3;
px = binopdf(x, 3, 0.5);
printf("Px is %1.4f \n", px);
%the values of the probabilities should add up to 1


% b) find the cumulative distribution function of X, Fx.
xx = 0:0.01:3;
cx = binocdf(xx,3,0.5);

% c)
% P(X=0) = value of the pdf in 0

p1 = binopdf(0,3,0.5);
%P(X <> 0) = 1- P(X = 0)

p2 = 1 - p1;

printf("P(X=0) = %1.6f \n", p1);
printf("P(X<>0) = %1.6f \n", p2);


% d)
%P(x <= 2) = cdf(2)
p3 = binocdf(2, 3,0.5);

%p(x<2)= p(x<= 1)
p4 = binocdf(1,3,0.5);
printf("P(x <=2) = %1.6f \n", p3);
printf("P(X<2) = %1.6f \n", p4);

% e)

%P(x>= 1) = 1 - P(x<1) = 1- P(x <= 0);

p5 = 1 - binocdf(0,3,0.5);
printf("P(X >= 1) = %1.6f \n", p5);

% P(x > 1) = 1 - P(X<=1)
p6 = 1 - binocdf(1,3,0.5);
printf("P(X > 1) = %1.6f \n", p6);

% f)

N= input("Give the number of simulations N=");
U= rand(3,N); %simulates 3 coin tosses N times
Y = (U < 0.5); %Y = 1(heads) if U < 0.5 , Y=O(tails) if U>= 5

X = sum(Y); %X = number of heads in 3 tosses
clf

hist(X) %the shape of the pdf of x

