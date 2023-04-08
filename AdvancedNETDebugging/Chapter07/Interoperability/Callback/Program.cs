using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace Callback
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
        public delegate void Callback(int Result);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        [DllImport("MyNative.dll")]
        private static extern void AsyncProcess(Callback callBack);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public static void MyCallback(int Result)
        {
            Console.WriteLine(string.Format("Result=[{0}] !",Result)); 
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			// !!!!! CALLBACK delegate musi byt VZDY PINNED, inak sa vystavujem riziku, ze GC presunie jeho poziciu a NATIVE CODE pri volani CALLBACK bude volat adresu na ktorej UZ NEBUDE DELEGATE.
            Callback				C=new Callback(MyCallback);

            AsyncProcess(C);

            Console.WriteLine("AsyncProcess() CALLED !");

            // Do additional work.

			// !!! Umyselne vymazem CALLBACK (simulujem spustenie GC) a po spusteni GC prestane existovat. Vysledkom je EXCEPTION.
			// !!!!! Riesenim je ze CALLBACK objekt musi byt VZDY PINNED.
            C=null;
            GC.Collect();

            Console.WriteLine("Press any key to exit !");
            Console.ReadKey();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------