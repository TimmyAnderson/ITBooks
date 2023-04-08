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
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using Microsoft.Extensions.Logging.Console;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace PerformanceTuning1
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

			CEntityDependent									EntityDependent11=new CEntityDependent(111,"DEPENDENT 111");
			CEntityDependent									EntityDependent12=new CEntityDependent(222,"DEPENDENT 222");
			CEntityDependent									EntityDependent21=new CEntityDependent(333,"DEPENDENT 333");
			CEntityDependent									EntityDependent22=new CEntityDependent(444,"DEPENDENT 444");

			CEntityPrincipal									EntityPrincipal1=new CEntityPrincipal(111,"PRINCIPAL 111",new List<CEntityDependent>(new CEntityDependent[]{EntityDependent11,EntityDependent12}));
			CEntityPrincipal									EntityPrincipal2=new CEntityPrincipal(222,"PRINCIPAL 222",new List<CEntityDependent>(new CEntityDependent[]{EntityDependent21,EntityDependent22}));

			Context.EntitiesPrincipal.Add(EntityPrincipal1);
			Context.EntitiesPrincipal.Add(EntityPrincipal2);

			CEntityPrecompiledQueries							EntityPrecompiledQueries1=new CEntityPrecompiledQueries("111");
			CEntityPrecompiledQueries							EntityPrecompiledQueries2=new CEntityPrecompiledQueries("222");
			CEntityPrecompiledQueries							EntityPrecompiledQueries3=new CEntityPrecompiledQueries("333");
			CEntityPrecompiledQueries							EntityPrecompiledQueries4=new CEntityPrecompiledQueries("444");
			CEntityPrecompiledQueries							EntityPrecompiledQueries5=new CEntityPrecompiledQueries("555");
			CEntityPrecompiledQueries							EntityPrecompiledQueries6=new CEntityPrecompiledQueries("666");
			CEntityPrecompiledQueries							EntityPrecompiledQueries7=new CEntityPrecompiledQueries("777");
			CEntityPrecompiledQueries							EntityPrecompiledQueries8=new CEntityPrecompiledQueries("888");
			CEntityPrecompiledQueries							EntityPrecompiledQueries9=new CEntityPrecompiledQueries("999");

			Context.EntitiesPrecompiledQueries.Add(EntityPrecompiledQueries1);
			Context.EntitiesPrecompiledQueries.Add(EntityPrecompiledQueries2);
			Context.EntitiesPrecompiledQueries.Add(EntityPrecompiledQueries3);
			Context.EntitiesPrecompiledQueries.Add(EntityPrecompiledQueries4);
			Context.EntitiesPrecompiledQueries.Add(EntityPrecompiledQueries5);
			Context.EntitiesPrecompiledQueries.Add(EntityPrecompiledQueries6);
			Context.EntitiesPrecompiledQueries.Add(EntityPrecompiledQueries7);
			Context.EntitiesPrecompiledQueries.Add(EntityPrecompiledQueries8);
			Context.EntitiesPrecompiledQueries.Add(EntityPrecompiledQueries9);
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
		private static void TestNoLogging()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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

						CEntityDependent						DependentEntity1=new CEntityDependent(555,"NEW DEPENDENT 555");
						CEntityDependent						DependentEntity2=new CEntityDependent(666,"NEW DEPENDENT 666");

						CEntityPrincipal						PrincipalEntity=new CEntityPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityDependent>(new CEntityDependent[]{DependentEntity1,DependentEntity2}));

						Context.EntitiesPrincipal.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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

						CEntityPrincipal						PrincipalEntity=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesPrincipal.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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
		private static void ConfigureExistingLoggerFactory(CDBContext Context)
		{
			// !!!!! Ziska sa existujuca instancia LOGGER FACTORY.
			// !!!!! Na EXISTING LOGGER FACTORY som nenasiel sposob ako zmenit LOG LEVEL.
			ILoggerFactory										LoggerFactory=Context.GetService<ILoggerFactory>();

			OptionsFactory<ConsoleLoggerOptions>				OptionsFactory=new OptionsFactory<ConsoleLoggerOptions>(new ConfigureOptions<ConsoleLoggerOptions>[0],new IPostConfigureOptions<ConsoleLoggerOptions>[0]);
			OptionsMonitor<ConsoleLoggerOptions>				OptionsMonitor=new OptionsMonitor<ConsoleLoggerOptions>(OptionsFactory,new IOptionsChangeTokenSource<ConsoleLoggerOptions>[0],new OptionsCache<ConsoleLoggerOptions>());
			ConsoleLoggerProvider								LoggerProvider=new ConsoleLoggerProvider(OptionsMonitor);

			LoggerFactory.AddProvider(LoggerProvider);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void TestLoggingExistingLoggerFactory()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						ConfigureExistingLoggerFactory(Context);

						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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
						ConfigureExistingLoggerFactory(Context);

						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityDependent						DependentEntity1=new CEntityDependent(555,"NEW DEPENDENT 555");
						CEntityDependent						DependentEntity2=new CEntityDependent(666,"NEW DEPENDENT 666");

						CEntityPrincipal						PrincipalEntity=new CEntityPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityDependent>(new CEntityDependent[]{DependentEntity1,DependentEntity2}));

						Context.EntitiesPrincipal.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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
						ConfigureExistingLoggerFactory(Context);

						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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
						ConfigureExistingLoggerFactory(Context);

						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityPrincipal						PrincipalEntity=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesPrincipal.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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
						ConfigureExistingLoggerFactory(Context);

						CConsoleHelpers.WriteLine("AFTER DELETE ENTITIES:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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
		private static void TestLoggingCreatedLoggerFactory()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_LOGGER_FACTORY,LogLevel.Information))
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_LOGGER_FACTORY,LogLevel.Information))
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityDependent						DependentEntity1=new CEntityDependent(555,"NEW DEPENDENT 555");
						CEntityDependent						DependentEntity2=new CEntityDependent(666,"NEW DEPENDENT 666");

						CEntityPrincipal						PrincipalEntity=new CEntityPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityDependent>(new CEntityDependent[]{DependentEntity1,DependentEntity2}));

						Context.EntitiesPrincipal.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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

				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_LOGGER_FACTORY,LogLevel.Information))
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_LOGGER_FACTORY,LogLevel.Information))
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityPrincipal						PrincipalEntity=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesPrincipal.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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

				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_LOGGER_FACTORY,LogLevel.Information))
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE ENTITIES:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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
		private static void TestLoggingLogMethod()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_TO_LOG_METHOD,LogLevel.Information))
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_TO_LOG_METHOD,LogLevel.Information))
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityDependent						DependentEntity1=new CEntityDependent(555,"NEW DEPENDENT 555");
						CEntityDependent						DependentEntity2=new CEntityDependent(666,"NEW DEPENDENT 666");

						CEntityPrincipal						PrincipalEntity=new CEntityPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityDependent>(new CEntityDependent[]{DependentEntity1,DependentEntity2}));

						Context.EntitiesPrincipal.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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

				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_TO_LOG_METHOD,LogLevel.Information))
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_TO_LOG_METHOD,LogLevel.Information))
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityPrincipal						PrincipalEntity=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesPrincipal.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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

				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_TO_LOG_METHOD,LogLevel.Information))
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE ENTITIES:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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
		private static void TestLoggingUseToQueryStringMethod()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("NO LOGGING:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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
						CConsoleHelpers.WriteLine("WITH LOGGING:",ConsoleColor.Cyan);

						// !!! Vytvori sa QUERY.
						IQueryable<CEntityPrincipal>			Query1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent);

						// !!! Pre danu QUERY sa ziska SQL COMMAND, ktory ENTITY FRAMEWORK CORE vykona nad DATABASE.
						string									QueryString1=Query1.ToQueryString();

						CConsoleHelpers.WriteLine($"EXECITUING QUERY [{QueryString1}].",ConsoleColor.DarkYellow);

						CEntityPrincipal[]						Entities1=Query1.ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						// !!! Vytvori sa QUERY.
						IQueryable<CEntityDependent>			Query2=Context.EntitiesDependent.Include(P => P.EntityPrincipal);

						// !!! Pre danu QUERY sa ziska SQL COMMAND, ktory ENTITY FRAMEWORK CORE vykona nad DATABASE.
						string									QueryString2=Query2.ToQueryString();

						CConsoleHelpers.WriteLine($"EXECITUING QUERY [{QueryString2}].",ConsoleColor.DarkYellow);

						CEntityDependent[]						Entities2=Query2.ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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
		private static void TestFirstVsSingle()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			int													DependentID1=0;
			int													DependentID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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

						CEntityDependent						DependentEntity1=new CEntityDependent(555,"NEW DEPENDENT 555");
						CEntityDependent						DependentEntity2=new CEntityDependent(666,"NEW DEPENDENT 666");

						CEntityPrincipal						PrincipalEntity=new CEntityPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityDependent>(new CEntityDependent[]{DependentEntity1,DependentEntity2}));

						Context.EntitiesPrincipal.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;
							DependentID1=DependentEntity1.EntityDependentID;
							DependentID2=DependentEntity2.EntityDependentID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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
						CConsoleHelpers.WriteLine("TEST LINQ OPERATOR [First]:",ConsoleColor.Cyan);

						Stopwatch								SW=new Stopwatch();

						SW.Start();

						for(int Index=0;Index<5000;Index++)
						{
							Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).AsNoTracking().First();

							Context.EntitiesDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).AsNoTracking().First();
							Context.EntitiesDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).AsNoTracking().First();
						}

						SW.Stop();

						CConsoleHelpers.WriteLine($"PROCESSING TIME [{SW.ElapsedMilliseconds}].",ConsoleColor.Cyan);
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
						CConsoleHelpers.WriteLine("TEST LINQ OPERATOR [Single]:",ConsoleColor.Cyan);

						Stopwatch								SW=new Stopwatch();

						SW.Start();

						for(int Index=0;Index<5000;Index++)
						{
							Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).AsNoTracking().Single();

							Context.EntitiesDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).AsNoTracking().Single();
							Context.EntitiesDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).AsNoTracking().Single();
						}

						SW.Stop();

						CConsoleHelpers.WriteLine($"PROCESSING TIME [{SW.ElapsedMilliseconds}].",ConsoleColor.Cyan);
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

						CEntityPrincipal						PrincipalEntity=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesPrincipal.Remove(PrincipalEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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

						CEntityPrincipal[]						Entities1=Context.EntitiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityDependent[]						Entities2=Context.EntitiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityDependent.PrintToConsole(Entities2);
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
		public static void TestSelectTestByPrecompiledQuery()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("ALL RECORDS:",ConsoleColor.Cyan);

						CEntityPrecompiledQueries[]				Entities=Context.EntitiesPrecompiledQueries.ToArray();

						CEntityPrecompiledQueries.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				// !!!!! Vykona sa QUERY COMPILATION.
				Func<CDBContext,int,int,IEnumerable<CEntityPrecompiledQueries>>	PrecompiledQuery=EF.CompileQuery<CDBContext,int,int,IEnumerable<CEntityPrecompiledQueries>>((CDBContext Context, int NumberOfRecordsToSkip, int NumberOfRecordsToTake) => Context.EntitiesPrecompiledQueries.Skip(NumberOfRecordsToSkip).Take(NumberOfRecordsToTake));

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("USING COMPILED QUERY:",ConsoleColor.Cyan);

						// !!!!! Pouzije sa PRECOMPILED QUERY.
						CEntityPrecompiledQueries[]				Entities=PrecompiledQuery(Context,4,3).ToArray();

						CEntityPrecompiledQueries.PrintToConsole(Entities);
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
			//TestNoLogging();
			//TestLoggingExistingLoggerFactory();
			//TestLoggingCreatedLoggerFactory();
			//TestLoggingLogMethod();
			//TestLoggingUseToQueryStringMethod();
			//TestFirstVsSingle();
			TestSelectTestByPrecompiledQuery();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------