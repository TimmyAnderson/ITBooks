using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Data.Common;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Storage;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedFeaturesAndConcurrencySqlServer
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		private static void FillData(CDBContext Context)
		{
			CTestEntity											TestEntity1=new CTestEntity("AAA");
			CTestEntity											TestEntity2=new CTestEntity("BBB");

			Context.TestEntities.Add(TestEntity1);
			Context.TestEntities.Add(TestEntity2);

			CEntityUsingUDF										EntityUsingUDF1=new CEntityUsingUDF("VALUE 100",100,100.1);
			CEntityUsingUDF										EntityUsingUDF2=new CEntityUsingUDF("VALUE 200",200,200.2);
			CEntityUsingUDF										EntityUsingUDF3=new CEntityUsingUDF("VALUE 300",300,300.3);
			CEntityUsingUDF										EntityUsingUDF4=new CEntityUsingUDF("VALUE 400",400,400.4);

			Context.EntitiesUsingUDF.Add(EntityUsingUDF1);
			Context.EntitiesUsingUDF.Add(EntityUsingUDF2);
			Context.EntitiesUsingUDF.Add(EntityUsingUDF3);
			Context.EntitiesUsingUDF.Add(EntityUsingUDF4);

			CEntityUsingSequence								EntityUsingSequence1=new CEntityUsingSequence(100);
			CEntityUsingSequence								EntityUsingSequence2=new CEntityUsingSequence(200);

			Context.EntitiesUsingSequence.Add(EntityUsingSequence1);
			Context.EntitiesUsingSequence.Add(EntityUsingSequence2);

			CEntityTimestampsDataAnnotations					EntityTimestampsDataAnnotations1=new CEntityTimestampsDataAnnotations(10);
			CEntityTimestampsDataAnnotations					EntityTimestampsDataAnnotations2=new CEntityTimestampsDataAnnotations(20);

			Context.EntitiesTimestampsDataAnnotations.Add(EntityTimestampsDataAnnotations1);
			Context.EntitiesTimestampsDataAnnotations.Add(EntityTimestampsDataAnnotations2);

			CEntityTimestampsFluentAPI							EntityTimestampsFluentAPI1=new CEntityTimestampsFluentAPI(10);
			CEntityTimestampsFluentAPI							EntityTimestampsFluentAPI2=new CEntityTimestampsFluentAPI(20);

			Context.EntitiesTimestampsFluentAPI.Add(EntityTimestampsFluentAPI1);
			Context.EntitiesTimestampsFluentAPI.Add(EntityTimestampsFluentAPI2);

			// !!!!! Vytvoria sa USER DEFINED FUNCTIONS.

			string												UserDefinedFunctionCodeDbContextNonStaticUserDefinedFunctionAddValueDataAnnotations=$"CREATE FUNCTION {nameof(CDBContext.DbContextNonStaticUserDefinedFunctionAddValueDataAnnotations)}(@Value1 int, @Value2 int) RETURNS int AS BEGIN RETURN (@Value1+@Value2) END";

			Context.Database.ExecuteSqlRaw(UserDefinedFunctionCodeDbContextNonStaticUserDefinedFunctionAddValueDataAnnotations);

			string												UserDefinedFunctionCodeDbContextNonStaticUserDefinedFunctionAddValueFluentAPI=$"CREATE FUNCTION {nameof(CDBContext.DbContextNonStaticUserDefinedFunctionAddValueFluentAPI)}(@Value1 int, @Value2 int) RETURNS int AS BEGIN RETURN (@Value1+@Value2) END";

			Context.Database.ExecuteSqlRaw(UserDefinedFunctionCodeDbContextNonStaticUserDefinedFunctionAddValueFluentAPI);

			string												UserDefinedFunctionCodeDbContextStaticUserDefinedFunctionAddValueDataAnnotations=$"CREATE FUNCTION {nameof(CDBContext.DbContextStaticUserDefinedFunctionAddValueDataAnnotations)}(@Value1 int, @Value2 int) RETURNS int AS BEGIN RETURN (@Value1+@Value2) END";

			Context.Database.ExecuteSqlRaw(UserDefinedFunctionCodeDbContextStaticUserDefinedFunctionAddValueDataAnnotations);

			string												UserDefinedFunctionCodeDbContextStaticUserDefinedFunctionAddValueFluentAPI=$"CREATE FUNCTION {nameof(CDBContext.DbContextStaticUserDefinedFunctionAddValueFluentAPI)}(@Value1 int, @Value2 int) RETURNS int AS BEGIN RETURN (@Value1+@Value2) END";

			Context.Database.ExecuteSqlRaw(UserDefinedFunctionCodeDbContextStaticUserDefinedFunctionAddValueFluentAPI);

			string												UserDefinedFunctionCodeCustomClassUserDefinedFunctionAddValueFluentAPI=$"CREATE FUNCTION {nameof(CUserDefinedFunctions.CustomClassUserDefinedFunctionAddValueFluentAPI)}(@Value1 int, @Value2 int) RETURNS int AS BEGIN RETURN (@Value1+@Value2) END";

			Context.Database.ExecuteSqlRaw(UserDefinedFunctionCodeCustomClassUserDefinedFunctionAddValueFluentAPI);

			string												UserDefinedFunctionCodeDbContextNonStaticUserDefinedFunctionAddValueTableValuedDataAnnotations=$"CREATE FUNCTION {nameof(Context.DbContextNonStaticUserDefinedFunctionAddValueTableValuedDataAnnotations)}(@Value int) RETURNS TABLE AS RETURN SELECT StringValue, IntValue, DoubleValue FROM {CDBContext.TABLE_NAME_USING_UDF} WHERE IntValue>@Value";

			Context.Database.ExecuteSqlRaw(UserDefinedFunctionCodeDbContextNonStaticUserDefinedFunctionAddValueTableValuedDataAnnotations);

			string												UserDefinedFunctionCodeDbContextNonStaticUserDefinedFunctionAddValueTableValuedFluentAPI=$"CREATE FUNCTION {nameof(Context.DbContextNonStaticUserDefinedFunctionAddValueTableValuedFluentAPI)}(@Value int) RETURNS TABLE AS RETURN SELECT StringValue, IntValue, DoubleValue FROM {CDBContext.TABLE_NAME_USING_UDF} WHERE IntValue>@Value";

			Context.Database.ExecuteSqlRaw(UserDefinedFunctionCodeDbContextNonStaticUserDefinedFunctionAddValueTableValuedFluentAPI);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void CreateTestDB()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				bool											DatabaseCreated=false;

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						Context.Database.EnsureDeleted();

						// !!! Na vytvorenie DB sa pouziva METHOD DatabaseFacade.Migrate().
						Context.Database.Migrate();

						FillData(Context);

						Context.SaveChanges();

						DatabaseCreated=true;
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						DatabaseCreated=false;
					}
				}

				if (DatabaseCreated==true)
				{
					CConsoleHelpers.WriteLine($"DATABASE CREATED !",ConsoleColor.Green);
				}
				else
				{
					CConsoleHelpers.WriteLine($"DATABASE ALREADY EXISTS !",ConsoleColor.Blue);
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void DeleteTestDB()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				bool											DatabaseDeleted=false;

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						DatabaseDeleted=Context.Database.EnsureDeleted();
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
						DatabaseDeleted=false;
					}
				}

				if (DatabaseDeleted==true)
				{
					CConsoleHelpers.WriteLine($"DATABASE DELETED !",ConsoleColor.Green);
				}
				else
				{
					CConsoleHelpers.WriteLine($"DATABASE NOT DELETED !",ConsoleColor.Blue);
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestSelectTestEntity()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CTestEntity[]							Entities=Context.TestEntities.ToArray();

						CTestEntity.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void TestUsingScalarValuedUDF()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("NORMAL QUERY:",ConsoleColor.Cyan);

						CEntityUsingUDF[]						Entities=Context.EntitiesUsingUDF.ToArray();

						CEntityUsingUDF.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! USER DEFINED FUNCTION sa pouzije vo LINQ OPERATOR [Where] i LINQ OPERATOR [Select].
						CConsoleHelpers.WriteLine("USING Context.DbContextNonStaticUserDefinedFunctionAddValueDataAnnotations:",ConsoleColor.Cyan);

						CEntityUsingUDF[]						Entities=Context.EntitiesUsingUDF.Where(P => Context.DbContextNonStaticUserDefinedFunctionAddValueDataAnnotations(P.IntValue,1000)>1250).Select(P => new CEntityUsingUDF(P.ID,P.StringValue,Context.DbContextNonStaticUserDefinedFunctionAddValueDataAnnotations(P.IntValue,1000),P.DoubleValue)).ToArray();

						CEntityUsingUDF.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! USER DEFINED FUNCTION sa pouzije vo LINQ OPERATOR [Where] i LINQ OPERATOR [Select].
						CConsoleHelpers.WriteLine("USING Context.DbContextNonStaticUserDefinedFunctionAddValueFluentAPI:",ConsoleColor.Cyan);

						CEntityUsingUDF[]						Entities=Context.EntitiesUsingUDF.Where(P => Context.DbContextNonStaticUserDefinedFunctionAddValueFluentAPI(P.IntValue,1000)>1250).Select(P => new CEntityUsingUDF(P.ID,P.StringValue,Context.DbContextNonStaticUserDefinedFunctionAddValueFluentAPI(P.IntValue,1000),P.DoubleValue)).ToArray();

						CEntityUsingUDF.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! USER DEFINED FUNCTION sa pouzije vo LINQ OPERATOR [Where] i LINQ OPERATOR [Select].
						CConsoleHelpers.WriteLine("USING CDBContext.DbContextStaticUserDefinedFunctionAddValueDataAnnotations:",ConsoleColor.Cyan);

						CEntityUsingUDF[]						Entities=Context.EntitiesUsingUDF.Where(P => CDBContext.DbContextStaticUserDefinedFunctionAddValueDataAnnotations(P.IntValue,1000)>1250).Select(P => new CEntityUsingUDF(P.ID,P.StringValue,CDBContext.DbContextStaticUserDefinedFunctionAddValueDataAnnotations(P.IntValue,1000),P.DoubleValue)).ToArray();

						CEntityUsingUDF.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! USER DEFINED FUNCTION sa pouzije vo LINQ OPERATOR [Where] i LINQ OPERATOR [Select].
						CConsoleHelpers.WriteLine("USING CDBContext.DbContextStaticUserDefinedFunctionAddValueFluentAPI:",ConsoleColor.Cyan);

						CEntityUsingUDF[]						Entities=Context.EntitiesUsingUDF.Where(P => CDBContext.DbContextStaticUserDefinedFunctionAddValueFluentAPI(P.IntValue,1000)>1250).Select(P => new CEntityUsingUDF(P.ID,P.StringValue,CDBContext.DbContextStaticUserDefinedFunctionAddValueFluentAPI(P.IntValue,1000),P.DoubleValue)).ToArray();

						CEntityUsingUDF.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! USER DEFINED FUNCTION sa pouzije vo LINQ OPERATOR [Where] i LINQ OPERATOR [Select].
						CConsoleHelpers.WriteLine("USING CUserDefinedFunctions.CustomClassUserDefinedFunctionAddValueFluentAPI:",ConsoleColor.Cyan);

						CEntityUsingUDF[]						Entities=Context.EntitiesUsingUDF.Where(P => CUserDefinedFunctions.CustomClassUserDefinedFunctionAddValueFluentAPI(P.IntValue,1000)>1250).Select(P => new CEntityUsingUDF(P.ID,P.StringValue,CUserDefinedFunctions.CustomClassUserDefinedFunctionAddValueFluentAPI(P.IntValue,1000),P.DoubleValue)).ToArray();

						CEntityUsingUDF.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void TestUsingTableValuedUDF()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("NORMAL QUERY:",ConsoleColor.Cyan);

						CEntityUsingUDF[]						Entities=Context.EntitiesUsingUDF.ToArray();

						CEntityUsingUDF.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! USER DEFINED FUNCTION sa pouzije ako TABLE SET pre LINQ QUERY.
						CConsoleHelpers.WriteLine("USING Context.DbContextNonStaticUserDefinedFunctionAddValueTableValuedDataAnnotations:",ConsoleColor.Cyan);

						CEntityTableValuedFunctionResult[]		Entities=Context.DbContextNonStaticUserDefinedFunctionAddValueTableValuedDataAnnotations(250).OrderByDescending(P => P.IntValue).ToArray();

						CEntityTableValuedFunctionResult.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! USER DEFINED FUNCTION sa pouzije ako TABLE SET pre LINQ QUERY.
						CConsoleHelpers.WriteLine("USING Context.DbContextNonStaticUserDefinedFunctionAddValueTableValuedFluentAPI:",ConsoleColor.Cyan);

						CEntityTableValuedFunctionResult[]		Entities=Context.DbContextNonStaticUserDefinedFunctionAddValueTableValuedFluentAPI(250).OrderByDescending(P => P.IntValue).ToArray();

						CEntityTableValuedFunctionResult.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void TestUsingSequence()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityUsingSequence[]					Entities=Context.EntitiesUsingSequence.ToArray();

						CEntityUsingSequence.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityUsingSequence					Entity=new CEntityUsingSequence(300);

						Context.EntitiesUsingSequence.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.ID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.ID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityUsingSequence[]					Entities=Context.EntitiesUsingSequence.ToArray();

						CEntityUsingSequence.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

						CEntityUsingSequence					Entity=Context.EntitiesUsingSequence.Where(P => P.ID==ID).First();

						Entity.Value=999;

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.ID}] was UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT UPDATED!",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityUsingSequence[]					Entities=Context.EntitiesUsingSequence.ToArray();

						CEntityUsingSequence.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityUsingSequence					Entity=Context.EntitiesUsingSequence.Where(P => P.ID==ID).First();

						Context.EntitiesUsingSequence.Remove(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.ID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE ENTITIES:",ConsoleColor.Cyan);

						CEntityUsingSequence[]					Entities=Context.EntitiesUsingSequence.ToArray();

						CEntityUsingSequence.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pouzivaju sa TIMESTAMPS na zaklade ktorych ENTITY FRAMEWORK CORE identifikuje vznik CONCURRENCY CONFLICT a hodi EXCEPTION [DbUpdateConcurrencyException].
		public static void UpdateTimestampsDataAnnotationsEntityTask(int TaskID, int Step, int SleepTime, int EntityID)
		{
			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityTimestampsDataAnnotations		Entity=Context.EntitiesTimestampsDataAnnotations.Where(P => P.EntityID==EntityID).First();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] READ VALUE [{Entity.EntityValue}] !",ConsoleColor.Green);

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] WAITING STARTED !",ConsoleColor.Yellow);

						Thread.Sleep(SleepTime);

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] WAITING FINISHED !",ConsoleColor.Yellow);

						Entity.EntityValue+=Step;

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] ADDING VALUE [{Step}] !",ConsoleColor.Green);

						Context.SaveChanges();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] UPDATED VALUE to VALUE [{Entity.EntityValue}] !",ConsoleColor.Green);
					}
					catch(DbUpdateConcurrencyException E)
					{
						CConsoleHelpers.WriteLine($"TASK [{TaskID}] DB UPDATE CONCURRENCY EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"TASK [{TaskID}] EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(DbUpdateConcurrencyException E)
			{
				CConsoleHelpers.WriteLine($"TASK [{TaskID}] DB UPDATE CONCURRENCY EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"TASK [{TaskID}] EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void TestUpdateTimestampsDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityTimestampsDataAnnotations[]		Entities=Context.EntitiesTimestampsDataAnnotations.ToArray();

						CEntityTimestampsDataAnnotations.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityTimestampsDataAnnotations		Entity=new CEntityTimestampsDataAnnotations(100);

						Context.EntitiesTimestampsDataAnnotations.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityTimestampsDataAnnotations[]		Entities=Context.EntitiesTimestampsDataAnnotations.ToArray();

						CEntityTimestampsDataAnnotations.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

				Task											Task1=new Task(() => UpdateTimestampsDataAnnotationsEntityTask(1,10,500,ID));
				Task											Task2=new Task(() => UpdateTimestampsDataAnnotationsEntityTask(2,20,1000,ID));

				Task1.Start();
				Task2.Start();

				Task.WaitAll(Task1,Task2);

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityTimestampsDataAnnotations[]		Entities=Context.EntitiesTimestampsDataAnnotations.ToArray();

						CEntityTimestampsDataAnnotations.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityTimestampsDataAnnotations		Entity=Context.EntitiesTimestampsDataAnnotations.Where(P => P.EntityID==ID).First();

						Context.EntitiesTimestampsDataAnnotations.Remove(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE ENTITIES:",ConsoleColor.Cyan);

						CEntityTimestampsDataAnnotations[]		Entities=Context.EntitiesTimestampsDataAnnotations.ToArray();

						CEntityTimestampsDataAnnotations.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pouzivaju sa TIMESTAMPS na zaklade ktorych ENTITY FRAMEWORK CORE identifikuje vznik CONCURRENCY CONFLICT a hodi EXCEPTION [DbUpdateConcurrencyException].
		public static void UpdateTimestampsFluentAPIEntityTask(int TaskID, int Step, int SleepTime, int EntityID)
		{
			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityTimestampsFluentAPI				Entity=Context.EntitiesTimestampsFluentAPI.Where(P => P.EntityID==EntityID).First();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] READ VALUE [{Entity.EntityValue}] !",ConsoleColor.Green);

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] WAITING STARTED !",ConsoleColor.Yellow);

						Thread.Sleep(SleepTime);

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] WAITING FINISHED !",ConsoleColor.Yellow);

						Entity.EntityValue+=Step;

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] ADDING VALUE [{Step}] !",ConsoleColor.Green);

						Context.SaveChanges();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] UPDATED VALUE to VALUE [{Entity.EntityValue}] !",ConsoleColor.Green);
					}
					catch(DbUpdateConcurrencyException E)
					{
						CConsoleHelpers.WriteLine($"TASK [{TaskID}] DB UPDATE CONCURRENCY EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"TASK [{TaskID}] EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(DbUpdateConcurrencyException E)
			{
				CConsoleHelpers.WriteLine($"TASK [{TaskID}] DB UPDATE CONCURRENCY EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"TASK [{TaskID}] EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void TestUpdateTimestampsFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityTimestampsFluentAPI[]			Entities=Context.EntitiesTimestampsFluentAPI.ToArray();

						CEntityTimestampsFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityTimestampsFluentAPI				Entity=new CEntityTimestampsFluentAPI(100);

						Context.EntitiesTimestampsFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityTimestampsFluentAPI[]			Entities=Context.EntitiesTimestampsFluentAPI.ToArray();

						CEntityTimestampsFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

				Task											Task1=new Task(() => UpdateTimestampsFluentAPIEntityTask(1,10,500,ID));
				Task											Task2=new Task(() => UpdateTimestampsFluentAPIEntityTask(2,20,1000,ID));

				Task1.Start();
				Task2.Start();

				Task.WaitAll(Task1,Task2);

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityTimestampsFluentAPI[]			Entities=Context.EntitiesTimestampsFluentAPI.ToArray();

						CEntityTimestampsFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityTimestampsFluentAPI				Entity=Context.EntitiesTimestampsFluentAPI.Where(P => P.EntityID==ID).First();

						Context.EntitiesTimestampsFluentAPI.Remove(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE ENTITIES:",ConsoleColor.Cyan);

						CEntityTimestampsFluentAPI[]			Entities=Context.EntitiesTimestampsFluentAPI.ToArray();

						CEntityTimestampsFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        static void Main(string[] args)
        {
			//CreateTestDB();
			//DeleteTestDB();
			//TestSelectTestEntity();
			//TestUsingScalarValuedUDF();
			//TestUsingTableValuedUDF();
			//TestUsingSequence();
			//TestUpdateTimestampsDataAnnotations();
			//TestUpdateTimestampsFluentAPI();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------