//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue1, typename TReturnValue2>
struct SCoroutineObjectMultiReturnPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TReturnValue1											MValue1;
		TReturnValue2											MValue2;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);

		// !!!!! METHOD [void yield_value(TReturnValue Value)] moze byt OVERLOADED.
		void return_value(const TReturnValue1& Value);
		void return_value(const TReturnValue2& Value);
		std::suspend_always final_suspend(void) noexcept;

	public:
		const TReturnValue1& GetValue1(void) const noexcept;
		const TReturnValue2& GetValue2(void) const noexcept;

	public:
		SCoroutineObjectMultiReturnPromiseType(void);
		~SCoroutineObjectMultiReturnPromiseType(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue1, typename TReturnValue2>
SCoroutineObjectMultiReturnPromiseType<TCoroutineObject,TReturnValue1,TReturnValue2>::SCoroutineObjectMultiReturnPromiseType(void)
	: MValue1(), MValue2()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue1, typename TReturnValue2>
SCoroutineObjectMultiReturnPromiseType<TCoroutineObject,TReturnValue1,TReturnValue2>::~SCoroutineObjectMultiReturnPromiseType(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue1, typename TReturnValue2>
TCoroutineObject SCoroutineObjectMultiReturnPromiseType<TCoroutineObject,TReturnValue1,TReturnValue2>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectMultiReturnPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue1, typename TReturnValue2>
std::suspend_always SCoroutineObjectMultiReturnPromiseType<TCoroutineObject,TReturnValue1,TReturnValue2>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue1, typename TReturnValue2>
void SCoroutineObjectMultiReturnPromiseType<TCoroutineObject,TReturnValue1,TReturnValue2>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue1, typename TReturnValue2>
void SCoroutineObjectMultiReturnPromiseType<TCoroutineObject,TReturnValue1,TReturnValue2>::return_value(const TReturnValue1& Value)
{
	MValue1=Value;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue1, typename TReturnValue2>
void SCoroutineObjectMultiReturnPromiseType<TCoroutineObject,TReturnValue1,TReturnValue2>::return_value(const TReturnValue2& Value)
{
	MValue2=Value;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue1, typename TReturnValue2>
std::suspend_always SCoroutineObjectMultiReturnPromiseType<TCoroutineObject,TReturnValue1,TReturnValue2>::SCoroutineObjectMultiReturnPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue1, typename TReturnValue2>
const TReturnValue1& SCoroutineObjectMultiReturnPromiseType<TCoroutineObject,TReturnValue1,TReturnValue2>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue1, typename TReturnValue2>
const TReturnValue2& SCoroutineObjectMultiReturnPromiseType<TCoroutineObject,TReturnValue1,TReturnValue2>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue1, typename TReturnValue2>
class [[nodiscard]] CCoroutineObjectMultiReturn final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectMultiReturnPromiseType<CCoroutineObjectMultiReturn,TReturnValue1,TReturnValue2>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectMultiReturn& operator=(const CCoroutineObjectMultiReturn&)=delete;
		CCoroutineObjectMultiReturn& operator=(CCoroutineObjectMultiReturn&& Other) noexcept;

	public:
		bool Resume(void) const;
		
	public:
		const TReturnValue1& GetValue1(void) const noexcept;
		const TReturnValue2& GetValue2(void) const noexcept;

	public:
		CCoroutineObjectMultiReturn(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectMultiReturn(const CCoroutineObjectMultiReturn&)=delete;
		CCoroutineObjectMultiReturn(CCoroutineObjectMultiReturn&& Other) noexcept;
		~CCoroutineObjectMultiReturn(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue1, typename TReturnValue2>
CCoroutineObjectMultiReturn<TReturnValue1,TReturnValue2>::CCoroutineObjectMultiReturn(std::coroutine_handle<promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue1, typename TReturnValue2>
CCoroutineObjectMultiReturn<TReturnValue1,TReturnValue2>::CCoroutineObjectMultiReturn(CCoroutineObjectMultiReturn&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue1, typename TReturnValue2>
CCoroutineObjectMultiReturn<TReturnValue1,TReturnValue2>::~CCoroutineObjectMultiReturn(void) noexcept
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
template<typename TReturnValue1, typename TReturnValue2>
CCoroutineObjectMultiReturn<TReturnValue1,TReturnValue2>& CCoroutineObjectMultiReturn<TReturnValue1,TReturnValue2>::operator=(CCoroutineObjectMultiReturn&& Other) noexcept
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
template<typename TReturnValue1, typename TReturnValue2>
bool CCoroutineObjectMultiReturn<TReturnValue1,TReturnValue2>::Resume(void) const
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
template<typename TReturnValue1, typename TReturnValue2>
const TReturnValue1& CCoroutineObjectMultiReturn<TReturnValue1,TReturnValue2>::GetValue1(void) const noexcept
{
	promise_type&												Promise=MHandle.promise();
	const TReturnValue1&										Value1=Promise.GetValue1();

	return(Value1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue1, typename TReturnValue2>
const TReturnValue2& CCoroutineObjectMultiReturn<TReturnValue1,TReturnValue2>::GetValue2(void) const noexcept
{
	promise_type&												Promise=MHandle.promise();
	const TReturnValue2&										Value2=Promise.GetValue2();

	return(Value2);
}
//----------------------------------------------------------------------------------------------------------------------