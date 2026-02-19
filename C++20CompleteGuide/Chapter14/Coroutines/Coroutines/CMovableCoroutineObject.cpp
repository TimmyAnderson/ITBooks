//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CMovableCoroutineObject.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CMovableCoroutineObject::CMovableCoroutineObject(coroutine_handle<SMovableCoroutineObjectPromiseType<CMovableCoroutineObject>> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CMovableCoroutineObject::CMovableCoroutineObject(CMovableCoroutineObject&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	wcout << L"COROUTINE MOVE CONSTRUCTOR CALLED." << endl;

	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CMovableCoroutineObject::~CMovableCoroutineObject(void) noexcept
{
	wcout << L"COROUTINE DESTRUCTOR CALLED." << endl;

	if (static_cast<bool>(MHandle)==true)
	{
		wcout << L"COROUTINE DESTRUCTOR RELEASED COROUTINE HANDLE." << endl;

		// !!! Uvolni sa instancia COROUTINE HANDLE.
		MHandle.destroy();
		MHandle=nullptr;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CMovableCoroutineObject& CMovableCoroutineObject::operator=(CMovableCoroutineObject&& Other) noexcept
{
	wcout << L"COROUTINE MOVE OPERATOR CALLED." << endl;

	if (this!=&Other)
	{
		if (static_cast<bool>(MHandle)==true)
		{
			MHandle.destroy();
			MHandle=nullptr;
		}

		MHandle=move(Other.MHandle);

		Other.MHandle=nullptr;
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CMovableCoroutineObject::Resume(void) const
{
	// !!! Vykona sa kontrola, ci COROUTINE HANDLE nie je uvolneny, alebo COROUTINE uz neskoncila.
	if (static_cast<bool>(MHandle)==false || MHandle.done()==true)
	{
		return(false);
	}

	// !!! Vykona sa RESUME COROUTINE, ktoru reprezentuje COROUTINE HANDLE.
	// !!! Volanie METHOD [void coroutine_handle::resume(void) const] je BLOCKING. To znamena, ze METHOD sa neskonci, kym COROUTINE nevykona dalsi SUSPEND.
	MHandle.resume();

	// !!! Vykona sa kontrola ci COROUTINE uz neskoncila.
	bool														CanResume=(!MHandle.done());

	return(CanResume);
}
//----------------------------------------------------------------------------------------------------------------------