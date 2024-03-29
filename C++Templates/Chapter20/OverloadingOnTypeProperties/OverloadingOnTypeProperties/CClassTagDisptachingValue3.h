//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CClassTagDisptaching3.h"
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CClassTagDisptachingValue3 final
{
//----------------------------------------------------------------------------------------------------------------------
	friend std::wostream& operator<<(std::wostream& Stream, const CClassTagDisptachingValue3& Value);

	public:
		using													TAG=CClassTagDisptaching3;

	private:
		CString													MValue;

	public:
		const CString& GetValue(void) const noexcept;

	public:
		CClassTagDisptachingValue3(const CString& Value);
		virtual ~CClassTagDisptachingValue3(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------