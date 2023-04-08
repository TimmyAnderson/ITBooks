using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Finalizer
{
//-------------------------------------------------------------------------------------------------------
	class CData
	{
//-------------------------------------------------------------------------------------------------------
		private MyCOMLib.BasicMathClass 						MData;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public CData(MyCOMLib.BasicMathClass Data)
        {
			// Je to STA COM OBJEKT zdielany so SEKUNDARNYM THREADOM.
            MData=Data;

			Console.WriteLine(string.Format("CData.CData() - Hash: [{0}] !",MData.GetHashCode()));
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        ~CData()
        {
            int				Result;

			Console.WriteLine(string.Format("CData.~CData() - Hash: [{0}] !",MData.GetHashCode()));

			Console.WriteLine("~CData() - 111 !!!");

			// !!! Pouziva INSTANCIU MyCOMLib.BasicMathClass na ktoru sa ODKAZUJE aj z INEHO THREADU.
			// !!!!! Kedze ten THREAD je STA a NECITA WINDOWS QUEUE (je v Sleep()), tak funkcia Add(), ktora MUSI BYT pre STA COM objekty serializovana cez WINDOWS QUEUE, dojde k STVRDNUTIU FINALIZER THREADU.
            MData.Add(1, 2, out Result);

			// Tu sa uz kod NIKDY NEDOSTANE.
			Console.WriteLine("~CData() - 222 !!!");
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------