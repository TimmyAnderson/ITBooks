using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public interface IChildRemoteValidationProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		CChildRemoteValidation AddChild(CChildRemoteValidation Child);
		CChildRemoteValidation UpdateChild(CChildRemoteValidation Child);
		void RemoveChild(int ID);
		CChildRemoteValidation GetChild(int ID);
		CChildRemoteValidation[] GetChildren();
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------