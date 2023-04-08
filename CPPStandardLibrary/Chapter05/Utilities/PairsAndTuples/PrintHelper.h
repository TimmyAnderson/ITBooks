//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <tuple>
#include <iostream>
//-----------------------------------------------------------------------------
// NON-TEMPLATE FUNCTION, ktora ma iba 1 PARAMETER obsahujuci FORMAT STRING.
// !!! FUNCTION UKONCUJE RECURSION.
void GenericPrint(const wchar_t* FormatString)
{
	const wchar_t*												Pointer=FormatString;

	while(*Pointer!=L'\0')
	{
		if (*Pointer=='{')
		{
			Pointer++;

			if (*Pointer!='{')
			{
				bool											ClosingBracketFound=false;

				while(*Pointer!=L'\0')
				{
					if (*Pointer=='}')
					{
						Pointer++;
						ClosingBracketFound=true;
						break;
					}
					else
					{
						Pointer++;
					}
				}

				if (ClosingBracketFound==true)
				{
					throw(CException(L"FORMAT STRING EXPECTS too MANY PARAMETERS !"));
				}
				else
				{
					throw(CException(L"CLOSING BRACKET after OPENING BRACKET not FOUND !"));
				}
			}
			else
			{
				std::wcout << L"{";
				Pointer++;
			}
		}
		else if (*Pointer=='}')
		{
			Pointer++;

			if (*Pointer!=L'\0')
			{
				if (*Pointer=='}')
				{
					std::wcout << "}";
					Pointer++;
				}
				else
				{
					throw(CException(L"CLOSING BRACKET must be FOLLOWED be CLOSE BRACKET int this CONTENT !"));
				}
			}
			else
			{
				throw(CException(L"CLOSING BRACKET must NOT be at END of STRING !"));
			}
		}
		else
		{
			std::wcout << *Pointer;
			Pointer++;
		}
	}
}
//-----------------------------------------------------------------------------
// !!! VARIADIC TEMPLATE FUNCTION, ktora ma <2,N> PARAMETERS. 1. PARAMETER je FORMAT STRING.
// !!! FUNCTION reprezentuje RECURSION STEP.
template<typename TFirstParameter, typename ...TParameters>
void GenericPrint(const wchar_t* FormatString, TFirstParameter FirstParameter, TParameters... Parameters)
{
	const wchar_t*												Pointer=FormatString;

	while(*Pointer!=L'\0')
	{
		if (*Pointer=='{')
		{
			Pointer++;

			if (*Pointer!='{')
			{
				std::wstring									ParameterFormat;
				bool											ClosingBracketFound=false;

				while(*Pointer!=L'\0')
				{
					if (*Pointer=='}')
					{
						Pointer++;
						ClosingBracketFound=true;
						break;
					}
					else
					{
						ParameterFormat.append(1,*Pointer);
						Pointer++;
					}
				}

				if (ClosingBracketFound==true)
				{
					std::wcout << FirstParameter;

					// !!!!! Tu je mozne pouzit 'ParameterFormat'.
					if (ParameterFormat.length()>0)
					{
						std::wcout << L" (" << ParameterFormat << L")";
					}

					// !!!!! Rekurzivne sa vola FUNCTION, pricom sa odstrani 1. TYPE PARAMETER.
					GenericPrint(Pointer,Parameters...);

					return;
				}
				else
				{
					throw(CException(L"CLOSING BRACKET after OPENING BRACKET not FOUND !"));
				}
			}
			else
			{
				std::wcout << L"{";
				Pointer++;
			}
		}
		else if (*Pointer=='}')
		{
			Pointer++;

			if (*Pointer!=L'\0')
			{
				if (*Pointer=='}')
				{
					std::wcout << "}";
					Pointer++;
				}
				else
				{
					throw(CException(L"CLOSING BRACKET must be FOLLOWED be CLOSE BRACKET int this CONTENT !"));
				}
			}
			else
			{
				throw(CException(L"CLOSING BRACKET must NOT be at END of STRING !"));
			}
		}
		else
		{
			std::wcout << *Pointer;
			Pointer++;
		}
	}
}
//-----------------------------------------------------------------------------