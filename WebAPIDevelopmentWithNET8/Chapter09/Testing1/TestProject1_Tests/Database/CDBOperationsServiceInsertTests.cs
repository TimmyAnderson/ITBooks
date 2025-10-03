using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Testing1;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject1_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! TEST UNIT CLASS implementuje INTERFACE [IDisposable] na implementaciu DATABASE CLEANUP.
	// !!!!! UNIT TEST METHODS sa v ramci jednej UNIT TEST CLASS vykonavaju SEKVENCNE.
	public sealed class CDBOperationsServiceInsertTests : IClassFixture<CTestDatabaseFixtureCreateDeleteDB>, IDisposable
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Instancia FIXTURE CLASS je zdielana vsetkymi UNIT TEST METHODS.
		private readonly CTestDatabaseFixtureCreateDeleteDB		MFixture;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! TESTING LIBRARY [xUnit] podporuje DEPENDENCY INJECTION.
		public CDBOperationsServiceInsertTests(CTestDatabaseFixtureCreateDeleteDB Fixture)
		{
			Console.WriteLine($"CONSTRUCTOR [{nameof(CDBOperationsServiceInsertTests)}] CALLED.");

			MFixture=Fixture;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Theory]
		[InlineData("Joshua","Foley",13,ESex.E_MALE)]
		[InlineData("Connor","Phills",15,ESex.E_MALE)]
		public async Task InsertName1(string FirstName, string LastName, int Age, ESex Sex)
		{
			Console.WriteLine($"TEST STARTED - FIRST NAME [{FirstName}] LAST NAME [{LastName}] AGE [{Age}] SEX [{Sex}].");

			Thread.Sleep(2000);

			// !!! Pomocou FIXTURE CLASS OBJECT sa vytvori DB CONTEXT.
			using(CDBContext DBContext=MFixture.CreateDBContext())
			{
				IDBOperationsService							DBOperationsService=new CDBOperationsService(DBContext);

				CEntityName										ExpectedName=new CEntityName(FirstName,LastName,Age,Sex);
	
				CEntityName										Name=await DBOperationsService.InsertName(ExpectedName);

				Assert.NotNull(Name);

				Assert.True(Name.ID!=0);
				Assert.Equal(ExpectedName.FirstName,Name.FirstName);
				Assert.Equal(ExpectedName.LastName,Name.LastName);
				Assert.Equal(ExpectedName.Sex,Name.Sex);
			}

			Console.WriteLine($"TEST STOPPED - FIRST NAME [{FirstName}] LAST NAME [{LastName}] AGE [{Age}] SEX [{Sex}].");
		}
//----------------------------------------------------------------------------------------------------------------------
		[Theory]
		[InlineData("Jennifer","Scott",13,ESex.E_FEMALE)]
		[InlineData("River","Leary",13,ESex.E_FEMALE)]
		public async Task InsertName2(string FirstName, string LastName, int Age, ESex Sex)
		{
			Console.WriteLine($"TEST STARTED - FIRST NAME [{FirstName}] LAST NAME [{LastName}] AGE [{Age}] SEX [{Sex}].");

			Thread.Sleep(2000);

			// !!! Pomocou FIXTURE CLASS OBJECT sa vytvori DB CONTEXT.
			using(CDBContext DBContext=MFixture.CreateDBContext())
			{
				IDBOperationsService							DBOperationsService=new CDBOperationsService(DBContext);

				CEntityName										ExpectedName=new CEntityName(FirstName,LastName,Age,Sex);
	
				CEntityName										Name=await DBOperationsService.InsertName(ExpectedName);

				Assert.NotNull(Name);

				Assert.True(Name.ID!=0);
				Assert.Equal(ExpectedName.FirstName,Name.FirstName);
				Assert.Equal(ExpectedName.LastName,Name.LastName);
				Assert.Equal(ExpectedName.Sex,Name.Sex);
			}

			Console.WriteLine($"TEST STOPPED - FIRST NAME [{FirstName}] LAST NAME [{LastName}] AGE [{Age}] SEX [{Sex}].");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			// !!!!! METHOD vymaze zmeny vykonane v DATABASE.
			MFixture.Cleanup();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------