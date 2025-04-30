using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.Data.Sqlite;
using Microsoft.EntityFrameworkCore;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace DataAccess3
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuRawSqlOperations : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuRawSqlOperations()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCreateDatabase(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					if (Context.Database.CanConnect()==false)
					{
						Context.Database.Migrate();

						Console.WriteLine("DATABASE CREATED !");
					}
					else
					{
						Console.WriteLine("Can't CREATE DATABASE.");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteDatabase(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					if (Context.Database.EnsureDeleted()==true)
					{
						Console.WriteLine("DATABASE DELETED !");
					}
					else
					{
						Console.WriteLine("Can't DELETE to DATABASE.");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntitiesRawSql(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityRawSql[]								Entities=Context.EntitiesRawSql.ToArray();

					CEntityRawSql.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUseFromSql(string CommandID, object[] Parameters)
		{
			int													Category=(int)Parameters[0];

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					// !!! Nazov TABLE musi zodpovedat nazvu ENTITY.
					// !!! Nazvy COLUMNS musia zodpovedat nazvom ENTITY PROPERTIES.
					// !!! METHOD [FromSql()] je SAFE voci DEPENDENCY INJECTION ATTACKS.
					CEntityRawSql[]								Entities=Context.EntitiesRawSql.FromSql($"SELECT * FROM EntitiesRawSql WHERE Category={Category}").ToArray();

					CEntityRawSql.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUseFromSqlRaw(string CommandID, object[] Parameters)
		{
			int													Category=(int)Parameters[0];

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					string										ColumnName="Category";

					// !!!!! TYPE [SqliteParameter] je DERIVED z CLASS [DbParameter], a preto PARAMETER je zabezpeceny voci DEPENDENCY INJECTION ATTACKS.
					SqliteParameter								Value=new SqliteParameter("ColumnValue",Category);

					// !!!!! QUERY NIE JE chranena voci DEPENDENCY INJECTION ATTACKS.
					// !!!!! QEURY moze parametrizovat aj TABLE NAME ci COLUMN NAMES.
					string										Query=$"SELECT * FROM EntitiesRawSql WHERE {ColumnName}=@ColumnValue";

					// !!! Nazov TABLE musi zodpovedat nazvu ENTITY.
					// !!! Nazvy COLUMNS musia zodpovedat nazvom ENTITY PROPERTIES.
					// !!! METHOD [FromSqlRaw()] NIE je SAFE voci DEPENDENCY INJECTION ATTACKS.
					CEntityRawSql[]								Entities=Context.EntitiesRawSql.FromSqlRaw(Query,Value).ToArray();

					CEntityRawSql.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUseSqlQuery(string CommandID, object[] Parameters)
		{
			int													Category=(int)Parameters[0];

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					// !!! METHOD [SqlQuery()] je SAFE voci DEPENDENCY INJECTION ATTACKS.
					int[]										Values=Context.Database.SqlQuery<int>($"SELECT Value FROM EntitiesRawSql WHERE Category={Category}").ToArray();
						
					for(int Index=0;Index<Values.Length;Index++)
					{
						int										Value=Values[Index];

						Console.WriteLine($"{(Index+1)}. VALUE [{Value}].");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUseSqlQueryRaw(string CommandID, object[] Parameters)
		{
			int													Category=(int)Parameters[0];

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					string										ColumnName="Category";

					// !!!!! TYPE [SqliteParameter] je DERIVED z CLASS [DbParameter], a preto PARAMETER je zabezpeceny voci DEPENDENCY INJECTION ATTACKS.
					SqliteParameter								ParameterValue=new SqliteParameter("ColumnValue",Category);

					// !!!!! QUERY NIE JE chranena voci DEPENDENCY INJECTION ATTACKS.
					// !!!!! QEURY moze parametrizovat aj TABLE NAME ci COLUMN NAMES.
					string										Query=$"SELECT Value FROM EntitiesRawSql WHERE {ColumnName}=@ColumnValue";

					// !!! METHOD [SqlQueryRaw()] NIE je SAFE voci DEPENDENCY INJECTION ATTACKS.
					int[]										Values=Context.Database.SqlQueryRaw<int>(Query,ParameterValue).ToArray();

					for(int Index=0;Index<Values.Length;Index++)
					{
						int										Value=Values[Index];

						Console.WriteLine($"{(Index+1)}. VALUE [{Value}].");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUseExecuteSql(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityRawSql								NewEntity=new CEntityRawSql(10000,99999);

					Context.Add(NewEntity);

					Context.SaveChanges();

					ID=NewEntity.ID;

					Console.WriteLine($"NEW ENTITY INSERTED with ID [{ID}].");
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
				}
			}

			CConsoleHelpers.WriteLineSeparator();

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityRawSql[]								Entities=Context.EntitiesRawSql.ToArray();

					CEntityRawSql.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}

			CConsoleHelpers.WriteLineSeparator();

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					// !!! METHOD [ExecuteSql()] je SAFE voci DEPENDENCY INJECTION ATTACKS.
					int											Result=Context.Database.ExecuteSql($"DELETE FROM EntitiesRawSql WHERE ID={ID}");
						
					Console.WriteLine($"OPERATION RESULT [{Result}].");
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
				}
			}

			CConsoleHelpers.WriteLineSeparator();

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityRawSql[]								Entities=Context.EntitiesRawSql.ToArray();

					CEntityRawSql.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUseExecuteSqlRaw(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityRawSql								NewEntity=new CEntityRawSql(10000,99999);

					Context.Add(NewEntity);

					Context.SaveChanges();

					ID=NewEntity.ID;

					Console.WriteLine($"NEW ENTITY INSERTED with ID [{ID}].");
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
				}
			}

			CConsoleHelpers.WriteLineSeparator();

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityRawSql[]								Entities=Context.EntitiesRawSql.ToArray();

					CEntityRawSql.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}

			CConsoleHelpers.WriteLineSeparator();

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					string										ColumnName="ID";

					// !!!!! TYPE [SqliteParameter] je DERIVED z CLASS [DbParameter], a preto PARAMETER je zabezpeceny voci DEPENDENCY INJECTION ATTACKS.
					SqliteParameter								ParameterValue=new SqliteParameter("ColumnValue",ID);

					// !!!!! QUERY NIE JE chranena voci DEPENDENCY INJECTION ATTACKS.
					// !!!!! QEURY moze parametrizovat aj TABLE NAME ci COLUMN NAMES.
					string										Query=$"DELETE FROM EntitiesRawSql WHERE {ColumnName}=@ColumnValue";

					// !!! METHOD [ExecuteSqlRaw()] NIE je SAFE voci DEPENDENCY INJECTION ATTACKS.
					int											Result=Context.Database.ExecuteSqlRaw(Query,ParameterValue);

					Context.Database.ExecuteSql($"DELETE FROM EntitiesRawSql WHERE ID={ID}");
						
					Console.WriteLine($"OPERATION RESULT [{Result}].");
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
				}
			}

			CConsoleHelpers.WriteLineSeparator();

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityRawSql[]								Entities=Context.EntitiesRawSql.ToArray();

					CEntityRawSql.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("cdb","CREATE DB",new EMenuCommandParameterType[0],ExecuteCommandCreateDatabase));
			CommandsCollection.Add(new CMenuCommand("ddb","DELETE DB",new EMenuCommandParameterType[0],ExecuteCommandDeleteDatabase));
			CommandsCollection.Add(new CMenuCommand("1","GET ALL RAW SQL",new EMenuCommandParameterType[0],ExecuteCommandGetEntitiesRawSql));
			CommandsCollection.Add(new CMenuCommand("2","USE FROM SQL",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandUseFromSql));
			CommandsCollection.Add(new CMenuCommand("3","USE FROM SQL RAW",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandUseFromSqlRaw));
			CommandsCollection.Add(new CMenuCommand("4","USE SQL QUERY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandUseSqlQuery));
			CommandsCollection.Add(new CMenuCommand("5","USE SQL QUERY RAW",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandUseSqlQueryRaw));
			CommandsCollection.Add(new CMenuCommand("6","USE EQECUTE SQL",new EMenuCommandParameterType[0],ExecuteCommandUseExecuteSql));
			CommandsCollection.Add(new CMenuCommand("7","USE EQECUTE SQL RAW",new EMenuCommandParameterType[0],ExecuteCommandUseExecuteSqlRaw));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------