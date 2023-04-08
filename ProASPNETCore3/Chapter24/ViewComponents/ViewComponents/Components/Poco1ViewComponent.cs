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
	// !!! POCO VIEW COMPONENTS MUSIA mat POSTFIX [ViewComponent].
	public sealed class Poco1ViewComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAME PROVIDER je naplneny DEPENDENCY INJECTION FRAMEWORK.
		public Poco1ViewComponent(INameProvider NameProvider)
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