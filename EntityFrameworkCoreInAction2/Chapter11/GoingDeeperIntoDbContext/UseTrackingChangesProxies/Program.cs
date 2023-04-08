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
namespace UseTrackingChangesProxies
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		private static void FillData(CDBContext Context)
		{
			// !!!!! PROXIES sa MUSIA vytvarat pomocou METHOD [TEntity DbContext.CreateProxy<TEntity>(params object[] ConstructorArguments)].
			CEntityOneToManyTrackingChangesProxiesDependent		EntityOneToManyTrackingChangesProxiesDependent11=Context.CreateProxy<CEntityOneToManyTrackingChangesProxiesDependent>(111,"DEPENDENT 111");
			CEntityOneToManyTrackingChangesProxiesDependent		EntityOneToManyTrackingChangesProxiesDependent12=Context.CreateProxy<CEntityOneToManyTrackingChangesProxiesDependent>(222,"DEPENDENT 222");
			CEntityOneToManyTrackingChangesProxiesDependent		EntityOneToManyTrackingChangesProxiesDependent21=Context.CreateProxy<CEntityOneToManyTrackingChangesProxiesDependent>(333,"DEPENDENT 333");
			CEntityOneToManyTrackingChangesProxiesDependent		EntityOneToManyTrackingChangesProxiesDependent22=Context.CreateProxy<CEntityOneToManyTrackingChangesProxiesDependent>(444,"DEPENDENT 444");

			// !!!!! PROXIES sa MUSIA vytvarat pomocou METHOD [TEntity DbContext.CreateProxy<TEntity>(params object[] ConstructorArguments)].
			CEntityOneToManyTrackingChangesProxiesPrincipal		EntityOneToManyTrackingChangesProxiesPrincipal1=Context.CreateProxy<CEntityOneToManyTrackingChangesProxiesPrincipal>(111,"PRINCIPAL 111",new ObservableCollection<CEntityOneToManyTrackingChangesProxiesDependent>(new CEntityOneToManyTrackingChangesProxiesDependent[]{EntityOneToManyTrackingChangesProxiesDependent11,EntityOneToManyTrackingChangesProxiesDependent12}));
			CEntityOneToManyTrackingChangesProxiesPrincipal		EntityOneToManyTrackingChangesProxiesPrincipal2=Context.CreateProxy<CEntityOneToManyTrackingChangesProxiesPrincipal>(222,"PRINCIPAL 222",new ObservableCollection<CEntityOneToManyTrackingChangesProxiesDependent>(new CEntityOneToManyTrackingChangesProxiesDependent[]{EntityOneToManyTrackingChangesProxiesDependent21,EntityOneToManyTrackingChangesProxiesDependent22}));

			Context.EntitiesOneToManyTrackingChangesProxiesPrincipal.Add(EntityOneToManyTrackingChangesProxiesPrincipal1);
			Context.EntitiesOneToManyTrackingChangesProxiesPrincipal.Add(EntityOneToManyTrackingChangesProxiesPrincipal2);
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
		private static object GetOriginalValue(PropertyEntry Property)
		{
			try
			{
				return(Property.OriginalValue);
			}
			catch
			{
				return(null);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void PrintEntityState<TEntity>(CDBContext Context, TEntity Enitity, [CallerArgumentExpression(nameof(Enitity))] string EntityName=null) where TEntity : class
		{
			Context.ChangeTracker.DetectChanges();

			CConsoleHelpers.WriteLineSeparator();

			EntityEntry<TEntity>								EntityEntry=Context.Entry<TEntity>(Enitity);
			ConsoleColor										Color;

			if (EntityEntry.State==EntityState.Detached)
			{
				Color=ConsoleColor.White;
			}
			else if (EntityEntry.State==EntityState.Unchanged)
			{
				Color=ConsoleColor.Green;
			}
			else if (EntityEntry.State==EntityState.Added)
			{
				Color=ConsoleColor.Cyan;
			}
			else if (EntityEntry.State==EntityState.Modified)
			{
				Color=ConsoleColor.Blue;
			}
			else if (EntityEntry.State==EntityState.Deleted)
			{
				Color=ConsoleColor.Red;
			}
			else
			{
				throw(new InvalidOperationException($"UNSUPPORTED VALUE [{EntityEntry.State}]."));
			}

			CConsoleHelpers.WriteLine($"ENTITY [{EntityName}]:",Color);
			CConsoleHelpers.WriteLine($"STATE [{EntityEntry.State}].",Color);

			PropertyEntry[]										Properties=EntityEntry.Properties.ToArray();

			foreach(PropertyEntry Property in Properties)
			{
				if (Property.IsModified==false)
				{
					CConsoleHelpers.WriteLine($"\tPROPERTY [{Property.Metadata.Name}] IS MODIFIED [{Property.IsModified}] ORIGINAL VALUE [{GetOriginalValue(Property) ?? "----- ORIGINAL VALUE NOT STORED in DB CONTEXT. -----"}].",ConsoleColor.Magenta);
				}
				else
				{
					CConsoleHelpers.WriteLine($"\tPROPERTY [{Property.Metadata.Name}] IS MODIFIED [{Property.IsModified}] ORIGINAL VALUE [{GetOriginalValue(Property) ?? "----- ORIGINAL VALUE NOT STORED in DB CONTEXT. -----"}] CURRENT VALUE [{Property.CurrentValue}].",ConsoleColor.Blue);
				}
			}

			NavigationEntry[]									Navigations=EntityEntry.Navigations.ToArray();

			foreach(NavigationEntry Navigation in Navigations)
			{
				StringBuilder									SB=new StringBuilder();

				SB.Append($"\tNAVIGATION [{Navigation.Metadata.Name}] IS MODIFIED [{Navigation.IsModified}]");

				if ((Navigation.CurrentValue is IEnumerable)==true)
				{
					IEnumerable									TypedValue=(IEnumerable) Navigation.CurrentValue;
					int											Count=0;

					foreach(object Value in TypedValue)
					{
						++Count;
					}

					SB.Append($" CURRENT LENGTH [{Count}]");
				}

				SB.Append(".");

				if (Navigation.IsModified==false)
				{
					CConsoleHelpers.WriteLine(SB.ToString(),ConsoleColor.Magenta);
				}
				else
				{
					CConsoleHelpers.WriteLine(SB.ToString(),ConsoleColor.Blue);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestTrackingChangesProxies()
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

						CEntityOneToManyTrackingChangesProxiesPrincipal[]	Entities1=Context.EntitiesOneToManyTrackingChangesProxiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesProxiesPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesProxiesDependent[]	Entities2=Context.EntitiesOneToManyTrackingChangesProxiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesProxiesDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						// !!!!! PROXIES sa MUSIA vytvarat pomocou METHOD [TEntity DbContext.CreateProxy<TEntity>(params object[] ConstructorArguments)].
						CEntityOneToManyTrackingChangesProxiesDependent	DependentEntity1=Context.CreateProxy<CEntityOneToManyTrackingChangesProxiesDependent>(555,"NEW DEPENDENT 555");
						CEntityOneToManyTrackingChangesProxiesDependent	DependentEntity2=Context.CreateProxy<CEntityOneToManyTrackingChangesProxiesDependent>(666,"NEW DEPENDENT 666");

						// !!!!! PROXIES sa MUSIA vytvarat pomocou METHOD [TEntity DbContext.CreateProxy<TEntity>(params object[] ConstructorArguments)].
						CEntityOneToManyTrackingChangesProxiesPrincipal	PrincipalEntity=Context.CreateProxy<CEntityOneToManyTrackingChangesProxiesPrincipal>(333,"NEW PRINCIPAL 333",new ObservableCollection<CEntityOneToManyTrackingChangesProxiesDependent>(new CEntityOneToManyTrackingChangesProxiesDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyTrackingChangesProxiesPrincipal.Add(PrincipalEntity);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

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

							PrintEntityState(Context,PrincipalEntity);
							PrintEntityState(Context,DependentEntity1);
							PrintEntityState(Context,DependentEntity2);

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

						CEntityOneToManyTrackingChangesProxiesPrincipal[]	Entities1=Context.EntitiesOneToManyTrackingChangesProxiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesProxiesPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesProxiesDependent[]	Entities2=Context.EntitiesOneToManyTrackingChangesProxiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesProxiesDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesProxiesPrincipal				ExistingPrincipalEntity=Context.EntitiesOneToManyTrackingChangesProxiesPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyTrackingChangesProxiesDependent				ExistingDependentEntity1=ExistingPrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyTrackingChangesProxiesDependent				ExistingDependentEntity2=ExistingPrincipalEntity.EntitiesDependent[1];

						// !!!!! PROXIES sa MUSIA vytvarat pomocou METHOD [TEntity DbContext.CreateProxy<TEntity>(params object[] ConstructorArguments)].
						CEntityOneToManyTrackingChangesProxiesDependent				NewDependentEntity=Context.CreateProxy<CEntityOneToManyTrackingChangesProxiesDependent>(777,"NEW DEPENDENT 777");

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity);
						PrintEntityState(Context,ExistingDependentEntity1);
						PrintEntityState(Context,ExistingDependentEntity2);
						PrintEntityState(Context,NewDependentEntity);

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

						PrintEntityState(Context,ExistingPrincipalEntity);
						PrintEntityState(Context,ExistingDependentEntity1);
						PrintEntityState(Context,ExistingDependentEntity2);
						PrintEntityState(Context,NewDependentEntity);

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

							PrintEntityState(Context,ExistingPrincipalEntity);
							PrintEntityState(Context,ExistingDependentEntity1);
							PrintEntityState(Context,ExistingDependentEntity2);
							PrintEntityState(Context,NewDependentEntity);
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

						CEntityOneToManyTrackingChangesProxiesPrincipal[]				Entities1=Context.EntitiesOneToManyTrackingChangesProxiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesProxiesPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesProxiesDependent[]				Entities2=Context.EntitiesOneToManyTrackingChangesProxiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesProxiesDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesProxiesPrincipal	PrincipalEntity=Context.EntitiesOneToManyTrackingChangesProxiesPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyTrackingChangesProxiesDependent	DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyTrackingChangesProxiesDependent	DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyTrackingChangesProxiesPrincipal.Remove(PrincipalEntity);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntity);
							PrintEntityState(Context,DependentEntity1);
							PrintEntityState(Context,DependentEntity2);

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
						CConsoleHelpers.WriteLine("AFTER DELETE ENTITIES:",ConsoleColor.Cyan);

						CEntityOneToManyTrackingChangesProxiesPrincipal[]				Entities1=Context.EntitiesOneToManyTrackingChangesProxiesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesProxiesPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesProxiesDependent[]				Entities2=Context.EntitiesOneToManyTrackingChangesProxiesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesProxiesDependent.PrintToConsole(Entities2);
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
			TestTrackingChangesProxies();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------