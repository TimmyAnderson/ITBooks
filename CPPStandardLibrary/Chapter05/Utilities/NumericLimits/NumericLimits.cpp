//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <limits>
#include <string>
#include <iostream>
#include <cstdint>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
// !!! VC++ ma hodnoty 'min' a 'max' definovane ako MACROS a preto ich je nutne oddefinovat.
#ifdef _MSC_VER
#undef min
#undef max
#endif
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArraySize(void)
{
	PrintLineSeparator();

	// !!! Kedze METHOD numeric_limits<uint8_t>::max() je CONSTEXPR, tak je ju mozne pouzit na definiciu velkosti ARRAY.
	uint8_t														Array[numeric_limits<uint8_t>::max()+1];

	for(int Index=numeric_limits<uint8_t>::min();Index<=numeric_limits<uint8_t>::max();Index++)
	{
		Array[Index]=Index;
	}

	for(int Index=numeric_limits<uint8_t>::min();Index<=numeric_limits<uint8_t>::max();Index++)
	{
		wcout << L"ARRAY[" << Index << L"]=[" << Array[Index] << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void TestDumpNumericLimits(void)
{
	PrintLineSeparator();

	bool														HasSpecialization=numeric_limits<TType>::is_specialized;

	wcout << L"TYPE [" << ConvertStringToWideString(typeid(TType).name()) << L"] !" << endl;

	if (HasSpecialization==true)
	{
		wcout << L"VALUE numeric_limits<TType>::is_integer [" << ((numeric_limits<TType>::is_integer==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::is_signed [" << ((numeric_limits<TType>::is_signed==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::is_iec559 [" << ((numeric_limits<TType>::is_iec559==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::min() [" << numeric_limits<TType>::min() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::max() [" << numeric_limits<TType>::max() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::lowest() [" << numeric_limits<TType>::lowest() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::epsilon() [" << numeric_limits<TType>::epsilon() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::round_error() [" << numeric_limits<TType>::round_error() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::infinity() [" << numeric_limits<TType>::infinity() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::quiet_NaN() [" << numeric_limits<TType>::quiet_NaN() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::signaling_NaN() [" << numeric_limits<TType>::signaling_NaN() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::denorm_min() [" << numeric_limits<TType>::denorm_min() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::is_exact [" << ((numeric_limits<TType>::is_exact==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::has_infinity [" << ((numeric_limits<TType>::has_infinity==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::has_quiet_NaN [" << ((numeric_limits<TType>::has_quiet_NaN==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::has_signaling_NaN [" << ((numeric_limits<TType>::has_signaling_NaN==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::has_denorm [" << numeric_limits<TType>::has_denorm << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::has_denorm_loss [" << ((numeric_limits<TType>::has_denorm_loss==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::round_style [" << numeric_limits<TType>::round_style << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::is_bounded [" << ((numeric_limits<TType>::is_bounded==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::is_modulo [" << ((numeric_limits<TType>::is_modulo==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::digits [" << numeric_limits<TType>::digits << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::digits10 [" << numeric_limits<TType>::digits10 << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::max_digits10 [" << numeric_limits<TType>::max_digits10 << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::radix [" << numeric_limits<TType>::radix << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::min_exponent [" << numeric_limits<TType>::min_exponent << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::min_exponent10 [" << numeric_limits<TType>::min_exponent10 << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::max_exponent [" << numeric_limits<TType>::max_exponent << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::max_exponent10 [" << numeric_limits<TType>::max_exponent10 << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::traps [" << ((numeric_limits<TType>::traps==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::tinyness_before [" << ((numeric_limits<TType>::tinyness_before==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	}
	else
	{
		wcout << L"TYPE has NO SPECIALIZATION !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestArraySize();
	//TestDumpNumericLimits<bool>();
	//TestDumpNumericLimits<int8_t>();
	//TestDumpNumericLimits<uint8_t>();
	//TestDumpNumericLimits<int16_t>();
	//TestDumpNumericLimits<uint16_t>();
	TestDumpNumericLimits<int32_t>();
	//TestDumpNumericLimits<uint32_t>();
	//TestDumpNumericLimits<int64_t>();
	//TestDumpNumericLimits<uint64_t>();
	//TestDumpNumericLimits<float>();
	//TestDumpNumericLimits<double>();
	//TestDumpNumericLimits<long double>();
	//TestDumpNumericLimits<wstring>();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------