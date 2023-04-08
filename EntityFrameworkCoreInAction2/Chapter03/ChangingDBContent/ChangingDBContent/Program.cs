using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace ChangingDBContent
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

			CEntityOneToOneDependent							EntityOneToOneDependent1=new CEntityOneToOneDependent("CHILD AAA");
			CEntityOneToOneDependent							EntityOneToOneDependent2=new CEntityOneToOneDependent("CHILD BBB");

			CEntityOneToOnePrincipal							EntityOneToOnePrincipal1=new CEntityOneToOnePrincipal("PARENT AAA");
			CEntityOneToOnePrincipal							EntityOneToOnePrincipal2=new CEntityOneToOnePrincipal("PARENT BBB");

			EntityOneToOnePrincipal1.EntityDependent=EntityOneToOneDependent1;
			EntityOneToOnePrincipal2.EntityDependent=EntityOneToOneDependent2;

			Context.EntitiesOneToOnePrincipal.Add(EntityOneToOnePrincipal1);
			Context.EntitiesOneToOnePrincipal.Add(EntityOneToOnePrincipal2);

			CEntityOneToManyDependent							EntityOneToManyDependent11=new CEntityOneToManyDependent("AAA 111");
			CEntityOneToManyDependent							EntityOneToManyDependent12=new CEntityOneToManyDependent("AAA 222");
			CEntityOneToManyDependent							EntityOneToManyDependent21=new CEntityOneToManyDependent("BBB 111");
			CEntityOneToManyDependent							EntityOneToManyDependent22=new CEntityOneToManyDependent("BBB 222");

			CEntityOneToManyPrincipal							EntityOneToManyPrincipal1=new CEntityOneToManyPrincipal("AAA",new CEntityOneToManyDependent[]{EntityOneToManyDependent11,EntityOneToManyDependent12});
			CEntityOneToManyPrincipal							EntityOneToManyPrincipal2=new CEntityOneToManyPrincipal("BBB",new CEntityOneToManyDependent[]{EntityOneToManyDependent21,EntityOneToManyDependent22});

			Context.EntitiesOneToManyPrincipal.Add(EntityOneToManyPrincipal1);
			Context.EntitiesOneToManyPrincipal.Add(EntityOneToManyPrincipal2);

			CEntityManyToManyM									EntityManyToManyM1=new CEntityManyToManyM("AAA");
			CEntityManyToManyM									EntityManyToManyM2=new CEntityManyToManyM("BBB");

			CEntityManyToManyN									EntityManyToManyN1=new CEntityManyToManyN("111");
			CEntityManyToManyN									EntityManyToManyN2=new CEntityManyToManyN("222");

			CEntityManyToManyMN									EntityManyToManyMN11=new CEntityManyToManyMN("LINK 11");
			CEntityManyToManyMN									EntityManyToManyMN12=new CEntityManyToManyMN("LINK 12");
			CEntityManyToManyMN									EntityManyToManyMN21=new CEntityManyToManyMN("LINK 21");
			CEntityManyToManyMN									EntityManyToManyMN22=new CEntityManyToManyMN("LINK 22");

			EntityManyToManyMN11.EntityM=EntityManyToManyM1;
			EntityManyToManyMN11.EntityN=EntityManyToManyN1;

			EntityManyToManyMN12.EntityM=EntityManyToManyM1;
			EntityManyToManyMN12.EntityN=EntityManyToManyN2;

			EntityManyToManyMN21.EntityM=EntityManyToManyM2;
			EntityManyToManyMN21.EntityN=EntityManyToManyN1;

			EntityManyToManyMN22.EntityM=EntityManyToManyM2;
			EntityManyToManyMN22.EntityN=EntityManyToManyN2;

			Context.EntitiesManyToManyMN.Add(EntityManyToManyMN11);
			Context.EntitiesManyToManyMN.Add(EntityManyToManyMN12);
			Context.EntitiesManyToManyMN.Add(EntityManyToManyMN21);
			Context.EntitiesManyToManyMN.Add(EntityManyToManyMN22);

			CEntityManyToManyAutoM								EntityManyToManyAutoM1=new CEntityManyToManyAutoM("AAA");
			CEntityManyToManyAutoM								EntityManyToManyAutoM2=new CEntityManyToManyAutoM("BBB");

			CEntityManyToManyAutoN								EntityManyToManyAutoN1=new CEntityManyToManyAutoN("111");
			CEntityManyToManyAutoN								EntityManyToManyAutoN2=new CEntityManyToManyAutoN("222");

			EntityManyToManyAutoM1.EntitiesN.Add(EntityManyToManyAutoN1);
			EntityManyToManyAutoM1.EntitiesN.Add(EntityManyToManyAutoN2);
			EntityManyToManyAutoM2.EntitiesN.Add(EntityManyToManyAutoN1);
			EntityManyToManyAutoM2.EntitiesN.Add(EntityManyToManyAutoN2);

			Context.EntitiesManyToManyAutoM.Add(EntityManyToManyAutoM1);
			Context.EntitiesManyToManyAutoM.Add(EntityManyToManyAutoM2);

			CNumber												Number1=new CNumber(1,"ONE");
			CNumber												Number2=new CNumber(2,"TWO");
			CNumber												Number3=new CNumber(3,"THREE");
			CNumber												Number4=new CNumber(4,"FOUR");
			CNumber												Number5=new CNumber(5,"FIVE");
			CNumber												Number6=new CNumber(6,"SIX");
			CNumber												Number7=new CNumber(7,"SEVEN");
			CNumber												Number8=new CNumber(8,"EIGHT");
			CNumber												Number9=new CNumber(9,"NINE");
			CNumber												Number10=new CNumber(10,"TEN");

			Context.EntitiesNumbers.Add(Number1);
			Context.EntitiesNumbers.Add(Number2);
			Context.EntitiesNumbers.Add(Number3);
			Context.EntitiesNumbers.Add(Number4);
			Context.EntitiesNumbers.Add(Number5);
			Context.EntitiesNumbers.Add(Number6);
			Context.EntitiesNumbers.Add(Number7);
			Context.EntitiesNumbers.Add(Number8);
			Context.EntitiesNumbers.Add(Number9);
			Context.EntitiesNumbers.Add(Number10);

			CEntityZeroToManyDependent							EntityZeroToManyDependent11=new CEntityZeroToManyDependent("AAA 111");
			CEntityZeroToManyDependent							EntityZeroToManyDependent12=new CEntityZeroToManyDependent("AAA 222");
			CEntityZeroToManyDependent							EntityZeroToManyDependent21=new CEntityZeroToManyDependent("BBB 111");
			CEntityZeroToManyDependent							EntityZeroToManyDependent22=new CEntityZeroToManyDependent("BBB 222");

			CEntityZeroToManyPrincipal							EntityZeroToManyPrincipal1=new CEntityZeroToManyPrincipal("AAA",new CEntityZeroToManyDependent[]{EntityZeroToManyDependent11,EntityZeroToManyDependent12});
			CEntityZeroToManyPrincipal							EntityZeroToManyPrincipal2=new CEntityZeroToManyPrincipal("BBB",new CEntityZeroToManyDependent[]{EntityZeroToManyDependent21,EntityZeroToManyDependent22});

			Context.EntitiesZeroToManyPrincipal.Add(EntityZeroToManyPrincipal1);
			Context.EntitiesZeroToManyPrincipal.Add(EntityZeroToManyPrincipal2);
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
		private static void TestSelect()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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
		private static void TestFind()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext(true))
				{
					try
					{
						// !!! Vykona sa QUERY do DB a vyhlada sa ENTITY s ID 1.
						// !!! DB QUERY sa vykona, pretoze ENTITY s ID 1 este NEBOLA nacitana z DB a NIE JE v DB CONTEXT.
						CEntityOneToManyPrincipal				Entity1=Context.EntitiesOneToManyPrincipal.Find(1);
						string									Entity1Text=Entity1.Print(null);

						CConsoleHelpers.Write(Entity1Text,ConsoleColor.Green);
						CConsoleHelpers.WriteLineSeparator();

						Thread.Sleep(1000);

						// !!!!! NACITA sa ZNOVA ta ISTA ENTITY s ID 1. Kedze sa vsak pouzila METHOD [TEntity DbSet<TEntity>.Find(params object[] KeyValues)], ktora NAJPRV zistuje ci instancia ENTITY CLASS uz nebola nacitana z DB a ak ano, tak ju vrati, NEVYKONANA sa QUERY do DB.
						CEntityOneToManyPrincipal				Entity2=Context.EntitiesOneToManyPrincipal.Find(1);
						string									Entity2Text=Entity2.Print(null);

						CConsoleHelpers.Write(Entity2Text,ConsoleColor.Green);
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
		private static void TestInsert()
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

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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

						CEntityOneToManyPrincipal				NewEntity=new CEntityOneToManyPrincipal("NEW ROW",null);

						CConsoleHelpers.WriteLine("ENTITY CREATED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,NewEntity);

						Context.EntitiesOneToManyPrincipal.Add(NewEntity);

						CConsoleHelpers.WriteLine("PRINCIPAL ENTITY ADDED to CONTEXT.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,NewEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						// !!! STATE pridanej instancie ENTITY CLASS je nastaveny na [Unchanged].
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities==1)
						{
							// !!! Nacita sa ID ENTITY, aby sa neskor mohla zmazat.
							ID=NewEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"ENTITY with ID [{ID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT INSERTED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,NewEntity);
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

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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

						CEntityOneToManyPrincipal				Entity=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID).First();

						Context.EntitiesOneToManyPrincipal.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities==1)
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{ID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{ID}] was NOT DELETED !",ConsoleColor.Red);
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

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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
		private static void TestInsertRelationship()
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

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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

						CEntityOneToManyPrincipal				NewPrincipalEntity=new CEntityOneToManyPrincipal("NEW PRINCIPAL ENTITY",new List<CEntityOneToManyDependent>());

						CConsoleHelpers.WriteLine("PRINCIPAL ENTITY CREATED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,NewPrincipalEntity);

						CEntityOneToManyDependent				NewDependentEntity=new CEntityOneToManyDependent("NEW DEPENDENT ENTITY");

						CConsoleHelpers.WriteLine("DEPENDENT ENTITY CREATED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,NewDependentEntity);

						NewPrincipalEntity.EntitiesDependent.Add(NewDependentEntity);

						CConsoleHelpers.WriteLine("DEPENDENT ENTITY ADDED to PRINCIPAL ENTITY.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,NewPrincipalEntity);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,NewDependentEntity);

						Context.EntitiesOneToManyPrincipal.Add(NewPrincipalEntity);

						CConsoleHelpers.WriteLine("PRINCIPAL ENTITY ADDED to CONTEXT.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,NewPrincipalEntity);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,NewDependentEntity);

						// !!! IDs vsetkych PRIMARY KEYS a FOREIGN KEYS su nastavene na 0.
						CConsoleHelpers.WriteLine($"NewPrincipalEntity.EntityPrincipalID [{NewPrincipalEntity.EntityPrincipalID}] !",ConsoleColor.Magenta);
						CConsoleHelpers.WriteLine($"NewDependentEntity.EntityDependentID [{NewDependentEntity.EntityDependentID}] !",ConsoleColor.Magenta);
						CConsoleHelpers.WriteLine($"NewDependentEntity.EntityPrincipalID [{NewDependentEntity.EntityPrincipalID}] !",ConsoleColor.Magenta);

						// ENTITY FRAMEWORK CORE zapise DB RECORDS do DB.
						// !!! STATE pridanych instancii ENTITY CLASSES je nastaveny na [Unchanged].
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							// !!! Nacita sa ID ENTITY, aby sa neskor mohla zmazat.
							ID=NewPrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"ENTITY with ID [{ID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT INSERTED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,NewPrincipalEntity);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,NewDependentEntity);

						// !!! IDs vsetkych PRIMARY KEYS a FOREIGN KEYS su nastavene na korektne VALUES nacitane z DB.
						CConsoleHelpers.WriteLine($"NewPrincipalEntity.EntityPrincipalID [{NewPrincipalEntity.EntityPrincipalID}] !",ConsoleColor.Magenta);
						CConsoleHelpers.WriteLine($"NewDependentEntity.EntityDependentID [{NewDependentEntity.EntityDependentID}] !",ConsoleColor.Magenta);
						CConsoleHelpers.WriteLine($"NewDependentEntity.EntityPrincipalID [{NewDependentEntity.EntityPrincipalID}] !",ConsoleColor.Magenta);
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

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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

						CEntityOneToManyPrincipal				Entity=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID).First();

						Context.EntitiesOneToManyPrincipal.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{ID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{ID}] was NOT DELETED !",ConsoleColor.Red);
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

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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
		private static void TestInsertRelationshipOfExistingObject()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													EntityMID=0;
			int													EntityNID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityManyToManyM[]					EntitiesM=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(EntitiesM);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyN[]					EntitiesN=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyN.PrintToConsole(EntitiesN);
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
						
						CEntityManyToManyN						NewEntityN=new CEntityManyToManyN("NEW ENTITY N");

						CConsoleHelpers.WriteLine("ENTITY N CREATED.",ConsoleColor.Yellow);

						Context.EntitiesManyToManyN.Add(NewEntityN);

						CConsoleHelpers.WriteLine("ENTITY N ADDED to CONTEXT.",ConsoleColor.Yellow);

						int										NumberOfModifiedEntities1=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities1>0)
						{
							EntityNID=NewEntityN.EntityNID;

							CConsoleHelpers.WriteLine($"ENTITY N with ID [{EntityNID}] was INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY N was NOT INSERTED !",ConsoleColor.Red);
						}

						CEntityManyToManyN						ExistingEntityN=Context.EntitiesManyToManyN.Where(P => P.EntityNID==EntityNID).First();

						CConsoleHelpers.WriteLine($"ENTITY N with ID [{ExistingEntityN.EntityNID}] read FROM DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N",Context,ExistingEntityN);

						CEntityManyToManyM						NewEntityM=new CEntityManyToManyM("NEW ENTITY M");

						CConsoleHelpers.WriteLine("ENTITY M CREATED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY M",Context,NewEntityM);

						CEntityManyToManyMN						NewEntityMN=new CEntityManyToManyMN("NEW ENTITY MN");

						CConsoleHelpers.WriteLine("ENTITY MN CREATED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY MN",Context,NewEntityMN);

						NewEntityMN.EntityN=ExistingEntityN;

						CConsoleHelpers.WriteLine("ENTITY N LINKED to ENTITY MN.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY MN",Context,NewEntityMN);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N",Context,NewEntityN);

						NewEntityM.EntitiesMN.Add(NewEntityMN);

						CConsoleHelpers.WriteLine("ENTITY MN ADDED to ENTITY M.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY M",Context,NewEntityM);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY MN",Context,NewEntityMN);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N",Context,ExistingEntityN);

						Context.EntitiesManyToManyM.Add(NewEntityM);

						CConsoleHelpers.WriteLine("ENTITY M ADDED to CONTEXT.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY M",Context,NewEntityM);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY MN",Context,NewEntityMN);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N",Context,ExistingEntityN);

						CConsoleHelpers.WriteLine($"NewEntityM.EntityMID [{NewEntityM.EntityMID}] !",ConsoleColor.Magenta);
						CConsoleHelpers.WriteLine($"ExistingEntityN.EntityNID [{ExistingEntityN.EntityNID}] !",ConsoleColor.Magenta);
						CConsoleHelpers.WriteLine($"NewEntityMN.EntityMID [{NewEntityMN.EntityMID}] !",ConsoleColor.Magenta);
						CConsoleHelpers.WriteLine($"NewEntityMN.EntityNID [{NewEntityMN.EntityNID}] !",ConsoleColor.Magenta);

						// ENTITY FRAMEWORK CORE zapise DB RECORDS do DB.
						// !!! STATE pridanych instancii ENTITY CLASSES je nastaveny na [Unchanged].
						int										NumberOfModifiedEntities2=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities2>0)
						{
							// !!! Nacita sa ID ENTITY, aby sa neskor mohla zmazat.
							EntityMID=NewEntityM.EntityMID;

							CConsoleHelpers.WriteLine($"ENTITIES were INSERTED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT INSERTED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M",Context,NewEntityM);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY MN",Context,NewEntityMN);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N",Context,ExistingEntityN);

						// !!! IDs vsetkych PRIMARY KEYS a FOREIGN KEYS su nastavene na korektne VALUES nacitane z DB.
						CConsoleHelpers.WriteLine($"NewEntityM.EntityMID [{NewEntityM.EntityMID}] !",ConsoleColor.Magenta);
						CConsoleHelpers.WriteLine($"ExistingEntityN.EntityNID [{ExistingEntityN.EntityNID}] !",ConsoleColor.Magenta);
						CConsoleHelpers.WriteLine($"NewEntityMN.EntityMID [{NewEntityMN.EntityMID}] !",ConsoleColor.Magenta);
						CConsoleHelpers.WriteLine($"NewEntityMN.EntityNID [{NewEntityMN.EntityNID}] !",ConsoleColor.Magenta);
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

						CEntityManyToManyM[]					EntitiesM=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(EntitiesM);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyN[]					EntitiesN=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyN.PrintToConsole(EntitiesN);
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

						CEntityManyToManyM						EntityM=Context.EntitiesManyToManyM.Where(P => P.EntityMID==EntityMID).First();
						CEntityManyToManyN						EntityN=Context.EntitiesManyToManyN.Where(P => P.EntityNID==EntityNID).First();

						Context.EntitiesManyToManyM.Remove(EntityM);
						Context.EntitiesManyToManyN.Remove(EntityN);

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

						CEntityManyToManyM[]					EntitiesM=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(EntitiesM);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyN[]					EntitiesN=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyN.PrintToConsole(EntitiesN);
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
		private static void TestUpdate()
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

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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

						CEntityOneToManyPrincipal				NewEntity=new CEntityOneToManyPrincipal("NEW ROW",null);

						Context.EntitiesOneToManyPrincipal.Add(NewEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						// !!! STATE pridanej instancie ENTITY CLASS je nastaveny na [Unchanged].
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							// !!! Nacita sa ID ENTITY, aby sa neskor mohla zmazat.
							ID=NewEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"ENTITY with ID [{ID}] was INSERTED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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

						CEntityOneToManyPrincipal				ExistingEntity=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID).First();

						CConsoleHelpers.WriteLine("ENTITY READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY",Context,ExistingEntity);

						// !!! Vykona sa zmena 1 PROPERTY.
						ExistingEntity.EntityPrincipalValue+=" !!!!!!!!!!!!!!!";

						CConsoleHelpers.WriteLine("ENTITY was MODIFIED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Modified].
						CDBHelpers.WriteEntityState("ENTITY",Context,ExistingEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						// !!! STATE pridanej instancie ENTITY CLASS je nastaveny na [Unchanged].
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{ID}] was UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY was NOT UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY",Context,ExistingEntity);
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

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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

						CEntityOneToManyPrincipal				Entity=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID).First();

						Context.EntitiesOneToManyPrincipal.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{ID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{ID}] was NOT DELETED !",ConsoleColor.Red);
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

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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
		private static void TestUpdateByCallingUpdateMethod()
		{
			CConsoleHelpers.WriteLineSeparator();

			CEntityOneToManyPrincipal							EntityFromDifferentContext=null;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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

						// !!! Vytvori sa ENTITY a ulozi do DB v SEPARATNOM DB CONTEXT.
						EntityFromDifferentContext=new CEntityOneToManyPrincipal("NEW ROW",null);

						Context.EntitiesOneToManyPrincipal.Add(EntityFromDifferentContext);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						// !!! STATE pridanej instancie ENTITY CLASS je nastaveny na [Unchanged].
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{EntityFromDifferentContext.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				// !!! Vytvori sa NOVY DB CONTEXT.
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY",Context,EntityFromDifferentContext);

						// !!! Vykona sa zmena 1 PROPERTY.
						EntityFromDifferentContext.EntityPrincipalValue+=" !!!!!!!!!!!!!!!";

						CConsoleHelpers.WriteLine("ENTITY was MODIFIED.",ConsoleColor.Yellow);

						// !!!!! STATE je nastaveny na [Detached], pretoze ENTITY este NEBOLA vlozena do DB CONTEXT.
						CDBHelpers.WriteEntityState("ENTITY",Context,EntityFromDifferentContext);

						// !!!!! Instancia ENTITY CLASS, ktora bola nacitana v INOM DB CONTEXT je vlozena do aktualneho DB CONTEXT volanim METHOD [EntityEntry<TEntity> DbContext.Update<TEntity>(TEntity Entity)].
						Context.Update(EntityFromDifferentContext);

						CConsoleHelpers.WriteLine("ENTITY was ADDED TO DB CONTEXT by UPDATE METHOD.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Modified], pretoze je v DB CONTEXT a BOLA MODIFIED.
						CDBHelpers.WriteEntityState("ENTITY",Context,EntityFromDifferentContext);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{EntityFromDifferentContext.EntityPrincipalID}] was UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{EntityFromDifferentContext.EntityPrincipalID}] was NOT UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE zmenenej instancie ENTITY CLASS je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY",Context,EntityFromDifferentContext);
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

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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

						CEntityOneToManyPrincipal				Entity=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==EntityFromDifferentContext.EntityPrincipalID).First();

						Context.EntitiesOneToManyPrincipal.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{EntityFromDifferentContext.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITY with ID [{EntityFromDifferentContext.EntityPrincipalID}] was NOT DELETED !",ConsoleColor.Red);
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

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyPrincipal.PrintToConsole(Entities);
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
		private static void TestUpdateRelationship1To1OnPrincipalEntity()
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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToOnePrincipal				Entity1=new CEntityOneToOnePrincipal("NEW ENTITY PRINCIPAL");
						CEntityOneToOneDependent				Entity2=new CEntityOneToOneDependent("NEW ENTITY DEPENDENT");

						Entity1.EntityDependent=Entity2;

						Context.EntitiesOneToOnePrincipal.Add(Entity1);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						// !!! STATE pridanej instancie ENTITY CLASS je nastaveny na [Unchanged].
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity1.EntityPrincipalID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						// !!!!! Pri RELATIONSHIP 1:1 je NUTNE pouzit LINQ OPERATOR [Include], aby ENTITY FRAMEWORK CORE vedel, ci DEPENDENT ENTITY EXISTUJE a pri jej nahradeni novou DEPENDENT ENTITY na tu povodnu vykonal DELETE. Ak by sa LINQ OPERATOR [Include] NEPOUZIL, ENTITY FRAMEWORK CORE by sa pokusil vlozit novu DEPENDENT ENTITY s ROVNAKYM FOREIGN KEY, cim by doslo k naruseniu FOREIGN KEY UNIQUE CONSTRAINT a DB by hodila EXCEPTION.
						CEntityOneToOnePrincipal				EntityPrincipal=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==ID).First();
						CEntityOneToOneDependent				EntityDependentOriginal=EntityPrincipal.EntityDependent;

						CConsoleHelpers.WriteLine("ENTITY PRINCIPAL READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT ORIGINAL",Context,EntityDependentOriginal);

						CEntityOneToOneDependent				EntityDependentNew=new CEntityOneToOneDependent("NEW MODIFIED ENTITY 2");

						CConsoleHelpers.WriteLine("ENTITY DEPENDENT CREATED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState($"ENTITY DEPENDENT NEW",Context,EntityDependentNew);

						// !!! UPDATE sa vykona nastavenim novej instancie DEPENDENT ENTITY do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						EntityPrincipal.EntityDependent=EntityDependentNew;

						CConsoleHelpers.WriteLine("ENTITY DEPENDENT NEW LINKED to ENTITY PRINCIPAL.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						// !!! STATE je nastaveny na [Deleted].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT ORIGINAL",Context,EntityDependentOriginal);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState($"ENTITY DEPENDENT NEW",Context,EntityDependentNew);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT ORIGINAL",Context,EntityDependentOriginal);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState($"ENTITY DEPENDENT NEW",Context,EntityDependentNew);
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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						CEntityOneToOnePrincipal				Entity=Context.EntitiesOneToOnePrincipal.Where(P => P.EntityPrincipalID==ID).First();

						Context.EntitiesOneToOnePrincipal.Remove(Entity);

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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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
		private static void TestUpdateRelationship1To1OnDependentEntityByChangingNavigationProperty()
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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToOnePrincipal				Entity1A=new CEntityOneToOnePrincipal("NEW ENTITY PRINCIPAL AAA");
						CEntityOneToOnePrincipal				Entity1B=new CEntityOneToOnePrincipal("NEW ENTITY PRINCIPAL BBB");
						CEntityOneToOneDependent				Entity2=new CEntityOneToOneDependent("NEW ENTITY DEPENDENT");

						Entity1A.EntityDependent=Entity2;

						Context.EntitiesOneToOnePrincipal.Add(Entity1A);
						Context.EntitiesOneToOnePrincipal.Add(Entity1B);
						Context.EntitiesOneToOneDependent.Add(Entity2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=Entity1A.EntityPrincipalID;
							ID2=Entity1B.EntityPrincipalID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						// !!!!! Pri RELATIONSHIP 1:1 je NUTNE pouzit LINQ OPERATOR [Include], aby ENTITY FRAMEWORK CORE vedel, ci DEPENDENT ENTITY EXISTUJE a pri jej nahradeni novou DEPENDENT ENTITY na tu povodnu vykonal DELETE. Ak by sa LINQ OPERATOR [Include] NEPOUZIL, ENTITY FRAMEWORK CORE by sa pokusil vlozit novu DEPENDENT ENTITY s ROVNAKYM FOREIGN KEY, cim by doslo k naruseniu FOREIGN KEY UNIQUE CONSTRAINT a DB by hodila EXCEPTION.
						CEntityOneToOnePrincipal				EntityPrincipal1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==ID1).First();
						CEntityOneToOneDependent				EntityDependent=EntityPrincipal1.EntityDependent;
						// !!!!! Pri RELATIONSHIP 1:1 je NUTNE pouzit LINQ OPERATOR [Include], aby ENTITY FRAMEWORK CORE vedel, ci DEPENDENT ENTITY EXISTUJE a pri jej nahradeni novou DEPENDENT ENTITY na tu povodnu vykonal DELETE. Ak by sa LINQ OPERATOR [Include] NEPOUZIL, ENTITY FRAMEWORK CORE by sa pokusil vlozit novu DEPENDENT ENTITY s ROVNAKYM FOREIGN KEY, cim by doslo k naruseniu FOREIGN KEY UNIQUE CONSTRAINT a DB by hodila EXCEPTION.
						CEntityOneToOnePrincipal				EntityPrincipal2=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==ID2).First();

						CConsoleHelpers.WriteLine("ENTITIES READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);

						// !!! UPDATE sa vykona nastavenim novej instancie PRINCIPAL ENTITY v NAVIGATION PROPERTY DEPENDENT ENTITY.
						EntityDependent.EntityPrincipal=EntityPrincipal2;

						CConsoleHelpers.WriteLine("ENTITY DEPENDENT LINKED from ENTITY PRINCIPAL 1 to ENTITY PRINCIPAL 2 by CHANGING NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Modified].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);
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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						CEntityOneToOnePrincipal				Entity1=Context.EntitiesOneToOnePrincipal.Where(P => P.EntityPrincipalID==ID1).First();
						CEntityOneToOnePrincipal				Entity2=Context.EntitiesOneToOnePrincipal.Where(P => P.EntityPrincipalID==ID2).First();

						Context.EntitiesOneToOnePrincipal.Remove(Entity1);
						Context.EntitiesOneToOnePrincipal.Remove(Entity2);

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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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
		private static void TestUpdateRelationship1To1OnDependentEntityByChangingForeignKey()
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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToOnePrincipal				Entity1A=new CEntityOneToOnePrincipal("NEW ENTITY PRINCIPAL AAA");
						CEntityOneToOnePrincipal				Entity1B=new CEntityOneToOnePrincipal("NEW ENTITY PRINCIPAL BBB");
						CEntityOneToOneDependent				Entity2=new CEntityOneToOneDependent("NEW ENTITY DEPENDENT");

						Entity1A.EntityDependent=Entity2;

						Context.EntitiesOneToOnePrincipal.Add(Entity1A);
						Context.EntitiesOneToOnePrincipal.Add(Entity1B);
						Context.EntitiesOneToOneDependent.Add(Entity2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=Entity1A.EntityPrincipalID;
							ID2=Entity1B.EntityPrincipalID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						// !!!!! Pri RELATIONSHIP 1:1 je NUTNE pouzit LINQ OPERATOR [Include], aby ENTITY FRAMEWORK CORE vedel, ci DEPENDENT ENTITY EXISTUJE a pri jej nahradeni novou DEPENDENT ENTITY na tu povodnu vykonal DELETE. Ak by sa LINQ OPERATOR [Include] NEPOUZIL, ENTITY FRAMEWORK CORE by sa pokusil vlozit novu DEPENDENT ENTITY s ROVNAKYM FOREIGN KEY, cim by doslo k naruseniu FOREIGN KEY UNIQUE CONSTRAINT a DB by hodila EXCEPTION.
						CEntityOneToOnePrincipal				EntityPrincipal1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==ID1).First();
						CEntityOneToOneDependent				EntityDependent=EntityPrincipal1.EntityDependent;
						// !!!!! Pri RELATIONSHIP 1:1 je NUTNE pouzit LINQ OPERATOR [Include], aby ENTITY FRAMEWORK CORE vedel, ci DEPENDENT ENTITY EXISTUJE a pri jej nahradeni novou DEPENDENT ENTITY na tu povodnu vykonal DELETE. Ak by sa LINQ OPERATOR [Include] NEPOUZIL, ENTITY FRAMEWORK CORE by sa pokusil vlozit novu DEPENDENT ENTITY s ROVNAKYM FOREIGN KEY, cim by doslo k naruseniu FOREIGN KEY UNIQUE CONSTRAINT a DB by hodila EXCEPTION.
						CEntityOneToOnePrincipal				EntityPrincipal2=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==ID2).First();

						CConsoleHelpers.WriteLine("ENTITIES READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);

						// !!! UPDATE sa vykona nastavenim FOREIGN KEY PROPERTY v DEPENDENT ENTITY.
						// !!! ENTITY DEPENDENT, ktora bola priradena ENTITY PRINCIPAL 1 bude priradena ENTITY PRINCIPAL 1. NAVIGATION PROPERTY v ENTITY PRINCIPAL 1 odkazujuci na ENTITY DEPENDENT bude nastaveny na NULL.
						EntityDependent.EntityPrincipalID=EntityPrincipal2.EntityPrincipalID;

						CConsoleHelpers.WriteLine("ENTITY DEPENDENT LINKED from ENTITY PRINCIPAL 1 to ENTITY PRINCIPAL 2 by CHANGING FOREIGN KEY PROPERTY.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Modified].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);
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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						CEntityOneToOnePrincipal				Entity1=Context.EntitiesOneToOnePrincipal.Where(P => P.EntityPrincipalID==ID1).First();
						CEntityOneToOnePrincipal				Entity2=Context.EntitiesOneToOnePrincipal.Where(P => P.EntityPrincipalID==ID2).First();

						Context.EntitiesOneToOnePrincipal.Remove(Entity1);
						Context.EntitiesOneToOnePrincipal.Remove(Entity2);

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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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
		private static void TestUpdateRelationship1To1ByAddingDependentEntity()
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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						// !!! Vytvori sa ENTITY a ulozi do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToOnePrincipal				Entity=new CEntityOneToOnePrincipal("NEW ENTITY PRINCIPAL");

						Context.EntitiesOneToOnePrincipal.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityPrincipalID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						// !!!!! Pri RELATIONSHIP 1:1 je NUTNE pouzit LINQ OPERATOR [Include], aby ENTITY FRAMEWORK CORE vedel, ci DEPENDENT ENTITY EXISTUJE a pri jej nahradeni novou DEPENDENT ENTITY na tu povodnu vykonal DELETE. Ak by sa LINQ OPERATOR [Include] NEPOUZIL, ENTITY FRAMEWORK CORE by sa pokusil vlozit novu DEPENDENT ENTITY s ROVNAKYM FOREIGN KEY, cim by doslo k naruseniu FOREIGN KEY UNIQUE CONSTRAINT a DB by hodila EXCEPTION.
						CEntityOneToOnePrincipal				EntityPrincipal=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==ID).First();

						CConsoleHelpers.WriteLine("ENTITY PRINCIPAL READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						// Vytvori sa DEPENDENT ENTITY.
						CEntityOneToOneDependent				EntityDependent=new CEntityOneToOneDependent("NEW ENTITY DEPENDENT");

						CConsoleHelpers.WriteLine("ENTITY DEPENDENT CREATED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! UPDATE sa vykona nastavenim FOREIGN KEY PROPERTY v DEPENDENT ENTITY.
						EntityDependent.EntityPrincipalID=EntityPrincipal.EntityPrincipalID;

						CConsoleHelpers.WriteLine("NEW ENTITY DEPENDENT LINKED to ENTITY PRINCIPAL by CHANGING FOREIGN KEY PROPERTY.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! UPDATE sa vykona pridanim novej instancie DEPENDENT ENTITY priamo do DB CONTEXT.
						// !!!!! DEPENDENT ENTITY MUSI mat nastaveny validny FOREIGN KEY.
						Context.EntitiesOneToOneDependent.Add(EntityDependent);

						CConsoleHelpers.WriteLine("NEW ENTITY DEPENDENT ADDED to CONTEXT.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);
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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						CEntityOneToOnePrincipal				Entity=Context.EntitiesOneToOnePrincipal.Where(P => P.EntityPrincipalID==ID).First();

						Context.EntitiesOneToOnePrincipal.Remove(Entity);

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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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
		private static void TestUpdateRelationship1To1ByAddingDependentEntityNotUsingIncludeOperator()
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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToOneDependent				EntityDependent=new CEntityOneToOneDependent("NEW ENTITY DEPENDENT");
						CEntityOneToOnePrincipal				EntityPrincipal=new CEntityOneToOnePrincipal("NEW ENTITY PRINCIPAL");

						EntityPrincipal.EntityDependent=EntityDependent;

						Context.EntitiesOneToOnePrincipal.Add(EntityPrincipal);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=EntityPrincipal.EntityPrincipalID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						// !!!!! Ak sa pouzije LINQ OPERATOR [Include], ktorym sa nacita DEPENDENT ENTITY, tak pri nahradeni jednej DEPENDENT ENTITY za inu ENTITY FRAMEWORK CORE zisti, ze povodna DEPENDENT ENTITY musi byt DELETED a az potom je mozne pridat novu DEPENDENT ENTITY, ktorej FOREIGN KEY bude odkazovat na PRINCIPAL ENTITY. UPDATE teda zbehne bez problemov.
						//CEntityOneToOnePrincipal				EntityPrincipal=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).Where(P => P.EntityPrincipalID==ID).First();

						// !!!!! HODI EXCEPTION.
						// !!!!! Ak sa pouzije LINQ OPERATOR [Include], ktorym sa nacita DEPENDENT ENTITY NEPOUZIJE, tak pri ENTITY FRAMEWORK CORE nezisti, ze pri priradeni novej DEPENDENT ENTITY do PRINCIPAL ENTITY malo dojst k DELETE povodnej DEPENDENT ENTITY, kedze ta nebola nacitana do DB CONTEXT pomocou LINQ OPERATOR [Include]. Tym padom sa ENTITY FRAMEWORK CORE pokusi vlozit novu DEPENDENT ENTITY, ktora ma ROVNAKY FOREIGN KEY ako povodna DEPENDENT ENTITY. Pri RELATIONSHIP 1:1 vsak dojde k naruseniu FOREIGN KEY CONTRAINT, ktory vyzaduje, aby FOREIGN KEYS v DEPENDENT ENTITIES boli UNIKATNE. Vysledkom je hodenie EXCEPTION.
						CEntityOneToOnePrincipal				EntityPrincipal=Context.EntitiesOneToOnePrincipal.Where(P => P.EntityPrincipalID==ID).First();

						CConsoleHelpers.WriteLine("ENTITY PRINCIPAL READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						// Vytvori sa DEPENDENT ENTITY.
						CEntityOneToOneDependent				EntityDependent=new CEntityOneToOneDependent("MODIFIED ENTITY DEPENDENT");

						CConsoleHelpers.WriteLine("ENTITY DEPENDENT CREATED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! UPDATE sa vykona nastavenim FOREIGN KEY PROPERTY v DEPENDENT ENTITY.
						EntityDependent.EntityPrincipalID=EntityPrincipal.EntityPrincipalID;

						CConsoleHelpers.WriteLine("NEW ENTITY DEPENDENT LINKED to ENTITY PRINCIPAL by CHANGING FOREIGN KEY PROPERTY.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! UPDATE sa vykona pridanim novej instancie DEPENDENT ENTITY priamo do DB CONTEXT.
						// !!!!! DEPENDENT ENTITY MUSI mat nastaveny validny FOREIGN KEY.
						Context.EntitiesOneToOneDependent.Add(EntityDependent);

						CConsoleHelpers.WriteLine("NEW ENTITY DEPENDENT ADDED to CONTEXT.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);
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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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

						CEntityOneToOnePrincipal				Entity=Context.EntitiesOneToOnePrincipal.Where(P => P.EntityPrincipalID==ID).First();

						Context.EntitiesOneToOnePrincipal.Remove(Entity);

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

						CEntityOneToOnePrincipal[]				Entities1=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToOneDependent[]				Entities2=Context.EntitiesOneToOneDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToOneDependent.PrintToConsole(Entities2);
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
		private static void TestUpdateRelationship1ToNOnPrincipalEntityByAddingExistingDependentEntityToCollection()
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToManyDependent				EntityDependent=new CEntityOneToManyDependent("NEW ENTITY DEPENDENT");
						CEntityOneToManyPrincipal				EntityPrincipal1=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL 1",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{EntityDependent}));
						CEntityOneToManyPrincipal				EntityPrincipal2=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL 2",new List<CEntityOneToManyDependent>());

						Context.EntitiesOneToManyPrincipal.Add(EntityPrincipal1);
						Context.EntitiesOneToManyPrincipal.Add(EntityPrincipal2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityPrincipal1.EntityPrincipalID;
							ID2=EntityPrincipal2.EntityPrincipalID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				EntityPrincipal1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID1).First();
						CEntityOneToManyDependent				EntityDependent=EntityPrincipal1.EntitiesDependent.ElementAt(0);
						CEntityOneToManyPrincipal				EntityPrincipal2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID2).First();

						CConsoleHelpers.WriteLine("ENTITIES READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);

						// !!! UPDATE sa vykona pridanim existujucej DEPENDENT ENTITY do NAVIGATION PROPERTY PRINCIPAL PROPERTY.
						// !!! DEPENDENT ENTITY, ktora bola priradena PRINCIPAL ENTITY 1 bude priradena PRINCIPAL ENTITY 2. DEPENDENT ENTITY z PRINCIPAL ENTITY 1 bude odstranena.
						EntityPrincipal2.EntitiesDependent.Add(EntityDependent);

						CConsoleHelpers.WriteLine("ENTITY DEPENDENT LINKED from ENTITY PRINCIPAL 1 to ENTITY PRINCIPAL 2.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Modified].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				Entity1=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID1).First();
						CEntityOneToManyPrincipal				Entity2=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID2).First();

						Context.EntitiesOneToManyPrincipal.Remove(Entity1);
						Context.EntitiesOneToManyPrincipal.Remove(Entity2);

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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
		private static void TestUpdateRelationship1ToNOnPrincipalEntityByReplacingNavigationPropertyCollection()
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToManyDependent				EntityDependent1=new CEntityOneToManyDependent("NEW DEPENDENT ENTITY 1");
						CEntityOneToManyDependent				EntityDependent2=new CEntityOneToManyDependent("NEW DEPENDENT ENTITY 2");
						CEntityOneToManyPrincipal				EntityPrincipal=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{EntityDependent1,EntityDependent2}));

						Context.EntitiesOneToManyPrincipal.Add(EntityPrincipal);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=EntityPrincipal.EntityPrincipalID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

						// !!!!! Pri tomto type UPDATE je NUTNE nacitat DEPENDENT ENTITIES pomocou LINQ OPERATOR [Include], inak ENTITY FRAMEWORK CORE nebude vediet o tom, ze v DB su existujuce DEPENDENT ENTITIES a pri vymene NAVIGATIONAL PROPERTY COLLECTION na DEPENDENT ENTITIES NEDOJDE k DELETE povodnych DEPENDENT ENTITIES.
						CEntityOneToManyPrincipal				EntityPrincipal=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID).First();
						ICollection<CEntityOneToManyDependent>	EntitiesDependentOriginal=EntityPrincipal.EntitiesDependent;

						CConsoleHelpers.WriteLine("ENTITY PRINCIPAL READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						for(int Index=0;Index<EntitiesDependentOriginal.Count;Index++)
						{
							// !!! STATE je nastaveny na [Unchanged].
							CDBHelpers.WriteEntityState($"ORIGINAL ENTITY DEPENDENT [{(Index+1)}]",Context,EntitiesDependentOriginal.ElementAt(Index));
						}

						CEntityOneToManyDependent				EntityDependent1=new CEntityOneToManyDependent("NEW DEPENDENT ENTITY 11111111111 !!!!!!!!!!");
						CEntityOneToManyDependent				EntityDependent2=new CEntityOneToManyDependent("NEW DEPENDENT ENTITY 22222222222 !!!!!!!!!!");
						List<CEntityOneToManyDependent>			EntitiesDependentNew=new List<CEntityOneToManyDependent>();

						EntitiesDependentNew.Add(EntityDependent1);
						EntitiesDependentNew.Add(EntityDependent2);

						CConsoleHelpers.WriteLine("NEW ENTITIES DEPENDENT CREATED.",ConsoleColor.Yellow);

						for(int Index=0;Index<EntitiesDependentNew.Count;Index++)
						{
							// !!! STATE je nastaveny na [Detached].
							CDBHelpers.WriteEntityState($"NEW ENTITY DEPENDENT [{(Index+1)}]",Context,EntitiesDependentNew.ElementAt(Index));
						}

						// !!! UPDATE sa vykona NAHRADENIM NAVIGATION PROPERTY COLLECTION za novu COLLECTION.
						EntityPrincipal.EntitiesDependent=EntitiesDependentNew;

						CConsoleHelpers.WriteLine("NEW ENTITIES DEPENDENT LINKED to PRINCIPAL ENTITY.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						for(int Index=0;Index<EntitiesDependentOriginal.Count;Index++)
						{
							// !!! STATE je nastaveny na [Deleted].
							CDBHelpers.WriteEntityState($"ORIGINAL ENTITY DEPENDENT [{(Index+1)}]",Context,EntitiesDependentOriginal.ElementAt(Index));
						}

						for(int Index=0;Index<EntitiesDependentNew.Count;Index++)
						{
							// !!! STATE je nastaveny na [Added].
							CDBHelpers.WriteEntityState($"NEW ENTITY DEPENDENT [{(Index+1)}]",Context,EntitiesDependentNew.ElementAt(Index));
						}

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						for(int Index=0;Index<EntitiesDependentOriginal.Count;Index++)
						{
							// !!! STATE je nastaveny na [Detached].
							CDBHelpers.WriteEntityState($"ORIGINAL ENTITY DEPENDENT [{(Index+1)}]",Context,EntitiesDependentOriginal.ElementAt(Index));
						}

						for(int Index=0;Index<EntitiesDependentNew.Count;Index++)
						{
							// !!! STATE je nastaveny na [Unchanged].
							CDBHelpers.WriteEntityState($"NEW ENTITY DEPENDENT [{(Index+1)}]",Context,EntitiesDependentNew.ElementAt(Index));
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				Entity=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID).First();

						Context.EntitiesOneToManyPrincipal.Remove(Entity);

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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
		private static void TestUpdateRelationship1ToNOnDependentEntityByChangingNavigationProperty()
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToManyDependent				EntityDependent=new CEntityOneToManyDependent("NEW ENTITY DEPENDENT");
						CEntityOneToManyPrincipal				EntityPrincipal1=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL 1",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{EntityDependent}));
						CEntityOneToManyPrincipal				EntityPrincipal2=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL 2",new List<CEntityOneToManyDependent>());

						Context.EntitiesOneToManyPrincipal.Add(EntityPrincipal1);
						Context.EntitiesOneToManyPrincipal.Add(EntityPrincipal2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityPrincipal1.EntityPrincipalID;
							ID2=EntityPrincipal2.EntityPrincipalID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				EntityPrincipal1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID1).First();
						CEntityOneToManyDependent				EntityDependent=EntityPrincipal1.EntitiesDependent.ElementAt(0);
						CEntityOneToManyPrincipal				EntityPrincipal2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID2).First();

						CConsoleHelpers.WriteLine("ENTITIES READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);

						// !!! UPDATE sa vykona nastavenim PRINCIPAL ENTITY v NAVIGATION PROPERTY DEPENDENT ENTITY.
						// !!! DEPENDENT ENTITY, ktora bola priradena PRINCIPAL ENTITY 1 bude priradena PRINCIPAL ENTITY 2. DEPENDENT ENTITY z PRINCIPAL ENTITY 1 bude odstranena.
						EntityDependent.EntityPrincipal=EntityPrincipal2;

						CConsoleHelpers.WriteLine("ENTITY DEPENDENT LINKED from ENTITY PRINCIPAL 1 to ENTITY PRINCIPAL 2 by CHANGING NAVIGATION PROPERTY of DEPENDENT ENTITY.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Modified].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				Entity1=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID1).First();
						CEntityOneToManyPrincipal				Entity2=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID2).First();

						Context.EntitiesOneToManyPrincipal.Remove(Entity1);
						Context.EntitiesOneToManyPrincipal.Remove(Entity2);

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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
		private static void TestUpdateRelationship1ToNOnDependentEntityByChangingForeignKey()
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToManyDependent				EntityDependent=new CEntityOneToManyDependent("NEW ENTITY DEPENDENT");
						CEntityOneToManyPrincipal				EntityPrincipal1=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL 1",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{EntityDependent}));
						CEntityOneToManyPrincipal				EntityPrincipal2=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL 2",new List<CEntityOneToManyDependent>());

						Context.EntitiesOneToManyPrincipal.Add(EntityPrincipal1);
						Context.EntitiesOneToManyPrincipal.Add(EntityPrincipal2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityPrincipal1.EntityPrincipalID;
							ID2=EntityPrincipal2.EntityPrincipalID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				EntityPrincipal1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID1).First();
						CEntityOneToManyDependent				EntityDependent=EntityPrincipal1.EntitiesDependent.ElementAt(0);
						CEntityOneToManyPrincipal				EntityPrincipal2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID2).First();

						CConsoleHelpers.WriteLine("ENTITIES READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);

						// !!! UPDATE sa vykona nastavenim FOREIGN KEY PROPERTY v DEPENDENT ENTITY.
						// !!! DEPENDENT ENTITY, ktora bola priradena PRINCIPAL ENTITY 1 bude priradena PRINCIPAL ENTITY 2. DEPENDENT ENTITY z PRINCIPAL ENTITY 1 bude odstranena.
						EntityDependent.EntityPrincipalID=EntityPrincipal2.EntityPrincipalID;

						CConsoleHelpers.WriteLine("ENTITY DEPENDENT LINKED from ENTITY PRINCIPAL 1 to ENTITY PRINCIPAL 2 by CHANGING FOREIGN KEY of DEPENDENT ENTITY.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Modified].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 1",Context,EntityPrincipal1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL 2",Context,EntityPrincipal2);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				Entity1=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID1).First();
						CEntityOneToManyPrincipal				Entity2=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID2).First();

						Context.EntitiesOneToManyPrincipal.Remove(Entity1);
						Context.EntitiesOneToManyPrincipal.Remove(Entity2);

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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
		private static void TestUpdateRelationship1ToNByAddingDependentEntity()
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvori sa ENTITY a ulozi do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToManyPrincipal				Entity=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL",new List<CEntityOneToManyDependent>());

						Context.EntitiesOneToManyPrincipal.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityPrincipalID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				EntityPrincipal=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID).First();

						CConsoleHelpers.WriteLine("ENTITY PRINCIPAL READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						CEntityOneToManyDependent				EntityDependent=new CEntityOneToManyDependent("NEW ENTITY DEPENDENT");

						CConsoleHelpers.WriteLine("ENTITY DEPENDENT CREATED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						// !!! UPDATE sa vykona pridanim novej instancie DEPENDENT ENTITY do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						EntityPrincipal.EntitiesDependent.Add(EntityDependent);

						CConsoleHelpers.WriteLine("ENTITY DEPENDENT ADDED to ENTITY PRINCIPAL.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT",Context,EntityDependent);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				Entity=Context.EntitiesOneToManyPrincipal.Where(P => P.EntityPrincipalID==ID).First();

						Context.EntitiesOneToManyPrincipal.Remove(Entity);

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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
		private static void TestUpdateRelationshipMToNOnPrincipalEntity()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityManyToManyM[]					Entities1=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyN[]					Entities2=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyN.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMN[]					Entities3=Context.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMN.PrintToConsole(Entities3);
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

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityManyToManyM						EntityM1=new CEntityManyToManyM("NEW ENTITY M 111");
						CEntityManyToManyM						EntityM2=new CEntityManyToManyM("NEW ENTITY M 222");
						CEntityManyToManyN						EntityN1=new CEntityManyToManyN("NEW ENTITY N 111");
						CEntityManyToManyN						EntityN2=new CEntityManyToManyN("NEW ENTITY N 222");

						Context.EntitiesManyToManyM.Add(EntityM1);
						Context.EntitiesManyToManyM.Add(EntityM2);
						Context.EntitiesManyToManyN.Add(EntityN1);
						Context.EntitiesManyToManyN.Add(EntityN2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityM1.EntityMID;
							ID2=EntityM2.EntityMID;
							ID3=EntityN1.EntityNID;
							ID4=EntityN2.EntityNID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityManyToManyM[]					Entities1=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyN[]					Entities2=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyN.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMN[]					Entities3=Context.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMN.PrintToConsole(Entities3);
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

						CEntityManyToManyM						EntityM1=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).Where(P => P.EntityMID==ID1).First();
						CEntityManyToManyM						EntityM2=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).Where(P => P.EntityMID==ID2).First();
						CEntityManyToManyN						EntityN1=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).Where(P => P.EntityNID==ID3).First();
						CEntityManyToManyN						EntityN2=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).Where(P => P.EntityNID==ID4).First();

						CConsoleHelpers.WriteLine("ENTITIES READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 1",Context,EntityM1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 2",Context,EntityM2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 1",Context,EntityN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 2",Context,EntityN2);

						CEntityManyToManyMN						EntityMN1=new CEntityManyToManyMN("NEW LINK 111");
						CEntityManyToManyMN						EntityMN2=new CEntityManyToManyMN("NEW LINK 222");

						CConsoleHelpers.WriteLine("ENTITIES MN CREATED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY MN 1",Context,EntityMN1);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY MN 2",Context,EntityMN2);

						// !!! UPDATE sa vykona pridanim novej instancie DEPENDENT ENTITY do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						EntityM1.EntitiesMN.Add(EntityMN1);

						CConsoleHelpers.WriteLine("ENTITY MN 1 ADDED to ENTITY M 1 NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! UPDATE sa vykona pridanim novej instancie DEPENDENT ENTITY do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						EntityM2.EntitiesMN.Add(EntityMN2);

						CConsoleHelpers.WriteLine("ENTITY MN 2 ADDED to ENTITY M 2 NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! UPDATE sa vykona pridanim novej instancie DEPENDENT ENTITY do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						EntityN1.EntitiesMN.Add(EntityMN1);

						CConsoleHelpers.WriteLine("ENTITY MN 1 ADDED to ENTITY N 1 NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! UPDATE sa vykona pridanim novej instancie DEPENDENT ENTITY do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						EntityN2.EntitiesMN.Add(EntityMN2);

						CConsoleHelpers.WriteLine("ENTITY MN 2 ADDED to ENTITY N 2 NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 1",Context,EntityM1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 2",Context,EntityM2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 1",Context,EntityN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 2",Context,EntityN2);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY MN 1",Context,EntityMN1);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY MN 2",Context,EntityMN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 1",Context,EntityM1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 2",Context,EntityM2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 1",Context,EntityN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 2",Context,EntityN2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY MN 1",Context,EntityMN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY MN 2",Context,EntityMN2);
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

						CEntityManyToManyM[]					Entities1=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyN[]					Entities2=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyN.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMN[]					Entities3=Context.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMN.PrintToConsole(Entities3);
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

						CEntityManyToManyM						EntityM1=Context.EntitiesManyToManyM.Where(P => P.EntityMID==ID1).First();
						CEntityManyToManyM						EntityM2=Context.EntitiesManyToManyM.Where(P => P.EntityMID==ID2).First();
						CEntityManyToManyN						EntityN1=Context.EntitiesManyToManyN.Where(P => P.EntityNID==ID3).First();
						CEntityManyToManyN						EntityN2=Context.EntitiesManyToManyN.Where(P => P.EntityNID==ID4).First();

						Context.EntitiesManyToManyM.Remove(EntityM1);
						Context.EntitiesManyToManyM.Remove(EntityM2);
						Context.EntitiesManyToManyN.Remove(EntityN1);
						Context.EntitiesManyToManyN.Remove(EntityN2);

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

						CEntityManyToManyM[]					Entities1=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyN[]					Entities2=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyN.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMN[]					Entities3=Context.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMN.PrintToConsole(Entities3);
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
		private static void TestUpdateRelationshipMToNByAddingDependentEntity()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityManyToManyM[]					Entities1=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyN[]					Entities2=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyN.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMN[]					Entities3=Context.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMN.PrintToConsole(Entities3);
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

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityManyToManyM						EntityM1=new CEntityManyToManyM("NEW ENTITY M 111");
						CEntityManyToManyM						EntityM2=new CEntityManyToManyM("NEW ENTITY M 222");
						CEntityManyToManyN						EntityN1=new CEntityManyToManyN("NEW ENTITY N 111");
						CEntityManyToManyN						EntityN2=new CEntityManyToManyN("NEW ENTITY N 222");

						Context.EntitiesManyToManyM.Add(EntityM1);
						Context.EntitiesManyToManyM.Add(EntityM2);
						Context.EntitiesManyToManyN.Add(EntityN1);
						Context.EntitiesManyToManyN.Add(EntityN2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityM1.EntityMID;
							ID2=EntityM2.EntityMID;
							ID3=EntityN1.EntityNID;
							ID4=EntityN2.EntityNID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityManyToManyM[]					Entities1=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyN[]					Entities2=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyN.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMN[]					Entities3=Context.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMN.PrintToConsole(Entities3);
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

						CEntityManyToManyM						EntityM1=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).Where(P => P.EntityMID==ID1).First();
						CEntityManyToManyM						EntityM2=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).Where(P => P.EntityMID==ID2).First();
						CEntityManyToManyN						EntityN1=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).Where(P => P.EntityNID==ID3).First();
						CEntityManyToManyN						EntityN2=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).Where(P => P.EntityNID==ID4).First();

						CConsoleHelpers.WriteLine("ENTITIES READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 1",Context,EntityM1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 2",Context,EntityM2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 1",Context,EntityN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 2",Context,EntityN2);

						CEntityManyToManyMN						EntityMN1=new CEntityManyToManyMN("NEW LINK 111");
						CEntityManyToManyMN						EntityMN2=new CEntityManyToManyMN("NEW LINK 222");

						CConsoleHelpers.WriteLine("ENTITIES MN CREATED.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY MN 1",Context,EntityMN1);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY MN 2",Context,EntityMN2);

						// !!! Vytvori sa LINK medzi PRINCIPAL ENTITY a DEPENDENT ENTITY nastavenim NAVIGATION PROPERTY na DEPENDENT ENTITY.
						EntityMN1.EntityM=EntityM1;

						CConsoleHelpers.WriteLine("ENTITY MN 1 LINKED to ENTITY M 1 by setting ENTITY MN NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! Vytvori sa LINK medzi PRINCIPAL ENTITY a DEPENDENT ENTITY nastavenim NAVIGATION PROPERTY na DEPENDENT ENTITY.
						EntityMN1.EntityN=EntityN1;

						CConsoleHelpers.WriteLine("ENTITY MN 1 LINKED to ENTITY N 1 by setting ENTITY MN NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! Vytvori sa LINK medzi PRINCIPAL ENTITY a DEPENDENT ENTITY nastavenim NAVIGATION PROPERTY na DEPENDENT ENTITY.
						EntityMN2.EntityM=EntityM2;

						CConsoleHelpers.WriteLine("ENTITY MN 2 LINKED to ENTITY M 2 by setting ENTITY MN NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! Vytvori sa LINK medzi PRINCIPAL ENTITY a DEPENDENT ENTITY nastavenim NAVIGATION PROPERTY na DEPENDENT ENTITY.
						EntityMN2.EntityN=EntityN2;

						CConsoleHelpers.WriteLine("ENTITY MN 2 LINKED to ENTITY N 2 by setting ENTITY MN NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 1",Context,EntityM1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 2",Context,EntityM2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 1",Context,EntityN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 2",Context,EntityN2);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY MN 1",Context,EntityMN1);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY MN 2",Context,EntityMN2);

						// !!! UPDATE sa vykona pridanim novej instancie DEPENDENT ENTITY priamo do DB CONTEXT.
						Context.EntitiesManyToManyMN.Add(EntityMN1);

						CConsoleHelpers.WriteLine("ENTITY MN 1 ADDED to CONTEXT.",ConsoleColor.Yellow);

						// !!! UPDATE sa vykona pridanim novej instancie DEPENDENT ENTITY priamo do DB CONTEXT.
						Context.EntitiesManyToManyMN.Add(EntityMN2);

						CConsoleHelpers.WriteLine("ENTITY MN 2 ADDED to CONTEXT.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 1",Context,EntityM1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 2",Context,EntityM2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 1",Context,EntityN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 2",Context,EntityN2);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY MN 1",Context,EntityMN1);

						// !!! STATE je nastaveny na [Added].
						CDBHelpers.WriteEntityState("ENTITY MN 2",Context,EntityMN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 1",Context,EntityM1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 2",Context,EntityM2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 1",Context,EntityN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 2",Context,EntityN2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY MN 1",Context,EntityMN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY MN 2",Context,EntityMN2);
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

						CEntityManyToManyM[]					Entities1=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyN[]					Entities2=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyN.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMN[]					Entities3=Context.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMN.PrintToConsole(Entities3);
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

						CEntityManyToManyM						EntityM1=Context.EntitiesManyToManyM.Where(P => P.EntityMID==ID1).First();
						CEntityManyToManyM						EntityM2=Context.EntitiesManyToManyM.Where(P => P.EntityMID==ID2).First();
						CEntityManyToManyN						EntityN1=Context.EntitiesManyToManyN.Where(P => P.EntityNID==ID3).First();
						CEntityManyToManyN						EntityN2=Context.EntitiesManyToManyN.Where(P => P.EntityNID==ID4).First();

						Context.EntitiesManyToManyM.Remove(EntityM1);
						Context.EntitiesManyToManyM.Remove(EntityM2);
						Context.EntitiesManyToManyN.Remove(EntityN1);
						Context.EntitiesManyToManyN.Remove(EntityN2);

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

						CEntityManyToManyM[]					Entities1=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyN[]					Entities2=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

						CEntityManyToManyN.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyMN[]					Entities3=Context.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

						CEntityManyToManyMN.PrintToConsole(Entities3);
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
		private static void TestCascadeDelete()
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityOneToManyDependent				EntityDependent1=new CEntityOneToManyDependent("NEW ENTITY DEPENDENT 1");
						CEntityOneToManyDependent				EntityDependent2=new CEntityOneToManyDependent("NEW ENTITY DEPENDENT 2");
						CEntityOneToManyPrincipal				EntityPrincipal=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{EntityDependent1,EntityDependent2}));

						Context.EntitiesOneToManyPrincipal.Add(EntityPrincipal);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=EntityPrincipal.EntityPrincipalID;

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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				EntityPrincipal=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID).First();

						CConsoleHelpers.WriteLine("ENTITIES READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						for(int Index=0;Index<EntityPrincipal.EntitiesDependent.Count;Index++)
						{
							CEntityOneToManyDependent			EntityDependent=EntityPrincipal.EntitiesDependent.ElementAt(Index);

							// !!! STATE je nastaveny na [Unchanged].
							CDBHelpers.WriteEntityState($"ENTITY DEPENDENT [{(Index+1)}]",Context,EntityDependent);
						}

						Context.EntitiesOneToManyPrincipal.Remove(EntityPrincipal);

						CConsoleHelpers.WriteLine("ENTITY PRINCIPAL DELETED from DB CONTEXT.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Deleted].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						for(int Index=0;Index<EntityPrincipal.EntitiesDependent.Count;Index++)
						{
							CEntityOneToManyDependent			EntityDependent=EntityPrincipal.EntitiesDependent.ElementAt(Index);

							// !!! STATE je nastaveny na [Deleted].
							CDBHelpers.WriteEntityState($"ENTITY DEPENDENT [{(Index+1)}]",Context,EntityDependent);
						}

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						for(int Index=0;Index<EntityPrincipal.EntitiesDependent.Count;Index++)
						{
							CEntityOneToManyDependent			EntityDependent=EntityPrincipal.EntitiesDependent.ElementAt(Index);

							// !!! STATE je nastaveny na [Detached].
							CDBHelpers.WriteEntityState($"ENTITY DEPENDENT [{(Index+1)}]",Context,EntityDependent);
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
		private static void TestNonCascadeDelete()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipal[]			Entities1=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependent[]			Entities2=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependent.PrintToConsole(Entities2);
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

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityZeroToManyDependent				EntityDependent1=new CEntityZeroToManyDependent("NEW ENTITY DEPENDENT 1");
						CEntityZeroToManyDependent				EntityDependent2=new CEntityZeroToManyDependent("NEW ENTITY DEPENDENT 2");
						CEntityZeroToManyPrincipal				EntityPrincipal=new CEntityZeroToManyPrincipal("NEW ENTITY PRINCIPAL",new List<CEntityZeroToManyDependent>(new CEntityZeroToManyDependent[]{EntityDependent1,EntityDependent2}));

						Context.EntitiesZeroToManyPrincipal.Add(EntityPrincipal);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityPrincipal.EntityPrincipalID;
							ID2=EntityDependent1.EntityDependentID;
							ID3=EntityDependent2.EntityDependentID;

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

						CEntityZeroToManyPrincipal[]			Entities1=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependent[]			Entities2=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependent.PrintToConsole(Entities2);
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

						CEntityZeroToManyPrincipal				EntityPrincipal=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID1).First();

						CConsoleHelpers.WriteLine("ENTITY READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						for(int Index=0;Index<EntityPrincipal.EntitiesDependent.Count;Index++)
						{
							CEntityZeroToManyDependent			EntityDependent=EntityPrincipal.EntitiesDependent.ElementAt(Index);

							// !!! STATE je nastaveny na [Unchanged].
							CDBHelpers.WriteEntityState($"ENTITY DEPENDENT [{(Index+1)}]",Context,EntityDependent);
						}

						Context.EntitiesZeroToManyPrincipal.Remove(EntityPrincipal);

						CConsoleHelpers.WriteLine("ENTITY PRINCIPAL DELETED from DB CONTEXT.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Deleted].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						for(int Index=0;Index<EntityPrincipal.EntitiesDependent.Count;Index++)
						{
							CEntityZeroToManyDependent			EntityDependent=EntityPrincipal.EntitiesDependent.ElementAt(Index);

							// !!! STATE je nastaveny na [Modified].
							CDBHelpers.WriteEntityState($"ENTITY DEPENDENT [{(Index+1)}]",Context,EntityDependent);
						}

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY PRINCIPAL",Context,EntityPrincipal);

						for(int Index=0;Index<EntityPrincipal.EntitiesDependent.Count;Index++)
						{
							CEntityZeroToManyDependent			EntityDependent=EntityPrincipal.EntitiesDependent.ElementAt(Index);

							// !!! STATE je nastaveny na [Unchanged].
							CDBHelpers.WriteEntityState($"ENTITY DEPENDENT [{(Index+1)}]",Context,EntityDependent);
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

						CEntityZeroToManyPrincipal[]			Entities1=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependent[]			Entities2=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependent.PrintToConsole(Entities2);
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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITIES:",ConsoleColor.Cyan);

						CEntityZeroToManyDependent				Entity1=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==ID2).First();
						CEntityZeroToManyDependent				Entity2=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==ID3).First();

						CConsoleHelpers.WriteLine("ENTITIES DEPENDENT READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT 1",Context,Entity1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT 2",Context,Entity2);

						Context.EntitiesZeroToManyDependent.Remove(Entity1);
						Context.EntitiesZeroToManyDependent.Remove(Entity2);

						CConsoleHelpers.WriteLine("ENTITIES DEPENDENT DELETED from DB CONTEXT.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Deleted].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT 1",Context,Entity1);

						// !!! STATE je nastaveny na [Deleted].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT 2",Context,Entity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were DELETED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were NOT DELETED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT 1",Context,Entity1);

						// !!! STATE je nastaveny na [Detached].
						CDBHelpers.WriteEntityState("ENTITY DEPENDENT 2",Context,Entity2);
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
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT ENTITIES:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipal[]				Entities1=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityZeroToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityZeroToManyDependent[]				Entities2=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityZeroToManyDependent.PrintToConsole(Entities2);
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
		private static void TestUpdateRelationshipMToNAuto()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityManyToManyAutoM[]				Entities1=Context.EntitiesManyToManyAutoM.Include(P => P.EntitiesN).ToArray();

						CEntityManyToManyAutoM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyAutoN[]				Entities2=Context.EntitiesManyToManyAutoN.Include(P => P.EntitiesM).ToArray();

						CEntityManyToManyAutoN.PrintToConsole(Entities2);
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

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CEntityManyToManyAutoM					EntityM1=new CEntityManyToManyAutoM("NEW ENTITY M 111");
						CEntityManyToManyAutoM					EntityM2=new CEntityManyToManyAutoM("NEW ENTITY M 222");
						CEntityManyToManyAutoN					EntityN1=new CEntityManyToManyAutoN("NEW ENTITY N 111");
						CEntityManyToManyAutoN					EntityN2=new CEntityManyToManyAutoN("NEW ENTITY N 222");

						Context.EntitiesManyToManyAutoM.Add(EntityM1);
						Context.EntitiesManyToManyAutoM.Add(EntityM2);
						Context.EntitiesManyToManyAutoN.Add(EntityN1);
						Context.EntitiesManyToManyAutoN.Add(EntityN2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=EntityM1.EntityMID;
							ID2=EntityM2.EntityMID;
							ID3=EntityN1.EntityNID;
							ID4=EntityN2.EntityNID;

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
						CConsoleHelpers.WriteLine("BEFORE UPDATE:",ConsoleColor.Cyan);

						CEntityManyToManyAutoM[]				Entities1=Context.EntitiesManyToManyAutoM.Include(P => P.EntitiesN).ToArray();

						CEntityManyToManyAutoM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyAutoN[]				Entities2=Context.EntitiesManyToManyAutoN.Include(P => P.EntitiesM).ToArray();

						CEntityManyToManyAutoN.PrintToConsole(Entities2);
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

						CEntityManyToManyAutoM					EntityM1=Context.EntitiesManyToManyAutoM.Include(P => P.EntitiesN).Where(P => P.EntityMID==ID1).First();
						CEntityManyToManyAutoM					EntityM2=Context.EntitiesManyToManyAutoM.Include(P => P.EntitiesN).Where(P => P.EntityMID==ID2).First();
						CEntityManyToManyAutoN					EntityN1=Context.EntitiesManyToManyAutoN.Include(P => P.EntitiesM).Where(P => P.EntityNID==ID3).First();
						CEntityManyToManyAutoN					EntityN2=Context.EntitiesManyToManyAutoN.Include(P => P.EntitiesM).Where(P => P.EntityNID==ID4).First();

						CConsoleHelpers.WriteLine("ENTITIES READ from DB.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 1",Context,EntityM1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 2",Context,EntityM2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 1",Context,EntityN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 2",Context,EntityN2);

						// !!! UPDATE sa vykona pridanim novej instancie ENTITY N do NAVIGATION PROPERTY v ENTITY M.
						EntityM1.EntitiesN.Add(EntityN1);

						CConsoleHelpers.WriteLine("ENTITY N 1 ADDED to ENTITY M 1 NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! UPDATE sa vykona pridanim novej instancie ENTITY N do NAVIGATION PROPERTY v ENTITY M.
						EntityM1.EntitiesN.Add(EntityN2);

						CConsoleHelpers.WriteLine("ENTITY N 2 ADDED to ENTITY M 1 NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! UPDATE sa vykona pridanim novej instancie ENTITY M do NAVIGATION PROPERTY v ENTITY N.
						EntityN1.EntitiesM.Add(EntityM2);

						CConsoleHelpers.WriteLine("ENTITY M 2 ADDED to ENTITY N 1 NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! UPDATE sa vykona pridanim novej instancie ENTITY M do NAVIGATION PROPERTY v ENTITY N.
						EntityN2.EntitiesM.Add(EntityM2);

						CConsoleHelpers.WriteLine("ENTITY M 2 ADDED to ENTITY N 2 NAVIGATION PROPERTY.",ConsoleColor.Yellow);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 1",Context,EntityM1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 2",Context,EntityM2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 1",Context,EntityN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 2",Context,EntityN2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Blue);
						}
						else
						{
							CConsoleHelpers.WriteLine($"ENTITIES were UPDATED !",ConsoleColor.Red);
						}

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 1",Context,EntityM1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY M 2",Context,EntityM2);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 1",Context,EntityN1);

						// !!! STATE je nastaveny na [Unchanged].
						CDBHelpers.WriteEntityState("ENTITY N 2",Context,EntityN2);
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

						CEntityManyToManyAutoM[]				Entities1=Context.EntitiesManyToManyAutoM.Include(P => P.EntitiesN).ToArray();

						CEntityManyToManyAutoM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyAutoN[]				Entities2=Context.EntitiesManyToManyAutoN.Include(P => P.EntitiesM).ToArray();

						CEntityManyToManyAutoN.PrintToConsole(Entities2);
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

						CEntityManyToManyAutoM					EntityM1=Context.EntitiesManyToManyAutoM.Where(P => P.EntityMID==ID1).First();
						CEntityManyToManyAutoM					EntityM2=Context.EntitiesManyToManyAutoM.Where(P => P.EntityMID==ID2).First();
						CEntityManyToManyAutoN					EntityN1=Context.EntitiesManyToManyAutoN.Where(P => P.EntityNID==ID3).First();
						CEntityManyToManyAutoN					EntityN2=Context.EntitiesManyToManyAutoN.Where(P => P.EntityNID==ID4).First();

						Context.EntitiesManyToManyAutoM.Remove(EntityM1);
						Context.EntitiesManyToManyAutoM.Remove(EntityM2);
						Context.EntitiesManyToManyAutoN.Remove(EntityN1);
						Context.EntitiesManyToManyAutoN.Remove(EntityN2);

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

						CEntityManyToManyAutoM[]				Entities1=Context.EntitiesManyToManyAutoM.Include(P => P.EntitiesN).ToArray();

						CEntityManyToManyAutoM.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityManyToManyAutoN[]				Entities2=Context.EntitiesManyToManyAutoN.Include(P => P.EntitiesM).ToArray();

						CEntityManyToManyAutoN.PrintToConsole(Entities2);
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
						CNumber[]								Numbers=Context.EntitiesNumbers.OrderBy(P => P.Number).ToArray();

						for(int Index=0;Index<Numbers.Length;Index++)
						{
							CNumber								Number=Numbers[Index];
							string								NumberText=Number.Print(Index+1);
							
							if (Index>0)
							{
								CConsoleHelpers.WriteLineSeparator();
							}

							CConsoleHelpers.Write(NumberText,ConsoleColor.Green);
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
						CConsoleHelpers.WriteLine("QUERY FILTERS DISABLED:",ConsoleColor.Cyan);

						// !!! QUERY FILTERS su VYPNUTE, lebo sa aplikovala METHOD [IQueryable<TEntity> IQueryable<TEntity>.IgnoreQueryFilters<TEntity>()].
						CNumber[]								Numbers=Context.EntitiesNumbers.OrderBy(P => P.Number).IgnoreQueryFilters().ToArray();

						for(int Index=0;Index<Numbers.Length;Index++)
						{
							CNumber								Number=Numbers[Index];
							string								NumberText=Number.Print(Index+1);
							
							if (Index>0)
							{
								CConsoleHelpers.WriteLineSeparator();
							}

							CConsoleHelpers.Write(NumberText,ConsoleColor.Green);
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
		private static void TestDeleteEntityWithoutRelationships()
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Prida sa PRINCIPAL ENTITY bez DEPENDENT ENTITIES.
						CEntityOneToManyPrincipal				Entity=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL",new List<CEntityOneToManyDependent>());

						Context.EntitiesOneToManyPrincipal.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityPrincipalID;

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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!!!! Ak sa vykonava DELETE PRINCIPAL ENTITY, ktora ma DEPENDENT ENTITIES je vzdy VHODNE pomocou LINQ OPERATOR [Include] nacitat tieto DEPENDENT ENTITIES. Ak totizto nie su nacitane do DB CONTEXT, ENTITY FRAMEWORK CORE NEVYKONA explicitny DELETE DEPENDENT ENTITIES a je na DB SERVERI ako ma nastaveny DEFAULT BEHAVIOR. Ak ho NEMA nastaveny na CASCADE DELETE, tak DEPENDENT ENTITIES NEBUDU DELETED, no dojde k poruseniu FOREIGN KEY CONSTRAINT co sposobi hodenie EXCEPTION.
						CEntityOneToManyPrincipal				Entity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID).First();

						Context.EntitiesOneToManyPrincipal.Remove(Entity);

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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
		private static void TestDeleteEntityWithRelationships()
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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						// !!! Prida sa PRINCIPAL ENTITY s DEPENDENT ENTITIES.
						CEntityOneToManyDependent				EntityDependent1=new CEntityOneToManyDependent("NEW ENTITY DEPENDENT 1");
						CEntityOneToManyDependent				EntityDependent2=new CEntityOneToManyDependent("NEW ENTITY DEPENDENT 2");
						CEntityOneToManyPrincipal				EntityPrincipal=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{EntityDependent1,EntityDependent2}));

						Context.EntitiesOneToManyPrincipal.Add(EntityPrincipal);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=EntityPrincipal.EntityPrincipalID;

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
						CConsoleHelpers.WriteLine("BEFORE DELETE:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						// !!!!! Ak sa vykonava DELETE PRINCIPAL ENTITY, ktora ma DEPENDENT ENTITIES je vzdy VHODNE pomocou LINQ OPERATOR [Include] nacitat tieto DEPENDENT ENTITIES. Ak totizto nie su nacitane do DB CONTEXT, ENTITY FRAMEWORK CORE NEVYKONA explicitny DELETE DEPENDENT ENTITIES a je na DB SERVERI ako ma nastaveny DEFAULT BEHAVIOR. Ak ho NEMA nastaveny na CASCADE DELETE, tak DEPENDENT ENTITIES NEBUDU DELETED, no dojde k poruseniu FOREIGN KEY CONSTRAINT co sposobi hodenie EXCEPTION.
						CEntityOneToManyPrincipal				Entity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==ID).First();

						Context.EntitiesOneToManyPrincipal.Remove(Entity);

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

						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

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
			//TestSelect();
			//TestFind();
			//TestInsert();
			//TestInsertRelationship();
			//TestInsertRelationshipOfExistingObject();
			//TestUpdate();
			//TestUpdateByCallingUpdateMethod();
			//TestUpdateRelationship1To1OnPrincipalEntity();
			//TestUpdateRelationship1To1OnDependentEntityByChangingNavigationProperty();
			//TestUpdateRelationship1To1OnDependentEntityByChangingForeignKey();
			//TestUpdateRelationship1To1ByAddingDependentEntity();
			//TestUpdateRelationship1To1ByAddingDependentEntityNotUsingIncludeOperator();
			//TestUpdateRelationship1ToNOnPrincipalEntityByAddingExistingDependentEntityToCollection();
			//TestUpdateRelationship1ToNOnPrincipalEntityByReplacingNavigationPropertyCollection();
			//TestUpdateRelationship1ToNOnDependentEntityByChangingNavigationProperty();
			//TestUpdateRelationship1ToNOnDependentEntityByChangingForeignKey();
			//TestUpdateRelationship1ToNByAddingDependentEntity();
			//TestUpdateRelationshipMToNOnPrincipalEntity();
			//TestUpdateRelationshipMToNByAddingDependentEntity();
			//TestUpdateRelationshipMToNAuto();
			//TestCascadeDelete();
			//TestNonCascadeDelete();
			//TestQueryFilters();
			//TestDeleteEntityWithoutRelationships();
			TestDeleteEntityWithRelationships();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------