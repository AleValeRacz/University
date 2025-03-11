use PetShopDB

go 
Create or alter proc ChangeFidelityCardType 
as
begin
alter table Clients 
alter column fidelityCard int 
end

go
execute ChangeFidelityCardType
go


Create or alter proc UndoChangeFidelityCardType 
as
begin
alter table Clients 
alter column fidelityCard bit
end

go
execute UndoChangeFidelityCardType
go

create or alter proc AddColumnAge
as
begin
alter table Clients
add  age int
end

go
execute AddColumnAge
go

create or alter proc RemoveColumnAge
as
begin
alter table Clients
drop column age
end

go
execute RemoveColumnAge
go

create or alter proc AddDefaultConstraintPrice
as
begin
alter table Accessories
add constraint df_0 default 0 for price
end

go
execute AddDefaultConstraintPrice
go


create or alter proc RemoveDefaultConstraintPrice
as
begin
alter table Accessories
drop constraint df_0
end

go
execute RemoveDefaultConstraintPrice
go

create or alter proc dropVolunteers as
begin
drop table Volunteers
end


go
create or alter proc createVolunteers as
begin
create table Volunteers(
volunteerID int identity(1,1),
name varchar(40),
age int,
hours_of_volunteering int,
constraint pk_Volunteer primary key(volunteerID),
supervisorID int constraint fk_Supervisor foreign key(supervisorID) references Employees(employeeID),
phoneNr varchar(12));
end


go
create or alter proc RemovePrimaryKey
as
begin
alter table Volunteers
drop constraint pk_Volunteer
end

go
execute RemovePrimaryKey
go


create or alter proc AddPrimaryKey
as
begin
alter table Volunteers
add constraint pk_Volunteer primary key(VolunteerID)
end

go
execute AddPrimaryKey
go


create or alter proc AddCandidateKey
as
begin
alter table Volunteers
add constraint uk_Volunteer Unique(phoneNr)
end

go
execute AddCandidateKey
go

create or alter proc RemoveCandidateKey
as
begin
alter table Volunteers
drop constraint uk_Volunteer 
end

go
execute RemoveCandidateKey
go

create or alter proc RemoveForeignKey
as
begin
alter table Volunteers
drop constraint fk_Supervisor
end

go
execute RemoveForeignKey
go

create or alter proc AddForeignKey
as
begin
alter table Volunteers
add constraint fk_Supervisor foreign key(SupervisorID) references Clients(clientID)
end

go
execute AddForeignKey
go


create or alter procedure createTables 
as
begin
create table VersionTable(version int primary key)
insert into  VersionTable (version) values(0)
end

go
execute createTables
go

create or alter procedure dropTables
as
begin
drop table VersionTable;
drop table ProceduresTable;
end
go
execute dropTables
go

create table ProceduresTable(
oldVersion int,
newVersion int,
name varchar(100),
primary key (oldVersion,newVersion));

select * from ProceduresTable
insert into ProceduresTable(oldVersion,newVersion,name) values
(0,1,'ChangeFidelityCardType'),
(1,2,'AddColumnAge'),
(2,3,'AddDefaultConstraintPrice'),
(3,4,'createVolunteers'),
(4,5,'RemovePrimaryKey'),
(5,6,'AddCandidateKey'),
(6,7,'RemoveForeignKey'),
(7,6,'AddForeignKey'),
(6,5,'RemoveCandidateKey'),
(5,4,'AddPrimaryKey'),
(4,3,'dropVolunteers'),
(3,2,'RemoveDefaultConstraintPrice'),
(2,1,'RemoveColumnAge'),
(1,0,'UndoChangeFidelityCardType')

go
create or alter procedure main(@newVersion int) as
begin
	declare @currentVersion int;
	declare @procName varchar(100);



	if @newVersion < 0 or @newVersion > 7
		begin
			raiserror('Invalid version',16,1);
			return
		end;

	select @currentVersion=vt.version
	from VersionTable vt

	while @currentVersion < @newVersion begin
		select @procName=name 
		from ProceduresTable
		where oldVersion=@currentVersion and newVersion=@currentVersion +1;
		
		exec(@procName);

		set @currentVersion = @currentVersion+1;
		update VersionTable set version = @currentVersion;
	end;

	while @currentVersion > @newVersion begin
		select @procName=name 
		from ProceduresTable
		where oldVersion=@currentVersion and newVersion=@currentVersion -1;
		
		exec(@procName);

		set @currentVersion = @currentVersion-1;
		update VersionTable set version = @currentVersion;
	end;

end;

exec main 4;

select * from VersionTable
go







