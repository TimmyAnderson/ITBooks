using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.EntityFrameworkCore.Storage;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace TipsAndTechniques
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

			CEntityHierarchical							EntityHierarchicalLevel311=new CEntityHierarchical("LEVEL 3 - 111",3,new List<CEntityHierarchical>());
			CEntityHierarchical							EntityHierarchicalLevel312=new CEntityHierarchical("LEVEL 3 - 222",3,new List<CEntityHierarchical>());
			CEntityHierarchical							EntityHierarchicalLevel313=new CEntityHierarchical("LEVEL 3 - 333",3,new List<CEntityHierarchical>());
			CEntityHierarchical							EntityHierarchicalLevel314=new CEntityHierarchical("LEVEL 3 - 444",3,new List<CEntityHierarchical>());
			CEntityHierarchical							EntityHierarchicalLevel321=new CEntityHierarchical("LEVEL 3 - 555",3,new List<CEntityHierarchical>());
			CEntityHierarchical							EntityHierarchicalLevel322=new CEntityHierarchical("LEVEL 3 - 666",3,new List<CEntityHierarchical>());
			CEntityHierarchical							EntityHierarchicalLevel323=new CEntityHierarchical("LEVEL 3 - 777",3,new List<CEntityHierarchical>());
			CEntityHierarchical							EntityHierarchicalLevel324=new CEntityHierarchical("LEVEL 3 - 888",3,new List<CEntityHierarchical>());

			CEntityHierarchical							EntityHierarchicalLevel211=new CEntityHierarchical("LEVEL 2 - 111",2,new List<CEntityHierarchical>(new CEntityHierarchical[]{EntityHierarchicalLevel311,EntityHierarchicalLevel312}));
			CEntityHierarchical							EntityHierarchicalLevel212=new CEntityHierarchical("LEVEL 2 - 222",2,new List<CEntityHierarchical>(new CEntityHierarchical[]{EntityHierarchicalLevel313,EntityHierarchicalLevel314}));
			CEntityHierarchical							EntityHierarchicalLevel221=new CEntityHierarchical("LEVEL 2 - 333",2,new List<CEntityHierarchical>(new CEntityHierarchical[]{EntityHierarchicalLevel321,EntityHierarchicalLevel322}));
			CEntityHierarchical							EntityHierarchicalLevel222=new CEntityHierarchical("LEVEL 2 - 444",2,new List<CEntityHierarchical>(new CEntityHierarchical[]{EntityHierarchicalLevel323,EntityHierarchicalLevel324}));

			CEntityHierarchical							EntityHierarchicalLevel11=new CEntityHierarchical("LEVEL 1 - 111",1,new List<CEntityHierarchical>(new CEntityHierarchical[]{EntityHierarchicalLevel211,EntityHierarchicalLevel212}));
			CEntityHierarchical							EntityHierarchicalLevel12=new CEntityHierarchical("LEVEL 1 - 222",1,new List<CEntityHierarchical>(new CEntityHierarchical[]{EntityHierarchicalLevel221,EntityHierarchicalLevel222}));

			Context.EntitiesHierarchical.Add(EntityHierarchicalLevel11);
			Context.EntitiesHierarchical.Add(EntityHierarchicalLevel12);

			List<CEntityIncludeDependent1>				EntitiesDependent1=new List<CEntityIncludeDependent1>();
			List<CEntityIncludeDependent2>				EntitiesDependent2=new List<CEntityIncludeDependent2>();
			List<CEntityIncludeDependent3>				EntitiesDependent3=new List<CEntityIncludeDependent3>();

			// !!! Simuluje sa velky pocet RECORDS.
			for(int Index=0;Index<100;Index++)
			{
				CEntityIncludeDependent1				EntityDependent1=new CEntityIncludeDependent1($"DEPENDENT 1 - [{(Index+1)}]");
				CEntityIncludeDependent2				EntityDependent2=new CEntityIncludeDependent2($"DEPENDENT 2 - [{(Index+1)}]");
				CEntityIncludeDependent3				EntityDependent3=new CEntityIncludeDependent3($"DEPENDENT 3 - [{(Index+1)}]");

				EntitiesDependent1.Add(EntityDependent1);
				EntitiesDependent2.Add(EntityDependent2);
				EntitiesDependent3.Add(EntityDependent3);
			}

			CEntityIncludePrincipal						EntityPrincipal=new CEntityIncludePrincipal("PRINCIPAL",EntitiesDependent1,EntitiesDependent2,EntitiesDependent3);

			Context.EntitiesIncludePrincipal.Add(EntityPrincipal);

			CEntityGroupByFunction								GroupByFunction1A=new CEntityGroupByFunction(1,"ONE AAA",1);
			CEntityGroupByFunction								GroupByFunction1B=new CEntityGroupByFunction(1,"ONE AAA",2);
			CEntityGroupByFunction								GroupByFunction1C=new CEntityGroupByFunction(1,"ONE BBB",3);
			CEntityGroupByFunction								GroupByFunction1D=new CEntityGroupByFunction(1,"ONE BBB",4);
			CEntityGroupByFunction								GroupByFunction2A=new CEntityGroupByFunction(2,"TWO AAA",5);
			CEntityGroupByFunction								GroupByFunction2B=new CEntityGroupByFunction(2,"TWO AAA",6);
			CEntityGroupByFunction								GroupByFunction2C=new CEntityGroupByFunction(2,"TWO BBB",7);
			CEntityGroupByFunction								GroupByFunction2D=new CEntityGroupByFunction(2,"TWO BBB",8);
			CEntityGroupByFunction								GroupByFunction3A=new CEntityGroupByFunction(3,"THREE AAA",9);
			CEntityGroupByFunction								GroupByFunction3B=new CEntityGroupByFunction(3,"THREE AAA",10);
			CEntityGroupByFunction								GroupByFunction3C=new CEntityGroupByFunction(3,"THREE BBB",11);
			CEntityGroupByFunction								GroupByFunction3D=new CEntityGroupByFunction(3,"THREE BBB",12);

			Context.EntitiesGroupByFunction.Add(GroupByFunction1A);
			Context.EntitiesGroupByFunction.Add(GroupByFunction1B);
			Context.EntitiesGroupByFunction.Add(GroupByFunction1C);
			Context.EntitiesGroupByFunction.Add(GroupByFunction1D);
			Context.EntitiesGroupByFunction.Add(GroupByFunction2A);
			Context.EntitiesGroupByFunction.Add(GroupByFunction2B);
			Context.EntitiesGroupByFunction.Add(GroupByFunction2C);
			Context.EntitiesGroupByFunction.Add(GroupByFunction2D);
			Context.EntitiesGroupByFunction.Add(GroupByFunction3A);
			Context.EntitiesGroupByFunction.Add(GroupByFunction3B);
			Context.EntitiesGroupByFunction.Add(GroupByFunction3C);
			Context.EntitiesGroupByFunction.Add(GroupByFunction3D);

			CEntityMaxDependent									EntityMaxDependent11=new CEntityMaxDependent(1);
			CEntityMaxDependent									EntityMaxDependent12=new CEntityMaxDependent(2);
			CEntityMaxDependent									EntityMaxDependent21=new CEntityMaxDependent(3);
			CEntityMaxDependent									EntityMaxDependent22=new CEntityMaxDependent(4);

			CEntityMaxPrincipal									EntityMaxPrincipal1=new CEntityMaxPrincipal("AAA",new CEntityMaxDependent[]{EntityMaxDependent11,EntityMaxDependent12});
			CEntityMaxPrincipal									EntityMaxPrincipal2=new CEntityMaxPrincipal("BBB",new CEntityMaxDependent[]{EntityMaxDependent21,EntityMaxDependent22});
			CEntityMaxPrincipal									EntityMaxPrincipal3=new CEntityMaxPrincipal("CCC",null);

			Context.EntitiesMaxPrincipal.Add(EntityMaxPrincipal1);
			Context.EntitiesMaxPrincipal.Add(EntityMaxPrincipal2);
			Context.EntitiesMaxPrincipal.Add(EntityMaxPrincipal3);

			CEntityConstructorsDependent						EntityConstructorsDependent11=new CEntityConstructorsDependent("AAA 111",0);
			CEntityConstructorsDependent						EntityConstructorsDependent12=new CEntityConstructorsDependent("AAA 222",0);
			CEntityConstructorsDependent						EntityConstructorsDependent21=new CEntityConstructorsDependent("BBB 111",0);
			CEntityConstructorsDependent						EntityConstructorsDependent22=new CEntityConstructorsDependent("BBB 222",0);

			CEntityConstructorsPrincipal						EntityConstructorsPrincipal1=new CEntityConstructorsPrincipal("AAA");
			CEntityConstructorsPrincipal						EntityConstructorsPrincipal2=new CEntityConstructorsPrincipal("BBB");

			EntityConstructorsPrincipal1.EntitiesDependent=new CEntityConstructorsDependent[]{EntityConstructorsDependent11,EntityConstructorsDependent12};
			EntityConstructorsPrincipal2.EntitiesDependent=new CEntityConstructorsDependent[]{EntityConstructorsDependent21,EntityConstructorsDependent22};

			Context.EntitiesConstructorsPrincipal.Add(EntityConstructorsPrincipal1);
			Context.EntitiesConstructorsPrincipal.Add(EntityConstructorsPrincipal2);

			CEntityLazyLoadingDependent							EntityLazyLoadingDependent11=new CEntityLazyLoadingDependent("AAA 111");
			CEntityLazyLoadingDependent							EntityLazyLoadingDependent12=new CEntityLazyLoadingDependent("AAA 222");
			CEntityLazyLoadingDependent							EntityLazyLoadingDependent21=new CEntityLazyLoadingDependent("BBB 111");
			CEntityLazyLoadingDependent							EntityLazyLoadingDependent22=new CEntityLazyLoadingDependent("BBB 222");

			CEntityLazyLoadingPrincipal							EntityLazyLoadingPrincipal1=new CEntityLazyLoadingPrincipal("AAA",new CEntityLazyLoadingDependent[]{EntityLazyLoadingDependent11,EntityLazyLoadingDependent12});
			CEntityLazyLoadingPrincipal							EntityLazyLoadingPrincipal2=new CEntityLazyLoadingPrincipal("BBB",new CEntityLazyLoadingDependent[]{EntityLazyLoadingDependent21,EntityLazyLoadingDependent22});

			Context.EntitiesLazyLoadingPrincipal.Add(EntityLazyLoadingPrincipal1);
			Context.EntitiesLazyLoadingPrincipal.Add(EntityLazyLoadingPrincipal2);
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
		private static void TestRelationalFixup()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("NO LINQ OPERATOR [AsNoTracking] - READING PRINCIPAL ENTITIES FIRST:",ConsoleColor.Cyan);

						CConsoleHelpers.WriteLine("READING PRINCIPAL ENTITIES ONLY:",ConsoleColor.Yellow);

						// !!!!! Nepouzije sa LINQ OPERATOR [Include], aby sa demonstroval RELATIONAL FIXUP.
						// !!!!! Po vykonani QUERY NAVIGATION PROPERTIES PRINCIPAL ENTITIES NIE SU NASTAVENE, kedze sa NEPOUZIL LINQ OPERATOR [Include].
						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.ToArray();

						CConsoleHelpers.WriteLine("PRINCIPAL ENTITIES:",ConsoleColor.Blue);

						CEntityOneToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CConsoleHelpers.WriteLine("READING DEPENDENT ENTITIES ONLY:",ConsoleColor.Yellow);

						// !!!!! Nepouzije sa LINQ OPERATOR [Include], aby sa demonstroval RELATIONAL FIXUP.
						// !!!!! Po vykonani QUERY su nastave NAVIGATION PROPERTIES nielen u DEPENDENT ENTITIES, ale aj u PRINCIPAL ENTITIES, pretoze PRINCIPAL ENTITIES boli nacitane do DB CONTEXT v predchadzajuce QUERY.
						CEntityOneToManyDependent[]				Entities2=Context.EntitiesOneToManyDependent.ToArray();

						CConsoleHelpers.WriteLine("PRINCIPAL ENTITIES:",ConsoleColor.Blue);

						CEntityOneToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CConsoleHelpers.WriteLine("DEPENDENT ENTITIES:",ConsoleColor.Blue);

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
						CConsoleHelpers.WriteLine("NO LINQ OPERATOR [AsNoTracking] - READING DEPENDENT ENTITIES FIRST:",ConsoleColor.Cyan);

						CConsoleHelpers.WriteLine("READING PRINCIPAL ENTITIES ONLY:",ConsoleColor.Yellow);

						// !!!!! Nepouzije sa LINQ OPERATOR [Include], aby sa demonstroval RELATIONAL FIXUP.
						// !!!!! Po vykonani QUERY NAVIGATION PROPERTIES PRINCIPAL ENTITIES NIE SU NASTAVENE, kedze sa NEPOUZIL LINQ OPERATOR [Include].
						CEntityOneToManyDependent[]				Entities1=Context.EntitiesOneToManyDependent.ToArray();

						CConsoleHelpers.WriteLine("DEPENDENT ENTITIES:",ConsoleColor.Blue);

						CEntityOneToManyDependent.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CConsoleHelpers.WriteLine("READING DEPENDENT ENTITIES ONLY:",ConsoleColor.Yellow);

						// !!!!! Nepouzije sa LINQ OPERATOR [Include], aby sa demonstroval RELATIONAL FIXUP.
						// !!!!! Po vykonani QUERY su nastave NAVIGATION PROPERTIES nielen u PRINCIPAL ENTITIES, ale aj u DEPENDENT ENTITIES, pretoze DEPENDENT ENTITIES boli nacitane do DB CONTEXT v predchadzajuce QUERY.
						CEntityOneToManyPrincipal[]				Entities2=Context.EntitiesOneToManyPrincipal.ToArray();

						CConsoleHelpers.WriteLine("PRINCIPAL ENTITIES:",ConsoleColor.Blue);

						CEntityOneToManyPrincipal.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CConsoleHelpers.WriteLine("DEPENDENT ENTITIES:",ConsoleColor.Blue);

						CEntityOneToManyDependent.PrintToConsole(Entities1);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("WITH LINQ OPERATOR [AsNoTracking] - READING PRINCIPAL ENTITIES FIRST:",ConsoleColor.Cyan);

						CConsoleHelpers.WriteLine("READING PRINCIPAL ENTITIES ONLY:",ConsoleColor.Yellow);

						// !!!!! Nepouzije sa LINQ OPERATOR [Include], aby sa demonstroval RELATIONAL FIXUP.
						// !!!!! RELATIONAL FIXUP sa NEVYKONA, lebo bol pouzity LINQ OPERATOR [AsNoTracking].
						CEntityOneToManyPrincipal[]				Entities1=Context.EntitiesOneToManyPrincipal.AsNoTracking().ToArray();

						CConsoleHelpers.WriteLine("PRINCIPAL ENTITIES:",ConsoleColor.Blue);

						CEntityOneToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CConsoleHelpers.WriteLine("READING DEPENDENT ENTITIES ONLY:",ConsoleColor.Yellow);

						// !!!!! Nepouzije sa LINQ OPERATOR [Include], aby sa demonstroval RELATIONAL FIXUP.
						// !!!!! RELATIONAL FIXUP sa NEVYKONA, lebo bol pouzity LINQ OPERATOR [AsNoTracking].
						CEntityOneToManyDependent[]				Entities2=Context.EntitiesOneToManyDependent.AsNoTracking().ToArray();

						CConsoleHelpers.WriteLine("PRINCIPAL ENTITIES:",ConsoleColor.Blue);

						CEntityOneToManyPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CConsoleHelpers.WriteLine("DEPENDENT ENTITIES:",ConsoleColor.Blue);

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
						CConsoleHelpers.WriteLine("WITH LINQ OPERATOR [AsNoTracking] - READING DEPENDENT ENTITIES FIRST:",ConsoleColor.Cyan);

						CConsoleHelpers.WriteLine("READING PRINCIPAL ENTITIES ONLY:",ConsoleColor.Yellow);

						// !!!!! Nepouzije sa LINQ OPERATOR [Include], aby sa demonstroval RELATIONAL FIXUP.
						// !!!!! RELATIONAL FIXUP sa NEVYKONA, lebo bol pouzity LINQ OPERATOR [AsNoTracking].
						CEntityOneToManyDependent[]				Entities1=Context.EntitiesOneToManyDependent.AsNoTracking().ToArray();

						CConsoleHelpers.WriteLine("DEPENDENT ENTITIES:",ConsoleColor.Blue);

						CEntityOneToManyDependent.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CConsoleHelpers.WriteLine("READING DEPENDENT ENTITIES ONLY:",ConsoleColor.Yellow);

						// !!!!! Nepouzije sa LINQ OPERATOR [Include], aby sa demonstroval RELATIONAL FIXUP.
						// !!!!! RELATIONAL FIXUP sa NEVYKONA, lebo bol pouzity LINQ OPERATOR [AsNoTracking].
						CEntityOneToManyPrincipal[]				Entities2=Context.EntitiesOneToManyPrincipal.AsNoTracking().ToArray();

						CConsoleHelpers.WriteLine("PRINCIPAL ENTITIES:",ConsoleColor.Blue);

						CEntityOneToManyPrincipal.PrintToConsole(Entities2);

						CConsoleHelpers.WriteLineSeparators(3);

						CConsoleHelpers.WriteLine("DEPENDENT ENTITIES:",ConsoleColor.Blue);

						CEntityOneToManyDependent.PrintToConsole(Entities1);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("WITH LINQ OPERATOR [AsNoTracking] - READING PRINCIPAL and DEPENDENT ENTITIES in ONE QUERY:",ConsoleColor.Cyan);

						CConsoleHelpers.WriteLine("READING PRINCIPAL and DEPENDENT ENTITIES in ONE QUERY:",ConsoleColor.Yellow);

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).AsNoTracking().ToArray();

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
		private static void TestAsNoTrackingAndAsNoTrackingWithIdentityResolution()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("NORMAL QUERIES:",ConsoleColor.Cyan);

						// !!!!! QUERY pre ROVNAKE RECORDS vytvori TU ISTU instanciu ENTITY CLASS.
						CEntityManyToManyM[]					EntitiesMQuery1=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(EntitiesMQuery1);

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine("COMPARING ENTITIES N from QUERY 1.",ConsoleColor.Yellow);

						for (int Index1=0;Index1<EntitiesMQuery1.Length-1;Index1++)
						{
							for (int Index2=Index1+1;Index2<EntitiesMQuery1.Length;Index2++)
							{
								CEntityManyToManyM				EntityM1=EntitiesMQuery1[Index1];
								CEntityManyToManyM				EntityM2=EntitiesMQuery1[Index2];
								CEntityManyToManyN[]			EntitiesN1=EntityM1.EntitiesMN.Select(P => P.EntityN).ToArray();
								CEntityManyToManyN[]			EntitiesN2=EntityM2.EntitiesMN.Select(P => P.EntityN).ToArray();

								for (int Index3=0;Index3<EntitiesN1.Length;Index3++)
								{
									for (int Index4=0;Index4<EntitiesN2.Length;Index4++)
									{
										CEntityManyToManyN		EntityN1=EntitiesN1[Index3];
										CEntityManyToManyN		EntityN2=EntitiesN2[Index4];
										bool					AreEqual=object.ReferenceEquals(EntityN1,EntityN2);

										if (AreEqual==true)
										{
											CConsoleHelpers.WriteLine($"INDEXES [{Index3},{Index4}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are EQUAL !",ConsoleColor.Green);
										}
										else
										{
											CConsoleHelpers.WriteLine($"INDEXES [{Index3},{Index4}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are NOT EQUAL !",ConsoleColor.Red);
										}
									}
								}
							}
						}

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine("COMPARING ENTITIES M from QUERY 1 and QUERY 2.",ConsoleColor.Yellow);

						// !!!!! Aplikuje sa RELATIONAL FIXUP, a preto QUERY 1 a QUERY 2 vratia TIE ISTE instancie ENTITY CLASSES.
						CEntityManyToManyM[]					EntitiesMQuery2=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						for (int Index=0;Index<EntitiesMQuery1.Length;Index++)
						{
							CEntityManyToManyM					EntityM1=EntitiesMQuery1[Index];
							CEntityManyToManyM					EntityM2=EntitiesMQuery2[Index];
							bool								AreEqual=object.ReferenceEquals(EntityM1,EntityM2);

							if (AreEqual==true)
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityM1.EntityMID}] and ENTITY [{EntityM2.EntityMID}] are EQUAL !",ConsoleColor.Green);
							}
							else
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityM1.EntityMID}] and ENTITY [{EntityM2.EntityMID}] are NOT EQUAL !",ConsoleColor.Red);
							}
						}

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine("COMPARING ENTITIES N from QUERY 1 and QUERY 2.",ConsoleColor.Yellow);

						// !!!!! Aplikuje sa RELATIONAL FIXUP, a preto QUERY 1 a QUERY 2 vratia TIE ISTE instancie ENTITY CLASSES.
						CEntityManyToManyN[]					EntitiesNQuery1=EntitiesMQuery1.SelectMany(P => P.EntitiesMN).Select(P => P.EntityN).ToArray();
						CEntityManyToManyN[]					EntitiesNQuery2=EntitiesMQuery2.SelectMany(P => P.EntitiesMN).Select(P => P.EntityN).ToArray();

						for (int Index=0;Index<EntitiesNQuery1.Length;Index++)
						{
							CEntityManyToManyN					EntityN1=EntitiesNQuery1[Index];
							CEntityManyToManyN					EntityN2=EntitiesNQuery2[Index];
							bool								AreEqual=object.ReferenceEquals(EntityN1,EntityN2);

							if (AreEqual==true)
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are EQUAL !",ConsoleColor.Green);
							}
							else
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are NOT EQUAL !",ConsoleColor.Red);
							}
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
						CConsoleHelpers.WriteLine("QUERIES with LINQ OPERATOR [AsNoTracking]:",ConsoleColor.Cyan);

						// !!!!! Kedze sa aplikuje LINQ OPERATOR [AsNoTracking], pre ROVNAKE RECORDS sa NEVYTVORI ta ISTA instancia ENTITY CLASS.
						CEntityManyToManyM[]					EntitiesMQuery1=Context.EntitiesManyToManyM.AsNoTracking().Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(EntitiesMQuery1);

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine("COMPARING ENTITIES N from QUERY 1.",ConsoleColor.Yellow);

						for (int Index1=0;Index1<EntitiesMQuery1.Length-1;Index1++)
						{
							for (int Index2=Index1+1;Index2<EntitiesMQuery1.Length;Index2++)
							{
								CEntityManyToManyM				EntityM1=EntitiesMQuery1[Index1];
								CEntityManyToManyM				EntityM2=EntitiesMQuery1[Index2];
								CEntityManyToManyN[]			EntitiesN1=EntityM1.EntitiesMN.Select(P => P.EntityN).ToArray();
								CEntityManyToManyN[]			EntitiesN2=EntityM2.EntitiesMN.Select(P => P.EntityN).ToArray();

								for (int Index3=0;Index3<EntitiesN1.Length;Index3++)
								{
									for (int Index4=0;Index4<EntitiesN2.Length;Index4++)
									{
										CEntityManyToManyN		EntityN1=EntitiesN1[Index3];
										CEntityManyToManyN		EntityN2=EntitiesN2[Index4];
										bool					AreEqual=object.ReferenceEquals(EntityN1,EntityN2);

										if (AreEqual==true)
										{
											CConsoleHelpers.WriteLine($"INDEXES [{Index3},{Index4}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are EQUAL !",ConsoleColor.Green);
										}
										else
										{
											CConsoleHelpers.WriteLine($"INDEXES [{Index3},{Index4}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are NOT EQUAL !",ConsoleColor.Red);
										}
									}
								}
							}
						}

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine("COMPARING ENTITIES M from QUERY 1 and QUERY 2.",ConsoleColor.Yellow);

						// !!!!! Kedze sa na QUERY aplikoval [AsNoTracking], RELATIONAL FIXUP sa VYKONA IBA v ramci QUERY, ale NIE medzi rozlicnymi QUERIES.
						CEntityManyToManyM[]					EntitiesMQuery2=Context.EntitiesManyToManyM.AsNoTracking().Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						for (int Index=0;Index<EntitiesMQuery1.Length;Index++)
						{
							CEntityManyToManyM					EntityM1=EntitiesMQuery1[Index];
							CEntityManyToManyM					EntityM2=EntitiesMQuery2[Index];
							bool								AreEqual=object.ReferenceEquals(EntityM1,EntityM2);

							if (AreEqual==true)
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityM1.EntityMID}] and ENTITY [{EntityM2.EntityMID}] are EQUAL !",ConsoleColor.Green);
							}
							else
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityM1.EntityMID}] and ENTITY [{EntityM2.EntityMID}] are NOT EQUAL !",ConsoleColor.Red);
							}
						}

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine("COMPARING ENTITIES N from QUERY 1 and QUERY 2.",ConsoleColor.Yellow);

						// !!!!! Kedze sa na QUERY aplikoval [AsNoTracking], RELATIONAL FIXUP sa VYKONA IBA v ramci QUERY, ale NIE medzi rozlicnymi QUERIES.
						CEntityManyToManyN[]					EntitiesNQuery1=EntitiesMQuery1.SelectMany(P => P.EntitiesMN).Select(P => P.EntityN).ToArray();
						CEntityManyToManyN[]					EntitiesNQuery2=EntitiesMQuery2.SelectMany(P => P.EntitiesMN).Select(P => P.EntityN).ToArray();

						for (int Index=0;Index<EntitiesNQuery1.Length;Index++)
						{
							CEntityManyToManyN					EntityN1=EntitiesNQuery1[Index];
							CEntityManyToManyN					EntityN2=EntitiesNQuery2[Index];
							bool								AreEqual=object.ReferenceEquals(EntityN1,EntityN2);

							if (AreEqual==true)
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are EQUAL !",ConsoleColor.Green);
							}
							else
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are NOT EQUAL !",ConsoleColor.Red);
							}
						}
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("QUERIES with LINQ OPERATOR [AsNoTrackingWithIdentityResolution]:",ConsoleColor.Cyan);

						// !!!!! Kedze sa aplikuje LINQ OPERATOR [AsNoTrackingWithIdentityResolution], pre ROVNAKE RECORDS sa VYTVORI tia ISTA instancia ENTITY CLASS.
						CEntityManyToManyM[]					EntitiesMQuery1=Context.EntitiesManyToManyM.AsNoTrackingWithIdentityResolution().Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(EntitiesMQuery1);

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine("COMPARING ENTITIES N from QUERY 1.",ConsoleColor.Yellow);

						for (int Index1=0;Index1<EntitiesMQuery1.Length-1;Index1++)
						{
							for (int Index2=Index1+1;Index2<EntitiesMQuery1.Length;Index2++)
							{
								CEntityManyToManyM				EntityM1=EntitiesMQuery1[Index1];
								CEntityManyToManyM				EntityM2=EntitiesMQuery1[Index2];
								CEntityManyToManyN[]			EntitiesN1=EntityM1.EntitiesMN.Select(P => P.EntityN).ToArray();
								CEntityManyToManyN[]			EntitiesN2=EntityM2.EntitiesMN.Select(P => P.EntityN).ToArray();

								for (int Index3=0;Index3<EntitiesN1.Length;Index3++)
								{
									for (int Index4=0;Index4<EntitiesN2.Length;Index4++)
									{
										CEntityManyToManyN		EntityN1=EntitiesN1[Index3];
										CEntityManyToManyN		EntityN2=EntitiesN2[Index4];
										bool					AreEqual=object.ReferenceEquals(EntityN1,EntityN2);

										if (AreEqual==true)
										{
											CConsoleHelpers.WriteLine($"INDEXES [{Index3},{Index4}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are EQUAL !",ConsoleColor.Green);
										}
										else
										{
											CConsoleHelpers.WriteLine($"INDEXES [{Index3},{Index4}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are NOT EQUAL !",ConsoleColor.Red);
										}
									}
								}
							}
						}

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine("COMPARING ENTITIES M from QUERY 1 and QUERY 2.",ConsoleColor.Yellow);

						// !!!!! Kedze sa na QUERY aplikoval [AsNoTrackingWithIdentityResolution], RELATIONAL FIXUP sa VYKONA IBA v ramci QUERY, ale NIE medzi rozlicnymi QUERIES.
						CEntityManyToManyM[]					EntitiesMQuery2=Context.EntitiesManyToManyM.AsNoTrackingWithIdentityResolution().Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						for (int Index=0;Index<EntitiesMQuery1.Length;Index++)
						{
							CEntityManyToManyM					EntityM1=EntitiesMQuery1[Index];
							CEntityManyToManyM					EntityM2=EntitiesMQuery2[Index];
							bool								AreEqual=object.ReferenceEquals(EntityM1,EntityM2);

							if (AreEqual==true)
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityM1.EntityMID}] and ENTITY [{EntityM2.EntityMID}] are EQUAL !",ConsoleColor.Green);
							}
							else
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityM1.EntityMID}] and ENTITY [{EntityM2.EntityMID}] are NOT EQUAL !",ConsoleColor.Red);
							}
						}

						CConsoleHelpers.WriteLineSeparator();

						CConsoleHelpers.WriteLine("COMPARING ENTITIES N from QUERY 1 and QUERY 2.",ConsoleColor.Yellow);

						// !!!!! Kedze sa na QUERY aplikoval [AsNoTrackingWithIdentityResolution], RELATIONAL FIXUP sa VYKONA IBA v ramci QUERY, ale NIE medzi rozlicnymi QUERIES.
						CEntityManyToManyN[]					EntitiesNQuery1=EntitiesMQuery1.SelectMany(P => P.EntitiesMN).Select(P => P.EntityN).ToArray();
						CEntityManyToManyN[]					EntitiesNQuery2=EntitiesMQuery2.SelectMany(P => P.EntitiesMN).Select(P => P.EntityN).ToArray();

						for (int Index=0;Index<EntitiesNQuery1.Length;Index++)
						{
							CEntityManyToManyN					EntityN1=EntitiesNQuery1[Index];
							CEntityManyToManyN					EntityN2=EntitiesNQuery2[Index];
							bool								AreEqual=object.ReferenceEquals(EntityN1,EntityN2);

							if (AreEqual==true)
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are EQUAL !",ConsoleColor.Green);
							}
							else
							{
								CConsoleHelpers.WriteLine($"INDEX [{Index}] - ENTITY [{EntityN1.EntityNID}] and ENTITY [{EntityN2.EntityNID}] are NOT EQUAL !",ConsoleColor.Red);
							}
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
		private static void TestSelectHierarchicalEntities()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("READING LEVEL 1 ONLY - NO LINQ OPERATOR [Include]:",ConsoleColor.Cyan);

						// !!!!! Kedze sa NEPOUZIL LINQ OPERATOR [Include], tak sa nacia iba LEVEL 1.
						CEntityHierarchical[]					Entities=Context.EntitiesHierarchical.Where(P => P.Level==1).ToArray();

						CEntityHierarchical.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("READING LEVEL 1 ONLY - WITH LINQ OPERATOR [Include]:",ConsoleColor.Cyan);

						// !!!!! Kedze sa POUZIL LINQ OPERATOR [Include], tak sa nacita LEVEL 1 a LEVEL 2.
						CEntityHierarchical[]					Entities=Context.EntitiesHierarchical.Include(P => P.EntitiesDependent).Where(P => P.Level==1).ToArray();

						CEntityHierarchical.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("READING LEVEL 1 ONLY - WITH LINQ OPERATOR [Include] and LINQ OPERATOR [ThenInclude]:",ConsoleColor.Cyan);

						// !!!!! Kedze sa NEPOUZIL LINQ OPERATOR [Include] a nasledne LINQ OPERATOR [ThenInclude], tak sa nacia LEVEL 1, LEVEL 2 a LEVEL 3.
						CEntityHierarchical[]					Entities=Context.EntitiesHierarchical.Include(P => P.EntitiesDependent).ThenInclude(P => P.EntitiesDependent).Where(P => P.Level==1).ToArray();

						CEntityHierarchical.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("READING ALL ENTITIES - NO LINQ OPERATOR [Include]:",ConsoleColor.Cyan);

						// !!!!! Ak ked sa NEPOUZIL LINQ OPERATOR [Include], kedze sa nacitali VSETKY instancie ENTITY CLASSES, tak vdaka RELATIONAL FIXUP sa nacitaju vsetky 3 LEVELS.
						CEntityHierarchical[]					Entities=Context.EntitiesHierarchical.ToArray();

						CEntityHierarchical.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("READING ALL ENTITIES - NO LINQ OPERATOR [Include] WITH LINQ OPERATOR [AsNoTracking]:",ConsoleColor.Cyan);

						// !!!!! Kedze sa NEPOUZIL LINQ OPERATOR [Include], ale POUZIL sa LINQ OPERATOR [AsNoTracking], tak instancie ENTITIES NEBUDU mat nastavene NAVIGATION PROPERTIES.
						CEntityHierarchical[]					Entities=Context.EntitiesHierarchical.AsNoTracking().ToArray();

						CEntityHierarchical.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("READING ALL ENTITIES - WITH LINQ OPERATOR [Include] and LINQ OPERATOR [ThenInclude] and WITH LINQ OPERATOR [AsNoTracking]:",ConsoleColor.Cyan);

						// !!!!! Kedze sa POUZIL LINQ OPERATOR [Include], LINQ OPERATOR [ThenInclude] a LINQ OPERATOR [AsNoTracking], na INCLUDES ENTITIES sa VYKONA RELATIONAL FIXUP a NAVIGATION PROPERTIES sa spravne nastavia pre LEVEL 1, LEVEL 2 aj LEVEL 3.
						CEntityHierarchical[]					Entities=Context.EntitiesHierarchical.Include(P => P.EntitiesDependent).ThenInclude(P => P.EntitiesDependent).AsNoTracking().ToArray();

						CEntityHierarchical.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("READING ALL ENTITIES - NO LINQ OPERATOR [Include] WITH LINQ OPERATOR [AsNoTrackingWithIdentityResolution]:",ConsoleColor.Cyan);

						// !!!!! Kedze sa NEPOUZIL LINQ OPERATOR [Include], ale POUZIL sa LINQ OPERATOR [AsNoTrackingWithIdentityResolution], tak instancie ENTITIES BUDU mat nastavene NAVIGATION PROPERTIES.
						CEntityHierarchical[]					Entities=Context.EntitiesHierarchical.AsNoTrackingWithIdentityResolution().ToArray();

						CEntityHierarchical.PrintToConsole(Entities);
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
		private static void TestLinqOperatorAsSplitQuery()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("EXECUTING DUMMY QUERY:",ConsoleColor.Cyan);

						// !!!!! SPRAVI sa DUMMY QUERY na inicializaciu DB CONTEXT.
						Context.EntitiesIncludePrincipal.Include(P => P.EntitiesDependent1).Include(P => P.EntitiesDependent2).Include(P => P.EntitiesDependent3).ToArray();
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("LINQ OPERATOR [Include]:",ConsoleColor.Cyan);

						Stopwatch								SW=new Stopwatch();

						SW.Start();

						// !!!!! QUERY je EXTREMNE POMALA, lebo sa NEPOUZIL LINQ OPERATOR [AsSplitQuery].
						Context.EntitiesIncludePrincipal.Include(P => P.EntitiesDependent1).Include(P => P.EntitiesDependent2).Include(P => P.EntitiesDependent3).ToArray();

						SW.Stop();

						CConsoleHelpers.WriteLine($"QUERY TIME [{SW.ElapsedMilliseconds} ms].",ConsoleColor.Blue);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("LINQ OPERATOR [Include] and LINQ OPERATOR [AsSplitQuery] after 3. LINQ OPERATOR [Include]:",ConsoleColor.Cyan);

						Stopwatch								SW=new Stopwatch();

						SW.Start();

						// !!!!! QUERY je VYRAZNE RYCHLEJSIA, lebo sa pouzil LINQ OPERATOR [AsSplitQuery].
						Context.EntitiesIncludePrincipal.Include(P => P.EntitiesDependent1).Include(P => P.EntitiesDependent2).AsSplitQuery().Include(P => P.EntitiesDependent3).ToArray();

						SW.Stop();

						CConsoleHelpers.WriteLine($"QUERY TIME [{SW.ElapsedMilliseconds} ms].",ConsoleColor.Blue);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("LINQ OPERATOR [Include] and LINQ OPERATOR [AsSplitQuery] after 2. LINQ OPERATOR [Include]:",ConsoleColor.Cyan);

						Stopwatch								SW=new Stopwatch();

						SW.Start();

						// !!!!! QUERY je VYRAZNE RYCHLEJSIA, lebo sa pouzil LINQ OPERATOR [AsSplitQuery].
						Context.EntitiesIncludePrincipal.Include(P => P.EntitiesDependent1).AsSplitQuery().Include(P => P.EntitiesDependent2).Include(P => P.EntitiesDependent3).ToArray();

						SW.Stop();

						CConsoleHelpers.WriteLine($"QUERY TIME [{SW.ElapsedMilliseconds} ms].",ConsoleColor.Blue);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparator();

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("LINQ OPERATOR [Include] and LINQ OPERATOR [AsSplitQuery] after 1. LINQ OPERATOR [Include]:",ConsoleColor.Cyan);

						Stopwatch								SW=new Stopwatch();

						SW.Start();

						// !!!!! QUERY je VYRAZNE RYCHLEJSIA, lebo sa pouzil LINQ OPERATOR [AsSplitQuery].
						Context.EntitiesIncludePrincipal.AsSplitQuery().Include(P => P.EntitiesDependent1).Include(P => P.EntitiesDependent2).Include(P => P.EntitiesDependent3).ToArray();

						SW.Stop();

						CConsoleHelpers.WriteLine($"QUERY TIME [{SW.ElapsedMilliseconds} ms].",ConsoleColor.Blue);
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
		private static void TestMaxFunction()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("ALL ENTITIES:",ConsoleColor.Cyan);

						CEntityMaxPrincipal[]					Entities=Context.EntitiesMaxPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityMaxPrincipal.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("LINQ OPERATOR [Max] RETURNING VALUE [NULL]:",ConsoleColor.Cyan);

						// !!!!! Pouzije sa LINQ OPERATOR [Max].
						// !!!!! VALUE 'CMaxPrincipalWithMax.EntitiesDependentMaxValue' MUSI byt NULLABLE, pretoze LINQ OPERATOR [Max] MOZE vratit VALUE [NULL].
						CMaxPrincipalWithMax[]					Values=Context.EntitiesMaxPrincipal.Include(P => P.EntitiesDependent).Select(P => new CMaxPrincipalWithMax(P.EntityPrincipalID,P.EntityPrincipalValue,P.EntitiesDependent.Max(P => P.EntityDependentValue))).ToArray();

						CMaxPrincipalWithMax.PrintToConsole(Values);
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
		private static void TestGroupByFunction()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("ALL ENTITIES:",ConsoleColor.Cyan);

						CEntityGroupByFunction[]				Entities=Context.EntitiesGroupByFunction.ToArray();

						CEntityGroupByFunction.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("LINQ OPERATOR [GroupBy]:",ConsoleColor.Cyan);

						// !!!!! Pouzije sa LINQ OPERATOR [GroupBy] s COMPLEX KEY 'CGroupByFunctionKey' a VALUE 'CGroupByFunctionValue', ktora vola AGGREGATION FUNCTION.
						CGroupByFunctionValue[]					Groups=Context.EntitiesGroupByFunction.GroupBy(P => new CGroupByFunctionKey{Number=P.Number,NumberAsText=P.NumberAsText}).Select(P => new CGroupByFunctionValue{Number=P.Key.Number,NumberAsText=P.Key.NumberAsText,Sum=P.Sum(R => R.NumericValue)}).ToArray();

						CGroupByFunctionValue.PrintToConsole(Groups);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("LINQ OPERATOR [GroupBy] and LINQ OPERATOR [Where] to GENERATE HAVING CLAUSE:",ConsoleColor.Cyan);

						// !!!!! Pouzije sa LINQ OPERATOR [GroupBy] s COMPLEX KEY 'CGroupByFunctionKey' a VALUE 'CGroupByFunctionValue', ktora vola AGGREGATION FUNCTION.
						// !!!!! Za LINQ OPERATOR [GroupBy] sa pouzije LINQ OPERATOR [Where], ktory sa prelozil na HAVING CLAUSE.
						CGroupByFunctionValue[]					Groups=Context.EntitiesGroupByFunction.GroupBy(P => new CGroupByFunctionKey{Number=P.Number,NumberAsText=P.NumberAsText}).Where(P => P.Sum(R => R.NumericValue)>10).Select(P => new CGroupByFunctionValue{Number=P.Key.Number,NumberAsText=P.Key.NumberAsText,Sum=P.Sum(R => R.NumericValue)}).ToArray();

						CGroupByFunctionValue.PrintToConsole(Groups);
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
		private static void TestCustomConstructors()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityConstructorsPrincipal[]			Entities=Context.EntitiesConstructorsPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityConstructorsPrincipal.PrintToConsole(Entities);
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
		private static void TestLazyLoading()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityLazyLoadingPrincipal[]			Entities=Context.EntitiesLazyLoadingPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityLazyLoadingPrincipal.PrintToConsole(Entities);
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
		private static void TestRelationshipInsertOfNewEntities()
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

						CEntityOneToManyPrincipal				PrincipalEntity=new CEntityOneToManyPrincipal("NEW ENTITY PRINCIPAL",new List<CEntityOneToManyDependent>());
						CEntityOneToManyDependent				DependentEntity=new CEntityOneToManyDependent("NEW ENTITY DEPENDENT");

						CConsoleHelpers.WriteLine("BEFORE ADD ENTITIES to CONTEXT.",ConsoleColor.Yellow);

						// !!!!! Pred volanim METHOD [int SaveChanges()] PROPERTIES PRIMARY KEYS a FOREIGN KEYS su nastavene na DEFAULT VALUES.
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(PrincipalEntity)}.{nameof(PrincipalEntity.EntityPrincipalID)}] - [{PrincipalEntity.EntityPrincipalID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(DependentEntity)}.{nameof(DependentEntity.EntityDependentID)}] - [{DependentEntity.EntityDependentID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(DependentEntity)}.{nameof(DependentEntity.EntityPrincipalID)}] - [{DependentEntity.EntityPrincipalID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(DependentEntity)}.{nameof(DependentEntity.EntityPrincipal)}] - [{DependentEntity.EntityPrincipal}].",ConsoleColor.Blue);

						PrincipalEntity.EntitiesDependent.Add(DependentEntity);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity);

						CConsoleHelpers.WriteLine("AFTER ADD ENTITIES to CONTEXT.",ConsoleColor.Yellow);

						// !!!!! Pred volanim METHOD [int SaveChanges()] PROPERTIES PRIMARY KEYS a FOREIGN KEYS su nastavene na DEFAULT VALUES.
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(PrincipalEntity)}.{nameof(PrincipalEntity.EntityPrincipalID)}] - [{PrincipalEntity.EntityPrincipalID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(DependentEntity)}.{nameof(DependentEntity.EntityDependentID)}] - [{DependentEntity.EntityDependentID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(DependentEntity)}.{nameof(DependentEntity.EntityPrincipalID)}] - [{DependentEntity.EntityPrincipalID}].",ConsoleColor.Blue);
						// !!!!! NAVIGATION PROPERTY je KOREKTNE NASTAVENA.
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(DependentEntity)}.{nameof(DependentEntity.EntityPrincipal)}] - [{DependentEntity.EntityPrincipal}].",ConsoleColor.Blue);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"ENTITY was INSERTED !",ConsoleColor.Blue);

							CConsoleHelpers.WriteLine("AFTER SAVE CHANGES.",ConsoleColor.Yellow);

							// !!!!! Po volani METHOD [int SaveChanges()] PROPERTIES PRIMARY KEYS a FOREIGN KEYS su nastavene na VALUES nacitane z DB.
							CConsoleHelpers.WriteLine($"PROPERTY [{nameof(PrincipalEntity)}.{nameof(PrincipalEntity.EntityPrincipalID)}] - [{PrincipalEntity.EntityPrincipalID}].",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PROPERTY [{nameof(DependentEntity)}.{nameof(DependentEntity.EntityDependentID)}] - [{DependentEntity.EntityDependentID}].",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PROPERTY [{nameof(DependentEntity)}.{nameof(DependentEntity.EntityPrincipalID)}] - [{DependentEntity.EntityPrincipalID}].",ConsoleColor.Blue);
							// !!!!! NAVIGATION PROPERTY je KOREKTNE NASTAVENA.
							CConsoleHelpers.WriteLine($"PROPERTY [{nameof(DependentEntity)}.{nameof(DependentEntity.EntityPrincipal)}] - [{DependentEntity.EntityPrincipal}].",ConsoleColor.Blue);
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
		private static void TestRelationshipInsertOfNewAndExistingEntities()
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
						CConsoleHelpers.WriteLine("BEFORE INSERT ENTITY N:",ConsoleColor.Cyan);

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
						CConsoleHelpers.WriteLine("INSERTING ENTITY N:",ConsoleColor.Cyan);

						CEntityManyToManyN						EntityN=new CEntityManyToManyN("NEW ENTITY N");

						Context.EntitiesManyToManyN.Add(EntityN);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID2=EntityN.EntityNID;

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
						CConsoleHelpers.WriteLine("AFTER INSERT ENTITY N:",ConsoleColor.Cyan);

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
						CConsoleHelpers.WriteLine("INSERTING ENTITY M and ENTITY MN:",ConsoleColor.Cyan);

						CEntityManyToManyN						ExistingEntityN=Context.EntitiesManyToManyN.Where(P => P.EntityNID==ID2).First();
						CEntityManyToManyMN						NewEntityMN=new CEntityManyToManyMN("NEW ENTITY MN");

						NewEntityMN.EntityN=ExistingEntityN;

						CEntityManyToManyM						NewEntityM=new CEntityManyToManyM("NEW ENTITY M");

						NewEntityM.EntitiesMN.Add(NewEntityMN);

						CConsoleHelpers.WriteLine("BEFORE ADD ENTITIES to CONTEXT.",ConsoleColor.Yellow);

						// !!!!! Pred volanim METHOD [EntityEntry<TEntity> Add(TEntity Entity)] PROPERTIES PRIMARY KEYS a FOREIGN KEYS su nastavene na DEFAULT VALUES.
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(NewEntityM)}.{nameof(NewEntityM.EntityMID)}] - [{NewEntityM.EntityMID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(NewEntityMN)}.{nameof(NewEntityMN.EntityMID)}] - [{NewEntityMN.EntityMID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(NewEntityMN)}.{nameof(NewEntityMN.EntityNID)}] - [{NewEntityMN.EntityNID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(ExistingEntityN)}.{nameof(ExistingEntityN.EntityNID)}] - [{ExistingEntityN.EntityNID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(ExistingEntityN)}.{nameof(ExistingEntityN.EntitiesMN)}] - [{ExistingEntityN.EntitiesMN}].",ConsoleColor.Blue);

						Context.EntitiesManyToManyM.Add(NewEntityM);

						CConsoleHelpers.WriteLine("AFTER ADD ENTITIES to CONTEXT.",ConsoleColor.Yellow);

						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(NewEntityM)}.{nameof(NewEntityM.EntityMID)}] - [{NewEntityM.EntityMID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(NewEntityMN)}.{nameof(NewEntityMN.EntityMID)}] - [{NewEntityMN.EntityMID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(NewEntityMN)}.{nameof(NewEntityMN.EntityNID)}] - [{NewEntityMN.EntityNID}].",ConsoleColor.Blue);
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(ExistingEntityN)}.{nameof(ExistingEntityN.EntityNID)}] - [{ExistingEntityN.EntityNID}].",ConsoleColor.Blue);
						// !!!!! NAVIGATION PROPERTY je KOREKTNE NASTAVENA.
						CConsoleHelpers.WriteLine($"PROPERTY [{nameof(ExistingEntityN)}.{nameof(ExistingEntityN.EntitiesMN)}] - [{ExistingEntityN.EntitiesMN}].",ConsoleColor.Blue);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=NewEntityM.EntityMID;

							CConsoleHelpers.WriteLine("AFTER SAVE CHANGES.",ConsoleColor.Yellow);

							// !!!!! Po volani METHOD [int SaveChanges()] PROPERTIES PRIMARY KEYS a FOREIGN KEYS su nastavene na VALUES nacitane z DB.
							CConsoleHelpers.WriteLine($"PROPERTY [{nameof(NewEntityM)}.{nameof(NewEntityM.EntityMID)}] - [{NewEntityM.EntityMID}].",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PROPERTY [{nameof(NewEntityMN)}.{nameof(NewEntityMN.EntityMID)}] - [{NewEntityMN.EntityMID}].",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PROPERTY [{nameof(NewEntityMN)}.{nameof(NewEntityMN.EntityNID)}] - [{NewEntityMN.EntityNID}].",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PROPERTY [{nameof(ExistingEntityN)}.{nameof(ExistingEntityN.EntityNID)}] - [{ExistingEntityN.EntityNID}].",ConsoleColor.Blue);
							// !!!!! NAVIGATION PROPERTY je KOREKTNE NASTAVENA.
							CConsoleHelpers.WriteLine($"PROPERTY [{nameof(ExistingEntityN)}.{nameof(ExistingEntityN.EntitiesMN)}] - [{ExistingEntityN.EntitiesMN}].",ConsoleColor.Blue);

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
						CConsoleHelpers.WriteLine("AFTER INSERT ENTITY M and ENTITY MN:",ConsoleColor.Cyan);

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

						CEntityManyToManyM						EntityM=Context.EntitiesManyToManyM.Where(P => P.EntityMID==ID1).First();
						CEntityManyToManyN						EntityN=Context.EntitiesManyToManyN.Where(P => P.EntityNID==ID2).First();

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
		private static void TestCopyingEntityWithRelationship()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE COPY:",ConsoleColor.Cyan);

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
						CConsoleHelpers.WriteLine("COPYING:",ConsoleColor.Cyan);

						// !!!!! Pri kopirovani ENTITIES s RELATIONSHIPS MUSI byt pouzity LINQ OPERATOR [AsNoTracking].
						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).AsNoTracking().First();

						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY READ from DB.",ConsoleColor.Yellow);

						CConsoleHelpers.WriteLine(PrincipalEntity.Print(null),ConsoleColor.Blue);

						CConsoleHelpers.WriteLineSeparator();

						// !!! Vykona sa RESET PRIMARY KEYS a FOREIGN KEYS, pricom RELATIONSHIP PROPERTY OSTANU NASTAVENE.
						PrincipalEntity.EntityPrincipalID=default(int);

						for(int Index=0;Index<PrincipalEntity.EntitiesDependent.Count;Index++)
						{
							CEntityOneToManyDependent			DependentEntity=PrincipalEntity.EntitiesDependent.ElementAt(Index);

							DependentEntity.EntityDependentID=default(int);
							DependentEntity.EntityPrincipalID=default(int);
						}

						CConsoleHelpers.WriteLine($"COPIED PRINCIPAL ENTITY MODIFIED.",ConsoleColor.Yellow);

						CConsoleHelpers.WriteLine(PrincipalEntity.Print(null),ConsoleColor.Blue);

						CConsoleHelpers.WriteLineSeparator();

						// !!! PRINCIPAL ENTITY sa PRIDA do DB CONTEXT.
						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity);
						
						CConsoleHelpers.WriteLine($"COPIED PRINCIPAL ENTITY ADDED to DB CONTEXT.",ConsoleColor.Yellow);

						CConsoleHelpers.WriteLine(PrincipalEntity.Print(null),ConsoleColor.Blue);

						CConsoleHelpers.WriteLineSeparator();

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=PrincipalEntity.EntityPrincipalID;

							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY was INSERTED !",ConsoleColor.Blue);

							CConsoleHelpers.WriteLine(PrincipalEntity.Print(null),ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER COPY:",ConsoleColor.Cyan);

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
		private static void TestFastDelete()
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

						CEntityOneToManyDependent				EntityDependent1=new CEntityOneToManyDependent("NEW ENTITY DEPENDENT 111");
						CEntityOneToManyDependent				EntityDependent2=new CEntityOneToManyDependent("NEW ENTITY DEPENDENT 222");
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

						// !!!!! NEVYKONA sa DB QUERY, pretoze PRIMARY KEY ENTITY, ktora ma byt DELETED je znama.
						// !!!!! VYTVORI sa NOVA instancia ENTITY CLASS, ktore sa nastavi EXISTUJUCI PRIMARY KEY.
						CEntityOneToManyPrincipal				Entity=new CEntityOneToManyPrincipal();

						Entity.EntityPrincipalID=ID;

						// !!! VYKONA sa DELETE tejto NOVEJ instancie ENTITY CLASS.
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
			//TestRelationalFixup();
			//TestAsNoTrackingAndAsNoTrackingWithIdentityResolution();
			//TestSelectHierarchicalEntities();
			//TestLinqOperatorAsSplitQuery();
			//TestMaxFunction();
			//TestGroupByFunction();
			//TestCustomConstructors();
			//TestLazyLoading();
			//TestRelationshipInsertOfNewEntities();
			//TestRelationshipInsertOfNewAndExistingEntities();
			//TestCopyingEntityWithRelationship();
			TestFastDelete();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------