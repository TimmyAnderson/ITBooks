using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace DataAccess3SqlServer
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuConcurrencyTimestampsOperations : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQL_SERVER=@"Data Source=(LocalDb)\MSSQLLocalDB;Initial Catalog=DataAccess3SqlServer";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuConcurrencyTimestampsOperations()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public static void UpdateEntityTimestampsDataAnnotationsThread(int EntityID, int ValueToAdd, int SleepTime)
		{
			int													ThreadID=Thread.CurrentThread.ManagedThreadId;

			try
			{
				DbContextOptionsBuilder<CDBContext>				OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

				OptionsBuilder.UseSqlServer(MConnectionString_SQL_SERVER);

				DbContextOptions<CDBContext>					Options=OptionsBuilder.Options;

				using(CDBContext Context=new CDBContext(Options))
				{
					try
					{
						CEntityTimestampsDataAnnotations		Entity=Context.EntitiesTimestampsDataAnnotations.Where(P => P.EntityID==EntityID).First();

						Console.WriteLine($"THREAD [{ThreadID}] READ VALUE [{Entity.EntityValue}] !");

						Console.WriteLine($"THREAD [{ThreadID}] WAITING STARTED !");

						Thread.Sleep(SleepTime);

						Console.WriteLine($"THREAD [{ThreadID}] WAITING FINISHED !");

						Entity.EntityValue+=ValueToAdd;

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
		public static void UpdateEntityTimestampsFluentAPIThread(int EntityID, int ValueToAdd, int SleepTime)
		{
			int													ThreadID=Thread.CurrentThread.ManagedThreadId;

			try
			{
				DbContextOptionsBuilder<CDBContext>				OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

				OptionsBuilder.UseSqlServer(MConnectionString_SQL_SERVER);

				DbContextOptions<CDBContext>					Options=OptionsBuilder.Options;

				using(CDBContext Context=new CDBContext(Options))
				{
					try
					{
						CEntityTimestampsFluentAPI				Entity=Context.EntitiesTimestampsFluentAPI.Where(P => P.EntityID==EntityID).First();

						Console.WriteLine($"THREAD [{ThreadID}] READ VALUE [{Entity.EntityValue}] !");

						Console.WriteLine($"THREAD [{ThreadID}] WAITING STARTED !");

						Thread.Sleep(SleepTime);

						Console.WriteLine($"THREAD [{ThreadID}] WAITING FINISHED !");

						Entity.EntityValue+=ValueToAdd;

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

			OptionsBuilder.UseSqlServer(MConnectionString_SQL_SERVER);

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

			OptionsBuilder.UseSqlServer(MConnectionString_SQL_SERVER);

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
		private void ExecuteCommandGetEntitiesTimestampsDataAnnotations(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlServer(MConnectionString_SQL_SERVER);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityTimestampsDataAnnotations[]			Entities=Context.EntitiesTimestampsDataAnnotations.ToArray();

					CEntityTimestampsDataAnnotations.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetEntitiesTimestampsFluentAPI(string CommandID, object[] Parameters)
		{
			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlServer(MConnectionString_SQL_SERVER);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityTimestampsFluentAPI[]				Entities=Context.EntitiesTimestampsFluentAPI.ToArray();

					CEntityTimestampsFluentAPI.PrintToConsole(Entities);
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}] !");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateTimestampsDataAnnotations(string CommandID, object[] Parameters)
		{
			int													ID;

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlServer(MConnectionString_SQL_SERVER);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			Console.WriteLine("BEFORE UPDATE:");

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityTimestampsDataAnnotations			Entity=Context.EntitiesTimestampsDataAnnotations.First();

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

			Thread												Thread1=new Thread(P => UpdateEntityTimestampsDataAnnotationsThread(ID,10,500));
			Thread												Thread2=new Thread(P => UpdateEntityTimestampsDataAnnotationsThread(ID,20,1000));

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
					CEntityTimestampsDataAnnotations			Entity=Context.EntitiesTimestampsDataAnnotations.First();

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
		private void ExecuteCommandUpdateTimestampsFluentAPI(string CommandID, object[] Parameters)
		{
			int													ID;

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlServer(MConnectionString_SQL_SERVER);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			Console.WriteLine("BEFORE UPDATE:");

			using(CDBContext Context=new CDBContext(Options))
			{
				try
				{
					CEntityTimestampsFluentAPI					Entity=Context.EntitiesTimestampsFluentAPI.First();

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

			Thread												Thread1=new Thread(P => UpdateEntityTimestampsFluentAPIThread(ID,10,500));
			Thread												Thread2=new Thread(P => UpdateEntityTimestampsFluentAPIThread(ID,20,1000));

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
					CEntityTimestampsFluentAPI					Entity=Context.EntitiesTimestampsFluentAPI.First();

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
			CommandsCollection.Add(new CMenuCommand("1","GET ALL TIMESTAMPS DATA ANNOTATIONS",new EMenuCommandParameterType[0],ExecuteCommandGetEntitiesTimestampsDataAnnotations));
			CommandsCollection.Add(new CMenuCommand("2","GET ALL TIMESTAMPS FLUENT API",new EMenuCommandParameterType[0],ExecuteCommandGetEntitiesTimestampsFluentAPI));
			CommandsCollection.Add(new CMenuCommand("3","UPDATE TIMESTAMPS DATA ANNOTATIONS",new EMenuCommandParameterType[0],ExecuteCommandUpdateTimestampsDataAnnotations));
			CommandsCollection.Add(new CMenuCommand("4","UPDATE TIMESTAMPS FLUENT API",new EMenuCommandParameterType[0],ExecuteCommandUpdateTimestampsFluentAPI));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------