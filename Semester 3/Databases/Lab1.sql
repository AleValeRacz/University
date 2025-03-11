use PetShopDB

create table Suppliers(
supplierID int  primary key identity(1,1),
name varchar(50),
typeSupply varchar(50))


CREATE table Animals(  
	animalID int primary key identity(1,1),
	species varchar(50),
	supplierID int,
	name varchar(50),
	age float,
	sex varchar(10),
	foreign key(supplierID) references Suppliers(supplierID))


create table Accessories(
accessoryID int primary key identity(1,1),
name varchar(50) ,
price float,
check(price >0),
supplierID int,
foreign key(supplierID) references Suppliers(supplierID))

create table Food(
foodID int primary key identity(1,1),
name varchar(50),
brand varchar(50),
supplierID int,
foreign key(supplierID) references Suppliers(supplierID))


create table  HealthCareRecords(
recordID int primary key identity(1,1),
animalID int,
foreign key(animalID) references Animals(animalID)
on delete cascade,
type varchar(50),
date date)

create table Clients(
clientID int  primary key identity(1,1),
name varchar(50),
phoneNumber varchar(12),
fidelityCard bit)



create table FeedingRequirements(
animalID int,
foreign key (animalID) references Animals(animalID),
foodID int,
foreign key(foodID) references Food(foodID),
primary key(animalID, foodID),
timesPerDay int not null)

create table Employees(
employeeID int primary key identity(1,1),
name varchar(50),
phoneNumber varchar(12),
salary float,
age int,
check (age >= 16),
qualifications varchar(200))

create table Adoptions(
clientID int,
animalID int,
foreign key(clientID) references Clients(clientID) on delete cascade,
foreign key(animalID) references Animals(animalID) on delete cascade,
primary key(animalID,clientID),
date date)

create table Sales(
clientID int,
employeeID int,
accessoryID int,
foreign key(clientID) references Clients(clientID),
foreign key (employeeID) references Employees(employeeID),
foreign key (accessoryID) references Accessories(accessoryID),
primary key(clientID,employeeID,accessoryID),
sum float,
check(sum > 0),
date date)

create table Shifts(
shiftID int primary key identity(1,1),
day varchar(50),
startingTime time,
endingTime time,
)

create table Schedule(
employeeID int,
shiftID int,
foreign key (employeeID) references Employees(employeeID) on delete cascade,
foreign key(shiftID) references Shifts(shiftID),
primary key(employeeID, shiftID),
date date)

/*
drop table Shifts
drop table Sales
drop table Adoptions
drop table Employees
drop table FeedingRequirements
drop table Clients
drop table HealthCareRecords
drop table Food
drop table Accessories
drop table Animals
drop table Suppliers
*/





