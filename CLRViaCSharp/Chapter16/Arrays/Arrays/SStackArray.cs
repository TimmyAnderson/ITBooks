﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Arrays
{
//-------------------------------------------------------------------------------------------------------
	// !!! Instancie tohto VALUE TYPE su ALOKOVANE na STACK.
	public unsafe struct SStackArray
	{
//-------------------------------------------------------------------------------------------------------
		// Znaky [] sa definuju AZ ZA MENOM PREMMENEJ a MUSI za nimi nasledovat DLZKA BUFFERA, ktory sa vytvori na STACK.
		public fixed char										MArrayOnStack[1000];
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------