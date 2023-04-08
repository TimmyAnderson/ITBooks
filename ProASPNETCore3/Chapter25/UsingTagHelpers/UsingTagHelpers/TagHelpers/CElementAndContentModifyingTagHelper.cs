using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Razor.TagHelpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingTagHelpers.TagHelpers
{
//----------------------------------------------------------------------------------------------------------------------
	[HtmlTargetElement("div",Attributes="Use")]
	public sealed class CElementAndContentModifyingTagHelper : TagHelper
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MMyFontSizeInPixels;
		private bool											MMyFontSizeInPixelsIsSet;
		private string											MMyFontFamily;
		private bool											MMyFontFamilyIsSet;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ASP.NET sa pri nastavovani PROPERTY pokusi vykonat konverziu na PROPERTY TYPE [int].
		public int												MyFontSizeInPixels
		{
			get
			{
				return(MMyFontSizeInPixels);
			}
			set
			{
				MMyFontSizeInPixels=value;
				MMyFontSizeInPixelsIsSet=true;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! ASP.NET sa pri nastavovani PROPERTY pokusi vykonat konverziu na PROPERTY TYPE [int].
		// !!!!! PROPERTY ma definovany CUSTOM HTML ATTRIBUTE NAME cez ktory sa k nej pristupuje pri pouziti TAG HELPER.
		[HtmlAttributeName("MyFontName")]
		public string											MyFontFamily
		{
			get
			{
				return(MMyFontFamily);
			}
			set
			{
				MMyFontFamily=value;
				MMyFontFamilyIsSet=true;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD [void Process(TagHelperContext Context, TagHelperOutput Output)] modifikuje HTML CONTENT na zaklade nastavenia TAG HELPER.
		public override void Process(TagHelperContext Context, TagHelperOutput Output)
		{
			StringBuilder										SB=new StringBuilder();
			TagHelperAttribute									Color;

			if (Context.AllAttributes.TryGetAttribute("my-color",out Color)==true)
			{
				SB.Append($"color:{Color.Value};");
			}

			if (MMyFontSizeInPixelsIsSet==true)
			{
				SB.Append($"font-size:{MyFontSizeInPixels}px;");
			}

			if (MMyFontFamilyIsSet==true)
			{
				SB.Append($"font-family:{MyFontFamily};");
			}

			// !!! Odstrani sa HTML ATTRIBUTE 'my-color', ktora kedze NEMA DEFINOVANU C# PROPERTY, je AUTOMATICKY prenesena z povodneho HTML ELEMENT na ktory bol aplikovany TAG HELPER do generovaneho HTML ELEMENT.
			// !!! HTML ATTRIBUTES, ktore maju definovanu C# PROPERTY NIE SU AUTOMATICKY prenesene do generovaneho HTML ELEMENT.
			Output.Attributes.Clear();

			if (SB.Length>0)
			{
				Output.Attributes.SetAttribute("style",SB.ToString());
			}

			// !!! Vytvori sa HTML ELEMENT, ktory sa prida ako PREFIX HTML ELEMENT.
			TagBuilder											ElementPrefix=new TagBuilder("h2");

			ElementPrefix.Attributes.Add("class","INNER_BOX");
			ElementPrefix.InnerHtml.Append("This is PREFIX H2 HTML ELEMENT !");

			// !!! Vytvori sa HTML ELEMENT, ktory sa prida ako POSTFIX HTML ELEMENT.
			TagBuilder											ElementPostfix=new TagBuilder("h4");

			ElementPostfix.Attributes.Add("class","INNER_BOX");
			ElementPostfix.InnerHtml.Append("This is POSTFIX H4 HTML ELEMENT !");

			// !!! Pred generovany HTML ELEMENT sa prida PREFIX ELEMENT.
			Output.PreElement.SetHtmlContent(ElementPrefix);

			// !!! Za generovany HTML ELEMENT sa prida POSTFIX ELEMENT.
			Output.PostElement.SetHtmlContent(ElementPostfix);

			// !!! CONTENT sa vlozi pred CONTENT generovaneho HTML ELEMENT.
			Output.PreContent.SetHtmlContent("This is PREFIX CONTENT !<br/>");

			// !!! CONTENT sa vlozi za CONTENT generovaneho HTML ELEMENT.
			Output.PostContent.SetHtmlContent("<br/>This is POSTFIX CONTENT !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------