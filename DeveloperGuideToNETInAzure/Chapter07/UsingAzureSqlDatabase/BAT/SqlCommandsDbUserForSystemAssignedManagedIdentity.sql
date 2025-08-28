CREATE USER [MyWebProgram] FROM EXTERNAL PROVIDER;

ALTER ROLE db_datareader ADD MEMBER [MyWebProgram;
ALTER ROLE db_datawriter ADD MEMBER [MyWebProgram];

// !!!!! Je to nutne iba kvoli MIGRATIONS.
ALTER ROLE db_dbowner ADD MEMBER [MyWebProgram];