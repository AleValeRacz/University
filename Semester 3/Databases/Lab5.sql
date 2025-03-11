create database A5
use  A5

create table Actors(
aid int primary key identity,
name varchar(50),
age int,
cnp int unique,
agent varchar(50))

create table Movies(
mid int primary key identity,
name varchar(50),
year int,
genre varchar(50),
studio varchar(50))




create table ActorsToMovies(
amid int primary key identity,
mid int foreign key references Movies(mid),
pid int foreign key references Actors(aid))

select * from Movies
select * from Actors
select * from ActorsToMovies

insert into Actors(name,age, cnp, agent) values('Alex Pop', 35, 50956, 'Mich') ,('Diana Berry', 19, 61294, 'Bennet') ,('Jesse Pinkman', 25,58933,'Walter'), ('Paris Geller', 23,61969, 'Emily'), ('Amelia Farrow', 41, 53289, 'Peter'), ('Jo March', 39, 61734, 'Amy'), ('Liesel German', 15,64421, 'Max'), ('Anastasia Romanov', 21, 61180,'Burr'), ('Logan Hunserber', 26, 51876, 'Parker'), ('Ben Schrader', 46, 54671, 'Darla')
insert into Movies(name, year, genre, studio) values('Anne of Green Gables', 1987, 'family', 'StudFormidable'), ('Avangers Endgame', 2019, 'action', 'Marvel'), ('Harry Potter and the chamber of secrets', 2002, 'adventure', 'Warner Brothers') ,('Barbie', 2023, 'drama, comedy', 'WB'), ('Oppenheimer', 2023, 'documentary', 'Paramount'), ('Princess Diaries', 1999, 'comedy', 'Disney'), ('Tangled', 2010, 'animation', 'Disney'), ('Attack on Titan', 2023, 'action', 'Mappa'), ('The conjuring', 2012, 'horror', 'Scale'), ('Emma' ,2022, 'drama, comedy', 'WB'), ('Toy Story 3', 1999, 'animation', 'Pixar'),  ('Clueless', 1995, 'romcom', 'Paramount')
insert into ActorsToMovies(mid, pid) values (4,9), (1,5), (3,1), (1,6), (10,10), (12, 6), (6,4), (11,8), (7,9), (12, 6), (10,2), (2,2), (9,10), (5,3), (10,1), (4,9)
--a

--cl index scan
select aid
from Actors
order by aid desc

--cl index seek

select aid 
from Actors
where aid = 5

--ncl index scan
select aid
from Actors

--ncl index seek
select cnp
from Actors
where cnp > 60000

--key lookup
select cnp
from Actors
where cnp = 61294 and age > 18

--b
select *
from Movies m
where year = 2023

create nonclustered index index_b on Movies(year) include (name, genre, studio)
drop index index_b on Movies


go
create or alter view tableView   as
select m.name as MovieName, m.year
from Movies m
inner join ActorsToMovies am on m.mid = am.mid
where m.year = 2023
go

create nonclustered index index_c3 on ActorsToMovies(mid)
drop index index_c3 on ActorsToMovies


select * from tableView