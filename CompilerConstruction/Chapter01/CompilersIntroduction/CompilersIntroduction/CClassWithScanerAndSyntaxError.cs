﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CompilersIntroduction
{
//-------------------------------------------------------------------------------------------------------
	public class CClassWithScanerAndSyntaxError
	{
//-------------------------------------------------------------------------------------------------------
		public void SomeMethod1()
		{
			// Hodim tu znak, ktory C# nepozna.
			$;

			// Tuto chybu kompilator VOBEC NEZACHYTI.
			intx			i=0;
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeMethod2()
		{
			// Vykonam SYNTAKTICKU chybu.
			if )1==1(
			{

			}
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeMethod3()
		{
			// !!! Ani tuto chybu uz kompilator NEZACHYTI.
			intx			i=0;
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------