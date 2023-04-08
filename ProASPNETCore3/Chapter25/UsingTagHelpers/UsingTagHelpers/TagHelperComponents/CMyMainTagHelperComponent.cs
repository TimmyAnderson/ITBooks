using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using Microsoft.AspNetCore.Razor.TagHelpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingTagHelpers.TagHelperComponents
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! TAG HELPER COMPONENT MUSI byt DERIVED z CLASS [TagHelperComponent].
	// !!!!! Na to, aby TAG HELPER COMPONENT bol aplikovany aj na HTML ELEMENT [<main>] je nutne implementovat TAG HELPER COMPONENT TAG HELPER.
	// !!!!! CLASS implementujuca TAG HELPER COMPONENT TAG HELPER sa vola 'CMyTagHelperComponentTagHelper'.
	public sealed class CMyMainTagHelperComponent : TagHelperComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private ViewContext										MMyViewContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! VIEW CONTEXT PROPERTY MUSI byt oznacena pomocou ATTRIBUTE [ViewContextAttribute].
		[ViewContext]
		// !!! Aplikovanim ATTRIBUTE [HtmlAttributeNotBoundAttribute], C# PROPERTY NEBUDE mapovana na HTML ATTRIBUTE.
		[HtmlAttributeNotBound]
		public ViewContext										MyViewContext
		{
			get
			{
				return(MMyViewContext);
			}
			set
			{
				MMyViewContext=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! TAG HELPER COMPONENTS MUSIA vykonat OVERRIDE METHOD [void Process(TagHelperContext Context, TagHelperOutput Output)], alebo METHOD [Task ProcessAsync(TagHelperContext Context, TagHelperOutput Output)].
		public override Task ProcessAsync(TagHelperContext Context, TagHelperOutput Output)
		{
			if (MyViewContext.RouteData.Values.ContainsKey("Controller")==true && MyViewContext.RouteData.Values.ContainsKey("Action")==true)
			{
				string											Controller=MyViewContext.RouteData.Values["Controller"].ToString();
				string											Action=MyViewContext.RouteData.Values["Action"].ToString();

				// !!!!! TAG HELPER COMPONENTS sa aplikuju na UPLNE VSETKY VIEWS a RAZOR PAGES v celom PROJECT.
				// !!!!! Na to aby zbytocne nebol aplikovany na vsetky VIEWS a RAZOR PAGES, tak sa spravi filtrovanie.
				if (Controller=="MyTagHelpers" && Action=="UseTagHelperComponentTagHelper")
				{
					// !!!!! BY-DEFAULT sa TAG HELPER COMPONENTS aplikuju na HTML ELEMENT [<head>] a HTML ELEMENT [<body>], ale to je mozne zmenit implementaciou TAG HELPER COMPONENT TAG HELPER.
					if (Output.TagName=="main")
					{
						TagBuilder								NewElement=new TagBuilder("div");

						NewElement.Attributes.Add("class","OUTER_BOX");
						NewElement.InnerHtml.Append("This CONTENT was ADDED by [CMyMainTagHelperComponent] TAG HELPER COMPONENT !");

						// !!! HTML ELEMENT sa prida do CONTENT HTML ELEMENT [<body>].
						Output.PreElement.AppendHtml(NewElement);
					}
				}
			}

			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------