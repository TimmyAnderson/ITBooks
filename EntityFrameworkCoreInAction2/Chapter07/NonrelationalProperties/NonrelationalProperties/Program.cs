using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Storage;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace NonrelationalProperties
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

			CEntityDifferentConfigurations						EntityDifferentConfigurations1=new CEntityDifferentConfigurations(100,null,null,"BBB","CCC",new DateTime(2001,1,1),123.123);
			CEntityDifferentConfigurations						EntityDifferentConfigurations2=new CEntityDifferentConfigurations(200,300,"DDD","EEE","FFF",new DateTime(2002,2,2),456.456);

			Context.EntitiesDifferentConfigurations.Add(EntityDifferentConfigurations1);
			Context.EntitiesDifferentConfigurations.Add(EntityDifferentConfigurations2);

			CEntityNotExcluded									EntityNotExcluded11=new CEntityNotExcluded("NOT EXCLUDED CLASS VALUE AAA");
			CEntityNotExcluded									EntityNotExcluded12=new CEntityNotExcluded("NOT EXCLUDED CLASS VALUE BBB");

			CEntityExcludedDataAnnotations						EntityExcludedDataAnnotations1=new CEntityExcludedDataAnnotations("EXCLUDED CLASS VALUE AAA");
			CEntityExcludedDataAnnotations						EntityExcludedDataAnnotations2=new CEntityExcludedDataAnnotations("EXCLUDED CLASS VALUE BBB");

			CEntityNotMappedDataAnnotations						EntityNotMappedDataAnnotations1=new CEntityNotMappedDataAnnotations("VALUE AAA","EXCLUDED PROPERTY VALUE AAA",EntityNotExcluded11,EntityExcludedDataAnnotations1);
			CEntityNotMappedDataAnnotations						EntityNotMappedDataAnnotations2=new CEntityNotMappedDataAnnotations("VALUE BBB","EXCLUDED PROPERTY VALUE BBB",EntityNotExcluded12,EntityExcludedDataAnnotations2);

			Context.EntitiesNotMappedDataAnnotations.Add(EntityNotMappedDataAnnotations1);
			Context.EntitiesNotMappedDataAnnotations.Add(EntityNotMappedDataAnnotations2);

			CEntityNotExcluded									EntityNotExcluded21=new CEntityNotExcluded("NOT EXCLUDED CLASS VALUE AAA");
			CEntityNotExcluded									EntityNotExcluded22=new CEntityNotExcluded("NOT EXCLUDED CLASS VALUE BBB");

			CEntityExcludedFluentAPI							EntityExcludedFluentAPI1=new CEntityExcludedFluentAPI("EXCLUDED CLASS VALUE AAA");
			CEntityExcludedFluentAPI							EntityExcludedFluentAPI2=new CEntityExcludedFluentAPI("EXCLUDED CLASS VALUE BBB");

			CEntityNotMappedFluentAPI							EntityNotMappedFluentAPI1=new CEntityNotMappedFluentAPI("VALUE AAA","EXCLUDED PROPERTY VALUE AAA",EntityNotExcluded21,EntityExcludedFluentAPI1);
			CEntityNotMappedFluentAPI							EntityNotMappedFluentAPI2=new CEntityNotMappedFluentAPI("VALUE BBB","EXCLUDED PROPERTY VALUE BBB",EntityNotExcluded22,EntityExcludedFluentAPI2);

			Context.EntitiesNotMappedFluentAPI.Add(EntityNotMappedFluentAPI1);
			Context.EntitiesNotMappedFluentAPI.Add(EntityNotMappedFluentAPI2);

			CEntityColumnPropertiesDataAnnotations				EntityColumnPropertiesDataAnnotations1=new CEntityColumnPropertiesDataAnnotations("AAA","BBB",new DateTime(2001,1,1),100);
			CEntityColumnPropertiesDataAnnotations				EntityColumnPropertiesDataAnnotations2=new CEntityColumnPropertiesDataAnnotations("CCC","DDD",new DateTime(2002,2,2),200);

			Context.EntitiesColumnPropertiesDataAnnotations.Add(EntityColumnPropertiesDataAnnotations1);
			Context.EntitiesColumnPropertiesDataAnnotations.Add(EntityColumnPropertiesDataAnnotations2);

			CEntityColumnPropertiesFluentAPI					EntityColumnPropertiesFluentAPI1=new CEntityColumnPropertiesFluentAPI("AAA","BBB",new DateTime(2001,1,1),100,"CCC",123.123);
			CEntityColumnPropertiesFluentAPI					EntityColumnPropertiesFluentAPI2=new CEntityColumnPropertiesFluentAPI("DDD","EEE",new DateTime(2002,2,2),200,"FFF",456.456);

			Context.EntitiesColumnPropertiesFluentAPI.Add(EntityColumnPropertiesFluentAPI1);
			Context.EntitiesColumnPropertiesFluentAPI.Add(EntityColumnPropertiesFluentAPI2);

			CEntityUsingValueConversions						EntityUsingValueConversions1=new CEntityUsingValueConversions("One",EEnumType.E_ONE,EEnumType.E_ONE,EEnumType.E_ONE);
			CEntityUsingValueConversions						EntityUsingValueConversions2=new CEntityUsingValueConversions("Two",EEnumType.E_TWO,EEnumType.E_TWO,EEnumType.E_TWO);
			CEntityUsingValueConversions						EntityUsingValueConversions3=new CEntityUsingValueConversions("Three",EEnumType.E_THREE,EEnumType.E_THREE,EEnumType.E_THREE);

			Context.EntitiesUsingValueConversions.Add(EntityUsingValueConversions1);
			Context.EntitiesUsingValueConversions.Add(EntityUsingValueConversions2);
			Context.EntitiesUsingValueConversions.Add(EntityUsingValueConversions3);

			CEntityPrimaryKeyConventions						EntityPrimaryKeyConventions1=new CEntityPrimaryKeyConventions("111");
			CEntityPrimaryKeyConventions						EntityPrimaryKeyConventions2=new CEntityPrimaryKeyConventions("222");

			Context.EntitiesPrimaryKeyConventions.Add(EntityPrimaryKeyConventions1);
			Context.EntitiesPrimaryKeyConventions.Add(EntityPrimaryKeyConventions2);

			CEntityPrimaryKeyDataAnnotations					EntityPrimaryKeyDataAnnotations1=new CEntityPrimaryKeyDataAnnotations("111");
			CEntityPrimaryKeyDataAnnotations					EntityPrimaryKeyDataAnnotations2=new CEntityPrimaryKeyDataAnnotations("222");

			Context.EntitiesPrimaryKeyDataAnnotations.Add(EntityPrimaryKeyDataAnnotations1);
			Context.EntitiesPrimaryKeyDataAnnotations.Add(EntityPrimaryKeyDataAnnotations2);

			CEntityPrimaryKeyFluentAPI							EntityPrimaryKeyFluentAPI1=new CEntityPrimaryKeyFluentAPI(1,101,"111");
			CEntityPrimaryKeyFluentAPI							EntityPrimaryKeyFluentAPI2=new CEntityPrimaryKeyFluentAPI(2,102,"222");

			Context.EntitiesPrimaryKeyFluentAPI.Add(EntityPrimaryKeyFluentAPI1);
			Context.EntitiesPrimaryKeyFluentAPI.Add(EntityPrimaryKeyFluentAPI2);

			CEntityDataForKeylessView							DataForKeylessView1=new CEntityDataForKeylessView(111,"AAA");
			CEntityDataForKeylessView							DataForKeylessView2=new CEntityDataForKeylessView(222,"BBB");

			Context.EntitiesDataForKeylessView.Add(DataForKeylessView1);
			Context.EntitiesDataForKeylessView.Add(DataForKeylessView2);

			// !!! Vytvori sa CUSTOM VIEW na ktory sa namapuje KEYLESS ENTITY 'CEntityKeylessDataAnnotations'.
			Context.Database.ExecuteSqlRaw(@"CREATE VIEW View_Keyless1 AS SELECT IntValue AS MyInt, StringValue AS MyString FROM EntitiesDataForKeylessView");

			// !!! Vytvori sa CUSTOM VIEW na ktory sa namapuje KEYLESS ENTITY 'CEntityKeylessFluentAPI'.
			Context.Database.ExecuteSqlRaw(@"CREATE VIEW View_Keyless2 AS SELECT IntValue AS MyInt, StringValue AS MyString FROM EntitiesDataForKeylessView");

			CEntityIndexesDataAnnotations						IndexesDataAnnotations1=new CEntityIndexesDataAnnotations("AAA 111","BBB 111","CCC 111","DDD 111");
			CEntityIndexesDataAnnotations						IndexesDataAnnotations2=new CEntityIndexesDataAnnotations("AAA 222","BBB 222","CCC 222","DDD 222");
			CEntityIndexesDataAnnotations						IndexesDataAnnotations3=new CEntityIndexesDataAnnotations("AAA 333","BBB 333","CCC 333","DDD 333");

			Context.EntitiesIndexesDataAnnotations.Add(IndexesDataAnnotations1);
			Context.EntitiesIndexesDataAnnotations.Add(IndexesDataAnnotations2);
			Context.EntitiesIndexesDataAnnotations.Add(IndexesDataAnnotations3);

			CEntityIndexesFluentAPI								IndexesFluentAPI1=new CEntityIndexesFluentAPI("AAA 111","BBB 111","CCC 111","DDD 111",1);
			CEntityIndexesFluentAPI								IndexesFluentAPI2=new CEntityIndexesFluentAPI("AAA 222","BBB 222","CCC 222","DDD 222",2);
			CEntityIndexesFluentAPI								IndexesFluentAPI3=new CEntityIndexesFluentAPI("AAA 333","BBB 333","CCC 333","DDD 333",3);

			Context.EntitiesIndexesFluentAPI.Add(IndexesFluentAPI1);
			Context.EntitiesIndexesFluentAPI.Add(IndexesFluentAPI2);
			Context.EntitiesIndexesFluentAPI.Add(IndexesFluentAPI3);

			CEntityCustomNamesDataAnnotations					CustomNamesDataAnnotations1=new CEntityCustomNamesDataAnnotations("AAA");
			CEntityCustomNamesDataAnnotations					CustomNamesDataAnnotations2=new CEntityCustomNamesDataAnnotations("BBB");

			Context.EntitiesCustomNamesDataAnnotations.Add(CustomNamesDataAnnotations1);
			Context.EntitiesCustomNamesDataAnnotations.Add(CustomNamesDataAnnotations2);

			CEntityCustomNamesFluentAPI							CustomNamesFluentAPI1=new CEntityCustomNamesFluentAPI("AAA");
			CEntityCustomNamesFluentAPI							CustomNamesFluentAPI2=new CEntityCustomNamesFluentAPI("BBB");

			Context.EntitiesCustomNamesFluentAPI.Add(CustomNamesFluentAPI1);
			Context.EntitiesCustomNamesFluentAPI.Add(CustomNamesFluentAPI2);

			CEntityQueryFilter									QueryFilter1=new CEntityQueryFilter(1);
			CEntityQueryFilter									QueryFilter2=new CEntityQueryFilter(2);
			CEntityQueryFilter									QueryFilter3=new CEntityQueryFilter(3);
			CEntityQueryFilter									QueryFilter4=new CEntityQueryFilter(4);
			CEntityQueryFilter									QueryFilter5=new CEntityQueryFilter(5);
			CEntityQueryFilter									QueryFilter6=new CEntityQueryFilter(6);

			Context.EntitiesQueryFilter.Add(QueryFilter1);
			Context.EntitiesQueryFilter.Add(QueryFilter2);
			Context.EntitiesQueryFilter.Add(QueryFilter3);
			Context.EntitiesQueryFilter.Add(QueryFilter4);
			Context.EntitiesQueryFilter.Add(QueryFilter5);
			Context.EntitiesQueryFilter.Add(QueryFilter6);

			CEntityShadowProperties								ShadowProperties1=new CEntityShadowProperties("AAA");
			CEntityShadowProperties								ShadowProperties2=new CEntityShadowProperties("BBB");
			CEntityShadowProperties								ShadowProperties3=new CEntityShadowProperties("CCC");

			Context.EntitiesShadowProperties.Add(ShadowProperties1);
			Context.EntitiesShadowProperties.Add(ShadowProperties2);
			Context.EntitiesShadowProperties.Add(ShadowProperties3);

			// !!!!! Pristup k SHADOW PROPERTIES je mozny, az ked je ENTITY TRACKED v DB CONTEXT, pretoze VALUES SHADOW PROPERTIES su ukladane do TRACKED ENTITY DATA.
			EntityEntry<CEntityShadowProperties>				EntryShadowProperties1=Context.Entry<CEntityShadowProperties>(ShadowProperties1);
			EntityEntry<CEntityShadowProperties>				EntryShadowProperties2=Context.Entry<CEntityShadowProperties>(ShadowProperties2);
			EntityEntry<CEntityShadowProperties>				EntryShadowProperties3=Context.Entry<CEntityShadowProperties>(ShadowProperties3);

			EntryShadowProperties1.Property("ShadowPropertyString").CurrentValue="SHADOW AAA";
			EntryShadowProperties1.Property("ShadowPropertyInt").CurrentValue=100;

			EntryShadowProperties2.Property("ShadowPropertyString").CurrentValue="SHADOW BBB";
			EntryShadowProperties2.Property("ShadowPropertyInt").CurrentValue=200;

			EntryShadowProperties3.Property("ShadowPropertyString").CurrentValue="SHADOW CCC";
			EntryShadowProperties3.Property("ShadowPropertyInt").CurrentValue=300;

			CEntityBackingFieldsConventions						BackingFieldsConventions1=new CEntityBackingFieldsConventions("AAA 111","AAA 222","AAA 333");
			CEntityBackingFieldsConventions						BackingFieldsConventions2=new CEntityBackingFieldsConventions("BBB 111","BBB 222","BBB 333");

			Context.EntitiesBackingFieldsConventions.Add(BackingFieldsConventions1);
			Context.EntitiesBackingFieldsConventions.Add(BackingFieldsConventions2);

			CEntityBackingFieldsDataAnnotations					BackingFieldsDataAnnotations1=new CEntityBackingFieldsDataAnnotations("AAA 111","AAA 222","AAA 333");
			CEntityBackingFieldsDataAnnotations					BackingFieldsDataAnnotations2=new CEntityBackingFieldsDataAnnotations("BBB 111","BBB 222","BBB 333");

			Context.EntitiesBackingFieldsDataAnnotations.Add(BackingFieldsDataAnnotations1);
			Context.EntitiesBackingFieldsDataAnnotations.Add(BackingFieldsDataAnnotations2);

			CEntityBackingFieldsFluentAPI						BackingFieldsFluentAPI1=new CEntityBackingFieldsFluentAPI("AAA 111","AAA 222","AAA 333","AAA 444");
			CEntityBackingFieldsFluentAPI						BackingFieldsFluentAPI2=new CEntityBackingFieldsFluentAPI("BBB 111","BBB 222","BBB 333","BBB 444");

			Context.EntitiesBackingFieldsFluentAPI.Add(BackingFieldsFluentAPI1);
			Context.EntitiesBackingFieldsFluentAPI.Add(BackingFieldsFluentAPI2);

			CEntityBackingFieldsAccessModes						BackingFieldsAccessModes1=new CEntityBackingFieldsAccessModes("AAA 111","AAA 222","AAA 333","AAA 444","AAA 555","AAA 666");
			CEntityBackingFieldsAccessModes						BackingFieldsAccessModes2=new CEntityBackingFieldsAccessModes("BBB 111","BBB 222","BBB 333","BBB 444","BBB 555","BBB 666");

			Context.EntitiesBackingFieldsAccessModes.Add(BackingFieldsAccessModes1);
			Context.EntitiesBackingFieldsAccessModes.Add(BackingFieldsAccessModes2);

			CEntityAutoConfiguration1							AutoConfiguration11=new CEntityAutoConfiguration1("AAA",111,111.111);
			CEntityAutoConfiguration1							AutoConfiguration12=new CEntityAutoConfiguration1("BBB",222,222.222);

			Context.EntitiesAutoConfiguration1.Add(AutoConfiguration11);
			Context.EntitiesAutoConfiguration1.Add(AutoConfiguration12);

			CEntityAutoConfiguration2							AutoConfiguration21=new CEntityAutoConfiguration2("CCC",333,333.333);
			CEntityAutoConfiguration2							AutoConfiguration22=new CEntityAutoConfiguration2("DDD",444,444.444);

			Context.EntitiesAutoConfiguration2.Add(AutoConfiguration21);
			Context.EntitiesAutoConfiguration2.Add(AutoConfiguration22);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void PrintProperty(IProperty Property)
		{
			StoreObjectIdentifier?								ObjectIdentifier=StoreObjectIdentifier.Create(Property.DeclaringEntityType,StoreObjectType.Table);

			CConsoleHelpers.WriteLine($"NAME [{Property.Name}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"COLUMN NAME [{Property.GetColumnName(ObjectIdentifier.Value)}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"COLUMN TYPE [{Property.GetColumnType()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"NULLABLE [{Property.IsNullable}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"MAX LENGTH [{Property.GetMaxLength()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"PRECISION [{Property.GetPrecision()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"SCALE [{Property.GetScale()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"IS UNICODE [{Property.IsUnicode()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"IS SHADOW PROPERTY [{Property.IsShadowProperty()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"FIELD INFO NAME [{Property.FieldInfo?.Name}].",ConsoleColor.Magenta);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void PrintIndex(IIndex Index)
		{
			CConsoleHelpers.WriteLine($"NAME [{Index.Name}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"DATABASE NAME [{Index.GetDatabaseName()}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"IS UNIQUE [{Index.IsUnique}].",ConsoleColor.Magenta);
			CConsoleHelpers.WriteLine($"FILTER [{Index.GetFilter()}].",ConsoleColor.Magenta);

			IProperty[]											Properties=Index.Properties.ToArray();

			foreach(IProperty Property in Properties)
			{
				CConsoleHelpers.WriteLine($"\tNAME [{Property.Name}].",ConsoleColor.Magenta);
			}
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
		private static void TestSelectEntityDifferentConfigurations()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityDifferentConfigurations[]		Entities=Context.EntitiesDifferentConfigurations.ToArray();

						CEntityDifferentConfigurations.PrintToConsole(Entities);
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
		private static void TestNotMappedDataAnnotations()
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

						CEntityNotMappedDataAnnotations[]		Entities=Context.EntitiesNotMappedDataAnnotations.Include(P => P.NotExcludedClassValue).ToArray();

						CEntityNotMappedDataAnnotations.PrintToConsole(Entities);
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

						CEntityNotExcluded						EntityNotExcluded=new CEntityNotExcluded("NEW NOT EXCLUDED CLASS VALUE");
						CEntityExcludedDataAnnotations			EntityExcludedDataAnnotations=new CEntityExcludedDataAnnotations("NEW EXCLUDED CLASS VALUE");
						CEntityNotMappedDataAnnotations			EntityNotMappedDataAnnotations=new CEntityNotMappedDataAnnotations("NEW VALUE","NEW EXCLUDED PROPERTY VALUE",EntityNotExcluded,EntityExcludedDataAnnotations);

						Context.EntitiesNotMappedDataAnnotations.Add(EntityNotMappedDataAnnotations);

						string									TextEntityNotMappedDataAnnotations=EntityNotMappedDataAnnotations.Print(null);

						CConsoleHelpers.Write(TextEntityNotMappedDataAnnotations,ConsoleColor.Blue);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=EntityNotMappedDataAnnotations.ID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
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

						CEntityNotMappedDataAnnotations[]		Entities=Context.EntitiesNotMappedDataAnnotations.Include(P => P.NotExcludedClassValue).ToArray();

						CEntityNotMappedDataAnnotations.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityNotMappedDataAnnotations			Entity=Context.EntitiesNotMappedDataAnnotations.Where(P => P.ID==ID).First();

						Context.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityNotMappedDataAnnotations[]		Entities=Context.EntitiesNotMappedDataAnnotations.Include(P => P.NotExcludedClassValue).ToArray();

						CEntityNotMappedDataAnnotations.PrintToConsole(Entities);
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
		private static void TestNotMappedFluentAPI()
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

						CEntityNotMappedFluentAPI[]				Entities=Context.EntitiesNotMappedFluentAPI.Include(P => P.NotExcludedClassValue).ToArray();

						CEntityNotMappedFluentAPI.PrintToConsole(Entities);
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

						CEntityNotExcluded						EntityNotExcluded=new CEntityNotExcluded("NEW NOT EXCLUDED CLASS VALUE");
						CEntityExcludedFluentAPI				EntityExcludedFluentAPI=new CEntityExcludedFluentAPI("NEW EXCLUDED CLASS VALUE");
						CEntityNotMappedFluentAPI				EntityNotMappedFluentAPI=new CEntityNotMappedFluentAPI("NEW VALUE","NEW EXCLUDED PROPERTY VALUE",EntityNotExcluded,EntityExcludedFluentAPI);

						Context.EntitiesNotMappedFluentAPI.Add(EntityNotMappedFluentAPI);

						string									TextEntityNotMappedFluentAPI=EntityNotMappedFluentAPI.Print(null);

						CConsoleHelpers.Write(TextEntityNotMappedFluentAPI,ConsoleColor.Blue);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=EntityNotMappedFluentAPI.ID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
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

						CEntityNotMappedFluentAPI[]				Entities=Context.EntitiesNotMappedFluentAPI.Include(P => P.NotExcludedClassValue).ToArray();

						CEntityNotMappedFluentAPI.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityNotMappedFluentAPI				Entity=Context.EntitiesNotMappedFluentAPI.Where(P => P.ID==ID).First();

						Context.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityNotMappedFluentAPI[]				Entities=Context.EntitiesNotMappedFluentAPI.Include(P => P.NotExcludedClassValue).ToArray();

						CEntityNotMappedFluentAPI.PrintToConsole(Entities);
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
		private static void TestColumnPropertiesDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityColumnPropertiesDataAnnotations[]	Entities=Context.EntitiesColumnPropertiesDataAnnotations.ToArray();

						CEntityColumnPropertiesDataAnnotations.PrintToConsole(Entities);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityColumnPropertiesDataAnnotations));
						IProperty								PropertyStringNonNull=EntityType.FindProperty(nameof(CEntityColumnPropertiesDataAnnotations.StringNonNull));
						IProperty								PropertyStringWithMaxLength=EntityType.FindProperty(nameof(CEntityColumnPropertiesDataAnnotations.StringWithMaxLength));
						IProperty								PropertyDateTimeWithSQLTypeDATE=EntityType.FindProperty(nameof(CEntityColumnPropertiesDataAnnotations.DateTimeWithSQLTypeDATE));
						IProperty								PropertyIntRenamed=EntityType.FindProperty(nameof(CEntityColumnPropertiesDataAnnotations.IntRenamed));

						PrintProperty(PropertyStringNonNull);

						CConsoleHelpers.WriteLineSeparator();
						
						PrintProperty(PropertyStringWithMaxLength);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyDateTimeWithSQLTypeDATE);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyIntRenamed);
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
		private static void TestColumnPropertiesDataFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityColumnPropertiesFluentAPI[]		Entities=Context.EntitiesColumnPropertiesFluentAPI.ToArray();

						CEntityColumnPropertiesFluentAPI.PrintToConsole(Entities);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityColumnPropertiesFluentAPI));
						IProperty								PropertyStringNonNull=EntityType.FindProperty(nameof(CEntityColumnPropertiesFluentAPI.StringNonNull));
						IProperty								PropertyStringWithMaxLength=EntityType.FindProperty(nameof(CEntityColumnPropertiesFluentAPI.StringWithMaxLength));
						IProperty								PropertyDateTimeWithSQLTypeDATE=EntityType.FindProperty(nameof(CEntityColumnPropertiesFluentAPI.DateTimeWithSQLTypeDATE));
						IProperty								PropertyIntRenamed=EntityType.FindProperty(nameof(CEntityColumnPropertiesFluentAPI.IntRenamed));
						IProperty								PropertyStringNonUnicode=EntityType.FindProperty(nameof(CEntityColumnPropertiesFluentAPI.StringNonUnicode));
						IProperty								PropertyDoubleWithLimitedPrecision=EntityType.FindProperty(nameof(CEntityColumnPropertiesFluentAPI.DoubleWithLimitedPrecision));

						PrintProperty(PropertyStringNonNull);

						CConsoleHelpers.WriteLineSeparator();
						
						PrintProperty(PropertyStringWithMaxLength);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyDateTimeWithSQLTypeDATE);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyIntRenamed);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyStringNonUnicode);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyDoubleWithLimitedPrecision);
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
		private static void TestUsingValueConversions()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityUsingValueConversions[]			Entities=Context.EntitiesUsingValueConversions.ToArray();

						CEntityUsingValueConversions.PrintToConsole(Entities);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityUsingValueConversions));
						IProperty								PropertyValue=EntityType.FindProperty(nameof(CEntityUsingValueConversions.Value));
						IProperty								PropertyEnumTypeNoConversion=EntityType.FindProperty(nameof(CEntityUsingValueConversions.EnumTypeNoConversion));
						IProperty								PropertyEnumTypeWithConversion1=EntityType.FindProperty(nameof(CEntityUsingValueConversions.EnumTypeWithConversion1));
						IProperty								PropertyEnumTypeWithConversion2=EntityType.FindProperty(nameof(CEntityUsingValueConversions.EnumTypeWithConversion2));

						PrintProperty(PropertyValue);

						CConsoleHelpers.WriteLineSeparator();
						
						PrintProperty(PropertyEnumTypeNoConversion);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyEnumTypeWithConversion1);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyEnumTypeWithConversion2);
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
		private static void TestPrimaryKeyConventions()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityPrimaryKeyConventions[]			Entities=Context.EntitiesPrimaryKeyConventions.ToArray();

						CEntityPrimaryKeyConventions.PrintToConsole(Entities);
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
		private static void TestPrimaryKeyDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityPrimaryKeyDataAnnotations[]		Entities=Context.EntitiesPrimaryKeyDataAnnotations.ToArray();

						CEntityPrimaryKeyDataAnnotations.PrintToConsole(Entities);
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
		private static void TestPrimaryKeyFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityPrimaryKeyFluentAPI[]			Entities=Context.EntitiesPrimaryKeyFluentAPI.ToArray();

						CEntityPrimaryKeyFluentAPI.PrintToConsole(Entities);
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
		private static void TestKeylessDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityKeylessDataAnnotations[]			Entities=Context.EntitiesKeylessDataAnnotations.ToArray();

						CEntityKeylessDataAnnotations.PrintToConsole(Entities);
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
		private static void TestKeylessFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityKeylessFluentAPI[]				Entities=Context.EntitiesKeylessFluentAPI.ToArray();

						CEntityKeylessFluentAPI.PrintToConsole(Entities);
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
		private static void TestIndexesDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityIndexesDataAnnotations[]			Entities=Context.EntitiesIndexesDataAnnotations.ToArray();

						CEntityIndexesDataAnnotations.PrintToConsole(Entities);

						IModel									Model=Context.GetService<IDesignTimeModel>().Model;
						IEntityType								EntityType=Model.FindEntityType(typeof(CEntityIndexesDataAnnotations));
						IIndex[]								Indexes=EntityType.GetIndexes().ToArray();

						foreach(IIndex Index in Indexes)
						{
							CConsoleHelpers.WriteLineSeparator();

							PrintIndex(Index);
						}
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
		private static void TestIndexesFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityIndexesFluentAPI[]				Entities=Context.EntitiesIndexesFluentAPI.ToArray();

						CEntityIndexesFluentAPI.PrintToConsole(Entities);

						IModel									Model=Context.GetService<IDesignTimeModel>().Model;
						IEntityType								EntityType=Model.FindEntityType(typeof(CEntityIndexesFluentAPI));
						IIndex[]								Indexes=EntityType.GetIndexes().ToArray();

						foreach(IIndex Index in Indexes)
						{
							CConsoleHelpers.WriteLineSeparator();

							PrintIndex(Index);
						}
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
		private static void TestCustomNamesDataAnnotations()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityCustomNamesDataAnnotations[]		Entities=Context.EntitiesCustomNamesDataAnnotations.ToArray();

						CEntityCustomNamesDataAnnotations.PrintToConsole(Entities);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityCustomNamesDataAnnotations));
						IProperty								PropertyValue=EntityType.FindProperty(nameof(CEntityCustomNamesDataAnnotations.Value));

						PrintProperty(PropertyValue);
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
		private static void TestCustomNamesFluentAPI()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityCustomNamesFluentAPI[]			Entities=Context.EntitiesCustomNamesFluentAPI.ToArray();

						CEntityCustomNamesFluentAPI.PrintToConsole(Entities);

						CConsoleHelpers.WriteLineSeparator();

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityCustomNamesFluentAPI));
						IProperty								PropertyValue=EntityType.FindProperty(nameof(CEntityCustomNamesFluentAPI.Value));

						PrintProperty(PropertyValue);
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
		private static void TestQueryFilters()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("QUERY FILTERS APPLIED:",ConsoleColor.Cyan);

						// !!! AUTOMATICKY sa aplikuju QUERY FILTERS.
						CEntityQueryFilter[]					Entities=Context.EntitiesQueryFilter.ToArray();

						CEntityQueryFilter.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("QUERY FILTERS DISABLED:",ConsoleColor.Cyan);

						// !!! QUERY FILTERS su VYPNUTE, lebo sa aplikovala METHOD [IQueryable<TEntity> IQueryable<TEntity>.IgnoreQueryFilters<TEntity>()].
						CEntityQueryFilter[]					Entities=Context.EntitiesQueryFilter.IgnoreQueryFilters().ToArray();

						CEntityQueryFilter.PrintToConsole(Entities);
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
		private static void TestShadowProperties()
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

						CEntityShadowProperties[]				Entities=Context.EntitiesShadowProperties.ToArray();

						CEntityShadowProperties.PrintToConsole(Entities,Context);
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

						CEntityShadowProperties					Entity=new CEntityShadowProperties("DDD");

						Context.EntitiesShadowProperties.Add(Entity);

						// !!!!! Pristup k SHADOW PROPERTIES je mozny, az ked je ENTITY TRACKED v DB CONTEXT, pretoze VALUES SHADOW PROPERTIES su ukladane do TRACKED ENTITY DATA.
						EntityEntry<CEntityShadowProperties>	EntryEntity=Context.Entry<CEntityShadowProperties>(Entity);

						EntryEntity.Property("ShadowPropertyString").CurrentValue="SHADOW DDD";
						EntryEntity.Property("ShadowPropertyInt").CurrentValue=400;

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.ID;

							CConsoleHelpers.WriteLine($"ENTITY was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT INSERTED !",ConsoleColor.Red);
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
						CConsoleHelpers.WriteLine("BEFORE DELETE:",ConsoleColor.Cyan);

						CEntityShadowProperties[]				Entities=Context.EntitiesShadowProperties.ToArray();

						CEntityShadowProperties.PrintToConsole(Entities,Context);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityShadowProperties					Entity=Context.EntitiesShadowProperties.Where(P => P.ID==ID).First();

						Context.EntitiesShadowProperties.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT DELETED !",ConsoleColor.Red);
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
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityShadowProperties[]				Entities=Context.EntitiesShadowProperties.ToArray();

						CEntityShadowProperties.PrintToConsole(Entities,Context);
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
						CConsoleHelpers.WriteLine("USING NO TRACKING:",ConsoleColor.Cyan);

						CEntityShadowProperties[]				Entities=Context.EntitiesShadowProperties.AsNoTracking().ToArray();

						CEntityShadowProperties.PrintToConsole(Entities,Context);
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
						CConsoleHelpers.WriteLine("SHADOW PROPERTIES used in QUERY:",ConsoleColor.Cyan);

						// !!! SHADOW PROPERTIES je mozne pouzivat aj v QUERIES.
						CEntityShadowProperties[]				Entities=Context.EntitiesShadowProperties.Where(P => EF.Property<int>(P,"ShadowPropertyInt")>100).ToArray();

						CEntityShadowProperties.PrintToConsole(Entities,Context);
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
						CConsoleHelpers.WriteLine("SHADOW PROPERTIES INFO:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityShadowProperties));
						IProperty								PropertyNonShadowProperty=EntityType.FindProperty(nameof(CEntityShadowProperties.NonShadowProperty));
						IProperty								PropertyShadowPropertyString=EntityType.FindProperty("ShadowPropertyString");
						IProperty								PropertyShadowPropertyInt=EntityType.FindProperty("ShadowPropertyInt");

						PrintProperty(PropertyNonShadowProperty);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyShadowPropertyString);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyShadowPropertyInt);
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
		private static void TestBackingFieldsConventions()
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

						CEntityBackingFieldsConventions[]		Entities=Context.EntitiesBackingFieldsConventions.ToArray();

						CEntityBackingFieldsConventions.PrintToConsole(Entities);
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

						CEntityBackingFieldsConventions			Entity=new CEntityBackingFieldsConventions("CCC 111","CCC 222","CCC 333");

						Context.EntitiesBackingFieldsConventions.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.ID;

							CConsoleHelpers.WriteLine($"ENTITY was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT INSERTED !",ConsoleColor.Red);
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
						CConsoleHelpers.WriteLine("BEFORE DELETE:",ConsoleColor.Cyan);

						CEntityBackingFieldsConventions[]		Entities=Context.EntitiesBackingFieldsConventions.ToArray();

						CEntityBackingFieldsConventions.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityBackingFieldsConventions			Entity=Context.EntitiesBackingFieldsConventions.Where(P => P.ID==ID).First();

						Context.EntitiesBackingFieldsConventions.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT DELETED !",ConsoleColor.Red);
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
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityBackingFieldsConventions[]		Entities=Context.EntitiesBackingFieldsConventions.ToArray();

						CEntityBackingFieldsConventions.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("BACKING FIELDS INFO:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityBackingFieldsConventions));
						IProperty								PropertyNoBackingField=EntityType.FindProperty(nameof(CEntityBackingFieldsConventions.NoBackingField));
						IProperty								PropertyBackingField1=EntityType.FindProperty(nameof(CEntityBackingFieldsConventions.BackingField1));
						IProperty								PropertyBackingField2=EntityType.FindProperty(nameof(CEntityBackingFieldsConventions.BackingField2));

						PrintProperty(PropertyNoBackingField);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingField1);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingField2);
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
		private static void TestBackingFieldsDataAnnotations()
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

						CEntityBackingFieldsDataAnnotations[]	Entities=Context.EntitiesBackingFieldsDataAnnotations.ToArray();

						CEntityBackingFieldsDataAnnotations.PrintToConsole(Entities);
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

						CEntityBackingFieldsDataAnnotations		Entity=new CEntityBackingFieldsDataAnnotations("CCC 111","CCC 222","CCC 333");

						Context.EntitiesBackingFieldsDataAnnotations.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.ID;

							CConsoleHelpers.WriteLine($"ENTITY was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT INSERTED !",ConsoleColor.Red);
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
						CConsoleHelpers.WriteLine("BEFORE DELETE:",ConsoleColor.Cyan);

						CEntityBackingFieldsDataAnnotations[]	Entities=Context.EntitiesBackingFieldsDataAnnotations.ToArray();

						CEntityBackingFieldsDataAnnotations.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityBackingFieldsDataAnnotations		Entity=Context.EntitiesBackingFieldsDataAnnotations.Where(P => P.ID==ID).First();

						Context.EntitiesBackingFieldsDataAnnotations.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT DELETED !",ConsoleColor.Red);
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
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityBackingFieldsDataAnnotations[]	Entities=Context.EntitiesBackingFieldsDataAnnotations.ToArray();

						CEntityBackingFieldsDataAnnotations.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("BACKING FIELDS INFO:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityBackingFieldsDataAnnotations));
						IProperty								PropertyNoBackingField=EntityType.FindProperty(nameof(CEntityBackingFieldsDataAnnotations.NoBackingField));
						IProperty								PropertyBackingField1=EntityType.FindProperty(nameof(CEntityBackingFieldsDataAnnotations.BackingField1));
						IProperty								PropertyBackingField2=EntityType.FindProperty(nameof(CEntityBackingFieldsDataAnnotations.BackingField2));

						PrintProperty(PropertyNoBackingField);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingField1);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingField2);
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
		private static void TestBackingFieldsFluentAPI()
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

						CEntityBackingFieldsFluentAPI[]			Entities=Context.EntitiesBackingFieldsFluentAPI.ToArray();

						CEntityBackingFieldsFluentAPI.PrintToConsole(Entities);
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

						CEntityBackingFieldsFluentAPI			Entity=new CEntityBackingFieldsFluentAPI("CCC 111","CCC 222","CCC 333","CCC 444");

						Context.EntitiesBackingFieldsFluentAPI.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.ID;

							CConsoleHelpers.WriteLine($"ENTITY was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT INSERTED !",ConsoleColor.Red);
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
						CConsoleHelpers.WriteLine("BEFORE DELETE:",ConsoleColor.Cyan);

						CEntityBackingFieldsFluentAPI[]			Entities=Context.EntitiesBackingFieldsFluentAPI.ToArray();

						CEntityBackingFieldsFluentAPI.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityBackingFieldsFluentAPI			Entity=Context.EntitiesBackingFieldsFluentAPI.Where(P => P.ID==ID).First();

						Context.EntitiesBackingFieldsFluentAPI.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT DELETED !",ConsoleColor.Red);
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
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityBackingFieldsFluentAPI[]			Entities=Context.EntitiesBackingFieldsFluentAPI.ToArray();

						CEntityBackingFieldsFluentAPI.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("BACKING FIELDS INFO:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityBackingFieldsFluentAPI));
						IProperty								PropertyNoBackingField=EntityType.FindProperty(nameof(CEntityBackingFieldsFluentAPI.NoBackingField));
						IProperty								PropertyBackingField1=EntityType.FindProperty(nameof(CEntityBackingFieldsFluentAPI.BackingField1));
						IProperty								PropertyBackingField2=EntityType.FindProperty(nameof(CEntityBackingFieldsFluentAPI.BackingField2));
						IProperty								PropertyBackingField3=EntityType.FindProperty("MBackingField3");

						PrintProperty(PropertyNoBackingField);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingField1);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingField2);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingField3);
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
		private static void TestBackingFieldsAccessModes()
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

						CEntityBackingFieldsAccessModes[]		Entities=Context.EntitiesBackingFieldsAccessModes.ToArray();

						CEntityBackingFieldsAccessModes.PrintToConsole(Entities);
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

						CEntityBackingFieldsAccessModes			Entity=new CEntityBackingFieldsAccessModes("CCC 111","CCC 222","CCC 333","CCC 444","CCC 555","CCC 666");

						Context.EntitiesBackingFieldsAccessModes.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.ID;

							CConsoleHelpers.WriteLine($"ENTITY was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT INSERTED !",ConsoleColor.Red);
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
						CConsoleHelpers.WriteLine("BEFORE DELETE:",ConsoleColor.Cyan);

						CEntityBackingFieldsAccessModes[]		Entities=Context.EntitiesBackingFieldsAccessModes.ToArray();

						CEntityBackingFieldsAccessModes.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityBackingFieldsAccessModes			Entity=Context.EntitiesBackingFieldsAccessModes.Where(P => P.ID==ID).First();

						Context.EntitiesBackingFieldsAccessModes.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT DELETED !",ConsoleColor.Red);
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
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CEntityBackingFieldsAccessModes[]		Entities=Context.EntitiesBackingFieldsAccessModes.ToArray();

						CEntityBackingFieldsAccessModes.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("BACKING FIELDS INFO:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityBackingFieldsAccessModes));
						IProperty								PropertyBackingFieldField=EntityType.FindProperty(nameof(CEntityBackingFieldsAccessModes.BackingFieldField));
						IProperty								PropertyBackingFieldFieldDuringConstruction=EntityType.FindProperty(nameof(CEntityBackingFieldsAccessModes.BackingFieldFieldDuringConstruction));
						IProperty								PropertyBackingFieldProperty=EntityType.FindProperty(nameof(CEntityBackingFieldsAccessModes.BackingFieldProperty));
						IProperty								PropertyBackingFieldPreferField=EntityType.FindProperty(nameof(CEntityBackingFieldsAccessModes.BackingFieldPreferField));
						IProperty								PropertyBackingFieldPreferFieldDuringConstruction=EntityType.FindProperty(nameof(CEntityBackingFieldsAccessModes.BackingFieldPreferFieldDuringConstruction));
						IProperty								PropertyBackingFieldPreferProperty=EntityType.FindProperty(nameof(CEntityBackingFieldsAccessModes.BackingFieldPreferProperty));

						PrintProperty(PropertyBackingFieldField);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingFieldFieldDuringConstruction);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingFieldProperty);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingFieldPreferField);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingFieldPreferFieldDuringConstruction);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyBackingFieldPreferProperty);
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
		private static void TestAutoConfigurationEntities()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("ENTITY TYPE 1:",ConsoleColor.Cyan);

						CEntityAutoConfiguration1[]				Entities=Context.EntitiesAutoConfiguration1.ToArray();

						CEntityAutoConfiguration1.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("ENTITY TYPE 2:",ConsoleColor.Cyan);

						CEntityAutoConfiguration2[]				Entities=Context.EntitiesAutoConfiguration2.ToArray();

						CEntityAutoConfiguration2.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("ENTITY 1 PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityAutoConfiguration1));
						IProperty								PropertyStringValue=EntityType.FindProperty(nameof(CEntityAutoConfiguration1.StringValue));
						IProperty								PropertyIntValue=EntityType.FindProperty(nameof(CEntityAutoConfiguration1.IntValue));
						IProperty								PropertyDoubleValue=EntityType.FindProperty(nameof(CEntityAutoConfiguration1.DoubleValue));

						PrintProperty(PropertyStringValue);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyIntValue);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyDoubleValue);
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
						CConsoleHelpers.WriteLine("ENTITY 2 PROPERTIES:",ConsoleColor.Cyan);

						IEntityType								EntityType=Context.Model.FindEntityType(typeof(CEntityAutoConfiguration2));
						IProperty								PropertyStringValue=EntityType.FindProperty(nameof(CEntityAutoConfiguration2.StringValue));
						IProperty								PropertyIntValue=EntityType.FindProperty(nameof(CEntityAutoConfiguration2.IntValue));
						IProperty								PropertyDoubleValue=EntityType.FindProperty(nameof(CEntityAutoConfiguration2.DoubleValue));

						PrintProperty(PropertyStringValue);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyIntValue);

						CConsoleHelpers.WriteLineSeparator();

						PrintProperty(PropertyDoubleValue);
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
			//TestSelectEntityDifferentConfigurations();
			//TestNotMappedDataAnnotations();
			//TestNotMappedFluentAPI();
			//TestColumnPropertiesDataAnnotations();
			//TestColumnPropertiesDataFluentAPI();
			//TestUsingValueConversions();
			//TestPrimaryKeyConventions();
			//TestPrimaryKeyDataAnnotations();
			//TestPrimaryKeyFluentAPI();
			//TestKeylessDataAnnotations();
			//TestKeylessFluentAPI();
			//TestIndexesDataAnnotations();
			//TestIndexesFluentAPI();
			//TestCustomNamesDataAnnotations();
			//TestCustomNamesFluentAPI();
			//TestQueryFilters();
			//TestShadowProperties();
			//TestBackingFieldsConventions();
			//TestBackingFieldsDataAnnotations();
			//TestBackingFieldsFluentAPI();
			//TestBackingFieldsAccessModes();
			TestAutoConfigurationEntities();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------