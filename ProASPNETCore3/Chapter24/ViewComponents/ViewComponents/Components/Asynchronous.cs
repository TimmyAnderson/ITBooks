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
	public sealed class Asynchronous : ViewComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public Asynchronous(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!! METHOD [Task<ViewViewComponentResult> InvokeAsync()] je ASYNCHRONOUS VERSION METHOD [ViewViewComponentResult Invoke()].
		public Task<ViewViewComponentResult> InvokeAsync()
		{
			CName[]												Model=MNameProvider.GetNames();

			// !!! Pouzije sa HELPER METHOD [View()] na vratenie PARTIAL VIEW.
			ViewViewComponentResult								ResultData=View("AsynchronousPartialView",Model);
			Task<ViewViewComponentResult>						Result=Task<ViewViewComponentResult>.FromResult(ResultData);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------