//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CException.h"
//-------------------------------------------------------------------------------------------------------
void PrintfTemplateByIterator(const std::wstring& Format, std::wstring::const_iterator& Iterator)
{
	while(Iterator!=Format.cend())
	{
		if (*Iterator!=L'!')
		{
			std::wcout << *Iterator;
			Iterator++;
		}
		else
		{
			Iterator++;

			if (Iterator!=Format.cend())
			{
				if (*Iterator==L'!')
				{
					std::wcout << *Iterator;
					Iterator++;
				}
				else
				{
					throw(CException(L"NOT ENOUGH PARAMETERS !"));
				}
			}
			else
			{
				throw(CException(L"INVALID FORMAT STRING !"));
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------
template<typename TFirstParameter, typename... TOtherParameters>
void PrintfTemplateByIterator(const std::wstring& Format, std::wstring::const_iterator& Iterator, TFirstParameter FirstParameter, TOtherParameters... OtherParameters)
{
	while(Iterator!=Format.cend())
	{
		if (*Iterator!=L'!')
		{
			std::wcout << *Iterator;
			Iterator++;
		}
		else
		{
			Iterator++;

			if (Iterator!=Format.cend())
			{
				if (*Iterator==L'!')
				{
					std::wcout << *Iterator;
					Iterator++;
				}
				else if (*Iterator==L'%')
				{
					std::wcout << FirstParameter;

					Iterator++;

					// !!! Vykona sa REKURZIA, ktora spracuje nasledujuci TYPE PARAMETER.
					PrintfTemplateByIterator(Format,Iterator,OtherParameters...);
					return;
				}
				else
				{
					throw(CException(L"INVALID FORMAT STRING !"));
				}
			}
			else
			{
				throw(CException(L"INVALID FORMAT STRING !"));
			}
		}
	}

	throw(CException(L"TOO MANY PARAMETERS !"));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void PrintfTemplateByIndex(const std::wstring& Format, size_t Index)
{
	while(Index<Format.length())
	{
		if (Format[Index]!=L'!')
		{
			std::wcout << Format[Index];
			Index++;
		}
		else
		{
			Index++;

			if (Index<Format.length())
			{
				if (Format[Index]==L'!')
				{
					std::wcout << Format[Index];
					Index++;
				}
				else
				{
					throw(CException(L"NOT ENOUGH PARAMETERS !"));
				}
			}
			else
			{
				throw(CException(L"INVALID FORMAT STRING !"));
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------
template<typename TFirstParameter, typename... TOtherParameters>
void PrintfTemplateByIndex(const std::wstring& Format, size_t Index, TFirstParameter FirstParameter, TOtherParameters... OtherParameters)
{
	while(Index<Format.length())
	{
		if (Format[Index]!=L'!')
		{
			std::wcout << Format[Index];
			Index++;
		}
		else
		{
			Index++;

			if (Index<Format.length())
			{
				if (Format[Index]==L'!')
				{
					std::wcout << Format[Index];
					Index++;
				}
				else if (Format[Index]==L'%')
				{
					std::wcout << FirstParameter;

					Index++;

					// !!! Vykona sa REKURZIA, ktora spracuje nasledujuci TYPE PARAMETER.
					PrintfTemplateByIndex(Format,Index,OtherParameters...);
					return;
				}
				else
				{
					throw(CException(L"INVALID FORMAT STRING !"));
				}
			}
			else
			{
				throw(CException(L"INVALID FORMAT STRING !"));
			}
		}
	}

	throw(CException(L"TOO MANY PARAMETERS !"));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename... TParameters>
void PrintfByIndex(std::wstring Format, TParameters... Parameters)
{
	PrintfTemplateByIndex(Format,0,Parameters...);
}
//-------------------------------------------------------------------------------------------------------
template<typename... TParameters>
void PrintfByIterator(std::wstring Format, TParameters... Parameters)
{
	std::wstring::const_iterator								Iterator=Format.cbegin();

	PrintfTemplateByIterator(Format,Iterator,Parameters...);
}
//-------------------------------------------------------------------------------------------------------