using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Threading;
using System.Transactions;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace TransactionScope
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void InternalTransaction(TransactionScopeOption TSO)
		{
			try
			{
				using(System.Transactions.TransactionScope Scope=new System.Transactions.TransactionScope(TSO))
				{
					Transaction				T=Transaction.Current;

					Console.WriteLine(CDebugHelper.GetTransactionString(T));
					CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,"Transaction 2",T);
					Console.WriteLine(CDebugHelper.GetTransactionString(T));
					Scope.Complete();
				}
			}
			catch(TransactionAbortedException E)
			{
				// Chyba pri Dispose() - transakcia sa nevykonala - chyba pri Commit.
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			catch
			{
				// Hocijaka na chyba pri vykonavani DB operacii - Rollback.
				Console.WriteLine("Cannot complete transaction !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void SuppressedInternalTransaction()
		{
			try
			{
				using(System.Transactions.TransactionScope Scope=new System.Transactions.TransactionScope(TransactionScopeOption.Suppress))
				{
					Transaction			T=Transaction.Current;

					Console.WriteLine(CDebugHelper.GetTransactionString(T));
					CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,"Transaction 2",T);
					Console.WriteLine(CDebugHelper.GetTransactionString(T));
				}
			}
			catch(TransactionAbortedException E)
			{
				// Chyba pri Dispose() - transakcia sa nevykonala - chyba pri Commit.
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			catch
			{
				// Hocijaka na chyba pri vykonavani DB operacii - Rollback.
				Console.WriteLine("Cannot complete transaction !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			try
			{
				using(System.Transactions.TransactionScope Scope1=new System.Transactions.TransactionScope())
				{
					Transaction				T1=Transaction.Current;

					Console.WriteLine(CDebugHelper.GetTransactionString(T1));
					CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,"Transaction 1",T1);
					Console.WriteLine(CDebugHelper.GetTransactionString(T1));

					using(System.Transactions.TransactionScope Scope2=new System.Transactions.TransactionScope())
					{
						Transaction			T2=Transaction.Current;

						Console.WriteLine(CDebugHelper.GetTransactionString(T2));
						CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,"Transaction 2",T2);
						Console.WriteLine(CDebugHelper.GetTransactionString(T2));
						Scope2.Complete();
					}

					Console.WriteLine(CDebugHelper.GetTransactionString(T1));
					Scope1.Complete();
				}
			}
			catch(TransactionAbortedException E)
			{
				// Chyba pri Dispose() - transakcia sa nevykonala - chyba pri Commit.
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			catch
			{
				// Hocijaka na chyba pri vykonavani DB operacii - Rollback.
				Console.WriteLine("Cannot complete transaction !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			try
			{
				using(System.Transactions.TransactionScope Scope1=new System.Transactions.TransactionScope())
				{
					Transaction				T1=Transaction.Current;

					Console.WriteLine(CDebugHelper.GetTransactionString(T1));
					CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,"Transaction 1",T1);
					Console.WriteLine(CDebugHelper.GetTransactionString(T1));

					using(System.Transactions.TransactionScope Scope2=new System.Transactions.TransactionScope())
					{
						Transaction			T2=Transaction.Current;

						Console.WriteLine(CDebugHelper.GetTransactionString(T2));
						CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,"Transaction 2",T2);
						Console.WriteLine(CDebugHelper.GetTransactionString(T2));

						// Nerobim voting a teda dojde k Rollback.
						//Scope2.Complete();
					}

					Console.WriteLine(CDebugHelper.GetTransactionString(T1));
					Scope1.Complete();
				}
			}
			catch(TransactionAbortedException E)
			{
				// Chyba pri Dispose() - transakcia sa nevykonala - chyba pri Commit.
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			catch
			{
				// Hocijaka na chyba pri vykonavani DB operacii - Rollback.
				Console.WriteLine("Cannot complete transaction !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			try
			{
				using(System.Transactions.TransactionScope Scope=new System.Transactions.TransactionScope())
				{
					Transaction				T=Transaction.Current;

					Console.WriteLine(CDebugHelper.GetTransactionString(T));
					CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,"Transaction 1",T);
					Console.WriteLine(CDebugHelper.GetTransactionString(T));

					InternalTransaction(TransactionScopeOption.Required);
					Console.WriteLine(CDebugHelper.GetTransactionString(T));
					Scope.Complete();
				}
			}
			catch(TransactionAbortedException E)
			{
				// Chyba pri Dispose() - transakcia sa nevykonala - chyba pri Commit.
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			catch
			{
				// Hocijaka na chyba pri vykonavani DB operacii - Rollback.
				Console.WriteLine("Cannot complete transaction !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			try
			{
				using(System.Transactions.TransactionScope Scope=new System.Transactions.TransactionScope())
				{
					Transaction				T=Transaction.Current;

					Console.WriteLine(CDebugHelper.GetTransactionString(T));
					CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,"Transaction 1",T);
					Console.WriteLine(CDebugHelper.GetTransactionString(T));

					InternalTransaction(TransactionScopeOption.RequiresNew);
					Console.WriteLine(CDebugHelper.GetTransactionString(T));
					Scope.Complete();
				}
			}
			catch(TransactionAbortedException E)
			{
				// Chyba pri Dispose() - transakcia sa nevykonala - chyba pri Commit.
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			catch
			{
				// Hocijaka na chyba pri vykonavani DB operacii - Rollback.
				Console.WriteLine("Cannot complete transaction !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			try
			{
				using(System.Transactions.TransactionScope Scope=new System.Transactions.TransactionScope())
				{
					Transaction				T=Transaction.Current;

					Console.WriteLine(CDebugHelper.GetTransactionString(T));
					CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,"Transaction 1",T);
					Console.WriteLine(CDebugHelper.GetTransactionString(T));

					SuppressedInternalTransaction();
					Console.WriteLine(CDebugHelper.GetTransactionString(T));
					Scope.Complete();
				}
			}
			catch(TransactionAbortedException E)
			{
				// Chyba pri Dispose() - transakcia sa nevykonala - chyba pri Commit.
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			catch
			{
				// Hocijaka na chyba pri vykonavani DB operacii - Rollback.
				Console.WriteLine("Cannot complete transaction !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			try
			{
				using(System.Transactions.TransactionScope Scope=new System.Transactions.TransactionScope())
				{
					Transaction				T=Transaction.Current;

					Console.WriteLine(CDebugHelper.GetTransactionString(T));

					// Zahlasujem za koniec transakcie.
					Scope.Complete();

					Console.WriteLine("Waiting for 70 seconds to CANCEL TRANSACTION !");

					// Ale neurobim Dispose() - teda Commit.
					// Pri Dispose() hodi exception - TransactionAbortedException.
					Thread.Sleep(70*1000);

					Console.WriteLine(CDebugHelper.GetTransactionString(T));
				}
			}
			catch(TransactionAbortedException E)
			{
				// Chyba pri Dispose() - transakcia sa nevykonala - chyba pri Commit.
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			catch
			{
				// Hocijaka na chyba pri vykonavani DB operacii - Rollback.
				Console.WriteLine("Cannot complete transaction !");
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			// Zmaz DB.
			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_1);
			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_2);

			Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			//Test6();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------