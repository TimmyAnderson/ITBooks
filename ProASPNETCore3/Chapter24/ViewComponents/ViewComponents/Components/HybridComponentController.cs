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
	// !!! HYBRID VIEW COMPONENTS MUSIA byt DERIVED z CLASS [Controller].
	// !!! HYBRID VIEW COMPONENTS MUSIA mat aplikovany ATTRIBUTE [ViewComponentAttribute].
	[ViewComponent(Name="Hybrid")]
	public sealed class HybridComponentController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public HybridComponentController(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD [Invoke()] sa vola vtedy, ked je HYBRID VIEW COMPONENT zobrazovany ako VIEW COMPONENT z PARENT VIEW.
		// !!!!! METHOD [Invoke()] zobrazi zoznam NAMES.
		public ViewViewComponentResult Invoke()
		{
			CName[]												Model=MNameProvider.GetNames();
			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			// !!! Nastavi sa MODEL OBJECT.
			DataDictionary.Model=Model;

			ViewViewComponentResult								Result=new ViewViewComponentResult();

			// !!! Nastavi sa nazov PARTIAL VIEW.
			// !!!!! PARTIAL VIEW sa MUSI nachadzat v DIRECTORY [Hybrid], pretoze nazov VIEW COMPONENT urceny v ATTRIBUTE [ViewComponentAttribute] je 'Hybrid'.
			Result.ViewName="HybridComponentPartialView";
			Result.ViewData=DataDictionary;

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Kedze HYBRID VIEW COMPONENTS su VIEW COMPONENTS a zaroven aj CONTROLLERS, tak mozu mat ACTION METHODS.
		// !!!!! Tato ACTION METHOD je volana z PARTIAL VIEW 'HybridComponentPartialView' ako reakcia na stlacenie BUTTON na pridanie noveho NAME.
		public ViewResult AddNewName()
		{
			// !!! HYBRID VIEW COMPONENT vyvola VIEW, ktory zobrazi formular na zadavanie novych NAMES.
			// !!!!! VIEW sa MUSI nachadzat v DIRECTORY [Views\HybridComponent], pretoze nazov CONTROLLER je 'HybridComponent' a VIEWS, aj ked vyvolane z HYBRID VIEW COMPONENT su vyhladavane podla pravidiel pre vyhladavanie VIEWS.
			ViewResult											Result=View("AddNewNameForm");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! HTTP POST ACTION METHOD spracovava POSTBACK z VIEW 'AddNewNameForm' zapisanim NAME do DB.
		[HttpPost]
		public IActionResult ProcessAddNewName(CName Name)
		{
			MNameProvider.AddName(Name);

			// !!! Spravi REDIRECT na POVODNY PARENT VIEW.
			IActionResult										Result=RedirectToAction("MyActionMethod","HybridParentView");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------