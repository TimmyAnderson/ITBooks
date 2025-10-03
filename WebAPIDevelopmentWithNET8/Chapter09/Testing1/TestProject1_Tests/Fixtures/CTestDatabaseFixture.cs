using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Testing1;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject1_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje implementaciu implementaciu FIXTURE CLASS.
	public sealed class CTestDatabaseFixture
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pouziva sa REALNA DB, nie IN MEMORY DATABASE.
		private const string									CONNECTION_STRING="Data Source=MyTestDatabase.db";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static readonly object							MLock=new object();
		private static bool										MIsDatabaseInitialized=false;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! DEFAULT CONSTRUCTOR vo FIXTURE CLASS musi THREAD SAFE sposobom vytvorit a inicializovat DATABASE.
		public CTestDatabaseFixture()
		{
			lock(MLock)
			{
				if (MIsDatabaseInitialized==false)
				{
					InitializeDatabase();
					MIsDatabaseInitialized=true;
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CDBContext CreateDBContext()
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(CONNECTION_STRING);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			CDBContext											DBContext=new CDBContext(Options);

			return(DBContext);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void InitializeDatabase()
		{
			using(CDBContext DBContext=CreateDBContext())
			{
				// !!! Povodna TEST DATABASE sa zmaze.
			    DBContext.Database.EnsureDeleted();

				// !!! Vytvori sa nova TEST DATABASE.
				DBContext.Database.EnsureCreated();

				// !!! Vytvoria sa TEST DATA.

				List<CEntityName>								Names=new List<CEntityName>();

				Names.Add(new CEntityName("Josh","Hurt",12,ESex.E_MALE));
				Names.Add(new CEntityName("Lucas","Jones",13,ESex.E_MALE));

				DBContext.AddRange(Names);

				DBContext.SaveChanges();
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------