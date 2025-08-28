CREATE TABLE NamesEntities
(
    ID INT PRIMARY KEY IDENTITY(1,1),
    [FirstName] NVARCHAR(MAX),
    [LastName] NVARCHAR(MAX),
    [Age] INT,
    [Sex] INT
)

GO

INSERT INTO [dbo].[NamesEntities] ([FirstName],[LastName],[Age],[Sex]) VALUES ('Timmy','Anderson',12,1), ('Jenny','Thompson',13,2)

GO