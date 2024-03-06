//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CDumpType final
{
//----------------------------------------------------------------------------------------------------------------------
	friend std::wostream& operator<<(std::wostream& Stream, const CDumpType& Value);

	private:
		CString													MValue;

	public:
		CDumpType& operator=(const CDumpType& Other);
		CDumpType& operator=(CDumpType&& Other) noexcept;

	public:
		const CString& GetValue(void) const noexcept;

	public:
		CDumpType(void);
		CDumpType(const CString& Value);
		CDumpType(CString&& Value);
		CDumpType(const CDumpType& Other);
		CDumpType(CDumpType&& Other) noexcept;
		virtual ~CDumpType(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------