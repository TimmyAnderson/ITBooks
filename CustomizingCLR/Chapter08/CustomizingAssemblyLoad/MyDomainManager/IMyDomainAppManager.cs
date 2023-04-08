using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace MyDomainManager
{
//-------------------------------------------------------------------------------------------------------
	// !!! INTERFACE bude vystaveny ako COM INTERFACE, aby pomocou neho mohol UNMANAGED HOST pristupovat do MANAGED CODE.
	// !!! Aby UNMANAGED HOST mohol pristupovat ku MANAGED INTERFACES ako COM INTERFACES je nutne pouzit [TlBEXP.EXE], ktory bude spusteny vo VS COMMAND PROMPT X64 - kedze BUILD robim pre X64.
	[ComVisible(true)]
	[Guid("DAF48119-39DD-40E4-AAA0-A0AEA82E76F2")]
	public interface IMyDomainAppManager
	{
//-------------------------------------------------------------------------------------------------------
		void PrintAppCurrentDomainName();
		void CreateNewDomain(string DomainName);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------