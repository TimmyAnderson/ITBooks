//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ranges>
#include <complex>
#include <thread>
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
#include "Helpers/MyDebug.h"
#include "Helpers/CString.h"
#include "Helpers/CException.h"
//----------------------------------------------------------------------------------------------------------------------
#include "CRangeVector.h"
#include "CSentinelNullTerminator.h"
#include "CSentinelTemplate.h"
#include "CBorrowedIteratorVector.h"
#include "CGeneratorRange.h"
#include "CDumpVector.h"
#include "CMoveableRangeVector.h"
#include "CLINQLikeView.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#pragma warning( disable : 26498 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCollection>
void PrintView(wstring Prefix, TCollection&& Collection)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	for(const auto& Value : Collection)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCollection>
void PrintCollection(wstring Prefix, const TCollection& Collection)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	for(const auto& Value : Collection)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! V SYNTAX [template<typename...> typename TCollection] je NUTNE pouzit VARIADIC TEMPLATE [typename...], pretoze COLLECTIONS maju dodatocne TEMPLATE PARAMETERS, ktore su pokryte pouzitim VARIADIC TEMPLATE.
template<typename TCollectionItem, template<typename...> typename TCollection>
void PrintCollection(wstring Prefix, TCollection<TCollectionItem>& Collection)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	for(TCollectionItem Value : Collection)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TArrayItem, size_t ARRAY_SIZE>
void PrintCollection(wstring Prefix, TArrayItem (&Array)[ARRAY_SIZE])
{
	wcout << Prefix << endl;

	size_t														Index=0;

	for(TArrayItem Value : Array)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSimpleUse(void)
{
	PrintLineSeparator();

	vector<int>													Collection{25,42,2,0,122,5,7};

	PrintCollection(L"COLLECTION UNSORTED:",Collection);

	PrintLineSeparator();

	// !!!!! Vykona sa SORT COLLECTION pomocou RANGES.
	ranges::sort(Collection);

	PrintCollection(L"COLLECTION SORTED:",Collection);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestRangesConcepts(void)
{
	PrintLineSeparator();

	{
		vector<wstring>											Collection{L"Timmy",L"Jenny",L"Atreyu",L"Josh",L"Lucas"};

		PrintCollection(L"COLLECTION UNSORTED:",Collection);

		PrintLineSeparator();

		// !!! RANGES ALGORITHMS mozu byt aplikovane na STANDARD COLLECTIONS.
		ranges::sort(Collection);

		PrintCollection(L"COLLECTION SORTED:",Collection);
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		int														Collection[]{25,42,2,0,122,5,7};

		PrintCollection(L"ARRAY UNSORTED:",Collection);

		PrintLineSeparator();

		// !!! RANGES ALGORITHMS mozu byt aplikovane na ARRAYS.
		ranges::sort(Collection);

		PrintCollection(L"ARRAY SORTED:",Collection);
	}

	/*
	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		list<wstring>											Collection{L"Timmy",L"Jenny",L"Atreyu",L"Josh",L"Lucas"};

		PrintCollection(L"COLLECTION UNSORTED:",Collection);

		PrintLineSeparator();

		// !!!!! COMPILER hodi ERROR, pretoze nie je splneny CONCEPT, ze COLLECTION ma mat RANDOM ACCESS ITERATOR.
		ranges::sort(Collection);

		PrintCollection(L"COLLECTION SORTED:",Collection);
	}
	*/

	/*
	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		vector<complex<double>>									Collection{8,3,5,4,9};

		PrintCollection(L"COLLECTION UNSORTED:",Collection);

		PrintLineSeparator();

		// !!!!! COMPILER hodi ERROR, pretoze nie je splneny CONCEPT, ze COLLECTION ma mat OPERTATOR [OPERTATOR<].
		ranges::sort(Collection);

		PrintCollection(L"COLLECTION SORTED:",Collection);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestViewsRangeAdaptors1(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

		PrintCollection(L"COLLECTION:",Collection);

		PrintLineSeparator();

		ranges::take_view										View=views::take(Collection,3);

		// !!! Na COLLECTION sa aplikuje RANGE ADAPTOR.
		PrintView(L"COLLECTION - RANGE ADAPTORS:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestViewsRangeAdaptors2(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

		PrintCollection(L"COLLECTION:",Collection);

		PrintLineSeparator();

		// !!! Na COLLECTION sa aplikuju RANGE ADAPTORS.
		// !!!!! RANGE ADAPTORS mozu byt kombinovane.
		ranges::take_view										View=views::take(views::transform(views::filter(Collection,[](auto P){return((P%3)==0);}),[](auto P){return(P*P);}),3);

		PrintView(L"COLLECTION - RANGE ADAPTORS:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestViewsPipelines2(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

		PrintCollection(L"COLLECTION:",Collection);

		PrintLineSeparator();

		// !!! Na COLLECTION sa aplikuju RANGE ADAPTORS.
		// !!!!! RANGE ADAPTORS mozu byt kombinovane.
		ranges::take_view										View=views::filter(Collection,[](auto P){return((P%3)==0);}) | views::transform([](auto P){return(P*P);}) | views::take(3);

		PrintView(L"COLLECTION - RANGE ADAPTORS:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestGeneratingViews(void)
{
	PrintLineSeparator();

	{
		// !!! VIEW generuje nove VALUES.
		ranges::iota_view										GeneratingView=views::iota(1,11);

		PrintView(L"GENERATING VIEW:",GeneratingView);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestViewsTypes(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{1,2,3,4,5};

		PrintCollection(L"COLLECTION:",Collection);

		PrintLineSeparator();

		// !!! Na VIEW sa da referovat pomocou KEYWORD [auto].
		auto													View1=views::take(Collection,3);

		PrintView(L"VIEW 1:",View1);

		// !!! Na VIEW sa da referovat pomocou TYPE [ranges::take_view], kde TEMPLATE ARGUMENTS TYPE [ranges::take_view] su DEDUCED.
		ranges::take_view										View2=views::take(Collection,3);

		PrintView(L"VIEW 2:",View2);

		// !!! Na VIEW sa da referovat pomocou TEMPLATE TYPE [ranges::take_view<ranges::ref_view<vector<int>>>].
		ranges::take_view<ranges::ref_view<vector<int>>>		View3=views::take(Collection,3);

		PrintView(L"VIEW 3:",View3);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestViewsTypesConstructors(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{1,2,3,4,5};

		PrintCollection(L"COLLECTION:",Collection);

		PrintLineSeparator();

		// !!! VIEWS je mozne vytvarat pomocou CONSTRUCTORS.
		ranges::take_view<ranges::ref_view<vector<int>>>		View(Collection,3);

		PrintView(L"VIEW:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestWritableViews(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{7,8,2,5,6,1};

		PrintCollection(L"UNSORTED COLLECTION:",Collection);

		PrintLineSeparator();

		// !!!!! Vytvori sa VIEW, ktory je WRITABLE.
		ranges::take_view<ranges::ref_view<vector<int>>>		View=(Collection | views::take(3));

		// !!!!! Vykona sa SORT VIEW. SORTING sa robi aj na COLLECTION, nad ktorou je VIEW postaveny.
		ranges::sort(View);

		PrintCollection(L"SORTED COLLECTION:",Collection);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestLazyEvaluation(void)
{
	PrintLineSeparator();

	{
		CRangeVector<int>										Collection{1,2,3,4,5,6,7,8,9,10};

		PrintCollection(L"COLLECTION:",Collection);

		PrintLineSeparator();

		// !!! Vytvori sa VIEW, ale k ITERATION este NEDOCHADZA.
		ranges::take_view<ranges::ref_view<CRangeVector<int>>>	View=Collection | views::take(5);

		PrintView(L"VIEW:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestViewsCaching(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{1,2,3,4,5,6,7,8,9,10};

		PrintCollection(L"COLLECTION:",Collection);

		PrintLineSeparator();

		ranges::take_view										View=views::take(Collection,5);

		// !!!!! Prida sa ELEMENT na zaciatok COLLECTION pred pouzitim VIEW.
		// !!!!! Modifikacia COLLECTIONS nad ktorymi su vytvorene VIEWS pred ich pouzitim je NEBEZPECNA a moze viest k UNDEFINED BEHAVIOR.
		Collection.insert(Collection.begin(),999);

		PrintView(L"VIEW:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSentinels(void)
{
	PrintLineSeparator();

	{
		const wchar_t											Value[]=L"Timmy Anderson";

		// !!! Definuje sa SENTINEL.
		CSentinelNullTerminator									Sentinel;

		wcout << L"VALUE [";

		// !!!!! BEGIN ITERATOR a END ITERATOR su ROZDIELNE.
		for(const wchar_t* Iterator=Value;Iterator!=Sentinel;++Iterator)
		{
			wchar_t												Value=*Iterator;

			wcout << Value;
		}

		wcout << L"]." << endl;
	}

	PrintLineSeparator();

	{
		const wchar_t											Value[]=L"Timmy Anderson";

		// !!! Definuje sa SENTINEL.
		CSentinelNullTerminator									Sentinel;

		wcout << L"VALUE [";

		// !!!!! STANDARD ALGORITHMS definovane v NAMESPACE [std::ranges] umoznuju pouzivanie rozlicnych TYPES BEGIN ITERATORS a END ITERATORS.
		ranges::for_each(Value,Sentinel,[] (wchar_t Value) {wcout << Value;});

		wcout << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCArraysAsRanges(void)
{
	PrintLineSeparator();

	int															Array[]{400,600,500,100,300,200};

	PrintCollection(L"C ARRAY:",Array);

	PrintLineSeparator();

	// !!! C-ARRAYS su tiez RANGES a je na ne mozne aplikovat RANGE ALGORITHMS.
	ranges::sort(Array);

	PrintCollection(L"SORTED C ARRAY:",Array);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSubrangeType(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{111,222,333,444,555};

		// !!! SUBRANGES je mozne vytvarat pre RANGES, ktore maju ROVNAKY TYPE BEGIN ITERATOR a END ITERATOR.
		ranges::subrange										SubRange(Collection.begin(),Collection.end());

		wcout << L"SUBRANGE SAME TYPE ITERATORS:" << endl;

		// !!! SUBRANGES je mozne ITEROVAT pomocou FOR LOOPS.
		for(int Value : SubRange)
		{
			wcout << L"VALUE [" << Value << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		vector<int>												Collection{111,222,333,444,555,-1};
		CSentinelTemplate<-1>									Sentinel;

		// !!! SUBRANGES je mozne vytvarat pre RANGES, ktore maju BEGIN ITERATOR a SENTINEL, ktore su ROZNYCH TYPES.
		ranges::subrange										SubRange(Collection.begin(),Sentinel);

		wcout << L"SUBRANGE DIFFERENT TYPE ITERATORS:" << endl;

		// !!! SUBRANGES je mozne ITEROVAT pomocou FOR LOOPS.
		for(int Value : SubRange)
		{
			wcout << L"VALUE [" << Value << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		vector<int>												Collection{444,333,555,222,111,-1};
		CSentinelTemplate<-1>									Sentinel;

		// !!! SUBRANGES je mozne vytvarat pre RANGES, ktore maju BEGIN ITERATOR a SENTINEL, ktore su ROZNYCH TYPES.
		ranges::subrange										SubRange(Collection.begin(),Sentinel);

		wcout << L"UNORDERED SUBRANGE:" << endl;

		// !!! SUBRANGES je mozne ITEROVAT pomocou FOR LOOPS.
		for(int Value : SubRange)
		{
			wcout << L"VALUE [" << Value << L"]." << endl;
		}

		PrintLineSeparator();

		// !!! SUBRANGES je mozne zasialat do RANGE ALGORITHMS.
		ranges::sort(SubRange);

		wcout << L"UNORDERED SUBRANGE:" << endl;

		// !!! SUBRANGES je mozne ITEROVAT pomocou FOR LOOPS.
		for(int Value : SubRange)
		{
			wcout << L"VALUE [" << Value << L"]." << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCountedRanges(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{111,222,333,444,555,666};
		vector<int>::const_iterator								BeginIterator=Collection.begin();
		size_t													Count=Collection.size();

		// !!! Vytvori sa RANGE z BEGIN ITERATOR a COUNT.
		auto													Range=views::counted(BeginIterator,Count);

		PrintView(L"COUNTED RANGE:",Range);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestProjections(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{3,7,5,2,8,1,4,2,6};

		PrintCollection(L"COLLECTION:",Collection);

		PrintLineSeparator();

		ranges::sort(Collection);

		PrintCollection(L"SORTED COLLECTION:",Collection);

		PrintLineSeparator();

		// !!! Pouzije sa PROJECTION.
		// !!!!! COLLECTION NEBUDE obsahovat ZAPORNE VALUES, lebo PROJECTION NEMENI VALUES danej COLLECTION, iba ich pred vykonanim OPERATION zmeni pre danu OPERATION, ale NIE v samotnej COLLECTION.
		ranges::sort(Collection,ranges::less{},[](int Value)->int{return(-Value);});

		PrintCollection(L"SORTED COLLECTION with PROJECTION:",Collection);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION reprezentuje implementaciu CUSTOM RANGE ALGORITHM.
// !!! CONCEPT vyzaduje aby TYPE PARAMETER bol INPUT RANGE.
template<ranges::input_range TRange>
// !!! RETURN VALUE TYPE je VALUE RANGE ITERATOR.
ranges::range_value_t<TRange> GetMaxValue(const TRange& Range)
{
	// !!! HELPER FUNCTION [empty()] testuje ci RANGE je EMPTY.
	if (ranges::empty(Range)==true)
	{
		// !!! HELPER USING [range_value_t] vracia VALUE TYPE danej RANGE.
		ranges::range_value_t<TRange>							DefaultValue{};

		return(DefaultValue);
	}

	// !!! HELPER FUNCTION [begin()] vracia BEGIN ITERATOR danej RANGE.
	auto														Iterator=ranges::begin(Range);

	// !!! HELPER USING [range_value_t] vracia VALUE TYPE danej RANGE.
	ranges::range_value_t<TRange>								MaxValue=*Iterator;

	// !!! HELPER FUNCTION [end()] vracia END ITERATOR (SENTINEL) danej RANGE.
	while(++Iterator!=ranges::end(Range))
	{
		if (*Iterator>MaxValue)
		{
			MaxValue=*Iterator;
		}
	}

	return(MaxValue);
}
//----------------------------------------------------------------------------------------------------------------------
void TestRangesUtilities(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{3,7,5,2,8,1,4,2,6};

		PrintCollection(L"COLLECTION:",Collection);

		// !!! CUSTOM RANGE ALGORITHM sa aplikuje na C++ STANDARD COLLECTION.
		int														MaxValue=GetMaxValue(Collection);

		wcout << L"MAX VALUE [" << MaxValue << L"]." << endl;
	}

	PrintLineSeparator();

	{
		int														CArray[]{3,7,5,2,8,1,4,2,6};

		PrintCollection(L"COLLECTION:",CArray);

		// !!! CUSTOM RANGE ALGORITHM sa aplikuje na C-ARRAY.
		int														MaxValue=GetMaxValue(CArray);

		wcout << L"MAX VALUE [" << MaxValue << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CBorrowedIteratorVector<int> BorrowedIteratorsCreateCollection(void)
{
	CBorrowedIteratorVector<int>								Collection{3,7,5,2,8,1,4,2,6};

	return(Collection);
}
//----------------------------------------------------------------------------------------------------------------------
/*
void ProcessBorrowedIterator(ranges::borrowed_iterator_t<CBorrowedIteratorVector<int>> Iterator)
{
	// !!!!! COMPILER hodi ERROR, pretoze BORROWED ITERATOR NEMA definovany OPERATOR [OPERATOR*].
	int															Value=*Iterator;

	wcout << L"ITEM [" << Value << L"] FOUND." << endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------
void TestBorrowedIterators(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{3,7,5,2,8,1,4,2,6};

		PrintCollection(L"LVALUE - COLLECTION:",Collection);

		// !!! Do ALGORITHM ide ako PARAMETER LVALUE, takze tato verzia ALGORITHM [find()] NEPOUZIVA BORROWED ITERATOR.
		ranges::iterator_t<vector<int>>							Position=ranges::find(Collection,2);

		if (Position!=Collection.end())
		{
			int													Value=*Position;

			wcout << L"ITEM [" << Value << L"] FOUND." << endl;
		}
		else
		{
			wcout << L"ITEM NOT FOUND." << endl;
		}
	}

	/*
	PrintLineSeparator();

	{
		vector<int>												Collection{3,7,5,2,8,1,4,2,6};

		PrintCollection(L"RVALUE - COLLECTION:",Collection);

		// !!!!! Do ALGORITHM ide ako PARAMETER RVALUE, takze tato verzia ALGORITHM POUZIVA BORROWED ITERATOR.
		ranges::borrowed_iterator_t<vector<int>>				Position=ranges::find(vector<int>(Collection),2);

		// !!!!! COMPILER hodi ERROR, pretoze BORROWED ITERATOR NEMA definovany OPERATOR [OPERATOR!=].
		if (Position!=Collection.end())
		{
			// !!!!! COMPILER hodi ERROR, pretoze BORROWED ITERATOR NEMA definovany OPERATOR [OPERATOR*].
			int													Value=*Position;

			wcout << L"ITEM [" << Value << L"] FOUND." << endl;
		}
		else
		{
			wcout << L"ITEM NOT FOUND." << endl;
		}
	}
	*/

	PrintLineSeparator();

	{
		CBorrowedIteratorVector<int>							Collection=BorrowedIteratorsCreateCollection();

		PrintCollection(L"LVALUE - COLLECTION by VALUE:",Collection);

		// !!! Do ALGORITHM ide ako PARAMETER LVALUE, takze tato verzia ALGORITHM [find()] NEPOUZIVA BORROWED ITERATOR.
		ranges::iterator_t<CBorrowedIteratorVector<int>>		Position=ranges::find(Collection,2);

		if (Position!=Collection.end())
		{
			int													Value=*Position;

			wcout << L"ITEM [" << Value << L"] FOUND." << endl;
		}
		else
		{
			wcout << L"ITEM NOT FOUND." << endl;
		}
	}

	PrintLineSeparator();

	{
		const CBorrowedIteratorVector<int>&						Collection=BorrowedIteratorsCreateCollection();

		PrintCollection(L"LVALUE - COLLECTION by CONST LVALUE REFERENCE:",Collection);

		// !!! Do ALGORITHM ide ako PARAMETER LVALUE, takze tato verzia ALGORITHM [find()] NEPOUZIVA BORROWED ITERATOR.
		ranges::iterator_t<CBorrowedIteratorVector<int>>		Position=ranges::find(Collection,2);

		if (Position!=Collection.end())
		{
			int													Value=*Position;

			wcout << L"ITEM [" << Value << L"] FOUND." << endl;
		}
		else
		{
			wcout << L"ITEM NOT FOUND." << endl;
		}
	}

	PrintLineSeparator();

	{
		CBorrowedIteratorVector<int>&&							Collection=BorrowedIteratorsCreateCollection();

		PrintCollection(L"LVALUE - COLLECTION by RVALUE REFERENCE:",Collection);

		// !!! Do ALGORITHM ide ako PARAMETER LVALUE, takze tato verzia ALGORITHM [find()] NEPOUZIVA BORROWED ITERATOR.
		ranges::iterator_t<CBorrowedIteratorVector<int>>		Position=ranges::find(Collection,2);

		if (Position!=Collection.end())
		{
			int													Value=*Position;

			wcout << L"ITEM [" << Value << L"] FOUND." << endl;
		}
		else
		{
			wcout << L"ITEM NOT FOUND." << endl;
		}
	}

	/*
	PrintLineSeparator();

	{
		CBorrowedIteratorVector<int>&&							Collection=BorrowedIteratorsCreateCollection();

		PrintCollection(L"RVALUE - COLLECTION:",Collection);

		// !!!!! Do ALGORITHM ide ako PARAMETER RVALUE (pre pouzitie FUNCTION [move()]), takze tato verzia ALGORITHM POUZIVA BORROWED ITERATOR.
		ranges::borrowed_iterator_t<CBorrowedIteratorVector<int>>	Position=ranges::find(move(Collection),2);

		// !!!!! COMPILER hodi ERROR, pretoze BORROWED ITERATOR NEMA definovany OPERATOR [OPERATOR!=].
		if (Position!=Collection.end())
		{
			// !!!!! COMPILER hodi ERROR, pretoze BORROWED ITERATOR NEMA definovany OPERATOR [OPERATOR*].
			int													Value=*Position;

			wcout << L"ITEM [" << Value << L"] FOUND." << endl;
		}
		else
		{
			wcout << L"ITEM NOT FOUND." << endl;
		}
	}
	*/

	/*
	PrintLineSeparator();

	{
		PrintCollection(L"RVALUE - COLLECTION:",BorrowedIteratorsCreateCollection());

		// !!!!! Do ALGORITHM ide ako PARAMETER RVALUE no aj po skonceni ALGORITHM je ITERATOR stale platny, lebo nedoslo uvolneniu RVALUE COLLECTION. No aj ked toto pouzitie RANGE ITERATOR je VALIDNE, a NEDOSLO by k vzniku UNDEFINED BEHAVIOR, pre pouzitie BORROWED ITERATOR COMPILER hodi ERROR.
		ProcessBorrowedIterator(ranges::find(BorrowedIteratorsCreateCollection(),2));
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestBorrowedRanges(void)
{
	PrintLineSeparator();

	{
		vector<int>												Collection{3,7,5,2,8,1,4,2,6};

		PrintCollection(L"LVALUE - COLLECTION:",Collection);

		// !!! RANGE [Collection] je prenesena pomocou LVALUE, a preto sa jedna o BORROWED RANGE.
		ranges::iterator_t<vector<int>>							Position=ranges::find(Collection,2);

		if (Position!=Collection.end())
		{
			int													Value=*Position;

			wcout << L"ITEM [" << Value << L"] FOUND." << endl;
		}
		else
		{
			wcout << L"ITEM NOT FOUND." << endl;
		}
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! RANGE je prenesena pomocou RVALUE, a preto sa NEJEDNA o BORROWED RANGE.
		ranges::borrowed_iterator_t<vector<int>>				Position=ranges::find(vector<int>{3,7,5,2,8,1,4,2,6},2);

		// !!!!! Pokus o pouzitie BORROWED ITERATOR nad NON-BORROWED RANGE vedie ku COMPILATION ERROR.
		int														Value=*Position;

		wcout << L"ITEM [" << Value << L"] FOUND." << endl;
	}
	*/

	/*
	PrintLineSeparator();

	{
		// !!!!! VIEW [single()] vytvara TEMPORARY VIEW. Pri pouziti ALGORITHM [find()] vznika DANGLING ITERATOR.
		ranges::dangling										Position=ranges::find(views::single(8),8);

		// !!!!! Pokus o pouzitie DANGLED ITERATOR vedie ku COMPILATION ERROR.
		int														Value=*Position;

		wcout << L"ITEM [" << Value << L"] FOUND." << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! Kedze VIEW [iota()] je GENERATOR, ktory generuje VALUES. ITERATORS VIEW [iota_view<TValue>] maju VALUE ulozenu LOKALNE, a preto reprezentuju BORROWED RANGES, ktore nie su zavisle na existencii povodneho VIEW.
		ranges::iterator_t<ranges::iota_view<int>>				Position=ranges::find(views::iota(8),8);

		// !!!!! ITERATORS BORROWED RANGES je mozne pouzit aj po skonceni zivotnosti povodnej RANGE.
		int														Value=*Position;

		wcout << L"ITEM [" << Value << L"] FOUND." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! VIEW [take] sa referuje na RANGE zaslanu ako RVALUE, a teda sa NEJEDNA o BORROWED RANGE. Preto vrateny ITERATOR je DANGLING ITERATOR.
		ranges::dangling										Position=ranges::find(views::take(std::vector{0,8,15},2),8);

		// !!!!! Pokus o pouzitie DANGLED ITERATOR vedie ku COMPILATION ERROR.
		int														Value=*Position;

		wcout << L"ITEM [" << Value << L"] FOUND." << endl;
	}
	*/

	/*
	PrintLineSeparator();

	// !!!!! Tento CODE sposobuje UNDEFINED BEHAVIOR.
	{
		// !!!!! COUNTED VIEWS su povazovane za BORROWED RANGES, pretoze ITERATORS obsahuju REFERENCE na OBJECT na ktory referuju.
		ranges::borrowed_iterator_t<span<int>>					Position=ranges::find(views::counted(vector{0,8,15}.begin(),2),8);
		
		// !!!!! Aj napriek tomu, ze COUNTED VIEWS su BORROWED RANGES a pri pouziti ich ITERATORS NEDOJDE ku COMPILE ERROR, kedze ITERATORS obsahuju iba REFERENCE na OBJECT v povodnej UNDERLYING RANGE, pouzitie tychto ITERATORS sposobi RUNTIME ERROR, ak UNDERLYING RANGE uz viac NEEXISTUJE.
		// !!!!! CODE sposobuje UNDEFINED BEHAVIOR.
		int														Value=*Position;

		wcout << L"ITEM [" << Value << L"] FOUND." << endl;
	}
	*/

	PrintLineSeparator();

	{
		CGeneratorRange											Generator{};

		CGeneratorRangeIterator									Position=ranges::find(Generator,3);

		int														Value=*Position;

		wcout << L"ITEM [" << Value << L"] FOUND." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Kedze RANGE je prenasany ako RVALUE, CODE funguje IBA ak je CLASS [CGeneratorRange] oznaceny za BORROWED RANGE.
		CGeneratorRangeIterator									Position=ranges::find(CGeneratorRange{},3);

		int														Value=*Position;

		wcout << L"ITEM [" << Value << L"] FOUND." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestRangesToViews(void)
{
	PrintLineSeparator();

	{
		// !!! Kazda C++ STANDARD COLLECTION je RANGE, ale NIE VIEW.
		vector<int>												Range{1,2,3,4,5};

		// !!! Z RANGE sa spravi VIEW pomocou VIEW [ALL].
		auto													View=views::all(Range);
		wstring													Type=GetTypeInfoName<decltype(View)>();

		PrintView(format(L"VIEW ALL - TYPE [{}]:",Type),View);
	}

	PrintLineSeparator();

	{
		// !!! Kazda C++ STANDARD COLLECTION je RANGE, ale NIE VIEW.
		vector<int>												Range{1,2,3,4,5};

		// !!! Z RANGE sa spravi VIEW pomocou CLASS [SUBRANGE].
		auto													View=ranges::subrange(Range.begin(),Range.end());
		wstring													Type=GetTypeInfoName<decltype(View)>();

		PrintView(format(L"VIEW SUBRANGE - TYPE [{}]:",Type),View);
	}

	PrintLineSeparator();

	{
		// !!! Kazda C++ STANDARD COLLECTION je RANGE, ale NIE VIEW.
		vector<int>												Range{1,2,3,4,5};

		// !!! Z RANGE sa spravi VIEW pomocou VIEW [COUNTED].
		auto													View=views::counted(Range.begin(),Range.size());
		wstring													Type=GetTypeInfoName<decltype(View)>();

		PrintView(format(L"VIEW COUNTED - TYPE [{}]:",Type),View);
	}

	PrintLineSeparator();

	{
		// !!! Kazda C++ STANDARD COLLECTION je RANGE, ale NIE VIEW.
		vector<int>												Range{1,2,3,4,5};

		// !!! Z RANGE sa spravi VIEW pomocou ADAPTOR FUNCTION.
		auto													View=views::take(Range,Range.size());
		wstring													Type=GetTypeInfoName<decltype(View)>();

		PrintView(format(L"VIEW ADAPTOR TAKE - TYPE [{}]:",Type),View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestViewCreations(void)
{
	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5};

		// !!! VIEWS je mozne vytvarat pomocou CONSTRUCTORS.
		ranges::take_view										View(Range,3);
		wstring													Type=GetTypeInfoName<decltype(View)>();

		PrintView(format(L"VIEW by CONSTRUCTOR - TYPE [{}]:",Type),View);
	}

	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5};

		// !!! VIEWS je mozne vytvarat pomocou ADAPTOR FUNCTIONS.
		auto													View=views::take(Range,3);
		wstring													Type=GetTypeInfoName<decltype(View)>();

		PrintView(format(L"VIEW by ADAPTOR FUNCTION - TYPE [{}]:",Type),View);
	}

	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5};

		// !!! VIEWS je mozne vytvarat pomocou PIPELINES.
		auto													View=Range | views::take(3);
		wstring													Type=GetTypeInfoName<decltype(View)>();

		PrintView(format(L"VIEW by PIPELINE - TYPE [{}]:",Type),View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
vector<wstring> TestViewConversionsCreateRange(void)
{
	vector<wstring>												Range{L"AAA",L"BBB",L"CCC",L"DDD",L"EEE"};

	return(Range);
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewConversions(void)
{
	PrintLineSeparator();

	{
		vector<wstring>											Range{L"AAA",L"BBB",L"CCC",L"DDD",L"EEE"};

		// !!! Z RANGE sa vytvori VIEW.
		ranges::ref_view<vector<wstring>>						InnerView=views::all(Range);

		// !!!!! Kedze do ADAPTOR FUNCTION je poslany VIEW, tak sa pouzije tento VIEW.
		ranges::take_view<ranges::ref_view<vector<wstring>>>	View=views::take(InnerView,3);
		wstring													Type=GetTypeInfoName<decltype(View)>();

		PrintView(format(L"VIEW from VIEW - TYPE [{}]:",Type),View);
	}

	PrintLineSeparator();

	{
		vector<wstring>											Range{L"AAA",L"BBB",L"CCC",L"DDD",L"EEE"};

		// !!! Z RANGE sa vytvori VIEW pomocou LVALUE. Pri pouziti LVALUE sa vytvori INTERNY VIEW, ktory ma VIEW TYPE [ref_view<TYPE>].
		ranges::take_view<ranges::ref_view<vector<wstring>>>	View=views::take(Range,3);
		wstring													Type=GetTypeInfoName<decltype(View)>();

		PrintView(format(L"VIEW from LVALUE RANGE - TYPE [{}]:",Type),View);
	}

	PrintLineSeparator();

	{
		vector<wstring>											Range{L"AAA",L"BBB",L"CCC",L"DDD",L"EEE"};

		// !!! Z RANGE sa vytvori VIEW pomocou RVALUE. Pri pouziti RVALUE sa vytvori INTERNY VIEW, ktory ma VIEW TYPE [owning_view<TYPE>].
		ranges::take_view<ranges::owning_view<vector<wstring>>>	View=views::take(move(Range),3);
		wstring													Type=GetTypeInfoName<decltype(View)>();

		PrintView(format(L"VIEW from RVALUE RANGE - TYPE [{}]:",Type),View);
	}

	PrintLineSeparator();

	{
		// !!! Z RANGE sa vytvori VIEW pomocou RVALUE cez PIPELINE. Pri pouziti RVALUE sa vytvori INTERNY VIEW, ktory ma VIEW TYPE [owning_view<TYPE>].
		// !!!!! CODE NESPOSOBI RUNTIME ERROR, pretoze VIEW [TAKE] pouziva VIEW [OWNING], ktory pomocou MOVE SEMANTIC skopiruje obsah RVALUE a teda povodna RANGE NEZANIKNE, ale je ulozena v VIEW [OWNING].
		ranges::take_view<ranges::owning_view<vector<wstring>>>	View=TestViewConversionsCreateRange() | views::take(3);
		wstring													Type=GetTypeInfoName<decltype(View)>();

		PrintView(format(L"VIEW from RVALUE PIPELINE - TYPE [{}]:",Type),View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ViewsLazyEvaluation1Predicate1(int Value)
{
	wcout << L"\tFILTER 1 - VALUE [" << Value << L"]." << endl;

	if ((Value % 3)==0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
bool ViewsLazyEvaluation1Predicate2(int Value)
{
	wcout << L"\tFILTER 2 - VALUE [" << Value << L"]." << endl;

	if (Value>=10)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
int ViewsLazyEvaluation1Transform(int Value)
{
	wcout << L"\tTRANSFORM - VALUE [" << Value << L"]." << endl;

	int															TransformedValue=-Value;

	return(TransformedValue);
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewsLazyEvaluation1(void)
{
	PrintLineSeparator();

	CDumpVector<int>											Range{7,4,3,14,18,6,12,22};
	auto														View=Range | views::filter(ViewsLazyEvaluation1Predicate1) | views::filter(ViewsLazyEvaluation1Predicate2) | views::transform(ViewsLazyEvaluation1Transform);

	wcout << L"ITERATION:" << endl;

	// !!! Az pri spusteni ITERATION dochadza k spracovanie VIEW.
	for(int Value : View)
	{
		wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ViewsLazyEvaluation2Predicate1(int Value)
{
	wcout << L"\tFILTER 1 - VALUE [" << Value << L"]." << endl;

	if ((Value % 3)==0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
bool ViewsLazyEvaluation2Predicate2(int Value)
{
	wcout << L"\tFILTER 2 - VALUE [" << Value << L"]." << endl;

	if (Value>=10)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
int ViewsLazyEvaluation2Transform(int Value)
{
	wcout << L"\tTRANSFORM - VALUE [" << Value << L"]." << endl;

	int															TransformedValue=-Value;

	return(TransformedValue);
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewsLazyEvaluation2(void)
{
	PrintLineSeparator();

	CDumpVector<int>											Range{7,4,3,14,18,6,12,22};
	auto														View=Range | views::filter(ViewsLazyEvaluation2Predicate1) | views::filter(ViewsLazyEvaluation2Predicate2) | views::transform(ViewsLazyEvaluation2Transform);

	wcout << L"ITERATION:" << endl;

	do
	{
		// !!! CODE vykona nasledujucu cinnost.
		// 1. Zavola sa METHOD [begin()] TRANSFORM VIEW. Ten zavola METHOD [begin()] FILTER 2 VIEW.
		// 2. Zavola sa METHOD [begin()] FILTER 2 VIEW. Ten zavola METHOD [begin()] FILTER 1 VIEW.
		// 3. Zavola sa METHOD [begin()] FILTER 1 VIEW. Ten zavola METHOD [begin()] VECTOR.
		// 4. Zavola sa METHOD [begin()] VECTOR. Ten vrati ITERTOR na zaciatok VECTOR do FILTER 1 VIEW.
		// 5. FILTER 1 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [7]. Kedze tato VALUE NIE je delitelna 3, zavola sa OPERATOR [OPERATOR++] na VECTOR.
		// 6. OPERATOR [OPERATOR++] na VECTOR posunie ITERATOR na 2. ELEMENT.
		// 7. FILTER 1 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [4]. Kedze tato VALUE NIE je delitelna 3, zavola sa OPERATOR [OPERATOR++] na VECTOR.
		// 8. OPERATOR [OPERATOR++] na VECTOR posunie ITERATOR na 3. ELEMENT.
		// 9. FILTER 1 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [3]. Kedze tato VALUE je delitelna 3, riadenie sa vrati do FILTER 2 VIEW.
		// 10. FILTER 2 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [3]. Kedze tato VALUE NIE je vacsia, alebo rovna 10, zavola sa OPERATOR [OPERATOR++] na FILTER 1.
		// 11. OPERATOR [OPERATOR++] na FILTER 1 VIEW zavola OPERATOR [OPERATOR++] na VECTOR.
		// 12. OPERATOR [OPERATOR++] na VECTOR posunie ITERATOR na 4. ELEMENT.
		// 13. FILTER 1 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [14]. Kedze tato VALUE NIE je delitelna 3, zavola sa OPERATOR [OPERATOR++] na VECTOR.
		// 14. OPERATOR [OPERATOR++] na VECTOR posunie ITERATOR na 5. ELEMENT.
		// 15. FILTER 1 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [18]. Kedze tato VALUE je delitelna 3, riadenie sa vrati do FILTER 2 VIEW.
		// 16. FILTER 2 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [18]. Kedze tato VALUE je vacsia, alebo rovna 10, ITERATOR sa vrati do TRANSFORM VIEW.
		// 17. TRANSFORM VIEW vrati ITERATOR na ELEMENT [18] do CALLING CODE.
		auto													Iterator=View.begin();

		auto													EndIterator=View.end();

		if (Iterator==EndIterator)
		{
			break;
		}

		{
			// !!! CODE vykona nasledujucu cinnost.
			// 1. Vola sa OPERATOR [OPERATOR*] v TRANSFORM VIEW.
			// 2. OPERATOR [OPERATOR*] TRANSFORM VIEW vrati VALUE [18], ktora sa vrati do CALLING CODE.
			int													Value=(*Iterator);

			wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
		}
	
		// !!! CODE vykona nasledujucu cinnost.
		// 1. OPERATOR [OPERATOR++] na TRANSFORM VIEW zavola OPERATOR [OPERATOR++] na FILTER VIEW 2.
		// 2. OPERATOR [OPERATOR++] na FILTER VIEW 2 zavola OPERATOR [OPERATOR++] na FILTER VIEW 1.
		// 3. OPERATOR [OPERATOR++] na FILTER VIEW 1 zavola OPERATOR [OPERATOR++] na VECTOR.
		// 4. OPERATOR [OPERATOR++] na VECTOR posunie ITERATOR na 6. ELEMENT.
		// 5. FILTER 1 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [6]. Kedze tato VALUE je delitelna 3, riadenie sa vrati do FILTER 2 VIEW.
		// 6. FILTER 2 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [6]. Kedze tato VALUE NIE je vacsia, alebo rovna 10, zavola sa OPERATOR [OPERATOR++] na FILTER 1.
		// 7. OPERATOR [OPERATOR++] na VECTOR posunie ITERATOR na 7. ELEMENT.
		// 8. FILTER 1 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [12]. Kedze tato VALUE je delitelna 3, riadenie sa vrati do FILTER 2 VIEW.
		// 9. FILTER 2 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [12]. Kedze tato VALUE je vacsia, alebo rovna 10, ITERATOR sa vrati do TRANSFORM VIEW.
		// 10. TRANSFORM VIEW vrati ITERATOR na ELEMENT [12] do CALLING CODE.
		Iterator++;

		if (Iterator==EndIterator)
		{
			break;
		}

		{
			// !!! CODE vykona nasledujucu cinnost.
			// 1. Vola sa OPERATOR [OPERATOR*] v TRANSFORM VIEW.
			// 2. OPERATOR [OPERATOR*] TRANSFORM VIEW vrati VALUE [12], ktora sa vrati do CALLING CODE.
			int													Value=(*Iterator);

			wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
		}

		// !!! CODE vykona nasledujucu cinnost.
		// 1. OPERATOR [OPERATOR++] na TRANSFORM VIEW zavola OPERATOR [OPERATOR++] na FILTER VIEW 2.
		// 2. OPERATOR [OPERATOR++] na FILTER VIEW 2 zavola OPERATOR [OPERATOR++] na FILTER VIEW 1.
		// 3. OPERATOR [OPERATOR++] na FILTER VIEW 1 zavola OPERATOR [OPERATOR++] na VECTOR.
		// 4. OPERATOR [OPERATOR++] na VECTOR posunie ITERATOR na 8. ELEMENT.
		// 5. FILTER 1 VIEW zavola OPERATOR [OPERATOR*]. Ten vrati ELEMENT [22]. Kedze tato VALUE NIE je delitelna 3, zavola sa OPERATOR [OPERATOR++] na VECTOR.
		// 7. OPERATOR [OPERATOR++] na VECTOR posunie END ITERATOR a riadenie sa vrati do FILTER 1 VIEW.
		// 8. OPERATOR [OPERATOR++] na FILTER 1 VIEW vrati riadenie do FILTER 2 VIEW.
		// 9. OPERATOR [OPERATOR++] na FILTER 2 VIEW vrati riadenie do TRANSFORM VIEW, ktory vrati riadenie do CALLING CODE.
		Iterator++;

		if (Iterator==EndIterator)
		{
			break;
		}
	}
	while(false);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ViewCachingPredicate1(int Value)
{
	wcout << L"\tFILTER 1 - VALUE [" << Value << L"]." << endl;

	if ((Value % 3)==0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
bool ViewCachingPredicate2(int Value)
{
	wcout << L"\tFILTER 2 - VALUE [" << Value << L"]." << endl;

	if (Value>=10)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
int ViewCachingTransform(int Value)
{
	wcout << L"\tTRANSFORM - VALUE [" << Value << L"]." << endl;

	int															TransformedValue=-Value;

	return(TransformedValue);
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewCaching(void)
{
	PrintLineSeparator();

	CDumpVector<int>											Range{7,4,3,14,18,6,12,22};
	auto														View=Range | views::filter(ViewCachingPredicate1) | views::filter(ViewCachingPredicate2) | views::transform(ViewCachingTransform);

	wcout << L"ITERATION 1:" << endl;

	// !!! Pri prvej ITERATION je CACHE UPDATED.
	for(int Value : View)
	{
		wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	wcout << L"ITERATION 2:" << endl;

	// !!! Pri dalsej ITERATION je CACHE pouzita.
	for(int Value : View)
	{
		wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestViewCachingWithRangeModifications1(void)
{
	PrintLineSeparator();

	list<int>													Range{1,2,3,4,5};
	auto														View=Range | views::drop(2);

	// !!!!! Modifikacia RANGE PO vykonanim prvej ITERATION, ktora vykona UPDATE CACHE NEPOSOBI NESPRAVNE VYSLEDKY.
	Range.push_front(0);

	wcout << L"COLLECTION:" << endl;

	for(int Value : Range)
	{
		wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
	}

	wcout << L"VIEW ITERATION - BEFORE RANGE MODIFICATION:" << endl;

	// !!! Pri prvej ITERATION je CACHE UPDATED.
	for(int Value : View)
	{
		wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	// !!!!! Modifikacia RANGE PO vykonanim prvej ITERATION, moze sposobit NESPRAVNE VYSLEDKY.
	Range.push_front(-1);

	wcout << L"COLLECTION:" << endl;

	for(int Value : Range)
	{
		wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
	}

	wcout << L"VIEW ITERATION - AFTER RANGE MODIFICATION:" << endl;

	// !!!!! Pouzije sa CACHE, co vzhladom na modifikaciu RANGE vedie k NESPRAVNYM VYSLEDKOM.
	for(int Value : View)
	{
		wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestViewCachingWithRangeModifications2(void)
{
	PrintLineSeparator();

	vector<int>													Range{1,2,3,4};
	auto														View=Range | views::filter([](int Value){return(Value>2);});

	wcout << L"COLLECTION:" << endl;

	for(int Value : Range)
	{
		wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
	}

	wcout << L"VIEW ITERATION - BEFORE RANGE MODIFICATION:" << endl;

	// !!! Pri prvej ITERATION je CACHE UPDATED.
	for(int Value : View)
	{
		wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	// !!!!! Modifikacia RANGE PO vykonanim prvej ITERATION, moze sposobit NESPRAVNE VYSLEDKY.
	++Range[1];
	Range[2]=0;

	wcout << L"COLLECTION:" << endl;

	for(int Value : Range)
	{
		wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
	}

	wcout << L"VIEW ITERATION - AFTER RANGE MODIFICATION:" << endl;

	// !!!!! Pouzije sa CACHE, co vzhladom na modifikaciu RANGE vedie k NESPRAVNYM VYSLEDKOM.
	for(int Value : View)
	{
		wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ViewPerformanceIssuesPredicate1(int Value)
{
	wcout << L"\tFILTER 1 - VALUE [" << Value << L"]." << endl;

	if ((Value % 3)==0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
bool ViewPerformanceIssuesPredicate2(int Value)
{
	wcout << L"\tFILTER 2 - VALUE [" << Value << L"]." << endl;

	if ((Value % 4)==0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
int ViewPerformanceIssuesTransform1(int Value)
{
	wcout << L"\tTRANSFORM 1 - VALUE [" << Value << L"]." << endl;

	int															TransformedValue=-Value;

	return(TransformedValue);
}
//----------------------------------------------------------------------------------------------------------------------
int ViewPerformanceIssuesTransform2(int Value)
{
	wcout << L"\tTRANSFORM 2 - VALUE [" << Value << L"]." << endl;

	int															TransformedValue=-Value;

	return(TransformedValue);
}
//----------------------------------------------------------------------------------------------------------------------
int ViewPerformanceIssuesTransform3(int Value)
{
	wcout << L"\tTRANSFORM 3 - VALUE [" << Value << L"]." << endl;

	int															TransformedValue=-Value;

	return(TransformedValue);
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewPerformanceIssues(void)
{
	PrintLineSeparator();

	{
		vector<int>												Range{1};
		auto													View=Range | views::transform(ViewPerformanceIssuesTransform1) | views::transform(ViewPerformanceIssuesTransform2) | views::filter(ViewPerformanceIssuesPredicate1) | views::transform(ViewPerformanceIssuesTransform3) | views::filter(ViewPerformanceIssuesPredicate2);

		wcout << L"VIEW ITERATION 1:" << endl;

		// !!! Zavolaju sa nasledujuce VIEWS.
	    // 1. VIEW [TRANSFORM_1].
	    // 2. VIEW [TRANSFORM_2].
	    // 3. VIEW [FILTER_1].
		for(int Value : View)
		{
			wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		vector<int>												Range{3};
		auto													View=Range | views::transform(ViewPerformanceIssuesTransform1) | views::transform(ViewPerformanceIssuesTransform2) | views::filter(ViewPerformanceIssuesPredicate1) | views::transform(ViewPerformanceIssuesTransform3) | views::filter(ViewPerformanceIssuesPredicate2);

		wcout << L"VIEW ITERATION 1:" << endl;

		// !!! Zavolaju sa nasledujuce VIEWS.
	    // 1. VIEW [TRANSFORM_1].
	    // 2. VIEW [TRANSFORM_2].
	    // 3. VIEW [FILTER_1].
		// !!! 4. VIEW [TRANSFORM_1].
		// !!! 5. VIEW [TRANSFORM_2].
		// !!! 6. VIEW [TRANSFORM_3].
		// !!! 7. VIEW [FILTER_2].
		for(int Value : View)
		{
			wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		vector<int>												Range{12};
		auto													View=Range | views::transform(ViewPerformanceIssuesTransform1) | views::transform(ViewPerformanceIssuesTransform2) | views::filter(ViewPerformanceIssuesPredicate1) | views::transform(ViewPerformanceIssuesTransform3) | views::filter(ViewPerformanceIssuesPredicate2);

		wcout << L"VIEW ITERATION 1:" << endl;

		// !!! Zavolaju sa nasledujuce VIEWS.
	    // 1. VIEW [TRANSFORM_1].
	    // 2. VIEW [TRANSFORM_2].
	    // 3. VIEW [FILTER_1].
		// !!! 4. VIEW [TRANSFORM_1].
		// !!! 5. VIEW [TRANSFORM_2].
		// !!! 6. VIEW [TRANSFORM_3].
		// !!! 7. VIEW [FILTER_2].
		// !!! 8. VIEW [TRANSFORM_1].
		// !!! 9. VIEW [TRANSFORM_2].
		// !!! 10. VIEW [TRANSFORM_3].
		for(int Value : View)
		{
			wcout << L"!!!!!!!!!! VALUE [" << Value << L"]." << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ViewsLifetimePredicate(int Value)
{
	if (Value>2)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
int ViewsLifetimeTransform(int Value)
{
	int															TransformedValue=-Value;

	return(TransformedValue);
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewsLifetime(void)
{
	PrintLineSeparator();

	{
		CMoveableRangeVector<int>								Range{1,2,3,4,5};

		// !!! VIIEW si ulozi RANGE ako LVALUE REFERENCE.
		auto													View=Range | views::filter(ViewsLifetimePredicate) | views::transform(ViewsLifetimeTransform);

		wcout << L"VIEW ITERATION - LVALUE:" << endl;

		// !!!!! RANGE MUSI existovat pri ITERATION cez VIEW, inak dojde k UNDEFINED BEHAVIOR.
		for(int Value : View)
		{
			wcout << L"\tVALUE [" << Value << L"]." << endl;
		}
	}

	/*
	PrintLineSeparator();

	// !!!!! CODE sposobi UNDEFINED BEHAVIOR.
	{
		CMoveableRangeVector<int>*								Range=new CMoveableRangeVector<int>{1,2,3,4,5};

		// !!! VIIEW si ulozi RANGE ako LVALUE REFERENCE.
		auto													View=*Range | views::filter(ViewsLifetimePredicate) | views::transform(ViewsLifetimeTransform);

		// !!!!! Uvolnenie RANGE na ktory referuje VIEW cez LVALUE REFERENCE sposobi UNDEFINED BEHAVIOR.
		delete(Range);

		wcout << L"VIEW ITERATION - LVALUE:" << endl;

		// !!!!! RANGE MUSI existovat pri ITERATION cez VIEW, inak dojde k UNDEFINED BEHAVIOR.
		// !!!!! CODE sposobi UNDEFINED BEHAVIOR.
		for(int Value : View)
		{
			wcout << L"\tVALUE [" << Value << L"]." << endl;
		}
	}
	*/

	PrintLineSeparator();

	{
		// !!! VIIEW si ulozi RANGE pomocou MOVE SEMANTICS ako RVALUE REFERENCE.
		auto													View=CMoveableRangeVector<int>{1,2,3,4,5} | views::filter(ViewsLifetimePredicate) | views::transform(ViewsLifetimeTransform);

		wcout << L"VIEW ITERATION - RVALUE:" << endl;

		// !!!!! RANGE NEMUSI existovat pri ITERATION cez VIEW, pretoze cez MOVE SEMANTICS bola prenesena do VIEW.
		for(int Value : View)
		{
			wcout << L"\tVALUE [" << Value << L"]." << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ModificationsInViewsPredicate1(const int& Value)
{
	if (Value>2)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tento CODE sposobi UNDEFINED BEHAVIOR.
bool ModificationsInViewsPredicate2(int& Value)
{
	if (Value>2)
	{
		// !!!!! Tento CODE sposobi UNDEFINED BEHAVIOR.
		// !!!!! VIEWS NESMU modifikovat ELEMENTS.
		Value+=100;

		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestModificationsInViews(void)
{
	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5};

		PrintView(L"COLLECTION - BEFORE VIEW:",Range);

		PrintLineSeparator();

		// !!! PIPELINE NEMODIFIKUJE ELEMENT vo svojich VIEWS.
		auto													View=Range | views::filter(ModificationsInViewsPredicate1);

		for(int& Value : View)
		{
			// !!!!! ELEMENTS, ktore su vratene VIEW je mozne modifikovat.
			Value+=100;

			wcout << L"\tVALUE [" << Value << L"]." << endl;
		}

		PrintLineSeparator();

		PrintView(L"COLLECTION - AFTER VIEW:",Range);
	}

	/*
	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!!!! Tento CODE sposobi UNDEFINED BEHAVIOR.
	{
		vector<int>												Range{1,2,3,4,5};

		PrintView(L"COLLECTION - BEFORE VIEW:",Range);

		PrintLineSeparator();

		// !!!!! PIPELINE MODIFIKUJE ELEMENT vo svojich VIEWS, cim sposobi UNDEFINED BEHAVIOR..
		auto													View=Range | views::filter(ModificationsInViewsPredicate2);

		wcout << L"VIEW:" << endl;

		for(int& Value : View)
		{
			wcout << L"\tVALUE [" << Value << L"]." << endl;
		}

		PrintLineSeparator();

		PrintView(L"COLLECTION - AFTER VIEW:",Range);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ModificationsOfRangesPredicate(int Value)
{
	if (Value>2)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestModificationsOfRanges(void)
{
	PrintLineSeparator();

	vector<int>													RangeVector{1,2,3,4,5};

	PrintView(L"VECTOR - BEFORE VIEW:",RangeVector);

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	list<int>													RangeList{1,2,3,4,5};

	PrintView(L"LIST - BEFORE VIEW:",RangeList);

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	auto														VectorView=RangeVector | views::filter(ModificationsOfRangesPredicate);

	// !!!!! Pri ITERATION sa vykona CACHING v danom VIEW.
	PrintView(L"VECTOR - USING VIEW:",VectorView);

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	auto														ListView=RangeList | views::filter(ModificationsOfRangesPredicate);

	// !!!!! Pri ITERATION sa vykona CACHING v danom VIEW.
	PrintView(L"LIST - USING VIEW:",ListView);

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!!!! Do RANGE sa pridaju ELEMENTS pred 1. ELEMENT.
	RangeVector.insert(RangeVector.begin(),{9,0,-1});

	PrintView(L"VECTOR (RANGE) - AFTER MODIFICATION:",RangeVector);

	PrintLineSeparator();

	// !!!!! Pri ITERATION sa vyuzije CACHE v danom VIEW a CODE vrati NESPRAVNE RESULTS.
	PrintView(L"VECTOR (VIEW) - AFTER MODIFICATION:",VectorView);

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!!!! Do RANGE sa pridaju ELEMENTS pred 1. ELEMENT.
	RangeList.insert(RangeList.begin(),{9,0,-1});

	PrintView(L"LIST (RANGE) - AFTER MODIFICATION:",RangeList);

	PrintLineSeparator();

	// !!!!! Pri ITERATION sa vyuzije CACHE v danom VIEW a CODE vrati NESPRAVNE RESULTS.
	PrintView(L"LIST (VIEW) - AFTER MODIFICATION:",ListView);

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!!!! Pri COPYING VECTOR VIEW NEDOCHADZA k modifikaci internej CACHE.
	auto														VectorViewCopy=VectorView;

	// !!!!! Pri ITERATION sa vyuzije NEZMENENA CACHE v danom VIEW a CODE vrati NESPRAVNE RESULTS.
	PrintView(L"VECTOR (VIEW) - AFTER COPYING:",VectorViewCopy);

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!!!! Pri COPYING LIST VIEW DOCHADZA k RESET internej CACHE.
	auto														ListViewCopy=ListView;

	// !!!!! Pri ITERATION sa sa NEVYUZIJE CACHE, kedze pri COPYING bola INVALIDATED. VIEW vrati SPRAVNE RESULTS.
	PrintView(L"LIST (VIEW) - AFTER COPYING:",ListViewCopy);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ConstViewsAsConstReferencePredicate(int Value)
{
	if ((Value%2)==0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION NIE je mozne volat pre vsetky typy VIEWS, pretoze niektore VIEWS modifikuju svoj STATE, a preto ich NIE je mozne pouzit ako CONST VIEW.
template<typename TRangeOfView>
void ConstViewsAsConstReferencePrint(wstring Prefix, const TRangeOfView& RangeOfView)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	for(const auto& Value : RangeOfView)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestConstViewsAsConstReference(void)
{
	PrintLineSeparator();

	vector<int>													RangeVector{1,2,3,4,5,6,7,8};
	list<int>													RangeList{1,2,3,4,5,6,7,8};

	ConstViewsAsConstReferencePrint(L"RANGE VECTOR:",RangeVector);

	PrintLineSeparator();

	ConstViewsAsConstReferencePrint(L"RANGE LIST:",RangeList);

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		auto													View=RangeVector | views::take(3);

		ConstViewsAsConstReferencePrint(L"VIEW VECTOR TAKE:",View);
	}

	PrintLineSeparator();

	{
		auto													View=RangeVector | views::drop(3);

		ConstViewsAsConstReferencePrint(L"VIEW VECTOR DROP:",View);
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		auto													View=RangeList | views::take(3);

		ConstViewsAsConstReferencePrint(L"VIEW LIST TAKE:",View);
	}

	/*
	PrintLineSeparator();

	{
		auto													View=RangeList | views::drop(3);

		// !!!!! COMPILER hodi ERROR, pretoze DROP VIEW modifikuje svoj STATE, a tym padom ho NIE je mozne pouzit ako CONST VIEW.
		ConstViewsAsConstReferencePrint(L"VIEW LIST DROP:",View);
	}
	*/

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		// !!!!! Tento CODE je COMPILED, lebo sa NEPOUZIVA CONST VIEW.
		auto													View=RangeList | views::drop(3);

		wcout << L"VIEW LIST DROP:" << endl;

		size_t													Index=0;

		for(const auto& Value : View)
		{
			wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
		}
	}

	/*
	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		auto													View=RangeVector | views::filter(ConstViewsAsConstReferencePredicate);

		// !!!!! COMPILER hodi ERROR, pretoze FILTER VIEW modifikuje svoj STATE, a tym padom ho NIE je mozne pouzit ako CONST VIEW.
		ConstViewsAsConstReferencePrint(L"VIEW LIST FILTER:",View);
	}
	*/

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		// !!!!! Tento CODE je COMPILED, lebo sa NEPOUZIVA CONST VIEW.
		auto													View=RangeList | views::filter(ConstViewsAsConstReferencePredicate);

		wcout << L"VIEW LIST FILTER:" << endl;

		size_t													Index=0;

		for(const auto& Value : View)
		{
			wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ConstViewsAsNonConstReferencePredicate(int Value)
{
	if ((Value%2)==0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION je mozne volat pre vsetky typy VIEWS, pretoze pouziva NON-CONST VIEWS, prenasany ako RVALUE REFERENCE.
template<typename TRangeOfView>
void ConstViewsAsNonConstReferencePrint(wstring Prefix, TRangeOfView&& RangeOfView)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	for(const auto& Value : RangeOfView)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestConstViewsAsNonConstReference(void)
{
	PrintLineSeparator();

	vector<int>													RangeVector{1,2,3,4,5,6,7,8};
	list<int>													RangeList{1,2,3,4,5,6,7,8};

	ConstViewsAsNonConstReferencePrint(L"RANGE VECTOR:",RangeVector);

	PrintLineSeparator();

	ConstViewsAsNonConstReferencePrint(L"RANGE LIST:",RangeList);

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		auto													View=RangeVector | views::take(3);

		ConstViewsAsNonConstReferencePrint(L"VIEW VECTOR TAKE:",View);
	}

	PrintLineSeparator();

	{
		auto													View=RangeVector | views::drop(3);

		ConstViewsAsNonConstReferencePrint(L"VIEW VECTOR DROP:",View);
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		auto													View=RangeList | views::take(3);

		ConstViewsAsNonConstReferencePrint(L"VIEW LIST TAKE:",View);
	}

	PrintLineSeparator();

	{
		auto													View=RangeList | views::drop(3);

		// !!!!! Tento CODE je COMPILED, pretoze pouziva NON-CONST VIEW.
		ConstViewsAsNonConstReferencePrint(L"VIEW LIST DROP:",View);
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze FILTER VIEW modifikuje svoj STATE, a tym padom ho NIE je mozne pouzit ako CONST VIEW.
		auto													View=RangeVector | views::filter(ConstViewsAsConstReferencePredicate);

		// !!!!! Tento CODE je COMPILED, pretoze pouziva NON-CONST VIEW.
		ConstViewsAsNonConstReferencePrint(L"VIEW LIST FILTER:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ViewsInMultipleThreadsPredicate(int Value)
{
	//Sleep(100);

	if (Value>2)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCollection>
void ViewsInMultipleThreadsPrintThread(wstring Prefix, TCollection&& Collection)
{
	using														ItemType=remove_cvref_t<decltype(*Collection.begin())>;

	ItemType													Sum{};

	for(const ItemType& Item : Collection)
	{
		Sum+=Item;

		wstringstream											StringStream;

		StringStream << L"THREAD [" << Prefix << L"] VALUE [" << Item << L"]." << endl;

		wcout << StringStream.str();
	}

	wstringstream												ResultStringStream;

	ResultStringStream << L"!!!!! THREAD [" << Prefix << L"] SUM [" << Sum << L"]." << endl;

	wcout << ResultStringStream.str();
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CODE sposobuje UNDEFINED BEHAVIOR, pretoze k tomu istemu VIEW sa pristupuje z viacerych THREADS.
void TestViewsInMultipleThreads(void)
{
	PrintLineSeparator();

	list<int>													Range{1,2,3,4,5,6,7,8};

	PrintCollection(L"COLLECTION:",Range);

	/*
	PrintLineSeparator();

	auto														View=Range | views::filter(ViewsInMultipleThreadsPredicate);

	{
		// !!!!! CODE sposobuje UNDEFINED BEHAVIOR, pretoze k tomu istemu VIEW sa pristupuje z viacerych THREADS.
		jthread													Thread1([&]{ViewsInMultipleThreadsPrintThread(L"1",View);});
		jthread													Thread2([&]{ViewsInMultipleThreadsPrintThread(L"2",View);});
		jthread													Thread3([&]{ViewsInMultipleThreadsPrintThread(L"3",View);});

		Thread1.join();
		Thread2.join();
		Thread3.join();
	}
	*/

	PrintLineSeparator();

	wcout << L"THREADS FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pouzije sa CONCEPT CONSTRAINT, ze TYPE PARAMETER MUSI byt RANGE.
template<ranges::input_range TRange>
// !!!!! Pouzije sa CONCEPT CONSTRAINT, ze TYPE PARAMETER NIESMIE byt VIEW.
requires(!ranges::view<TRange>)
void RangesAndViewsAlogorithms(wstring Prefix, const TRange& Range)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	for(const auto& Value : Range)
	{
		wcout << L"RANGE - INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Pouzije sa CONCEPT CONSTRAINT, ze TYPE PARAMETER MUSI byt VIEW.
template<ranges::view TView>
void RangesAndViewsAlogorithms(wstring Prefix, TView View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	for(const auto& Value : View)
	{
		wcout << L"VIEW - INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRangesAndViewsAlogorithms(void)
{
	PrintLineSeparator();

	list<int>													Range{1,2,3,4,5,6,7,8};

	// !!!!! Pouzije sa RANGE VERSION TEMPLATE FUNCTION.
	RangesAndViewsAlogorithms(L"RANGE:",Range);

	PrintLineSeparator();

	auto														View=Range | views::take(3);

	// !!!!! Pouzije sa VIEW VERSION TEMPLATE FUNCTION.
	RangesAndViewsAlogorithms(L"VIEW:",View);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool LINQLikeViewPredicate(int Value)
{
	if (Value>2)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCollection>
void PrintLINQLikeVievNonConst(wstring Prefix, TCollection& Collection)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	for(auto Value : Collection)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCollection>
void PrintLINQLikeViewConst(wstring Prefix, const TCollection& Collection)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	for(const auto& Value : Collection)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestLINQLikeView(void)
{
	PrintLineSeparator();

	vector<int>													Range{1,2,3,4,5,6,7,8};

	PrintLINQLikeViewConst(L"RANGE:",Range);

	PrintLineSeparator();

	CLINQLikeView												LINQLikeView(Range,LINQLikeViewPredicate);

	PrintLINQLikeVievNonConst(L"CONST NON-VIEW:",LINQLikeView);

	PrintLineSeparator();

	PrintLINQLikeViewConst(L"CONST VIEW:",LINQLikeView);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TRange>
void PrintRangeConstnessAsConstReferenceAndConstElements(wstring Prefix, const TRange& Range)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez CONST REFERENCE.
	for(const TElementType& Value : Range)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TRange>
void PrintRangeConstnessAsConstReferenceAndNonConstElements(wstring Prefix, const TRange& Range)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON-CONST REFERENCE.
	// !!!!! COMPILER hodi ERROR.
	for(TElementType& Value : Range)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TRange>
void PrintRangeConstnessAsNonConstReferenceAndNonConstElements(wstring Prefix, TRange& Range)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON-CONST REFERENCE.
	for(TElementType& Value : Range)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestRangeConstness(void)
{
	PrintLineSeparator();

	vector<int>													Range{1,2,3,4,5,6,7,8};

	PrintRangeConstnessAsConstReferenceAndConstElements<int>(L"RANGE by CONST REFERENCE and CONST ELEMENTS:",Range);

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR.
	PrintRangeConstnessAsConstReferenceAndNonConstElements<int>(L"RANGE by CONST REFERENCE and NON CONST ELEMENTS:",Range);
	*/

	PrintLineSeparator();

	PrintRangeConstnessAsNonConstReferenceAndNonConstElements<int>(L"RANGE by NON CONST REFERENCE and NON CONST ELEMENTS:",Range);

	PrintLineSeparator();

	PrintRangeConstnessAsConstReferenceAndConstElements<int>(L"RANGE by CONST REFERENCE and CONST ELEMENTS:",Range);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewLValueConstness1AsConstReferenceAndConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez CONST REFERENCE.
	for(const TElementType& Value : View)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewLValueConstness1AsConstReferenceAndNonConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON CONST REFERENCE.
	// !!!!! COMPILER pri VIEWS, na rozdiel od RANGES NEHODI ERROR.
	for(TElementType& Value : View)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewLValueConstness1(void)
{
	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5,6,7,8};

		ranges::take_view										View(Range,5);

		PrintViewLValueConstness1AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);

		PrintLineSeparator();

		// !!!!! Aj ked je VIEW preneseny ako CONST REFERENCE, VIEW umozni menit ELEMENTS UNDERLYING RANGE.
		PrintViewLValueConstness1AsConstReferenceAndNonConstElements<int>(L"VIEW by CONST REFERENCE and NON CONST ELEMENTS:",View);

		PrintLineSeparator();

		PrintViewLValueConstness1AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewLValueConstness2AsConstReferenceAndConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez CONST REFERENCE.
	for(const TElementType& Value : View)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewLValueConstness2AsConstReferenceAndNonConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON CONST REFERENCE.
	// !!!!! COMPILER pri VIEWS, na rozdiel od RANGES NEHODI ERROR.
	for(TElementType& Value : View)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewLValueConstness2(void)
{
	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5,6,7,8};

		auto													View=Range | views::take(5);

		PrintViewLValueConstness2AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);

		PrintLineSeparator();

		// !!!!! Aj ked je VIEW preneseny ako CONST REFERENCE, VIEW umozni menit ELEMENTS UNDERLYING RANGE.
		PrintViewLValueConstness2AsConstReferenceAndNonConstElements<int>(L"VIEW by CONST REFERENCE and NON CONST ELEMENTS:",View);

		PrintLineSeparator();

		PrintViewLValueConstness2AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewLValueConstness3AsConstReferenceAndConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez CONST REFERENCE.
	for(const TElementType& Value : View)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewLValueConstness3AsConstReferenceAndNonConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON CONST REFERENCE.
	// !!!!! COMPILER pri VIEWS, na rozdiel od RANGES NEHODI ERROR.
	for(TElementType& Value : View)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewLValueConstness3(void)
{
	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5,6,7,8};

		auto													View=Range | views::drop(5);

		PrintViewLValueConstness3AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);

		PrintLineSeparator();

		// !!!!! Aj ked je VIEW preneseny ako CONST REFERENCE, VIEW umozni menit ELEMENTS UNDERLYING RANGE.
		PrintViewLValueConstness3AsConstReferenceAndNonConstElements<int>(L"VIEW by CONST REFERENCE and NON CONST ELEMENTS:",View);

		PrintLineSeparator();

		PrintViewLValueConstness3AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewLValueConstness4AsConstReferenceAndConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez CONST REFERENCE.
	for(const TElementType& Value : View)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewLValueConstness4AsConstReferenceAndNonConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON CONST REFERENCE.
	// !!!!! COMPILER pri VIEWS, na rozdiel od RANGES NEHODI ERROR.
	for(TElementType& Value : View)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewLValueConstness4(void)
{
	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5,6,7,8};

		auto													View=views::all(Range);

		PrintViewLValueConstness4AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);

		PrintLineSeparator();

		// !!!!! Aj ked je VIEW preneseny ako CONST REFERENCE, VIEW umozni menit ELEMENTS UNDERLYING RANGE.
		PrintViewLValueConstness4AsConstReferenceAndNonConstElements<int>(L"VIEW by CONST REFERENCE and NON CONST ELEMENTS:",View);

		PrintLineSeparator();

		PrintViewLValueConstness4AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewRValueConstness1AsConstReferenceAndConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez CONST REFERENCE.
	for(const TElementType& Value : View)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewRValueConstness1AsConstReferenceAndNonConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON CONST REFERENCE.
	for(TElementType& Value : View)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewRValueConstness1(void)
{
	PrintLineSeparator();

	{
		// !!! Pouzije sa RVALUE REFERENCE.
		PrintViewRValueConstness1AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",vector<int>{1,2,3,4,5,6,7,8} | views::drop(5));

		/*
		PrintLineSeparator();

		// !!!!! VIEW preneseny ako RVALUE REFERENCE ZACHOVAVA CONSTNESS. To znamena, ze nasledujuci CODE hodi ERROR, pretoze k ELEMENTS daneho VIEW NIE je mozne pristupovat ako k NON CONST ELEMENTS a modifikovat ich.
		PrintViewRValueConstness1AsConstReferenceAndNonConstElements<int>(L"VIEW by CONST REFERENCE and NON CONST ELEMENTS:",vector<int>{1,2,3,4,5,6,7,8} | views::drop(5));
		*/

		PrintLineSeparator();

		// !!! Pouzije sa RVALUE REFERENCE.
		PrintViewRValueConstness1AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",vector<int>{1,2,3,4,5,6,7,8} | views::drop(5));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewRValueConstness2AsConstReferenceAndConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez CONST REFERENCE.
	for(const TElementType& Value : View)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewRValueConstness2AsConstReferenceAndNonConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON CONST REFERENCE.
	for(TElementType& Value : View)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewRValueConstness2(void)
{
	PrintLineSeparator();

	{
		// !!! Pouzije sa RVALUE REFERENCE.
		PrintViewRValueConstness2AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",vector<int>{1,2,3,4,5,6,7,8} | views::take(5));

		/*
		PrintLineSeparator();

		// !!!!! VIEW preneseny ako RVALUE REFERENCE ZACHOVAVA CONSTNESS. To znamena, ze nasledujuci CODE hodi ERROR, pretoze k ELEMENTS daneho VIEW NIE je mozne pristupovat ako k NON CONST ELEMENTS a modifikovat ich.
		PrintViewRValueConstness2AsConstReferenceAndNonConstElements<int>(L"VIEW by CONST REFERENCE and NON CONST ELEMENTS:",vector<int>{1,2,3,4,5,6,7,8} | views::take(5));
		*/

		PrintLineSeparator();

		// !!! Pouzije sa RVALUE REFERENCE.
		PrintViewRValueConstness2AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",vector<int>{1,2,3,4,5,6,7,8} | views::take(5));
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewConstRange1AsConstReferenceAndConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez CONST REFERENCE.
	for(const TElementType& Value : View)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewConstRange1AsConstReferenceAndNonConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON CONST REFERENCE.
	for(TElementType& Value : View)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewConstRange1(void)
{
	PrintLineSeparator();

	{
		// !!!!! RANGE je definovany ako CONST RANGE.
		const vector<int>										Range{1,2,3,4,5,6,7,8};

		PrintViewConstRange1AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",Range);

		/*
		PrintLineSeparator();

		// !!!!! VIEW je vytvoreny nad CONST RANGE, a preto NEUMOZNUJE modifikaciu ELEMENTS daneho RANGE.
		PrintViewConstRange1AsConstReferenceAndNonConstElements<int>(L"VIEW by CONST REFERENCE and NON CONST ELEMENTS:",Range);
		*/

		PrintLineSeparator();

		PrintViewConstRange1AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",Range);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewConstRange2AsConstReferenceAndConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez CONST REFERENCE.
	for(const TElementType& Value : View)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewConstRange2AsConstReferenceAndNonConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON CONST REFERENCE.
	for(TElementType& Value : View)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewConstRange2(void)
{
	PrintLineSeparator();

	{
		// !!!!! RANGE je definovany ako NON CONST RANGE.
		vector<int>												Range{1,2,3,4,5,6,7,8};

		// !!!!! Pri vyvarani VIEW je RANGE konvertovany na CONST RANGE pomocou FUNCTION [as_const(Range)].
		ranges::take_view										View(as_const(Range),5);

		PrintViewConstRange2AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);

		/*
		PrintLineSeparator();

		// !!!!! VIEW je vytvoreny nad CONST RANGE, a preto NEUMOZNUJE modifikaciu ELEMENTS daneho RANGE.
		PrintViewConstRange2AsConstReferenceAndNonConstElements<int>(L"VIEW by CONST REFERENCE and NON CONST ELEMENTS:",View);
		*/

		PrintLineSeparator();

		PrintViewConstRange2AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewConstRange3AsConstReferenceAndConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez CONST REFERENCE.
	for(const TElementType& Value : View)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewConstRange3AsConstReferenceAndNonConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON CONST REFERENCE.
	for(TElementType& Value : View)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewConstRange3(void)
{
	PrintLineSeparator();

	{
		// !!!!! RANGE je definovany ako NON CONST RANGE.
		vector<int>												Range{1,2,3,4,5,6,7,8};

		// !!!!! Pri vyvarani VIEW je RANGE konvertovany na CONST RANGE pomocou FUNCTION [as_const(Range)].
		auto													View=as_const(Range) | views::drop(5);

		PrintViewConstRange3AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);

		/*
		PrintLineSeparator();

		// !!!!! VIEW je vytvoreny nad CONST RANGE, a preto NEUMOZNUJE modifikaciu ELEMENTS daneho RANGE.
		PrintViewConstRange3AsConstReferenceAndNonConstElements<int>(L"VIEW by CONST REFERENCE and NON CONST ELEMENTS:",View);
		*/

		PrintLineSeparator();

		PrintViewConstRange3AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewConstRange4AsConstReferenceAndConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez CONST REFERENCE.
	for(const TElementType& Value : View)
	{
		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TElementType, typename TView>
void PrintViewConstRange4AsConstReferenceAndNonConstElements(wstring Prefix, const TView& View)
{
	wcout << Prefix << endl;

	size_t														Index=0;

	// !!!!! K ELEMENTS sa pristupuje cez NON CONST REFERENCE.
	for(TElementType& Value : View)
	{
		// !!!!! Kedze ELEMENT je NON-CONST, je ho mozne MODIFIKOVAT.
		Value=-Value;

		wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestViewConstRange4(void)
{
	PrintLineSeparator();

	{
		// !!!!! RANGE je definovany ako NON CONST RANGE.
		vector<int>												Range{1,2,3,4,5,6,7,8};

		// !!!!! VIEW sa vytvori ako CONST VIEW pomocou FUNCTION [views::as_const(Range)].
		ranges::as_const_view									View=views::as_const(Range | views::drop(5));

		PrintViewConstRange4AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);

		/*
		PrintLineSeparator();

		// !!!!! CONST VIEW NEUMOZNUJE modifikaciu ELEMENTS daneho RANGE.
		PrintViewConstRange4AsConstReferenceAndNonConstElements<int>(L"VIEW by CONST REFERENCE and NON CONST ELEMENTS:",View);
		*/

		PrintLineSeparator();

		PrintViewConstRange4AsConstReferenceAndConstElements<int>(L"VIEW by CONST REFERENCE and CONST ELEMENTS:",View);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestConstnessInViews(void)
{
	PrintLineSeparator();

	vector<int>													Range{1,2,3,4,5,6,7,8};

	PrintCollection(L"RANGE:",Range);

	PrintLineSeparator();

	{
		wcout << L"CONST VIEW:" << endl;

		auto													View=Range | views::drop(5);
		size_t													Index=0;

		// !!!!! Zabranit modifikacii VIEW ELEMENT je mozne pristupom k ELEMENTS pomocou CONST REFERENCES.
		for(const int& Value : View)
		{
			// !!!!! Kedze ELEMENT je CONST, NIE je ho mozne MODIFIKOVAT.
			//Value=-Value;

			wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		wcout << L"CONST VIEW:" << endl;

		auto													View=Range | views::drop(5);
		size_t													Index=0;

		for(int& RawValue : View)
		{
			// !!!!! Zabranit modifikacii VIEW ELEMENT je mozne pouzitim FUNCTION [std::as_const()].
			const int&											Value=as_const(RawValue);

			// !!!!! Kedze ELEMENT je CONST, NIE je ho mozne MODIFIKOVAT.
			//Value=-Value;

			wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestConstnessProblemsInViews1(void)
{
	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5,6,7,8};

		PrintCollection(L"RANGE:",Range);

		PrintLineSeparator();

		auto													View=Range | views::drop(2);
		size_t													Index=0;

		wcout << L"VIEW:" << endl;

		for (auto Iterator=std::cbegin(View);Iterator!=std::cend(View);++Iterator)
		{
			// !!!!! Pre chybnu implementaciu FUNCTION [std::cbegin()] a FUNCTION [std::cend()] je mozne z ITERATOR ziskat NON-CONST REFERENCE, vdaka comu je mozne zmenit VALUES povodneho RANGE.
			int&											Value=*Iterator;

			Value=-Value;

			wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
		}

		PrintLineSeparator();

		PrintCollection(L"RANGE:",Range);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestConstnessProblemsInViews2(void)
{
	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5,6,7,8};

		PrintCollection(L"RANGE:",Range);

		PrintLineSeparator();

		auto													View=Range | views::drop(2);
		size_t													Index=0;

		wcout << L"VIEW:" << endl;

		for (auto Iterator=ranges::cbegin(View);Iterator!=ranges::cend(View);++Iterator)
		{
			const int&											Value=*Iterator;

			wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
		}

		PrintLineSeparator();

		PrintCollection(L"RANGE:",Range);
	}

	/*
	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5,6,7,8};

		PrintCollection(L"RANGE:",Range);

		PrintLineSeparator();

		auto													View=Range | views::drop(2);
		size_t													Index=0;

		wcout << L"VIEW:" << endl;

		for (auto Iterator=ranges::cbegin(View);Iterator!=ranges::cend(View);++Iterator)
		{
			// !!!!! Implementacia FUNCTION [ranges::cbegin()] a FUNCTION [ranges::cend()] uz boli v C++ 23 FIXED a pre VIEWS a GARANTUJU CONSTNESS.
			// !!!!! Tento CODE NIE je COMPILED.
			int&												Value=*Iterator;

			Value=-Value;

			wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
		}

		PrintLineSeparator();

		PrintCollection(L"RANGE:",Range);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestConstnessProblemsInViews3(void)
{
	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5,6,7,8};

		PrintCollection(L"RANGE:",Range);

		PrintLineSeparator();

		auto													View=Range | views::drop(2);
		size_t													Index=0;

		wcout << L"VIEW:" << endl;

		for (auto Iterator=View.cbegin();Iterator!=View.cend();++Iterator)
		{
			const int&											Value=*Iterator;

			wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
		}

		PrintLineSeparator();

		PrintCollection(L"RANGE:",Range);
	}

	/*
	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		vector<int>												Range{1,2,3,4,5,6,7,8};

		PrintCollection(L"RANGE:",Range);

		PrintLineSeparator();

		auto													View=Range | views::drop(2);
		size_t													Index=0;

		wcout << L"VIEW:" << endl;

		for (auto Iterator=View.cbegin();Iterator!=View.cend();++Iterator)
		{
			// !!!!! Implementacia METHOD [cbegin()] a METHOD [cend()] v C++ 23 GARANTUJU pre VIEWS CONSTNESS.
			// !!!!! Tento CODE NIE je COMPILED.
			int&												Value=*Iterator;

			Value=-Value;

			wcout << L"INDEX [" << (Index+++1) << L"] VALUE [" << Value << L"]." << endl;
		}

		PrintLineSeparator();

		PrintCollection(L"RANGE:",Range);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main()
{
	SafeMain();

	//TestSimpleUse();
	//TestRangesConcepts();
	//TestViewsRangeAdaptors1();
	//TestViewsRangeAdaptors2();
	//TestViewsPipelines1();
	//TestViewsPipelines2();
	//TestGeneratingViews();
	//TestViewsTypes();
	//TestViewsTypesConstructors();
	//TestWritableViews();
	//TestLazyEvaluation();
	//TestViewsCaching();
	//TestSentinels();
	//TestCArraysAsRanges();
	//TestSubrangeType();
	//TestCountedRanges();
	//TestProjections();
	//TestRangesUtilities();
	//TestBorrowedIterators();
	//TestBorrowedRanges();
	//TestRangesToViews();
	//TestViewCreations();
	//TestViewConversions();
	//TestViewsLazyEvaluation1();
	//TestViewsLazyEvaluation2();
	//TestViewCaching();
	//TestViewCachingWithRangeModifications1();
	//TestViewCachingWithRangeModifications2();
	//TestViewPerformanceIssues();
	//TestViewsLifetime();
	//TestModificationsInViews();
	//TestModificationsOfRanges();
	//TestConstViewsAsConstReference();
	//TestConstViewsAsNonConstReference();
	//TestViewsInMultipleThreads();
	//TestRangesAndViewsAlogorithms();
	//TestLINQLikeView();
	//TestRangeConstness();
	//TestViewLValueConstness1();
	//TestViewLValueConstness2();
	//TestViewLValueConstness3();
	//TestViewLValueConstness4();
	//TestViewRValueConstness1();
	//TestViewRValueConstness2();
	//TestViewConstRange1();
	//TestViewConstRange2();
	//TestViewConstRange3();
	//TestViewConstRange4();
	//TestConstnessInViews();
	//TestConstnessProblemsInViews1();
	TestConstnessProblemsInViews2();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------