﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace PartialMethods
{
//-------------------------------------------------------------------------------------------------------
	public partial class CMyClass
	{
//-------------------------------------------------------------------------------------------------------
		partial void PartialMethod1()
		{
			Console.WriteLine("CMyClass.PartialMethod1() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------