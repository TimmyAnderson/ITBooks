using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
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
					throw(new CCompilerException("INVALID VALUE !"));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static int EXT_GetSizeof(this ESymbolType Value, EVariableType VariableType)
		{
			if (VariableType!=EVariableType.E_VT_POINTER && VariableType!=EVariableType.E_VT_VALUE)
			{
				throw(new CCompilerException("INVALID VALUE of EVariableType !"));
			}

			switch(Value)
			{
				case ESymbolType.E_ST_INT:
				{
					return(CSymbolTableData_Variable.INT_SIZE);
				}

				case ESymbolType.E_ST_STRING:
				{
					return(CSymbolTableData_Variable.POINTER_SIZE);
				}

				case ESymbolType.E_ST_INT_ARRAY:
				{
					if (VariableType==EVariableType.E_VT_VALUE)
					{
						// Vracia velkost iba 1 ITEM, kedze volajuca funkcia si tuto hodnotu vynasobi poctom ITEMS.
						return(CSymbolTableData_Variable.INT_SIZE);
					}
					else
					{
						return(CSymbolTableData_Variable.POINTER_SIZE);
					}
				}

				case ESymbolType.E_ST_STRING_ARRAY:
				{
					if (VariableType==EVariableType.E_VT_VALUE)
					{
						// Vracia velkost iba 1 ITEM, kedze volajuca funkcia si tuto hodnotu vynasobi poctom ITEMS.
						return(CSymbolTableData_Variable.POINTER_SIZE);
					}
					else
					{
						return(CSymbolTableData_Variable.POINTER_SIZE);
					}
				}

				default:
				{
					throw(new CCompilerException("INVALID VALUE !"));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static string EXT_GetCodeGenerationTypeName(this ESymbolType Value)
		{
			switch(Value)
			{
				case ESymbolType.E_ST_INT:
				{
					return("DWORD");
				}

				case ESymbolType.E_ST_STRING:
				{
					return("DWORD");
				}

				case ESymbolType.E_ST_INT_ARRAY:
				{
					return("DWORD");
				}

				case ESymbolType.E_ST_STRING_ARRAY:
				{
					return("DWORD");
				}

				default:
				{
					throw(new CCompilerException("INVALID VALUE !"));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static ESymbolType EXT_GetNonArraySymbolType(this ESymbolType Value)
		{
			switch(Value)
			{
				case ESymbolType.E_ST_INT_ARRAY:
				{
					return(ESymbolType.E_ST_INT);
				}

				case ESymbolType.E_ST_STRING_ARRAY:
				{
					return(ESymbolType.E_ST_STRING);
				}

				case ESymbolType.E_ST_VOID_ARRAY:
				{
					return(ESymbolType.E_ST_VOID);
				}

				default:
				{
					throw(new CCompilerException("INVALID VALUE !"));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------