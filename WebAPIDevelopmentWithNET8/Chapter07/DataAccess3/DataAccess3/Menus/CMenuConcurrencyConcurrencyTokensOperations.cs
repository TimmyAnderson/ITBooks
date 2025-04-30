using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace DataAccess3
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuConcurrencyConcurrencyTokensOperations : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuConcurrencyConcurrencyTokensOperations()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public static void UpdateEntityConcurrencyTokensDataAnnotationsThread(int EntityID, int ValueToAdd, int SleepTime)
		{
			int													ThreadID=Thread.CurrentThread.ManagedThreadId;

			try
			{
				DbContextOptionsBuilder<CDBContext>				OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

				OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

				DbContextOptions<CDBContext>					Options=OptionsBuilder.Options;

				using(CDBContext Context=new CDBContext(Options))
				{
					try
					{
						CEntityConcurrencyTokensDataAnnotations	Entity=Context.EntitiesConcurrencyTokensDataAnnotations.Where(P => P.EntityID==EntityID).First();

						Console.WriteLine($"THREAD [{ThreadID}] READ VALUE [{Entity.EntityValue}] !");

						Console.WriteLine($"THREAD [{ThreadID}] WAITING STARTED !");

						Thread.Sleep(SleepTime);

						Console.WriteLine($"THREAD [{ThreadID}] WAITING FINISHED !");

						Entity.EntityValue+=ValueToAdd;

						// !!!!! Pri pouziti CONCURRENCY TOKENS je NUTNE pri kazdej zmene DB RECORD vykonat zmenu CONCURRENCY TOKEN.
						Entity.Version=Guid.NewGuid();

						Console.WriteLine($"THREAD [{ThreadID}] ADDING VALUE [{ValueToAdd}] !");

						Context.SaveChanges();

						Console.WriteLine($"THREAD [{ThreadID}] UPDATED VALUE to VALUE [{Entity.EntityValue}] !");
					}
					catch(DbUpdateConcurrencyException E)
					{
						Console.WriteLine($"THREAD [{ThreadID}] DB UPDATE CONCURRENCY EXCEPTION [{E.Message}] !");
					}
					catch(Exception E)
					{
						Console.WriteLine($"THREAD [{ThreadID}] EXCEPTION [{E.Message}] !");
					}
				}
			}
			catch(DbUpdateConcurrencyException E)
			{
				Console.WriteLine($"THREAD [{ThreadID}] DB UPDATE CONCURRENCY EXCEPTION [{E.Message}] !");
			}
			catch(Exception E)
			{
				Console.WriteLine($"THREAD [{ThreadID}] EXCEPTION [{E.Message}] !");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public static void UpdateEntityConcurrencyTokensFluentAPIThread(int EntityID, int ValueToAdd, int SleepTime)
		{
			int													ThreadID=Thread.CurrentThread.ManagedThreadId;

			try
			{
				DbContextOptionsBuilder<CDBContext>				OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

				OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

				DbContextOptions<CDBContext>					Options=OptionsBuilder.Options;

				using(CDBContext Context=new CDBContext(Options))
				{
					try
					{
						CEntityConcurrencyTokensFluentAPI		Entity=Context.EntitiesConcurrencyTokensFluentAPI.Where(P => P.EntityID==EntityID).First();

						Console.WriteLine($"THREAD [{ThreadID}] READ VALUE [{Entity.EntityValue}] !");

						Console.WriteLine($"THREAD [{ThreadID}] WAITING STARTED !");

						Thread.Sleep(SleepTime);

						Console.WriteLine($"THREAD [{ThreadID}] WAITING FINISHED !");

						Entity.EntityValue+=ValueToAdd;

						// !!!!! Pri pouziti CONCURRENCY TOKENS je NUTNE pri kazdej zmene DB RECORD vykonat zmenu CONCURRENCY TOKEN.
						Entity.Version=Guid.NewGuid();

						Console.WriteLine($"THREAD [{ThreadID}] ADDING VALUE [{ValueToAdd}] !");

						Context.SaveChanges();

						Console.WriteLine($"THREAD [{ThreadID}] UPDATED VALUE to VALUE [{Entity.EntityValue}] !");
					}
					catch(DbUpdateConcurrencyException E)
					{
						Console.WriteLine($"THREAD [{ThreadID}] DB UPDATE CONCURRENCY EXCEPTION [{E.Message}] !");
					}
					catch(Exception E)
					{
						Console.WriteLine($"THREAD [{ThreadID}] EXCEPTION [{E.Message}] !");
					}
				}
			}
			catch(DbUpdateConcurrencyException E)
			{
				Console.WriteLine($"THREAD [{ThreadID}] DB UPDATE CONCURRENCY EXCEPTION [{E.Message}] !");
			}
			catch(Exception E)
			{
				Console.WriteLine($"THREAD [{ThreadID}] EXCEPTION [{E.Message}] !");
			}
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
		private void ExecuteCommandGetEntitiesConcurrencyTokensDataAnnotations(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityConcurrencyTokensDataAnnotations[]	Entities=Context.EntitiesConcurrencyTokensDataAnnotations.ToArray();

					CEntityConcurrencyTokensDataAnnotations.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntitiesConcurrencyTokensFluentAPI(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityConcurrencyTokensFluentAPI[]			Entities=Context.EntitiesConcurrencyTokensFluentAPI.ToArray();

					CEntityConcurrencyTokensFluentAPI.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateConcurrencyTokensDataAnnotations(string CommandID, object[] Parameters)
		{
			int													ID;

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			Console.WriteLine("BEFORE UPDATE:");

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityConcurrencyTokensDataAnnotations		Entity=Context.EntitiesConcurrencyTokensDataAnnotations.First();

					Console.Write(Entity.Print(null));

					ID=Entity.EntityID;
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
				}
			}

			Console.WriteLine(new string('-',80));
			Console.WriteLine(new string('-',80));
			Console.WriteLine(new string('-',80));

			Thread												Thread1=new Thread(P => UpdateEntityConcurrencyTokensDataAnnotationsThread(ID,10,500));
			Thread												Thread2=new Thread(P => UpdateEntityConcurrencyTokensDataAnnotationsThread(ID,20,1000));

			Thread1.Start();
			Thread2.Start();

			Thread1.Join();
			Thread2.Join();

			Console.WriteLine(new string('-',80));
			Console.WriteLine(new string('-',80));
			Console.WriteLine(new string('-',80));

			Console.WriteLine("AFTER UPDATE:");

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityConcurrencyTokensDataAnnotations		Entity=Context.EntitiesConcurrencyTokensDataAnnotations.First();

					Console.Write(Entity.Print(null));
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateConcurrencyTokensFluentAPI(string CommandID, object[] Parameters)
		{
			int													ID;

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			Console.WriteLine("BEFORE UPDATE:");

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityConcurrencyTokensFluentAPI			Entity=Context.EntitiesConcurrencyTokensFluentAPI.First();

					Console.Write(Entity.Print(null));

					ID=Entity.EntityID;
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
				}
			}

			Console.WriteLine(new string('-',80));
			Console.WriteLine(new string('-',80));
			Console.WriteLine(new string('-',80));

			Thread												Thread1=new Thread(P => UpdateEntityConcurrencyTokensFluentAPIThread(ID,10,500));
			Thread												Thread2=new Thread(P => UpdateEntityConcurrencyTokensFluentAPIThread(ID,20,1000));

			Thread1.Start();
			Thread2.Start();

			Thread1.Join();
			Thread2.Join();

			Console.WriteLine(new string('-',80));
			Console.WriteLine(new string('-',80));
			Console.WriteLine(new string('-',80));

			Console.WriteLine("AFTER UPDATE:");

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityConcurrencyTokensFluentAPI			Entity=Context.EntitiesConcurrencyTokensFluentAPI.First();

					Console.Write(Entity.Print(null));
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
					return;
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
			CommandsCollection.Add(new CMenuCommand("1","GET ALL CONCURRENCY TOKENS DATA ANNOTATIONS",new EMenuCommandParameterType[0],ExecuteCommandGetEntitiesConcurrencyTokensDataAnnotations));
			CommandsCollection.Add(new CMenuCommand("2","GET ALL CONCURRENCY TOKENS FLUENT API",new EMenuCommandParameterType[0],ExecuteCommandGetEntitiesConcurrencyTokensFluentAPI));
			CommandsCollection.Add(new CMenuCommand("3","UPDATE CONCURRENCY TOKENS DATA ANNOTATIONS",new EMenuCommandParameterType[0],ExecuteCommandUpdateConcurrencyTokensDataAnnotations));
			CommandsCollection.Add(new CMenuCommand("4","UPDATE CONCURRENCY TOKENS FLUENT API",new EMenuCommandParameterType[0],ExecuteCommandUpdateConcurrencyTokensFluentAPI));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------