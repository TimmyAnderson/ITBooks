using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace QueryingDB
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

			CNumber												Number1A=new CNumber(1,"ONE A");
			CNumber												Number1B=new CNumber(1,"ONE B");
			CNumber												Number2A=new CNumber(2,"TWO A");
			CNumber												Number2B=new CNumber(2,"TWO B");
			CNumber												Number3=new CNumber(3,"THREE");
			CNumber												Number4=new CNumber(4,"FOUR");
			CNumber												Number5=new CNumber(5,"FIVE");
			CNumber												Number6=new CNumber(6,"SIX");
			CNumber												Number7=new CNumber(7,"SEVEN");
			CNumber												Number8=new CNumber(8,"EIGHT");
			CNumber												Number9=new CNumber(9,"NINE");
			CNumber												Number10=new CNumber(10,"TEN");

			Context.EntitiesNumbers.Add(Number1A);
			Context.EntitiesNumbers.Add(Number1B);
			Context.EntitiesNumbers.Add(Number2A);
			Context.EntitiesNumbers.Add(Number2B);
			Context.EntitiesNumbers.Add(Number3);
			Context.EntitiesNumbers.Add(Number4);
			Context.EntitiesNumbers.Add(Number5);
			Context.EntitiesNumbers.Add(Number6);
			Context.EntitiesNumbers.Add(Number7);
			Context.EntitiesNumbers.Add(Number8);
			Context.EntitiesNumbers.Add(Number9);
			Context.EntitiesNumbers.Add(Number10);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void CreateTestDBUsingEnsureCreated()
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
							// !!! Na vytvorenie DB sa pouziva METHOD DatabaseFacade.EnsureCreated().
							Context.Database.EnsureCreated();

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
		private static void CreateTestDBUsingMigrations()
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
		private static void TestSelectWithExplicitConnectionString()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				string											ConnectionString=@"Data Source=MyDatabase.db";
				DbContextOptionsBuilder<CDBContextWithConstructor>	ContextBuilder=new DbContextOptionsBuilder<CDBContextWithConstructor>();

				// CONNECTION STRING sa explicitne nastavi cez CONSTRUCTOR.
				ContextBuilder.UseSqlite(ConnectionString);

				using(CDBContextWithConstructor Context=new CDBContextWithConstructor(ContextBuilder.Options))
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
		private static void TestSelectEntityOneToOne()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityOneToOnePrincipal[]				Entities=Context.EntitiesOneToOnePrincipal.Include(P => P.EntityDependent).ToArray();

						CEntityOneToOnePrincipal.PrintToConsole(Entities);
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
		private static void TestSelectEntityOneToMany()
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
		private static void TestSelectEntityManyToMany()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CEntityManyToManyM[]					EntitiesM=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(EntitiesM);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
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
		private static void TestEagerLoading()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! NEVYKONA sa EAGER LOADING, takze DEPENDENT RECORDS NEBUDU nacitane.
						CEntityOneToManyPrincipal				Entity1=Context.EntitiesOneToManyPrincipal.First();
						string									Entity1Text=Entity1.Print(null);

						CConsoleHelpers.Write(Entity1Text,ConsoleColor.Green);
						CConsoleHelpers.WriteLineSeparator();

						// !!! NEVYKONA sa EAGER LOADING, takze DEPENDENT RECORDS BUDU nacitane.
						CEntityOneToManyPrincipal				Entity2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).First();
						string									Entity2Text=Entity2.Print(null);

						CConsoleHelpers.Write(Entity2Text,ConsoleColor.Green);
						CConsoleHelpers.WriteLineSeparator();

						// !!! VYKONA sa EAGER LOADING, kde sa nacitaju nielen DEPENDENT RECORDS na ktore existuje z PRINCIPAL ENTITY NAVIGATION PROPERTY, ale aj DEPENDENT RECORDS, na ktore je mozny pristupu cez inu DEPEDENT ENTITY pomocou METHOD [IIncludableQueryable<TEntity,TProperty> ThenInclude<TEntity,TPreviousProperty,TProperty>(Expression<Func<TPreviousProperty,TProperty>> NavigationPropertyPath)]. Teda nacita sa RELATIONSHIP 2. urovne.
						CEntityManyToManyM						Entity3=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).First();
						string									Entity3Text=Entity3.Print(null);

						CConsoleHelpers.Write(Entity3Text,ConsoleColor.Green);
						CConsoleHelpers.WriteLineSeparator();
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
		private static void TestEagerLoadingIncludeFiltering()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				CConsoleHelpers.WriteLine("NO FILTERING:",ConsoleColor.Cyan);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! NEAPLIKUJE sa FILTERING v OPERATOR INCLUDE.
						CEntityManyToManyM[]					EntitiesM=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(EntitiesM);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				CConsoleHelpers.WriteLine("FILTERING in OPERATOR INCLUDE:",ConsoleColor.Cyan);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! APLIKUJE sa FILTERING v OPERATOR INCLUDE.
						// !!!!! OPERATOR WHERE sa aplikuje na v RAMCI OPERATOR INCLUDE a nie az za nim.
						CEntityManyToManyM[]					EntitiesM=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN.Where(P => P.EntityMNValue=="LINK 11")).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(EntitiesM);
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
		private static void TestEagerLoadingIncludeSorting()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				CConsoleHelpers.WriteLine("NO SORTING:",ConsoleColor.Cyan);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! NEAPLIKUJE sa FILTERING v OPERATOR INCLUDE.
						CEntityManyToManyM[]					EntitiesM=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(EntitiesM);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				CConsoleHelpers.WriteLine("SORTING in OPERATOR INCLUDE:",ConsoleColor.Cyan);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! APLIKUJE sa FILTERING v OPERATOR INCLUDE.
						// !!!!! OPERATOR ORDER_DESCENCING sa aplikuje na v RAMCI OPERATOR INCLUDE a nie az za nim.
						CEntityManyToManyM[]					EntitiesM=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN.OrderByDescending(P => P.EntityMNValue)).ThenInclude(P => P.EntityN).ToArray();

						CEntityManyToManyM.PrintToConsole(EntitiesM);
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
		private static void TestExplicitLoading()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! Nacita sa PRINCIPAL RECORD.
						CEntityManyToManyM						EntityManyToManyM=Context.EntitiesManyToManyM.First();
						string									EntityManyToManyM1Text=EntityManyToManyM.Print(null);

						CConsoleHelpers.Write(EntityManyToManyM1Text,ConsoleColor.Green);
						CConsoleHelpers.WriteLineSeparator();

						// !!! Ziska sa ENTRY na instanciu ENTITY CLASS 'CEntityManyToManyM'.
						EntityEntry<CEntityManyToManyM>			EntryEntityManyToManyM=Context.Entry(EntityManyToManyM);

						// !!! METHOD [CollectionEntry<TEntity,TProperty> Collection<TProperty>(Expression<Func<TEntity,IEnumerable<TProperty>>> PropertyExpression)] vracia instanciu CLASS [CollectionEntry<TEntity,TProperty>].
						// !!!!! METHOD [CollectionEntry<TEntity,TProperty> Collection<TProperty>(Expression<Func<TEntity,IEnumerable<TProperty>>> PropertyExpression)] sa pouziva vtedy, ak NAVIGATION PROPERTY je TYPE [ICollection<TEntity>].
						CollectionEntry<CEntityManyToManyM,CEntityManyToManyMN>	CollectionEntry=EntryEntityManyToManyM.Collection(P => P.EntitiesMN);

						// !!! Explicitne sa nacitaju RECORDS pre ENTITY CLASS 'CEntityManyToManyMN'.
						// !!!!! METHOD [void Load()] vykonava explicitne nacitanie RECORDS pre ENTITY CLASS 'CEntityManyToManyMN'. 
						CollectionEntry.Load();

						string									EntityManyToManyM2Text=EntityManyToManyM.Print(null);

						CConsoleHelpers.Write(EntityManyToManyM2Text,ConsoleColor.Green);
						CConsoleHelpers.WriteLineSeparator();

						// !!! Nacitaju sa vsetky instancie ENTITY CLASS 'CEntityManyToManyN' pomocou instancii ENTITY CLASS 'CEntityManyToManyMN'.
						foreach(CEntityManyToManyMN EntityManyToManyMN in EntityManyToManyM.EntitiesMN)
						{
							// !!! Ziska sa ENTRY na instanciu ENTITY CLASS 'CEntityManyToManyMN'.
							EntityEntry<CEntityManyToManyMN>	EntryEntityManyToManyMN=Context.Entry(EntityManyToManyMN);

							// !!! METHOD [ReferenceEntry<TEntity,TProperty> Reference<TProperty>(Expression<Func<TEntity,TProperty>> PropertyExpression)] vracia instanciu CLASS [ReferenceEntry<TEntity,TProperty>].
							// !!!!! METHOD ReferenceEntry<TEntity,TProperty> Reference<TProperty>(Expression<Func<TEntity,TProperty>> PropertyExpression)] vracia instanciu CLASS [ReferenceEntry<TEntity,TProperty>] sa pouziva vtedy, ak NAVIGATION PROPERTY je TYPE [TEntity].
							ReferenceEntry<CEntityManyToManyMN,CEntityManyToManyN>	ReferenceEntryEntityManyToManyN=EntryEntityManyToManyMN.Reference(P => P.EntityN);

							// !!! Explicitne sa nacita RECORD pre ENTITY CLASS 'CEntityManyToManyN'.
							// !!!!! METHOD [void Load()] vykonava explicitne nacitanie RECORD pre ENTITY CLASS 'CEntityManyToManyN'. 
							ReferenceEntryEntityManyToManyN.Load();
						}

						string									EntityManyToManyM3Text=EntityManyToManyM.Print(null);

						CConsoleHelpers.Write(EntityManyToManyM3Text,ConsoleColor.Green);
						CConsoleHelpers.WriteLineSeparator();
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
		private static void TestExplicitLoadingByQuery()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! Nacita sa PRINCIPAL RECORD.
						CEntityOneToManyPrincipal				EntityOneToManyPrincipal=Context.EntitiesOneToManyPrincipal.First();
						string									EntityOneToManyPrincipalText=EntityOneToManyPrincipal.Print(null);

						CConsoleHelpers.Write(EntityOneToManyPrincipalText,ConsoleColor.Green);
						CConsoleHelpers.WriteLineSeparator();

						// !!! Ziska sa ENTRY na instanciu ENTITY CLASS 'CEntityOneToManyPrincipal'.
						EntityEntry<CEntityOneToManyPrincipal>	EntryEntityOneToManyPrincipal=Context.Entry(EntityOneToManyPrincipal);

						// !!! METHOD [CollectionEntry<TEntity,TProperty> Collection<TProperty>(Expression<Func<TEntity,IEnumerable<TProperty>>> PropertyExpression)] vracia instanciu CLASS [CollectionEntry<TEntity,TProperty>].
						// !!!!! METHOD [CollectionEntry<TEntity,TProperty> Collection<TProperty>(Expression<Func<TEntity,IEnumerable<TProperty>>> PropertyExpression)] sa pouziva vtedy, ak NAVIGATION PROPERTY je TYPE [ICollection<TEntity>].
						CollectionEntry<CEntityOneToManyPrincipal,CEntityOneToManyDependent>	CollectionEntryOneToManyDependent=EntryEntityOneToManyPrincipal.Collection(P => P.EntitiesDependent);

						// !!! Nad instanciu CLASS [CollectionEntry<CEntityOneToManyPrincipal,CEntityOneToManyDependent>] sa vykona QUERY pomocou METHOD [IQueryable<TRelatedEntity> Query()].
						int										NumberOfDependentEntities=CollectionEntryOneToManyDependent.Query().Count();

						CConsoleHelpers.WriteLine($"NUMBER of DEPENDENT ENTITIES [{NumberOfDependentEntities}] !",ConsoleColor.Red);
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
		private static void TestSelectLoading()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! Nacita sa RECORD s vybranymi COLUMNS.
						// !!!!! LINQ QUERY obsahuje SUBQUERY.
						CSelectLoading							SelectLoading=Context.EntitiesOneToManyPrincipal.Select(P => new CSelectLoading(P.EntityPrincipalID,P.EntityPrincipalValue,P.EntitiesDependent.Count)).First();

						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY ID [{SelectLoading.PrincipalEntityID}] !",ConsoleColor.Green);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY VALUE [{SelectLoading.PrincipalEntityValue}] !",ConsoleColor.Green);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY COUNT [{SelectLoading.DependentEntityCount}] !",ConsoleColor.Green);
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
		private static string CustomCode(string Value, int NumberOfCharacters)
		{
			string												Result=Value.Substring(0,NumberOfCharacters).ToString();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void TestClientVsServerSideExecution()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! Nacita sa RECORD, ktory je ciastocne vykonany na SERVER SIDE aj na CLIENT SIDE.
						// !!! CODE [string.Join(' ',LINQ_QUERY)] je po vykonani LINQ QUERY vykonany na CLIENT SIDE.
						CServerVSClientExecution				ServerVSClientExecution=Context.EntitiesOneToManyPrincipal.Select(P => new CServerVSClientExecution(P.EntityPrincipalID,P.EntityPrincipalValue,string.Join(' ',P.EntitiesDependent.OrderByDescending(P => P.EntityPrincipal).Select(P => P.EntityDependentValue)),P.EntitiesDependent.Count)).Skip(1).First();

						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY ID [{ServerVSClientExecution.PrincipalEntityID}] !",ConsoleColor.Green);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY ID [{ServerVSClientExecution.PrincipalEntityValue}] !",ConsoleColor.Green);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY VALUES [{ServerVSClientExecution.DependentEntityValues}] !",ConsoleColor.Green);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY COUNT [{ServerVSClientExecution.DependentEntityCount}] !",ConsoleColor.Green);
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

			CConsoleHelpers.WriteLineSeparators(3);

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!!!! Vykona sa CLIENT EXECUTION CUSTOM C# METHOD, lebo je v POSLEDNEJ CASTI QUERY.
						string									ServerVSClientExecutionText=Context.EntitiesOneToManyPrincipal.Select(P => CustomCode(P.EntityPrincipalValue,2)).First();

						CConsoleHelpers.WriteLine($"VALUE [{ServerVSClientExecutionText}] !",ConsoleColor.Green);
						CConsoleHelpers.WriteLineSeparator();
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

			CConsoleHelpers.WriteLineSeparators(3);

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!!!! HODI EXCEPTION, pretoze CLIENT SIDE CODE nie je ako POSLEDNA CAST QUERY.
						CEntityOneToManyPrincipal				ServerVSClientExecution=Context.EntitiesOneToManyPrincipal.OrderBy(P => CustomCode(P.EntityPrincipalValue,2)).First();
						string									ServerVSClientExecutionText=ServerVSClientExecution.Print(null);

						CConsoleHelpers.Write(ServerVSClientExecutionText,ConsoleColor.Green);
						CConsoleHelpers.WriteLineSeparator();
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
		// !!!!! QUERY pouziva na vytvorenie instancie CLASS [CNumberDTO1] DEFAULT CONTRUCTOR.
		// !!!!! Vyuzitie DEFAULT CONTRUCTOR sposobi, ze na vyslednu INSTANCIU [IQueryable<CNumberDTO1>] JE MOZNE aplikovat LINQ OPERATORS ako napriklad LINQ OPERATROR [OrderBy].
		private static IQueryable<CNumberDTO1> CreateQueryForNumberDTO1(IQueryable<CNumber> Numbers)
		{
			IQueryable<CNumberDTO1>								Query=Numbers.Select(P => new CNumberDTO1{NumberID=P.NumberID,Number=P.Number,NumberAsText=P.NumberAsText,NumberSquared=(P.Number*P.Number)});

			return(Query);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! QUERY pouziva na vytvorenie instancie CLASS [CNumberDTO2] NON-DEFAULT CONTRUCTOR.
		// !!!!! Vyuzitie NON-DEFAULT CONTRUCTOR sposobi, ze na vyslednu INSTANCIU [IQueryable<CNumberDTO2>] NIE JE MOZNE aplikovat LINQ OPERATORS ako napriklad LINQ OPERATROR [OrderBy].
		private static IQueryable<CNumberDTO2> CreateQueryForNumberDTO2(IQueryable<CNumber> Numbers)
		{
			IQueryable<CNumberDTO2>								Query=Numbers.Select(P => new CNumberDTO2(P.NumberID,P.Number,P.NumberAsText,(P.Number*P.Number)));

			return(Query);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void TestDefaultVSNonDefaultConstructorsInQueries()
		{
			CConsoleHelpers.WriteLineSeparator();

			bool												ShowLogRecords=false;

			try
			{
				using(CDBContext Context=new CDBContext(ShowLogRecords))
				{
					try
					{
						CConsoleHelpers.WriteLine("DEFAULT CONSTRUCTOR:",ConsoleColor.Cyan);

						// !!!!! CODE zbehne USPESNE, pretoze NEPOUZIVA NON-DEFAULT CONSTRUCTOR CLASS [CNumberDTO1], ale DEFAULT CONSTRUCTOR.
						CNumberDTO1[]							NumberDTO1s=CreateQueryForNumberDTO1(Context.EntitiesNumbers).ToArray();

						Thread.Sleep(500);

						CNumberDTO1.PrintToConsole(NumberDTO1s);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext(ShowLogRecords))
				{
					try
					{
						CConsoleHelpers.WriteLine("DEFAULT CONSTRUCTOR + LINQ OPERATOR [Where(P => P.Number>5)]:",ConsoleColor.Cyan);

						// !!!!! CODE zbehne USPESNE, pretoze NEPOUZIVA NON-DEFAULT CONSTRUCTOR CLASS [CNumberDTO1], ale DEFAULT CONSTRUCTOR.
						CNumberDTO1[]							NumberDTO1s=CreateQueryForNumberDTO1(Context.EntitiesNumbers).Where(P => P.Number>5).ToArray();

						Thread.Sleep(500);

						CNumberDTO1.PrintToConsole(NumberDTO1s);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext(ShowLogRecords))
				{
					try
					{
						CConsoleHelpers.WriteLine("DEFAULT CONSTRUCTOR + LINQ OPERATOR [OrderByDescending(P => P.Number)]:",ConsoleColor.Cyan);

						// !!!!! CODE zbehne USPESNE, pretoze NEPOUZIVA NON-DEFAULT CONSTRUCTOR CLASS [CNumberDTO1], ale DEFAULT CONSTRUCTOR.
						CNumberDTO1[]							NumberDTO1s=CreateQueryForNumberDTO1(Context.EntitiesNumbers).OrderByDescending(P => P.Number).ToArray();

						Thread.Sleep(500);

						CNumberDTO1.PrintToConsole(NumberDTO1s);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext(ShowLogRecords))
				{
					try
					{
						CConsoleHelpers.WriteLine("NON-DEFAULT CONSTRUCTOR:",ConsoleColor.Cyan);

						// !!!!! CODE prebehne USPESNE, no uz na vratenu INSTANCIU CLASS [IQueryable<CNumberDTO2>] NIE JE MOZNE POUZIT LINQ OPERATOR [OrderBy], pretoze takuto LINQ QUERY by ENTITY FRAMEWORK CORE nedokazal prelozit do SQL COMMANDS.
						CNumberDTO2[]							NumberDTO2s=CreateQueryForNumberDTO2(Context.EntitiesNumbers).ToArray();

						Thread.Sleep(500);

						CNumberDTO2.PrintToConsole(NumberDTO2s);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext(ShowLogRecords))
				{
					try
					{
						CConsoleHelpers.WriteLine("NON-DEFAULT CONSTRUCTOR + LINQ OPERATOR [Where(P => P.Number>5)]:",ConsoleColor.Cyan);

						// !!!!! CODE hodi EXCEPTION, pretoze METHOD [IQueryable<CNumberDTO2> CreateQueryForNumberDTO2(IQueryable<CNumber> Numbers)] POUZIVA NON-DEFAULT CONSTRUCTOR CLASS [CNumberDTO2] co je v podstate CUSTOM C# METHOD na ktory nasledne aplikuje LINQ OPERATOR [Where]. CUSTOM C# CONSTRUCTOR ENTITY FRAMEWORK CORE NEDOKAZE prelozit do SQL COMMANDS.
						CNumberDTO2[]							NumberDTO2s=CreateQueryForNumberDTO2(Context.EntitiesNumbers).Where(P => P.Number>5).ToArray();

						Thread.Sleep(500);

						CNumberDTO2.PrintToConsole(NumberDTO2s);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext(ShowLogRecords))
				{
					try
					{
						CConsoleHelpers.WriteLine("NON-DEFAULT CONSTRUCTOR + LINQ OPERATOR [OrderByDescending(P => P.Number)]:",ConsoleColor.Cyan);

						// !!!!! CODE hodi EXCEPTION, pretoze METHOD [IQueryable<CNumberDTO2> CreateQueryForNumberDTO2(IQueryable<CNumber> Numbers)] POUZIVA NON-DEFAULT CONSTRUCTOR CLASS [CNumberDTO2] co je v podstate CUSTOM C# METHOD na ktory nasledne aplikuje LINQ OPERATOR [OrderByDescending]. CUSTOM C# CONSTRUCTOR ENTITY FRAMEWORK CORE NEDOKAZE prelozit do SQL COMMANDS.
						CNumberDTO2[]							NumberDTO2s=CreateQueryForNumberDTO2(Context.EntitiesNumbers).OrderByDescending(P => P.Number).ToArray();

						Thread.Sleep(500);

						CNumberDTO2.PrintToConsole(NumberDTO2s);
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
		public static void TestOrderOperators()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						{
							CConsoleHelpers.WriteLine("LINQ OPERATOR [OrderBy(P => P.Number)] + LINQ OPERATOR [ThenBy(P => P.NumberAsText)]:",ConsoleColor.Cyan);

							// !!! Na koniec QUERY sa prida LINQ OPERATOR [OrderBy] a nasledne LINQ OPERATOR [ThenBy].
							CNumber[]							Numbers=Context.EntitiesNumbers.Where(P => P.Number<=3).OrderBy(P => P.Number).ThenBy(P => P.NumberAsText).ToArray();

							CNumber.PrintToConsole(Numbers);
						}

						CConsoleHelpers.WriteLineSeparators(3);

						{
							CConsoleHelpers.WriteLine("LINQ OPERATOR [OrderByDescending(P => P.Number)] + LINQ OPERATOR [ThenByDescending(P => P.NumberAsText)]:",ConsoleColor.Cyan);

							// !!! Na koniec QUERY sa prida LINQ OPERATOR [OrderByDescending] a nasledne LINQ OPERATOR [ThenByDescending].
							CNumber[]							Numbers=Context.EntitiesNumbers.Where(P => P.Number<=3).OrderByDescending(P => P.Number).ThenByDescending(P => P.NumberAsText).ToArray();

							CNumber.PrintToConsole(Numbers);
						}

						CConsoleHelpers.WriteLineSeparators(3);

						{
							CConsoleHelpers.WriteLine("LINQ OPERATOR [OrderByDescending(P => P.Number))] + LINQ OPERATOR [OrderByDescending(P => P.NumberAsText)]:",ConsoleColor.Cyan);

							// !!! Na koniec QUERY sa prida LINQ OPERATOR [OrderByDescending] a nasledne LINQ OPERATOR [OrderByDescending].
							// !!!!! Kedze je LINQ OPERATOR [OrderByDescending] aplikovany 2 krat, NEDOJDE, k SORTING na 1. a 2. urovni, ale k SORTING na 1. UROVNI, pricom 2. LINQ OPERATOR [OrderByDescending] nahradi 1. volanie LINQ OPERATOR [OrderByDescending].
							CNumber[]							Numbers=Context.EntitiesNumbers.Where(P => P.Number<=3).OrderByDescending(P => P.Number).OrderByDescending(P => P.NumberAsText).ToArray();

							CNumber.PrintToConsole(Numbers);
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
		public static void TestWhereOperator()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						{
							CConsoleHelpers.WriteLine("LINQ WHERE [Where(P => P.Number<=5)]:",ConsoleColor.Cyan);

							// !!! Na koniec QUERY sa prida LINQ OPERATOR [Where].
							CNumber[]							Numbers=Context.EntitiesNumbers.Where(P => P.Number<=5).ToArray();

							CNumber.PrintToConsole(Numbers);
						}

						CConsoleHelpers.WriteLineSeparators(3);

						{
							CConsoleHelpers.WriteLine("LINQ WHERE [Where(P => P.Number>5)]:",ConsoleColor.Cyan);

							// !!! Na koniec QUERY sa prida LINQ OPERATOR [Where].
							CNumber[]							Numbers=Context.EntitiesNumbers.Where(P => P.Number>5).ToArray();

							CNumber.PrintToConsole(Numbers);
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
		public static void TestTextMethods()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						{
							CConsoleHelpers.WriteLine("NO TEXT METHOD:",ConsoleColor.Cyan);

							CNumber[]							Numbers=Context.EntitiesNumbers.ToArray();

							CNumber.PrintToConsole(Numbers);
						}

						CConsoleHelpers.WriteLineSeparators(3);

						{
							CConsoleHelpers.WriteLine("TEXT METHOD [StartsWith('T')]:",ConsoleColor.Cyan);

							// !!! Aplikuje sa STRING METHOD [bool StartsWith(string Value)].
							CNumber[]							Numbers=Context.EntitiesNumbers.Where(P => P.NumberAsText.StartsWith("T")==true).ToArray();

							CNumber.PrintToConsole(Numbers);
						}

						CConsoleHelpers.WriteLineSeparators(3);

						{
							CConsoleHelpers.WriteLine("TEXT METHOD [EndsWith('N')]:",ConsoleColor.Cyan);

							// !!! Aplikuje sa STRING METHOD [bool EndsWith(string Value)].
							CNumber[]							Numbers=Context.EntitiesNumbers.Where(P => P.NumberAsText.EndsWith("N")==true).ToArray();

							CNumber.PrintToConsole(Numbers);
						}

						CConsoleHelpers.WriteLineSeparators(3);

						{
							CConsoleHelpers.WriteLine("TEXT METHOD [Contains('E')]:",ConsoleColor.Cyan);

							// !!! Aplikuje sa STRING METHOD [bool Contains(string Value)].
							CNumber[]							Numbers=Context.EntitiesNumbers.Where(P => P.NumberAsText.Contains("E")==true).ToArray();

							CNumber.PrintToConsole(Numbers);
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
		public static void TestFunctionLike()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						{
							CConsoleHelpers.WriteLine("NO METHOD [Like]:",ConsoleColor.Cyan);

							CNumber[]							Numbers=Context.EntitiesNumbers.ToArray();

							CNumber.PrintToConsole(Numbers);
						}

						CConsoleHelpers.WriteLineSeparators(3);

						{
							CConsoleHelpers.WriteLine("METHOD [Like('%E%')]:",ConsoleColor.Cyan);

							// !!! Aplikuje sa ENTITY FRAMEWORK METHOD [bool DbFunctions.Like(string MatchExpression, string Pattern)], ktora je konvertovana na SQL COMMAND [LIKE].
							CNumber[]							Numbers=Context.EntitiesNumbers.Where(P => EF.Functions.Like(P.NumberAsText,"%E%")==true).ToArray();

							CNumber.PrintToConsole(Numbers);
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
		public static void TestSkipTakeOperators()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						{
							CConsoleHelpers.WriteLine("NO LINQ OPERATOR [Skip] or LINQ OPERATOR [Take]:",ConsoleColor.Cyan);

							CNumber[]							Numbers=Context.EntitiesNumbers.ToArray();

							CNumber.PrintToConsole(Numbers);
						}

						CConsoleHelpers.WriteLineSeparators(3);

						{
							CConsoleHelpers.WriteLine("LINQ OPERATOR [Skip(1)] + LINQ OPERATOR [Take(4)]:",ConsoleColor.Cyan);

							// !!! Aplikuje sa LINQ OPERATOR [IQueryable<TSource> Skip<TSource>(this IQueryable<TSource> Source, int Count)].
							// !!! Aplikuje sa LINQ OPERATOR [IQueryable<TSource> Take<TSource>(this IQueryable<TSource> Source, int Count)].
							// !!!!! COLLECTION MUSI byt ORDERED.
							CNumber[]							Numbers=Context.EntitiesNumbers.OrderBy(P => P.Number).Skip(1).Take(4).ToArray();

							CNumber.PrintToConsole(Numbers);
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
        static void Main(string[] args)
        {
			//CreateTestDBUsingEnsureCreated();
			//CreateTestDBUsingMigrations();
			//TestSelectTestEntity();
			//TestSelectWithExplicitConnectionString();
			//TestSelectEntityOneToOne();
			TestSelectEntityOneToMany();
			//TestSelectEntityManyToMany();
			//TestEagerLoading();
			//TestEagerLoadingIncludeFiltering();
			//TestEagerLoadingIncludeSorting();
			//TestExplicitLoading();
			//TestExplicitLoadingByQuery();
			//TestSelectLoading();
			//TestClientVsServerSideExecution();
			//TestDefaultVSNonDefaultConstructorsInQueries();
			//TestOrderOperators();
			//TestWhereOperator();
			//TestTextMethods();
			//TestFunctionLike();
			//TestSkipTakeOperators();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------