//-----------------------------------------------------------------------------
// Tato funkcia je definovana v C++ RunTime.
// !!!!! Je to STANDARDNA C++ FUNKCIA pre VYTVARANIE NOVYCH THREADS v C++, ktora zabezpeci KOREKNTU INICIALIZACIU C++ RunTime pre dany thread.
//-----------------------------------------------------------------------------
/*
uintptr_t __cdecl _beginthreadex(void *psa, unsigned cbStackSize, unsigned (__stdcall * pfnStartAddr) (void *), void * pvParam, unsigned dwCreateFlags, unsigned *pdwThreadID)
{
	// !!! V 'tiddata' su ulozene STATICKE a GLOBALNE PREMENNE potrebne pre beh C++ RunTime a C++ STANDARD LIBRARY.
	_ptiddata			ptd;
	// Handle na Thread.
	uintptr_t			thdl;

	// Alokujem novu instanciu 'tiddata'.
	if ((ptd = (_ptiddata)_calloc_crt(1, sizeof(struct _tiddata))) == NULL)
	  goto error_return;

	// Inicializujem instanciu 'tiddata'.
	initptd(ptd);

	// Do 'tiddata' ulozim hodnotu adresy thread funkcie, parametra pre thread funkciu a HANDLE na thread sa nastavi na INVALID.
	ptd->_initaddr = (void *) pfnStartAddr;
	ptd->_initarg = pvParam;
	ptd->_thandle = (uintptr_t)(-1);

	// !!! Pomocou CreateThread() sa vytvara NOVY THREAD.
	// !!!!! Ako THREAD FUNKCIA je RunTime funkcia '_threadstartex', ktora ZABEZPECI VYTVORENIE TLS.
	// !!!!! Ako CUSTOM PARAMETER predavam hodnotu 'tiddata'.
	thdl=(uintptr_t) CreateThread((LPSECURITY_ATTRIBUTES)psa, cbStackSize, _threadstartex, (PVOID) ptd, dwCreateFlags, pdwThreadID);

	// Ak vytvorenie threadu zlyha funkcia konci.
	if (thdl==0)
		goto error_return;

	// Thread bol uspesne vytvoreny a vracia sa jeho HANDLE.
	return(thdl);

	// Handler pri vyskyte chyby.
	error_return:

	// Odstranim pamet pridelenu 'tiddata'.
	_free_crt(ptd);

	// Vratim indikaciu chyby.
	return((uintptr_t)0L);
}
*/
//-----------------------------------------------------------------------------