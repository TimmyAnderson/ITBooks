//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER ide spustit IBA ak je na VIRTUAL MACHINE rozbehany VIRTUALIZATION BASED SECURITY, ktora vyzaduje zmmenu nastavenia WINDOWS.
//#define USE_SECURE_POOL
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DRIVER ide spustit na WINDOWS 10, IBA ak je CONFIGURATION [Configuration Properties->Driver Settings->General->_NT_TARGET_VERSION] nastaveny na VALUE [Windows 10.0.22000], alebo menej. Vyssia VALUE sposobi, ze DRIVER na WINDOWS 10 sa NEBUDE dat SPUSTIT.
#if (NTDDI_VERSION <= NTDDI_WIN10_CO)
#define USE_LOOKSIDE_LISTS
#endif
//----------------------------------------------------------------------------------------------------------------------