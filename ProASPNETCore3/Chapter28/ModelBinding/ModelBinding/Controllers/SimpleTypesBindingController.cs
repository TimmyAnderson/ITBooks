using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using ModelBinding.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class SimpleTypesBindingController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChildProvider							MChildProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public SimpleTypesBindingController(IChildProvider ChildProvider)
		{
			MChildProvider=ChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER TYPE [int?] umoznuje rozlisit ci VALUE VARIABLE 'ID' bola najdena MODEL BINDING, alebo bola SUBSTITUOVANA DEFAULT VALUE ID=null.
		[Route("{Controller}/{Action}/{id?}")]
		public ViewResult ShowName(int? ID)
		{
			if (ID.HasValue==true)
			{
				CChild											Model=MChildProvider.GetChild(ID.Value);

				if (Model!=null)
				{
					ViewResult									Result=View("ViewChild",Model);

					return(Result);
				}
				else
				{
					CResultMessage								Message=new CResultMessage($"NO OBJECT FOUND for ID [{ID}] !");
					ViewResult									Result=View("ShowResultMessage",Message);

					return(Result);
				}
			}
			else
			{
				CResultMessage									Message=new CResultMessage($"NO OBJECT FOUND for ID==NULL !");
				ViewResult										Result=View("ShowResultMessage",Message);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------