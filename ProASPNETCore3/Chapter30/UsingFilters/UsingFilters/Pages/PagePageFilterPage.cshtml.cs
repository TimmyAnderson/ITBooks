using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using UsingFilters.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class PagePageFilterPageModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private string											MMessage;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											Message
		{
			get
			{
				return(MMessage);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PAGE FILTER je implementovany priamo na urovni RAZOR PAGE.
		public override async Task OnPageHandlerExecutionAsync(PageHandlerExecutingContext Context, PageHandlerExecutionDelegate Next)
		{
			Stopwatch											Stopwatch=new Stopwatch();

			Stopwatch.Start();

			// !!! Explicitne sa vola sa RAZOR PAGE HANDLER.
			PageHandlerExecutedContext							ExecutedContext=await Next();

			Stopwatch.Stop();

			PageResult											Result=(PageResult) ExecutedContext.Result;
			PagePageFilterPageModel								Model=(PagePageFilterPageModel) Result.Model;
			CResultMessageWithExecutionTime						ModifiedModel=new CResultMessageWithExecutionTime(Model.Message,Stopwatch.ElapsedTicks.ToString());
			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			DataDictionary.Model=ModifiedModel;

			ViewResult											ModifiedResult=new ViewResult();

			ModifiedResult.ViewName="ResultMessageWithExecutionTime";
			ModifiedResult.ViewData=DataDictionary;

			// !!! RETURN VALUE DELEGATE sa pouzije na zmenu RESULT.
			ExecutedContext.Result=ModifiedResult;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        public IActionResult OnGet()
        {
			MMessage="RAZOR PAGE HANDLER is EXECUTED !";

			IActionResult										Result=Page();

			return(Result);
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------