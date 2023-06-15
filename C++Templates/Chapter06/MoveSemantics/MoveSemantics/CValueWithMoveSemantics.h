//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <cstddef>
//----------------------------------------------------------------------------------------------------------------------
class CValueWithMoveSemantics final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		wchar_t*												MBuffer;

	public:
		CValueWithMoveSemantics& operator=(const CValueWithMoveSemantics& Other);
		CValueWithMoveSemantics& operator=(CValueWithMoveSemantics&& Other) noexcept;

	private:
		static size_t GetLength(const wchar_t* Buffer);
		static void CopyData(wchar_t* Destination, const wchar_t* Source);

	public:
		const wchar_t* GetBuffer(void) const noexcept;

	public:
		CValueWithMoveSemantics(const wchar_t* Buffer);
		CValueWithMoveSemantics(const CValueWithMoveSemantics& Other);
		CValueWithMoveSemantics(CValueWithMoveSemantics&& Other) noexcept;
		virtual ~CValueWithMoveSemantics(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------