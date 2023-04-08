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
	public sealed class Parameters : ViewComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public Parameters(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD ma PARAMETER, ktory je preneseny z PARENT VIEW.
		public ViewViewComponentResult Invoke(ETextType TextType)
		{
			CName[]												Model=MNameProvider.GetNames();

			if (TextType==ETextType.E_PLAIN_TEXT)
			{
				ViewViewComponentResult							Result=View("NamesPartialViewInPlainText",Model);

				return(Result);
			}
			else if (TextType==ETextType.E_BOLD_TEXT)
			{
				ViewViewComponentResult							Result=View("NamesPartialViewInBoldText",Model);

				return(Result);
			}
			else if (TextType==ETextType.E_ITALICS_TEXT)
			{
				ViewViewComponentResult							Result=View("NamesPartialViewInItalicsText",Model);

				return(Result);
			}
			else
			{
				throw(new InvalidOperationException("UNSUPPORTED TEXT TYPE !"));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------