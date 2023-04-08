using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace SecurityAttributes
{
//-------------------------------------------------------------------------------------------------------
	[Serializable]
	[Flags]
	// CLASS reprezentuje hodnotu PERMISSION, ktoru PERMISSION CLASS CMyCustomPermission prideluje.
	public enum EMyCustomPermissionActions
	{
//-------------------------------------------------------------------------------------------------------
		E_NONE=0x00,
		E_READ=0x01,
		E_WRITE=0x02,
		E_ALL=E_READ | E_WRITE,
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------