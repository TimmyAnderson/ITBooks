﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Constructors
{
//-------------------------------------------------------------------------------------------------------
	public struct SStruct
	{
//-------------------------------------------------------------------------------------------------------
		static SStruct()
		{
			Console.WriteLine("CStruct.cctor() is CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// INLINE inicializaciu pre VALUE TYPES NIE JE MOZNE ROBIT.
		//private int											MValue1=10;
		private int												MValue1;
		private int												MValue2;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		/*
		// Bezparametricky konstruktor pre VALUE TYPES NIE JE MOZNE DEFINOVAT.
		public CStruct()
		{
			MValue2=0;
			MValue2=0;
		}
		*/
//-------------------------------------------------------------------------------------------------------
		/*
		// Konstuktor pre VALUE TYPES MUSI INICIALIZOVAT VSETKY FIELDS.
		public CStruct(int Value1, int Value2)
		{
		}
		*/
//-------------------------------------------------------------------------------------------------------
		public SStruct(int Value1, int Value2)
		{
			MValue1=Value1;
			MValue2=Value2;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void ShowValues()
		{
			Console.WriteLine(string.Format("VALUES - MValue1: [{0}], MValue2: [{1}] !",MValue1,MValue2));
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("MValue1: [{0}], MValue2: [{1}] !",MValue1,MValue2));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------