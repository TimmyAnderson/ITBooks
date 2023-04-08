//-------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning(disable:4244)
#endif
//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <iostream>
#include <memory>
#include <random>
#include <algorithm>
#include <sstream>
#include <complex>
#include <valarray>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
#undef min
#undef max
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TCollection>
void PrintCollection(const wstring& Prefix, const TCollection& Collection)
{
	wcout << Prefix;
	wcout << L" [";

	bool														PrintSeparator=false;

	for(const auto& Item : Collection)
	{
		if (PrintSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator=true;
		}

		wcout << Item;
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
template<typename TType>
void PrintValarray(const wstring& Prefix, const valarray<TType>& Valarray)
{
	wcout << Prefix;
	wcout << L" [";

	for(size_t Index=0;Index<Valarray.size();Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Valarray[Index];
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
template<typename TType>
void PrintValarray2Dimensions(const wstring& Prefix, const valarray<TType>& Valarray, size_t Difference)
{
	wcout << Prefix;
	wcout << L" [";

	for(size_t Index=0;Index<Valarray.size();Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		if (Index>0 && (Index % Difference)==0)
		{
			wcout << L" ";
		}

		wcout << Valarray[Index];
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
template<typename TType>
void PrintValarray3Dimensions(const wstring& Prefix, const valarray<TType>& Valarray, size_t Difference1, size_t Difference2)
{
	wcout << Prefix;
	wcout << L" [";

	for(size_t Index=0;Index<Valarray.size();Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		if (Index>0 && (Index % Difference1)==0)
		{
			wcout << L" ";
		}

		if (Index>0 && (Index % Difference2)==0)
		{
			wcout << L" ";
		}

		wcout << Valarray[Index];
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDefaultRandomGenerator(void)
{
	PrintLineSeparator();

	default_random_engine										Engine;

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10.0,20.0). Hodnota 20.0 nie je NIKDY generovana.
	uniform_real_distribution<double>							Distribution2(10,20);

	wcout << L"UNIFORM REAL DISTRIBUTION [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomGeneratorNoSeed(void)
{
	PrintLineSeparator();

	default_random_engine										Engine1;

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM DISTRIBUTION 1 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine1);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	default_random_engine										Engine2;

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution2(10,20);

	wcout << L"UNIFORM DISTRIBUTION 2 [";

	// !!! Generuje sa ROVNAKA POSTUPNOST VALUES.
	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine2);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomGeneratorWithSeed(void)
{
	PrintLineSeparator();

	// !!! Pouzije sa SEED.
	default_random_engine										Engine1(10);

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM DISTRIBUTION 1 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine1);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pouzije sa SEED.
	default_random_engine										Engine2(20);

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution2(10,20);

	wcout << L"UNIFORM DISTRIBUTION 2 [";

	// !!! Generuje sa ROZLICNA POSTUPNOST VALUES.
	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine2);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestShuffle(void)
{
	PrintLineSeparator();

	vector<int>													Vector({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	default_random_engine										Engine;

	shuffle(Vector.begin(),Vector.end(),Engine);

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomEngineSerialization(void)
{
	PrintLineSeparator();

	default_random_engine										Engine1;

	Engine1.discard(5);

	stringstream												EngineState;

	// !!! Interny STATE RANDOM ENGINE sa SERIALIZUJE do STREAM.
	EngineState << Engine1;

	wcout << L"ENGINE STATE [" << ConvertStringToWideString(EngineState.str()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"ENGINE STATE LENGTH [" << EngineState.str().size() << L"] !" << endl;

	PrintLineSeparator();

	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM DISTRIBUTION 1 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine1);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	default_random_engine										Engine2;

	// !!! Interny STATE RANDOM ENGINE sa DESERIALIZUJE zo STREAM.
	EngineState >> Engine2;

	uniform_int_distribution<int>								Distribution2(10,20);

	wcout << L"UNIFORM DISTRIBUTION 2 [";

	// !!!!! Budu sa generovat IDENTICKE VALUES, pretoze STATE 'Engine2' je identicky ako STATE 'Engine1' pred generovanim RANDOM VALUES.
	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine2);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNonDefaultRandomGenerator(void)
{
	PrintLineSeparator();

	knuth_b														Engine;

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10.0,20.0). Hodnota 20.0 nie je NIKDY generovana.
	uniform_real_distribution<double>							Distribution2(10,20);

	wcout << L"UNIFORM REAL DISTRIBUTION [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomEngineSetSeed(void)
{
	PrintLineSeparator();

	default_random_engine										Engine;

	// !!! Nastavi sa hodnota SEED.
	Engine.seed(100);

	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION 1 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Nastavi sa hodnota SEED.
	Engine.seed(100);

	uniform_int_distribution<int>								Distribution2(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION 2 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Nastavi sa hodnota SEED.
	Engine.seed(200);

	uniform_int_distribution<int>								Distribution3(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION 3 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution3(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Nastavi sa DEFAULT VALUE SEED.
	Engine.seed();

	uniform_int_distribution<int>								Distribution4(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION 4 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution4(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomEngineDiscard(void)
{
	PrintLineSeparator();

	default_random_engine										Engine;

	// !!! Nastavi sa hodnota SEED.
	Engine.seed(100);

	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION 1 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Nastavi sa hodnota SEED.
	Engine.seed(100);

	// !!! Posunie sa RANDOM VALUE o 1.
	Engine.discard(1);

	uniform_int_distribution<int>								Distribution2(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION 2 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomEnginesMinMax(void)
{
	PrintLineSeparator();

	wcout << L"RANDOM ENGINE [default_random_engine] - MINIMUM [" << default_random_engine().min() << L"] MAXIMUM [" << default_random_engine().max() << L"] !" << endl;
	wcout << L"RANDOM ENGINE [minstd_rand0] - MINIMUM [" << minstd_rand0().min() << L"] MAXIMUM [" << minstd_rand0().max() << L"] !" << endl;
	wcout << L"RANDOM ENGINE [minstd_rand] - MINIMUM [" << minstd_rand().min() << L"] MAXIMUM [" << minstd_rand().max() << L"] !" << endl;
	wcout << L"RANDOM ENGINE [mt19937] - MINIMUM [" << mt19937().min() << L"] MAXIMUM [" << mt19937().max() << L"] !" << endl;
	wcout << L"RANDOM ENGINE [mt19937_64] - MINIMUM [" << mt19937_64().min() << L"] MAXIMUM [" << mt19937_64().max() << L"] !" << endl;
	wcout << L"RANDOM ENGINE [ranlux24_base] - MINIMUM [" << ranlux24_base().min() << L"] MAXIMUM [" << ranlux24_base().max() << L"] !" << endl;
	wcout << L"RANDOM ENGINE [ranlux48_base] - MINIMUM [" << ranlux48_base().min() << L"] MAXIMUM [" << ranlux48_base().max() << L"] !" << endl;
	wcout << L"RANDOM ENGINE [ranlux24] - MINIMUM [" << ranlux24().min() << L"] MAXIMUM [" << ranlux24().max() << L"] !" << endl;
	wcout << L"RANDOM ENGINE [ranlux48] - MINIMUM [" << ranlux48().min() << L"] MAXIMUM [" << ranlux48().max() << L"] !" << endl;
	wcout << L"RANDOM ENGINE [knuth_b] - MINIMUM [" << knuth_b().min() << L"] MAXIMUM [" << knuth_b().max() << L"] !" << endl;
	wcout << L"RANDOM ENGINE [random_device] - MINIMUM [" << random_device().min() << L"] MAXIMUM [" << random_device().max() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomEnginesCompare(void)
{
	PrintLineSeparator();

	knuth_b														Engine1;
	knuth_b														Engine2;

	wcout << L"OPERATOR== [" << (Engine1==Engine2) << L"] !" << endl;
	wcout << L"OPERATOR!= [" << (Engine1!=Engine2) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"ENGINE 1 - VALUE [" << (Engine1()) << L"] !" << endl;

	wcout << L"OPERATOR== [" << (Engine1==Engine2) << L"] !" << endl;
	wcout << L"OPERATOR!= [" << (Engine1!=Engine2) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"ENGINE 2 - VALUE [" << (Engine2()) << L"] !" << endl;

	wcout << L"OPERATOR== [" << (Engine1==Engine2) << L"] !" << endl;
	wcout << L"OPERATOR!= [" << (Engine1!=Engine2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomEngineAdapter(void)
{
	PrintLineSeparator();

	knuth_b														Engine1;
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine1);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	discard_block_engine<knuth_b,3,2>							Engine2;
	uniform_int_distribution<int>								Distribution2(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION with ADAPTER [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine2);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDistributionSerialization(void)
{
	PrintLineSeparator();

	default_random_engine										Engine1;
	uniform_int_distribution<int>								Distribution1(10,20);

	stringstream												DistributionState;

	// !!! Interny STATE DISTRIBUTION sa SERIALIZUJE do STREAM.
	DistributionState << Distribution1;

	wcout << L"DISTRIBUTION STATE [" << ConvertStringToWideString(DistributionState.str()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"DISTRIBUTION STATE LENGTH [" << DistributionState.str().size() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"UNIFORM DISTRIBUTION 1 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine1);
	}

	wcout << L"] !" << endl;

	default_random_engine										Engine2;
	uniform_int_distribution<int>								Distribution2;

	DistributionState >> Distribution2;

	wcout << L"UNIFORM DISTRIBUTION 2 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine2);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDistributionCompare(void)
{
	PrintLineSeparator();

	uniform_int_distribution<int>								Distribution1(10,20);
	uniform_int_distribution<int>								Distribution2(10,20);
	uniform_int_distribution<int>								Distribution3(100,200);

	wcout << L"DISTRIBUTION (1,2) - OPERATOR== [" << (Distribution1==Distribution2) << L"] !" << endl;
	wcout << L"DISTRIBUTION (1,2) - OPERATOR!= [" << (Distribution1!=Distribution2) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"DISTRIBUTION (1,3) - OPERATOR== [" << (Distribution1==Distribution3) << L"] !" << endl;
	wcout << L"DISTRIBUTION (1,3) - OPERATOR!= [" << (Distribution1!=Distribution3) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"DISTRIBUTION (2,3) - OPERATOR== [" << (Distribution2==Distribution3) << L"] !" << endl;
	wcout << L"DISTRIBUTION (2,3) - OPERATOR!= [" << (Distribution2!=Distribution3) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDistributionWithParameters(void)
{
	PrintLineSeparator();

	default_random_engine										Engine1;
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM DISTRIBUTION 1 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine1);
	}

	wcout << L"] !" << endl;

	default_random_engine										Engine2;
	uniform_int_distribution<int>								Distribution2(100,200);

	wcout << L"UNIFORM DISTRIBUTION 2 [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine2);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	default_random_engine										Engine3;

	wcout << L"UNIFORM DISTRIBUTION 2 - CUSTOM PARAMS [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		// !!! Aj ked DISTRIBUTION ma ako PARAMETER (100,200), pouziju sa CUSTOM PARAMETERS (10,20).
		wcout << Distribution2(Engine3,uniform_int_distribution<int>::param_type(10,20));
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDistributionMinMax(void)
{
	PrintLineSeparator();

	wcout << L"DISTRIBUTION [uniform_int_distribution<int>] - MINIMUM [" << uniform_int_distribution<int>().min() << L"] MAXIMUM [" << uniform_int_distribution<int>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [uniform_real_distribution<double>] - MINIMUM [" << uniform_real_distribution<double>().min() << L"] MAXIMUM [" << uniform_real_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [bernoulli_distribution] - MINIMUM [" << bernoulli_distribution().min() << L"] MAXIMUM [" << bernoulli_distribution().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [binomial_distribution<int>] - MINIMUM [" << binomial_distribution<int>().min() << L"] MAXIMUM [" << binomial_distribution<int>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [negative_binomial_distribution<int>] - MINIMUM [" << negative_binomial_distribution<int>().min() << L"] MAXIMUM [" << negative_binomial_distribution<int>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [geometric_distribution<int>] - MINIMUM [" << geometric_distribution<int>().min() << L"] MAXIMUM [" << geometric_distribution<int>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [poisson_distribution<int>] - MINIMUM [" << poisson_distribution<int>().min() << L"] MAXIMUM [" << poisson_distribution<int>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [exponential_distribution<double>] - MINIMUM [" << exponential_distribution<double>().min() << L"] MAXIMUM [" << exponential_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [gamma_distribution<double>] - MINIMUM [" << gamma_distribution<double>().min() << L"] MAXIMUM [" << gamma_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [weibull_distribution<double>] - MINIMUM [" << weibull_distribution<double>().min() << L"] MAXIMUM [" << weibull_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [extreme_value_distribution<double>] - MINIMUM [" << extreme_value_distribution<double>().min() << L"] MAXIMUM [" << extreme_value_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [normal_distribution<double>] - MINIMUM [" << normal_distribution<double>().min() << L"] MAXIMUM [" << normal_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [lognormal_distribution<double>] - MINIMUM [" << lognormal_distribution<double>().min() << L"] MAXIMUM [" << lognormal_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [chi_squared_distribution<double>] - MINIMUM [" << chi_squared_distribution<double>().min() << L"] MAXIMUM [" << chi_squared_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [cauchy_distribution<double>] - MINIMUM [" << cauchy_distribution<double>().min() << L"] MAXIMUM [" << cauchy_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [fisher_f_distribution<double>] - MINIMUM [" << fisher_f_distribution<double>().min() << L"] MAXIMUM [" << fisher_f_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [student_t_distribution<double>] - MINIMUM [" << student_t_distribution<double>().min() << L"] MAXIMUM [" << student_t_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [discrete_distribution<int>] - MINIMUM [" << discrete_distribution<int>().min() << L"] MAXIMUM [" << discrete_distribution<int>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [piecewise_constant_distribution<double>] - MINIMUM [" << piecewise_constant_distribution<double>().min() << L"] MAXIMUM [" << piecewise_constant_distribution<double>().max() << L"] !" << endl;
	wcout << L"DISTRIBUTION [piecewise_linear_distribution<double>] - MINIMUM [" << piecewise_linear_distribution<double>().min() << L"] MAXIMUM [" << piecewise_linear_distribution<double>().max() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComplexNumbers(void)
{
	PrintLineSeparator();

	complex<double>												Number1(4,3);
	complex<double>												Number2(polar(5.0,0.75));

	wcout << L"NUMBER 1 [" << Number1 << L"] !" << endl;
	wcout << L"NUMBER 2 [" << Number2 << L"] !" << endl;

	wcout << L"NUMBER 1 - ABSOLUTE [" << abs(Number1) << L"] MAGNITUDE [" << norm(Number1) << L"] PHASE ANGLE [" << arg(Number1) << L"] CONJUGATE [" << conj(Number1) << L"] !" << endl;
	wcout << L"NUMBER 2 - ABSOLUTE [" << abs(Number2) << L"] MAGNITUDE [" << norm(Number2) << L"] PHASE ANGLE [" << arg(Number2) << L"] CONJUGATE [" << conj(Number2) << L"] !" << endl;

	PrintLineSeparator();

	complex<double>												Number3=Number1+Number2;

	wcout << L"NUMBER 3 [" << Number3 << L"] !" << endl;

	complex<double>												Number4=Number1-Number2;

	wcout << L"NUMBER 4 [" << Number4 << L"] !" << endl;

	complex<double>												Number5=Number1*Number2;

	wcout << L"NUMBER 5 [" << Number5 << L"] !" << endl;

	complex<double>												Number6=Number1/Number2;

	wcout << L"NUMBER 6 [" << Number6 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComplexNumberCreation(void)
{
	PrintLineSeparator();

	complex<double>												NumberA1(4,3);
	complex<double>												NumberA2(4,3);
	complex<double>												NumberA3(4,3);
	complex<double>												NumberA4(4,3);
	complex<double>												NumberB(5,8);

	wcout << L"A1 [" << NumberA1 << L"] !" << endl;
	wcout << L"A2 [" << NumberA2 << L"] !" << endl;
	wcout << L"A3 [" << NumberA3 << L"] !" << endl;
	wcout << L"A4 [" << NumberA4 << L"] !" << endl;
	wcout << L"B [" << NumberB << L"] !" << endl;

	PrintLineSeparator();

	NumberA1+=NumberB;
	NumberA2-=NumberB;
	NumberA3*=NumberB;
	NumberA4/=NumberB;

	wcout << L"A1+=B [" << NumberA1 << L"] !" << endl;
	wcout << L"A2-=B [" << NumberA2 << L"] !" << endl;
	wcout << L"A3*=B [" << NumberA3 << L"] !" << endl;
	wcout << L"A4/=B [" << NumberA4 << L"] !" << endl;

	PrintLineSeparator();

	// Vytvorenie COMPLEX NUMBER z POLAR VALUES.
	complex<double>												NumberC(polar(4.2,0.75));

	wcout << L"C [" << NumberC << L"] !" << endl;

	// Imaginarna cast ma obratene znamienko.
	complex<double>												NumberD=conj(NumberC);

	wcout << L"D [" << NumberD << L"] !" << endl;

	// Projekcia COMPLEX NUMBER do RIEMANN SPHERE.
	complex<double>												NumberE=proj(NumberC);

	wcout << L"E [" << NumberE << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComplexNumberConversion(void)
{
	PrintLineSeparator();

	complex<float>												NumberFloat1(4.2f,3.5f);

	wcout << L"NUMBER FLOAT 1 [" << NumberFloat1 << L"] !" << endl;

	// IMPLICIT CONVERSION je mozna ak NEDOCHADZA k strate presnosti.
	complex<double>												NumberDouble1(NumberFloat1);

	wcout << L"NUMBER DOUBLE 1 [" << NumberDouble1 << L"] !" << endl;

	// EXPLICIT CONVERSION je NUTNA, ak HROZI, ze dojde k STRATE PRESNOSTI.
	complex<float>												NumberFloat2(static_cast<complex<float>>(NumberDouble1));

	wcout << L"NUMBER FLOAT 2 [" << NumberFloat2 << L"] !" << endl;

	complex<double>												NumberDouble2;

	// IMPLICIT CONVERSION je mozna ak NEDOCHADZA k strate presnosti.
	NumberDouble2=NumberFloat1;

	wcout << L"NUMBER DOUBLE 2 [" << NumberDouble2 << L"] !" << endl;

	// EXPLICIT CONVERSION je NUTNA, ak HROZI, ze dojde k STRATE PRESNOSTI.
	complex<float>												NumberFloat3;

	NumberFloat3=static_cast<complex<float>>(NumberDouble2);

	wcout << L"NUMBER FLOAT 3 [" << NumberFloat3 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComplexNumberValueAccess(void)
{
	PrintLineSeparator();

	complex<double>												Number(4,3);

	wcout << L"NUMBER [" << Number << L"] !" << endl;
	wcout << L"REAL [" << Number.real() << L"] !" << endl;
	wcout << L"IMAGINARY [" << Number.imag() << L"] !" << endl;
	wcout << L"ABSOLUTE VALUE [" << abs(Number) << L"] !" << endl;
	wcout << L"NORMALIZED VALUE [" << norm(Number) << L"] !" << endl;
	wcout << L"ANGLE [" << arg(Number) << L"] !" << endl;

	PrintLineSeparator();

	// Zmenia sa hodnoty COMPLEX NUMBER.
	Number.real(8);
	Number.imag(12);

	wcout << L"NUMBER [" << Number << L"] !" << endl;
	wcout << L"REAL [" << Number.real() << L"] !" << endl;
	wcout << L"IMAGINARY [" << Number.imag() << L"] !" << endl;
	wcout << L"ABSOLUTE VALUE [" << abs(Number) << L"] !" << endl;
	wcout << L"NORMALIZED VALUE [" << norm(Number) << L"] !" << endl;
	wcout << L"ANGLE [" << arg(Number) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComplexNumberComparison(void)
{
	PrintLineSeparator();

	complex<double>												A(4,3);
	complex<double>												B(4,3);
	complex<double>												C(4,0);
	complex<double>												D(4,1);

	wcout << L"A [" << A << L"] !" << endl;
	wcout << L"B [" << B << L"] !" << endl;
	wcout << L"C [" << C << L"] !" << endl;
	wcout << L"D [" << D << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"A==B [" << (A==B) << L"] !" << endl;
	wcout << L"A==C [" << (A==C) << L"] !" << endl;
	wcout << L"A==D [" << (A==D) << L"] !" << endl;
	wcout << L"B==4.0 [" << (B==4.0) << L"] !" << endl;
	wcout << L"C==4.0 [" << (C==4.0) << L"] !" << endl;
	wcout << L"D==4.0 [" << (D==4.0) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"A!=B [" << (A!=B) << L"] !" << endl;
	wcout << L"A!=C [" << (A!=C) << L"] !" << endl;
	wcout << L"A!=D [" << (A!=D) << L"] !" << endl;
	wcout << L"B!=4.0 [" << (B!=4.0) << L"] !" << endl;
	wcout << L"C!=4.0 [" << (C!=4.0) << L"] !" << endl;
	wcout << L"D!=4.0 [" << (D!=4.0) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComplexNumberArithmeticOperations(void)
{
	PrintLineSeparator();

	complex<double>												A(4,3);
	complex<double>												B(polar(5.0,0.75));

	wcout << L"A [" << A << L"] !" << endl;
	wcout << L"B [" << B << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"+A [" << (+A) << L"] !" << endl;
	wcout << L"-A [" << (-A) << L"] !" << endl;
	wcout << L"A+B [" << (A+B) << L"] !" << endl;
	wcout << L"A-B [" << (A-B) << L"] !" << endl;
	wcout << L"A*B [" << (A*B) << L"] !" << endl;
	wcout << L"A/B [" << (A/B) << L"] !" << endl;
	wcout << L"A+1.7 [" << (A+1.7) << L"] !" << endl;
	wcout << L"A-1.7 [" << (A-1.7) << L"] !" << endl;
	wcout << L"A*1.7 [" << (A*1.7) << L"] !" << endl;
	wcout << L"A/1.7 [" << (A/1.7) << L"] !" << endl;

	PrintLineSeparator();

	complex<double>												NumberA1(4,3);
	complex<double>												NumberA2(4,3);
	complex<double>												NumberA3(4,3);
	complex<double>												NumberA4(4,3);
	complex<double>												NumberB(5,8);

	wcout << L"A1 [" << NumberA1 << L"] !" << endl;
	wcout << L"A2 [" << NumberA2 << L"] !" << endl;
	wcout << L"A3 [" << NumberA3 << L"] !" << endl;
	wcout << L"A4 [" << NumberA4 << L"] !" << endl;
	wcout << L"B [" << NumberB << L"] !" << endl;

	PrintLineSeparator();

	NumberA1+=NumberB;
	NumberA2-=NumberB;
	NumberA3*=NumberB;
	NumberA4/=NumberB;

	wcout << L"A1+=B [" << NumberA1 << L"] !" << endl;
	wcout << L"A2-=B [" << NumberA2 << L"] !" << endl;
	wcout << L"A3*=B [" << NumberA3 << L"] !" << endl;
	wcout << L"A4/=B [" << NumberA4 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComplexNumberTranscedentalFunctions(void)
{
	PrintLineSeparator();

	complex<double>												Number(4,3);

	wcout << L"NUMBER [" << Number << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"POW(COMPLEX(2,3)) [" << pow(Number,complex<double>(2,3)) << L"] !" << endl;
	wcout << L"EXP() [" << exp(Number) << L"] !" << endl;
	wcout << L"SQRT() [" << sqrt(Number) << L"] !" << endl;
	wcout << L"LOG() [" << log(Number) << L"] !" << endl;
	wcout << L"LOG10() [" << log10(Number) << L"] !" << endl;
	wcout << L"SIN() [" << sin(Number) << L"] !" << endl;
	wcout << L"COS() [" << cos(Number) << L"] !" << endl;
	wcout << L"TAN() [" << tan(Number) << L"] !" << endl;
	wcout << L"SINH() [" << sinh(Number) << L"] !" << endl;
	wcout << L"COSH() [" << cosh(Number) << L"] !" << endl;
	wcout << L"TANH() [" << tanh(Number) << L"] !" << endl;
	wcout << L"ASIN() [" << asin(Number) << L"] !" << endl;
	wcout << L"ACOS() [" << acos(Number) << L"] !" << endl;
	wcout << L"ATAN() [" << atan(Number) << L"] !" << endl;
	wcout << L"ASINH() [" << asinh(Number) << L"] !" << endl;
	wcout << L"ACOSH() [" << acosh(Number) << L"] !" << endl;
	wcout << L"ATANH() [" << atanh(Number) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComplexNumberStreams(void)
{
	PrintLineSeparator();

	complex<double>												A(4,3);
	complex<double>												B(4,0);

	wcout << L"A [" << A << L"] !" << endl;
	wcout << L"B [" << B << L"] !" << endl;

	PrintLineSeparator();

	wstringstream												Stream1(L"10");
	wstringstream												Stream2(L"(10)");
	wstringstream												Stream3(L"(10,20)");

	complex<double>												C;

	Stream1 >> C;

	wcout << L"C [" << C << L"] !" << endl;

	complex<double>												D;

	Stream2 >> D;

	wcout << L"D [" << D << L"] !" << endl;

	complex<double>												E;

	Stream3 >> E;

	wcout << L"E [" << E << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCMathFunctions(void)
{
	PrintLineSeparator();

	double														Number=5.4;

	wcout << L"EXP() [" << exp(Number) << L"] !" << endl;
	wcout << L"SQRT() [" << sqrt(Number) << L"] !" << endl;
	wcout << L"LOG() [" << log(Number) << L"] !" << endl;
	wcout << L"LOG10() [" << log10(Number) << L"] !" << endl;
	wcout << L"SIN() [" << sin(Number) << L"] !" << endl;
	wcout << L"COS() [" << cos(Number) << L"] !" << endl;
	wcout << L"TAN() [" << tan(Number) << L"] !" << endl;
	wcout << L"SINH() [" << sinh(Number) << L"] !" << endl;
	wcout << L"COSH() [" << cosh(Number) << L"] !" << endl;
	wcout << L"TANH() [" << tanh(Number) << L"] !" << endl;
	wcout << L"ASIN() [" << asin(Number) << L"] !" << endl;
	wcout << L"ACOS() [" << acos(Number) << L"] !" << endl;
	wcout << L"ATAN() [" << atan(Number) << L"] !" << endl;
	wcout << L"ASINH() [" << asinh(Number) << L"] !" << endl;
	wcout << L"ACOSH() [" << acosh(Number) << L"] !" << endl;
	wcout << L"ATANH() [" << atanh(Number) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayInitialization(void)
{
	PrintLineSeparator();

	// Vytvori VALARRAY s 5 ITEMS obsahujucimi hodnotu 0.
	valarray<int>												Valarray1(5);

	PrintValarray(L"VALARRAY 1",Valarray1);

	PrintLineSeparator();

	// Vytvori VALARRAY s 5 ITEMS obsahujucimi hodnotu 3.14.
	valarray<double>											Valarray2(3.14,5);

	PrintValarray(L"VALARRAY 2",Valarray2);

	PrintLineSeparator();

	valarray<int>												Valarray3({1,2,3,4,5,6,7});

	PrintValarray(L"VALARRAY 3",Valarray3);

	PrintLineSeparator();

	int															Array[]{10,20,30,40,50};

	// Inicializacia VALARRAY z ARRAY.
	valarray<int>												Valarray4(Array,sizeof(Array)/sizeof(Array[0]));

	PrintValarray(L"VALARRAY 4",Valarray4);

	PrintLineSeparator();

	// Inicializacia VALARRAY z ARRAY.
	valarray<int>												Valarray5(Array+1,3);

	PrintValarray(L"VALARRAY 5",Valarray5);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayOperations(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray1({10,20,30,40,50});
	valarray<int>												Valarray2({1,2,3,4,5});

	PrintValarray(L"VALARRAY 1",Valarray1);
	PrintValarray(L"VALARRAY 2",Valarray2);

	PrintLineSeparator();

	// Matematicke operacie je mozne vykonavat nad jednotlivymi ITEMS.
	Valarray2[0]=Valarray2[1]+Valarray2[2];

	PrintValarray(L"VALARRAY 2",Valarray2);

	PrintLineSeparator();

	// Matematicke operacie je mozne vykonavat nad CELYMI VALARRAYS.
	valarray<int>												Valarray3=3*Valarray1+Valarray2-2;

	PrintValarray(L"VALARRAY 3 - (3*VALARRAY_1+VALARRAY_2-2)",Valarray3);

	PrintLineSeparator();

	// Matematicke operacie je mozne vykonavat nad CELYMI VALARRAYS.
	valarray<int>												Valarray4=-Valarray3;

	PrintValarray(L"VALARRAY 4 - (-VALARRAY_3)",Valarray4);

	PrintLineSeparator();

	valarray<int>												Valarray5({17,3,12,28,19});
	
	PrintValarray(L"VALARRAY 5",Valarray5);

	wcout << L"VALARRAY 5 - MIN [" << Valarray5.min() << L"] !" << endl;
	wcout << L"VALARRAY 5 - MAX [" << Valarray5.max() << L"] !" << endl;
	wcout << L"VALARRAY 5 - SUM [" << Valarray5.sum() << L"] !" << endl;

	PrintLineSeparator();

	PrintValarray(L"VALARRAY 1",Valarray1);
	PrintValarray(L"VALARRAY 5",Valarray5);

	// !!! RETURN VALUE pre OPERATOR== je VALARRAY s BOOL VALUES.
	valarray<bool>												Valarray6=(Valarray1==Valarray5);

	PrintValarray(L"VALARRAY 6 - OPERATOR==",Valarray6);

	// !!! RETURN VALUE pre OPERATOR!= je VALARRAY s BOOL VALUES.
	valarray<bool>												Valarray7=(Valarray1!=Valarray5);

	PrintValarray(L"VALARRAY 7 - OPERATOR!=",Valarray7);

	// !!! RETURN VALUE pre OPERATOR< je VALARRAY s BOOL VALUES.
	valarray<bool>												Valarray8=(Valarray1<Valarray5);

	PrintValarray(L"VALARRAY 8 - OPERATOR<",Valarray8);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayIteration(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({17,3,12,28,19});
	
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	wcout << L"VALARRAY [";

	bool														PrintSeparator1=false;

	// !!! Aj ked CLASS [valarray<TType>] NEMA definovane METHOD begin() a METHOD end() ako METHODS, ma ich definovane ako FUNCTIONS.
	for(int Item : Valarray)
	{
		if (PrintSeparator1==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator1=true;
		}

		wcout << Item;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALARRAY [";

	bool														PrintSeparator2=false;

	// FUNCTION begin() a FUNCTION end() su definovane ako GLOBALNE FUNCTIONS.
	for(auto Iterator=begin(Valarray);Iterator!=end(Valarray);Iterator++)
	{
		if (PrintSeparator2==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator2=true;
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayTranscendentalFunctions(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray1({10,20,30,40,50});
	valarray<int>												Valarray2({1,2,3,4,5});

	PrintValarray(L"VALARRAY 1",Valarray1);
	PrintValarray(L"VALARRAY 2",Valarray2);

	PrintLineSeparator();

	valarray<int>												Valarray3=pow(Valarray1,Valarray2);

	PrintValarray(L"VALARRAY 3 - POW(VALARRAY_1,VALARRAY_2)",Valarray3);

	PrintLineSeparator();

	valarray<int>												Valarray4=sqrt(Valarray3);

	PrintValarray(L"VALARRAY 4 - SQRT(VALARRAY_3)",Valarray4);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarraySlicesDesignError(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray(4*3+2);

	for(size_t Index=0;Index<Valarray.size();Index++)
	{
		Valarray[Index]=int(Index+1);
	}

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	slice_array<int>											Slice1=Valarray[slice(0,4,3)];
	slice_array<int>											Slice2=Valarray[slice(1,4,3)];
	slice_array<int>											Slice3=Valarray[slice(2,4,3)];

	// !!! CLASS [slice_array<TType>] NEMA definovany OPERATOR[] a preto na vypis ITEMS je NUTNY CAST na VALARRAY.
	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"SLICE 2",valarray<int>(Slice2));
	PrintValarray(L"SLICE 3",valarray<int>(Slice3));
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	// !!!!! Kedze VALARRAY NEMA definovane MATHEMATICS OPERATORS nasledujuci CODE hodi COMPILATION ERROR.
	//Valarray[slice(0,4,3)]=Valarray[slice(1,4,3)]*Valarray[slice(2,4,3)];

	// !!!!! Na vykonanie MATHEMATICS OPERATORS je NUTNE vykonat EXPLICITNY CASTING.
	// !!!!! NEVYHODOU EXPLICITNEHO CASTING je vytvorenie TEMPORARY OBJECTS cim sa ZNIZUJE PERFORMANCE.
	Valarray[slice(0,4,3)]=static_cast<valarray<int>>(Valarray[slice(1,4,3)])*static_cast<valarray<int>>(Valarray[slice(2,4,3)]);

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"SLICE 2",valarray<int>(Slice2));
	PrintValarray(L"SLICE 3",valarray<int>(Slice3));
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarraySliceInitialization(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray(20);

	for(size_t Index=0;Index<Valarray.size();Index++)
	{
		Valarray[Index]=int(Index+1);
	}

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	slice_array<int>											Slice1=Valarray[slice(0,4,3)];

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));

	slice_array<int>											Slice2=Valarray[slice(1,4,3)];

	PrintValarray(L"SLICE 2",valarray<int>(Slice2));

	slice_array<int>											Slice3=Valarray[slice(2,4,3)];

	PrintValarray(L"SLICE 3",valarray<int>(Slice3));

	// !!! Hodnota STRIDE moze byt aj ZAPORNA.
	slice_array<int>											Slice4=Valarray[slice(15,4,-3)];

	PrintValarray(L"SLICE 4",valarray<int>(Slice4));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarraySliceConstVsNonCostValarrays(void)
{
	PrintLineSeparator();

	valarray<int>												NonConstValarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});
	const valarray<int>											ConstValarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});
	valarray<int>												AddValarray({100,100,100,100});

	PrintValarray(L"NON-CONST VALARRAY",NonConstValarray);
	PrintValarray(L"CONST VALARRAY",ConstValarray);
	PrintValarray(L"ADD VALARRAY",AddValarray);

	PrintLineSeparator();

	// !!!!! SLICE vytvoreny z NON-CONST VALARRAY obsahuje REFERENCES na ITEMS POVODNEHO VALARRAY
	// OPERATOR[] nad NON-CONST VALARRAY vracia instanciu SLICE.
	slice_array<int>											NonConstSlice=NonConstValarray[slice(2,4,3)];

	PrintValarray(L"NON-CONST SLICE",valarray<int>(NonConstSlice));

	// !!!!! SLICE vytvoreny z CONST VALARRAY je NOVA INSTANCIA VALARRAY, ktora NEREFERUJE na POVODNY VALARRAY.
	// !!!!! OPERATOR[] nad CONST VALARRAY vracia instanciu VALARRAY.
	valarray<int>												ConstSlice=ConstValarray[slice(2,4,3)];

	PrintValarray(L"CONST SLICE",ConstSlice);

	PrintLineSeparator();

	// !!! Modifikuje ITEMS POVODNEHO VALARRAY.
	NonConstSlice+=AddValarray;

	// !!!!! Nemodifikuje ITEMS POVODNEHO VALARRAY.
	ConstSlice+=AddValarray;

	PrintValarray(L"NON-CONST SLICE",valarray<int>(NonConstSlice));
	PrintValarray(L"CONST SLICE",ConstSlice);

	PrintLineSeparator();

	PrintValarray(L"NON-CONST VALARRAY",NonConstValarray);
	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarraySliceOperations(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	slice_array<int>											Slice1=Valarray[slice(0,4,3)];

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));

	slice_array<int>											Slice2=Valarray[slice(1,4,3)];

	PrintValarray(L"SLICE 2",valarray<int>(Slice2));

	slice_array<int>											Slice3=Valarray[slice(2,4,3)];

	PrintValarray(L"SLICE 3",valarray<int>(Slice3));

	PrintLineSeparator();

	// !!! Komplexna matematicka operacia.
	Slice1=static_cast<valarray<int>>(Slice2)*static_cast<valarray<int>>(Slice3);

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	// !!! Komplexna matematicka operacia.
	valarray<int>												PowValarray=pow(static_cast<valarray<int>>(Slice2),static_cast<valarray<int>>(Slice3));

	PrintValarray(L"SLICE 2",valarray<int>(Slice2));
	PrintValarray(L"SLICE 3",valarray<int>(Slice3));
	PrintValarray(L"POW VALARRAY",PowValarray);

	PrintLineSeparator();

	// Priradi VALUE do kazdeho ITEM.
	Slice1=555;

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayGSlice1Dimension(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	size_t														RawSizes[]={4};
	size_t														RawStrides[]={3};
	valarray<size_t>											Sizes(RawSizes,1);
	valarray<size_t>											Strides(RawStrides,1);

	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad NON-CONST VALARRAY vytvori instanciu CLASS [gslice_array<TType>].
	gslice_array<int>											Slice1=Valarray[gslice(2,Sizes,Strides)];
	gslice_array<int>											Slice2=Valarray[gslice(3,Sizes,Strides)];

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"SLICE 2",valarray<int>(Slice2));

	PrintLineSeparator();

	// !!! Modifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z NON-CONST VALARRAY obsahuju REFERENCES na povodny VALARRAY.
	Slice1+=Slice2;

	PrintValarray(L"SLICE 1 (Slice1+=Slice2)",valarray<int>(Slice1));

	PrintLineSeparator();

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	const valarray<int>											ConstValarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();

	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad CONST VALARRAY vytvori instanciu CLASS [valarray<TType>].
	valarray<int>												ValarraySlice1=ConstValarray[gslice(2,Sizes,Strides)];
	valarray<int>												ValarraySlice2=ConstValarray[gslice(3,Sizes,Strides)];

	PrintValarray(L"VALARRAY SLICE 1",valarray<int>(ValarraySlice1));
	PrintValarray(L"VALARRAY SLICE 2",valarray<int>(ValarraySlice2));

	PrintLineSeparator();

	// !!! Nemodifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z CONST VALARRAY obsahuju KOPIU dat z povodneho VALARRAY.
	ValarraySlice1+=ValarraySlice2;

	PrintValarray(L"VALARRAY SLICE 1 (ValarraySlice1+=ValarraySlice2)",valarray<int>(ValarraySlice1));

	PrintLineSeparator();

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayGSlice2Dimensions(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	// !!! V 1. DIMENSION su 2 ITEMS.
	// !!! V 2. DIMENSION su 4 ITEMS.
	size_t														RawSizes[]={2,4};
	size_t														NumberOfDimensions=sizeof(RawSizes)/sizeof(RawSizes[0]);
	// !!! V 1. DIMENSION je rozdiel medzi ITEMS 10 ITEMS z VALARRAY.
	// !!! V 2. DIMENSION je rozdiel medzi ITEMS 3 ITEMS z VALARRAY.
	size_t														RawStrides[]={10,3};
	valarray<size_t>											Sizes(RawSizes,NumberOfDimensions);
	valarray<size_t>											Strides(RawStrides,NumberOfDimensions);

	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad NON-CONST VALARRAY vytvori instanciu CLASS [gslice_array<TType>].
	gslice_array<int>											Slice1=Valarray[gslice(2,Sizes,Strides)];
	gslice_array<int>											Slice2=Valarray[gslice(3,Sizes,Strides)];

	PrintValarray2Dimensions(L"SLICE 1",valarray<int>(Slice1),RawSizes[NumberOfDimensions-1]);
	PrintValarray2Dimensions(L"SLICE 2",valarray<int>(Slice2),RawSizes[NumberOfDimensions-1]);

	PrintLineSeparator();

	// !!! Modifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z NON-CONST VALARRAY obsahuju REFERENCES na povodny VALARRAY.
	Slice1+=Slice2;

	PrintValarray2Dimensions(L"SLICE 1 (Slice1+=Slice2)",valarray<int>(Slice1),RawSizes[NumberOfDimensions-1]);

	PrintLineSeparator();

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	const valarray<int>											ConstValarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();

	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad CONST VALARRAY vytvori instanciu CLASS [valarray<TType>].
	valarray<int>												ValarraySlice1=ConstValarray[gslice(2,Sizes,Strides)];
	valarray<int>												ValarraySlice2=ConstValarray[gslice(3,Sizes,Strides)];

	PrintValarray2Dimensions(L"VALARRAY SLICE 1",valarray<int>(ValarraySlice1),RawSizes[NumberOfDimensions-1]);
	PrintValarray2Dimensions(L"VALARRAY SLICE 2",valarray<int>(ValarraySlice2),RawSizes[NumberOfDimensions-1]);

	PrintLineSeparator();

	// !!! Nemodifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z CONST VALARRAY obsahuju KOPIU dat z povodneho VALARRAY.
	ValarraySlice1+=ValarraySlice2;

	PrintValarray2Dimensions(L"VALARRAY SLICE 1 (ValarraySlice1+=ValarraySlice2)",valarray<int>(ValarraySlice1),RawSizes[NumberOfDimensions-1]);

	PrintLineSeparator();

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayGSlice3Dimensions(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	// !!! V 1. DIMENSION su 3 ITEMS.
	// !!! V 2. DIMENSION su 2 ITEMS.
	// !!! V 3. DIMENSION su 4 ITEMS.
	size_t														RawSizes[]={3,2,4};
	size_t														NumberOfDimensions=sizeof(RawSizes)/sizeof(RawSizes[0]);
	// !!! V 1. DIMENSION je rozdiel medzi ITEMS 30 ITEMS z VALARRAY.
	// !!! V 2. DIMENSION je rozdiel medzi ITEMS 10 ITEMS z VALARRAY.
	// !!! V 3. DIMENSION je rozdiel medzi ITEMS 3 ITEMS z VALARRAY.
	size_t														RawStrides[]={30,10,3};
	valarray<size_t>											Sizes(RawSizes,NumberOfDimensions);
	valarray<size_t>											Strides(RawStrides,NumberOfDimensions);

	// !!!!! Tento CODE v GCC sposobuje SEGMENTATION FAULT. Podla INTERNETU to vyzera, ze je to BUG v GCC. Vo VISUAL STUDIO CODE ide bez problemov.
#ifdef _MSC_VER
	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad NON-CONST VALARRAY vytvori instanciu CLASS [gslice_array<TType>].
	gslice_array<int>											Slice1=Valarray[gslice(2,Sizes,Strides)];
	gslice_array<int>											Slice2=Valarray[gslice(3,Sizes,Strides)];

	PrintValarray3Dimensions(L"SLICE 1",valarray<int>(Slice1),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);
	PrintValarray3Dimensions(L"SLICE 2",valarray<int>(Slice2),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);

	PrintLineSeparator();

	// !!! Modifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z NON-CONST VALARRAY obsahuju REFERENCES na povodny VALARRAY.
	Slice1+=Slice2;

	PrintValarray3Dimensions(L"SLICE 1 (Slice1+=Slice2)",valarray<int>(Slice1),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);
#endif

	PrintLineSeparator();

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	const valarray<int>											ConstValarray({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100});

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();

	// !!! Po aplikacii OPERATOR[] s PARAMETER [gslice<TType>] nad CONST VALARRAY vytvori instanciu CLASS [valarray<TType>].
	valarray<int>												ValarraySlice1=ConstValarray[gslice(2,Sizes,Strides)];
	valarray<int>												ValarraySlice2=ConstValarray[gslice(3,Sizes,Strides)];

	PrintValarray3Dimensions(L"VALARRAY SLICE 1",valarray<int>(ValarraySlice1),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);
	PrintValarray3Dimensions(L"VALARRAY SLICE 2",valarray<int>(ValarraySlice2),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);

	PrintLineSeparator();

	// !!! Nemodifikuju sa aj VALUES vo VALARRAY, kedze SLICES vytvorene z CONST VALARRAY obsahuju KOPIU dat z povodneho VALARRAY.
	ValarraySlice1+=ValarraySlice2;

	PrintValarray3Dimensions(L"VALARRAY SLICE 1 (ValarraySlice1+=ValarraySlice2)",valarray<int>(ValarraySlice1),RawSizes[NumberOfDimensions-1],RawSizes[NumberOfDimensions-1]*RawSizes[NumberOfDimensions-2]);

	PrintLineSeparator();

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayMaskArray(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	// !!! Aplikacia instancie CLASS [valarray<bool>] na NON-CONST VALARRAY vracia instanciu CLASS [mask_array<<TType>].
	mask_array<int>												Slice1=Valarray[Valarray<=20];
	mask_array<int>												Slice2=Valarray[Valarray>20];
	mask_array<int>												Slice3=Valarray[(Valarray % 2)==1];

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"SLICE 2",valarray<int>(Slice2));
	PrintValarray(L"SLICE 3",valarray<int>(Slice3));

	PrintLineSeparator();

	// Komplexna matematicka operacia.
	// !!! Kedze CLASS [indirect_array<int>] obsahuje REFERENCES na povodny VALARRAY, zmenia sa ITEMS vo VALARRAY.
	Slice1=valarray<int>(Slice2)+valarray<int>(Slice3);

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	const valarray<int>											ConstValarray({11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30});

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();

	// !!! Aplikacia instancie CLASS [valarray<bool>] na CONST VALARRAY vracia VALARRAY.
	valarray<int>												ConstSlice1=ConstValarray[ConstValarray<=20];
	valarray<int>												ConstSlice2=ConstValarray[ConstValarray>20];
	valarray<int>												ConstSlice3=ConstValarray[(ConstValarray % 2)==1];

	PrintValarray(L"CONST SLICE 1",ConstSlice1);
	PrintValarray(L"CONST SLICE 2",ConstSlice2);
	PrintValarray(L"CONST SLICE 3",ConstSlice3);

	PrintLineSeparator();

	// Komplexna matematicka operacia.
	// !!! Kedze CLASS [indirect_array<int>] obsahuje KOPIU povodneho VALARRAY, hodnoty ITEMS vo VALARRAY sa NEMENIA.
	ConstSlice1=valarray<int>(ConstSlice2)+valarray<int>(ConstSlice3);

	PrintValarray(L"CONST SLICE 1",valarray<int>(ConstSlice1));
	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestValarrayIndirectArray(void)
{
	PrintLineSeparator();

	valarray<int>												Valarray({11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30});

	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	// INDEXY sa NESMU OPAKOVAT, no NEMUSIA byt SORTED.
	valarray<size_t>											Indices1({2,4,7,12,13,1});
	valarray<size_t>											Indices2({3,5,6,8,19,1});
	valarray<size_t>											Indices3({5,6,7,8,9,10});

	PrintValarray(L"INDICES 1",Indices1);
	PrintValarray(L"INDICES 2",Indices2);
	PrintValarray(L"INDICES 3",Indices3);

	PrintLineSeparator();

	// !!! Aplikacia instancie CLASS [valarray<size_t>] na NON-CONST VALARRAY vracia instanciu CLASS [indirect_array<<TType>].
	indirect_array<int>											Slice1=Valarray[Indices1];
	indirect_array<int>											Slice2=Valarray[Indices2];
	indirect_array<int>											Slice3=Valarray[Indices3];

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"SLICE 2",valarray<int>(Slice2));
	PrintValarray(L"SLICE 3",valarray<int>(Slice3));

	PrintLineSeparator();

	// Komplexna matematicka operacia.
	// !!! Kedze CLASS [indirect_array<int>] obsahuje REFERENCES na povodny VALARRAY, zmenia sa ITEMS vo VALARRAY.
	Slice1=valarray<int>(Slice2)+valarray<int>(Slice3);

	PrintValarray(L"SLICE 1",valarray<int>(Slice1));
	PrintValarray(L"VALARRAY",Valarray);

	PrintLineSeparator();

	const valarray<int>											ConstValarray({11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30});

	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();

	// !!! Aplikacia instancie CLASS [valarray<size_t>] na CONST VALARRAY vracia VALARRAY.
	valarray<int>												ConstSlice1=ConstValarray[Indices1];
	valarray<int>												ConstSlice2=ConstValarray[Indices2];
	valarray<int>												ConstSlice3=ConstValarray[Indices3];

	PrintValarray(L"CONST SLICE 1",ConstSlice1);
	PrintValarray(L"CONST SLICE 2",ConstSlice2);
	PrintValarray(L"CONST SLICE 3",ConstSlice3);

	PrintLineSeparator();

	// Komplexna matematicka operacia.
	// !!! Kedze CLASS [indirect_array<int>] obsahuje KOPIU povodneho VALARRAY, hodnoty ITEMS vo VALARRAY sa NEMENIA.
	ConstSlice1=valarray<int>(ConstSlice2)+valarray<int>(ConstSlice3);

	PrintValarray(L"CONST SLICE 1",valarray<int>(ConstSlice1));
	PrintValarray(L"CONST VALARRAY",ConstValarray);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestDefaultRandomGenerator();
	//TestRandomGeneratorNoSeed();
	//TestRandomGeneratorWithSeed();
	//TestShuffle();
	//TestRandomEngineSerialization();
	//TestNonDefaultRandomGenerator();
	//TestRandomEngineSetSeed();
	//TestRandomEnginesMinMax();
	//TestRandomEnginesCompare();
	//TestRandomEngineAdapter();
	//TestDistributionSerialization();
	//TestDistributionCompare();
	//TestDistributionWithParameters();
	//TestDistributionMinMax();
	//TestComplexNumbers();
	//TestComplexNumberCreation();
	//TestComplexNumberConversion();
	//TestComplexNumberValueAccess();
	//TestComplexNumberComparison();
	//TestComplexNumberArithmeticOperations();
	//TestComplexNumberTranscedentalFunctions();
	//TestComplexNumberStreams();
	TestCMathFunctions();
	//TestValarrayInitialization();
	//TestValarrayOperations();
	//TestValarrayIteration();
	//TestValarrayTranscendentalFunctions();
	//TestValarraySlicesDesignError();
	//TestValarraySliceInitialization();
	//TestValarraySliceConstVsNonCostValarrays();
	//TestValarraySliceOperations();
	//TestValarrayGSlice1Dimension();
	//TestValarrayGSlice2Dimensions();
	//TestValarrayGSlice3Dimensions();
	//TestValarrayMaskArray();
	//TestValarrayIndirectArray();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------