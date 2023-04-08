rem !!! Vyrobi DATABASE z MIGRATION_1 a MIGRATION_2, v ktorej su aj ENTITY 'CEntityPrincipal' a ENTITY 'CEntityDependent'.
dotnet ef database update MIGRATION_2 --context CDBContext