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
	public sealed class CMenuLINQOperations : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									MConnectionString_SQLITE=@"Data Source=MyDatabase.db";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuLINQOperations()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static int Write(int Value, string Text)
		{
			CConsoleHelpers.WriteLine($"ITERATING [{Text}] - VALUE [{Value}] !",ConsoleColor.Red);

			return(Value);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static string CustomCode(string Value, int NumberOfCharacters)
		{
			string												Result=Value.Substring(0,NumberOfCharacters).ToString();

			return(Result);
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
		private void ExecuteCommandTestQuery(string CommandID, object[] Parameters)
		{
			CConsoleHelpers.WriteLineSeparator();

			int[]												Numbers=new int[]{4,2,5,1,3};
			IEnumerable<int>									Results=Numbers.Where(P => P>3).OrderBy(P => P);

			foreach(int Number in Results)
			{
				Console.WriteLine($"VALUE [{Number}] !");
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestLinqWithLogging(string CommandID, object[] Parameters)
		{
			CConsoleHelpers.WriteLineSeparator();

			int[]												Numbers=new int[]{4,2,5,1,3};
			IEnumerable<int>									Results=Numbers.Select(P => Write(P,"BEFORE WHERE")).Where(P => P>3).Select(P => Write(P,"AFTER WHERE")).OrderBy(P => P);

			Console.WriteLine($"BEFORE FOREACH !");

			foreach(int Number in Results)
			{
				Console.WriteLine($"VALUE [{Number}] !");
			}

			Console.WriteLine($"BEFORE FOREACH !");

			CConsoleHelpers.WriteLineSeparator();
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestClientVSServerEvaluation(string CommandID, object[] Parameters)
		{
			CConsoleHelpers.WriteLineSeparator();

			DbContextOptionsBuilder<CDBContext>					OptionsBuilder=new DbContextOptionsBuilder<CDBContext>();

			OptionsBuilder.UseSqlite(MConnectionString_SQLITE);

			DbContextOptions<CDBContext>						Options=OptionsBuilder.Options;

			try
			{
				using(CDBContext Context=new CDBContext(Options))
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
				using(CDBContext Context=new CDBContext(Options))
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
				using(CDBContext Context=new CDBContext(Options))
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
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("cdb","CREATE DB",new EMenuCommandParameterType[0],ExecuteCommandCreateDatabase));
			CommandsCollection.Add(new CMenuCommand("ddb","DELETE DB",new EMenuCommandParameterType[0],ExecuteCommandDeleteDatabase));
			CommandsCollection.Add(new CMenuCommand("1","TEST QUERY",new EMenuCommandParameterType[0],ExecuteCommandTestQuery));
			CommandsCollection.Add(new CMenuCommand("2","TEST LINQ WITH LOGGING",new EMenuCommandParameterType[0],ExecuteCommandTestLinqWithLogging));
			CommandsCollection.Add(new CMenuCommand("3","TEST CLIENT VS SERVER EVALUATION",new EMenuCommandParameterType[0],ExecuteCommandTestClientVSServerEvaluation));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------