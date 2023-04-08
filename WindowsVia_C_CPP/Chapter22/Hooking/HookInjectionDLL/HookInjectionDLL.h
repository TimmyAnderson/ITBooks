#ifdef HOOKINJECTIONDLL_EXPORTS
#define HOOKINJECTIONDLL_API __declspec(dllexport)
#else
#define HOOKINJECTIONDLL_API __declspec(dllimport)
#endif
//------------------------------------------------------------------------------
HOOKINJECTIONDLL_API bool InstallHook(HHOOK* PHook, bool UseFilter);
HOOKINJECTIONDLL_API bool UninstallHook(void);
//------------------------------------------------------------------------------