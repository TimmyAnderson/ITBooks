//-----------------------------------------------------------------------------
// Tato struktura je definovana v C++ RunTime.
// !!!!! Obsahuje VSETKY POTREBNE STATICKE A GLOBALNE PREMENNE, ktore musia byt pre KAZDY THREAD DUPLIKOVANE a ulozene do TLS, aby C++ RunTime mohol bezat korektne.
//-----------------------------------------------------------------------------
/*
struct _tiddata
{
	// Thread ID.
	unsigned long			_tid;
	// Thread handle.
	unsigned long			_thandle;

	// errno value.
	int						_terrno;
	// _doserrno value.
	unsigned long			_tdoserrno;
	// Floating Point data segment.
	unsigned int				_fpds;
	// rand() seed value.
	unsigned long			_holdrand;
	// ptr to strtok() token.
	char*					_token;
	// ptr to wcstok() token.
	wchar_t*					_wtoken;
	// ptr to _mbstok() token.
	unsigned char*			_mtoken;

	// Following pointers get malloc'd at runtime.
	// ptr to strerror()/_strerror() buff.
	char*					_errmsg;
	// ptr to _wcserror()/__wcserror() buff.
	wchar_t*					_werrmsg;
	// ptr to tmpnam() buffer.
	char*					_namebuf0;
	// ptr to _wtmpnam() buffer
	wchar_t*					_wnamebuf0;
	// ptr to tmpfile() buffer.
	char*					_namebuf1;
	// ptr to _wtmpfile() buffer.
	wchar_t*					_wnamebuf1;
	// ptr to asctime() buffer.
	char*					_asctimebuf;
	// ptr to _wasctime() buffer.
	wchar_t*					_wasctimebuf;
	// ptr to gmtime() structure.
	void*					_gmtimebuf;
	// ptr to ecvt()/fcvt buffer.
	char*					_cvtbuf;

	// ptr to putch() buffer.
	unsigned char			_con_ch_buf[MB_LEN_MAX];

	// If the _con_ch_buf is used.
	unsigned short			_ch_buf_used;

	// Following fields are needed by _beginthread code.
	// Initial user thread address.
	void*					_initaddr;
	// Initial user thread argument.
	void*					_initarg;

	// Following three fields are needed to support signal handling and runtime errors.
	// ptr to exception-action table.
	void*					_pxcptacttab;
	// ptr to exception info pointers.
	void*					_tpxcptinfoptrs;
	// Float point exception code.
	int						_tfpecode;

	// Pointer to the copy of the multibyte character information used by the thread.
	pthreadmbcinfo			ptmbcinfo;

	// Pointer to the copy of the locale information used by the thread.
	pthreadlocinfo			ptlocinfo;

	// If 1, this thread owns its own locale.
	int						_ownlocale;

	// Following field is needed by NLG routines.
	unsigned long			_NLG_dwCode;


	// Per-Thread data needed by C++ Exception Handling.
	// terminate() routine.
	void*					_terminate;

	// unexpected() routine.
	void*					_unexpected;
	// S.E. translator.
	void*					_translator;
	// Called when pure virtual happens.
	void*					_purecall;
	// Current exception.
	void*					_curexception;
	// Current exception context.
	void*					_curcontext;
	// For uncaught_exception.
	int						_ProcessingThrow;
	// For handling exceptions thrown from std::unexpected.
	void*					_curexcspec;

#if defined (_M_IA64) || defined (_M_AMD64)
	void*					_pExitContext;
	void*					_pUnwindContext;
	void*					_pFrameInfoChain;
	unsigned __int64		_ImageBase;
#if defined (_M_IA64)
	unsigned __int64		_TargetGp;
#endif // defined (_M_IA64)
	unsigned __int64		_ThrowImageBase;
	void*					_pForeignException;
#elif defined (_M_IX86)
	void*					_pFrameInfoChain;
#endif // defined (_M_IX86) 
	_setloc_struct			_setloc_data;

	// EncodePointer() routine.
	void*					_encode_ptr;
	// DecodePointer() routine.
	void*					_decode_ptr;

	void*					_reserved1;
	void*					_reserved2;
	void*					_reserved3;

	// Set to True if it's a rethrown C++ Exception.
	int						_cxxReThrow;

	// Initial domain used by _beginthread[ex] for managed function.
	unsigned long			__initDomain;
};
//-----------------------------------------------------------------------------
typedef struct _tiddata*	_ptiddata;
*/
//-----------------------------------------------------------------------------