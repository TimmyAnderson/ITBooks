//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectAwaitTransform.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaitTransform::CCoroutineObjectAwaitTransform(coroutine_handle<SCoroutineObjectAwaitTransformPromiseType<CCoroutineObjectAwaitTransform>> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaitTransform::CCoroutineObjectAwaitTransform(CCoroutineObjectAwaitTransform&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaitTransform::~CCoroutineObjectAwaitTransform(void) noexcept
{
	if (static_cast<bool>(MHandle)==true)
	{
		MHandle.destroy();
		MHandle=nullptr;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaitTransform& CCoroutineObjectAwaitTransform::operator=(CCoroutineObjectAwaitTransform&& Other) noexcept
{
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
bool CCoroutineObjectAwaitTransform::Resume(void) const
{
	if (static_cast<bool>(MHandle)==false || MHandle.done()==true)
	{
		return(false);
	}

	MHandle.resume();

	bool														CanResume=(!MHandle.done());

	return(CanResume);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CCoroutineObjectAwaitTransform::GetValue1(void) const noexcept
{
	promise_type&												Promise=MHandle.promise();
	int															Value=Promise.GetValue1();

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
double CCoroutineObjectAwaitTransform::GetValue2(void) const noexcept
{
	promise_type&												Promise=MHandle.promise();
	double														Value=Promise.GetValue2();

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------