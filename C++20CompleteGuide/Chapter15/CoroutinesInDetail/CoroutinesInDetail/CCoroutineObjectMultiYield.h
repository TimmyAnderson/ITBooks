//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
struct SCoroutineObjectMultiYieldPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TYieldValue1											MValue1;
		TYieldValue2											MValue2;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);

		// !!!!! METHOD [TAWaiterType yield_value(TYieldValue Value)] moze byt OVERLOADED.
		std::suspend_always yield_value(const TYieldValue1& Value);
		std::suspend_always yield_value(const TYieldValue2& Value);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;

	public:
		const TYieldValue1& GetValue1(void) const noexcept;
		const TYieldValue2& GetValue2(void) const noexcept;

	public:
		SCoroutineObjectMultiYieldPromiseType(void);
		~SCoroutineObjectMultiYieldPromiseType(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
SCoroutineObjectMultiYieldPromiseType<TCoroutineObject,TYieldValue1,TYieldValue2>::SCoroutineObjectMultiYieldPromiseType(void)
	: MValue1(), MValue2()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
SCoroutineObjectMultiYieldPromiseType<TCoroutineObject,TYieldValue1,TYieldValue2>::~SCoroutineObjectMultiYieldPromiseType(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
TCoroutineObject SCoroutineObjectMultiYieldPromiseType<TCoroutineObject,TYieldValue1,TYieldValue2>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectMultiYieldPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
std::suspend_always SCoroutineObjectMultiYieldPromiseType<TCoroutineObject,TYieldValue1,TYieldValue2>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
void SCoroutineObjectMultiYieldPromiseType<TCoroutineObject,TYieldValue1,TYieldValue2>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
std::suspend_always SCoroutineObjectMultiYieldPromiseType<TCoroutineObject,TYieldValue1,TYieldValue2>::yield_value(const TYieldValue1& Value)
{
	MValue1=Value;

	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
std::suspend_always SCoroutineObjectMultiYieldPromiseType<TCoroutineObject,TYieldValue1,TYieldValue2>::yield_value(const TYieldValue2& Value)
{
	MValue2=Value;

	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
void SCoroutineObjectMultiYieldPromiseType<TCoroutineObject,TYieldValue1,TYieldValue2>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
std::suspend_always SCoroutineObjectMultiYieldPromiseType<TCoroutineObject,TYieldValue1,TYieldValue2>::SCoroutineObjectMultiYieldPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
const TYieldValue1& SCoroutineObjectMultiYieldPromiseType<TCoroutineObject,TYieldValue1,TYieldValue2>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue1, typename TYieldValue2>
const TYieldValue2& SCoroutineObjectMultiYieldPromiseType<TCoroutineObject,TYieldValue1,TYieldValue2>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValue1, typename TYieldValue2>
class [[nodiscard]] CCoroutineObjectMultiYield final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectMultiYieldPromiseType<CCoroutineObjectMultiYield,TYieldValue1,TYieldValue2>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectMultiYield& operator=(const CCoroutineObjectMultiYield&)=delete;
		CCoroutineObjectMultiYield& operator=(CCoroutineObjectMultiYield&& Other) noexcept;

	public:
		bool Resume(void) const;
		
	public:
		const TYieldValue1& GetValue1(void) const noexcept;
		const TYieldValue2& GetValue2(void) const noexcept;

	public:
		CCoroutineObjectMultiYield(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectMultiYield(const CCoroutineObjectMultiYield&)=delete;
		CCoroutineObjectMultiYield(CCoroutineObjectMultiYield&& Other) noexcept;
		~CCoroutineObjectMultiYield(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValue1, typename TYieldValue2>
CCoroutineObjectMultiYield<TYieldValue1,TYieldValue2>::CCoroutineObjectMultiYield(std::coroutine_handle<promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValue1, typename TYieldValue2>
CCoroutineObjectMultiYield<TYieldValue1,TYieldValue2>::CCoroutineObjectMultiYield(CCoroutineObjectMultiYield&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValue1, typename TYieldValue2>
CCoroutineObjectMultiYield<TYieldValue1,TYieldValue2>::~CCoroutineObjectMultiYield(void) noexcept
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
template<typename TYieldValue1, typename TYieldValue2>
CCoroutineObjectMultiYield<TYieldValue1,TYieldValue2>& CCoroutineObjectMultiYield<TYieldValue1,TYieldValue2>::operator=(CCoroutineObjectMultiYield&& Other) noexcept
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
template<typename TYieldValue1, typename TYieldValue2>
bool CCoroutineObjectMultiYield<TYieldValue1,TYieldValue2>::Resume(void) const
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
template<typename TYieldValue1, typename TYieldValue2>
const TYieldValue1& CCoroutineObjectMultiYield<TYieldValue1,TYieldValue2>::GetValue1(void) const noexcept
{
	promise_type&												Promise=MHandle.promise();
	const TYieldValue1&											Value1=Promise.GetValue1();

	return(Value1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValue1, typename TYieldValue2>
const TYieldValue2& CCoroutineObjectMultiYield<TYieldValue1,TYieldValue2>::GetValue2(void) const noexcept
{
	promise_type&												Promise=MHandle.promise();
	const TYieldValue2&											Value2=Promise.GetValue2();

	return(Value2);
}
//----------------------------------------------------------------------------------------------------------------------