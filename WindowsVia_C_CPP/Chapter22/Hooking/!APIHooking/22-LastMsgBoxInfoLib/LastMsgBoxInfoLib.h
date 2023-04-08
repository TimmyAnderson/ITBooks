#ifndef LASTMSGBOXINFOLIBAPI 
#define LASTMSGBOXINFOLIBAPI extern "C" __declspec(dllimport)
#endif
//------------------------------------------------------------------------------
LASTMSGBOXINFOLIBAPI BOOL WINAPI LastMsgBoxInfo_HookAllApps(BOOL Install, DWORD ThreadId);
//------------------------------------------------------------------------------