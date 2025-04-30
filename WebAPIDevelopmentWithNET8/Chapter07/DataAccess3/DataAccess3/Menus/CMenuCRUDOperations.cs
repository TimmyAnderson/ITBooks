using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.Data.Sqlite;
using Microsoft.EntityFrameworkCore;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace DataAccess3
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuCRUDOperations : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuCRUDOperations()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCreateDatabase(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					if (Context.Database.CanConnect()==false)
					{
						Context.Database.Migrate();

						Console.WriteLine("DATABASE CREATED !");
					}
					else
					{
						Console.WriteLine("Can't CREATE DATABASE.");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteDatabase(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					if (Context.Database.EnsureDeleted()==true)
					{
						Console.WriteLine("DATABASE DELETED !");
					}
					else
					{
						Console.WriteLine("Can't DELETE to DATABASE.");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestSelect(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestInsert1(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestInsert2(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestInsert3(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													EntityMID=0;
			int													EntityNID=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestUpdate1(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestUpdate2(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			CEntityOneToManyPrincipal							EntityFromDifferentContext=null;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestUpdate3(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestUpdate4(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID1=0;
			int													ID2=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestUpdate5(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestUpdate6(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestUpdate7(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID1=0;
			int													ID2=0;
			int													ID3=0;
			int													ID4=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestDelete1(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestDelete2(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestDelete3(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			int													ID=0;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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

				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestFind(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestSelectTracking(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
				{
					try
					{
						CEntityOneToManyPrincipal[]				Entities=Context.EntitiesOneToManyPrincipal.Include(P => P.EntitiesDependent).AsTracking().ToArray();

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
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestSelectNoTracking(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
				{
					try
					{
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
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("cdb","CREATE DB",new EMenuCommandParameterType[0],ExecuteCommandCreateDatabase));
			CommandsCollection.Add(new CMenuCommand("ddb","DELETE DB",new EMenuCommandParameterType[0],ExecuteCommandDeleteDatabase));
			CommandsCollection.Add(new CMenuCommand("1","TEST SELECT",new EMenuCommandParameterType[0],ExecuteCommandTestSelect));
			CommandsCollection.Add(new CMenuCommand("2","TEST INSERT 1",new EMenuCommandParameterType[0],ExecuteCommandTestInsert1));
			CommandsCollection.Add(new CMenuCommand("3","TEST INSERT 2",new EMenuCommandParameterType[0],ExecuteCommandTestInsert2));
			CommandsCollection.Add(new CMenuCommand("4","TEST INSERT 3",new EMenuCommandParameterType[0],ExecuteCommandTestInsert3));
			CommandsCollection.Add(new CMenuCommand("5","TEST UPDATE 1",new EMenuCommandParameterType[0],ExecuteCommandTestUpdate1));
			CommandsCollection.Add(new CMenuCommand("6","TEST UPDATE 2",new EMenuCommandParameterType[0],ExecuteCommandTestUpdate2));
			CommandsCollection.Add(new CMenuCommand("7","TEST UPDATE 3",new EMenuCommandParameterType[0],ExecuteCommandTestUpdate3));
			CommandsCollection.Add(new CMenuCommand("8","TEST UPDATE 4",new EMenuCommandParameterType[0],ExecuteCommandTestUpdate4));
			CommandsCollection.Add(new CMenuCommand("9","TEST UPDATE 5",new EMenuCommandParameterType[0],ExecuteCommandTestUpdate5));
			CommandsCollection.Add(new CMenuCommand("10","TEST UPDATE 6",new EMenuCommandParameterType[0],ExecuteCommandTestUpdate6));
			CommandsCollection.Add(new CMenuCommand("11","TEST UPDATE 7",new EMenuCommandParameterType[0],ExecuteCommandTestUpdate7));
			CommandsCollection.Add(new CMenuCommand("12","TEST DELETE 1",new EMenuCommandParameterType[0],ExecuteCommandTestDelete1));
			CommandsCollection.Add(new CMenuCommand("13","TEST DELETE 2",new EMenuCommandParameterType[0],ExecuteCommandTestDelete2));
			CommandsCollection.Add(new CMenuCommand("14","TEST DELETE 3",new EMenuCommandParameterType[0],ExecuteCommandTestDelete3));
			CommandsCollection.Add(new CMenuCommand("15","TEST FIND",new EMenuCommandParameterType[0],ExecuteCommandTestFind));
			CommandsCollection.Add(new CMenuCommand("16","TEST TRACKING",new EMenuCommandParameterType[0],ExecuteCommandTestSelectTracking));
			CommandsCollection.Add(new CMenuCommand("17","TEST NO TRACKING",new EMenuCommandParameterType[0],ExecuteCommandTestSelectNoTracking));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------