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
//----------------------------------------------------------------------------------------------------------------------
namespace GoingDeeperIntoDbContext
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

			CEntityZeroToManyDependent							EntityZeroToManyDependent11=new CEntityZeroToManyDependent(111,"DEPENDENT 111");
			CEntityZeroToManyDependent							EntityZeroToManyDependent12=new CEntityZeroToManyDependent(222,"DEPENDENT 222");
			CEntityZeroToManyDependent							EntityZeroToManyDependent21=new CEntityZeroToManyDependent(333,"DEPENDENT 333");
			CEntityZeroToManyDependent							EntityZeroToManyDependent22=new CEntityZeroToManyDependent(444,"DEPENDENT 444");

			CEntityZeroToManyPrincipal							EntityZeroToManyPrincipal1=new CEntityZeroToManyPrincipal(111,"PRINCIPAL 111",new List<CEntityZeroToManyDependent>(new CEntityZeroToManyDependent[]{EntityZeroToManyDependent11,EntityZeroToManyDependent12}));
			CEntityZeroToManyPrincipal							EntityZeroToManyPrincipal2=new CEntityZeroToManyPrincipal(222,"PRINCIPAL 222",new List<CEntityZeroToManyDependent>(new CEntityZeroToManyDependent[]{EntityZeroToManyDependent21,EntityZeroToManyDependent22}));

			Context.EntitiesZeroToManyPrincipal.Add(EntityZeroToManyPrincipal1);
			Context.EntitiesZeroToManyPrincipal.Add(EntityZeroToManyPrincipal2);

			CEntityOneToManyTrackingChangesSnapshotDependent	EntityOneToManyTrackingChangesSnapshotDependent11=new CEntityOneToManyTrackingChangesSnapshotDependent(111,"DEPENDENT 111");
			CEntityOneToManyTrackingChangesSnapshotDependent	EntityOneToManyTrackingChangesSnapshotDependent12=new CEntityOneToManyTrackingChangesSnapshotDependent(222,"DEPENDENT 222");
			CEntityOneToManyTrackingChangesSnapshotDependent	EntityOneToManyTrackingChangesSnapshotDependent21=new CEntityOneToManyTrackingChangesSnapshotDependent(333,"DEPENDENT 333");
			CEntityOneToManyTrackingChangesSnapshotDependent	EntityOneToManyTrackingChangesSnapshotDependent22=new CEntityOneToManyTrackingChangesSnapshotDependent(444,"DEPENDENT 444");

			CEntityOneToManyTrackingChangesSnapshotPrincipal	EntityOneToManyTrackingChangesSnapshotPrincipal1=new CEntityOneToManyTrackingChangesSnapshotPrincipal(111,"PRINCIPAL 111",new List<CEntityOneToManyTrackingChangesSnapshotDependent>(new CEntityOneToManyTrackingChangesSnapshotDependent[]{EntityOneToManyTrackingChangesSnapshotDependent11,EntityOneToManyTrackingChangesSnapshotDependent12}));
			CEntityOneToManyTrackingChangesSnapshotPrincipal	EntityOneToManyTrackingChangesSnapshotPrincipal2=new CEntityOneToManyTrackingChangesSnapshotPrincipal(222,"PRINCIPAL 222",new List<CEntityOneToManyTrackingChangesSnapshotDependent>(new CEntityOneToManyTrackingChangesSnapshotDependent[]{EntityOneToManyTrackingChangesSnapshotDependent21,EntityOneToManyTrackingChangesSnapshotDependent22}));

			Context.EntitiesOneToManyTrackingChangesSnapshotPrincipal.Add(EntityOneToManyTrackingChangesSnapshotPrincipal1);
			Context.EntitiesOneToManyTrackingChangesSnapshotPrincipal.Add(EntityOneToManyTrackingChangesSnapshotPrincipal2);

			CEntityOneToManyTrackingChangesChangedNotificationsDependent	EntityOneToManyTrackingChangesChangedNotificationsDependent11=new CEntityOneToManyTrackingChangesChangedNotificationsDependent(111,"DEPENDENT 111");
			CEntityOneToManyTrackingChangesChangedNotificationsDependent	EntityOneToManyTrackingChangesChangedNotificationsDependent12=new CEntityOneToManyTrackingChangesChangedNotificationsDependent(222,"DEPENDENT 222");
			CEntityOneToManyTrackingChangesChangedNotificationsDependent	EntityOneToManyTrackingChangesChangedNotificationsDependent21=new CEntityOneToManyTrackingChangesChangedNotificationsDependent(333,"DEPENDENT 333");
			CEntityOneToManyTrackingChangesChangedNotificationsDependent	EntityOneToManyTrackingChangesChangedNotificationsDependent22=new CEntityOneToManyTrackingChangesChangedNotificationsDependent(444,"DEPENDENT 444");

			CEntityOneToManyTrackingChangesChangedNotificationsPrincipal	EntityOneToManyTrackingChangesChangedNotificationsPrincipal1=new CEntityOneToManyTrackingChangesChangedNotificationsPrincipal(111,"PRINCIPAL 111",new ObservableCollection<CEntityOneToManyTrackingChangesChangedNotificationsDependent>(new CEntityOneToManyTrackingChangesChangedNotificationsDependent[]{EntityOneToManyTrackingChangesChangedNotificationsDependent11,EntityOneToManyTrackingChangesChangedNotificationsDependent12}));
			CEntityOneToManyTrackingChangesChangedNotificationsPrincipal	EntityOneToManyTrackingChangesChangedNotificationsPrincipal2=new CEntityOneToManyTrackingChangesChangedNotificationsPrincipal(222,"PRINCIPAL 222",new ObservableCollection<CEntityOneToManyTrackingChangesChangedNotificationsDependent>(new CEntityOneToManyTrackingChangesChangedNotificationsDependent[]{EntityOneToManyTrackingChangesChangedNotificationsDependent21,EntityOneToManyTrackingChangesChangedNotificationsDependent22}));

			Context.EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal.Add(EntityOneToManyTrackingChangesChangedNotificationsPrincipal1);
			Context.EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal.Add(EntityOneToManyTrackingChangesChangedNotificationsPrincipal2);

			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent	EntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent11=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent(111,"DEPENDENT 111");
			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent	EntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent12=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent(222,"DEPENDENT 222");
			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent	EntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent21=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent(333,"DEPENDENT 333");
			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent	EntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent22=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent(444,"DEPENDENT 444");

			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal	EntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal1=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal(111,"PRINCIPAL 111",new ObservableCollection<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>(new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent[]{EntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent11,EntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent12}));
			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal	EntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal2=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal(222,"PRINCIPAL 222",new ObservableCollection<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>(new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent[]{EntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent21,EntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent22}));

			Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.Add(EntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal1);
			Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.Add(EntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal2);

			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent	EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent11=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent(111,"DEPENDENT 111");
			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent	EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent12=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent(222,"DEPENDENT 222");
			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent	EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent21=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent(333,"DEPENDENT 333");
			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent	EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent22=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent(444,"DEPENDENT 444");

			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal	EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal1=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal(111,"PRINCIPAL 111",new ObservableCollection<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent>(new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent[]{EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent11,EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent12}));
			CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal	EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal2=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal(222,"PRINCIPAL 222",new ObservableCollection<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent>(new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent[]{EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent21,EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent22}));

			Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.Add(EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal1);
			Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.Add(EntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal2);

			CEntityToSqlQueryBackendData						EntityToSqlQueryBackendData1=new CEntityToSqlQueryBackendData(111,"STRING 111",111.111);
			CEntityToSqlQueryBackendData						EntityToSqlQueryBackendData2=new CEntityToSqlQueryBackendData(222,"STRING 222",222.222);
			CEntityToSqlQueryBackendData						EntityToSqlQueryBackendData3=new CEntityToSqlQueryBackendData(333,"STRING 333",333.333);
			CEntityToSqlQueryBackendData						EntityToSqlQueryBackendData4=new CEntityToSqlQueryBackendData(444,"STRING 444",444.444);

			Context.EntitiesToSqlQueryBackendData.Add(EntityToSqlQueryBackendData1);
			Context.EntitiesToSqlQueryBackendData.Add(EntityToSqlQueryBackendData2);
			Context.EntitiesToSqlQueryBackendData.Add(EntityToSqlQueryBackendData3);
			Context.EntitiesToSqlQueryBackendData.Add(EntityToSqlQueryBackendData4);
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
		private static ConsoleColor GetColorForState(EntityState State)
		{
			if (State==EntityState.Detached)
			{
				return(ConsoleColor.White);
			}
			else if (State==EntityState.Unchanged)
			{
				return(ConsoleColor.DarkGray);
			}
			else if (State==EntityState.Added)
			{
				return(ConsoleColor.Cyan);
			}
			else if (State==EntityState.Modified)
			{
				return(ConsoleColor.Blue);
			}
			else if (State==EntityState.Deleted)
			{
				return(ConsoleColor.Red);
			}
			else
			{
				throw(new InvalidOperationException($"UNSUPPORTED VALUE [{State}]."));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void PrintEntityState<TEntity>(CDBContext Context, TEntity Enitity, [CallerArgumentExpression(nameof(Enitity))] string EntityName=null) where TEntity : class
		{
			Context.ChangeTracker.DetectChanges();

			CConsoleHelpers.WriteLineSeparator();

			EntityEntry<TEntity>								EntityEntry=Context.Entry<TEntity>(Enitity);
			ConsoleColor										Color=GetColorForState(EntityEntry.State);

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
		private static void TestOneToManyAddUpdateDelete()
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

						CEntityOneToManyDependent				DependentEntity1=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity2=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyPrincipal				PrincipalEntity=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity);

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

						CEntityOneToManyPrincipal				ExistingPrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				ExistingDependentEntity1=ExistingPrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity.EntitiesDependent[1];
						CEntityOneToManyDependent				NewDependentEntity=new CEntityOneToManyDependent(777,"NEW DEPENDENT 777");

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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyDependent.Remove(DependentEntity1);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

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

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity);

						Context.EntitiesOneToManyPrincipal.Remove(PrincipalEntity);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntity);
							PrintEntityState(Context,DependentEntity);

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
		private static void TestOneToManyMoveDependentEntityByChangingNavigationProperty()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID1=0;
			int													PrincipalID2=0;

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

						CEntityOneToManyDependent				DependentEntity11=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity12=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");
						CEntityOneToManyDependent				DependentEntity21=new CEntityOneToManyDependent(777,"NEW DEPENDENT 777");
						CEntityOneToManyDependent				DependentEntity22=new CEntityOneToManyDependent(888,"NEW DEPENDENT 888");

						CEntityOneToManyPrincipal				PrincipalEntity1=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity11,DependentEntity12}));
						CEntityOneToManyPrincipal				PrincipalEntity2=new CEntityOneToManyPrincipal(444,"NEW PRINCIPAL 444",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity21,DependentEntity22}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity1);
						PrintEntityState(Context,PrincipalEntity2);
						PrintEntityState(Context,DependentEntity11);
						PrintEntityState(Context,DependentEntity12);
						PrintEntityState(Context,DependentEntity21);
						PrintEntityState(Context,DependentEntity22);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity1);
						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity2);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity1);
						PrintEntityState(Context,PrincipalEntity2);
						PrintEntityState(Context,DependentEntity11);
						PrintEntityState(Context,DependentEntity12);
						PrintEntityState(Context,DependentEntity21);
						PrintEntityState(Context,DependentEntity22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID1=PrincipalEntity1.EntityPrincipalID;
							PrincipalID2=PrincipalEntity2.EntityPrincipalID;

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntity1);
							PrintEntityState(Context,PrincipalEntity2);
							PrintEntityState(Context,DependentEntity11);
							PrintEntityState(Context,DependentEntity12);
							PrintEntityState(Context,DependentEntity21);
							PrintEntityState(Context,DependentEntity22);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity1.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity2.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity11.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity12.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity21.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity22.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityOneToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityOneToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityOneToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[1];
						CEntityOneToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityOneToManyDependent				ExistingDependentEntity21=ExistingPrincipalEntity2.EntitiesDependent[0];
						CEntityOneToManyDependent				ExistingDependentEntity22=ExistingPrincipalEntity2.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity22)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity21);
						PrintEntityState(Context,ExistingDependentEntity22);

						// !!! Do PRINCIPAL ENTITY 'ExistingPrincipalEntity1' sa prida DEPENDENT ENTITY 'ExistingDependentEntity21' tak, ze sa na DEPENDENT ENTITY 'ExistingDependentEntity21' nastavi NAVIGATION PROPERTY z VALUE 'ExistingPrincipalEntity2' na VALUE 'ExistingPrincipalEntity1'.
						ExistingDependentEntity21.EntityPrincipal=ExistingPrincipalEntity1;

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] MODIFIED NAVIGATION PROPERTY [{nameof(ExistingDependentEntity21.EntityPrincipal)}] by SETTING to VALUE [{nameof(ExistingPrincipalEntity1)}].",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity21);
						PrintEntityState(Context,ExistingDependentEntity22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity22)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity21);
							PrintEntityState(Context,ExistingDependentEntity22);
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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityOneToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityOneToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[1];
						CEntityOneToManyDependent				ExistingDependentEntity13=ExistingPrincipalEntity1.EntitiesDependent[2];
						CEntityOneToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityOneToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity2.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity13)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity13);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity2);

						Context.EntitiesOneToManyDependent.Remove(ExistingDependentEntity11);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity13);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity13)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingDependentEntity13);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity2);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{ExistingDependentEntity11.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL ENTITIES:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityOneToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityOneToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityOneToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityOneToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity2.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity2);

						Context.EntitiesOneToManyPrincipal.Remove(ExistingPrincipalEntity1);
						Context.EntitiesOneToManyPrincipal.Remove(ExistingPrincipalEntity2);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							CConsoleHelpers.WriteLine("ENTITIES SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingDependentEntity2);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity1.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity2.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL ENTITIES:",ConsoleColor.Cyan);

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
		private static void TestOneToManyMoveDependentEntityByChangingForeignKeyProperty()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID1=0;
			int													PrincipalID2=0;

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

						CEntityOneToManyDependent				DependentEntity11=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity12=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");
						CEntityOneToManyDependent				DependentEntity21=new CEntityOneToManyDependent(777,"NEW DEPENDENT 777");
						CEntityOneToManyDependent				DependentEntity22=new CEntityOneToManyDependent(888,"NEW DEPENDENT 888");

						CEntityOneToManyPrincipal				PrincipalEntity1=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity11,DependentEntity12}));
						CEntityOneToManyPrincipal				PrincipalEntity2=new CEntityOneToManyPrincipal(444,"NEW PRINCIPAL 444",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity21,DependentEntity22}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity1);
						PrintEntityState(Context,PrincipalEntity2);
						PrintEntityState(Context,DependentEntity11);
						PrintEntityState(Context,DependentEntity12);
						PrintEntityState(Context,DependentEntity21);
						PrintEntityState(Context,DependentEntity22);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity1);
						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity2);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity1);
						PrintEntityState(Context,PrincipalEntity2);
						PrintEntityState(Context,DependentEntity11);
						PrintEntityState(Context,DependentEntity12);
						PrintEntityState(Context,DependentEntity21);
						PrintEntityState(Context,DependentEntity22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID1=PrincipalEntity1.EntityPrincipalID;
							PrincipalID2=PrincipalEntity2.EntityPrincipalID;

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntity1);
							PrintEntityState(Context,PrincipalEntity2);
							PrintEntityState(Context,DependentEntity11);
							PrintEntityState(Context,DependentEntity12);
							PrintEntityState(Context,DependentEntity21);
							PrintEntityState(Context,DependentEntity22);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity1.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity2.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity11.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity12.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity21.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity22.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityOneToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityOneToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityOneToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[1];
						CEntityOneToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityOneToManyDependent				ExistingDependentEntity21=ExistingPrincipalEntity2.EntitiesDependent[0];
						CEntityOneToManyDependent				ExistingDependentEntity22=ExistingPrincipalEntity2.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity22)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity21);
						PrintEntityState(Context,ExistingDependentEntity22);

						// !!! Do PRINCIPAL ENTITY 'ExistingPrincipalEntity1' sa prida DEPENDENT ENTITY 'ExistingDependentEntity21' tak, ze sa na DEPENDENT ENTITY 'ExistingDependentEntity21' zmeni FOREIGN KEY, aby odkazoval na PRINCIPAL ENTITY 'ExistingPrincipalEntity1'.
						ExistingDependentEntity21.EntityPrincipalID=ExistingPrincipalEntity1.EntityPrincipalID;

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] MODIFIED FOREIGN KEY PROPERTY [{nameof(ExistingDependentEntity21.EntityPrincipalID)}] by SETTING to FOREIGN KEY of ENTITY [{nameof(ExistingPrincipalEntity1)}].",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity21);
						PrintEntityState(Context,ExistingDependentEntity22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity22)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity21);
							PrintEntityState(Context,ExistingDependentEntity22);
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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityOneToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityOneToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[1];
						CEntityOneToManyDependent				ExistingDependentEntity13=ExistingPrincipalEntity1.EntitiesDependent[2];
						CEntityOneToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityOneToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity2.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity13)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity13);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity2);

						Context.EntitiesOneToManyDependent.Remove(ExistingDependentEntity11);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity13);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity13)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingDependentEntity13);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity2);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{ExistingDependentEntity11.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL ENTITIES:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityOneToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityOneToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityOneToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityOneToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity2.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity2);

						Context.EntitiesOneToManyPrincipal.Remove(ExistingPrincipalEntity1);
						Context.EntitiesOneToManyPrincipal.Remove(ExistingPrincipalEntity2);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingDependentEntity2);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity1.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity2.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL ENTITIES:",ConsoleColor.Cyan);

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
		private static void TestZeroToManyAddUpdateDelete()
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

						CEntityZeroToManyDependent				DependentEntity1=new CEntityZeroToManyDependent(555,"NEW DEPENDENT 555");
						CEntityZeroToManyDependent				DependentEntity2=new CEntityZeroToManyDependent(666,"NEW DEPENDENT 666");

						CEntityZeroToManyPrincipal				PrincipalEntity=new CEntityZeroToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityZeroToManyDependent>(new CEntityZeroToManyDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesZeroToManyPrincipal.Add(PrincipalEntity);

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
							DependentID1=DependentEntity2.EntityDependentID;

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
						CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipal				ExistingPrincipalEntity=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityZeroToManyDependent				ExistingDependentEntity1=ExistingPrincipalEntity.EntitiesDependent[0];
						CEntityZeroToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity.EntitiesDependent[1];
						CEntityZeroToManyDependent				NewDependentEntity=new CEntityZeroToManyDependent(777,"NEW DEPENDENT 777");

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
							DependentID2=NewDependentEntity.EntityDependentID;

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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY 1:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipal				PrincipalEntity=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityZeroToManyDependent				DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityZeroToManyDependent				DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesZeroToManyDependent.Remove(DependentEntity1);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

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
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT ENTITY 1:",ConsoleColor.Cyan);

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

						CEntityZeroToManyPrincipal				PrincipalEntity=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityZeroToManyDependent				DependentEntity=PrincipalEntity.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity);

						Context.EntitiesZeroToManyPrincipal.Remove(PrincipalEntity);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntity);
							PrintEntityState(Context,DependentEntity);

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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY 2:",ConsoleColor.Cyan);

						CEntityZeroToManyDependent				DependentEntity1=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityZeroToManyDependent				DependentEntity2=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesZeroToManyDependent.Remove(DependentEntity1);
						Context.EntitiesZeroToManyDependent.Remove(DependentEntity2);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,DependentEntity1);
							PrintEntityState(Context,DependentEntity2);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT ENTITY 2:",ConsoleColor.Cyan);

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
		private static void TestZeroToManyMoveDependentEntityByChangingNavigationProperty()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID1=0;
			int													PrincipalID2=0;
			int													DependentID1=0;
			int													DependentID2=0;
			int													DependentID3=0;

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

						CEntityZeroToManyDependent				DependentEntity11=new CEntityZeroToManyDependent(555,"NEW DEPENDENT 555");
						CEntityZeroToManyDependent				DependentEntity12=new CEntityZeroToManyDependent(666,"NEW DEPENDENT 666");
						CEntityZeroToManyDependent				DependentEntity21=new CEntityZeroToManyDependent(777,"NEW DEPENDENT 777");
						CEntityZeroToManyDependent				DependentEntity22=new CEntityZeroToManyDependent(888,"NEW DEPENDENT 888");

						CEntityZeroToManyPrincipal				PrincipalEntity1=new CEntityZeroToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityZeroToManyDependent>(new CEntityZeroToManyDependent[]{DependentEntity11,DependentEntity12}));
						CEntityZeroToManyPrincipal				PrincipalEntity2=new CEntityZeroToManyPrincipal(444,"NEW PRINCIPAL 444",new List<CEntityZeroToManyDependent>(new CEntityZeroToManyDependent[]{DependentEntity21,DependentEntity22}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity1);
						PrintEntityState(Context,PrincipalEntity2);
						PrintEntityState(Context,DependentEntity11);
						PrintEntityState(Context,DependentEntity12);
						PrintEntityState(Context,DependentEntity21);
						PrintEntityState(Context,DependentEntity22);

						Context.EntitiesZeroToManyPrincipal.Add(PrincipalEntity1);
						Context.EntitiesZeroToManyPrincipal.Add(PrincipalEntity2);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity1);
						PrintEntityState(Context,PrincipalEntity2);
						PrintEntityState(Context,DependentEntity11);
						PrintEntityState(Context,DependentEntity12);
						PrintEntityState(Context,DependentEntity21);
						PrintEntityState(Context,DependentEntity22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID1=PrincipalEntity1.EntityPrincipalID;
							PrincipalID2=PrincipalEntity2.EntityPrincipalID;
							DependentID1=DependentEntity12.EntityDependentID;
							DependentID2=DependentEntity21.EntityDependentID;
							DependentID3=DependentEntity22.EntityDependentID;

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntity1);
							PrintEntityState(Context,PrincipalEntity2);
							PrintEntityState(Context,DependentEntity11);
							PrintEntityState(Context,DependentEntity12);
							PrintEntityState(Context,DependentEntity21);
							PrintEntityState(Context,DependentEntity22);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity1.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity2.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity11.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity12.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity21.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity22.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityZeroToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityZeroToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[1];
						CEntityZeroToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityZeroToManyDependent				ExistingDependentEntity21=ExistingPrincipalEntity2.EntitiesDependent[0];
						CEntityZeroToManyDependent				ExistingDependentEntity22=ExistingPrincipalEntity2.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity22)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity21);
						PrintEntityState(Context,ExistingDependentEntity22);

						// !!! Do PRINCIPAL ENTITY 'ExistingPrincipalEntity1' sa prida DEPENDENT ENTITY 'ExistingDependentEntity21' tak, ze sa na DEPENDENT ENTITY 'ExistingDependentEntity21' nastavi NAVIGATION PROPERTY z VALUE 'ExistingPrincipalEntity2' na VALUE 'ExistingPrincipalEntity1'.
						ExistingDependentEntity21.EntityPrincipal=ExistingPrincipalEntity1;

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] MODIFIED NAVIGATION PROPERTY [{nameof(ExistingDependentEntity21.EntityPrincipal)}] by SETTING to VALUE [{nameof(ExistingPrincipalEntity1)}].",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity21);
						PrintEntityState(Context,ExistingDependentEntity22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity22)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity21);
							PrintEntityState(Context,ExistingDependentEntity22);
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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY 1:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityZeroToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityZeroToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[1];
						CEntityZeroToManyDependent				ExistingDependentEntity13=ExistingPrincipalEntity1.EntitiesDependent[2];
						CEntityZeroToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityZeroToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity2.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity13)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity13);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity2);

						Context.EntitiesZeroToManyDependent.Remove(ExistingDependentEntity11);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity13);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity13)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingDependentEntity13);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity2);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{ExistingDependentEntity11.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT ENTITY 1:",ConsoleColor.Cyan);

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
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL ENTITIES:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityZeroToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityZeroToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityZeroToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityZeroToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity2.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity2);

						Context.EntitiesZeroToManyPrincipal.Remove(ExistingPrincipalEntity1);
						Context.EntitiesZeroToManyPrincipal.Remove(ExistingPrincipalEntity2);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingDependentEntity2);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity1.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity2.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL ENTITIES:",ConsoleColor.Cyan);

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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY 2:",ConsoleColor.Cyan);

						CEntityZeroToManyDependent				DependentEntity1=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityZeroToManyDependent				DependentEntity2=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();
						CEntityZeroToManyDependent				DependentEntity3=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID3).First();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity3)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);
						PrintEntityState(Context,DependentEntity3);

						Context.EntitiesZeroToManyDependent.Remove(DependentEntity1);
						Context.EntitiesZeroToManyDependent.Remove(DependentEntity2);
						Context.EntitiesZeroToManyDependent.Remove(DependentEntity3);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity3)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);
						PrintEntityState(Context,DependentEntity3);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity3)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,DependentEntity1);
							PrintEntityState(Context,DependentEntity2);
							PrintEntityState(Context,DependentEntity3);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity3.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT ENTITY 2:",ConsoleColor.Cyan);

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
		private static void TestZeroToManyMoveDependentEntityByChangingForeignKeyProperty()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID1=0;
			int													PrincipalID2=0;
			int													DependentID1=0;
			int													DependentID2=0;
			int													DependentID3=0;

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

						CEntityZeroToManyDependent				DependentEntity11=new CEntityZeroToManyDependent(555,"NEW DEPENDENT 555");
						CEntityZeroToManyDependent				DependentEntity12=new CEntityZeroToManyDependent(666,"NEW DEPENDENT 666");
						CEntityZeroToManyDependent				DependentEntity21=new CEntityZeroToManyDependent(777,"NEW DEPENDENT 777");
						CEntityZeroToManyDependent				DependentEntity22=new CEntityZeroToManyDependent(888,"NEW DEPENDENT 888");

						CEntityZeroToManyPrincipal				PrincipalEntity1=new CEntityZeroToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityZeroToManyDependent>(new CEntityZeroToManyDependent[]{DependentEntity11,DependentEntity12}));
						CEntityZeroToManyPrincipal				PrincipalEntity2=new CEntityZeroToManyPrincipal(444,"NEW PRINCIPAL 444",new List<CEntityZeroToManyDependent>(new CEntityZeroToManyDependent[]{DependentEntity21,DependentEntity22}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity1);
						PrintEntityState(Context,PrincipalEntity2);
						PrintEntityState(Context,DependentEntity11);
						PrintEntityState(Context,DependentEntity12);
						PrintEntityState(Context,DependentEntity21);
						PrintEntityState(Context,DependentEntity22);

						Context.EntitiesZeroToManyPrincipal.Add(PrincipalEntity1);
						Context.EntitiesZeroToManyPrincipal.Add(PrincipalEntity2);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity1);
						PrintEntityState(Context,PrincipalEntity2);
						PrintEntityState(Context,DependentEntity11);
						PrintEntityState(Context,DependentEntity12);
						PrintEntityState(Context,DependentEntity21);
						PrintEntityState(Context,DependentEntity22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID1=PrincipalEntity1.EntityPrincipalID;
							PrincipalID2=PrincipalEntity2.EntityPrincipalID;
							DependentID1=DependentEntity12.EntityDependentID;
							DependentID2=DependentEntity21.EntityDependentID;
							DependentID3=DependentEntity22.EntityDependentID;

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity21)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity22)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntity1);
							PrintEntityState(Context,PrincipalEntity2);
							PrintEntityState(Context,DependentEntity11);
							PrintEntityState(Context,DependentEntity12);
							PrintEntityState(Context,DependentEntity21);
							PrintEntityState(Context,DependentEntity22);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity1.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity2.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity11.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity12.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity21.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity22.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityZeroToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityZeroToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[1];
						CEntityZeroToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityZeroToManyDependent				ExistingDependentEntity21=ExistingPrincipalEntity2.EntitiesDependent[0];
						CEntityZeroToManyDependent				ExistingDependentEntity22=ExistingPrincipalEntity2.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity22)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity21);
						PrintEntityState(Context,ExistingDependentEntity22);

						// !!! Do PRINCIPAL ENTITY 'ExistingPrincipalEntity1' sa prida DEPENDENT ENTITY 'ExistingDependentEntity21' tak, ze sa na DEPENDENT ENTITY 'ExistingDependentEntity21' zmeni FOREIGN KEY, aby odkazoval na PRINCIPAL ENTITY 'ExistingPrincipalEntity1'.
						ExistingDependentEntity21.EntityPrincipalID=ExistingPrincipalEntity1.EntityPrincipalID;

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] MODIFIED NAVIGATION PROPERTY [{nameof(ExistingDependentEntity21.EntityPrincipal)}] by SETTING to VALUE [{nameof(ExistingPrincipalEntity1)}].",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity21);
						PrintEntityState(Context,ExistingDependentEntity22);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity21)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity22)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity21);
							PrintEntityState(Context,ExistingDependentEntity22);
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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY 1:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityZeroToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityZeroToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[1];
						CEntityZeroToManyDependent				ExistingDependentEntity13=ExistingPrincipalEntity1.EntitiesDependent[2];
						CEntityZeroToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityZeroToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity2.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity13)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity13);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity2);

						Context.EntitiesZeroToManyDependent.Remove(ExistingDependentEntity11);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity13);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity13)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingDependentEntity13);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity2);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{ExistingDependentEntity11.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT ENTITY 1:",ConsoleColor.Cyan);

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
						CConsoleHelpers.WriteLine("DELETING PRINCIPAL ENTITIES:",ConsoleColor.Cyan);

						CEntityZeroToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityZeroToManyDependent				ExistingDependentEntity11=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityZeroToManyDependent				ExistingDependentEntity12=ExistingPrincipalEntity1.EntitiesDependent[0];
						CEntityZeroToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesZeroToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();
						CEntityZeroToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity2.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity2);

						Context.EntitiesZeroToManyPrincipal.Remove(ExistingPrincipalEntity1);
						Context.EntitiesZeroToManyPrincipal.Remove(ExistingPrincipalEntity2);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,ExistingPrincipalEntity1);
						PrintEntityState(Context,ExistingPrincipalEntity2);
						PrintEntityState(Context,ExistingDependentEntity11);
						PrintEntityState(Context,ExistingDependentEntity12);
						PrintEntityState(Context,ExistingDependentEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(ExistingPrincipalEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity11)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity12)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(ExistingDependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,ExistingPrincipalEntity1);
							PrintEntityState(Context,ExistingPrincipalEntity2);
							PrintEntityState(Context,ExistingDependentEntity11);
							PrintEntityState(Context,ExistingDependentEntity12);
							PrintEntityState(Context,ExistingDependentEntity2);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity1.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity2.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL ENTITIES:",ConsoleColor.Cyan);

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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY 2:",ConsoleColor.Cyan);

						CEntityZeroToManyDependent				DependentEntity1=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID1).First();
						CEntityZeroToManyDependent				DependentEntity2=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID2).First();
						CEntityZeroToManyDependent				DependentEntity3=Context.EntitiesZeroToManyDependent.Include(P => P.EntityPrincipal).Where(P => P.EntityDependentID==DependentID3).First();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity3)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);
						PrintEntityState(Context,DependentEntity3);

						Context.EntitiesZeroToManyDependent.Remove(DependentEntity1);
						Context.EntitiesZeroToManyDependent.Remove(DependentEntity2);
						Context.EntitiesZeroToManyDependent.Remove(DependentEntity3);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity3)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);
						PrintEntityState(Context,DependentEntity3);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity3)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,DependentEntity1);
							PrintEntityState(Context,DependentEntity2);
							PrintEntityState(Context,DependentEntity3);

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity1.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity2.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity3.EntityDependentID}] was DELETED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("AFTER DELETE DEPENDENT ENTITY 2:",ConsoleColor.Cyan);

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
		private static void TestUpdateMethod()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			CEntityOneToManyPrincipal							PrincipalEntityToUpdate=null;
			CEntityOneToManyDependent							DependentEntity1ToUpdate=null;
			CEntityOneToManyDependent							DependentEntity2ToUpdate=null;

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

						CEntityOneToManyDependent				DependentEntity1=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity2=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyPrincipal				PrincipalEntity=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity);

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
							PrincipalEntityToUpdate=PrincipalEntity;
							DependentEntity1ToUpdate=DependentEntity1;
							DependentEntity2ToUpdate=DependentEntity2;

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

						// !!!!! Vykona sa UPDATE DETACHED ENTITIES.

						// !!! Zmeni sa PROPERTY v PRINCIPAL ENTITY.
						PrincipalEntityToUpdate.EntityPrincipalStringValue+=" MODIFIED !!!!!";

						// !!! Zmeni sa PROPERTY v DEPENDENT ENTITY.
						DependentEntity1ToUpdate.EntityDependentIntValue+=100;

						CEntityOneToManyDependent				NewDependentEntity=new CEntityOneToManyDependent(777,"NEW DEPENDENT 777");

						// !!! Prida sa nova DEPENDENT ENTITY pridanim do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						PrincipalEntityToUpdate.EntitiesDependent.Add(NewDependentEntity);

						// !!! Odstrani sa existujuca DEPENDENT ENTITY odstranenim z NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						// !!!!! Realne tato DEPENDENT ENTITY NEBUDE DELETED z DB, pretoze pri volani METHOD [EntityEntry<TEntity> DbSet<TEntity>Update(TEntity Entity)] tato DEPENDENT ENTITY nebude najdena v COLLECTION PRINCIPAL ENTITY a teda sa nad nou NEVYKONA ZIADNA OPERATION, ani DELETE.
						PrincipalEntityToUpdate.EntitiesDependent.Remove(DependentEntity2ToUpdate);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntityToUpdate);
						PrintEntityState(Context,DependentEntity1ToUpdate);
						PrintEntityState(Context,DependentEntity2ToUpdate);
						PrintEntityState(Context,NewDependentEntity);

						// !!!!! Do DB CONTEXT sa pridaju ENTITIES, ktore boli nacitane v inom DB CONTEXT a nasledne modifikovane.
						Context.EntitiesOneToManyPrincipal.Update(PrincipalEntityToUpdate);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] UPDATED by CALLING METHOD [Update()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] UPDATED by CALLING METHOD [Update()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] UPDATED by CALLING METHOD [Update()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] UPDATED by CALLING METHOD [Update()].",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntityToUpdate);
						PrintEntityState(Context,DependentEntity1ToUpdate);
						PrintEntityState(Context,DependentEntity2ToUpdate);
						PrintEntityState(Context,NewDependentEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntityToUpdate);
							PrintEntityState(Context,DependentEntity1ToUpdate);
							PrintEntityState(Context,DependentEntity2ToUpdate);
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
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				DependentEntity2=PrincipalEntity.EntitiesDependent[1];
						CEntityOneToManyDependent				DependentEntity3=PrincipalEntity.EntitiesDependent[2];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity3)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);
						PrintEntityState(Context,DependentEntity3);

						Context.EntitiesOneToManyPrincipal.Remove(PrincipalEntity);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);
						PrintEntityState(Context,DependentEntity3);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity3)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntity);
							PrintEntityState(Context,DependentEntity1);
							PrintEntityState(Context,DependentEntity2);
							PrintEntityState(Context,DependentEntity3);

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
		private static void TestAttachMethod()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			CEntityOneToManyPrincipal							PrincipalEntityToUpdate=null;
			CEntityOneToManyDependent							DependentEntity1ToUpdate=null;
			CEntityOneToManyDependent							DependentEntity2ToUpdate=null;

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

						CEntityOneToManyDependent				DependentEntity1=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity2=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyPrincipal				PrincipalEntity=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity);

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
							PrincipalEntityToUpdate=PrincipalEntity;
							DependentEntity1ToUpdate=DependentEntity1;
							DependentEntity2ToUpdate=DependentEntity2;

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

						CEntityOneToManyDependent				NewDependentEntity=new CEntityOneToManyDependent(777,"NEW DEPENDENT 777");

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntityToUpdate);
						PrintEntityState(Context,DependentEntity1ToUpdate);
						PrintEntityState(Context,DependentEntity2ToUpdate);
						PrintEntityState(Context,NewDependentEntity);

						// !!!!! Vykona sa ATTACH do DB CONTEXT.
						Context.EntitiesOneToManyPrincipal.Attach(PrincipalEntityToUpdate);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] ADDED to DB CONTEXT by CALLING METHOD [Attach()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] ADDED to DB CONTEXT by CALLING METHOD [Attach()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] ADDED to DB CONTEXT by CALLING METHOD [Attach()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntityToUpdate);
						PrintEntityState(Context,DependentEntity1ToUpdate);
						PrintEntityState(Context,DependentEntity2ToUpdate);
						PrintEntityState(Context,NewDependentEntity);

						// !!! Zmeni sa PROPERTY v PRINCIPAL ENTITY.
						PrincipalEntityToUpdate.EntityPrincipalStringValue+=" MODIFIED !!!!!";

						// !!! Zmeni sa PROPERTY v DEPENDENT ENTITY.
						DependentEntity1ToUpdate.EntityDependentIntValue+=100;

						// !!! Prida sa nova DEPENDENT ENTITY pridanim do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						PrincipalEntityToUpdate.EntitiesDependent.Add(NewDependentEntity);

						// !!! Odstrani sa existujuca DEPENDENT ENTITY odstranenim z NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						PrincipalEntityToUpdate.EntitiesDependent.Remove(DependentEntity2ToUpdate);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] PROPERTY [{nameof(PrincipalEntityToUpdate.EntityPrincipalStringValue)}] MODIFIED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] PROPERTY [{nameof(DependentEntity1ToUpdate.EntityDependentIntValue)}] MODIFIED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] ADDED to PRINCIPAL ENTITY [{PrincipalEntityToUpdate}].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] REMOVED from PRINCIPAL ENTITY [{PrincipalEntityToUpdate}].",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntityToUpdate);
						PrintEntityState(Context,DependentEntity1ToUpdate);
						PrintEntityState(Context,DependentEntity2ToUpdate);
						PrintEntityState(Context,NewDependentEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntityToUpdate);
							PrintEntityState(Context,DependentEntity1ToUpdate);
							PrintEntityState(Context,DependentEntity2ToUpdate);
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
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyPrincipal.Remove(PrincipalEntity);

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
		private static void TestManuallyChangeState()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			CEntityOneToManyPrincipal							PrincipalEntityToUpdate=null;
			CEntityOneToManyDependent							DependentEntity1ToUpdate=null;
			CEntityOneToManyDependent							DependentEntity2ToUpdate=null;

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

						CEntityOneToManyDependent				DependentEntity1=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity2=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyPrincipal				PrincipalEntity=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity);

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
							PrincipalEntityToUpdate=PrincipalEntity;
							DependentEntity1ToUpdate=DependentEntity1;
							DependentEntity2ToUpdate=DependentEntity2;

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

						// !!!!! Vykona sa UPDATE DETACHED ENTITIES.

						// !!! Zmeni sa PROPERTY v PRINCIPAL ENTITY.
						PrincipalEntityToUpdate.EntityPrincipalStringValue+=" MODIFIED !!!!!";

						// !!! Zmeni sa PROPERTY v DEPENDENT ENTITY.
						DependentEntity1ToUpdate.EntityDependentIntValue+=100;

						CEntityOneToManyDependent				NewDependentEntity=new CEntityOneToManyDependent(777,"NEW DEPENDENT 777");

						// !!! Prida sa nova DEPENDENT ENTITY pridanim do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						PrincipalEntityToUpdate.EntitiesDependent.Add(NewDependentEntity);

						// !!! Odstrani sa existujuca DEPENDENT ENTITY odstranenim z NAVIGATION PROPERTY v PRINCIPAL ENTITY.
						PrincipalEntityToUpdate.EntitiesDependent.Remove(DependentEntity2ToUpdate);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntityToUpdate);
						PrintEntityState(Context,DependentEntity1ToUpdate);
						PrintEntityState(Context,DependentEntity2ToUpdate);
						PrintEntityState(Context,NewDependentEntity);

						// !!!!! Do DB CONTEXT sa pridaju ENTITIES, ktore boli nacitane v inom DB CONTEXT a nasledne modifikovane.
						Context.EntitiesOneToManyPrincipal.Attach(PrincipalEntityToUpdate);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] UPDATED by CALLING METHOD [Update()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] UPDATED by CALLING METHOD [Update()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] UPDATED by CALLING METHOD [Update()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] UPDATED by CALLING METHOD [Update()].",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntityToUpdate);
						PrintEntityState(Context,DependentEntity1ToUpdate);
						PrintEntityState(Context,DependentEntity2ToUpdate);
						PrintEntityState(Context,NewDependentEntity);

						EntityEntry<CEntityOneToManyPrincipal>	EntryPrincipalEntityToUpdate=Context.Entry<CEntityOneToManyPrincipal>(PrincipalEntityToUpdate);

						// !!!!! DEPENDENT ENTITY PROPERTY sa nastavi na STATE [Modified].
						EntryPrincipalEntityToUpdate.Property(nameof(PrincipalEntityToUpdate.EntityPrincipalStringValue)).IsModified=true;

						EntityEntry<CEntityOneToManyDependent>	EntryDependentEntity1ToUpdate=Context.Entry<CEntityOneToManyDependent>(DependentEntity1ToUpdate);

						// !!!!! DEPENDENT ENTITY PROPERTY sa nastavi na STATE [Modified].
						EntryDependentEntity1ToUpdate.Property(nameof(DependentEntity1ToUpdate.EntityDependentIntValue)).IsModified=true;

						EntityEntry<CEntityOneToManyDependent>	EntryDependentEntity2ToUpdate=Context.Entry<CEntityOneToManyDependent>(DependentEntity2ToUpdate);

						// !!!!! DEPENDENT ENTITY sa nastavi na STATE [Deleted].
						EntryDependentEntity2ToUpdate.State=EntityState.Deleted;

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] MANUALLY MODIFIED its STATE.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] MANUALLY MODIFIED its STATE.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] MANUALLY MODIFIED its STATE.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] MANUALLY MODIFIED its STATE.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntityToUpdate);
						PrintEntityState(Context,DependentEntity1ToUpdate);
						PrintEntityState(Context,DependentEntity2ToUpdate);
						PrintEntityState(Context,NewDependentEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntityToUpdate);
							PrintEntityState(Context,DependentEntity1ToUpdate);
							PrintEntityState(Context,DependentEntity2ToUpdate);
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
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyPrincipal.Remove(PrincipalEntity);

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
		private static void MyChangeEntityStates(EntityEntryGraphNode GraphNode)
		{
			// !!!!! Ak sa ma ENTITY pridat do DB CONTEXT, tak jej STATE MUSI byt VZDY iny ako STATE [Detached].
			GraphNode.Entry.State=EntityState.Unchanged;

			object												Entity=GraphNode.Entry.Entity;

			if ((Entity is CEntityOneToManyPrincipal)==true)
			{
				CEntityOneToManyPrincipal						PrincipalEntity=(CEntityOneToManyPrincipal) Entity;
				CEntityOneToManyDependent						DependentEntity1=PrincipalEntity.EntitiesDependent[0];

				// !!! Zmeni sa PROPERTY v PRINCIPAL ENTITY.
				PrincipalEntity.EntityPrincipalStringValue+=" MODIFIED !!!!!";

				// !!! Zmeni sa PROPERTY v DEPENDENT ENTITY.
				DependentEntity1.EntityDependentIntValue+=100;

				CEntityOneToManyDependent				NewDependentEntity=new CEntityOneToManyDependent(777,"NEW DEPENDENT 777");

				// !!! Prida sa nova DEPENDENT ENTITY pridanim do NAVIGATION PROPERTY v PRINCIPAL ENTITY.
				PrincipalEntity.EntitiesDependent.Add(NewDependentEntity);
			}
			else if ((Entity is CEntityOneToManyDependent)==true)
			{
				CEntityOneToManyDependent						DependentEntity=(CEntityOneToManyDependent) Entity;
				
				if (DependentEntity.EntityDependentID==0)
				{
					GraphNode.Entry.State=EntityState.Added;
				}
				else
				{
					CEntityOneToManyPrincipal					PrincipalEntity=DependentEntity.EntityPrincipal;
					CEntityOneToManyDependent					DependentEntity2=PrincipalEntity.EntitiesDependent[1];

					if (object.ReferenceEquals(DependentEntity,DependentEntity2)==true)
					{
						// !!! Odstrani sa EXISTUJUCA DEPENDENT ENTITY nastavenim STATE na VALUE [Deleted].
						GraphNode.Entry.State=EntityState.Deleted;
					}
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void TestTrackGraphMethod()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;
			CEntityOneToManyPrincipal							PrincipalEntityToUpdate=null;
			CEntityOneToManyDependent							DependentEntity1ToUpdate=null;
			CEntityOneToManyDependent							DependentEntity2ToUpdate=null;

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

						CEntityOneToManyDependent				DependentEntity1=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity2=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyPrincipal				PrincipalEntity=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity);

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
							PrincipalEntityToUpdate=PrincipalEntity;
							DependentEntity1ToUpdate=DependentEntity1;
							DependentEntity2ToUpdate=DependentEntity2;

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

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] NOT ATTACHED to DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntityToUpdate);
						PrintEntityState(Context,DependentEntity1ToUpdate);
						PrintEntityState(Context,DependentEntity2ToUpdate);

						// !!!!! Vykona sa UPDATE DETACHED ENTITIES pomocou METHOD [void ChangeTracker.TrackGraph(object RootEntity, Action<EntityEntryGraphNode> Callback)].
						Context.ChangeTracker.TrackGraph(PrincipalEntityToUpdate,MyChangeEntityStates);

						CEntityOneToManyDependent				NewDependentEntity=PrincipalEntityToUpdate.EntitiesDependent.Where(P => P.EntityDependentID==0).First();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] AFTER MODIFIED in METHOD [TrackGraph()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] AFTER MODIFIED in METHOD [TrackGraph()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] AFTER MODIFIED in METHOD [TrackGraph()].",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] AFTER MODIFIED in METHOD [TrackGraph()].",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntityToUpdate);
						PrintEntityState(Context,DependentEntity1ToUpdate);
						PrintEntityState(Context,DependentEntity2ToUpdate);
						PrintEntityState(Context,NewDependentEntity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntityToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1ToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2ToUpdate)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(NewDependentEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntityToUpdate);
							PrintEntityState(Context,DependentEntity1ToUpdate);
							PrintEntityState(Context,DependentEntity2ToUpdate);
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
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyPrincipal.Remove(PrincipalEntity);

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
		private static void TestTrackingChangesModeSnapshot()
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

						CEntityOneToManyTrackingChangesSnapshotPrincipal[]	Entities1=Context.EntitiesOneToManyTrackingChangesSnapshotPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesSnapshotPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesSnapshotDependent[]	Entities2=Context.EntitiesOneToManyTrackingChangesSnapshotDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesSnapshotDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesSnapshotDependent	DependentEntity1=new CEntityOneToManyTrackingChangesSnapshotDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyTrackingChangesSnapshotDependent	DependentEntity2=new CEntityOneToManyTrackingChangesSnapshotDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyTrackingChangesSnapshotPrincipal	PrincipalEntity=new CEntityOneToManyTrackingChangesSnapshotPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyTrackingChangesSnapshotDependent>(new CEntityOneToManyTrackingChangesSnapshotDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyTrackingChangesSnapshotPrincipal.Add(PrincipalEntity);

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

						CEntityOneToManyTrackingChangesSnapshotPrincipal[]	Entities1=Context.EntitiesOneToManyTrackingChangesSnapshotPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesSnapshotPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesSnapshotDependent[]	Entities2=Context.EntitiesOneToManyTrackingChangesSnapshotDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesSnapshotDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesSnapshotPrincipal				ExistingPrincipalEntity=Context.EntitiesOneToManyTrackingChangesSnapshotPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyTrackingChangesSnapshotDependent				ExistingDependentEntity1=ExistingPrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyTrackingChangesSnapshotDependent				ExistingDependentEntity2=ExistingPrincipalEntity.EntitiesDependent[1];
						CEntityOneToManyTrackingChangesSnapshotDependent				NewDependentEntity=new CEntityOneToManyTrackingChangesSnapshotDependent(777,"NEW DEPENDENT 777");

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

						CEntityOneToManyTrackingChangesSnapshotPrincipal[]				Entities1=Context.EntitiesOneToManyTrackingChangesSnapshotPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesSnapshotPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesSnapshotDependent[]				Entities2=Context.EntitiesOneToManyTrackingChangesSnapshotDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesSnapshotDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesSnapshotPrincipal	PrincipalEntity=Context.EntitiesOneToManyTrackingChangesSnapshotPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyTrackingChangesSnapshotDependent	DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyTrackingChangesSnapshotDependent	DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyTrackingChangesSnapshotPrincipal.Remove(PrincipalEntity);

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

						CEntityOneToManyTrackingChangesSnapshotPrincipal[]				Entities1=Context.EntitiesOneToManyTrackingChangesSnapshotPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesSnapshotPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesSnapshotDependent[]				Entities2=Context.EntitiesOneToManyTrackingChangesSnapshotDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesSnapshotDependent.PrintToConsole(Entities2);
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
		private static void TestTrackingChangesChangedNotifications()
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

						CEntityOneToManyTrackingChangesChangedNotificationsPrincipal[]	Entities1=Context.EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangedNotificationsPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangedNotificationsDependent[]	Entities2=Context.EntitiesOneToManyTrackingChangesChangedNotificationsDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangedNotificationsDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesChangedNotificationsDependent	DependentEntity1=new CEntityOneToManyTrackingChangesChangedNotificationsDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyTrackingChangesChangedNotificationsDependent	DependentEntity2=new CEntityOneToManyTrackingChangesChangedNotificationsDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyTrackingChangesChangedNotificationsPrincipal	PrincipalEntity=new CEntityOneToManyTrackingChangesChangedNotificationsPrincipal(333,"NEW PRINCIPAL 333",new ObservableCollection<CEntityOneToManyTrackingChangesChangedNotificationsDependent>(new CEntityOneToManyTrackingChangesChangedNotificationsDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal.Add(PrincipalEntity);

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

						CEntityOneToManyTrackingChangesChangedNotificationsPrincipal[]	Entities1=Context.EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangedNotificationsPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangedNotificationsDependent[]	Entities2=Context.EntitiesOneToManyTrackingChangesChangedNotificationsDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangedNotificationsDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesChangedNotificationsPrincipal				ExistingPrincipalEntity=Context.EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyTrackingChangesChangedNotificationsDependent				ExistingDependentEntity1=ExistingPrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyTrackingChangesChangedNotificationsDependent				ExistingDependentEntity2=ExistingPrincipalEntity.EntitiesDependent[1];
						CEntityOneToManyTrackingChangesChangedNotificationsDependent				NewDependentEntity=new CEntityOneToManyTrackingChangesChangedNotificationsDependent(777,"NEW DEPENDENT 777");

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

						CEntityOneToManyTrackingChangesChangedNotificationsPrincipal[]				Entities1=Context.EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangedNotificationsPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangedNotificationsDependent[]				Entities2=Context.EntitiesOneToManyTrackingChangesChangedNotificationsDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangedNotificationsDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesChangedNotificationsPrincipal	PrincipalEntity=Context.EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyTrackingChangesChangedNotificationsDependent	DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyTrackingChangesChangedNotificationsDependent	DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal.Remove(PrincipalEntity);

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

						CEntityOneToManyTrackingChangesChangedNotificationsPrincipal[]				Entities1=Context.EntitiesOneToManyTrackingChangesChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangedNotificationsPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangedNotificationsDependent[]				Entities2=Context.EntitiesOneToManyTrackingChangesChangedNotificationsDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangedNotificationsDependent.PrintToConsole(Entities2);
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
		private static void TestTrackingChangesChangingAndChangedNotifications()
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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal[]	Entities1=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent[]	Entities2=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent	DependentEntity1=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent	DependentEntity2=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal	PrincipalEntity=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal(333,"NEW PRINCIPAL 333",new ObservableCollection<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent>(new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.Add(PrincipalEntity);

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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal[]	Entities1=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent[]	Entities2=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal				ExistingPrincipalEntity=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent				ExistingDependentEntity1=ExistingPrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent				ExistingDependentEntity2=ExistingPrincipalEntity.EntitiesDependent[1];
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent				NewDependentEntity=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent(777,"NEW DEPENDENT 777");

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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal[]				Entities1=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent[]				Entities2=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal	PrincipalEntity=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent	DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent	DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.Remove(PrincipalEntity);

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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal[]				Entities1=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent[]				Entities2=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsDependent.PrintToConsole(Entities2);
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
		private static void TestTrackingChangesChangingAndChangedNotificationsWithOriginalValues()
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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal[]	Entities1=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent[]	Entities2=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent	DependentEntity1=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent	DependentEntity2=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal	PrincipalEntity=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal(333,"NEW PRINCIPAL 333",new ObservableCollection<CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent>(new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.Add(PrincipalEntity);

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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal[]	Entities1=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent[]	Entities2=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal				ExistingPrincipalEntity=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent				ExistingDependentEntity1=ExistingPrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent				ExistingDependentEntity2=ExistingPrincipalEntity.EntitiesDependent[1];
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent				NewDependentEntity=new CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent(777,"NEW DEPENDENT 777");

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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal[]				Entities1=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent[]				Entities2=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent.PrintToConsole(Entities2);
					}
					catch(Exception E)
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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal	PrincipalEntity=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent	DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent	DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.Remove(PrincipalEntity);

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

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal[]				Entities1=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.Include(P => P.EntitiesDependent).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesPrincipal.PrintToConsole(Entities1);

						CConsoleHelpers.WriteLineSeparators(3);

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent[]				Entities2=Context.EntitiesOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent.Include(P => P.EntityPrincipal).ToArray();

						CEntityOneToManyTrackingChangesChangingAndChangedNotificationsWithOriginalValuesDependent.PrintToConsole(Entities2);
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
		private static void PrintStates(CDBContext Context)
		{
			Context.ChangeTracker.DetectChanges();

			// !!!!! METHOD vrati ENTRIES vsetkych ENTITIES, ktorych STATE bol modifikovany.
			EntityEntry<CEntityOneToManyPrincipal>[]			PrincipalEntries=Context.ChangeTracker.Entries<CEntityOneToManyPrincipal>().ToArray();

			foreach(EntityEntry<CEntityOneToManyPrincipal> Entry in PrincipalEntries)
			{
				ConsoleColor									Color=GetColorForState(Entry.State);

				CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY with ID [{Entry.Entity.EntityPrincipalID}] has STATE [{Entry.State}].",Color);
			}

			// !!!!! METHOD vrati ENTRIES vsetkych ENTITIES, ktorych STATE bol modifikovany.
			EntityEntry<CEntityOneToManyDependent>[]			DependentEntries=Context.ChangeTracker.Entries<CEntityOneToManyDependent>().ToArray();

			foreach(EntityEntry<CEntityOneToManyDependent> Entry in DependentEntries)
			{
				ConsoleColor									Color=GetColorForState(Entry.State);

				CConsoleHelpers.WriteLine($"DEPENDENT ENTITY with ID [{Entry.Entity.EntityDependentID}] has STATE [{Entry.State}].",Color);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void TestUseChangeTrackerEntriesMethod()
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

						CEntityOneToManyDependent				DependentEntity1=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity2=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyPrincipal				PrincipalEntity=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] ADDED to DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						CConsoleHelpers.WriteLineSeparator();
						PrintStates(Context);

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

						CEntityOneToManyPrincipal				ExistingPrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				ExistingDependentEntity1=ExistingPrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				ExistingDependentEntity2=ExistingPrincipalEntity.EntitiesDependent[1];
						CEntityOneToManyDependent				NewDependentEntity=new CEntityOneToManyDependent(777,"NEW DEPENDENT 777");

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

						CConsoleHelpers.WriteLineSeparator();
						PrintStates(Context);

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
						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyDependent.Remove(DependentEntity1);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						CConsoleHelpers.WriteLineSeparator();
						PrintStates(Context);

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

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity);

						Context.EntitiesOneToManyPrincipal.Remove(PrincipalEntity);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity);

						CConsoleHelpers.WriteLineSeparator();
						PrintStates(Context);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntity);
							PrintEntityState(Context,DependentEntity);

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
		private static void TrackedEventHandler(object Sender, EntityTrackedEventArgs Arguments)
		{
			ConsoleColor										Color=GetColorForState(Arguments.Entry.State);

			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"EVENT TRACKED CALLED - ENTITY [{Arguments.Entry.Entity.GetType().Name}] STATE [{Arguments.Entry.State}] !",Color);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void StateChangedEventHandler(object Sender, EntityStateChangedEventArgs Arguments)
		{
			ConsoleColor										Color=GetColorForState(Arguments.Entry.State);

			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"EVENT STATE CHANGED CALLED - ENTITY [{Arguments.Entry.Entity.GetType().Name}] STATE [{Arguments.Entry.State}] OLD STATE [{Arguments.OldState}] NEW STATE [{Arguments.NewState}] !",Color);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void TestChangeTrackerEvents()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!!!! Zaregistruje sa odber CHANGE TRACKER EVENTS.
						Context.ChangeTracker.Tracked+=TrackedEventHandler;
						Context.ChangeTracker.StateChanged+=StateChangedEventHandler;

						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

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
						// !!!!! Zaregistruje sa odber CHANGE TRACKER EVENTS.
						Context.ChangeTracker.Tracked+=TrackedEventHandler;
						Context.ChangeTracker.StateChanged+=StateChangedEventHandler;

						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOneToManyDependent				DependentEntity1=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity2=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyPrincipal				PrincipalEntity=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity);

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
						// !!!!! Zaregistruje sa odber CHANGE TRACKER EVENTS.
						Context.ChangeTracker.Tracked+=TrackedEventHandler;
						Context.ChangeTracker.StateChanged+=StateChangedEventHandler;

						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

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
						// !!!!! Zaregistruje sa odber CHANGE TRACKER EVENTS.
						Context.ChangeTracker.Tracked+=TrackedEventHandler;
						Context.ChangeTracker.StateChanged+=StateChangedEventHandler;

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
						// !!!!! Zaregistruje sa odber CHANGE TRACKER EVENTS.
						Context.ChangeTracker.Tracked+=TrackedEventHandler;
						Context.ChangeTracker.StateChanged+=StateChangedEventHandler;

						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

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
						// !!!!! Zaregistruje sa odber CHANGE TRACKER EVENTS.
						Context.ChangeTracker.Tracked+=TrackedEventHandler;
						Context.ChangeTracker.StateChanged+=StateChangedEventHandler;

						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyDependent.Remove(DependentEntity1);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

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
						// !!!!! Zaregistruje sa odber CHANGE TRACKER EVENTS.
						Context.ChangeTracker.Tracked+=TrackedEventHandler;
						Context.ChangeTracker.StateChanged+=StateChangedEventHandler;

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
						// !!!!! Zaregistruje sa odber CHANGE TRACKER EVENTS.
						Context.ChangeTracker.Tracked+=TrackedEventHandler;
						Context.ChangeTracker.StateChanged+=StateChangedEventHandler;

						CConsoleHelpers.WriteLine("DELETING PRINCIPAL ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity=PrincipalEntity.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity);

						Context.EntitiesOneToManyPrincipal.Remove(PrincipalEntity);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntity);
							PrintEntityState(Context,DependentEntity);

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
						// !!!!! Zaregistruje sa odber CHANGE TRACKER EVENTS.
						Context.ChangeTracker.Tracked+=TrackedEventHandler;
						Context.ChangeTracker.StateChanged+=StateChangedEventHandler;

						CConsoleHelpers.WriteLine("AFTER DELETE PRINCIPAL ENTITY:",ConsoleColor.Cyan);

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
		private static void SavingChangesEventHandler(object Sender, SavingChangesEventArgs Arguments)
		{
			// !!! 1. PARAMETER VZDY obsahuje DB CONTEXT.
			CDBContext											Context=(CDBContext) Sender;

			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"EVENT SAVING CHANGES CALLED - DB CONTEXT ID [{Context.ContextId}] ACCEPT ALL CHANGES ON SUCCESS [{Arguments.AcceptAllChangesOnSuccess}] !",ConsoleColor.DarkRed);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void SavedChangesEventHandler(object Sender, SavedChangesEventArgs Arguments)
		{
			// !!! 1. PARAMETER VZDY obsahuje DB CONTEXT.
			CDBContext											Context=(CDBContext) Sender;

			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"EVENT SAVED CHANGES CALLED - DB CONTEXT ID [{Context.ContextId}] ACCEPT ALL CHANGES ON SUCCESS [{Arguments.AcceptAllChangesOnSuccess}] ENTITIES SAVED COUNT [{Arguments.EntitiesSavedCount}] !",ConsoleColor.DarkRed);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void SaveChangesFailedEventHandler(object Sender, SaveChangesFailedEventArgs Arguments)
		{
			// !!! 1. PARAMETER VZDY obsahuje DB CONTEXT.
			CDBContext											Context=(CDBContext) Sender;
			
			CConsoleHelpers.WriteLineSeparator();
			CConsoleHelpers.WriteLine($"EVENT SAVE CHANGES FAILED CALLED - DB CONTEXT ID [{Context.ContextId}] ACCEPT ALL CHANGES ON SUCCESS [{Arguments.AcceptAllChangesOnSuccess}] EXCEPTION [{Arguments.Exception}] !",ConsoleColor.DarkRed);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void TestDbContextEvents()
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
						// !!!!! Zaregistruje sa odber DB CONTEXT EVENTS.
						Context.SavingChanges+=SavingChangesEventHandler;
						Context.SavedChanges+=SavedChangesEventHandler;
						Context.SaveChangesFailed+=SaveChangesFailedEventHandler;

						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityOneToManyDependent				DependentEntity1=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity2=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");

						CEntityOneToManyPrincipal				PrincipalEntity=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity1,DependentEntity2}));

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] CREATED.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] CREATED.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity);

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
						// !!!!! Zaregistruje sa odber DB CONTEXT EVENTS.
						Context.SavingChanges+=SavingChangesEventHandler;
						Context.SavedChanges+=SavedChangesEventHandler;
						Context.SaveChangesFailed+=SaveChangesFailedEventHandler;

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
						// !!!!! Zaregistruje sa odber DB CONTEXT EVENTS.
						Context.SavingChanges+=SavingChangesEventHandler;
						Context.SavedChanges+=SavedChangesEventHandler;
						Context.SaveChangesFailed+=SaveChangesFailedEventHandler;

						CConsoleHelpers.WriteLine("DELETING DEPENDENT ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity1=PrincipalEntity.EntitiesDependent[0];
						CEntityOneToManyDependent				DependentEntity2=PrincipalEntity.EntitiesDependent[1];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity2)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity1);
						PrintEntityState(Context,DependentEntity2);

						Context.EntitiesOneToManyDependent.Remove(DependentEntity1);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity1)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

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
						// !!!!! Zaregistruje sa odber DB CONTEXT EVENTS.
						Context.SavingChanges+=SavingChangesEventHandler;
						Context.SavedChanges+=SavedChangesEventHandler;
						Context.SaveChangesFailed+=SaveChangesFailedEventHandler;

						CConsoleHelpers.WriteLine("DELETING PRINCIPAL ENTITY:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				PrincipalEntity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID).First();
						CEntityOneToManyDependent				DependentEntity=PrincipalEntity.EntitiesDependent[0];

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);
						CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity)}] READ from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity);

						Context.EntitiesOneToManyPrincipal.Remove(PrincipalEntity);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] REMOVED from DB CONTEXT.",ConsoleColor.Yellow);

						PrintEntityState(Context,PrincipalEntity);
						PrintEntityState(Context,DependentEntity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{nameof(PrincipalEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{nameof(DependentEntity)}] SAVED to DB CONTEXT.",ConsoleColor.Yellow);

							PrintEntityState(Context,PrincipalEntity);
							PrintEntityState(Context,DependentEntity);

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
		private static void TestRawSqlQueries()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID1=0;
			int													PrincipalID2=0;

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

						CEntityOneToManyDependent				DependentEntity11=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity12=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");
						CEntityOneToManyDependent				DependentEntity21=new CEntityOneToManyDependent(777,"NEW DEPENDENT 777");
						CEntityOneToManyDependent				DependentEntity22=new CEntityOneToManyDependent(888,"NEW DEPENDENT 888");

						CEntityOneToManyPrincipal				PrincipalEntity1=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity11,DependentEntity12}));
						CEntityOneToManyPrincipal				PrincipalEntity2=new CEntityOneToManyPrincipal(444,"NEW PRINCIPAL 444",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity21,DependentEntity22}));

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity1);
						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID1=PrincipalEntity1.EntityPrincipalID;
							PrincipalID2=PrincipalEntity2.EntityPrincipalID;

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity1.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity2.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity11.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity12.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity21.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity22.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("READING USING METHOD [FromSqlRaw()] 1:",ConsoleColor.Cyan);

						// !!!!! Definuje sa RAW SQL COMMAND.
						// !!!!! RAW SQL COMMAND moze obsahovat PARAMETERS.
						string									SQL="SELECT EntityPrincipalID, EntityPrincipalIntValue, EntityPrincipalStringValue FROM EntitiesOneToManyPrincipal";

						// !!!!! QUERY pouzivajuca RAW SQL COMMAND moze obsahovat LINQ OPERATOR [Include] na nacitanie DEPENDENT ENTITIES.
						// !!!!! QUERY pouzivajuca RAW SQL COMMAND moze obsahovat dalsie LINQ OPERATORS ako napriklad LINQ OPERATOR [Where].
						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.FromSqlRaw(SQL).Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalIntValue>200).ToArray();

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
						CConsoleHelpers.WriteLine("READING USING METHOD [FromSqlRaw()] 2:",ConsoleColor.Cyan);

						int										WhereValueFrom=200;
						int										WhereValueTo=400;

						// !!!!! Definuje sa RAW SQL COMMAND.
						// !!!!! RAW SQL COMMAND moze obsahovat PARAMETERS.
						string									SQL="SELECT EntityPrincipalID, EntityPrincipalIntValue, EntityPrincipalStringValue FROM EntitiesOneToManyPrincipal WHERE EntityPrincipalIntValue>{0} AND EntityPrincipalIntValue<{1}";

						// !!!!! QUERY pouzivajuca RAW SQL COMMAND moze obsahovat LINQ OPERATOR [Include] na nacitanie DEPENDENT ENTITIES.
						// !!!!! QUERY pouzivajuca RAW SQL COMMAND moze obsahovat dalsie LINQ OPERATORS ako napriklad LINQ OPERATOR [Where].
						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.FromSqlRaw(SQL,WhereValueFrom,WhereValueTo).Include(P => P.EntitiesDependent).OrderByDescending(P => P.EntityPrincipalIntValue).ToArray();

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
						CConsoleHelpers.WriteLine("READING USING METHOD [FromSqlInterpolated()] 1:",ConsoleColor.Cyan);

						// !!!!! Definuje sa RAW SQL COMMAND.
						// !!!!! RAW SQL COMMAND moze obsahovat PARAMETERS.
						// !!!!! SQL STRING MUSI byt TYPE [FormattableString], ktory je vytvarany pomocou C# STRING INTERPOLATION.
						FormattableString						SQL=$"SELECT EntityPrincipalID, EntityPrincipalIntValue, EntityPrincipalStringValue FROM EntitiesOneToManyPrincipal";

						// !!!!! QUERY pouzivajuca RAW SQL COMMAND moze obsahovat LINQ OPERATOR [Include] na nacitanie DEPENDENT ENTITIES.
						// !!!!! QUERY pouzivajuca RAW SQL COMMAND moze obsahovat dalsie LINQ OPERATORS ako napriklad LINQ OPERATOR [Where].
						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.FromSqlInterpolated(SQL).Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalIntValue>200).ToArray();

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
						CConsoleHelpers.WriteLine("READING USING METHOD [FromSqlInterpolated()] 2:",ConsoleColor.Cyan);

						int										WhereValueFrom=200;
						int										WhereValueTo=400;

						// !!!!! Definuje sa RAW SQL COMMAND.
						// !!!!! RAW SQL COMMAND moze obsahovat PARAMETERS.
						// !!!!! SQL STRING MUSI byt TYPE [FormattableString], ktory je vytvarany pomocou C# STRING INTERPOLATION.
						FormattableString						SQL=$"SELECT EntityPrincipalID, EntityPrincipalIntValue, EntityPrincipalStringValue FROM EntitiesOneToManyPrincipal WHERE EntityPrincipalIntValue>{WhereValueFrom} AND EntityPrincipalIntValue<{WhereValueTo}";

						// !!!!! QUERY pouzivajuca RAW SQL COMMAND moze obsahovat LINQ OPERATOR [Include] na nacitanie DEPENDENT ENTITIES.
						// !!!!! QUERY pouzivajuca RAW SQL COMMAND moze obsahovat dalsie LINQ OPERATORS ako napriklad LINQ OPERATOR [Where].
						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.FromSqlInterpolated(SQL).Include(P => P.EntitiesDependent).OrderByDescending(P => P.EntityPrincipalIntValue).ToArray();

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
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityOneToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();

						Context.EntitiesOneToManyPrincipal.Remove(ExistingPrincipalEntity1);
						Context.EntitiesOneToManyPrincipal.Remove(ExistingPrincipalEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity1.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity2.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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
		private static void TestRawSqlNonQueriesCommandsAndReloadEntities()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													PrincipalID1=0;
			int													PrincipalID2=0;

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

						CEntityOneToManyDependent				DependentEntity11=new CEntityOneToManyDependent(555,"NEW DEPENDENT 555");
						CEntityOneToManyDependent				DependentEntity12=new CEntityOneToManyDependent(666,"NEW DEPENDENT 666");
						CEntityOneToManyDependent				DependentEntity21=new CEntityOneToManyDependent(777,"NEW DEPENDENT 777");
						CEntityOneToManyDependent				DependentEntity22=new CEntityOneToManyDependent(888,"NEW DEPENDENT 888");

						CEntityOneToManyPrincipal				PrincipalEntity1=new CEntityOneToManyPrincipal(333,"NEW PRINCIPAL 333",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity11,DependentEntity12}));
						CEntityOneToManyPrincipal				PrincipalEntity2=new CEntityOneToManyPrincipal(444,"NEW PRINCIPAL 444",new List<CEntityOneToManyDependent>(new CEntityOneToManyDependent[]{DependentEntity21,DependentEntity22}));

						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity1);
						Context.EntitiesOneToManyPrincipal.Add(PrincipalEntity2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							PrincipalID1=PrincipalEntity1.EntityPrincipalID;
							PrincipalID2=PrincipalEntity2.EntityPrincipalID;

							CConsoleHelpers.WriteLineSeparator();
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity1.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{PrincipalEntity2.EntityPrincipalID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity11.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity12.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity21.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"DEPENDENT ENTITY [{DependentEntity22.EntityDependentID}] was INSERTED !",ConsoleColor.Blue);
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
						CConsoleHelpers.WriteLine("UPDATING USING METHOD [ExecuteSqlRaw()]:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				Entity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();

						CConsoleHelpers.WriteLine($"ENTITY READ from DB.",ConsoleColor.Yellow);

						CConsoleHelpers.Write(Entity.Print(null),ConsoleColor.Green);

						string									ModifiedValue="!!!!! MODIFIED 111 !!!";

						// !!!!! Definuje sa RAW SQL COMMAND.
						// !!!!! RAW SQL COMMAND moze obsahovat PARAMETERS.
						string									SQL="UPDATE EntitiesOneToManyPrincipal SET EntityPrincipalStringValue={0} WHERE EntityPrincipalID={1}";

						int										NumberOfRecordsModified=Context.Database.ExecuteSqlRaw(SQL,ModifiedValue,PrincipalID1);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"NUMBER OF RECORDS MODIFIED [{NumberOfRecordsModified}].",ConsoleColor.Yellow);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"ENTITY after MODIFYING by RAW SQL COMMAND.",ConsoleColor.Yellow);

						// !!!!! PROPERTY, ktora bola modifikovana pomocou RAW SQL COMMAND NEBUDE UPDATED v ENTITY, pretoze ENTITY NEBOLA RELOADED.
						CConsoleHelpers.Write(Entity.Print(null),ConsoleColor.Green);

						// !!!!! Vykona sa RELOAD ENTITY.
						Context.Entry(Entity).Reload();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"ENTITY after RELOADING from DB.",ConsoleColor.Yellow);

						// !!!!! PROPERTIES su UPDATED na CURRENT VALUES.
						CConsoleHelpers.Write(Entity.Print(null),ConsoleColor.Green);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE USING METHOD [ExecuteSqlRaw()]:",ConsoleColor.Cyan);

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
						CConsoleHelpers.WriteLine("UPDATING USING METHOD [ExecuteSqlInterpolated()]:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				Entity=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();

						CConsoleHelpers.WriteLine($"ENTITY READ from DB.",ConsoleColor.Yellow);

						CConsoleHelpers.Write(Entity.Print(null),ConsoleColor.Green);

						string									ModifiedValue="!!!!! MODIFIED 222 !!!";

						// !!!!! Definuje sa RAW SQL COMMAND.
						// !!!!! RAW SQL COMMAND moze obsahovat PARAMETERS.
						// !!!!! SQL STRING MUSI byt TYPE [FormattableString], ktory je vytvarany pomocou C# STRING INTERPOLATION.
						FormattableString						SQL=$"UPDATE EntitiesOneToManyPrincipal SET EntityPrincipalStringValue={ModifiedValue} WHERE EntityPrincipalID={PrincipalID2}";

						int										NumberOfRecordsModified=Context.Database.ExecuteSqlInterpolated(SQL);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"NUMBER OF RECORDS MODIFIED [{NumberOfRecordsModified}].",ConsoleColor.Yellow);

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"ENTITY after MODIFYING by RAW SQL COMMAND.",ConsoleColor.Yellow);

						// !!!!! PROPERTY, ktora bola modifikovana pomocou RAW SQL COMMAND NEBUDE UPDATED v ENTITY, pretoze ENTITY NEBOLA RELOADED.
						CConsoleHelpers.Write(Entity.Print(null),ConsoleColor.Green);

						// !!!!! Vykona sa RELOAD ENTITY.
						Context.Entry(Entity).Reload();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine($"ENTITY after RELOADING from DB.",ConsoleColor.Yellow);

						// !!!!! PROPERTIES su UPDATED na CURRENT VALUES.
						CConsoleHelpers.Write(Entity.Print(null),ConsoleColor.Green);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE USING METHOD [ExecuteSqlInterpolated()]:",ConsoleColor.Cyan);

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
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal				ExistingPrincipalEntity1=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID1).First();
						CEntityOneToManyPrincipal				ExistingPrincipalEntity2=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).Where(P => P.EntityPrincipalID==PrincipalID2).First();

						Context.EntitiesOneToManyPrincipal.Remove(ExistingPrincipalEntity1);
						Context.EntitiesOneToManyPrincipal.Remove(ExistingPrincipalEntity2);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity1.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
							CConsoleHelpers.WriteLine($"PRINCIPAL ENTITY [{ExistingPrincipalEntity2.EntityPrincipalID}] was DELETED !",ConsoleColor.Blue);
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
		private static void TestToSqlQueryEntity()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("READING BACKEND ENTITIES:",ConsoleColor.Cyan);

						CEntityToSqlQueryBackendData[]			Entities=Context.EntitiesToSqlQueryBackendData.ToArray();

						CEntityToSqlQueryBackendData.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("READING TO SQL QUERY ENTITIES:",ConsoleColor.Cyan);

						CEntityToSqlQuery[]						Entities=Context.EntitiesToSqlQuery.ToArray();

						CEntityToSqlQuery.PrintToConsole(Entities);
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
		public static void TestGetDbConnectionMethod()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						// !!! Pomocou METHOD [DbConnection DatabaseFacade.GetDbConnection()] sa ziska instancia DB CONNECTION.
						using(DbConnection Connection=Context.Database.GetDbConnection())
						{
							// !!! Otvori sa CONNECTION na DATABASE.
							Connection.Open();

							// Vytvori sa RAW SQL COMMAND.
							using(DbCommand Command=Connection.CreateCommand())
							{
								// !!! Definuje sa RAW SQL COMMAND.
								Command.CommandText=$"SELECT EntityID, EntityIntValue, EntityStringValue, EntityDoubleValue FROM {CDBContext.TO_SQL_QUERY_TABLE_NAME}";

								int								RecordNumber=0;

								// !!! Spusti sa READER na nacitanie vysledkov QUERY COMMAND.
								using(DbDataReader DataReader=Command.ExecuteReader())
								{
									// !!! Nacita sa RECORD z DATABASE.
									while(DataReader.Read()==true)
									{
										// !!! Nacita sa COLUMN 1 z RECORD.
										int						EntityID=DataReader.GetInt32(0);
										// !!! Nacita sa COLUMN 2 z RECORD.
										int						EntityIntValue=DataReader.GetInt32(1);
										// !!! Nacita sa COLUMN 3 z RECORD.
										string					EntityStringValue=DataReader.GetString(2);
										// !!! Nacita sa COLUMN 4 z RECORD.
										double					EntityDoubleValue=DataReader.GetDouble(3);

										CConsoleHelpers.WriteLine($"RECORD [{++RecordNumber}] - ENTITY ID [{EntityID}] ENTITY INT VALUE [{EntityIntValue}] ENTITY STRING VALUE [{EntityStringValue}] ENTITY DOUBLE VALUE [{EntityDoubleValue}] !",ConsoleColor.Green);
									}
								}
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
		private static void PrintMetadata<TType>(EntityEntry<TType> Entry) where TType : class
		{
			IEntityType											EntityType=Entry.Metadata;

			CConsoleHelpers.WriteLineSeparator();

			Console.WriteLine($"NAME [{EntityType.Name}].");
			Console.WriteLine($"\tTABLE NAME [{EntityType.GetTableName()}].");
			Console.WriteLine($"\tPROPERTIES:");

			IProperty[]											Properties=EntityType.GetProperties().ToArray();

			foreach(IProperty Property in Properties)
			{
				Console.WriteLine($"\t\tNAME [{Property.Name}].");
				Console.WriteLine($"\t\t\tCOLUMN NAME [{Property.GetColumnName()}].");
				Console.WriteLine($"\t\t\tCOLUMN TYPE [{Property.GetColumnType()}].");
				Console.WriteLine($"\t\t\tIS NULLABLE [{Property.IsNullable}].");

				PropertyInfo									PropertyInfo=Property.PropertyInfo;

				if (PropertyInfo!=null)
				{
					// !!!!! Ziska sa CURRENT VALUE danej ENTITY PROPERTY.
					object										PropertyValue=PropertyInfo.GetValue(Entry.Entity);

					CConsoleHelpers.WriteLine($"\t\t\tCURRENT VALUE [{PropertyValue}].",ConsoleColor.Red);
				}
			}

			Console.WriteLine($"\tNAVIGATIONS:");

			INavigation[]										Navigations=EntityType.GetNavigations().ToArray();

			foreach(INavigation Navigation in Navigations)
			{
				Console.WriteLine($"\t\tNAME [{Navigation.Name}].");
				Console.WriteLine($"\t\t\tIS COLLECTION [{Navigation.IsCollection}].");
				Console.WriteLine($"\t\t\tIS ON DEPENDENT [{Navigation.IsOnDependent}].");

				PropertyInfo									PropertyInfo=Navigation.PropertyInfo;

				if (PropertyInfo!=null)
				{
					// !!!!! Ziska sa CURRENT VALUE danej ENTITY PROPERTY.
					object										PropertyValue=PropertyInfo.GetValue(Entry.Entity);

					CConsoleHelpers.WriteLine($"\t\t\tCURRENT VALUE [{PropertyValue}].",ConsoleColor.Red);
				}
			}

			Console.WriteLine($"\tKEYS:");

			IKey[]												Keys=EntityType.GetKeys().ToArray();

			foreach(IKey Key in Keys)
			{
				Console.WriteLine($"\t\tNAME [{Key.GetName()}].");
				Console.WriteLine($"\t\t\tKEY TYPE [{Key.GetKeyType().Name}].");
				Console.WriteLine($"\t\t\tIS PRIMARY KEY [{Key.IsPrimaryKey()}].");
			}

			Console.WriteLine($"\tFOREIGN KEYS:");

			IForeignKey[]										ForeignKeys=EntityType.GetForeignKeys().ToArray();

			foreach(IForeignKey ForeignKey in ForeignKeys)
			{
				Console.WriteLine($"\t\tCONSTRAINT NAME [{ForeignKey.GetConstraintName()}].");
				Console.WriteLine($"\t\t\tIS UNIQUE [{ForeignKey.IsUnique}].");
				Console.WriteLine($"\t\t\tIS REQUIRED [{ForeignKey.IsRequired}].");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void TestEntityEntryMetadata()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("DATA:",ConsoleColor.Cyan);

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
						CConsoleHelpers.WriteLine("METADATA:",ConsoleColor.Cyan);

						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).ToArray();

						foreach(CEntityOneToManyPrincipal PrincipalEntity in Entities)
						{
							EntityEntry<CEntityOneToManyPrincipal>	PrincipalEntityEntry=Context.Entry(PrincipalEntity);

							PrintMetadata(PrincipalEntityEntry);

							foreach(CEntityOneToManyDependent DependentEntity in PrincipalEntity.EntitiesDependent)
							{
								EntityEntry<CEntityOneToManyDependent>	DependentEntityEntry=Context.Entry(DependentEntity);

								PrintMetadata(DependentEntityEntry);
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
		private static void PrintModel(IModel Model)
		{
			Console.WriteLine($"\tENTITY TYPES:");

			IEntityType[]										EntityTypes=Model.GetEntityTypes().ToArray();

			foreach(IEntityType EntityType in EntityTypes)
			{
				Console.WriteLine($"\t\tNAME [{EntityType.Name}].");
				Console.WriteLine($"\t\t\tTABLE NAME [{EntityType.GetTableName()}].");
				Console.WriteLine($"\t\t\tNUMBER OF PROPERTIES [{EntityType.GetProperties().Count()}].");
				Console.WriteLine($"\t\t\tNUMBER OF NAVIGATIONS [{EntityType.GetNavigations().Count()}].");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void TestDbContextMetadata()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("METADATA:",ConsoleColor.Cyan);

						IModel									Model=Context.Model;

						PrintModel(Model);
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
		public static void TestChangeConnectionString()
		{
			CConsoleHelpers.WriteLineSeparator();

			string												DefaultConnectionString=null;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("READING with DEFAULT CONNECTION STRING 1:",ConsoleColor.Cyan);

						string									ConnectionString=Context.Database.GetConnectionString();

						DefaultConnectionString=ConnectionString;

						CConsoleHelpers.WriteLine($"CONNECTION STRING [{ConnectionString}].",ConsoleColor.DarkRed);
						CConsoleHelpers.WriteLineSeparator();

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

					CConsoleHelpers.WriteLineSeparators(3);

					try
					{
						CConsoleHelpers.WriteLine("READING with INVALID CONNECTION STRING:",ConsoleColor.Cyan);

						// !!!!! CONNECTION STRING sa ZMENI na NEEXISTUJUCU DB.
						Context.Database.SetConnectionString("Data Source=XXX.db");

						string									ConnectionString=Context.Database.GetConnectionString();

						CConsoleHelpers.WriteLine($"CONNECTION STRING [{ConnectionString}].",ConsoleColor.DarkRed);
						CConsoleHelpers.WriteLineSeparator();

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

					CConsoleHelpers.WriteLineSeparators(3);

					try
					{
						CConsoleHelpers.WriteLine("READING with DEFAULT CONNECTION STRING 2:",ConsoleColor.Cyan);

						// !!!!! CONNECTION STRING sa POVODNU na NEZMYSELNU VALUE.
						Context.Database.SetConnectionString(DefaultConnectionString);

						string									ConnectionString=Context.Database.GetConnectionString();

						CConsoleHelpers.WriteLine($"CONNECTION STRING [{ConnectionString}].",ConsoleColor.DarkRed);
						CConsoleHelpers.WriteLineSeparator();

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
		// !!!!! V CODE EXECUTION STRATEGY je mozne vykonat CUSTOM CODE ako je opakovanie TRANSACTION.
		private static void MyActionInExecutionStrategy(CDBContext Context, int EntityID)
		{
			CConsoleHelpers.WriteLine($"CODE in EXECUTION STRATEGY ACTION METHOD STARTED !",ConsoleColor.Magenta);

			try
			{
				// !!! Vytvori sa nova TRANSACTION.
				using(IDbContextTransaction DbContextTransaction=Context.Database.BeginTransaction())
				{
					CConsoleHelpers.WriteLine($"QUERY is EXECUTING !",ConsoleColor.Magenta);

					CEntityToSqlQueryBackendData				Entity=Context.EntitiesToSqlQueryBackendData.Where(P => P.EntityID==EntityID).First();

					CConsoleHelpers.WriteLine($"QUERY is EXECUTED !",ConsoleColor.Magenta);

					Entity.EntityIntValue+=10000;

					CConsoleHelpers.WriteLine($"SAVE CHANGED 1 CALLING !",ConsoleColor.Magenta);

					Context.SaveChanges();

					CConsoleHelpers.WriteLine($"SAVE CHANGED 1 CALLED !",ConsoleColor.Magenta);

					Entity.EntityStringValue+=" MODIFIED !!!!!";

					CConsoleHelpers.WriteLine($"SAVE CHANGED 2 CALLING !",ConsoleColor.Magenta);

					Context.SaveChanges();

					CConsoleHelpers.WriteLine($"SAVE CHANGED 2 CALLED !",ConsoleColor.Magenta);

					Entity.EntityDoubleValue+=55555.55555;

					CConsoleHelpers.WriteLine($"SAVE CHANGED 3 CALLING !",ConsoleColor.Magenta);

					Context.SaveChanges();

					CConsoleHelpers.WriteLine($"SAVE CHANGED 3 CALLED !",ConsoleColor.Magenta);

					// !!! Vykona sa COMMIT TRANSACTION.
					DbContextTransaction.Commit();

					CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] UPDATED !",ConsoleColor.Yellow);
				}
			}
			catch(Exception E)
			{
				CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);

				// !!!!! EXCEPTION je RETHROWN, aby sa tym indikovalo, ze CODE v EXECUTION STRATEGY ZLYHAL.
				throw;
			}
			finally
			{
				CConsoleHelpers.WriteLine($"CODE in EXECUTION STRATEGY ACTION METHOD FINISHED !",ConsoleColor.Magenta);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void TestCustomCodeInExecutionStrategy()
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

						CEntityToSqlQueryBackendData[]			Entities=Context.EntitiesToSqlQueryBackendData.ToArray();

						CEntityToSqlQueryBackendData.PrintToConsole(Entities);
					}
					catch(Exception E)
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

						CEntityToSqlQueryBackendData			Entity=new CEntityToSqlQueryBackendData(555,"STRING 555",555.555);

						Context.EntitiesToSqlQueryBackendData.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
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

						CEntityToSqlQueryBackendData[]			Entities=Context.EntitiesToSqlQueryBackendData.ToArray();

						CEntityToSqlQueryBackendData.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

					// !!!!! Kedze CODE pouziva CUSTOM TRANSACTIONS, vytvori sa EXPLICITNA EXECUTION STRATEGY.
					IExecutionStrategy							ExecutionStrategy=Context.Database.CreateExecutionStrategy();

					// !!!!! Spusti sa vykonanie CUSTOM CODE v EXECUTION STRATEGY.
					ExecutionStrategy.Execute(() => MyActionInExecutionStrategy(Context,ID));
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityToSqlQueryBackendData[]			Entities=Context.EntitiesToSqlQueryBackendData.ToArray();

						CEntityToSqlQueryBackendData.PrintToConsole(Entities);
					}
					catch(Exception E)
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

						CEntityToSqlQueryBackendData			Entity=Context.EntitiesToSqlQueryBackendData.Where(P => P.EntityID==ID).First();

						Context.EntitiesToSqlQueryBackendData.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
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

						CEntityToSqlQueryBackendData[]			Entities=Context.EntitiesToSqlQueryBackendData.ToArray();

						CEntityToSqlQueryBackendData.PrintToConsole(Entities);
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
		private static void TestCustomCodeInExecutionStrategyWithCustomExecutionStrategy()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID=0;

			try
			{
				// !!!!! Pouzije sa CUSTOM EXECUTION STRATEGY.
				using(CDBContext Context=new CDBContext(ECustomExecutionStrategy.E_USE_CUSTOM_EXECUTION_STRATEGY))
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CEntityToSqlQueryBackendData[]			Entities=Context.EntitiesToSqlQueryBackendData.ToArray();

						CEntityToSqlQueryBackendData.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				// !!!!! Pouzije sa CUSTOM EXECUTION STRATEGY.
				using(CDBContext Context=new CDBContext(ECustomExecutionStrategy.E_USE_CUSTOM_EXECUTION_STRATEGY))
				{
					try
					{
						CConsoleHelpers.WriteLine("INSERTING:",ConsoleColor.Cyan);

						CEntityToSqlQueryBackendData			Entity=new CEntityToSqlQueryBackendData(555,"STRING 555",555.555);

						Context.EntitiesToSqlQueryBackendData.Add(Entity);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLineSeparator();
						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID=Entity.EntityID;

							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was INSERTED !",ConsoleColor.Blue);
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

				// !!!!! Pouzije sa CUSTOM EXECUTION STRATEGY.
				using(CDBContext Context=new CDBContext(ECustomExecutionStrategy.E_USE_CUSTOM_EXECUTION_STRATEGY))
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CEntityToSqlQueryBackendData[]			Entities=Context.EntitiesToSqlQueryBackendData.ToArray();

						CEntityToSqlQueryBackendData.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				// !!!!! Pouzije sa CUSTOM EXECUTION STRATEGY.
				using(CDBContext Context=new CDBContext(ECustomExecutionStrategy.E_USE_CUSTOM_EXECUTION_STRATEGY))
				{
					CConsoleHelpers.WriteLine("UPDATING:",ConsoleColor.Cyan);

					// !!!!! Kedze CODE pouziva CUSTOM TRANSACTIONS, vytvori sa EXPLICITNA EXECUTION STRATEGY.
					IExecutionStrategy							ExecutionStrategy=Context.Database.CreateExecutionStrategy();

					// !!!!! Spusti sa vykonanie CUSTOM CODE v EXECUTION STRATEGY.
					ExecutionStrategy.Execute(() => MyActionInExecutionStrategy(Context,ID));
				}

				CConsoleHelpers.WriteLineSeparators(3);

				// !!!!! Pouzije sa CUSTOM EXECUTION STRATEGY.
				using(CDBContext Context=new CDBContext(ECustomExecutionStrategy.E_USE_CUSTOM_EXECUTION_STRATEGY))
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER UPDATE:",ConsoleColor.Cyan);

						CEntityToSqlQueryBackendData[]			Entities=Context.EntitiesToSqlQueryBackendData.ToArray();

						CEntityToSqlQueryBackendData.PrintToConsole(Entities);
					}
					catch(Exception E)
					{
						CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				// !!!!! Pouzije sa CUSTOM EXECUTION STRATEGY.
				using(CDBContext Context=new CDBContext(ECustomExecutionStrategy.E_USE_CUSTOM_EXECUTION_STRATEGY))
				{
					try
					{
						CConsoleHelpers.WriteLine("DELETING ENTITIES:",ConsoleColor.Cyan);

						CEntityToSqlQueryBackendData			Entity=Context.EntitiesToSqlQueryBackendData.Where(P => P.EntityID==ID).First();

						Context.EntitiesToSqlQueryBackendData.Remove(Entity);

						int										NumberOfModifiedEntities=Context.SaveChanges();

						if (NumberOfModifiedEntities>0)
						{
							CConsoleHelpers.WriteLine($"ENTITY [{Entity.EntityID}] was DELETED !",ConsoleColor.Blue);
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

				// !!!!! Pouzije sa CUSTOM EXECUTION STRATEGY.
				using(CDBContext Context=new CDBContext(ECustomExecutionStrategy.E_USE_CUSTOM_EXECUTION_STRATEGY))
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE ENTITIES:",ConsoleColor.Cyan);

						CEntityToSqlQueryBackendData[]			Entities=Context.EntitiesToSqlQueryBackendData.ToArray();

						CEntityToSqlQueryBackendData.PrintToConsole(Entities);
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
			//TestOneToManyAddUpdateDelete();
			//TestOneToManyMoveDependentEntityByChangingNavigationProperty();
			//TestOneToManyMoveDependentEntityByChangingForeignKeyProperty();
			//TestZeroToManyAddUpdateDelete();
			//TestZeroToManyMoveDependentEntityByChangingNavigationProperty();
			//TestZeroToManyMoveDependentEntityByChangingForeignKeyProperty();
			//TestUpdateMethod();
			//TestAttachMethod();
			//TestManuallyChangeState();
			//TestTrackGraphMethod();
			//TestTrackingChangesModeSnapshot();
			//TestTrackingChangesChangedNotifications();
			//TestTrackingChangesChangingAndChangedNotifications();
			//TestTrackingChangesChangingAndChangedNotificationsWithOriginalValues();
			//TestUseChangeTrackerEntriesMethod();
			//TestChangeTrackerEvents();
			//TestDbContextEvents();
			//TestRawSqlQueries();
			//TestRawSqlNonQueriesCommandsAndReloadEntities();
			//TestToSqlQueryEntity();
			//TestGetDbConnectionMethod();
			//TestEntityEntryMetadata();
			//TestDbContextMetadata();
			//TestChangeConnectionString();
			//TestCustomCodeInExecutionStrategy();
			TestCustomCodeInExecutionStrategyWithCustomExecutionStrategy();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------