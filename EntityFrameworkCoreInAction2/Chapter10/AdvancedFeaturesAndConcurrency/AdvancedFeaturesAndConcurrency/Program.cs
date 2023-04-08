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
using Microsoft.Data.Sqlite;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedFeaturesAndConcurrency
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

			CEntityComputedColumns								EntityComputedColumns1=new CEntityComputedColumns("AAA","BBB",100,200);
			CEntityComputedColumns								EntityComputedColumns2=new CEntityComputedColumns("CCC","DDD",300,400);

			Context.EntitiesComputedColumns.Add(EntityComputedColumns1);
			Context.EntitiesComputedColumns.Add(EntityComputedColumns2);

			CEntityDefaultValueColumns							EntityDefaultValueColumns1=new CEntityDefaultValueColumns("AAA",default,default,default);
			CEntityDefaultValueColumns							EntityDefaultValueColumns2=new CEntityDefaultValueColumns("BBB",default,default,default);

			Context.EntitiesDefaultValueColumns.Add(EntityDefaultValueColumns1);
			Context.EntitiesDefaultValueColumns.Add(EntityDefaultValueColumns2);

			CEntityDBGeneratedPropertiesDataAnnotations			EntityDBGeneratedPropertiesDataAnnotations1=new CEntityDBGeneratedPropertiesDataAnnotations(100);
			CEntityDBGeneratedPropertiesDataAnnotations			EntityDBGeneratedPropertiesDataAnnotations2=new CEntityDBGeneratedPropertiesDataAnnotations(200);

			Context.EntitiesDBGeneratedPropertiesDataAnnotations.Add(EntityDBGeneratedPropertiesDataAnnotations1);
			Context.EntitiesDBGeneratedPropertiesDataAnnotations.Add(EntityDBGeneratedPropertiesDataAnnotations2);

			CEntityDBGeneratedPropertiesFluentAPI				EntityDBGeneratedPropertiesFluentAPI1=new CEntityDBGeneratedPropertiesFluentAPI(100,150);
			CEntityDBGeneratedPropertiesFluentAPI				EntityDBGeneratedPropertiesFluentAPI2=new CEntityDBGeneratedPropertiesFluentAPI(200,250);

			Context.EntitiesDBGeneratedPropertiesFluentAPI.Add(EntityDBGeneratedPropertiesFluentAPI1);
			Context.EntitiesDBGeneratedPropertiesFluentAPI.Add(EntityDBGeneratedPropertiesFluentAPI2);

			CEntityOptimisticConcurrency						EntityOptimisticConcurrency1=new CEntityOptimisticConcurrency(10);
			CEntityOptimisticConcurrency						EntityOptimisticConcurrency2=new CEntityOptimisticConcurrency(20);

			Context.EntitiesOptimisticConcurrency.Add(EntityOptimisticConcurrency1);
			Context.EntitiesOptimisticConcurrency.Add(EntityOptimisticConcurrency2);

			CEntityConcurrencyTokensDataAnnotations				EntityConcurrencyTokensDataAnnotations1=new CEntityConcurrencyTokensDataAnnotations(10);
			CEntityConcurrencyTokensDataAnnotations				EntityConcurrencyTokensDataAnnotations2=new CEntityConcurrencyTokensDataAnnotations(20);

			Context.EntitiesConcurrencyTokensDataAnnotations.Add(EntityConcurrencyTokensDataAnnotations1);
			Context.EntitiesConcurrencyTokensDataAnnotations.Add(EntityConcurrencyTokensDataAnnotations2);

			CEntityConcurrencyTokensFluentAPI					EntityConcurrencyTokensFluentAPI1=new CEntityConcurrencyTokensFluentAPI(10);
			CEntityConcurrencyTokensFluentAPI					EntityConcurrencyTokensFluentAPI2=new CEntityConcurrencyTokensFluentAPI(20);

			Context.EntitiesConcurrencyTokensFluentAPI.Add(EntityConcurrencyTokensFluentAPI1);
			Context.EntitiesConcurrencyTokensFluentAPI.Add(EntityConcurrencyTokensFluentAPI2);

			CEntityMultipleConcurrencyTokensFluentAPI			EntityMultipleConcurrencyTokensFluentAPI1=new CEntityMultipleConcurrencyTokensFluentAPI(10,60);
			CEntityMultipleConcurrencyTokensFluentAPI			EntityMultipleConcurrencyTokensFluentAPI2=new CEntityMultipleConcurrencyTokensFluentAPI(20,70);

			Context.EntitiesMultipleConcurrencyTokensFluentAPI.Add(EntityMultipleConcurrencyTokensFluentAPI1);
			Context.EntitiesMultipleConcurrencyTokensFluentAPI.Add(EntityMultipleConcurrencyTokensFluentAPI2);
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
						if (Context.Database.CanConnect()==false)
						{
							// !!! Na vytvorenie DB sa pouziva METHOD DatabaseFacade.Migrate().
							Context.Database.Migrate();

							FillData(Context);

							Context.SaveChanges();

							DatabaseCreated=true;
						}
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
						CConsoleHelpers.WriteLine("USING Context.DbContextNonStaticUserDefinedFunctionAddValueDataAnnotations:",ConsoleColor.Cyan);

						// !!!!! V SQLITE sa UDF FUNCTIONS NEDEFINUJU na DB SERVERI, kedze SQLITE NEMA DB SERVER, ale bezi v HOSTING PROCESS. SQLITE PODPORUJE UDF, ale tie su vykonavane na CLIENT SIDE.
						// !!!!! Kedze UDF FUNCTIONS NIE su ulozene v DB, ale iba v ramci beziacej DB CONNECTION, je ich treba pred kazdym pouzitim ZNOVA DEFINOVAT.
						// !!!!! UDF FUNCTIONS sa NEDEFINUJU pomocou SQL COMMANDS ako napriklad v SQL SERVER, ale pomocou METHOD [void CreateFunction<T1,T2,TResult>(string Name, Func<T1,T2,TResult> Function, bool IsDeterministic)].

						// !!! Ziska sa instancia CLASS [SqliteConnection].
						SqliteConnection						Connection=(SqliteConnection) Context.Database.GetDbConnection();

						// !!!!! Pre CURRENT CONNECTION sa definuje UDF FUNCTION.
						// !!!!! NAME UDF FUNCTION sa MUSI zhodovat s NAME UDF FUNCTION zaregistrovane v DB CONTEXT.
						Connection.CreateFunction<int,int,int>(nameof(Context.DbContextNonStaticUserDefinedFunctionAddValueDataAnnotations),(P1,P2) => (P1+P2),true);

						// !!! USER DEFINED FUNCTION sa pouzije vo LINQ OPERATOR [Where] i LINQ OPERATOR [Select].
						// !!!!! C# PLACEHOLDER METHOD sa mapuje volanie UDF FUNCTION.
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
						CConsoleHelpers.WriteLine("USING Context.DbContextNonStaticUserDefinedFunctionAddValueFluentAPI:",ConsoleColor.Cyan);

						// !!!!! V SQLITE sa UDF FUNCTIONS NEDEFINUJU na DB SERVERI, kedze SQLITE NEMA DB SERVER, ale bezi v HOSTING PROCESS. SQLITE PODPORUJE UDF, ale tie su vykonavane na CLIENT SIDE.
						// !!!!! Kedze UDF FUNCTIONS NIE su ulozene v DB, ale iba v ramci beziacej DB CONNECTION, je ich treba pred kazdym pouzitim ZNOVA DEFINOVAT.
						// !!!!! UDF FUNCTIONS sa NEDEFINUJU pomocou SQL COMMANDS ako napriklad v SQL SERVER, ale pomocou METHOD [void CreateFunction<T1,T2,TResult>(string Name, Func<T1,T2,TResult> Function, bool IsDeterministic)].

						// !!! Ziska sa instancia CLASS [SqliteConnection].
						SqliteConnection						Connection=(SqliteConnection) Context.Database.GetDbConnection();

						// !!!!! Pre CURRENT CONNECTION sa definuje UDF FUNCTION.
						// !!!!! NAME UDF FUNCTION sa MUSI zhodovat s NAME UDF FUNCTION zaregistrovane v DB CONTEXT.
						Connection.CreateFunction<int,int,int>(nameof(Context.DbContextNonStaticUserDefinedFunctionAddValueFluentAPI),(P1,P2) => (P1+P2),true);

						// !!! USER DEFINED FUNCTION sa pouzije vo LINQ OPERATOR [Where] i LINQ OPERATOR [Select].
						// !!!!! C# PLACEHOLDER METHOD sa mapuje volanie UDF FUNCTION.
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
						CConsoleHelpers.WriteLine("USING CDBContext.DbContextStaticUserDefinedFunctionAddValueDataAnnotations:",ConsoleColor.Cyan);

						// !!!!! V SQLITE sa UDF FUNCTIONS NEDEFINUJU na DB SERVERI, kedze SQLITE NEMA DB SERVER, ale bezi v HOSTING PROCESS. SQLITE PODPORUJE UDF, ale tie su vykonavane na CLIENT SIDE.
						// !!!!! Kedze UDF FUNCTIONS NIE su ulozene v DB, ale iba v ramci beziacej DB CONNECTION, je ich treba pred kazdym pouzitim ZNOVA DEFINOVAT.
						// !!!!! UDF FUNCTIONS sa NEDEFINUJU pomocou SQL COMMANDS ako napriklad v SQL SERVER, ale pomocou METHOD [void CreateFunction<T1,T2,TResult>(string Name, Func<T1,T2,TResult> Function, bool IsDeterministic)].

						// !!! Ziska sa instancia CLASS [SqliteConnection].
						SqliteConnection						Connection=(SqliteConnection) Context.Database.GetDbConnection();

						// !!!!! Pre CURRENT CONNECTION sa definuje UDF FUNCTION.
						// !!!!! NAME UDF FUNCTION sa MUSI zhodovat s NAME UDF FUNCTION zaregistrovane v DB CONTEXT.
						Connection.CreateFunction<int,int,int>(nameof(CDBContext.DbContextStaticUserDefinedFunctionAddValueDataAnnotations),(P1,P2) => (P1+P2),true);

						// !!! USER DEFINED FUNCTION sa pouzije vo LINQ OPERATOR [Where] i LINQ OPERATOR [Select].
						// !!!!! C# PLACEHOLDER METHOD sa mapuje volanie UDF FUNCTION.
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
						CConsoleHelpers.WriteLine("USING CDBContext.DbContextStaticUserDefinedFunctionAddValueFluentAPI:",ConsoleColor.Cyan);

						// !!!!! V SQLITE sa UDF FUNCTIONS NEDEFINUJU na DB SERVERI, kedze SQLITE NEMA DB SERVER, ale bezi v HOSTING PROCESS. SQLITE PODPORUJE UDF, ale tie su vykonavane na CLIENT SIDE.
						// !!!!! Kedze UDF FUNCTIONS NIE su ulozene v DB, ale iba v ramci beziacej DB CONNECTION, je ich treba pred kazdym pouzitim ZNOVA DEFINOVAT.
						// !!!!! UDF FUNCTIONS sa NEDEFINUJU pomocou SQL COMMANDS ako napriklad v SQL SERVER, ale pomocou METHOD [void CreateFunction<T1,T2,TResult>(string Name, Func<T1,T2,TResult> Function, bool IsDeterministic)].

						// !!! Ziska sa instancia CLASS [SqliteConnection].
						SqliteConnection						Connection=(SqliteConnection) Context.Database.GetDbConnection();

						// !!!!! Pre CURRENT CONNECTION sa definuje UDF FUNCTION.
						// !!!!! NAME UDF FUNCTION sa MUSI zhodovat s NAME UDF FUNCTION zaregistrovane v DB CONTEXT.
						Connection.CreateFunction<int,int,int>(nameof(CDBContext.DbContextStaticUserDefinedFunctionAddValueFluentAPI),(P1,P2) => (P1+P2),true);

						// !!! USER DEFINED FUNCTION sa pouzije vo LINQ OPERATOR [Where] i LINQ OPERATOR [Select].
						// !!!!! C# PLACEHOLDER METHOD sa mapuje volanie UDF FUNCTION.
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
						CConsoleHelpers.WriteLine("USING CUserDefinedFunctions.CustomClassUserDefinedFunctionAddValueFluentAPI:",ConsoleColor.Cyan);

						// !!!!! V SQLITE sa UDF FUNCTIONS NEDEFINUJU na DB SERVERI, kedze SQLITE NEMA DB SERVER, ale bezi v HOSTING PROCESS. SQLITE PODPORUJE UDF, ale tie su vykonavane na CLIENT SIDE.
						// !!!!! Kedze UDF FUNCTIONS NIE su ulozene v DB, ale iba v ramci beziacej DB CONNECTION, je ich treba pred kazdym pouzitim ZNOVA DEFINOVAT.
						// !!!!! UDF FUNCTIONS sa NEDEFINUJU pomocou SQL COMMANDS ako napriklad v SQL SERVER, ale pomocou METHOD [void CreateFunction<T1,T2,TResult>(string Name, Func<T1,T2,TResult> Function, bool IsDeterministic)].

						// !!! Ziska sa instancia CLASS [SqliteConnection].
						SqliteConnection						Connection=(SqliteConnection) Context.Database.GetDbConnection();

						// !!!!! Pre CURRENT CONNECTION sa definuje UDF FUNCTION.
						// !!!!! NAME UDF FUNCTION sa MUSI zhodovat s NAME UDF FUNCTION zaregistrovane v DB CONTEXT.
						Connection.CreateFunction<int,int,int>(nameof(CUserDefinedFunctions.CustomClassUserDefinedFunctionAddValueFluentAPI),(P1,P2) => (P1+P2),true);

						// !!! USER DEFINED FUNCTION sa pouzije vo LINQ OPERATOR [Where] i LINQ OPERATOR [Select].
						// !!!!! C# PLACEHOLDER METHOD sa mapuje volanie UDF FUNCTION.
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
		public static void TestComputedColumns()
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

						CEntityComputedColumns[]				Entities=Context.EntitiesComputedColumns.ToArray();

						CEntityComputedColumns.PrintToConsole(Entities);
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

						CEntityComputedColumns					Entity=new CEntityComputedColumns("EEE","FFF",500,600);

						Context.EntitiesComputedColumns.Add(Entity);

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

						CEntityComputedColumns[]				Entities=Context.EntitiesComputedColumns.ToArray();

						CEntityComputedColumns.PrintToConsole(Entities);
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

						CEntityComputedColumns					Entity=Context.EntitiesComputedColumns.Where(P => P.ID==ID).First();

						Entity.IntValue2=999;
						Entity.StringValue1="ZZZ";

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

						CEntityComputedColumns[]				Entities=Context.EntitiesComputedColumns.ToArray();

						CEntityComputedColumns.PrintToConsole(Entities);
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

						CEntityComputedColumns					Entity=Context.EntitiesComputedColumns.Where(P => P.ID==ID).First();

						Context.EntitiesComputedColumns.Remove(Entity);

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

						CEntityComputedColumns[]				Entities=Context.EntitiesComputedColumns.ToArray();

						CEntityComputedColumns.PrintToConsole(Entities);
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
		public static void TesDefaultValueColumns()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityDefaultValueColumns[]			Entities=Context.EntitiesDefaultValueColumns.ToArray();

						CEntityDefaultValueColumns.PrintToConsole(Entities);
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

						CEntityDefaultValueColumns				Entity1=new CEntityDefaultValueColumns("CCC",default,default,default);

						// !!!!! DEFAULT VALUES sa NEAPLIKUJU, pretoze VALUES su EXPLICITNE nastavene na NON DEFAULT C# VALUES.
						CEntityDefaultValueColumns				Entity2=new CEntityDefaultValueColumns("DDD",DateTime.UtcNow,333.444,555);

						Context.EntitiesDefaultValueColumns.Add(Entity1);
						Context.EntitiesDefaultValueColumns.Add(Entity2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=Entity1.ID;
							ID2=Entity2.ID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity1.ID}] and ENTITY [{Entity2.ID}] were INSERTED !",ConsoleColor.Blue);
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

						CEntityDefaultValueColumns[]			Entities=Context.EntitiesDefaultValueColumns.ToArray();

						CEntityDefaultValueColumns.PrintToConsole(Entities);
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

						CEntityDefaultValueColumns				Entity1=Context.EntitiesDefaultValueColumns.Where(P => P.ID==ID1).First();
						CEntityDefaultValueColumns				Entity2=Context.EntitiesDefaultValueColumns.Where(P => P.ID==ID2).First();

						Entity1.Value="XXX";
						Entity2.Value="YYY";

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity1.ID}] and ENTITY [{Entity2.ID}] were UPDATED !",ConsoleColor.Blue);
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

						CEntityDefaultValueColumns[]			Entities=Context.EntitiesDefaultValueColumns.ToArray();

						CEntityDefaultValueColumns.PrintToConsole(Entities);
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

						CEntityDefaultValueColumns				Entity1=Context.EntitiesDefaultValueColumns.Where(P => P.ID==ID1).First();
						CEntityDefaultValueColumns				Entity2=Context.EntitiesDefaultValueColumns.Where(P => P.ID==ID2).First();

						Context.EntitiesDefaultValueColumns.Remove(Entity1);
						Context.EntitiesDefaultValueColumns.Remove(Entity2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity1.ID}] and ENTITY [{Entity2.ID}] were DELETED !",ConsoleColor.Blue);
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

						CEntityDefaultValueColumns[]			Entities=Context.EntitiesDefaultValueColumns.ToArray();

						CEntityDefaultValueColumns.PrintToConsole(Entities);
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
		public static void TestDBGeneratedPropertiesDataAnnotations()
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

						CEntityDBGeneratedPropertiesDataAnnotations[]	Entities=Context.EntitiesDBGeneratedPropertiesDataAnnotations.ToArray();

						CEntityDBGeneratedPropertiesDataAnnotations.PrintToConsole(Entities);
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

						CEntityDBGeneratedPropertiesDataAnnotations	Entity=new CEntityDBGeneratedPropertiesDataAnnotations(300);

						Context.EntitiesDBGeneratedPropertiesDataAnnotations.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.DatabaseGeneratedIdentity;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.DatabaseGeneratedIdentity}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityDBGeneratedPropertiesDataAnnotations[]	Entities=Context.EntitiesDBGeneratedPropertiesDataAnnotations.ToArray();

						CEntityDBGeneratedPropertiesDataAnnotations.PrintToConsole(Entities);
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

						CEntityDBGeneratedPropertiesDataAnnotations	Entity=Context.EntitiesDBGeneratedPropertiesDataAnnotations.Where(P => P.DatabaseGeneratedIdentity==ID).First();

						Entity.NonDatabaseGenerated=999;

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.DatabaseGeneratedIdentity}] was UPDATED !",ConsoleColor.Blue);
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

						CEntityDBGeneratedPropertiesDataAnnotations[]	Entities=Context.EntitiesDBGeneratedPropertiesDataAnnotations.ToArray();

						CEntityDBGeneratedPropertiesDataAnnotations.PrintToConsole(Entities);
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

						CEntityDBGeneratedPropertiesDataAnnotations	Entity=Context.EntitiesDBGeneratedPropertiesDataAnnotations.Where(P => P.DatabaseGeneratedIdentity==ID).First();

						Context.EntitiesDBGeneratedPropertiesDataAnnotations.Remove(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.DatabaseGeneratedIdentity}] was DELETED !",ConsoleColor.Blue);
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

						CEntityDBGeneratedPropertiesDataAnnotations[]	Entities=Context.EntitiesDBGeneratedPropertiesDataAnnotations.ToArray();

						CEntityDBGeneratedPropertiesDataAnnotations.PrintToConsole(Entities);
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
		public static void TestDBGeneratedPropertiesFluentAPI()
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

						CEntityDBGeneratedPropertiesFluentAPI[]	Entities=Context.EntitiesDBGeneratedPropertiesFluentAPI.ToArray();

						CEntityDBGeneratedPropertiesFluentAPI.PrintToConsole(Entities);
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

						CEntityDBGeneratedPropertiesFluentAPI	Entity=new CEntityDBGeneratedPropertiesFluentAPI(300,350);

						Context.EntitiesDBGeneratedPropertiesFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.DatabaseGeneratedOnAdd;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.DatabaseGeneratedOnAdd}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityDBGeneratedPropertiesFluentAPI[]	Entities=Context.EntitiesDBGeneratedPropertiesFluentAPI.ToArray();

						CEntityDBGeneratedPropertiesFluentAPI.PrintToConsole(Entities);
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

						CEntityDBGeneratedPropertiesFluentAPI	Entity=Context.EntitiesDBGeneratedPropertiesFluentAPI.Where(P => P.DatabaseGeneratedOnAdd==ID).First();

						// !!!!! Tento UPDATE NEZBEHNE, pretoze PROPERTY je nastavena ako PROPERTY, ktorej VALUE je generovana v DATABASE pri UPDATE.
						Entity.DatabaseGeneratedOnUpdate=888;

						// !!!!! Vykona sa UPDATE ENTITY.
						Entity.NonDatabaseGenerated=999;

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.DatabaseGeneratedOnAdd}] was UPDATED !",ConsoleColor.Blue);
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

						CEntityDBGeneratedPropertiesFluentAPI[]	Entities=Context.EntitiesDBGeneratedPropertiesFluentAPI.ToArray();

						CEntityDBGeneratedPropertiesFluentAPI.PrintToConsole(Entities);
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

						CEntityDBGeneratedPropertiesFluentAPI	Entity=Context.EntitiesDBGeneratedPropertiesFluentAPI.Where(P => P.DatabaseGeneratedOnAdd==ID).First();

						Context.EntitiesDBGeneratedPropertiesFluentAPI.Remove(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.DatabaseGeneratedOnAdd}] was DELETED !",ConsoleColor.Blue);
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

						CEntityDBGeneratedPropertiesFluentAPI[]	Entities=Context.EntitiesDBGeneratedPropertiesFluentAPI.ToArray();

						CEntityDBGeneratedPropertiesFluentAPI.PrintToConsole(Entities);
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
		// !!! Pri OPTIMISTIC CONCURRENCY LAST WRITE WINS. To znamena, ze sa zapisa posledna zmena a prepisu sa predosle zmeny.
		public static void UpdateOptimisticConcurrencyEntityTask(int TaskID, int Step, int SleepTime, int EntityID)
		{
			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityOptimisticConcurrency			Entity=Context.EntitiesOptimisticConcurrency.Where(P => P.EntityID==EntityID).First();

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
		public static void TestUpdateOptimisticConcurrency()
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

						CEntityOptimisticConcurrency[]			Entities=Context.EntitiesOptimisticConcurrency.ToArray();

						CEntityOptimisticConcurrency.PrintToConsole(Entities);
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

						CEntityOptimisticConcurrency			Entity=new CEntityOptimisticConcurrency(100);

						Context.EntitiesOptimisticConcurrency.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityOptimisticConcurrency[]			Entities=Context.EntitiesOptimisticConcurrency.ToArray();

						CEntityOptimisticConcurrency.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

				Task											Task1=new Task(() => UpdateOptimisticConcurrencyEntityTask(1,10,500,ID));
				Task											Task2=new Task(() => UpdateOptimisticConcurrencyEntityTask(2,20,1000,ID));

				Task1.Start();
				Task2.Start();

				Task.WaitAll(Task1,Task2);

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityOptimisticConcurrency[]			Entities=Context.EntitiesOptimisticConcurrency.ToArray();

						CEntityOptimisticConcurrency.PrintToConsole(Entities);
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

						CEntityOptimisticConcurrency			Entity=Context.EntitiesOptimisticConcurrency.Where(P => P.EntityID==ID).First();

						Context.EntitiesOptimisticConcurrency.Remove(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
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

						CEntityOptimisticConcurrency[]			Entities=Context.EntitiesOptimisticConcurrency.ToArray();

						CEntityOptimisticConcurrency.PrintToConsole(Entities);
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
		// !!! Pouzivaju sa CONCURRENCY TOKENS na zaklade ktorych ENTITY FRAMEWORK CORE identifikuje vznik CONCURRENCY CONFLICT a hodi EXCEPTION [DbUpdateConcurrencyException].
		public static void UpdateConcurrencyTokensDataAnnotationsEntityTask(int TaskID, int Step, int SleepTime, int EntityID)
		{
			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityConcurrencyTokensDataAnnotations	Entity=Context.EntitiesConcurrencyTokensDataAnnotations.Where(P => P.EntityID==EntityID).First();

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
		public static void TestUpdateConcurrencyTokensDataAnnotations()
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

						CEntityConcurrencyTokensDataAnnotations[]	Entities=Context.EntitiesConcurrencyTokensDataAnnotations.ToArray();

						CEntityConcurrencyTokensDataAnnotations.PrintToConsole(Entities);
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

						CEntityConcurrencyTokensDataAnnotations	Entity=new CEntityConcurrencyTokensDataAnnotations(100);

						Context.EntitiesConcurrencyTokensDataAnnotations.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityConcurrencyTokensDataAnnotations[]	Entities=Context.EntitiesConcurrencyTokensDataAnnotations.ToArray();

						CEntityConcurrencyTokensDataAnnotations.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

				Task											Task1=new Task(() => UpdateConcurrencyTokensDataAnnotationsEntityTask(1,10,500,ID));
				Task											Task2=new Task(() => UpdateConcurrencyTokensDataAnnotationsEntityTask(2,20,1000,ID));

				Task1.Start();
				Task2.Start();

				Task.WaitAll(Task1,Task2);

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityConcurrencyTokensDataAnnotations[]	Entities=Context.EntitiesConcurrencyTokensDataAnnotations.ToArray();

						CEntityConcurrencyTokensDataAnnotations.PrintToConsole(Entities);
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

						CEntityConcurrencyTokensDataAnnotations	Entity=Context.EntitiesConcurrencyTokensDataAnnotations.Where(P => P.EntityID==ID).First();

						Context.EntitiesConcurrencyTokensDataAnnotations.Remove(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
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

						CEntityConcurrencyTokensDataAnnotations[]	Entities=Context.EntitiesConcurrencyTokensDataAnnotations.ToArray();

						CEntityConcurrencyTokensDataAnnotations.PrintToConsole(Entities);
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
		// !!! Pouzivaju sa CONCURRENCY TOKENS na zaklade ktorych ENTITY FRAMEWORK CORE identifikuje vznik CONCURRENCY CONFLICT a hodi EXCEPTION [DbUpdateConcurrencyException].
		public static void UpdateConcurrencyTokensFluentAPIEntityTask(int TaskID, int Step, int SleepTime, int EntityID)
		{
			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityConcurrencyTokensFluentAPI		Entity=Context.EntitiesConcurrencyTokensFluentAPI.Where(P => P.EntityID==EntityID).First();

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
		public static void TestUpdateConcurrencyTokensFluentAPI()
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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

						CEntityConcurrencyTokensFluentAPI		Entity=new CEntityConcurrencyTokensFluentAPI(100);

						Context.EntitiesConcurrencyTokensFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

				Task											Task1=new Task(() => UpdateConcurrencyTokensFluentAPIEntityTask(1,10,500,ID));
				Task											Task2=new Task(() => UpdateConcurrencyTokensFluentAPIEntityTask(2,20,1000,ID));

				Task1.Start();
				Task2.Start();

				Task.WaitAll(Task1,Task2);

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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

						CEntityConcurrencyTokensFluentAPI		Entity=Context.EntitiesConcurrencyTokensFluentAPI.Where(P => P.EntityID==ID).First();

						Context.EntitiesConcurrencyTokensFluentAPI.Remove(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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
		// !!! Pouzivaju sa CONCURRENCY TOKENS na zaklade ktorych ENTITY FRAMEWORK CORE identifikuje vznik CONCURRENCY CONFLICT a hodi EXCEPTION [DbUpdateConcurrencyException].
		public static void UpdateMultipleConcurrencyTokensFluentAPIEntityTask1(int TaskID, int Step, int SleepTime, int EntityID)
		{
			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityMultipleConcurrencyTokensFluentAPI	Entity=Context.EntitiesMultipleConcurrencyTokensFluentAPI.Where(P => P.EntityID==EntityID).First();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] READ VALUE 1 [{Entity.EntityValue1}] and READ VALUE 2 [{Entity.EntityValue2}] !",ConsoleColor.Green);

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] WAITING STARTED !",ConsoleColor.Yellow);

						Thread.Sleep(SleepTime);

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] WAITING FINISHED !",ConsoleColor.Yellow);

						Entity.EntityValue1+=Step;

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] ADDING VALUE [{Step}] to VALUE 1 [{Entity.EntityValue1}] !",ConsoleColor.Green);

						Context.SaveChanges();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] UPDATED VALUE to VALUE 1 [{Entity.EntityValue1}] !",ConsoleColor.Green);
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
		// !!! Pouzivaju sa CONCURRENCY TOKENS na zaklade ktorych ENTITY FRAMEWORK CORE identifikuje vznik CONCURRENCY CONFLICT a hodi EXCEPTION [DbUpdateConcurrencyException].
		public static void UpdateMultipleConcurrencyTokensFluentAPIEntityTask2(int TaskID, int Step, int SleepTime, int EntityID)
		{
			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityMultipleConcurrencyTokensFluentAPI	Entity=Context.EntitiesMultipleConcurrencyTokensFluentAPI.Where(P => P.EntityID==EntityID).First();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] READ VALUE 1 [{Entity.EntityValue1}] and READ VALUE 2 [{Entity.EntityValue2}] !",ConsoleColor.Green);

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] WAITING STARTED !",ConsoleColor.Yellow);

						Thread.Sleep(SleepTime);

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] WAITING FINISHED !",ConsoleColor.Yellow);

						Entity.EntityValue2+=Step;

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] ADDING VALUE [{Step}] to VALUE 2 [{Entity.EntityValue2}] !",ConsoleColor.Green);

						Context.SaveChanges();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] UPDATED VALUE to VALUE 2 [{Entity.EntityValue2}] !",ConsoleColor.Green);
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
		public static void TestUpdateMultipleConcurrencyTokensFluentAPI()
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

						CEntityMultipleConcurrencyTokensFluentAPI[]	Entities=Context.EntitiesMultipleConcurrencyTokensFluentAPI.ToArray();

						CEntityMultipleConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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

						CEntityMultipleConcurrencyTokensFluentAPI	Entity=new CEntityMultipleConcurrencyTokensFluentAPI(100,200);

						Context.EntitiesMultipleConcurrencyTokensFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityMultipleConcurrencyTokensFluentAPI[]	Entities=Context.EntitiesMultipleConcurrencyTokensFluentAPI.ToArray();

						CEntityMultipleConcurrencyTokensFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

				Task											Task1=new Task(() => UpdateMultipleConcurrencyTokensFluentAPIEntityTask1(1,10,500,ID));
				Task											Task2=new Task(() => UpdateMultipleConcurrencyTokensFluentAPIEntityTask2(2,20,1000,ID));

				Task1.Start();
				Task2.Start();

				Task.WaitAll(Task1,Task2);

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityMultipleConcurrencyTokensFluentAPI[]	Entities=Context.EntitiesMultipleConcurrencyTokensFluentAPI.ToArray();

						CEntityMultipleConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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

						CEntityMultipleConcurrencyTokensFluentAPI	Entity=Context.EntitiesMultipleConcurrencyTokensFluentAPI.Where(P => P.EntityID==ID).First();

						Context.EntitiesMultipleConcurrencyTokensFluentAPI.Remove(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
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

						CEntityMultipleConcurrencyTokensFluentAPI[]	Entities=Context.EntitiesMultipleConcurrencyTokensFluentAPI.ToArray();

						CEntityMultipleConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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
		// !!! Pouzivaju sa CONCURRENCY TOKENS na zaklade ktorych ENTITY FRAMEWORK CORE identifikuje vznik CONCURRENCY CONFLICT a hodi EXCEPTION [DbUpdateConcurrencyException].
		public static void DeleteDeleteConcurrencyTokensFluentAPIEntityTask(int TaskID, int SleepTime, int EntityID)
		{
			try
			{
				using(CDBContext Context=new CDBContext(true))
				{
					try
					{
						CEntityConcurrencyTokensFluentAPI		Entity=Context.EntitiesConcurrencyTokensFluentAPI.Where(P => P.EntityID==EntityID).First();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] READ VALUE [{Entity.EntityValue}] !",ConsoleColor.Green);

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] WAITING STARTED !",ConsoleColor.Yellow);

						Thread.Sleep(SleepTime);

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] WAITING FINISHED !",ConsoleColor.Yellow);

						Context.EntitiesConcurrencyTokensFluentAPI.Remove(Entity);

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] DELETING ENTITY [{Entity.EntityID}] !",ConsoleColor.Green);

						Context.SaveChanges();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] DELETED ENTITY [{Entity.EntityID}] !",ConsoleColor.Green);
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
		// !!! Pouzivaju sa CONCURRENCY TOKENS na zaklade ktorych ENTITY FRAMEWORK CORE identifikuje vznik CONCURRENCY CONFLICT a hodi EXCEPTION [DbUpdateConcurrencyException].
		public static void UpdateDeleteConcurrencyTokensFluentAPIEntityTask(int TaskID, int Step, int SleepTime, int EntityID)
		{
			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityConcurrencyTokensFluentAPI		Entity=Context.EntitiesConcurrencyTokensFluentAPI.Where(P => P.EntityID==EntityID).First();

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
		public static void TestDeleteConcurrencyTokensFluentAPI()
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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

						CEntityConcurrencyTokensFluentAPI		Entity=new CEntityConcurrencyTokensFluentAPI(100);

						Context.EntitiesConcurrencyTokensFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

				Task											Task1=new Task(() => DeleteDeleteConcurrencyTokensFluentAPIEntityTask(1,500,ID));
				Task											Task2=new Task(() => UpdateDeleteConcurrencyTokensFluentAPIEntityTask(2,20,1000,ID));

				Task1.Start();
				Task2.Start();

				Task.WaitAll(Task1,Task2);

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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

						CEntityConcurrencyTokensFluentAPI		Entity=Context.EntitiesConcurrencyTokensFluentAPI.Where(P => P.EntityID==ID).FirstOrDefault();

						if (Entity!=null)
						{
							Context.EntitiesConcurrencyTokensFluentAPI.Remove(Entity);

							// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
							int									NumberOfModifiedEntities=Context.SaveChanges();

							if (NumberOfModifiedEntities>0)
							{
								CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
							}
							else
							{
								CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
							}
						}
						else
						{
							CConsoleHelpers.WriteLine($"NO ENTITIES to DELETE !",ConsoleColor.Blue);
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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
		public static void FixingConcurrencyConflictsTask(int TaskID, int Step, int SleepTime, int EntityID)
		{
			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityConcurrencyTokensFluentAPI		Entity=Context.EntitiesConcurrencyTokensFluentAPI.Where(P => P.EntityID==EntityID).First();

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

						try
						{
							// !!!!! PROPERTY [IReadOnlyList<EntityEntry> DbUpdateConcurrencyException.Entries] obsahuje zoznam vsetkych ENTITY ENTRIES, ktore sposobili CONCURRENCY CONFLICT.
							foreach(EntityEntry Entry in E.Entries)
							{
								CEntityConcurrencyTokensFluentAPI	Entity=(CEntityConcurrencyTokensFluentAPI) Entry.Entity;

								// !!! Nacita sa CURRENT VALUE CONCURRENCY TOKEN PROPERTY z DATABASE.
								// !!!!! Pri citani je NUTNE pouzit LINQ OPERATOR [AsNoTracking], aby doslo k realnemu citaniu RECORD z DATABASE, a nie len vrateniu existujucej ENTITY z DB CONTEXT, ktora obsahuje neaktualizovanu (povodnu) VALUE CONCURRENCY TOKEN PROPERTY.
								CEntityConcurrencyTokensFluentAPI	UpdatedEntity=Context.EntitiesConcurrencyTokensFluentAPI.AsNoTracking().Where(P => P.EntityID==EntityID).First();

								// !!! Ziska sa REFERENCE na PROPERTY ENTRY UPDATED ENTITY, ktorej UPDATE ZLYHAL.
								PropertyEntry					ConcurrencyTokenPropertyInOriginalEntry=Entry.Property(nameof(CEntityConcurrencyTokensFluentAPI.EntityValue));
								object							OriginalConcurrencyTokenPropertyValue=ConcurrencyTokenPropertyInOriginalEntry.OriginalValue;

								// !!! Na vykonanie FIXING CONCURRENCY ERROR sa vykona zmena ORIGINAL VALUE CONCURRENCY TOKEN PROPERTY na VALUE, na ktoru CONCURRENCY TOKEN PROPERTY modifikoval iny THREAD.
								ConcurrencyTokenPropertyInOriginalEntry.OriginalValue=UpdatedEntity.EntityValue;

								CConsoleHelpers.WriteLine($"TASK [{TaskID}] UPDATING ORIGINAL VALUE [{OriginalConcurrencyTokenPropertyValue}] to NEW VALUE [{UpdatedEntity.EntityValue}] !",ConsoleColor.Green);

								// !!! Vykona sa opakovany pokus o UPDATE v DATABASE.
								Context.SaveChanges();

								CConsoleHelpers.WriteLine($"TASK [{TaskID}] UPDATED FIXED VALUE to VALUE [{Entity.EntityValue}] !",ConsoleColor.Green);
							}
						}
						catch(DbUpdateConcurrencyException Ex)
						{
							CConsoleHelpers.WriteLine($"TASK [{TaskID}] DB UPDATE CONCURRENCY EXCEPTION [{Ex.Message}] !",ConsoleColor.Red);
						}
						catch(Exception Ex)
						{
							CConsoleHelpers.WriteLine($"TASK [{TaskID}] EXCEPTION [{Ex.Message}] !",ConsoleColor.Red);
						}
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
		// !!! METHOD demonstruje FIXING CONCURRENCY CONFLICTS.
		public static void TestFixingConcurrencyConflicts()
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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

						CEntityConcurrencyTokensFluentAPI		Entity=new CEntityConcurrencyTokensFluentAPI(100);

						Context.EntitiesConcurrencyTokensFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

				Task											Task1=new Task(() => FixingConcurrencyConflictsTask(1,10,500,ID));
				Task											Task2=new Task(() => FixingConcurrencyConflictsTask(2,20,1000,ID));

				Task1.Start();
				Task2.Start();

				Task.WaitAll(Task1,Task2);

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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

						CEntityConcurrencyTokensFluentAPI		Entity=Context.EntitiesConcurrencyTokensFluentAPI.Where(P => P.EntityID==ID).First();

						Context.EntitiesConcurrencyTokensFluentAPI.Remove(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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
		public static void FixingLongTermConcurrencyConflictsTask(int TaskID, int Step, int SleepTime, int EntityID)
		{
			try
			{
				int												OriginalValue=0;

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityConcurrencyTokensFluentAPI		Entity=Context.EntitiesConcurrencyTokensFluentAPI.Where(P => P.EntityID==EntityID).First();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] READ VALUE [{Entity.EntityID}] !",ConsoleColor.Green);

						OriginalValue=Entity.EntityValue;
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

				// !!!!! Simuluje zobrazenie VALUES na FRONTEND, kde USER moze vykonat a potvrdit zmeny v radoch minut ci hodin.
				Thread.Sleep(SleepTime);

				// !!!!! Na simulaciu LONG TERM CONCURRENCY CONFLICT sa vytvori novy DB CONTEXT, ktory simuluje novu OPERATION, ktore prebieha dlhy cas (minuty) po nacinani ORIGINAL VALUES.
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityConcurrencyTokensFluentAPI		Entity=Context.EntitiesConcurrencyTokensFluentAPI.Where(P => P.EntityID==EntityID).First();

						CConsoleHelpers.WriteLine($"TASK [{TaskID}] READ VALUE [{Entity.EntityID}] in NEW CONTEXT !",ConsoleColor.Green);

						Entity.EntityValue=(OriginalValue+Step);

						// !!! Pre ENTITY sa ziska jej ENTRY.
						EntityEntry<CEntityConcurrencyTokensFluentAPI>	EntryForEntity=Context.Entry(Entity);

						// !!! Z ENTRY sa ziska CONCURRENCY TOKEN PROPERTY.
						PropertyEntry<CEntityConcurrencyTokensFluentAPI,int>	ConcurrencyTokenProperty=EntryForEntity.Property(P => P.EntityValue);

						// !!!!! CONCURRENCY TOKEN PROPERTY MUSI byt nastavena na ORIGINAL VALUE, aby doslo k detekcii CONCURRENCY CONFLICT.
						// !!!!! Interne ENTITY FRAMEWORK vykona UPDATE s WHERE CLAUSE, kde sa testuje ci CONCURRENCY TOKEN PROPERTY ma stale ORIGINAL VALUE. Ak nie a teda UPDATE nezmeni ani 1 RECORD, dojde k vzniku EXCEPTION [DbUpdateConcurrencyException].
						ConcurrencyTokenProperty.OriginalValue=OriginalValue;

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
		// !!! METHOD demonstruje FIXING LONG TERM CONCURRENCY CONFLICTS.
		public static void TestFixingLongTermConcurrencyConflicts()
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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

						CEntityConcurrencyTokensFluentAPI		Entity=new CEntityConcurrencyTokensFluentAPI(100);

						Context.EntitiesConcurrencyTokensFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

				Task											Task1=new Task(() => FixingLongTermConcurrencyConflictsTask(1,10,500,ID));
				Task											Task2=new Task(() => FixingLongTermConcurrencyConflictsTask(2,20,1000,ID));

				Task1.Start();
				Task2.Start();

				Task.WaitAll(Task1,Task2);

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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

						CEntityConcurrencyTokensFluentAPI		Entity=Context.EntitiesConcurrencyTokensFluentAPI.Where(P => P.EntityID==ID).First();

						Context.EntitiesConcurrencyTokensFluentAPI.Remove(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
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

						CEntityConcurrencyTokensFluentAPI[]		Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

						CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
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
			//TestSelectTestEntity();
			//TestUsingScalarValuedUDF();
			//TestComputedColumns();
			//TesDefaultValueColumns();
			//TestDBGeneratedPropertiesDataAnnotations();
			//TestDBGeneratedPropertiesFluentAPI();
			//TestUpdateOptimisticConcurrency();
			//TestUpdateConcurrencyTokensDataAnnotations();
			//TestUpdateConcurrencyTokensFluentAPI();
			//TestUpdateMultipleConcurrencyTokensFluentAPI();
			//TestDeleteConcurrencyTokensFluentAPI();
			//TestFixingConcurrencyConflicts();
			//TestFixingLongTermConcurrencyConflicts();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------