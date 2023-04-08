//-----------------------------------------------------------------------------
// Tato funkcia je definovana v C++ RunTime.
// !!!!! Funkcia je volana na konci threadu (alebo moze aj pocas behu threadu na jeho okamzite ukoncenie) a je zodpovedna za KOREKTNE UVOLNENIE C++ RunTime 'tiddata' struktury a naledne volanie ExitThread() na ukoncenie threadu.
//-----------------------------------------------------------------------------
/*
void __cdecl _endthreadex (unsigned retcode)
{
	_ptiddata			ptd;

	// Tu sa vykona VYCISTENIE float-point C++ support.
	// .......

	// Z TLS ziskam hodnotu 'tiddata'.
	ptd=_getptd_noexit ();

	// Uvolnim 'tiddata'.
	if (ptd!=NULL)
		_freeptd(ptd);

	// Volanim ExitThread() ukoncim thread.
	ExitThread(retcode);
}
*/
//-----------------------------------------------------------------------------