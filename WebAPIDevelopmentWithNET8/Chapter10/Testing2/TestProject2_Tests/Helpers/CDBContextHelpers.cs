using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Testing2;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject2_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CDBContextHelpers
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void SeedData(CDBContext DBContext, bool AddMigrationSeed)
		{
			List<CEntityName>									Names=new List<CEntityName>();

			if (AddMigrationSeed==true)
			{
				Names.Add(new CEntityName("Timmy","Anderson",12,ESex.E_MALE));
				Names.Add(new CEntityName("Jenny","Thompson",13,ESex.E_FEMALE));
			}

			Names.Add(new CEntityName("Josh","Hurt",12,ESex.E_MALE));
			Names.Add(new CEntityName("Lucas","Jones",13,ESex.E_MALE));

			DBContext.AddRange(Names);

			DBContext.SaveChanges();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void InitializeDatabase(CDBContext DBContext)
		{
			// !!! Vytvori sa DATABASE.
			DBContext.Database.EnsureDeleted();
			DBContext.Database.EnsureCreated();

			SeedData(DBContext,false);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void CleanupDatabase(CDBContext DBContext)
		{
			// !!! Odstrania sa zmeny vykonane v DATABSE.
			DBContext.EntitiesNames.ExecuteDelete();

			// !!! Obnovia sa povodne TEST DATA.
			SeedData(DBContext,true);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------