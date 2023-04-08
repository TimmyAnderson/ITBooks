#ifdef SIMPLEDLL_EXPORTS
#define SIMPLEDLL_API __declspec(dllexport)
#else
#define SIMPLEDLL_API __declspec(dllimport)
#endif
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// !!!!! MUSI TU BYT 'extern "C"' inak C++ kompilator ZMENI MENA FUNKCII a spravi z NICH MANGLED mena a NEBUDEM ICH VEDIET NACITAT.
extern "C" SIMPLEDLL_API void DLL_ConvertToUpper(wchar_t* Text);
extern "C" SIMPLEDLL_API void DLL_ConvertToLower(wchar_t* Text);
//------------------------------------------------------------------------------