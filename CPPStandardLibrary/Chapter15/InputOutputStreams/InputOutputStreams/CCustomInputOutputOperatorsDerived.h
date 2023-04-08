//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <sstream>
#include "CCustomInputOutputOperatorsBase.h"
#include "CustomManipulators.h"
//-----------------------------------------------------------------------------
class CCustomInputOutputOperatorsDerived : public CCustomInputOutputOperatorsBase
{
//-----------------------------------------------------------------------------
	private:
		int														MDerivedValueInt;
		double													MDerivedValueDouble;

	public:
		virtual std::wstring ToString(void) const override
		{
			std::wstringstream									Stream;

			Stream << CCustomInputOutputOperatorsBase::ToString();

			Stream << L" DERIVED VALUE INT [" << MDerivedValueInt << L"] DERIVED VALUE DOUBLE [" << MDerivedValueDouble << L"]";

			return(Stream.str());
		}

	public:
		// !!! VIRTUAL METHOD pre citanie FIELDS z C++ STREAM.
		virtual void ReadFromStream(std::wistream& Stream) override
		{
			CCustomInputOutputOperatorsBase::ReadFromStream(Stream);

			int													DerivedValueInt;
			double												DerivedValueDouble;

			Stream >> DerivedValueInt;

			if (Stream.operator bool()==true)
			{
				Stream >> DerivedValueDouble;

				if (Stream.operator bool()==true)
				{
					// !!! FIELDS sa nastavuju IBA ak bolo citanie oboch FIELDS uspesne.
					MDerivedValueInt=DerivedValueInt;
					MDerivedValueDouble=DerivedValueDouble;
				}
			}
		}

		// !!! VIRTUAL METHOD pre zapis FIELDS do C++ STREAM.
		virtual void WriteToStream(std::wostream& Stream) const override
		{
			CCustomInputOutputOperatorsBase::WriteToStream(Stream);

			// !!! Z C++ STREAM OBJECT sa vyberu CUSTOM DATA a aplikuju sa na OUTPUT STREAM.
			if (Stream.iword(CUSTOM_DATA_INT_INDEX)!=0 || Stream.pword(CUSTOM_DATA_VOID_POINTER_INDEX)!=nullptr)
			{
				std::wstringstream								StringStream;
				int												ValueInt=Stream.iword(CUSTOM_DATA_INT_INDEX);
				std::wstring*									ValueVoidPointer=static_cast<std::wstring*>(Stream.pword(CUSTOM_DATA_VOID_POINTER_INDEX));

				StringStream << L" {";

				if (ValueInt!=0)
				{
					StringStream << ValueInt;
				}
				
				if (ValueVoidPointer!=nullptr)
				{
					if (ValueInt!=0)
					{
						StringStream << L" ";
					}

					StringStream << (*ValueVoidPointer);
				}

				StringStream << L"} ";

				Stream << StringStream.str();
			}
			else
			{
				Stream << L" ";
			}

			Stream << MDerivedValueInt;
			Stream << L" ";
			Stream << MDerivedValueDouble;
		}

	public:
		int GetDerivedValueInt(void) const noexcept
		{
			return(MDerivedValueInt);
		}

		double GetDerivedValueDouble(void) const noexcept
		{
			return(MDerivedValueDouble);
		}

	public:
		CCustomInputOutputOperatorsDerived(void)
			: CCustomInputOutputOperatorsBase(), MDerivedValueInt(0), MDerivedValueDouble(0)
		{
		}

		CCustomInputOutputOperatorsDerived(int BaseValueInt, double BaseValueDouble, int DerivedValueInt, double DerivedValueDouble)
			: CCustomInputOutputOperatorsBase(BaseValueInt,BaseValueDouble), MDerivedValueInt(DerivedValueInt), MDerivedValueDouble(DerivedValueDouble)
		{
		}

		virtual ~CCustomInputOutputOperatorsDerived()
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------