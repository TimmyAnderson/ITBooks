using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security.Policy;
//------------------------------------------------------------------------------------------------------
namespace BagAppDomainManager
{
//------------------------------------------------------------------------------------------------------
	// !!! Reprezentuje CUSTOM EVIDENCE, ktoru budu musiet ASSEMBLIES MAT, aby splnili SECURITY REQUIREMENTS.
	// !!! CUSTOM EVIDENCE MUSI BYT CLASS ZDEDENA z EvidenceBase a MUSI byt SERIALIZABLE.
	[Serializable]
	public sealed class CMyEvidence : EvidenceBase
	{
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------