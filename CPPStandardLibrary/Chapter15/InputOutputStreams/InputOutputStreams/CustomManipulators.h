//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <ostream>
#include <string>
//-----------------------------------------------------------------------------
extern const int												CUSTOM_DATA_INT_INDEX;
extern const int												CUSTOM_DATA_VOID_POINTER_INDEX;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::wostream& AddIntegerCustomData(std::wostream& Stream, int ValueToSet);
std::wostream& AddVoidPointerCustomData(std::wostream& Stream, const std::wstring& ValueToSet);
//-----------------------------------------------------------------------------