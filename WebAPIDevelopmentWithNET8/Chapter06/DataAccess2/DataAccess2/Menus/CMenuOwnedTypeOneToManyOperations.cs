using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace DataAccess2
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuOwnedTypeOneToManyOperations : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuOwnedTypeOneToManyOperations()
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
					CEntityOwnedOneToManyPrincipal[]			EntitiesPrincipal=Context.EntitiesOwnedOneToManyPrincipal.ToArray();

					CEntityOwnedOneToManyPrincipal.PrintToConsole(EntitiesPrincipal);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntity(string CommandID, object[] Parameters)
		{
			int													PrincipalID=((int) Parameters[0]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityOwnedOneToManyPrincipal				Entity=Context.EntitiesOwnedOneToManyPrincipal.Where(P => P.EntityPrincipalID==PrincipalID).FirstOrDefault();

					if (Entity!=null)
					{
						string									EntityText=Entity.Print(null);

						Console.Write(EntityText);
					}
					else
					{
						Console.WriteLine($"ENTITY NOT FOUND for ID [{PrincipalID}].");
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
			string												EntityPrincipalValue=((string) Parameters[0]);
			string												EntityDependentValue1=((string) Parameters[1]);
			string												EntityDependentValue2=((string) Parameters[2]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityOwnedOneToManyDependent				EntityDependent1=new CEntityOwnedOneToManyDependent(EntityDependentValue1);
					CEntityOwnedOneToManyDependent				EntityDependent2=new CEntityOwnedOneToManyDependent(EntityDependentValue2);

					CEntityOwnedOneToManyPrincipal				EntityPrincipal=new CEntityOwnedOneToManyPrincipal(EntityPrincipalValue,new CEntityOwnedOneToManyDependent[]{EntityDependent1,EntityDependent2});

					Context.EntitiesOwnedOneToManyPrincipal.Add(EntityPrincipal);

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
			int													PrincipalID=((int) Parameters[0]);
			string												EntityPrincipalValue=((string) Parameters[1]);
			string												EntityDependentValue1=((string) Parameters[2]);
			string												EntityDependentValue2=((string) Parameters[3]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityOwnedOneToManyPrincipal				EntityPrincipal=Context.EntitiesOwnedOneToManyPrincipal.Where(P => P.EntityPrincipalID==PrincipalID).FirstOrDefault();

					if (EntityPrincipal!=null)
					{
						CEntityOwnedOneToManyDependent			EntityDependent1=EntityPrincipal.EntitiesDependent.OrderBy(P => P.EntityDependentID).FirstOrDefault();
						CEntityOwnedOneToManyDependent			EntityDependent2=EntityPrincipal.EntitiesDependent.OrderBy(P => P.EntityDependentID).Skip(1).FirstOrDefault();

						EntityPrincipal.EntityPrincipalValue=EntityPrincipalValue;

						if (EntityDependent1!=null)
						{
							EntityDependent1.EntityDependentValue=EntityDependentValue1;
						}

						if (EntityDependent2!=null)
						{
							EntityDependent2.EntityDependentValue=EntityDependentValue2;
						}

						int										NumberOfRecordsModified=Context.SaveChanges();

						Console.WriteLine($"NUMBER OF RECORDS MODIFIED [{NumberOfRecordsModified}].");
					}
					else
					{
						Console.WriteLine($"ENTITY NOT FOUND for ID [{PrincipalID}].");
					}
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteEntity(string CommandID, object[] Parameters)
		{
			int													PrincipalID=((int) Parameters[0]);

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					int											NumberOfRecordsModified=Context.EntitiesOwnedOneToManyPrincipal.Where(P => P.EntityPrincipalID==PrincipalID).ExecuteDelete();

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
			CommandsCollection.Add(new CMenuCommand("2","GET ENTITY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandGetEntity));
			CommandsCollection.Add(new CMenuCommand("3","INSERT ENTITIES",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandInsertEntity));
			CommandsCollection.Add(new CMenuCommand("4","UPDATE ENTITIES",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandUpdateEntity));
			CommandsCollection.Add(new CMenuCommand("5","DELETE ENTITY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandDeleteEntity));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------