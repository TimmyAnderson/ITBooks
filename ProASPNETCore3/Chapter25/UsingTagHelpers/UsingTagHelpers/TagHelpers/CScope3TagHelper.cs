using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Razor.TagHelpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingTagHelpers.TagHelpers
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! TAG HELPER sa aplikuje na LUBOVOLNY HTML ELEMENT, ktory ma definovany HTML ATTRIBUTE 'Use' a ten ma VALUE 'true'.
	[HtmlTargetElement("*",Attributes="[Use=true]")]
	public sealed class CScope3TagHelper : TagHelper
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

			// !!! Hodnota TAG HELPER PROPERTY sa cita z COLLECTION [TagHelperContext.AllAttributes].
			if (Context.AllAttributes.TryGetAttribute("my-color",out Color)==true)
			{
				SB.Append($"color:{Color.Value};");
			}

			// !!! Hodnota TAG HELPER PROPERTY sa cita z dedikovanej C# PROPERTY.
			if (MMyFontSizeInPixelsIsSet==true)
			{
				SB.Append($"font-size:{MyFontSizeInPixels}px;");
			}

			// !!! Hodnota TAG HELPER PROPERTY sa cita z dedikovanej C# PROPERTY, ktora ma definovany CUSTOM NAME cez ATTRIBUTE [HtmlAttributeNameAttribute].
			if (MMyFontFamilyIsSet==true)
			{
				SB.Append($"font-family:{MyFontFamily};");
			}

			if (SB.Length>0)
			{
				Output.Attributes.SetAttribute("style",SB.ToString());
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------