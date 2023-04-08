using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace FinalizerTest
{
//-------------------------------------------------------------------------------------------------------
	public class CLimitedResource
	{
//-------------------------------------------------------------------------------------------------------
		// Simulujem, ze CLimitedResource ma nejaky RESOURCE, ktoreho POCET MOZNYCH INSTANCII je LIMITOVANY na 3.
        private static HandleCollector							MHC=new HandleCollector("LimitedResource",0,3);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public CLimitedResource()
		{
            // Oznamenie HandleCollector, ze sa objekt CLimitedResource bol PRIDANY do PAMATE.
            MHC.Add();

            Console.WriteLine("LimitedResource CREATED - Count: [{0}] !",MHC.Count);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        ~CLimitedResource()
		{
            // Oznamenie HandleCollector, ze sa objekt CLimitedResource ODSTRANIL z PAMATE.
            MHC.Remove();

            Console.WriteLine("LimitedResource DESTROYED - Count: [{0}] !",MHC.Count);

			// Poskytne sa cas pri ukonceni programu na zobrazenie hlasky na CONSOLE.
			Thread.Sleep(1000);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------