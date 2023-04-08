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
	public sealed class CMyTagHelperComponent : TagHelperComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private ViewContext										MMyViewContext;
//----------------------------------------------------------------------------------------------------------------------
		//private string										MMyClassName;
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
		// !!!!! Pre TAG HELPER COMPONENTS na rozdiel od TAG HELPERS ASP.NET NEMAPUJE VALUES HTML ATTRIBUTES na prislusne C# PROPERTIES TAG HELPER COMPONENTS.
		/*
		[HtmlAttributeName("my_class-name")]
		public string											MyClassName
		{
			get
			{
				return(MMyClassName);
			}
			set
			{
				MMyClassName=value;
			}
		}
		*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! TAG HELPER COMPONENTS MUSIA vykonat OVERRIDE METHOD [void Process(TagHelperContext Context, TagHelperOutput Output)], alebo METHOD [Task ProcessAsync(TagHelperContext Context, TagHelperOutput Output)].
		public override Task ProcessAsync(TagHelperContext Context, TagHelperOutput Output)
		{
			if (MyViewContext.RouteData.Values.ContainsKey("Controller")==true && MyViewContext.RouteData.Values.ContainsKey("Controller")==true)
			{
				string											Controller=MyViewContext.RouteData.Values["Controller"].ToString();
				string											Action=MyViewContext.RouteData.Values["Action"].ToString();

				// !!!!! TAG HELPER COMPONENTS sa aplikuju na UPLNE VSETKY VIEWS a RAZOR PAGES v celom PROJECT.
				// !!!!! Na to aby zbytocne nebol aplikovany na vsetky VIEWS a RAZOR PAGES, tak sa spravi filtrovanie.
				if (Controller=="MyTagHelpers" && Action=="UseTagHelperComponent")
				{
					// !!!!! BY-DEFAULT sa TAG HELPER COMPONENTS aplikuju na HTML ELEMENT [<head>] a HTML ELEMENT [<body>].
					if (Output.TagName=="body")
					{
						// !!! Vytvori sa HTML ELEMENT, ktory sa prida na zaciatok CONTENT HTML ELEMENT [<body>].
						TagBuilder								NewElement=new TagBuilder("div");
						string									ClassName="OUTER_BOX";
						TagHelperAttribute						ClassNameAttribute;

						// !!!!! Aj ked pre TAG HELPER COMPONENTS ASP.NET NEMAPUJE VALUES HTML ATTRIBUTES na prislusne C# PROPERTIES TAG HELPER COMPONENTS, vsetky HTML ATTRIBUTES aplikovane na HTML ELEMENTS na ktore sa aplikuju TAG HELPER COMPONENTS su vsak pristupne pomocou PROPERTY [TagHelperContext.AllAttributes].
						if (Context.AllAttributes.TryGetAttribute("my_class-name",out ClassNameAttribute)==true)
						{
							ClassName=ClassNameAttribute.Value.ToString();
						}

						NewElement.Attributes.Add("class",ClassName);
						NewElement.InnerHtml.Append("This CONTENT was ADDED by [CMyTagHelperComponent] TAG HELPER COMPONENT !");

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