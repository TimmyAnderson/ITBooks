//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CClassTagDisptaching1.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CClassTagDisptachingValue1 final
{
//----------------------------------------------------------------------------------------------------------------------
	friend std::wostream& operator<<(std::wostream& Stream, const CClassTagDisptachingValue1& Value);

	public:
		using													TAG=CClassTagDisptaching1;

	private:
		int														MValue;

	public:
		int GetValue(void) const noexcept;

	public:
		CClassTagDisptachingValue1(int Value);
		virtual ~CClassTagDisptachingValue1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------