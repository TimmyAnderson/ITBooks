﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace BottomUpParsing
{
//-------------------------------------------------------------------------------------------------------
	public class CInputChar_OneOrMoreCharacters : CInputChar
	{
//-------------------------------------------------------------------------------------------------------
		private readonly char[]									MCharacters;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInputChar_OneOrMoreCharacters(string Name, char Character)
			: base(Name)
		{
			MCharacters=new char[]{Character};
		}
//-------------------------------------------------------------------------------------------------------
		public CInputChar_OneOrMoreCharacters(string Name, char[] Characters)
			: base(Name)
		{
			MCharacters=Characters;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool IsValidChar(char CharToCheck)
		{
			if (MCharacters.Contains(CharToCheck)==true)
				return(true);
			else
				return(false);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------