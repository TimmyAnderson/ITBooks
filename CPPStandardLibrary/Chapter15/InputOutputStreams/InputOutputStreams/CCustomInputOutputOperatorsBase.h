//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <string>
//-----------------------------------------------------------------------------
class CCustomInputOutputOperatorsBase
{
//-----------------------------------------------------------------------------
	private:
		int														MBaseValueInt;
		double													MBaseValueDouble;

	public:
		virtual std::wstring ToString(void) const
		{
			std::wstringstream									Stream;

			Stream << L"BASE VALUE INT [" << MBaseValueInt << L"] BASE VALUE DOUBLE [" << MBaseValueDouble << L"]";

			return(Stream.str());
		}

	public:
		// !!! VIRTUAL METHOD pre citanie FIELDS z C++ STREAM.
		virtual void ReadFromStream(std::wistream& Stream)
		{
			int													BaseValueInt;
			double												BaseValueDouble;

			Stream >> BaseValueInt;

			if (Stream.operator bool()==true)
			{
				Stream >> BaseValueDouble;

				if (Stream.operator bool()==true)
				{
					// !!! FIELDS sa nastavuju IBA ak bolo citanie oboch FIELDS uspesne.
					MBaseValueInt=BaseValueInt;
					MBaseValueDouble=BaseValueDouble;
				}
			}
		}

		// !!! VIRTUAL METHOD pre zapis FIELDS do C++ STREAM.
		virtual void WriteToStream(std::wostream& Stream) const
		{
			Stream << MBaseValueInt;
			Stream << L" ";
			Stream << MBaseValueDouble;
		}

	public:
		int GetBaseValueInt(void) const noexcept
		{
			return(MBaseValueInt);
		}

		double GetBaseValueDouble(void) const noexcept
		{
			return(MBaseValueDouble);
		}

	public:
		CCustomInputOutputOperatorsBase(void)
			: MBaseValueInt(0), MBaseValueDouble(0)
		{
		}

		CCustomInputOutputOperatorsBase(int BaseValueInt, double BaseValueDouble)
			: MBaseValueInt(BaseValueInt), MBaseValueDouble(BaseValueDouble)
		{
		}

		virtual ~CCustomInputOutputOperatorsBase()
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Iba BASE CLASSES v CLASS HIERARCHY by mali implementovat OPERATOR>>.
std::wistream& operator>>(std::wistream& Stream, CCustomInputOutputOperatorsBase& Object)
{
	Object.ReadFromStream(Stream);

	return(Stream);
}
//-----------------------------------------------------------------------------
// !!! Iba BASE CLASSES v CLASS HIERARCHY by mali implementovat OPERATOR<<.
std::wostream& operator<<(std::wostream& Stream, const CCustomInputOutputOperatorsBase& Object)
{
	// !!! Pri zapise je vhodne pouzit TEMPORARY STRING STREAM, aby sa eliminoval problem s resetovanim FLAG [width] po PRVOM volani OPERATOR<<.
	std::wostringstream											StringStream;

	// !!! Nastavia sa FLAGS povodneho STREAM.
	StringStream.copyfmt(Stream);

	// Resetuje sa WIDTH na 0.
	StringStream.width(0);

	Object.WriteToStream(StringStream);

	std::wstring												Text=StringStream.str();

	// Obsah TEMPORARY STREAM sa zapise do povodneho STREAM.
	Stream << Text;

	return(Stream);
}
//-----------------------------------------------------------------------------