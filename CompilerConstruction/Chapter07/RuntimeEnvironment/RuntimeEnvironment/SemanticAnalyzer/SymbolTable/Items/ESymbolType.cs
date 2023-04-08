using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public enum ESymbolType
	{
//-------------------------------------------------------------------------------------------------------
		E_ST_ERROR=0,
//-------------------------------------------------------------------------------------------------------
		E_ST_VOID=1,
		E_ST_INT=2,
		E_ST_STRING=3,
		E_ST_INT_ARRAY=4,
		E_ST_STRING_ARRAY=5,
		// Len pre uplnost. Programovaci jazyk tento typ NEUMOZNUJE.
		E_ST_VOID_ARRAY=6,
		E_ST_FUNCTION=7,
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	public static class CSymbolTypeExtensions
	{
//-------------------------------------------------------------------------------------------------------
		public static string EXT_GetFriendlyName(this ESymbolType Value)
		{
			switch(Value)
			{
				case ESymbolType.E_ST_VOID:
				{
					return("void");
				}

				case ESymbolType.E_ST_INT:
				{
					return("int");
				}

				case ESymbolType.E_ST_STRING:
				{
					return("string");
				}

				case ESymbolType.E_ST_INT_ARRAY:
				{
					return("int[]");
				}

				case ESymbolType.E_ST_STRING_ARRAY:
				{
					return("string[]");
				}

				case ESymbolType.E_ST_FUNCTION:
				{
					return("FUNCTION()");
				}

				default:
				{
					throw(new InvalidOperationException("INVALID VALUE !"));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static int EXT_GetSizeof(this ESymbolType Value, EVariableType VariableType)
		{
			if (VariableType!=EVariableType.E_VT_FUNCTION_PARAMETER && VariableType!=EVariableType.E_VT_LOCAL_VARIABLE)
			{
				throw(new InvalidOperationException("INVALID VALUE of EVariableType !"));
			}

			const int				INT_SIZE=4;
			const int				POINTER_SIZE=8;

			switch(Value)
			{
				case ESymbolType.E_ST_INT:
				{
					return(INT_SIZE);
				}

				case ESymbolType.E_ST_STRING:
				{
					return(POINTER_SIZE);
				}

				case ESymbolType.E_ST_INT_ARRAY:
				{
					if (VariableType==EVariableType.E_VT_LOCAL_VARIABLE)
					{
						return(INT_SIZE);
					}
					else
					{
						return(POINTER_SIZE);
					}
				}

				case ESymbolType.E_ST_STRING_ARRAY:
				{
					if (VariableType==EVariableType.E_VT_LOCAL_VARIABLE)
					{
						return(POINTER_SIZE);
					}
					else
					{
						return(POINTER_SIZE);
					}
				}

				default:
				{
					throw(new InvalidOperationException("INVALID VALUE !"));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------