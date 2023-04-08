using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.EntityFrameworkCore.Storage;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingEFCore1
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
		public static void TestTransactions()
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

				using(CDBContext Context=new CDBContext(true))
				{
					// !!! Vytvori sa nova TRANSACTION.
					using (IDbContextTransaction TransactionContext=Context.Database.BeginTransaction())
					{
						try
						{
							CConsoleHelpers.WriteLine("1. UPDATE:",ConsoleColor.Cyan);

							CConsoleHelpers.WriteLine("TRANSATCION was CREATED.",ConsoleColor.Yellow);

							CNumber								Number=Context.EntitiesNumbers.IgnoreQueryFilters().Where(P => P.NumberID==ID1).First();

							CConsoleHelpers.WriteLine("ENTITY READ from DB.",ConsoleColor.Yellow);

							// !!! STATE je nastaveny na [Unchanged].
							CDBHelpers.WriteEntityState("ENTITY NUMBER",Context,Number);

							Number.NumberAsText="MODIFIED 111 !!!";

							CConsoleHelpers.WriteLine("ENTITY MODIFIED.",ConsoleColor.Yellow);

							// !!! STATE je nastaveny na [Modified].
							CDBHelpers.WriteEntityState("ENTITY NUMBER",Context,Number);

							// !!!!! METHOD [int DbContext.SaveChanges()] vykona zapis dat do MEMORY, ale TRANSACTION sa este NEZAPISE do DB.
							int									NumberOfModifiedEntities=Context.SaveChanges();

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
							CDBHelpers.WriteEntityState("ENTITY NUMBER",Context,Number);

							// !!! TRANSACTION je COMMITTED. METHOD [void IDbContextTransaction.Commit()] vykonava OKAMZITY COMMIT danej TRANSACTION do DB.
							TransactionContext.Commit();

							CConsoleHelpers.WriteLine("TRANSACTION was COMMITED.",ConsoleColor.Yellow);

							CConsoleHelpers.WriteLine($"NUMBER ID [{Number.NumberID}] was UPDATED !",ConsoleColor.Green);

							// !!! STATE je nastaveny na [Unchanged].
							CDBHelpers.WriteEntityState("ENTITY NUMBER",Context,Number);
						}
						catch(Exception E)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);

							// !!! TRANSACTION je ROLLBACKED. METHOD [void IDbContextTransaction.Rollback()] vykona okamzity ROLLBACK TRANSACTION v DB.
							TransactionContext.Rollback();

							CConsoleHelpers.WriteLine("TRANSACTION was ROLLBACKED.",ConsoleColor.Yellow);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER 1. UPDATE:",ConsoleColor.Cyan);

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
					// !!! Vytvori sa nova TRANSACTION.
					using (IDbContextTransaction TransactionContext=Context.Database.BeginTransaction())
					{
						try
						{
							bool								ThrowException=true;

							CConsoleHelpers.WriteLine("2. UPDATE:",ConsoleColor.Cyan);

							CConsoleHelpers.WriteLine("TRANSATCION was CREATED.",ConsoleColor.Yellow);

							CNumber								Number=Context.EntitiesNumbers.IgnoreQueryFilters().Where(P => P.NumberID==ID2).First();

							CConsoleHelpers.WriteLine("ENTITY READ from DB.",ConsoleColor.Yellow);

							// !!! STATE je nastaveny na [Unchanged].
							CDBHelpers.WriteEntityState("ENTITY NUMBER",Context,Number);

							Number.NumberAsText="MODIFIED 222 !!!";

							CConsoleHelpers.WriteLine("ENTITY MODIFIED.",ConsoleColor.Yellow);

							// !!! STATE je nastaveny na [Modified].
							CDBHelpers.WriteEntityState("ENTITY NUMBER",Context,Number);

							// !!!!! METHOD [int DbContext.SaveChanges()] vykona zapis dat do MEMORY, ale TRANSACTION sa este NEZAPISE do DB.
							int									NumberOfModifiedEntities=Context.SaveChanges();

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
							CDBHelpers.WriteEntityState("ENTITY NUMBER",Context,Number);

							if (ThrowException==true)
							{
								// !!! Simuluje sa vznik EXCEPTION.
								throw(new InvalidOperationException("Something WRONG HAPPENED !"));
							}

							// !!! TRANSACTION je COMMITTED. METHOD [void IDbContextTransaction.Commit()] vykonava OKAMZITY COMMIT danej TRANSACTION do DB.
							TransactionContext.Commit();

							CConsoleHelpers.WriteLine("TRANSACTION was COMMITED.",ConsoleColor.Yellow);

							CConsoleHelpers.WriteLine($"NUMBER ID [{Number.NumberID}] was UPDATED !",ConsoleColor.Green);

							// !!! STATE je nastaveny na [Unchanged].
							CDBHelpers.WriteEntityState("ENTITY NUMBER",Context,Number);
						}
						catch(Exception E)
						{
							CConsoleHelpers.WriteLine($"EXCEPTION [{E.Message}] !",ConsoleColor.Red);

							// !!! TRANSACTION je ROLLBACKED. METHOD [void IDbContextTransaction.Rollback()] vykona okamzity ROLLBACK TRANSACTION v DB.
							TransactionContext.Rollback();

							CConsoleHelpers.WriteLine("TRANSACTION was ROLLBACKED.",ConsoleColor.Yellow);
						}
					}
				}

				CConsoleHelpers.WriteLineSeparators(3);

				using(CDBContext Context=new CDBContext())
				{
					try
					{
						CConsoleHelpers.WriteLine("AFTER 2. UPDATE:",ConsoleColor.Cyan);

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
        static void Main(string[] args)
        {
			//CreateTestDB();
			//TestSelectTestEntity();
			TestTransactions();

			Console.WriteLine("Press ENTER to EXIT !");
			Console.ReadLine();
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------