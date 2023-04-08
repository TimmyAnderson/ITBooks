using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.ViewComponents;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using ViewComponents.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ViewComponents.Pages
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! RAZOR PAGE je zaroven aj VIEW COMPONENT.
	[ViewComponent(Name="RazorPageHybridComponent")]
    public class RazorPageHybridViewComponent : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public RazorPageHybridViewComponent(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CName[]											Names
		{
			get
			{
				return(MNameProvider.GetNames());
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Kedze RAZOR PAGE je zaroven aj VIEW COMPONENT, MUSI implementovat METHOD [Invoke()].
		// !!!!! METHOD sa vola, ak sa RAZOR PAGE pouziva ako VIEW COMPONENT.
		// !!!!! METHOD NIE JE VOLANA, ak sa RAZOR PAGE pouziva ako RAZOR PAGE.
		public IViewComponentResult Invoke()
		{
			CName[]												Model=MNameProvider.GetNames();
			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			// !!! Nastavi sa MODEL OBJECT.
			DataDictionary.Model=Model;

			ViewViewComponentResult								Result=new ViewViewComponentResult();

			// !!! Nastavi sa nazov PARTIAL VIEW.
			Result.ViewName="MyRazorPageHybridViewComponentPartialView";
			Result.ViewData=DataDictionary;

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD sa vola, ak sa RAZOR PAGE pouziva ako RAZOR PAGE.
		// !!!!! METHOD NIE JE VOLANA, ak sa RAZOR PAGE pouziva ako VIEW COMPONENT.
        public IActionResult OnGet()
        {
			IActionResult										Result=Page();

			return(Result);
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------