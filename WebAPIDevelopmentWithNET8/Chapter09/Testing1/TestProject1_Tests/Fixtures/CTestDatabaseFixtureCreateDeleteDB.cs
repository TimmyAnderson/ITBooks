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
	public sealed class CTestDatabaseFixtureCreateDeleteDB
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pouziva sa REALNA DB, nie IN MEMORY DATABASE.
		private const string									CONNECTION_STRING="Data Source=MyTestDatabaseCreateDelete.db";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static readonly object							MLock=new object();
		private static bool										MIsDatabaseInitialized=false;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! DEFAULT CONSTRUCTOR vo FIXTURE CLASS musi THREAD SAFE sposobom vytvorit a inicializovat DATABASE.
		public CTestDatabaseFixtureCreateDeleteDB()
		{
			Console.WriteLine($"CONSTRUCTOR [{nameof(CTestDatabaseFixtureCreateDeleteDB)}] CALLED.");

			lock(MLock)
			{
				if (MIsDatabaseInitialized==false)
				{
					// !!! Vytvori sa nova DATABASE.
					using(CDBContext DBContext=CreateDBContext())
					{
						// !!! Povodna TEST DATABASE sa zmaze.
						DBContext.Database.EnsureDeleted();

						// !!! Vytvori sa nova TEST DATABASE.
						DBContext.Database.EnsureCreated();
					}

					// !!! DATABASE sa naplni TEST DATA.
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
		// !!! METHOD naplnit DATABASE TEST DATA.
		public void InitializeDatabase()
		{
			using(CDBContext DBContext=CreateDBContext())
			{
				// !!! Vytvoria sa TEST DATA.

				List<CEntityName>								Names=new List<CEntityName>();

				Names.Add(new CEntityName("Josh","Hurt",12,ESex.E_MALE));
				Names.Add(new CEntityName("Lucas","Jones",13,ESex.E_MALE));

				DBContext.AddRange(Names);

				DBContext.SaveChanges();
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD naplnit DATABASE TEST DATA.
		public void FillDatabase()
		{
			using(CDBContext DBContext=CreateDBContext())
			{
				// !!! Vytvoria sa TEST DATA.

				List<CEntityName>								Names=new List<CEntityName>();

				Names.Add(new CEntityName("Timmy","Anderson",12,ESex.E_MALE));
				Names.Add(new CEntityName("Jenny","Thompson",13,ESex.E_FEMALE));
				Names.Add(new CEntityName("Josh","Hurt",12,ESex.E_MALE));
				Names.Add(new CEntityName("Lucas","Jones",13,ESex.E_MALE));

				DBContext.AddRange(Names);

				DBContext.SaveChanges();
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public void Cleanup()
		{
			// !!!!! V DATABASE sa zmaze obsah vsetkych TABLES, aby sa DATABSE po vykonani UNIT TEST vycistila.
			using(CDBContext DBContext=CreateDBContext())
			{
				DBContext.EntitiesNames.ExecuteDelete();
			}

			// !!! DATABASE sa naplni TEST DATA.
			FillDatabase();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------