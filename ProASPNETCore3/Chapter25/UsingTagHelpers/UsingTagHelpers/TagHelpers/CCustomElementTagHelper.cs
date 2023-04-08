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
	// !!! TAG HELPER sa aplikuje na CUSTOM HTML ELEMENT, ktory NIE JE SUCASTOU HTML SPECIFICATION. TAG HELPER MUSI nahradit tento CUSTOM HTML ELEMENT za standardny HTML ELEMENT podporovany HTML SPECIFICATION.
	[HtmlTargetElement("tobereplaced")]
	public sealed class CCustomElementTagHelper : TagHelper
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

			// !!! Nastavi sa TAG na HTML ELEMENT, ktory PODPORUJE HTML SPECIFICATION.
			Output.TagName="div";

			// !!! Nastavi sa, aby generovany HTML ELEMENT mal BEGIN aj END TAG.
			Output.TagMode=TagMode.StartTagAndEndTag;

			// !!! Odstrani sa HTML ATTRIBUTE 'my-color', ktora kedze NEMA DEFINOVANU C# PROPERTY, je AUTOMATICKY prenesena z povodneho HTML ELEMENT na ktory bol aplikovany TAG HELPER do generovaneho HTML ELEMENT.
			// !!! HTML ATTRIBUTES, ktore maju definovanu C# PROPERTY NIE SU AUTOMATICKY prenesene do generovaneho HTML ELEMENT.
			Output.Attributes.Clear();

			if (SB.Length>0)
			{
				Output.Attributes.SetAttribute("style",SB.ToString());
			}

			// !!!!! CONTENT NETREBA nastavovat, pretoze sa prenesie z povodneho HTML ELEMENT.
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------