using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace Finalizer
{
//-------------------------------------------------------------------------------------------------------
// !!!!! To co ma na tomto programe miatlo bolo, ze som si neuvedomil, ze je vytvorena IBA 1 INSTANCIA MyCOMLib.BasicMathClass a to v STA threade.
// !!!!! Kedze STA thread je v SLEEP STAVE a NECITA WINDOWS QUEUE, tak voalnie metody Add() z FINALIZER MTA THRADU je riesene zaslanim MESSAGE do skryteho WINDOW v STA THREADE. No ale kedze tento thread nic nerobi - je v Sleep() a NECITA WINDOWS QUEUE, tak Add() v CData.~CData() STVRDNE, cakajuc nato kym sa STA THREAD ROZBEHNE. Tym stvrdne aj CELA FINALIZACIA a dochadza k MEMORY LEAKS.
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
        private static MyCOMLib.BasicMathClass					MS;
        private static CWorker									MWorker;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private static void Initialize()
        {
            byte[]				B=new byte[100];

            MWorker=new CWorker();
            MWorker.ProcessData(B);

            MWorker=null;
            GC.Collect();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        static void Helper()
        {
			// !!!!! Je to JEDINA INSTANCIA MyCOMLib.BasicMathClass() v CELOM PROGRAME.
            MS=new MyCOMLib.BasicMathClass();

			Console.WriteLine(string.Format("Program.Helper() - Hash: [{0}] !",MS.GetHashCode()));

            Thread.Sleep(60000*5);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] Args)
		{
            if (Args.Length<1)
            {
                Console.WriteLine("Finalizer.exe <num iterations>");
                return;
            }

            Thread				NewThread=new Thread(new ThreadStart(Helper));

			// Tu je CHYBA. Thread v Helper() je v SLEEP stave a NEROBI citanie WINDOW QUEUE, ktora sa pouziva pri synchronizacii STA. Preto ani FINALIZER nemaze pamat, lebo caka kym sa Helper() rozbehne.
            NewThread.SetApartmentState(ApartmentState.STA);

            NewThread.IsBackground=true;
            NewThread.Start();

            Thread.Sleep(2000);

			// 
            CData				D=new CData(MS);
            
            D=null;
            GC.Collect();
            GC.Collect();

            Initialize();

            for (int i=0;i<int.Parse(Args[0]);i++)
            {
                byte[]			B=new byte[10000];
                WMI				W=new WMI(B);

                W.ProcessData();
            }

            GC.Collect();

            Console.WriteLine("Press any key to EXIT !");
            Console.ReadKey();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------