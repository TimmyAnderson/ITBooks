using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.EntityFrameworkCore.Storage;
using Helpers;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingEFCore2
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

			CNumber												Number1=new CNumber(1,"ONE");
			CNumber												Number2=new CNumber(2,"TWO");
			CNumber												Number3=new CNumber(3,"THREE");
			CNumber												Number4=new CNumber(4,"FOUR");
			CNumber												Number5=new CNumber(5,"FIVE");
			CNumber												Number6=new CNumber(6,"SIX");
			CNumber												Number7=new CNumber(7,"SEVEN");
			CNumber												Number8=new CNumber(8,"EIGHT");
			CNumber												Number9=new CNumber(9,"NINE");
			CNumber												Number10=new CNumber(10,"TEN");

			Context.EntitiesNumbers.Add(Number1);
			Context.EntitiesNumbers.Add(Number2);
			Context.EntitiesNumbers.Add(Number3);
			Context.EntitiesNumbers.Add(Number4);
			Context.EntitiesNumbers.Add(Number5);
			Context.EntitiesNumbers.Add(Number6);
			Context.EntitiesNumbers.Add(Number7);
			Context.EntitiesNumbers.Add(Number8);
			Context.EntitiesNumbers.Add(Number9);
			Context.EntitiesNumbers.Add(Number10);
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
		public static void TestSynchronousInsertDelete()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						CNumber[]								Entities=Context.EntitiesNumbers.OrderBy(P => P.Number).IgnoreQueryFilters().ToArray();

						CNumber.PrintToConsole(Entities);
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

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CNumber									Entity1=new CNumber(111,"NEW ENTITY 111");
						CNumber									Entity2=new CNumber(222,"NEW ENTITY 222");

						Context.EntitiesNumbers.Add(Entity1);
						Context.EntitiesNumbers.Add(Entity2);

						// ENTITY FRAMEWORK CORE zapise DB RECORD do DB.
						int										NumberOfModifiedEntities=Context.SaveChanges();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=Entity1.NumberID;
							ID2=Entity2.NumberID;

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

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						CNumber[]								Entities=Context.EntitiesNumbers.OrderBy(P => P.Number).IgnoreQueryFilters().ToArray();

						CNumber.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CNumber									Entity1=Context.EntitiesNumbers.Where(P => P.NumberID==ID1).First();
						CNumber									Entity2=Context.EntitiesNumbers.Where(P => P.NumberID==ID2).First();

						Context.EntitiesNumbers.Remove(Entity1);
						Context.EntitiesNumbers.Remove(Entity2);

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

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						CNumber[]								Entities=Context.EntitiesNumbers.OrderBy(P => P.Number).IgnoreQueryFilters().ToArray();

						CNumber.PrintToConsole(Entities);
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
		// !!!!! METHODA vykonava operacia nad DB ASYNCHRONOUSLY.
		public static async Task TestAsynchronousInsertDeleteInternal()
		{
			CConsoleHelpers.WriteLineSeparator();

			int													ID1=0;
			int													ID2=0;

			try
			{
				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("BEFORE INSERT:",ConsoleColor.Cyan);

						// !!!!! Pouziva sa ASYNC API.
						CNumber[]								Entities=await Context.EntitiesNumbers.OrderBy(P => P.Number).IgnoreQueryFilters().ToArrayAsync();

						CNumber.PrintToConsole(Entities);
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

						// !!! Vytvoria sa ENTITIES a ulozia do DB v SEPARATNOM DB CONTEXT.
						CNumber									Entity1=new CNumber(111,"NEW ENTITY 111");
						CNumber									Entity2=new CNumber(222,"NEW ENTITY 222");

						Context.EntitiesNumbers.Add(Entity1);
						Context.EntitiesNumbers.Add(Entity2);

						// !!!!! Modifikacia DB je vykonana ASYNCHRONOUSLY.
						// ENTITY FRAMEWORK CORE zapise DB RECORDS do DB.
						int										NumberOfModifiedEntities=await Context.SaveChangesAsync();

						CConsoleHelpers.WriteLine("CHANGES SAVED.",ConsoleColor.Yellow);

						if (NumberOfModifiedEntities>0)
						{
							ID1=Entity1.NumberID;
							ID2=Entity2.NumberID;

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

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER INSERT:",ConsoleColor.Cyan);

						// !!!!! Pouziva sa ASYNC API.
						CNumber[]								Entities=await Context.EntitiesNumbers.OrderBy(P => P.Number).IgnoreQueryFilters().ToArrayAsync();

						CNumber.PrintToConsole(Entities);
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
						CConsoleHelpers.WriteLine("DELETING:",ConsoleColor.Cyan);

						CNumber									Entity1=Context.EntitiesNumbers.Where(P => P.NumberID==ID1).First();
						CNumber									Entity2=Context.EntitiesNumbers.Where(P => P.NumberID==ID2).First();

						Context.EntitiesNumbers.Remove(Entity1);
						Context.EntitiesNumbers.Remove(Entity2);

						// !!!!! Modifikacia DB je vykonana ASYNCHRONOUSLY.
						int										NumberOfModifiedEntities=await Context.SaveChangesAsync();

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

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER DELETE:",ConsoleColor.Cyan);

						// !!!!! Pouziva sa ASYNC API.
						CNumber[]								Entities=await Context.EntitiesNumbers.OrderBy(P => P.Number).IgnoreQueryFilters().ToArrayAsync();

						CNumber.PrintToConsole(Entities);
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
		public static void TestAsynchronousInsertDelete()
		{
			Task												AsynchronousTask=TestAsynchronousInsertDeleteInternal();

			AsynchronousTask.Wait();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        static void Main(string[] args)
        {
			//CreateTestDB();
			//TestSelectTestEntity();
			//TestSynchronousInsertDelete();
			TestAsynchronousInsertDelete();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------