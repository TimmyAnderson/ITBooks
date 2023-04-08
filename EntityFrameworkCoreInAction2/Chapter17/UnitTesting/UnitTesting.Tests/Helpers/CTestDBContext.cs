using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Data.Sqlite;
using Microsoft.EntityFrameworkCore;
using UnitTesting;
//----------------------------------------------------------------------------------------------------------------------
namespace UnitTesting.Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CTestDBContext : CDBContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly SqliteConnection						MConnection;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Instancia CLASS [SqliteConnection] moze byt SHARED medzi viacerymi DB CONTEXT. V takom pripade sa vsetky DB CONTEXTS pripajaju k TEJ ISTEJ IN MEMORY DATABASE.
		public CTestDBContext(SqliteConnection Connection)
		{
			MConnection=Connection;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnConfiguring(DbContextOptionsBuilder OptionsBuilder)
		{
			if (OptionsBuilder.IsConfigured==false)
			{
				// !!!! Pri IN MEMORY [Sqlite] DATABASE je treba pouzit ako PARAMETER instanciu CLASS [SqliteConnection].
				OptionsBuilder.UseSqlite(MConnection);
			}
		}		
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------