using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.ViewComponents;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using ViewComponents.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ViewComponents.Components
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! VIEW COMPONENT je DERIVED z CLASS [ViewComponent].
	public sealed class Derived1CV : ViewComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAME PROVIDER je naplneny DEPENDENCY INJECTION FRAMEWORK.
		public Derived1CV(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! VIEW COMPONENTS MUSIA ma implementovanu METHOD [Invoke()], ktora moze mat LUBOVOLNU RETURN VALUE.
		public string Invoke()
		{
			CName[]												Names=MNameProvider.GetNames();

			return($"[{Names[0]}] [{Names[1]}] [{Names[2]}] !!!");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------