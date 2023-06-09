﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public interface ISimpleChildProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		CSimpleChild AddChild(CSimpleChild Child);
		CSimpleChild UpdateChild(CSimpleChild Child);
		void RemoveChild(int ID);
		CSimpleChild GetChild(int ID);
		CSimpleChild[] GetChildren();
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------