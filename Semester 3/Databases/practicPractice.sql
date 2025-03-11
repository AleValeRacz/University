
use BankDB


create table Costumers(
Cid int primary key,
name varchar(50),
dob date
)

create table Accounts(
IBAN varchar(50) primary key,
balance float,
Cid int foreign key references Costumers(Cid),
)

create table Cards(
number int primary key,
CVV int,
IBAN varchar(50) foreign key references Accounts(IBAN)
)

create table ATM(
atmid int primary key,
adress varchar(50))

create table Transactions(
Tid int primary key,
atmid int foreign key references ATM(atmid),
sum float,
cardNr int foreign key references Cards(number),
time datetime)

insert into ATM values (1, 'Al Vlahuta'), (2,'Viteazu'), (3,'Bihihi')
insert into Costumers values(1, 'Cosmin', '2004-07-17'), (2, 'Ale', '2004-01-17'), (3,'Cata', '2005-03-01')
insert into Accounts values ('RO467', 13.6,1) , ('RO57', 101, 2), ('RO818', 5, 2)
insert into Cards values (1, 563, 'RO467'), (2, 567, 'RO818')
insert into Transactions values(6,2,10,2, '2025-01-01 18:11:7'), (4,2,5,1, '2024-11-01 20:11:17'), (5,1,10,1, '2024-12-21 08:12:47')

select * from ATM
select * from Accounts
select * from Cards
select * from Costumers
select * from Transactions

go
create or alter proc DeleteT (@Cnumber int) as
begin
	if exists (select number from Cards where number=@Cnumber)
	begin
		delete from Transactions
		where cardNr = @Cnumber
	end
	else
	begin
		print 'Wrong number!'
		return
	end
end
go
exec DeleteT 5
go
create or alter view  CardNrATM as
	select crd.number 
	from Cards crd
	where crd.number in( 
		select t.cardNr
		from Transactions t
		group by t.cardNr
		having count(distinct t.atmid) = (select count(*) from ATM)
	)
go


select * from CardNrATM
go

create or alter function ListCardsTotalTransactionGreater()
returns table as return
select c.number, c.CVV
from Cards c
where c.number in (
	select t.cardNr
	from Transactions t
	group by t.cardNr
	having sum( t.sum) > 10)
go

select * from ListCardsTotalTransactionGreater()

----------

create database ShoesBD
use ShoesBD

create table Shoes(
Shoeid int primary key,
price float,
mid int foreign key references Models(mid)
)

create table Models(
mid int primary key,
name varchar(50),
season varchar(50)
)

create table Shops(
shopid int primary key,
name varchar(50),
city varchar(50)
)

create table Women(
wid int primary key,
name varchar(50),
max_sum int
)

create table WomenToShoes(
wid int foreign key references Women(wid),
shoeid int foreign key references Shoes(Shoeid),
primary key(wid, shoeid),
quantity_bought int,
spent_amount float
)

create table ShopsToShoes(
shoeid int foreign key references Shoes(Shoeid),
shopid int foreign key references Shops(shopid),
primary key (shoeid, shopid),
quantity int
)


insert into Women values(1, 'Ale', 100), (2, 'Ioana', 200), (3, 'Sara', 56), (4,'Mirela', 459)
insert into Shoes values(1, 45, 2), (2, 30, 1), (3, 100, 2), (4,10, 3)
insert into Models values(1, 'port', 'summer'), (2, 'stiletto', 'spring'), (3, 'boots', 'winter')
insert into  Shops values (1, 'Marelbo', 'Cluj'), (2, 'Daichman', 'Bucuresti'), (3, 'Nike', 'Cluj')
insert into WomenToShoes values (2,1,1,45), (1,4,2,20), (4, 2,2,60), (4,1,1,45)
insert into ShopsToShoes values (1,2, 30), (2,2,40), (3, 1, 50), (4,3,10), (2,3,18),(3,3,100)

select * from Women
select * from Shoes
select * from Models
select * from Shops
select * from WomenToShoes
select * from ShopsToShoes
go

create or alter proc AddShoeToShop(@shoeid int, @shopName varchar(50), @nrShoes int) as
begin
	declare @shopid int;
	set @shopid = (select shopid from Shops where @shopName = name);

	if @shopid is null 
	return

	if exists ( select 1 from  ShopsToShoes where shoeid = @shoeid and shopid = @shopid)
	begin
		print 'Theres already this shoe in this shop!'
		return
	end
	else
		insert into ShopsToShoes values(@shoeid, @shopid, @nrShoes)
end

