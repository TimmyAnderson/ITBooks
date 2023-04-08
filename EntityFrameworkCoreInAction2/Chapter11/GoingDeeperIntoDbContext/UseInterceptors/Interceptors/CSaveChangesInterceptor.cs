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
	public sealed class CSaveChangesInterceptor : ISaveChangesInterceptor
	{
//----------------------------------------------------------------------------------------------------------------------
		public int SavedChanges(SaveChangesCompletedEventData EventData, int Result)
		{
			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"CONTEXT [{EventData.Context.ContextId}] SAVED CHANGES with RESULT [{Result}].",ConsoleColor.DarkGreen);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void SaveChangesFailed(DbContextErrorEventData EventData)
		{
			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"CONTEXT [{EventData.Context.ContextId}] FAILED to SAVE CHANGES.",ConsoleColor.DarkGreen);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------