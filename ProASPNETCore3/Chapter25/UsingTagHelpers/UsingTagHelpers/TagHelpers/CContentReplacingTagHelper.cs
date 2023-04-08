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
	[HtmlTargetElement("div")]
	public sealed class CContentReplacingTagHelper : TagHelper
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
		// !!! METHOD [Task ProcessAsync(TagHelperContext Context, TagHelperOutput Output)] modifikuje HTML CONTENT na zaklade nastavenia TAG HELPER.
		// !!! Je to ASYNCHRONNA verzia METHOD [void Process(TagHelperContext Context, TagHelperOutput Output)].
		public override async Task ProcessAsync(TagHelperContext Context, TagHelperOutput Output)
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

			// !!! Nacita sa CONTENT HTML ELEMENT na ktory je TAG HELPER aplikovany.
			TagHelperContent									OriginalContent=await Output.GetChildContentAsync();
			string												OriginalContentValue=OriginalContent.GetContent();
			string												NewContent=$"Hello TIMMY ANDERSON ! {OriginalContentValue} Hello JENNY THOMPSON !";

			// !!! Nastavi sa CONTENT HTML ELEMENT na ktory je TAG HELPER aplikovany.
			Output.Content.SetHtmlContent(NewContent);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------