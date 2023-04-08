using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ManagedReaderWriterLocks
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static int						MReaderThread1Wait;
		private static int						MReaderThread2Wait;
		private static int						MReaderThread3Wait;
		private static int						MWriterThreadWait;
		private static int						MUpgradableThreadWait;
		private static bool						MUpgradable=true;
//------------------------------------------------------------------------------
		private static ReaderWriterLockSlim		MRWSL=new ReaderWriterLockSlim();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void ReaderThread1()
		{
			Console.WriteLine("ReaderThread 111 STARED !");

			Thread.Sleep(MReaderThread1Wait);

			Console.WriteLine("ReaderThread 111 wants to acquire READER LOCK !");

			MRWSL.EnterReadLock();

			try
			{
				Console.WriteLine("ReaderThread 111 READER LOCK IS LOCKED !");

				Thread.Sleep(3*1000);
			}
			catch
			{
			}
			finally
			{
				Console.WriteLine("ReaderThread 111 READER LOCK WILL BE RELEASED !");
				MRWSL.ExitReadLock();
			}

			Console.WriteLine("ReaderThread 111 FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void ReaderThread2()
		{
			Console.WriteLine("ReaderThread 222 STARED !");

			Thread.Sleep(MReaderThread2Wait);

			Console.WriteLine("ReaderThread 222 wants to acquire READER LOCK !");

			MRWSL.EnterReadLock();

			try
			{
				Console.WriteLine("ReaderThread 222 READER LOCK IS LOCKED !");

				Thread.Sleep(3*1000);
			}
			catch
			{
			}
			finally
			{
				Console.WriteLine("ReaderThread 222 READER LOCK WILL BE RELEASED !");
				MRWSL.ExitReadLock();
			}

			Console.WriteLine("ReaderThread 222 FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void ReaderThread3()
		{
			Console.WriteLine("ReaderThread 333 STARED !");

			Thread.Sleep(MReaderThread3Wait);

			Console.WriteLine("ReaderThread 333 wants to acquire READER LOCK !");

			MRWSL.EnterReadLock();

			try
			{
				Console.WriteLine("ReaderThread 333 READER LOCK IS LOCKED !");

				Thread.Sleep(3*1000);
			}
			catch
			{
			}
			finally
			{
				Console.WriteLine("ReaderThread 333 READER LOCK WILL BE RELEASED !");
				MRWSL.ExitReadLock();
			}

			Console.WriteLine("ReaderThread 333 FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void WriterThread()
		{
			Console.WriteLine("WriterThread STARED !");

			Thread.Sleep(MWriterThreadWait);

			Console.WriteLine("WriterThread wants to acquire WRITER LOCK !");

			MRWSL.EnterWriteLock();

			try
			{
				Console.WriteLine("WriterThread WRITER LOCK IS LOCKED !");

				Thread.Sleep(3*1000);
			}
			catch
			{
			}
			finally
			{
				Console.WriteLine("WriterThread WRITER LOCK WILL BE RELEASED !");
				MRWSL.ExitWriteLock();
			}

			Console.WriteLine("WriterThread FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void UpgradeableThread()
		{
			Console.WriteLine("UpgradeableThread STARED !");

			Thread.Sleep(MUpgradableThreadWait);

			Console.WriteLine("UpgradeableThread wants to acquire UPGRADABLE LOCK !");

			bool					MustReleaseUpgradeableLock=true;

			MRWSL.EnterUpgradeableReadLock();

			try
			{
				Console.WriteLine("UpgradeableThread UPGRADABLE LOCK IS LOCKED !");

				if (MUpgradable==true)
				{
					Console.WriteLine("UpgradeableThread is trying to UPGRADE LOCK !");

					// POKUSAM SA o UPGRADE.
					MRWSL.EnterWriteLock();

					try
					{
						Console.WriteLine("WriterThread UPGRADABLE LOCK is UPGRADED !");
						Thread.Sleep(3*1000);
					}
					finally
					{
						Console.WriteLine("UpgradeableThread UPGRADED LOCK WILL BE RELEASED !");
						MRWSL.ExitWriteLock();
					}
				}
				else
				{
					Console.WriteLine("UpgradeableThread is trying to DOWNGRADE LOCK !");

					// VYKONAM DOWNGRADE.
					MRWSL.EnterReadLock();

					Console.WriteLine("UpgradeableThread UPGRADABLE LOCK WILL BE RELEASED !");

					// !!!!! Kedze teraz uz som v SHARED LOCK - MUSIM UVOLNIT UPGRADABLE LOCK, aby OSTATNE THREADS NEBOLI BLOKOVANE.
					MRWSL.ExitUpgradeableReadLock();
					MustReleaseUpgradeableLock=false;

					try
					{
						Console.WriteLine("WriterThread UPGRADABLE LOCK is DOWNGRADED !");
						Thread.Sleep(3*1000);
					}
					finally
					{
						Console.WriteLine("UpgradeableThread DOWNGRADED LOCK WILL BE RELEASED !");
						MRWSL.ExitReadLock();
					}
				}
			}
			catch
			{
			}
			finally
			{
				if (MustReleaseUpgradeableLock==true)
				{
					Console.WriteLine("UpgradeableThread UPGRADABLE LOCK WILL BE RELEASED !");
					MRWSL.ExitUpgradeableReadLock();
				}
			}

			Console.WriteLine("UpgradeableThread FINISHED !");
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test()
		{
			MReaderThread1Wait=100;
			MReaderThread2Wait=100;
			MReaderThread3Wait=500;
			MWriterThreadWait=1000;
			MUpgradableThreadWait=300;

			Thread[]			T=new Thread[5];

			T[0]=new Thread(ReaderThread1);
			T[1]=new Thread(ReaderThread2);
			T[2]=new Thread(ReaderThread3);
			T[3]=new Thread(WriterThread);
			T[4]=new Thread(UpgradeableThread);

			for (int i=0;i<5;i++)
				T[i].Start();

			for (int i=0;i<5;i++)
				T[i].Join();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------