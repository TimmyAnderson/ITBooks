//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <iostream>
#include <cstddef>
#include <array>
#include <memory_resource>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectCustomAllocationSectionPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
#ifndef _MSC_VER
		// !!!!! MEMORY BUFFER sa vytvori v specialnej MEMORY SECTION, ktore je mimo STACK aj HEAP.
		static std::array<std::byte,200'000>					MBuffer;
		static std::pmr::monotonic_buffer_resource				MMonoBuffer;
		// !!!!! MEMORY POOL je THREAD SAFE.
		static std::pmr::synchronized_pool_resource				MMemoryPool;
#endif

#ifdef _MSC_VER
		// !!!!! Vo WINDOWS je NUTNE pouzit INLINE STATIC, inak dojde k RUNTIME ERROR.

		// !!!!! MEMORY BUFFER sa vytvori v specialnej MEMORY SECTION, ktore je mimo STACK aj HEAP.
		inline static std::array<std::byte,200'000>				MBuffer;
		inline static std::pmr::monotonic_buffer_resource		MMonoBuffer{MBuffer.data(),MBuffer.size(),std::pmr::null_memory_resource()};
		// !!!!! MEMORY POOL je THREAD SAFE.
		inline static std::pmr::synchronized_pool_resource		MMemoryPool{&MMonoBuffer};
#endif

	public:
		void* operator new(std::size_t Count);
		void operator delete(void* Pointer, std::size_t Count);

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#ifndef _MSC_VER
template<typename TCoroutineObject>
std::array<std::byte,200'000>									SCoroutineObjectCustomAllocationSectionPromiseType<TCoroutineObject>::MBuffer{};
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::pmr::monotonic_buffer_resource								SCoroutineObjectCustomAllocationSectionPromiseType<TCoroutineObject>::MMonoBuffer{MBuffer.data(),MBuffer.size(),std::pmr::null_memory_resource()};
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::pmr::synchronized_pool_resource							SCoroutineObjectCustomAllocationSectionPromiseType<TCoroutineObject>::MMemoryPool{&MMonoBuffer};
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void* SCoroutineObjectCustomAllocationSectionPromiseType<TCoroutineObject>::operator new(std::size_t Count)
{
	// !!! Alokuje sa MEMORY z MEMORY POOL.
	void*														Pointer=MMemoryPool.allocate(Count);

	std::wcout << L"OPERATOR NEW CALLED. POINTER [" << Pointer << L"] COUNT [" << Count << L"]." << std::endl;

	return(Pointer);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationSectionPromiseType<TCoroutineObject>::operator delete(void* Pointer, std::size_t Count)
{
	std::wcout << L"OPERATOR DELETE CALLED. POINTER [" << Pointer << L"]." << std::endl;

	if (Pointer!=nullptr)
	{
		// !!! Uvolni sa MEMORY z MEMORY POOL.
		MMemoryPool.deallocate(Pointer,Count);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectCustomAllocationSectionPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectCustomAllocationSectionPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCustomAllocationSectionPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationSectionPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationSectionPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCustomAllocationSectionPromiseType<TCoroutineObject>::SCoroutineObjectCustomAllocationSectionPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectCustomAllocationSection final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectCustomAllocationSectionPromiseType<CCoroutineObjectCustomAllocationSection>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectCustomAllocationSection& operator=(const CCoroutineObjectCustomAllocationSection&)=delete;
		CCoroutineObjectCustomAllocationSection& operator=(CCoroutineObjectCustomAllocationSection&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CCoroutineObjectCustomAllocationSection(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectCustomAllocationSection(const CCoroutineObjectCustomAllocationSection&)=delete;
		CCoroutineObjectCustomAllocationSection(CCoroutineObjectCustomAllocationSection&& Other) noexcept;
		~CCoroutineObjectCustomAllocationSection(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------