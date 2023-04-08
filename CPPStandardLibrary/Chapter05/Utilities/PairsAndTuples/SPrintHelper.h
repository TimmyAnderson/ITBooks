//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <tuple>
#include <string>
#include <iostream>
#include <sstream>
//-----------------------------------------------------------------------------
void InternalGenericSPrint(std::wstringstream& StringBuffer, const wchar_t* FormatString)
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
				StringBuffer << L"{";
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
					StringBuffer << "}";
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
			StringBuffer << *Pointer;
			Pointer++;
		}
	}
}
//-----------------------------------------------------------------------------
template<typename TFirstParameter, typename ...TParameters>
void InternalGenericSPrint(std::wstringstream& StringBuffer, const wchar_t* FormatString, TFirstParameter FirstParameter, TParameters... Parameters)
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
					StringBuffer << FirstParameter;

					// !!!!! Tu je mozne pouzit 'ParameterFormat'.
					if (ParameterFormat.length()>0)
					{
						StringBuffer << L" (" << ParameterFormat << L")";
					}

					InternalGenericSPrint(StringBuffer,Pointer,Parameters...);

					return;
				}
				else
				{
					throw(CException(L"CLOSING BRACKET after OPENING BRACKET not FOUND !"));
				}
			}
			else
			{
				StringBuffer << L"{";
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
					StringBuffer << "}";
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
			StringBuffer << *Pointer;
			Pointer++;
		}
	}
}
//-----------------------------------------------------------------------------
template<typename ...TParameters>
std::wstring GenericSPrint(const wchar_t* FormatString, TParameters... Parameters)
{
	std::wstringstream											StringBuffer;

	InternalGenericSPrint(StringBuffer,FormatString,Parameters...);

	std::wstring												String=StringBuffer.str();

	return(String);
}
//-------------------------------------------------------------------------------------------------------