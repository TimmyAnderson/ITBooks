using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.EntityFrameworkCore;
using Helpers;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedFeaturesAndConcurrencySqlServer
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CUserDefinedFunctions
	{
//----------------------------------------------------------------------------------------------------------------------
		/*
		// !!!!! DATA ANNOTATION ATTRIBUTE [DbFunction] moze byt pouzity IBA ak je METHOD definovana v DB CONTEXT CLASS.
		[DbFunction]
		public static int CustomClassUserDefinedFunctionAddValueDataAnnotations(int Value1, int Value2)
		{
			// !!!!! FUNCTION BODY sa NIKDY NEVOLA.

			return(0);
		}
		*/
//----------------------------------------------------------------------------------------------------------------------
		public static int CustomClassUserDefinedFunctionAddValueFluentAPI(int Value1, int Value2)
		{
			// !!!!! FUNCTION BODY sa NIKDY NEVOLA.

			return(0);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------