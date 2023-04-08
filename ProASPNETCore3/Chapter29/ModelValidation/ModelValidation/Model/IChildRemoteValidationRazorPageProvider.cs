using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public interface IChildRemoteValidationRazorPageProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		CChildRemoteValidationRazorPage AddChild(CChildRemoteValidationRazorPage Child);
		CChildRemoteValidationRazorPage UpdateChild(CChildRemoteValidationRazorPage Child);
		void RemoveChild(int ID);
		CChildRemoteValidationRazorPage GetChild(int ID);
		CChildRemoteValidationRazorPage[] GetChildren();
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------