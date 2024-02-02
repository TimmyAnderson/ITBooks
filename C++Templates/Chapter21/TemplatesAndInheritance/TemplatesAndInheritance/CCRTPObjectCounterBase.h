//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <mutex>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS implementuje BASE CLASS v CURIOUSLY RECURRING TEMPLATE PATTERN.
// !!!!! TEMPLATE PARAMETER [TDerivedObject] bude DERVIED CLASS, ktora bude mat ako BASE CLASS [CCRTPObjectCounterBase<TDerivedObject>].
// !!!!! TEMPLATE PARAMETER [TDerivedObject] sluzi iba ako KEY, aby sa od seba odlisili jednotlive BASE CLASSES na zaklade TYPE DERIVED CLASS. Inak povedane, aby pre DERIVED CLASS [CLASS_1] a DERIVED CLASS [CLASS_2] existovali 2 nezavisle FIELDS [MCounter], kde kazdy pocita instancie daneho TYPE.
template<typename TDerivedObject>
class CCRTPObjectCounterBase
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		inline static std::recursive_mutex						MMutex{};
		inline static size_t									MCounter=0;

	public:
		static size_t GetCounter(void);

	public:
		CCRTPObjectCounterBase(void);
		CCRTPObjectCounterBase(const CCRTPObjectCounterBase&);
		CCRTPObjectCounterBase(CCRTPObjectCounterBase&&);
		virtual ~CCRTPObjectCounterBase(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CCRTPObjectCounterBase<TDerivedObject>::CCRTPObjectCounterBase(void)
{
	MMutex.lock();

	++MCounter;

	MMutex.unlock();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CCRTPObjectCounterBase<TDerivedObject>::CCRTPObjectCounterBase(const CCRTPObjectCounterBase&)
{
	MMutex.lock();

	++MCounter;

	MMutex.unlock();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CCRTPObjectCounterBase<TDerivedObject>::CCRTPObjectCounterBase(CCRTPObjectCounterBase&&)
{
	MMutex.lock();

	++MCounter;

	MMutex.unlock();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
CCRTPObjectCounterBase<TDerivedObject>::~CCRTPObjectCounterBase(void) noexcept
{
	MMutex.lock();

	--MCounter;

	MMutex.unlock();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TDerivedObject>
size_t CCRTPObjectCounterBase<TDerivedObject>::GetCounter(void)
{
	size_t														Value;

	MMutex.lock();

	Value=MCounter;

	MMutex.unlock();

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------