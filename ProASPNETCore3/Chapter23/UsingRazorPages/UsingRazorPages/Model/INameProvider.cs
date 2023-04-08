﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingRazorPages.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public interface INameProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		CName AddName(CName Name);
		CName UpdateName(CName Name);
		void RemoveName(int ID);
		CName GetName(int ID);
		CName[] GetNames();
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------