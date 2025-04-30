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
	public sealed class CMenuBulkOperations : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuBulkOperations()
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
		private void ExecuteCommandGetEntitiesBulkOperations(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityBulkOperations[]						Entities=Context.EntitiesBulkOperations.ToArray();

					CEntityBulkOperations.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandBulkUpdate(string CommandID, object[] Parameters)
		{
			int													Category=10000;

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityBulkOperations						Entity1=new CEntityBulkOperations(Category,10001,10006);
					CEntityBulkOperations						Entity2=new CEntityBulkOperations(Category,10002,10007);

					Context.Add(Entity1);
					Context.Add(Entity2);

					Context.SaveChanges();
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}

			Console.WriteLine("AFTER INSERT:");

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityBulkOperations[]						Entities=Context.EntitiesBulkOperations.ToArray();

					CEntityBulkOperations.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}

			CConsoleHelpers.WriteLineSeparators(3);

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					// !!!!! Vykona sa BULK UPDATE.
					// !!!!! NIE JE NUTNE volat METHOD [int DbContext.SaveChanges()], pretoze OPERATION sa vykonava priamo nad DB.
					int											Result=Context.EntitiesBulkOperations.Where(P => P.Category==Category).ExecuteUpdate(P => P.SetProperty(R => R.Value1,999).SetProperty(R => R.Value2,9999));

					Console.WriteLine($"BULK OPERATION RESULT [{Result}].");
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}

			CConsoleHelpers.WriteLineSeparators(3);

			Console.WriteLine("AFTER UPDATE:");

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityBulkOperations[]						Entities=Context.EntitiesBulkOperations.ToArray();

					CEntityBulkOperations.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityBulkOperations[]						Entities=Context.EntitiesBulkOperations.Where(P => P.Category==10000).ToArray();

					Context.RemoveRange(Entities);

					Context.SaveChanges();
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}

			CConsoleHelpers.WriteLineSeparators(3);

			Console.WriteLine("AFTER DELETE:");

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityBulkOperations[]						Entities=Context.EntitiesBulkOperations.ToArray();

					CEntityBulkOperations.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandBulkDelete(string CommandID, object[] Parameters)
		{
			int													Category=10000;

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityBulkOperations						Entity1=new CEntityBulkOperations(Category,10001,10006);
					CEntityBulkOperations						Entity2=new CEntityBulkOperations(Category,10002,10007);

					Context.Add(Entity1);
					Context.Add(Entity2);

					Context.SaveChanges();
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}

			Console.WriteLine("AFTER INSERT:");

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityBulkOperations[]						Entities=Context.EntitiesBulkOperations.ToArray();

					CEntityBulkOperations.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}

			CConsoleHelpers.WriteLineSeparators(3);

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					// !!!!! Vykona sa BULK DELETE.
					// !!!!! NIE JE NUTNE volat METHOD [int DbContext.SaveChanges()], pretoze OPERATION sa vykonava priamo nad DB.
					int											Result=Context.EntitiesBulkOperations.Where(P => P.Category==Category).ExecuteDelete();

					Console.WriteLine($"BULK OPERATION RESULT [{Result}].");
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}

			CConsoleHelpers.WriteLineSeparators(3);

			Console.WriteLine("AFTER DELETE:");

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityBulkOperations[]						Entities=Context.EntitiesBulkOperations.ToArray();

					CEntityBulkOperations.PrintToConsole(Entities);
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

			CommandsCollection.Add(new CMenuCommand("cdb","CREATE DB",new EMenuCommandParameterType[0],ExecuteCommandCreateDatabase));
			CommandsCollection.Add(new CMenuCommand("ddb","DELETE DB",new EMenuCommandParameterType[0],ExecuteCommandDeleteDatabase));
			CommandsCollection.Add(new CMenuCommand("1","GET ALL ENTITIES BULK OPERATIONS",new EMenuCommandParameterType[0],ExecuteCommandGetEntitiesBulkOperations));
			CommandsCollection.Add(new CMenuCommand("2","BULK UPDATE",new EMenuCommandParameterType[0],ExecuteCommandBulkUpdate));
			CommandsCollection.Add(new CMenuCommand("3","BULK DELETE",new EMenuCommandParameterType[0],ExecuteCommandBulkDelete));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------