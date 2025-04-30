using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Design;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess3SqlServer
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! CLASS reprezentuje DESIGN TIME DB CONTEXT FACTORY CLASS pre DB CONTEXT CLASS 'CDBContext'.
	public sealed class CDBContextDesignFactory : IDesignTimeDbContextFactory<CDBContext>
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQL_SERVER=@"Data Source=(LocalDb)\MSSQLLocalDB;Initial Catalog=DataAccess3SqlServer";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD je volana TOOL [dotnet ef] vzdy, ked tento TOOL potrebuje vytvorit instanciu DB CONTEXT CLASS.
		// !!!!! COMMAND LINE PARAMETERS zadane v TOOL [dotnet ef] su prenesene do METHOD prostrednictvom PARAMETER.
		// !!!!! COMMAND LINE PARAMETERS sa zadavaju na konci COMMAND pomocou SYNTAX [-- "PARAMETER 1" "PARAMETER 2" ... "PARAMETER N"]. Priklad [dotnet ef migrations add MIGRATION --context CDBContext -- "MY_PARAMETER 1" "MY_PARAMETER 2"].
		public CDBContext CreateDbContext(string[] Args)
		{
			Console.WriteLine($"NUMBER of PARAMETERS [{Args.Length}] !");

			foreach(string Arg in Args)
			{
				Console.WriteLine($"PARAMETER [{Arg}] !");
			}

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.EnableDetailedErrors(true);
			OptionsBuilder.EnableSensitiveDataLogging(true);
			OptionsBuilder.UseSqlServer(MConnectionString_SQL_SERVER);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			// !!! Vytvori sa instancia DB CONTEXT CLASS.
			CDBContext											DBContext=new CDBContext(Options);
			
			return(DBContext);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------