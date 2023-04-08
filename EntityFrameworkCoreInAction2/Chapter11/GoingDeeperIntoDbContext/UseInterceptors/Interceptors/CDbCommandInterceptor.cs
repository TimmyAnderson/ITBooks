using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore.Diagnostics;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UseInterceptors
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDbCommandInterceptor : IDbCommandInterceptor
	{
//----------------------------------------------------------------------------------------------------------------------
		public DbCommand CommandInitialized(CommandEndEventData EventData, DbCommand Result)
		{
			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"COMMAND [{Result.CommandText}] INITIALIZED.",ConsoleColor.DarkMagenta);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void CommandFailed(DbCommand Command, CommandErrorEventData EventData)
		{
			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"COMMAND [{Command.CommandText}] FAILED.",ConsoleColor.DarkMagenta);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------