go
exec AddShoeToShop 2, 'Marelbo', 40
go
create or alter view  VWomen as
select w.wid
from WomenToShoes w
join Shoes s on w.shoeid = s.Shoeid
join Models m on s.mid = m.mid
group by w.wid
having count(w.shoeid) >= 2
go

select * from VWomen
go

create or alter function ListShoes (@T int) 
returns table as return
select ss.shoeid
from ShopsToShoes ss
group by ss.shoeid
having count(*) >= @T
go

select * from ListShoes(2)

use TaxesDB
go

create table TaxCompany(
compid int primary key,
name varchar(50),
nrClients int,
nrSRLs int,
)

create table Clients(
cid int primary key,
number int,
moneyAtDisposal int,
compid int foreign key references TaxCompany(compid)
)

create table Assets(
aid int primary key,
cid int foreign key references Clients(cid),
name varchar(50),
number int,
location varchar(50) ,
srlid int foreign key references  SRLs(srlid)
)

create table SRLs(
srlid int primary key,
cid int foreign key references Clients(cid),
location varchar(50),
name varchar(50),
activity varchar(50)
)
go

create or alter proc NrAssetsAndSRLs(@cid int)
as
begin
  select
	(select sum(a.number)
	from Assets a 
	where a.cid = @cid)  as NrAssets,

	(select count(*)
	from SRLs 
	where cid = @cid) as NRSrls
	
end

go
exec NrAssetsAndSRLs 1


INSERT INTO TaxCompany (compid, name, nrClients, nrSRLs)
VALUES 
(1, 'AlphaTax', 3, 5),
(2, 'BetaTax', 2, 2),
(3, 'GammaTax', 1, 1);


INSERT INTO Clients (cid, number, moneyAtDisposal, compid)
VALUES 
(1, 12345, 5000, 1), -- Client of AlphaTax
(2, 67890, 3000, 1), -- Client of AlphaTax
(3, 11111, 2000, 1), -- Client of AlphaTax
(4, 22222, 4000, 2), -- Client of BetaTax
(5, 33333, 2500, 2), -- Client of BetaTax
(6, 44444, 6000, 3); -- Client of GammaTax


INSERT INTO SRLs (srlid, cid, location, name, activity)
VALUES 
(1, 1, 'New York', 'Tech Solutions', 'IT Services'),    -- Client 12345
(2, 1, 'Chicago', 'BuildPro', 'Construction'),          -- Client 12345
(3, 2, 'Los Angeles', 'Foodie Inc.', 'Restaurant'),     -- Client 67890
(4, 3, 'San Francisco', 'GreenWorld', 'Agriculture'),   -- Client 11111
(5, 4, 'Miami', 'Design Studio', 'Graphic Design'),     -- Client 22222
(6, 4, 'Boston', 'Urban Architects', 'Architecture'),   -- Client 22222
(7, 6, 'Seattle', 'StartUp Hub', 'Business Consulting'); -- Client 44444

INSERT INTO Assets (aid, cid, name, number, location, srlid)
VALUES 
(1, 1, 'Laptops', 10, 'New York', 1),           -- Assets for Tech Solutions
(2, 1, 'Servers', 5, 'New York', 1),            -- Assets for Tech Solutions
(3, 1, 'Construction Equipment', 15, 'Chicago', 2), -- Assets for BuildPro
(4, 2, 'Kitchen Appliances', 8, 'Los Angeles', 3),  -- Assets for Foodie Inc.
(5, 3, 'Farming Tools', 20, 'San Francisco', 4),    -- Assets for GreenWorld
(6, 4, 'Office Furniture', 12, 'Miami', 5),     -- Assets for Design Studio
(7, 4, 'Blueprint Printers', 6, 'Boston', 6);   -- Assets for Urban Architects

go

create or alter view TaxView as
select c.number, c.moneyAtDisposal, s.name, s.activity
from Clients c, Srls s
--inner join SRLs s on s.cid = c.cid
where c.cid = s.cid
go

select * from TaxView


create or alter function  FunctionTax ()
returns table as return
select c.number, s.name as SrlName, s.location as SrlLocation, a.number as NrAssets
from Clients c
left join SRLs s on c.cid = s.cid
left join Assets a on a.srlid = s.srlid
go

select * from FunctionTax()


create table Museum(
mid int primary key,
name varchar(50),
openingYear int,
city varchar(50),
country varchar(50)
)
create table Exhibition(
eid int primary key,
name varchar(50),
description varchar(50),
mid int foreign key references Museum(mid)
)

