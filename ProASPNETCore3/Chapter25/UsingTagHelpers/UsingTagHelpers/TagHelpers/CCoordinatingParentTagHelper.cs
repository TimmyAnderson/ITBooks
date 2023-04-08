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
	// !!! TAG HELPER iba uklada CUSTOM VALUES do PROPERTY [TagHelperContext.Items] odkial ich TAG HELPER 'CCoordinatingChildTagHelper' aplikovany na CHILD HTML ELEMENT vybera.
	[HtmlTargetElement("div")]
	public sealed class CCoordinatingParentTagHelper : TagHelper
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
		public override void Process(TagHelperContext Context, TagHelperOutput Output)
		{
			TagHelperAttribute									Color;

			// !!! Hodnota TAG HELPER PROPERTY sa cita z COLLECTION [TagHelperContext.AllAttributes].
			if (Context.AllAttributes.TryGetAttribute("my-color",out Color)==true)
			{
				// !!! Do PROPERTY [TagHelperContext.Items] sa ulozi hotnota COLOR.
				Context.Items["MyColor"]=Color.Value;
			}

			// !!! Hodnota TAG HELPER PROPERTY sa cita z dedikovanej C# PROPERTY.
			if (MMyFontSizeInPixelsIsSet==true)
			{
				// !!! Do PROPERTY [TagHelperContext.Items] sa ulozi hotnota FONT SIZE.
				Context.Items["MyFontSizeInPixels"]=MyFontSizeInPixels;
			}

			// !!! Hodnota TAG HELPER PROPERTY sa cita z dedikovanej C# PROPERTY, ktora ma definovany CUSTOM NAME cez ATTRIBUTE [HtmlAttributeNameAttribute].
			if (MMyFontFamilyIsSet==true)
			{
				// !!! Do PROPERTY [TagHelperContext.Items] sa ulozi hotnota FONT FAMILY.
				Context.Items["MyFontFamily"]=MyFontFamily;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------