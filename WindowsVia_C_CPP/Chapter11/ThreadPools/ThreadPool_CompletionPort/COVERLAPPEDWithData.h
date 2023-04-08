#include <windows.h>
//------------------------------------------------------------------------------
// Pomocna struktura asociujuca OVERLAPPED s datami.
class COVERLAPPEDWithData : public OVERLAPPED
{
	public:
		BYTE*			Data;
};
//------------------------------------------------------------------------------
typedef COVERLAPPEDWithData* LPCOVERLAPPEDWithData;
//------------------------------------------------------------------------------