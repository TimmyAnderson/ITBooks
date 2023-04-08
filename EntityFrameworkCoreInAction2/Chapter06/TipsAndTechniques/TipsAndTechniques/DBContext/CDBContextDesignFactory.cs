using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Design;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace TipsAndTechniques
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! CLASS reprezentuje DESIGN TIME DB CONTEXT FACTORY CLASS pre DB CONTEXT CLASS 'CDBContext'.
	public sealed class CDBContextDesignFactory : IDesignTimeDbContextFactory<CDBContext>
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD je volana TOOL [dotnet ef] vzdy, ked tento TOOL potrebuje vytvorit instanciu DB CONTEXT CLASS.
		// !!!!! COMMAND LINE PARAMETERS zadane v TOOL [dotnet ef] su prenesene do METHOD prostrednictvom PARAMETER.
		// !!!!! COMMAND LINE PARAMETERS sa zadavaju na konci COMMAND pomocou SYNTAX [-- "PARAMETER 1" "PARAMETER 2" ... "PARAMETER N"]. Priklad [dotnet ef migrations add MIGRATION --context CDBContext -- "MY_PARAMETER 1" "MY_PARAMETER 2"].
		public CDBContext CreateDbContext(string[] Args)
		{
			CConsoleHelpers.WriteLine($"NUMBER of PARAMETERS [{Args.Length}] !",ConsoleColor.Red);

			foreach(string Arg in Args)
			{
				CConsoleHelpers.WriteLine($"PARAMETER [{Arg}] !",ConsoleColor.Red);
			}

			// !!! Vytvori sa instancia DB CONTEXT CLASS.
			CDBContext											DBContext=new CDBContext();
			
			return(DBContext);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------