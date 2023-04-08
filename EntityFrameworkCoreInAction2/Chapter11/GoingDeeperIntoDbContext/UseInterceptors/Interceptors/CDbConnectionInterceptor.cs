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
	public sealed class CDbConnectionInterceptor : IDbConnectionInterceptor
	{
//----------------------------------------------------------------------------------------------------------------------
		public void ConnectionOpened(DbConnection Connection, ConnectionEndEventData EventData)
		{
			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"CONNECTION [{EventData.ConnectionId}] OPENED.",ConsoleColor.DarkRed);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void ConnectionClosed(DbConnection Connection, ConnectionEndEventData EventData)
		{
			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"CONNECTION [{EventData.ConnectionId}] CLOSED.",ConsoleColor.DarkRed);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------