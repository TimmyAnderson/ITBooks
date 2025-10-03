using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Testing1;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject1_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDBOperationsServiceTests : IClassFixture<CTestDatabaseFixture>
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Instancia FIXTURE CLASS je zdielana vsetkymi UNIT TEST METHODS.
		private readonly CTestDatabaseFixture					MFixture;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! TESTING LIBRARY [xUnit] podporuje DEPENDENCY INJECTION.
		public CDBOperationsServiceTests(CTestDatabaseFixture Fixture)
		{
			MFixture=Fixture;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task GetNames()
		{
			// !!! Pomocou FIXTURE CLASS OBJECT sa vytvori DB CONTEXT.
			using(CDBContext DBContext=MFixture.CreateDBContext())
			{
				IDBOperationsService							DBOperationsService=new CDBOperationsService(DBContext);

				CEntityName[]									Names=await DBOperationsService.GetNames();

				Assert.NotNull(Names);

				CEntityName[]									ExpectedNames=new CEntityName[]{new CEntityName(1,"Timmy","Anderson",12,ESex.E_MALE),new CEntityName(2,"Jenny","Thompson",13,ESex.E_FEMALE),new CEntityName(3,"Josh","Hurt",12,ESex.E_MALE),new CEntityName(4,"Lucas","Jones",13,ESex.E_MALE)};

				Assert.Equal(ExpectedNames.Length,Names.Length);

				for(int Index=0;Index<ExpectedNames.Length;Index++)
				{
					CEntityName									Name=Names[Index];
					CEntityName									ExpectedName=ExpectedNames[Index];

					Assert.NotNull(Name);

					Assert.Equal(ExpectedName.ID,Name.ID);
					Assert.Equal(ExpectedName.FirstName,Name.FirstName);
					Assert.Equal(ExpectedName.LastName,Name.LastName);
					Assert.Equal(ExpectedName.Sex,Name.Sex);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Theory]
		[InlineData(1,"Timmy","Anderson",12,ESex.E_MALE)]
		[InlineData(2,"Jenny","Thompson",13,ESex.E_FEMALE)]
		[InlineData(3,"Josh","Hurt",12,ESex.E_MALE)]
		[InlineData(4,"Lucas","Jones",13,ESex.E_MALE)]
		public async Task GetName(int ID, string FirstName, string LastName, int Age, ESex Sex)
		{
			// !!! Pomocou FIXTURE CLASS OBJECT sa vytvori DB CONTEXT.
			using(CDBContext DBContext=MFixture.CreateDBContext())
			{
				IDBOperationsService							DBOperationsService=new CDBOperationsService(DBContext);

				CEntityName										Name=await DBOperationsService.GetName(ID);

				Assert.NotNull(Name);

				CEntityName										ExpectedName=new CEntityName(ID,FirstName,LastName,Age,Sex);

				Assert.Equal(ExpectedName.ID,Name.ID);
				Assert.Equal(ExpectedName.FirstName,Name.FirstName);
				Assert.Equal(ExpectedName.LastName,Name.LastName);
				Assert.Equal(ExpectedName.Sex,Name.Sex);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------