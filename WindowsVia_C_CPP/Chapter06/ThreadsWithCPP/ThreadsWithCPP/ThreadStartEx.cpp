//-----------------------------------------------------------------------------
// Tato funkcia je definovana v C++ RunTime.
// !!!!! Toto je THREAD FUNKCIA, v ktorej bezi thread vytvoreny _beginthreadex(). AZ NASLEDNE TATO THREAD FUNKCIA vola CUSTOM THREAD FUNKCIU, ktoru som zadal AKO PARAMETER v _beginthreadex().
//-----------------------------------------------------------------------------
// !!!!! Parameter 'ptd' obsahuje NAINICIALZIOVANU strukturu 'tiddata' so STATICKYMI a GLOBALNYMI C++ RunTime premennymi.
/*
static unsigned long WINAPI _threadstartex (void* ptd)
{
	// Uklada do TLS ENTRY hondotu 'tiddata'.
	// ??? Samotna TLS ENTRY sa asi vytvara C++ RunTime na zaciatku celeho procesu.
	TlsSetValue(__tlsindex, ptd);

	// Do 'tiddata' ulozim ID threadu.
	((_ptiddata) ptd)->_tid = GetCurrentThreadId();

	// Tu sa vykonaju inicializacie float-point C++ support.
	// .......

	// Zavola sa helper funkcia, ktora ZAVOLA CUSTOM THREAD FUNKCIU.
	_callthreadstartex();

	// Do tohto bodu sa kod NIKDY NEDOSTANE, lebo _callthreadstartex() UKONCI THREAD (alebo proces ak sa vyskytne neosetrena EXCEPTION).
	return(0L);
}
*/
//-----------------------------------------------------------------------------