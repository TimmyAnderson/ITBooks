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
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Storage;
using Helpers;
using Microsoft.Azure.Cosmos;
//----------------------------------------------------------------------------------------------------------------------
namespace NoSQLDatabases
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		private static void FillData(CDBContext Context)
		{
			// !!!!! PRIMARY KEYS MUSIA byt EXPLICITNE NASTAVENE.
			CTestEntity											TestEntity1=new CTestEntity(1,"AAA");
			CTestEntity											TestEntity2=new CTestEntity(2,"BBB");

			Context.TestEntities.Add(TestEntity1);
			Context.TestEntities.Add(TestEntity2);

			CEntityDependent									EntityDependent11=new CEntityDependent(1111,"DEPENDENT 11",1111.1111);
			CEntityDependent									EntityDependent12=new CEntityDependent(2222,"DEPENDENT 12",2222.2222);
			CEntityDependent									EntityDependent21=new CEntityDependent(3333,"DEPENDENT 11",3333.3333);
			CEntityDependent									EntityDependent22=new CEntityDependent(4444,"DEPENDENT 11",4444.4444);

			// !!!!! PRIMARY KEYS MUSIA byt EXPLICITNE NASTAVENE.
			CEntityPrincipal									EntityPrincipal1=new CEntityPrincipal(1,11,"PRINCIPAL 1",11.11,new List<CEntityDependent>(new CEntityDependent[]{EntityDependent11,EntityDependent12}));
			CEntityPrincipal									EntityPrincipal2=new CEntityPrincipal(2,22,"PRINCIPAL 2",22.22,new List<CEntityDependent>(new CEntityDependent[]{EntityDependent21,EntityDependent22}));

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
						Context.Database.EnsureDeleted();

						// !!! Na vytvorenie DB sa pouziva METHOD [bool DatabaseFacade.EnsureCreated()].
						Context.Database.EnsureCreated();

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
		private static void TestSelectPrincipalEntity()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!!!! Na nacitanie DEPENDENT ENTITIES NIE JE potrebne pouzitie LINQ OPERATOR [Include].
						CEntityPrincipal[]						Entities=Context.EntitiesPrincipal.ToArray();

						CEntityPrincipal.PrintToConsole(Entities);
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
		private static void TestAddUpdateDelete()
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

						CEntityPrincipal[]						Entities=Context.EntitiesPrincipal.ToArray();

						CEntityPrincipal.PrintToConsole(Entities);
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

						CEntityDependent						DependentEntity1=new CEntityDependent(5555,"NEW DEPENDENT 31",5555.5555);
						CEntityDependent						DependentEntity2=new CEntityDependent(6666,"NEW DEPENDENT 32",6666.6666);

						CEntityPrincipal						PrincipalEntity=new CEntityPrincipal(3,33,"NEW PRINCIPAL 3",33.33,new List<CEntityDependent>(new CEntityDependent[]{DependentEntity1,DependentEntity2}));

						Context.EntitiesPrincipal.Add(PrincipalEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityPrincipal[]						Entities=Context.EntitiesPrincipal.ToArray();

						CEntityPrincipal.PrintToConsole(Entities);
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

						CEntityPrincipal						ExistingPrincipalEntity=Context.EntitiesPrincipal.Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityDependent						ExistingDependentEntity1=ExistingPrincipalEntity.EntitiesDependent[0];
						CEntityDependent						ExistingDependentEntity2=ExistingPrincipalEntity.EntitiesDependent[1];
						CEntityDependent						NewDependentEntity=new CEntityDependent(7777,"NEW DEPENDENT 33",7777.7777);

						// !!! Zmeni sa PROPERTY v PRINCIPAL ENTITY.
						ExistingPrincipalEntity.EntityPrincipalStringValue+=" MODIFIED !!!!!";

						// !!! Zmeni sa PROPERTY v DEPENDENT ENTITY.
						ExistingDependentEntity1.EntityDependentIntValue+=100;

						// !!! Prida sa nova DEPENDENT ENTITY pridanim do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						ExistingPrincipalEntity.EntitiesDependent.Add(NewDependentEntity);

						// !!! Odstrani sa existujuca DEPENDENT ENTITY odstranenim z NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						ExistingPrincipalEntity.EntitiesDependent.Remove(ExistingDependentEntity2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity.EntityPrincipalID}] was UPDATED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity1)}] was UPDATED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] was UPDATED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] was UPDATED !",ConsoleColor.Blue);
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

						CEntityPrincipal[]						Entities=Context.EntitiesPrincipal.ToArray();

						CEntityPrincipal.PrintToConsole(Entities);
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

						CEntityPrincipal						Entity=Context.EntitiesPrincipal.Where(P => P.EntityPrincipalID==PrincipalID).First();

						Context.EntitiesPrincipal.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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

						CEntityPrincipal[]						Entities=Context.EntitiesPrincipal.ToArray();

						CEntityPrincipal.PrintToConsole(Entities);
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
			//TestSelectPrincipalEntity();
			TestAddUpdateDelete();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------