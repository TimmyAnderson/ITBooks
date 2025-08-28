CREATE USER [MyIdentity] FROM EXTERNAL PROVIDER;

ALTER ROLE db_datareader ADD MEMBER [MyIdentity];
ALTER ROLE db_datawriter ADD MEMBER [MyIdentity];

// !!!!! Je to nutne iba kvoli MIGRATIONS.
ALTER ROLE db_dbowner ADD MEMBER [MyIdentity];