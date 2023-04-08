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
	public sealed class Poco2ViewComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAME PROVIDER je naplneny DEPENDENCY INJECTION FRAMEWORK.
		public Poco2ViewComponent(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD [Invoke()] vracia TYPE [ViewViewComponentResult], ktory sluzi na zobrazenie PARTIAL VIEW.
		// !!!!! CLASS [ViewViewComponentResult] umoznuje spojenie VIEW COMPONENT s PARTIAL VIEW.
		public ViewViewComponentResult Invoke()
		{
			CName[]												Model=MNameProvider.GetNames();
			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			// !!! Nastavi sa MODEL OBJECT.
			DataDictionary.Model=Model;

			ViewViewComponentResult								Result=new ViewViewComponentResult();

			// !!! Nastavi sa nazov PARTIAL VIEW.
			Result.ViewName="MyPocoPartialView";
			Result.ViewData=DataDictionary;

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------