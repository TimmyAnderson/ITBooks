﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Constructors
{
//-------------------------------------------------------------------------------------------------------
	// !!! Kedze tento typ DEFINUJE EXPLICITNY staticky konstruktor, tak C# triedu NEOZNACI priznakom BeforeFieldInit.
	internal sealed class CPrecise
	{
//-------------------------------------------------------------------------------------------------------
        public static int										X;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        static CPrecise()
		{
			Console.WriteLine("CPrecise STATIC CONSTRUCTOR CALLED !");

			X=123;
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------