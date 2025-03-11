use PetShopDB

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Tables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRunTables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRunViews]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRuns]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestTables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestViews]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Tests]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Views]

GO



CREATE TABLE [Tables] (

	[TableID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRunTables] (

	[TestRunID] [int] NOT NULL ,

	[TableID] [int] NOT NULL ,

	[StartAt] [datetime] NOT NULL ,

	[EndAt] [datetime] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRunViews] (

	[TestRunID] [int] NOT NULL ,

	[ViewID] [int] NOT NULL ,

	[StartAt] [datetime] NOT NULL ,

	[EndAt] [datetime] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRuns] (

	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,

	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,

	[StartAt] [datetime] NULL ,

	[EndAt] [datetime] NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestTables] (

	[TestID] [int] NOT NULL ,

	[TableID] [int] NOT NULL ,

	[NoOfRows] [int] NOT NULL ,

	[Position] [int] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestViews] (

	[TestID] [int] NOT NULL ,

	[ViewID] [int] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [Tests] (

	[TestID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [Views] (

	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



ALTER TABLE [Tables] WITH NOCHECK ADD 

	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED 

	(

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunTables] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID],

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunViews] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID],

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRuns] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestTables] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED 

	(

		[TestID],

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestViews] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED 

	(

		[TestID],

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [Tests] WITH NOCHECK ADD 

	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED 

	(

		[TestID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [Views] WITH NOCHECK ADD 

	CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED 

	(

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunTables] ADD 

	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY 

	(

		[TableID]

	) REFERENCES [Tables] (

		[TableID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY 

	(

		[TestRunID]

	) REFERENCES [TestRuns] (

		[TestRunID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestRunViews] ADD 

	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY 

	(

		[TestRunID]

	) REFERENCES [TestRuns] (

		[TestRunID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY 

	(

		[ViewID]

	) REFERENCES [Views] (

		[ViewID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestTables] ADD 

	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY 

	(

		[TableID]

	) REFERENCES [Tables] (

		[TableID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY 

	(

		[TestID]

	) REFERENCES [Tests] (

		[TestID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestViews] ADD 

	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY 

	(

		[TestID]

	) REFERENCES [Tests] (

		[TestID]

	),

	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY 

	(

		[ViewID]

	) REFERENCES [Views] (

		[ViewID]

	)

GO


create or alter procedure addToTables (@tableName varchar(50)) as
    if @tableName in (select Name from Tables) begin
        print 'Table already present in Tables'
        return
    end
    if @tableName not in (select TABLE_NAME from INFORMATION_SCHEMA.TABLES) begin
        print 'Table not present in the database'
        return
    end
    insert into Tables (Name) values (@tableName)
GO

create or alter procedure addToViews (@viewName varchar(50)) as
    if @viewName in (select Name from Views) begin
        print 'There is already a view with this name'
        return
    end
    if @viewName not in (select TABLE_NAME from INFORMATION_SCHEMA.VIEWS) begin
        print 'View not present in the database'
        return
    end
    insert into Views (Name) values (@viewName)
GO

create or alter procedure addToTests (@testName varchar(50)) as
    if @testName in (select Name from Tests) begin
        print 'Test already present in Tests'
        return
    end
    insert into Tests (Name) values (@testName)
GO

create or alter procedure addToTestTables (@tableName varchar(50), @testName varchar(50), @rows int, @pos int) as
    if @tableName not in (select Name from Tables) begin
        print 'Table not present in Tables'
        return
    end
    if @testName not in (select Name from Tests) begin
        print 'Tests not present in Tests'
        return
    end
    if exists(
        select *
        from TestTables T1 join Tests T2 on T1.TestID = T2.TestID
        where T2.Name=@testName and Position=@pos
        ) begin
        print 'Incorect position'
        return
    end
    insert into TestTables (TestID, TableID, NoOfRows, Position) values (
        (select Tests.TestID from Tests where Name=@testName),
        (select Tables.TableID from Tables where Name=@tableName),
        @rows, @pos)
GO

create or alter procedure addToTestViews (@viewName varchar(50), @testName varchar(50)) as
    if @viewName not in (select Name from Views) begin
        print 'View not present in Views'
        return
    end
    if @testName not in (select Name from Tests) begin
        print 'Tests not present in Tests'
        return
    end
    insert into TestViews (TestID, ViewID) values (
        (select Tests.TestID from Tests where Name=@testName),
        (select Views.ViewID from Views where Name=@viewName)
    )
GO




 create or alter proc runTest (@testName varchar(50))
as
begin

    if not exists (select 1 from Tests where Name = @testName)
    begin
        print 'Test not found in Tests table';
        return;
    end

    declare @testId int;
    declare @testRunId int;
    declare @testStartTime datetime2;
    declare @table varchar(50);
    declare @rows int;
    declare @pos int;
    declare @view varchar(50);
    declare @command varchar(100);
    declare @startTime datetime2;
    declare @endTime datetime2;
    

    select @testId = TestID from Tests where Name = @testName;

    select @testRunId = ISNULL(MAX(TestRunID), 0) + 1 from TestRuns;
    
    set @testStartTime = SYSDATETIME();
    
    set identity_insert TestRuns on;
    insert into TestRuns (TestRunID, Description, StartAt)
    values (@testRunId, 'Test results for: ' + @testName, @testStartTime);
    set identity_insert TestRuns off;


    declare @tablesToDelete table (TableName VARCHAR(50), Position INT);
    
    insert into @tablesToDelete (TableName, Position)
    select T.Name, TT.Position
    from Tables T
    join TestTables TT on T.TableID = TT.TableID
    where TT.TestID = @testId
    order by TT.Position desc;

    while exists (select 1 FROM @tablesToDelete)
    begin
        select top 1 @table = TableName from @tablesToDelete;
        exec ('DELETE FROM ' + @table);
        delete from @tablesToDelete where TableName = @table;
    end


    declare @tablesToInsert table (TableName varchar(50), NoOfRows int, Position int);
    
    insert into @tablesToInsert (TableName, NoOfRows, Position)
    select T.Name, TT.NoOfRows, TT.Position
    from Tables T
    join TestTables TT on T.TableID = TT.TableID
    where TT.TestID = @testId
    order by TT.Position;


    while exists (select 1 from @tablesToInsert)
    begin
        select top 1 @table = TableName, @rows = NoOfRows from @tablesToInsert;
        set @command = 'populate' + @table;
        if not exists (select ROUTINE_NAME from INFORMATION_SCHEMA.ROUTINES where ROUTINE_NAME = @command)
        begin
            print @command + ' does not exist';
            return;
        end
        set @startTime = SYSDATETIME();
        exec @command @rows;
        set @endTime = SYSDATETIME();
        
        insert into TestRunTables (TestRunID, TableId, StartAt, EndAt)
        values (@testRunId, (select TableID from Tables where Name = @table), @startTime, @endTime);

        delete from @tablesToInsert where TableName = @table;
    end

    declare @viewsToEvaluate table (ViewName varchar(50));

    insert into @viewsToEvaluate (ViewName)
    select V.Name
    from Views V
    join TestViews TV on V.ViewID = TV.ViewID
    where TV.TestID = @testId;

    while EXISTS (select 1 from @viewsToEvaluate)
    begin
        select top 1 @view = ViewName from @viewsToEvaluate;
        set @command = 'SELECT * FROM ' + @view;
        set @startTime = SYSDATETIME();
        exec (@command);
        Set @endTime = SYSDATETIME();
        
        insert into TestRunViews (TestRunID, ViewID, StartAt, EndAt)
        values (@testRunId, (select ViewID from Views where Name = @view), @startTime, @endTime);

        delete from @viewsToEvaluate where ViewName = @view;
    end

    update TestRuns
    set EndAt = SYSDATETIME()
    where TestRunID = @testRunId;
end
go

create or alter proc populateShifts(@rows int) as
   begin
        declare @i int = 1
        while @i <= @rows
        begin
            insert into Shifts (day, startingTime, endingTime)
            values (concat('day ',@i), '10:00:00','18:00:00')
            set @i = @i + 1
        end
    end
go

create or alter proc populateEmployees(@rows int) as
  begin
        declare @i INT = 1
        WHILE @i <= @Rows
        begin
            insert into Employees (name, phoneNumber, salary, age, qualifications)
            values (concat('Employee_', @i),'07563578',4500,20,'responsible, gentle, serious')
            set @i = @i + 1
        end
    end
go

create table Medicine( 
medicineID int primary key identity(1,1),
name varchar(50),
brand varchar(50),
type varchar(50))
go

create or alter PROC populateSchedule(@rows int) as
   begin
        declare @i int = 1
		declare @j int
		declare @k int
		set @j = (select min(employeeID) from Employees)
		set @k = (select min(shiftID) from Shifts)
        while @i <= @Rows
        begin
			
            insert into Schedule (employeeID, shiftID, date)
            values (@j,@k, DATEADD(DAY, @i, GETDATE()))
            set @i = @i + 1
			set @j = @j + 1
			set @k = @k + 1
        end
    end
go


create or alter PROC populateMedicine(@rows int) as
   begin
        declare @i int = 1
        while @i <= @Rows
        begin
            insert into Medicine (name, brand, type)
            values (concat('name_',@i),'some brand','pain killers')
            set @i = @i + 1

        end
    end
go

CREATE or alter PROC populateSuppliers(@rows int) as
   BEGIN
        DECLARE @i INT = 1
        WHILE @i <= @Rows
        BEGIN
            INSERT INTO Suppliers (name, typeSupply)
            VALUES (concat('name_',@i),'food')
            SET @i = @i + 1

        END
    END
go

CREATE or alter PROC populateFood(@rows int) as
   BEGIN
        DECLARE @i INT = 1
		declare @j int
		set @j = (select min(supplierID) from Suppliers)
        WHILE @i <= @Rows
        BEGIN
			
            INSERT INTO Food (name, brand, supplierID)
            VALUES (concat('name ', @i), 'generic brand', @j)
            SET @i = @i + 1
			SET @j = @j + 1
        END
    END
go

create or alter VIEW MedicineView AS
SELECT medicineID, name, brand, type
FROM Medicine
go

CREATE or alter VIEW EmployeeScheduleView AS
SELECT 
    e.employeeID,
    e.name,
    s.shiftID,
    s.date,
    sh.day,
    sh.startingTime,
    sh.endingTime
FROM 
    Employees e
    INNER JOIN Schedule s ON e.employeeID = s.employeeID
    INNER JOIN Shifts sh ON s.shiftID = sh.shiftID;

go

CREATE or alter VIEW FoodSuppliersView AS
SELECT 
    s.supplierID,
	s.name as supplierName,
    f.name as foodName
FROM 
    Suppliers s
    INNER JOIN Food f ON s.supplierID = f.supplierID
GROUP BY 
    s.supplierID , s.name, f.name
go

---Test 1
exec addToTables 'Medicine'
exec addToViews 'MedicineView'
exec addToTests 'Test1'
exec addToTestTables 'Medicine', 'Test1', 100, 1
exec addToTestViews 'MedicineView', 'Test1'
exec runTest 'Test1'
go

--Test 2
exec addToTables 'Suppliers'
exec addToTables 'Food'
exec addToViews 'FoodSuppliersView'
exec addToTests 'Test2'
exec addToTestTables 'Suppliers', 'Test2',100,2
exec addToTestTables 'Food', 'Test2',100,3
exec addToTestViews'FoodSuppliersView', 'Test2'
exec runTest 'Test2'
go 

--Test 3
exec addToTables 'Employees'
exec addToTables 'Shifts'
exec addToTables 'Schedule'
exec addToViews 'EmployeeScheduleView'
exec addToTests 'Test3'
exec addToTestTables 'Schedule', 'Test3',100, 4
exec addToTestTables 'Shifts', 'Test3', 100, 5
exec addToTestTables 'Employees', 'Test3',100,6
exec addToTestViews'EmployeeScheduleView', 'Test3'
exec runTest 'Test3'
go



select * from Employees
select * from Schedule
select * from Shifts
select * from Volunteers


delete from TestRunViews
delete from TestRunTables
delete from TestRuns
delete from TestViews
delete from Views
delete from TestTables
delete from Tables
delete from Tests

select * from Tests
select * from Views
select * from Tables
select * from TestTables
select * from TestViews


select * from TestRuns
select * from TestRunTables
select * from TestRunViews

delete from Medicine
delete from Employees
delete from Food
delete from Suppliers
delete from Schedule 
delete from Shifts

DBCC CHECKIDENT ('Employees', RESEED, 0);
DBCC CHECKIDENT ('Suppliers', RESEED, 0);
DBCC CHECKIDENT ('Medicine', RESEED, 0);
DBCC CHECKIDENT ('Food', RESEED, 0);
DBCC CHECKIDENT ('Shifts', RESEED, 0);






 