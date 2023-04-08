// !!! Toto je HEADER, ktory MUSI byt pridany ako do DLL, tak i do EXE projektu.
//------------------------------------------------------------------------------
#ifdef SIMPLEDLL_EXPORTS
	// V DLL projekte sa pouzije tato deklaracia, pretoze SIMPLEDLL_EXPORTS v nom je DEFINOVANY.
	#define SIMPLEDLL_API __declspec(dllexport)
#else
	// V EXE projekte sa pouzije tato deklaracia, pretoze SIMPLEDLL_EXPORTS v nom NIE JE DEFINOVANY.
	#define SIMPLEDLL_API __declspec(dllimport)
#endif
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Priklad exportovanej premennej.
extern SIMPLEDLL_API int			DLL_SomeValue;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Priklad exportovanej funkcie.
SIMPLEDLL_API void DLL_ConvertToUpper(wchar_t* Text);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Priklad exportovanej triedy.
class SIMPLEDLL_API CSimpleDLL
{
	private:
		static const int			BUFFER_SIZE=1024;

	private:
		wchar_t						MBuffer[BUFFER_SIZE];

	public:
		wchar_t* GetBuffer(void);
		void SetBuffer(wchar_t* Text);

	public:
		CSimpleDLL(void);
		~CSimpleDLL(void);
};
//------------------------------------------------------------------------------