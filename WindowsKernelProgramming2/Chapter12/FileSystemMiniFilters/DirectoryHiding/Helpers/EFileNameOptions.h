//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <fltKernel.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
enum class EFileNameOptions : ULONG
{
//----------------------------------------------------------------------------------------------------------------------
	E_NORMALIZED=FLT_FILE_NAME_NORMALIZED,
	E_OPENED=FLT_FILE_NAME_OPENED,
	E_SHORT=FLT_FILE_NAME_SHORT,
	E_QUERY_DEFAULT=FLT_FILE_NAME_QUERY_DEFAULT,
	E_QUERY_CACHE_ONLY=FLT_FILE_NAME_QUERY_CACHE_ONLY,
	E_QUERY_FILE_SYSTEM_ONLY=FLT_FILE_NAME_QUERY_FILESYSTEM_ONLY,
	E_REQUEST_FROM_CURRENT_PROVIDER=FLT_FILE_NAME_REQUEST_FROM_CURRENT_PROVIDER,
	E_DO_NOT_CHACHE=FLT_FILE_NAME_DO_NOT_CACHE,
	E_ALLOW_QUERY_ON_REPARSE=FLT_FILE_NAME_ALLOW_QUERY_ON_REPARSE
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
inline EFileNameOptions operator|(EFileNameOptions Value1, EFileNameOptions Value2)
{
	ULONG														NumericValue1=static_cast<ULONG>(Value1);
	ULONG														NumericValue2=static_cast<ULONG>(Value2);
	ULONG														NumericResult=(NumericValue1 | NumericValue2);
	EFileNameOptions											Result=static_cast<EFileNameOptions>(NumericResult);

    return(Result);
}
//----------------------------------------------------------------------------------------------------------------------