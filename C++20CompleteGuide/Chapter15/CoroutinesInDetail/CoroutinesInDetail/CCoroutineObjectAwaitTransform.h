//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectAwaitTransformPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue1;
		double													MValue2;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;

	public:
		std::suspend_always await_transform(int Value);
		std::suspend_always await_transform(double Value);

	public:
		int GetValue1(void) const noexcept;
		double GetValue2(void) const noexcept;

	public:
		SCoroutineObjectAwaitTransformPromiseType(void);
		~SCoroutineObjectAwaitTransformPromiseType(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectAwaitTransformPromiseType<TCoroutineObject>::SCoroutineObjectAwaitTransformPromiseType(void)
	: MValue1(), MValue2()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectAwaitTransformPromiseType<TCoroutineObject>::~SCoroutineObjectAwaitTransformPromiseType(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectAwaitTransformPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle<SCoroutineObjectAwaitTransformPromiseType>	Handle=std::coroutine_handle<SCoroutineObjectAwaitTransformPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectAwaitTransformPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectAwaitTransformPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectAwaitTransformPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectAwaitTransformPromiseType<TCoroutineObject>::SCoroutineObjectAwaitTransformPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectAwaitTransformPromiseType<TCoroutineObject>::await_transform(int Value)
{
	std::wcout << "METHOD [suspend_always await_transform(int Value)] CALLED. VALUE [" << Value << L"]." << std::endl;

	MValue1=Value;

	std::suspend_always											Awaiter{};

	return(Awaiter);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectAwaitTransformPromiseType<TCoroutineObject>::await_transform(double Value)
{
	std::wcout << "METHOD [suspend_always await_transform(double Value)] CALLED. VALUE [" << Value << L"]." << std::endl;

	MValue2=Value;

	std::suspend_always											Awaiter{};

	return(Awaiter);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
int SCoroutineObjectAwaitTransformPromiseType<TCoroutineObject>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
double SCoroutineObjectAwaitTransformPromiseType<TCoroutineObject>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectAwaitTransform final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectAwaitTransformPromiseType<CCoroutineObjectAwaitTransform>;

	private:
		std::coroutine_handle<SCoroutineObjectAwaitTransformPromiseType<CCoroutineObjectAwaitTransform>>	MHandle;

	public:
		CCoroutineObjectAwaitTransform& operator=(const CCoroutineObjectAwaitTransform&)=delete;
		CCoroutineObjectAwaitTransform& operator=(CCoroutineObjectAwaitTransform&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		int GetValue1(void) const noexcept;
		double GetValue2(void) const noexcept;

	public:
		CCoroutineObjectAwaitTransform(std::coroutine_handle<SCoroutineObjectAwaitTransformPromiseType<CCoroutineObjectAwaitTransform>> Handle);
		CCoroutineObjectAwaitTransform(const CCoroutineObjectAwaitTransform&)=delete;
		CCoroutineObjectAwaitTransform(CCoroutineObjectAwaitTransform&& Other) noexcept;
		~CCoroutineObjectAwaitTransform(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------