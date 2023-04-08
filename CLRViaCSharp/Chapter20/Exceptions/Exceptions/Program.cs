using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Runtime.ExceptionServices;
using System.Runtime.Serialization;
using System.IO;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace Exceptions
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Handler pre UNHANDLED EXCEPTIONS.
		private static void CurrentDomain_UnhandledException(object Sender, UnhandledExceptionEventArgs E)
		{
			Console.WriteLine(string.Format("EXCEPTION HANDLER - IsTerminating: [{0}], ExceptionObject: [{1}] !",E.IsTerminating,E.ExceptionObject));

			Console.WriteLine("\nEXCEPTION HANDLER - Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		// Tento handler je zavolany PRED ZACIATKOM HLADANIA EXCEPTION FILTER.
		private static void CurrentDomain_FirstChanceException(object Sender, FirstChanceExceptionEventArgs E)
		{
			Console.WriteLine(string.Format("!!! FirstChanceException: [{0}] !",E.Exception));
		}
//-------------------------------------------------------------------------------------------------------
		private static void ExceptionMethodLevel1()
		{
			try
			{
				ExceptionMethodLevel2();
			}
			catch(Exception E)
			{
				throw(new Exception("LEVEL 1 EXCEPTION !",E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void ExceptionMethodLevel2()
		{
			try
			{
				ExceptionMethodLevel3();
			}
			catch(Exception E)
			{
				throw(new Exception("LEVEL 2 EXCEPTION !",E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void ExceptionMethodLevel3()
		{
			throw(new Exception("LEVEL 3 EXCEPTION !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void MethodLevel1_NewException()
		{
			try
			{
				MethodLevel2();
			}
			catch(Exception E)
			{
				throw(new Exception("LEVEL 1 EXCEPTION !",E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void MethodLevel1_RethrowException()
		{
			try
			{
				MethodLevel2();
			}
			catch
			{
				// Zachova sa povodny STACK TRACE.
				throw;
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void MethodLevel2()
		{
			throw(new Exception("LEVEL 2 EXCEPTION !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void ThreadFunctionNoCatchAbort(object Param)
		{
			try
			{
				Console.WriteLine("Working thread - TRY 1 !");
				
				try
				{
					throw(new Exception("SOME EXCEPTION !"));
				}
				// !!!!! THREAD v CATCH BLOCK NEMOZE BYT ABORTED.
				catch
				{
					Console.WriteLine("Working thread - CATCH - BEFORE WAIT !");

					Thread.Sleep(5000);

					Console.WriteLine("Working thread - CATCH - AFTER WAIT !");
				}

				// !!!!! Az tu je THREAD ABORTED, pretoze vo FINNALY bloku NEMOZE BYT THREAD ABORTED.
				Console.WriteLine("Working thread - TRY 2 !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void ThreadFunctionNoFinallyAbort(object Param)
		{
			try
			{
				Console.WriteLine("Working thread - TRY 1 !");
				
				try
				{
				}
				// !!!!! THREAD vo FINALLY BLOCK NEMOZE BYT ABORTED.
				finally
				{
					Console.WriteLine("Working thread - FINALLY - BEFORE WAIT !");

					Thread.Sleep(5000);

					Console.WriteLine("Working thread - FINALLY - AFTER WAIT !");
				}

				// !!!!! Az tu je THREAD ABORTED, pretoze vo FINNALY bloku NEMOZE BYT THREAD ABORTED.
				Console.WriteLine("Working thread - TRY 2 !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void ThreadAbortFunction(object Param)
		{
			try
			{
				Console.WriteLine("WORKING THREAD - TRY 1 !");
				
				Thread.Sleep(10000);

				// !!!!! CODE sa sem nedostane, pretoze bude ABORTED.
				Console.WriteLine("WORKING THREAD - TRY 2 !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("WORKING THREAD - EXCEPTION: [{0}] !",E.Message));
			}
			finally
			{
				// !!! FINALLY BLOCK bude EXECUTED, aj ked bol THREAD ABORTED.
				Console.WriteLine(string.Format("WORKING THREAD - FINALLY BLOCK EXECUTED !"));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Console.WriteLine("BEFORE TRY !");

			try
			{
				Console.WriteLine("INSIDE TRY 1 !");
				
				int												X=100;
				int												Y=0;
				int												ReturnValue=X/Y;

				Console.WriteLine(string.Format("ReturnValue: [{0}] !",ReturnValue));

				Console.WriteLine("INSIDE TRY 2 !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("INSIDE CATCH - [{0}] !",E.Message));
			}
			finally
			{
				Console.WriteLine("INSIDE FINALLY !");
			}

			Console.WriteLine("AFTER FINALLY !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			try
			{
				int												X=100;
				int												Y=0;
				int												ReturnValue=X/Y;

				Console.WriteLine(string.Format("ReturnValue: [{0}] !",ReturnValue));
			}
			catch(ArgumentException E)
			{
				Console.WriteLine(string.Format("ArgumentException - [{0}] !",E.Message));
			}
			// Tento EXCEPTION BLOCK zachytava VSETKY EXCEPTIONS.
			catch
			{
				Console.WriteLine("GENERIC EXCEPTION HANDLER called !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			// Tento EVENT sa vyvola PRED ZACIATKOM HLADANIA EXCEPTION FILTER.
			AppDomain.CurrentDomain.FirstChanceException+=new EventHandler<FirstChanceExceptionEventArgs>(CurrentDomain_FirstChanceException);

			Console.WriteLine("BEFORE TRY !");

			try
			{
				Console.WriteLine("INSIDE TRY 1 !");
				
				int												X=100;
				int												Y=0;
				int												ReturnValue=X/Y;

				Console.WriteLine(string.Format("Ret: [{0}] !",ReturnValue));

				Console.WriteLine("INSIDE TRY 2 !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("INSIDE CATCH - [{0}] !",E.Message));
			}
			finally
			{
				Console.WriteLine("INSIDE FINALLY !");
			}

			Console.WriteLine("AFTER FINALLY !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Thread												T=new Thread(ThreadAbortFunction);

			T.Start();

			// Pockam kym THREAD NABEHNE.
			Thread.Sleep(500);

			Console.WriteLine("THREAD ABORTING...");

			// Vykonam ABORT.
			T.Abort();

			T.Join();

			Console.WriteLine("THREAD ABORTED !!!");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Sposobi PAD PROGRAMU.
		private static void Test5()
		{
			try
			{
				// !!! Zabrani vykonaniu FINALLY BLOCKS.
				// Zapise informaciu do EVENT LOG.
				Environment.FailFast("PROCESS is DEAD !!!",new Exception("I'm DEAD !"));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION - [{0}] !",E.Message));
			}
			finally
			{
				// !!! Tento CODE sa NEVYKONA.
				Console.WriteLine(string.Format("FINALLY BLOCK EXECUTED !"));
				Console.ReadLine();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			try
			{
				try
				{
					throw(new Exception("This is EXCEPTION 1 !"));
				}
				finally
				{
					// !!! Hodenim EXCEPTION vo FINALLY BLOCK sa informacia o POVODNEJ EXCEPTION STRATI.
					throw(new Exception("This is EXCEPTION 2 !"));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION - [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			try
			{
				MethodLevel1_NewException();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("OUTER: [MESSAGE: [{0}]!\nSTACK TRACE: [{1}]]!\nBASE EXCEPTION [{2}] !",E.Message,E.StackTrace,E.GetBaseException()));
				Console.WriteLine();
				Console.WriteLine(string.Format("INNER: [MESSAGE: [{0}]!\nSTACK TRACE: [{1}]]!\nBASE EXCEPTION [{2}] !",E.InnerException.Message,E.InnerException.StackTrace,E.InnerException.GetBaseException()));
			}

			Console.WriteLine();

			try
			{
				MethodLevel1_RethrowException();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("OUTER: [MESSAGE: [{0}] !\nSTACK TRACE: [{1}]]!\nBASE EXCEPTION [{2}] !",E.Message,E.StackTrace,E.GetBaseException()));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			try
			{
				ExceptionMethodLevel1();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("OUTER: [MESSAGE: [{0}]!\nSTACK TRACE: [{1}]]!\nBASE EXCEPTION [{2}] !",E.Message,E.StackTrace,E.GetBaseException()));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			Console.WriteLine("".PadLeft(79,'-'));

			try
			{
				CStringExceptionDetail							Detail=new CStringExceptionDetail("HELLO WORLD !");
				CGenericException<CStringExceptionDetail>		MyException=new CGenericException<CStringExceptionDetail>(Detail,"Some BIG EXCEPTION !");

				throw(MyException);
			}
			catch(CGenericException<CStringExceptionDetail> E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}], Param: [{1}] !",E,E.ExceptionParam));
			}

			Console.WriteLine("".PadLeft(79,'-'));

			try
			{
				CStringExceptionDetail							Detail=new CStringExceptionDetail("HELLO WORLD !");
				CGenericException<CStringExceptionDetail>		MyException=new CGenericException<CStringExceptionDetail>(Detail,"Some BIG EXCEPTION !");
				DataContractSerializer							Serializer=new DataContractSerializer(typeof(CGenericException<CStringExceptionDetail>),new Type[]{typeof(CStringExceptionDetail)});

				MemoryStream									MS=new MemoryStream();

				// Serializujem CUSTOM EXCEPTION.
				Serializer.WriteObject(MS,MyException);

				MS.Seek(0,SeekOrigin.Begin);

				CGenericException<CStringExceptionDetail>		MyDeserializedException;
				DataContractSerializer							Deserializer=new DataContractSerializer(typeof(CGenericException<CStringExceptionDetail>),new Type[]{typeof(CStringExceptionDetail)});
				
				// Deserializujem CUSTOM EXCEPTION.
				MyDeserializedException=(CGenericException<CStringExceptionDetail>) Deserializer.ReadObject(MS);

				throw(MyDeserializedException);
			}
			catch(CGenericException<CStringExceptionDetail> E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}], Param: [{1}] !",E,E.ExceptionParam));
			}

			Console.WriteLine("".PadLeft(79,'-'));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			Thread												T=new Thread(ThreadFunctionNoCatchAbort);

			T.Start();

			// Pockam kym THREAD NABEHNE.
			Thread.Sleep(500);

			Console.WriteLine("THREAD ABORTING...");

			// Vykonam ABORT.
			T.Abort();

			T.Join();

			Console.WriteLine("THREAD ABORTED !!!");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			Thread												T=new Thread(ThreadFunctionNoFinallyAbort);

			T.Start();

			// Pockam kym THREAD NABEHNE.
			Thread.Sleep(500);

			Console.WriteLine("THREAD ABORTING...");

			// Vykonam ABORT.
			T.Abort();

			T.Join();

			Console.WriteLine("THREAD ABORTED !!!");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			Console.WriteLine("".PadLeft(79,'-'));

			CMyList												Names=new CMyList(new string[]{"Timmy","Jenny","Atreyu"});

			// Na konci enumerovania sa vola IEnumerator<T>.Dispose().
			foreach(string Name in Names)
			{
				Console.WriteLine(string.Format("Name: [{0}] !",Name));
			}

			Console.WriteLine("".PadLeft(79,'-'));

			try
			{
				// !!! Na konci enumerovania sa vola IEnumerator<T>.Dispose() - vo FINALLY BLOCK.
				foreach(string Name in Names)
				{
					Console.WriteLine(string.Format("Name: [{0}] !",Name));

					throw(new Exception("Enumeration ABORTED !"));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("".PadLeft(79,'-'));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			try
			{
				Exception										NewException=new Exception("Some EXCEPTION !");
				
				// CUSTOM DATA v EXCEPTION.
				NewException.Data.Add("Name","Timmy Anderson");
				NewException.Data.Add("Age","12");

				throw(NewException);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));

				foreach(object Key in E.Data.Keys)
				{
					Console.WriteLine(string.Format("\tKEY: [{0}] - VALUE [{1}] !",Key,E.Data[Key]));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Sposobi PAD PROGRAMU.
		private static void Test14()
		{
			AppDomain.CurrentDomain.UnhandledException+=new UnhandledExceptionEventHandler(CurrentDomain_UnhandledException);

			// Hodim UNHANDLED EXCEPTION. ERROR sa zapise do WINDOWS LOG, ale iba ak sa PROGRAM nespusti z VISUAL STUDIO.
			throw(new Exception("This EXCEPTION WILL NOT BE HANDLED !"));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			//Test6();
			//Test7();
			//Test8();
			//Test9();
			//Test10();
			//Test11();
			//Test12();
			//Test13();
			Test14();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------