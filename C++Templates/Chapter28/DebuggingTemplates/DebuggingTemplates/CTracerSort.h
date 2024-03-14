//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <mutex>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CTracerSort final
{
//----------------------------------------------------------------------------------------------------------------------
	friend bool operator<(const CTracerSort& Value1, const CTracerSort& Value2);

	private:
		inline static std::recursive_mutex						MMutex{};

	private:
		inline static long										MCreated=0;
		inline static long										MDestroyed=0;
		inline static long										MAssigned=0;
		inline static long										MCompared=0;
		inline static long										MMaxLive=0;

	private:
		int														MValue;
		int														MGeneration;

	private:
		static void UpdateMaxLive(void);

	public:
		static void Reset(void);
		static long GetCreations(void);
		static long GetDestructions(void);
		static long GetAssignments(void);
		static long GetComparisons(void);
		static long GetMaxLive(void);

	public:
		CTracerSort& operator=(const CTracerSort& Other);

	public:
		int GetValue(void) const;

	public:
		CTracerSort (int Value=0);
		CTracerSort(const CTracerSort& Other);
		virtual ~CTracerSort(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------