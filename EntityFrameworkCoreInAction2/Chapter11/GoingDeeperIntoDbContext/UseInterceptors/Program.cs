using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Storage;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UseInterceptors
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

			CEntityOneToManyDependent							EntityOneToManyDependent11=new CEntityOneToManyDependent(111,"DEPENDENT 111");
			CEntityOneToManyDependent							EntityOneToManyDependent12=new CEntityOneToManyDependent(222,"DEPENDENT 222");
			CEntityOneToManyDependent							EntityOneToManyDependent21=new CEntityOneToManyDependent(333,"DEPENDENT 333");
			CEntityOneToManyDependent							EntityOneToManyDependent22=new CEntityOneToManyDependent(444,"DEPENDENT 444");

			CEntityOneToManyPrincipal							EntityOneToManyPrincipal1=new CEntityOneToManyPrincipal(111,"PRINCIPAL 111",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{EntityOneToManyDependent11,EntityOneToManyDependent12}));
			CEntityOneToManyPrincipal							EntityOneToManyPrincipal2=new CEntityOneToManyPrincipal(222,"PRINCIPAL 222",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{EntityOneToManyDependent21,EntityOneToManyDependent22}));

			Context.EntitiesOneToManyPrincipal.Add(EntityOneToManyPrincipal1);
			Context.EntitiesOneToManyPrincipal.Add(EntityOneToManyPrincipal2);
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
		private static void TestInterceptors()
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CConsoleHelpers.WriteLineSeparator();
						CEntityOneToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyDependent[]				Entities2=Context.EntitiesOneToManyDependent.Include(P => P.EntityPrincipal).ToArray();

						CConsoleHelpers.WriteLineSeparator();
						CEntityOneToManyDependent.PrintToConsole(Entities2);
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

						CEntityOneToManyDependent				DependentEntity1=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity2=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyPrincipal				PrincipalEntity=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CConsoleHelpers.WriteLineSeparator();
						CEntityOneToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyDependent[]				Entities2=Context.EntitiesOneToManyDependent.Include(P => P.EntityPrincipal).ToArray();

						CConsoleHelpers.WriteLineSeparator();
						CEntityOneToManyDependent.PrintToConsole(Entities2);
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

						CEntityOneToManyPrincipal				ExistingPrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				ExistingDependentEntity1=ExistingPrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity.EntitiesDependent[1];
						CEntityOneToManyDependent				NewDependentEntity=new CEntityOneToManyDependent(777,"NEW DEPENDENT 777");

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] CREATED.",ConsoleColor.Yellow);

						// !!! Zmeni sa PROPERTY v PRINCIPAL ENTITY.
						ExistingPrincipalEntity.EntityPrincipalStringValue+=" MODIFIED !!!!!";

						// !!! Zmeni sa PROPERTY v DEPENDENT ENTITY.
						ExistingDependentEntity1.EntityDependentIntValue+=100;

						// !!! Prida sa nova DEPENDENT ENTITY pridanim do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						ExistingPrincipalEntity.EntitiesDependent.Add(NewDependentEntity);

						// !!! Odstrani sa existujuca DEPENDENT ENTITY odstranenim z NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						ExistingPrincipalEntity.EntitiesDependent.Remove(ExistingDependentEntity2);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity)}] PROPERTY [{nameof(ExistingPrincipalEntity.EntityPrincipalStringValue)}] MODIFIED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity1)}] PROPERTY [{nameof(ExistingDependentEntity1.EntityDependentIntValue)}] MODIFIED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] ADDED to PRINCIPAL ENTITY [{ExistingPrincipalEntity}].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] REMOVED from PRINCIPAL ENTITY [{ExistingPrincipalEntity}].",ConsoleColor.Yellow);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
						}
						else
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"ENTITIES were NOT UPDATED !",ConsoleColor.Red);
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CConsoleHelpers.WriteLineSeparator();
						CEntityOneToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyDependent[]				Entities2=Context.EntitiesOneToManyDependent.Include(P => P.EntityPrincipal).ToArray();

						CConsoleHelpers.WriteLineSeparator();
						CEntityOneToManyDependent.PrintToConsole(Entities2);
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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						Context.EntitiesOneToManyDependent.Remove(DependentEntity1);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CConsoleHelpers.WriteLineSeparator();
						CEntityOneToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyDependent[]				Entities2=Context.EntitiesOneToManyDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyDependent.PrintToConsole(Entities2);
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
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity=PrincipalEntity.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						Context.EntitiesOneToManyPrincipal.Remove(PrincipalEntity);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CConsoleHelpers.WriteLineSeparator();
						CEntityOneToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyDependent[]				Entities2=Context.EntitiesOneToManyDependent.Include(P => P.EntityPrincipal).ToArray();

						CConsoleHelpers.WriteLineSeparator();
						CEntityOneToManyDependent.PrintToConsole(Entities2);
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
			TestInterceptors();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------