using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Design;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingAzureSqlDatabase
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! CLASS reprezentuje DESIGN TIME DB CONTEXT FACTORY CLASS pre DB CONTEXT CLASS 'CDBContext'.
	public sealed class CDBContextDesignFactory : IDesignTimeDbContextFactory<CDBContext>
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									CONNECTION_STRING="Server=tcp:ta76dbserver.database.windows.net,1433;Initial Catalog=MyDatabase;Encrypt=True;TrustServerCertificate=False;Connection Timeout=30;Authentication=Active Directory Default;";
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

			OptionsBuilder.UseSqlServer(CONNECTION_STRING);

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