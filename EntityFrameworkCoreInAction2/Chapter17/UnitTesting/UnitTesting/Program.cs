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
namespace UnitTesting
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
		private static void TestClearContext()
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

							CConsoleHelpers.WriteLine($"ADDED PRINCIPAL ENTITY:",ConsoleColor.Yellow);

							string								PrincipalEntityString=PrincipalEntity.Print(null);

							CConsoleHelpers.Write(PrincipalEntityString,ConsoleColor.Magenta);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine($"RELOADED PRINCIPAL ENTITY BEFORE DB CONTEXT CLEAR:",ConsoleColor.Yellow);

						// !!!!! Nacita sa PRINCIPAL ENTITY bez pouzitia LINQ OPERATOR [Include] na nacitanie DEPENDENT ENTITIES.
						// !!!!! DEPENDENT ENTITIES vsak aj napriek NEPOUZITIU LINQ OPERATOR [Include] BUDU NACITANE, pretoze vsetky ENTTIES boli pocas INSERT ulozene v DB CONTEXT a DB CONTEXT namiesto vykonania QUERY tieto ENTITIES iba vrati z DB CONTEXT.
						CEntityPrincipal				ExistingPrincipalEntity1=Context.EntitiesPrincipal.Where(P => P.EntityPrincipalID==PrincipalID).First();
						string									ExistingPrincipalEntityString1=ExistingPrincipalEntity1.Print(null);

						CConsoleHelpers.Write(ExistingPrincipalEntityString1,ConsoleColor.Magenta);

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine($"DB CONTEXT CLEARED.",ConsoleColor.Yellow);

						// !!!!! Z DB CONTEXT sa vymazu vsetky ulozene ENTITY OBJECTS.
						Context.ChangeTracker.Clear();

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine($"RELOADED PRINCIPAL ENTITY AFTER DB CONTEXT CLEAR:",ConsoleColor.Yellow);

						// !!!!! Nacita sa PRINCIPAL ENTITY bez pouzitia LINQ OPERATOR [Include] na nacitanie DEPENDENT ENTITIES.
						// !!!!! DEPENDENT ENTITIES sa uz NENACITAJU, pretoze DB CONTEXT bol CLEARED.
						CEntityPrincipal						ExistingPrincipalEntity2=Context.EntitiesPrincipal.Where(P => P.EntityPrincipalID==PrincipalID).First();
						string									ExistingPrincipalEntityString2=ExistingPrincipalEntity2.Print(null);

						CConsoleHelpers.Write(ExistingPrincipalEntityString2,ConsoleColor.Magenta);
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
		private static void TestLoggingUseLoggerFactory()
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

				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_LOGGER_FACTORY))
				{
					try
					{
						CConsoleHelpers.WriteLine("WITH LOGGING:",ConsoleColor.Cyan);

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
		private static void TestLoggingUseToLogMethod()
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

				using(CDBContext Context=new CDBContext(ELoggingType.E_USE_TO_LOG_METHOD))
				{
					try
					{
						CConsoleHelpers.WriteLine("WITH LOGGING:",ConsoleColor.Cyan);

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
        static void Main(string[] args)
        {
			//CreateTestDB();
			//TestSelectTestEntity();
			//TestClearContext();
			//TestLoggingUseLoggerFactory();
			TestLoggingUseToLogMethod();
			//TestLoggingUseToQueryStringMethod();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------