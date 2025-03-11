select * from Suppliers

use PetShopDB
insert into Suppliers(name,typeSupply) values ('Petco','animals')
insert into Suppliers(name,typeSupply) values ('Carrefour', 'food'), ('AniLove', 'animals'), ('Stylish', 'accessories'), ('Serlad','food'),('Furrtastic','accessories')

select * from Animals
insert into Animals(species, supplierID, name,age,sex) values ('dog',3,'Max',0.5,'male'), ('cat',1,'Lulu',1.6,'female'), ('canary bird',1,'Tweety',3.1,'male'),('cat',3,'Pepe', 5,'male')
insert into Animals(species, supplierID, name,age,sex) values ('fish',16,'sally',0.1,'female')
insert into Animals(species, supplierID,name,age,sex) values ('horse', 1,'Bubbles', 8,'female'), ('axolotl', 1, 'Axel', 0.2, 'female'), ('turtle',3,'Cakey', 1.1,'male'), ('cat', 1, 'Benji', 2,'male') 
select* from Clients
insert into Clients(name,phoneNumber,fidelityCard) values ('Anica Tulbure','0772567001',0), ('Andrei Popescu', '0745646123',1), ('Sara Horea', '0734675198',1),('Iulia S.','0742981700',0)
insert into Clients(name,fidelityCard)  values ('Ana Balta',0)
insert into Clients(name,phoneNumber,fidelityCard) values ('Cosmin Secrier','0774651276',1), ('georgiana_fr','0722672091',0), ('Catalina Ungurean','0771184430',0), ('Vlad Horvat','0752221342',1)

select * from Adoptions
insert into Adoptions(clientID,animalID,date) values (1,2,'2023-05-15'),(4,4,'2019-06-08')
insert into Adoptions(clientID,animalID,date) values (1,3,'2017-25-01')
insert into Adoptions(clientID,animalID,date) values (6,7,'2023-06-02'), (7,9,'2024-04-16'),(8,6,'2022-03-13'),(9,8,'2023-10-27')
Update Clients
set name ='Iulia Szarics'
where clientID=4 and fidelityCard <>1
select* from Clients

Update Animals
set sex='female'
where name like 'L%' or name like '_a%'
select* from Animals

Update Animals
set name='Maxine'
where species='dog' and supplierID in (2,3,4)
select * from Animals

Update Suppliers
set name='Ani.Love' 
where supplierID between 2.1 and 3.5
select *from Suppliers

delete from Clients
where phoneNumber is null
select * from Clients

delete from  Animals
where age <=1 and age >=0.3
select * from Animals

--Q1:  Animals who are older than 2 or are adopted with the id 2 or 7

select * from Adoptions

select A.animalID
from Animals A
where A.age > 2
Union 
select Ad.animalID
from Adoptions Ad
where Ad.animalID in (2,7)

select
