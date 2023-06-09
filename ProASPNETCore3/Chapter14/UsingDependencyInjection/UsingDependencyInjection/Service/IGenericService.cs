﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Service
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! DEPENDENCY INJECTION FRAMEWORK umoznuje registrovat GENERIC TYPES ako SERVICES.
	public interface IGenericService<TType>
	{
//----------------------------------------------------------------------------------------------------------------------
		TType GetValue();
		void SetValue(TType Value);
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------