//----------------------------------------------------------------------------------------------------------------------
#include "CTracerSort.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CTracerSort::CTracerSort(int Value)
	: MValue(Value), MGeneration(1)
{
	long														Created;
	long														Destroyed;

	MMutex.lock();

	++MCreated;

	UpdateMaxLive();

	Created=MCreated;
	Destroyed=MDestroyed;

	MMutex.unlock();

	wcout << L"SORT TRACER - CONSTRUCTION - GENERATION [" << MGeneration << L"] CREATED [" << Created << L"] DESTROYED [" << Destroyed << L"] (CREATED-DESTROYED) [" << (Created-Destroyed) << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CTracerSort::CTracerSort(const CTracerSort& Other)
	: MValue(Other.MValue), MGeneration(Other.MGeneration+1)
{
	long														Created;
	long														Destroyed;

	MMutex.lock();

	++MCreated;

	UpdateMaxLive();

	Created=MCreated;
	Destroyed=MDestroyed;

	MMutex.unlock();

	wcout << L"SORT TRACER - COPY CONSTRUCTION - GENERATION [" << MGeneration << L"] CREATED [" << Created << L"] DESTROYED [" << Destroyed << L"] (CREATED-DESTROYED) [" << (Created-Destroyed) << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CTracerSort::~CTracerSort(void) noexcept
{
	long														Created;
	long														Destroyed;

	MMutex.lock();

	++MDestroyed;

	UpdateMaxLive();

	Created=MCreated;
	Destroyed=MDestroyed;

	MMutex.unlock();

	wcout << L"SORT TRACER - DESTRUCTION - GENERATION [" << MGeneration << L"] CREATED [" << Created << L"] DESTROYED [" << Destroyed << L"] (CREATED-DESTROYED) [" << (Created-Destroyed) << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CTracerSort& CTracerSort::operator=(const CTracerSort& Other)
{
	long														Assigned;

	CTracerSort::MMutex.lock();

	Assigned=++CTracerSort::MAssigned;

	CTracerSort::MMutex.unlock();

	wcout << L"SORT TRACER - ASSIGNMENT - ASSIGNED [" << Assigned << L"] OTHER.GENERATION [" << Other.MGeneration << L"]." << endl;

	MValue=Other.MValue;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool operator<(const CTracerSort& Value1, const CTracerSort& Value2)
{
	long														Compared;

	CTracerSort::MMutex.lock();

	Compared=++CTracerSort::MCompared;

	CTracerSort::MMutex.unlock();
	
	wcout << L"SORT TRACER - COMPARISON - COMPARED [" << Compared << L"] VALUE_1.GENERATION [" << Value1.MGeneration << L"] VALUE_2.GENERATION [" << Value2.MGeneration << L"]." << endl;
	
	bool														Result=(Value1.MValue<Value2.MValue);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CTracerSort::UpdateMaxLive(void)
{
	MMutex.lock();

	if ((MCreated-MDestroyed)>MMaxLive)
	{
		MMaxLive=(MCreated-MDestroyed);
	}

	MMutex.unlock();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CTracerSort::Reset(void)
{
	MMutex.lock();

	MCreated=0;
	MDestroyed=0;
	MAssigned=0;
	MCompared=0;
	MMaxLive=0;

	MMutex.unlock();
}
//----------------------------------------------------------------------------------------------------------------------
long CTracerSort::GetCreations(void)
{
	long														Created;

	MMutex.lock();

	Created=MCreated;

	MMutex.unlock();

	return(Created);
}
//----------------------------------------------------------------------------------------------------------------------
long CTracerSort::GetDestructions(void)
{
	long														Destroyed;

	MMutex.lock();

	Destroyed=MDestroyed;

	MMutex.unlock();

	return(Destroyed);
}
//----------------------------------------------------------------------------------------------------------------------
long CTracerSort::GetAssignments(void)
{
	long														Assigned;

	MMutex.lock();

	Assigned=MAssigned;

	MMutex.unlock();

	return(Assigned);
}
//----------------------------------------------------------------------------------------------------------------------
long CTracerSort::GetComparisons(void)
{
	long														Compared;

	MMutex.lock();

	Compared=MCompared;

	MMutex.unlock();

	return(Compared);
}
//----------------------------------------------------------------------------------------------------------------------
long CTracerSort::GetMaxLive(void)
{
	long														MaxLive;

	MMutex.lock();

	MaxLive=MMaxLive;

	MMutex.unlock();

	return(MaxLive);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CTracerSort::GetValue(void) const
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------