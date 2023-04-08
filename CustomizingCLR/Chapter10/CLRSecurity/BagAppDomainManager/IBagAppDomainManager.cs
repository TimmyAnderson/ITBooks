using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace BagAppDomainManager
{
//-------------------------------------------------------------------------------------------------------
	// !!! INTERFACE bude vystaveny ako COM INTERFACE, aby pomocou neho mohol UNMANAGED HOST pristupovat do MANAGED CODE.
	// !!! Aby UNMANAGED HOST mohol pristupovat ku MANAGED INTERFACES ako COM INTERFACES je nutne pouzit [TlBEXP.EXE], ktory bude spusteny vo VS COMMAND PROMPT X64 - kedze BUILD robim pre X64.
	[ComVisible(true)]
	[Guid("A88229EA-473F-42F3-94CF-816C036E8AA8")]
	public interface IBagAppDomainManager
	{
//-------------------------------------------------------------------------------------------------------
		void CreateNewDomain(string DomainName);
		void CreateNewDomainAndRunBag(string DomainName, string BagExecutable, string RunnableType);
		void RunBagInDefaultAppDomain(string DomainName, string BagExecutable, string RunnableType);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------