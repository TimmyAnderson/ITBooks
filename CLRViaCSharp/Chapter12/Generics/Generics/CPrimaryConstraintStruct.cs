﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Generics
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CPrimaryConstraintStruct<TType> where TType : struct
	{
//-------------------------------------------------------------------------------------------------------
		public void PrintType()
		{
			Console.WriteLine(string.Format("METHOD PrintType() from TYPE [{0}] CALLED !",GetType()));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------