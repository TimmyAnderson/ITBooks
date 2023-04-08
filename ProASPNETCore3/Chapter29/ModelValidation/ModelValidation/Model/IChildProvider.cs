﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public interface IChildProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		CChild AddChild(CChild Child);
		CChild UpdateChild(CChild Child);
		void RemoveChild(int ID);
		CChild GetChild(int ID);
		CChild[] GetChildren();
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------