using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace OwnedTypes
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuManyToManyOperations : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuManyToManyOperations()
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
						Console.WriteLine("Can't CONNECT to DATABASE.");
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
		private void ExecuteCommandGetAllEntities(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityManyToManyM[]						EntitiesM=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).ToArray();

					CEntityManyToManyM.PrintToConsole(EntitiesM);

					Console.WriteLine(new string('-',80));
					Console.WriteLine(new string('-',80));
					Console.WriteLine(new string('-',80));

					CEntityManyToManyN[]						EntitiesN=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).ToArray();

					CEntityManyToManyN.PrintToConsole(EntitiesN);

					Console.WriteLine(new string('-',80));
					Console.WriteLine(new string('-',80));
					Console.WriteLine(new string('-',80));

					CEntityManyToManyMN[]						EntitiesMN=Context.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).ToArray();

					CEntityManyToManyMN.PrintToConsole(EntitiesMN);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntityM(string CommandID, object[] Parameters)
		{
			int													EntityMID=((int) Parameters[0]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityManyToManyM							Entity=Context.EntitiesManyToManyM.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityN).Where(P => P.EntityMID==EntityMID).FirstOrDefault();

					if (Entity!=null)
					{
						string									EntityText=Entity.Print(null);

						Console.Write(EntityText);
					}
					else
					{
						Console.WriteLine($"ENTITY NOT FOUND for ID [{EntityMID}].");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntityN(string CommandID, object[] Parameters)
		{
			int													EntityNID=((int) Parameters[0]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityManyToManyN							Entity=Context.EntitiesManyToManyN.Include(P => P.EntitiesMN).ThenInclude(P => P.EntityM).Where(P => P.EntityNID==EntityNID).FirstOrDefault();

					if (Entity!=null)
					{
						string									EntityText=Entity.Print(null);

						Console.Write(EntityText);
					}
					else
					{
						Console.WriteLine($"ENTITY NOT FOUND for ID [{EntityNID}].");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntityMN(string CommandID, object[] Parameters)
		{
			int													EntityMNID=((int) Parameters[0]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityManyToManyMN							Entity=Context.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==EntityMNID).FirstOrDefault();

					if (Entity!=null)
					{
						string									EntityText=Entity.Print(null);

						Console.Write(EntityText);
					}
					else
					{
						Console.WriteLine($"ENTITY NOT FOUND for ID [{EntityMNID}].");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInsertEntity(string CommandID, object[] Parameters)
		{
			string												EntityMValue1=((string) Parameters[0]);
			string												EntityMValue2=((string) Parameters[1]);
			string												EntityNValue1=((string) Parameters[2]);
			string												EntityNValue2=((string) Parameters[3]);
			string												EntityMNValue1=((string) Parameters[4]);
			string												EntityMNValue2=((string) Parameters[5]);
			string												EntityMNValue3=((string) Parameters[6]);
			string												EntityMNValue4=((string) Parameters[7]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityManyToManyM							EntityM1=new CEntityManyToManyM(EntityMValue1);
					CEntityManyToManyM							EntityM2=new CEntityManyToManyM(EntityMValue2);

					CEntityManyToManyN							EntityN1=new CEntityManyToManyN(EntityNValue1);
					CEntityManyToManyN							EntityN2=new CEntityManyToManyN(EntityNValue2);

					CEntityManyToManyMN							EntityMN1=new CEntityManyToManyMN(EntityMNValue1);
					CEntityManyToManyMN							EntityMN2=new CEntityManyToManyMN(EntityMNValue2);
					CEntityManyToManyMN							EntityMN3=new CEntityManyToManyMN(EntityMNValue4);
					CEntityManyToManyMN							EntityMN4=new CEntityManyToManyMN(EntityMNValue4);

					EntityMN1.EntityM=EntityM1;
					EntityMN1.EntityN=EntityN1;

					EntityMN2.EntityM=EntityM1;
					EntityMN2.EntityN=EntityN2;

					EntityMN3.EntityM=EntityM2;
					EntityMN3.EntityN=EntityN1;

					EntityMN4.EntityM=EntityM2;
					EntityMN4.EntityN=EntityN2;

					Context.EntitiesManyToManyMN.Add(EntityMN1);
					Context.EntitiesManyToManyMN.Add(EntityMN2);
					Context.EntitiesManyToManyMN.Add(EntityMN3);
					Context.EntitiesManyToManyMN.Add(EntityMN4);

					int											NumberOfRecordsModified=Context.SaveChanges();

					Console.WriteLine($"NUMBER OF RECORDS MODIFIED [{NumberOfRecordsModified}].");
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateEntity(string CommandID, object[] Parameters)
		{
			int													EntityMNID=((int) Parameters[0]);
			string												EntityMValue=((string) Parameters[1]);
			string												EntityNValue=((string) Parameters[2]);
			string												EntityMNValue=((string) Parameters[3]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityManyToManyMN							EntityMN=Context.EntitiesManyToManyMN.Include(P => P.EntityM).Include(P => P.EntityN).Where(P => P.EntityMNID==EntityMNID).FirstOrDefault();

					if (EntityMN!=null)
					{
						CEntityManyToManyM						EntityM=EntityMN.EntityM;
						CEntityManyToManyN						EntityN=EntityMN.EntityN;

						EntityMN.EntityMNValue=EntityMNValue;

						if (EntityM!=null)
						{
							EntityM.EntityMValue=EntityMValue;
						}

						if (EntityN!=null)
						{
							EntityN.EntityNValue=EntityNValue;
						}

						int										NumberOfRecordsModified=Context.SaveChanges();

						Console.WriteLine($"NUMBER OF RECORDS MODIFIED [{NumberOfRecordsModified}].");
					}
					else
					{
						Console.WriteLine($"ENTITY MN NOT FOUND for ID [{EntityMNID}].");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteEntityM(string CommandID, object[] Parameters)
		{
			int													EntityMID=((int) Parameters[0]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					int											NumberOfRecordsModified=Context.EntitiesManyToManyM.Where(P => P.EntityMID==EntityMID).ExecuteDelete();

					Console.WriteLine($"NUMBER OF RECORDS MODIFIED [{NumberOfRecordsModified}].");
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteEntityN(string CommandID, object[] Parameters)
		{
			int													EntityNID=((int) Parameters[0]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					int											NumberOfRecordsModified=Context.EntitiesManyToManyN.Where(P => P.EntityNID==EntityNID).ExecuteDelete();

					Console.WriteLine($"NUMBER OF RECORDS MODIFIED [{NumberOfRecordsModified}].");
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteEntityMN(string CommandID, object[] Parameters)
		{
			int													EntityMNID=((int) Parameters[0]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					int											NumberOfRecordsModified=Context.EntitiesManyToManyMN.Where(P => P.EntityMNID==EntityMNID).ExecuteDelete();

					Console.WriteLine($"NUMBER OF RECORDS MODIFIED [{NumberOfRecordsModified}].");
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
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("db","CREATE DB",new EMenuCommandParameterType[0],ExecuteCommandCreateDatabase));
			CommandsCollection.Add(new CMenuCommand("1","GET ALL ENTITIES",new EMenuCommandParameterType[0],ExecuteCommandGetAllEntities));
			CommandsCollection.Add(new CMenuCommand("2","GET ENTITY M",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandGetEntityM));
			CommandsCollection.Add(new CMenuCommand("3","GET ENTITY N",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandGetEntityN));
			CommandsCollection.Add(new CMenuCommand("4","GET ENTITY MN",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandGetEntityMN));
			CommandsCollection.Add(new CMenuCommand("5","INSERT ENTITIES",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandInsertEntity));
			CommandsCollection.Add(new CMenuCommand("6","UPDATE ENTITIES",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandUpdateEntity));
			CommandsCollection.Add(new CMenuCommand("7","DELETE ENTITY M",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandDeleteEntityM));
			CommandsCollection.Add(new CMenuCommand("8","DELETE ENTITY N",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandDeleteEntityN));
			CommandsCollection.Add(new CMenuCommand("9","DELETE ENTITY MN",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandDeleteEntityMN));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------