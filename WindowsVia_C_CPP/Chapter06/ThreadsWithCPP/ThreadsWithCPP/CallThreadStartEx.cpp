//-----------------------------------------------------------------------------
// Tato funkcia je definovana v C++ RunTime.
// !!!!! Pomocna HELPER FUNKCIA zabezpecujuca SPUSTENIE CUSTOM THREAD FUNKCIE a OSETRENIE pripadnych NEOSETRENYCH EXCEPTION.
// !!!!! Funkcia je zodpovedna za UKONCENIE THREADU volanim _endtrheadex().
//-----------------------------------------------------------------------------
/*
static void _callthreadstartex(void)
{
   _ptiddata			ptd;

   // Z TLS ziskam hodnotu 'tiddata'.
   ptd=_getptd();

   // Obalim volanie CUSTOM THREAD FUNKCIE do SEH bloku.
	__try
	{
		// Zavola sa CUSTOM THREAD FUNKCIA.
		// !!! Do CUSTOM THREAD FUNKCIE sa preda ako parameter CUSTOM PARAMETER zadany v _beginthreadex().
		// !!!!! Po jej skonceni sa NAVRATOVA HODNOTA CUSTOM THREAD FUNCKIE PREDA do _endthreadex().
		_endthreadex(((unsigned (WINAPI *)(void *))(((_ptiddata)ptd)->_initaddr)) (((_ptiddata)ptd)->_initarg));
	}
	__except(_XcptFilter(GetExceptionCode(), GetExceptionInformation()))
	{
		// V pripade UNHANDLED EXCEPTION dochadza k TERMINOVANIU CELEHO PROCESU.
		_exit(GetExceptionCode());
	}
}
*/
//-----------------------------------------------------------------------------