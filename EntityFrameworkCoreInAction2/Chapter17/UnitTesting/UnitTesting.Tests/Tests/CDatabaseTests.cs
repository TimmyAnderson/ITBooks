using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Data.Sqlite;
using Microsoft.EntityFrameworkCore;
using Xunit;
using Xunit.Abstractions;
using UnitTesting;
//----------------------------------------------------------------------------------------------------------------------
namespace UnitTesting.Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CDatabaseTests
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! INTERFACE [ITestOutputHelper] umoznuje zapisovat LOGS pocas vykonavania UNIT TESTS.
		private readonly ITestOutputHelper						MTestOutputHelper;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Instancia INTERFACE [ITestOutputHelper] naplni LIBRARY [xUnit] pomocou DEPENDENCY INJECTION.
		public CDatabaseTests(ITestOutputHelper TestOutputHelper)
		{
			MTestOutputHelper=TestOutputHelper;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private string CreateConnectionString()
		{
			SqliteConnectionStringBuilder						ConnectionStringBuilder=new SqliteConnectionStringBuilder();

			ConnectionStringBuilder.DataSource=":memory:";

			string												ConnectionString=ConnectionStringBuilder.ConnectionString;

			return(ConnectionString);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private CDBContext CreateDatabaseContext1(SqliteConnection Connection)
		{
			DbContextOptionsBuilder								OptionsBuilder=new DbContextOptionsBuilder();

			// !!!! Pri IN MEMORY [Sqlite] DATABASE je treba pouzit ako PARAMETER instanciu CLASS [SqliteConnection].
			OptionsBuilder.UseSqlite(Connection);

			CDBContext											Context=new CDBContext(OptionsBuilder.Options);

			return(Context);
		}
//----------------------------------------------------------------------------------------------------------------------
		private CDBContext CreateDatabaseContext2(SqliteConnection Connection)
		{
			CTestDBContext										Context=new CTestDBContext(Connection);

			return(Context);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void FillDatabaseContext(CDBContext Context)
		{
			CTestEntity											TestEntity1=new CTestEntity("AAA");
			CTestEntity											TestEntity2=new CTestEntity("BBB");
			CTestEntity											TestEntity3=new CTestEntity("CCC");
			CTestEntity											TestEntity4=new CTestEntity("DDD");

			Context.TestEntities.Add(TestEntity1);
			Context.TestEntities.Add(TestEntity2);
			Context.TestEntities.Add(TestEntity3);
			Context.TestEntities.Add(TestEntity4);

			Context.SaveChanges();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void TestMethod1UsingCDBContext()
		{
			MTestOutputHelper.WriteLine($"TEST [{nameof(TestMethod1UsingCDBContext)}] STARTED !");

			CTestEntity[]										Result1;
			CTestEntity[]										Result2;
			string												ConnectionString=CreateConnectionString();
			
			// !!!!! Pri IN MEMORY [Sqlite] DATABASE je NUTNE vytvorit CONNECTION, ktora sluzi ako PARAMETER do METHOD [DbContextOptionsBuilder DbContextOptionsBuilder.UseSqlite(DbConnection Connection, Action<SqliteDbContextOptionsBuilder> SqliteOptionsAction)].
			using(SqliteConnection Connection=new SqliteConnection(ConnectionString))
			{
				// !!!!! Pri IN MEMORY [Sqlite] DATABASE CONNECTION MUSI byt OPEN, aby sa vytvorila DATABASE.
				Connection.Open();

				using(CDBContext Context1=CreateDatabaseContext1(Connection))
				{
					// !!! TEST DATABASE sa vytvori volanim METHOD [bool DatabaseFacade.EnsureCreated()].
					Context1.Database.EnsureCreated();

					CCodeToTest										CodeToTest=new CCodeToTest();

					Result1=CodeToTest.Method1(Context1);

					FillDatabaseContext(Context1);

					// !!!!! UNIT TEST by sa VZDY mal vytvarat nad SEPARATNYM DB CONTEXT, ktory je NEZAVISLY od DB CONTEXT, ktory bol pouzity na naplnenie DATABASE.
					// !!!!! Na demonstraciu, ze sa novy CONTEXT pripaja k tej istej instancii IN MEMORY DATABASE sa vytvori novy DB CONTEXT pre tu istu CONNECTION.
					using(CDBContext Context2=CreateDatabaseContext1(Connection))
					{
						Result2=CodeToTest.Method1(Context2);
					}
				}
			}

			Assert.Empty(Result1);
			Assert.Equal(4,Result2.Length);

			Assert.Equal("AAA",Result2[0].Value);
			Assert.Equal("BBB",Result2[1].Value);
			Assert.Equal("CCC",Result2[2].Value);
			Assert.Equal("DDD",Result2[3].Value);

			MTestOutputHelper.WriteLine($"TEST [{nameof(TestMethod1UsingCDBContext)}] FINISHED SUCCESSFULLY !");
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void TestMethod2UsingCDBContext()
		{
			MTestOutputHelper.WriteLine($"TEST [{nameof(TestMethod2UsingCDBContext)}] STARTED !");

			CTestEntity[]										Result1;
			CTestEntity[]										Result2;
			string												ConnectionString=CreateConnectionString();

			// !!!!! Pri IN MEMORY [Sqlite] DATABASE je NUTNE vytvorit CONNECTION, ktora sluzi ako PARAMETER do METHOD [DbContextOptionsBuilder DbContextOptionsBuilder.UseSqlite(DbConnection Connection, Action<SqliteDbContextOptionsBuilder> SqliteOptionsAction)].
			using(SqliteConnection Connection=new SqliteConnection(ConnectionString))
			{
				// !!!!! Pri IN MEMORY [Sqlite] DATABASE CONNECTION MUSI byt OPEN, aby sa vytvorila DATABASE.
				Connection.Open();

				using(CDBContext Context1=CreateDatabaseContext1(Connection))
				{
					// !!! TEST DATABASE sa vytvori volanim METHOD [bool DatabaseFacade.EnsureCreated()].
					Context1.Database.EnsureCreated();

					CCodeToTest										CodeToTest=new CCodeToTest();

					Result1=CodeToTest.Method2(Context1,1,2);

					FillDatabaseContext(Context1);

					// !!!!! UNIT TEST by sa VZDY mal vytvarat nad SEPARATNYM DB CONTEXT, ktory je NEZAVISLY od DB CONTEXT, ktory bol pouzity na naplnenie DATABASE.
					// !!!!! Na demonstraciu, ze sa novy CONTEXT pripaja k tej istej instancii IN MEMORY DATABASE sa vytvori novy DB CONTEXT pre tu istu CONNECTION.
					using(CDBContext Context2=CreateDatabaseContext1(Connection))
					{
						Result2=CodeToTest.Method2(Context2,1,2);
					}
				}
			}

			Assert.Empty(Result1);
			Assert.Equal(2,Result2.Length);

			Assert.Equal("BBB",Result2[0].Value);
			Assert.Equal("CCC",Result2[1].Value);

			MTestOutputHelper.WriteLine($"TEST [{nameof(TestMethod2UsingCDBContext)}] FINISHED SUCCESSFULLY !");
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void TestMethod1UsingCTestDBContext()
		{
			MTestOutputHelper.WriteLine($"TEST [{nameof(TestMethod1UsingCTestDBContext)}] STARTED !");

			CTestEntity[]										Result1;
			CTestEntity[]										Result2;
			string												ConnectionString=CreateConnectionString();

			// !!!!! Pri IN MEMORY [Sqlite] DATABASE je NUTNE vytvorit CONNECTION, ktora sluzi ako PARAMETER do METHOD [DbContextOptionsBuilder DbContextOptionsBuilder.UseSqlite(DbConnection Connection, Action<SqliteDbContextOptionsBuilder> SqliteOptionsAction)].
			using(SqliteConnection Connection=new SqliteConnection(ConnectionString))
			{
				// !!!!! Pri IN MEMORY [Sqlite] DATABASE CONNECTION MUSI byt OPEN, aby sa vytvorila DATABASE.
				Connection.Open();

				using(CDBContext Context1=CreateDatabaseContext2(Connection))
				{
					// !!! TEST DATABASE sa vytvori volanim METHOD [bool DatabaseFacade.EnsureCreated()].
					Context1.Database.EnsureCreated();

					CCodeToTest										CodeToTest=new CCodeToTest();

					Result1=CodeToTest.Method1(Context1);

					FillDatabaseContext(Context1);

					// !!!!! UNIT TEST by sa VZDY mal vytvarat nad SEPARATNYM DB CONTEXT, ktory je NEZAVISLY od DB CONTEXT, ktory bol pouzity na naplnenie DATABASE.
					// !!!!! Na demonstraciu, ze sa novy CONTEXT pripaja k tej istej instancii IN MEMORY DATABASE sa vytvori novy DB CONTEXT pre tu istu CONNECTION.
					using(CDBContext Context2=CreateDatabaseContext2(Connection))
					{
						Result2=CodeToTest.Method1(Context2);
					}
				}
			}

			Assert.Empty(Result1);
			Assert.Equal(4,Result2.Length);

			Assert.Equal("AAA",Result2[0].Value);
			Assert.Equal("BBB",Result2[1].Value);
			Assert.Equal("CCC",Result2[2].Value);
			Assert.Equal("DDD",Result2[3].Value);

			MTestOutputHelper.WriteLine($"TEST [{nameof(TestMethod1UsingCTestDBContext)}] FINISHED SUCCESSFULLY !");
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void TestMethod2UsingCTestDBContext()
		{
			MTestOutputHelper.WriteLine($"TEST [{nameof(TestMethod2UsingCTestDBContext)}] STARTED !");

			CTestEntity[]										Result1;
			CTestEntity[]										Result2;
			string												ConnectionString=CreateConnectionString();

			// !!!!! Pri IN MEMORY [Sqlite] DATABASE je NUTNE vytvorit CONNECTION, ktora sluzi ako PARAMETER do METHOD [DbContextOptionsBuilder DbContextOptionsBuilder.UseSqlite(DbConnection Connection, Action<SqliteDbContextOptionsBuilder> SqliteOptionsAction)].
			using(SqliteConnection Connection=new SqliteConnection(ConnectionString))
			{
				// !!!!! Pri IN MEMORY [Sqlite] DATABASE CONNECTION MUSI byt OPEN, aby sa vytvorila DATABASE.
				Connection.Open();

				using(CDBContext Context1=CreateDatabaseContext2(Connection))
				{
					// !!! TEST DATABASE sa vytvori volanim METHOD [bool DatabaseFacade.EnsureCreated()].
					Context1.Database.EnsureCreated();

					CCodeToTest										CodeToTest=new CCodeToTest();

					Result1=CodeToTest.Method2(Context1,1,2);

					FillDatabaseContext(Context1);

					// !!!!! UNIT TEST by sa VZDY mal vytvarat nad SEPARATNYM DB CONTEXT, ktory je NEZAVISLY od DB CONTEXT, ktory bol pouzity na naplnenie DATABASE.
					// !!!!! Na demonstraciu, ze sa novy CONTEXT pripaja k tej istej instancii IN MEMORY DATABASE sa vytvori novy DB CONTEXT pre tu istu CONNECTION.
					using(CDBContext Context2=CreateDatabaseContext2(Connection))
					{
						Result2=CodeToTest.Method2(Context2,1,2);
					}
				}
			}

			Assert.Empty(Result1);
			Assert.Equal(2,Result2.Length);

			Assert.Equal("BBB",Result2[0].Value);
			Assert.Equal("CCC",Result2[1].Value);

			MTestOutputHelper.WriteLine($"TEST [{nameof(TestMethod2UsingCTestDBContext)}] FINISHED SUCCESSFULLY !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------