create table Tour(
tourid int primary key,
name varchar(50),
date datetime,
TourGuide varchar(50),
price float,
mid int foreign key references Museum(mid)
)
create table Tourist(
tid int primary key,
name varchar(50),
surname varchar(50),
gender varchar(50),
age int
)

create table TouristTOTour(
bid int primary key,
tid int foreign key references Tourist(tid),
tourid int foreign key references Tour(tourid),
nrTickets int,
rate int,
)

go
CREATE OR ALTER FUNCTION GetTouristsWithMoreThanMTours (@m INT)
RETURNS TABLE
AS
R ETURN
(
    SELECT t.name, t.surname
    FROM Tourist t
    INNER JOIN TouristTOTour tt ON t.tid = tt.tid
    GROUP BY t.tid, t.name, t.surname
    HAVING COUNT(tt.tourid) > @m
);


    IF NOT EXISTS (SELECT 1 FROM Tour WHERE tourid = @tourid)
    BEGIN
        RAISERROR ('Tour ID %d does not exist.', 16, 1, @tourid);
        RETURN;
    END
go

SELECT *
FROM Tour
WHERE date > GETDATE();

use sem_2024_2025
create table TrainTypes(
	tid int PRIMARY KEY,
	typename varchar(100),
	typedescription varchar(100)
)
create table Trains(
	tid int PRIMARY KEY,
	tname varchar(100),
	ttype int references TrainTypes(tid)
)


create table Stations(
	stationid int PRIMARY KEY,
	stationname varchar(100) unique
)

create table Routes(
	rid int PRIMARY KEY,
	routename varchar(100) unique,
	routetrain int references Trains(tid)
)

create table Program(
	rid int references Routes(rid),
	stationid int references Stations(stationid),
	arrivaltime time,
	departuretime time
)

insert into TrainTypes (tid, typedescription, typename) values
(1, 'very good', 't1'),
(2, 'not so good', 't2'),
(3, 'okay', 't3')

insert into  Trains (tid, tname, ttype) values 
(1, 'Thomas', 1),
(2, 'Gordon', 2),
(3, 'Controlorul rotofei', 1)

insert into Stations (stationid, stationname) values
(1, 'Stei'),
(2, 'Beius'),
(3, 'Baia de aries')
insert into Routes (rid, routename, routetrain) values
(1, 'Linia verde', 2),
(2, 'Spre viitor', 3),
(3, 'Spre trecut', 2),
(4, 'Oraselul lenes', 1)

insert into Program (rid, stationid, arrivaltime, departuretime) values
(2, 3, '07:01pm', '07:11pm'),
(4, 1, '00:19am', '01:00pm'),
(3, 2, '03:07pm', '03:08pm'),
(2, 1, '09:18pm', '09:30pm')

go
create or alter proc USP_AddOrUpdateStationToRoute(@RouteName varchar(100), @StationName varchar(100),
@ArrivalTime time, @Departure time) as
begin
	declare @rid int;
	declare @sid int;
	set @sid = (select stationid from Stations where stationname=@StationName);
	set @rid = (select rid from Routes where routename=@RouteName);
	if @sid is null or @rid is null
	return

	if exists(select * from Program where stationid=@sid and rid=@rid)
	update Program set arrivaltime=@ArrivalTime, departuretime = @Departure 
	where rid=@rid and stationid = @sid;
	else 
	insert into Program(stationid, rid, arrivaltime, departuretime) 
	values (@sid, @rid, @ArrivalTime, @Departure);
end

delete from Program;
select * from Program;
exec USP_AddOrUpdateStationToRoute 'Spre viitor', 'Beius', '22:22', '23:00';
exec USP_AddOrUpdateStationToRoute 'Spre viitor', 'Beius', '22:50', '00:00';

go
create or alter view viewAllStations as
	select R.routename from Routes R
	where R.rid in (
	select P.rid 
	from Program P
	group by P.rid
	having count(*) = (select count(*) from Stations))

go 

select * from viewAllStations

go
create or alter view viewAllStations2 as
	select R.routename 
	from Routes R
	where not exists (
		select S.stationid
		from Stations S
		except 
		select P.stationid
		from Program P
		where P.rid = R.rid
	)

go 
select * from viewAllStations2


go
create or alter function ListNameStations (@R int)
returns table as return 
select S.stationname from Stations S
	where S.stationid in (
	select P.stationid 
	from Program P
	group by P.stationid
	having count(*) > @R)
go
select * from ListNameStations(1)


go
create or alter function ListNameStations2 (@R int)
returns table as return 
	select S.stationname 
	from Stations S
	where @R < (
	select count(*)
	from Program P
	where P.stationid = S.stationid
	)
go

select * from ListNameStations2(1)

	




	
