//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <mutex>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CDouble final
{
//----------------------------------------------------------------------------------------------------------------------
	friend CDouble operator+(const CDouble& Value1, const CDouble& Value2);
	friend CDouble operator*(const CDouble& Value1, const CDouble& Value2);
	friend CDouble operator*(const double& Value1, const CDouble& Value2);
	friend std::wostream& operator<<(std::wostream& Stream, const CDouble& Value);

	private:
		inline static std::recursive_mutex						MMutex{};
		inline static size_t									MCounter=0;

	private:
		double													MValue;

	public:
		CDouble& operator=(const CDouble& Other);
		CDouble& operator=(CDouble&& Other) noexcept;

	public:
		operator size_t(void) const;

	public:
		CDouble& operator+=(const CDouble& Value);
		CDouble& operator*=(const CDouble& Value);
		CDouble& operator*=(const double& Value);

	private:
		static void IncrementCounter(void);

	public:
		static size_t GetCounter(void);
		static void ResetCounter(void);

	public:
		double GetValue(void) const;

	public:
		CDouble(void);
		CDouble(double Value);
		CDouble(const CDouble& Value);
		CDouble(CDouble&& Value) noexcept;
		virtual ~CDouble(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------