﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFormTagHelpers.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public interface INameWithNoteProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		CNameWithNote AddName(CNameWithNote Name);
		CNameWithNote UpdateName(CNameWithNote Name);
		void RemoveName(int ID);
		CNameWithNote GetName(int ID);
		CNameWithNote[] GetNames();
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------