rem DATABASE musi byt vytvorena v CURRENT DIRECTORY.
dotnet ef dbcontext scaffold "Data Source=MyDatabase.db" Microsoft.EntityFrameworkCore.Sqlite --output-dir ScaffoldedDBContext