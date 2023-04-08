using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.EntityFrameworkCore;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace LINQQueries
{
//----------------------------------------------------------------------------------------------------------------------
    internal class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		private static int Write(int Value, string Text)
		{
			CConsoleHelpers.WriteLine($"ITERATING [{Text}] - VALUE [{Value}] !",ConsoleColor.Red);

			return(Value);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestQuerySyntax()
		{
			CConsoleHelpers.WriteLineSeparator();

			int[]												Numbers=new int[]{4,2,5,1,3};
			IEnumerable<int>									Results=from Number in Numbers where Number>3 orderby Number select Number;

			foreach(int Number in Results)
			{
				Console.WriteLine($"VALUE [{Number}] !");
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestMethodSyntax()
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestLINQWithLogging()
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestCustomWhereOperator()
		{
			CConsoleHelpers.WriteLineSeparator();

			int[]												Numbers=new int[]{4,2,5,1,3};

			// !!! Pouziju sa CUSTOM LINQ OPERATORS.
			IEnumerable<int>									Results=Numbers.ToLog("BEFORE CUSTOM OPERATOR").MyBigNumbersWhere().ToLog("AFTER CUSTOM OPERATOR").OrderBy(P => P);

			Console.WriteLine($"BEFORE FOREACH !");

			foreach(int Number in Results)
			{
				Console.WriteLine($"VALUE [{Number}] !");
			}

			Console.WriteLine($"BEFORE FOREACH !");

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestCustomOrderByQueryableOperator()
		{
			CConsoleHelpers.WriteLineSeparator();

			int[]												Numbers=new int[]{4,2,5,1,3};

			{
				// !!! Pouzije sa CUSTOM LINQ OPERATOR.
				IEnumerable<int>								Results1=Numbers.Where(P => P<3);
				IEnumerable<int>								Results2=Results1.MyCustomOrderByOperator(true).ToLog("AFTER CUSTOM OPERATOR");

				foreach(int Number in Results2)
				{
					Console.WriteLine($"VALUE [{Number}] !");
				}
			}

			CConsoleHelpers.WriteLineSeparator();

			{
				// !!! Pouzije sa CUSTOM LINQ OPERATOR.
				// !!! Pouzije sa OPERATOR [IQueryable<TElement> AsQueryable<TElement>(this IEnumerable<TElement> Source)].
				IQueryable<int>									Results1=Numbers.AsQueryable().Where(P => P<3);
				IEnumerable<int>								Results2=Results1.MyCustomOrderByOperator(false).ToLog("AFTER CUSTOM OPERATOR");

				foreach(int Number in Results2)
				{
					Console.WriteLine($"VALUE [{Number}] !");
				}
			}

			CConsoleHelpers.WriteLineSeparator();

			{
				// !!! Pouzije sa CUSTOM LINQ OPERATOR.
				// !!! Pouzije sa OPERATOR [IQueryable<TElement> AsQueryable<TElement>(this IEnumerable<TElement> Source)].
				IEnumerable<int>								Results=Numbers.AsQueryable().Where(P => P>3).MyCustomOrderByOperator(true);

				foreach(int Number in Results)
				{
					Console.WriteLine($"VALUE [{Number}] !");
				}
			}

			CConsoleHelpers.WriteLineSeparator();

			{
				// !!! Pouzije sa CUSTOM LINQ OPERATOR.
				// !!! Pouzije sa OPERATOR [IQueryable<TElement> AsQueryable<TElement>(this IEnumerable<TElement> Source)].
				IEnumerable<int>								Results=Numbers.AsQueryable().Where(P => P>3).MyCustomOrderByOperator(false);

				foreach(int Number in Results)
				{
					Console.WriteLine($"VALUE [{Number}] !");
				}
			}

			CConsoleHelpers.WriteLineSeparator();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void FillData(CDBContext Context)
		{
			CTestEntity											TestEntity1=new CTestEntity("XXX");
			CTestEntity											TestEntity2=new CTestEntity("YYY");

			Context.TestEntities.Add(TestEntity1);
			Context.TestEntities.Add(TestEntity2);

			CDependentEntity									DependentEntity1=new CDependentEntity("XXX 11");
			CDependentEntity									DependentEntity2=new CDependentEntity("XXX 12");
			CDependentEntity									DependentEntity3=new CDependentEntity("YYY 13");
			CDependentEntity									DependentEntity4=new CDependentEntity("YYY 14");

			CPrincipalEntity									PrincipalEntity1=new CPrincipalEntity("XXX",new CDependentEntity[]{DependentEntity1,DependentEntity2});
			CPrincipalEntity									PrincipalEntity2=new CPrincipalEntity("YYY",new CDependentEntity[]{DependentEntity3,DependentEntity4});

			Context.PrincipalEntities.Add(PrincipalEntity1);
			Context.PrincipalEntities.Add(PrincipalEntity2);
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
					CConsoleHelpers.WriteLine($"DATABASE NOT CREATED !",ConsoleColor.Red);
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
		public static void TestSelectTestEntity()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CTestEntity[]							Entities=Context.TestEntities.ToArray();

						for(int Index=0;Index<Entities.Length;Index++)
						{
							CTestEntity							Entity=Entities[Index];
							string								EntityText=Entity.Print(Index+1);
							
							if (Index>0)
							{
								CConsoleHelpers.WriteLineSeparator();
							}

							CConsoleHelpers.Write(EntityText,ConsoleColor.Green);
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
		public static void TestSelectPrincipalEntity()
		{
			CConsoleHelpers.WriteLineSeparator();

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CPrincipalEntity[]						Entities=Context.PrincipalEntities.Include(P => P.DependentEntities).ToArray();

						for(int Index=0;Index<Entities.Length;Index++)
						{
							CPrincipalEntity					Entity=Entities[Index];
							string								EntityText=Entity.Print(Index+1,0);
							
							if (Index>0)
							{
								CConsoleHelpers.WriteLineSeparator();
							}

							CConsoleHelpers.Write(EntityText,ConsoleColor.Green);
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
			//TestQuerySyntax();
			//TestMethodSyntax();
			//TestLINQWithLogging();
			//TestCustomWhereOperator();
			//TestCustomOrderByQueryableOperator();
			//CreateTestDB();
			//TestSelectTestEntity();
			TestSelectPrincipalEntity();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------