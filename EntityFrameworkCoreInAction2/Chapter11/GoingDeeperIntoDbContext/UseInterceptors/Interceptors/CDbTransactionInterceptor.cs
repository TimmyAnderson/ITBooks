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
	public sealed class CDbTransactionInterceptor : IDbTransactionInterceptor
	{
//----------------------------------------------------------------------------------------------------------------------
		public DbTransaction TransactionStarted(DbConnection Connection, TransactionEndEventData EventData, DbTransaction Result)
		{
			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"TRANSACTION [{EventData.TransactionId}] STARTED.",ConsoleColor.DarkYellow);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void TransactionCommitted(DbTransaction Transaction, TransactionEndEventData EventData)
		{
			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"TRANSACTION [{EventData.TransactionId}] COMMITED.",ConsoleColor.DarkYellow);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void TransactionRolledBack(DbTransaction Transaction, TransactionEndEventData EventData)
		{
			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"TRANSACTION [{EventData.TransactionId}] ROLLED BACK.",ConsoleColor.DarkYellow);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void TransactionFailed(DbTransaction Transaction, TransactionErrorEventData EventData)
		{
			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"TRANSACTION [{EventData.TransactionId}] FAILED.",ConsoleColor.DarkYellow);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------