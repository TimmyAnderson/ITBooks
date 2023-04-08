using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public interface IChildAutoValidationProvider
	{
//----------------------------------------------------------------------------------------------------------------------
		CChildAutoValidation AddChild(CChildAutoValidation Child);
		CChildAutoValidation UpdateChild(CChildAutoValidation Child);
		void RemoveChild(int ID);
		CChildAutoValidation GetChild(int ID);
		CChildAutoValidation[] GetChildren();
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------