using Microsoft.AspNetCore.Mvc.Razor.TagHelpers;
using Microsoft.AspNetCore.Razor.TagHelpers;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingTagHelpers.TagHelperComponentTagHelpers
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! CLASS predstavuje implementaciu TAG HELPER COMPONENT TAG HELPER, ktora rozsiruje VSETKY TAG HELPER COMPONENTS v CELOM PROJECT o ich aplikaciu na HTML ELEMENT [<main>].
	// !!!!! Pomocou ATTRIBUTES [HtmlTargetElementAttribute] sa urcuje na ktore HTML ELEMENTS sa TAG HELPER COMPONENTS budu aplikovat.
	[HtmlTargetElement("main")]
	public class CMyTagHelperComponentTagHelper : TagHelperComponentTagHelper
	{
//----------------------------------------------------------------------------------------------------------------------
		public CMyTagHelperComponentTagHelper(ITagHelperComponentManager Manager, ILoggerFactory LoggerFactory)
			: base(Manager,LoggerFactory)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------