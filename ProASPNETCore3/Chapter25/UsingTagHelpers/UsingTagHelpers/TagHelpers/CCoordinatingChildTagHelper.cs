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
	// !!! TAG HELPER iba cita CUSTOM VALUES z PROPERTY [TagHelperContext.Items] kde ich ulozit TAG HELPER 'CCoordinatingParentTagHelper' aplikovany na PARENT HTML ELEMENT.
	// !!! CHILD HTML ELEMENT TAG HELPER sa aplikuje IBA ak ma ako PARENT HTML ELEMENT [<div>].
	[HtmlTargetElement("main",ParentTag="div")]
	public sealed class CCoordinatingChildTagHelper : TagHelper
	{
//----------------------------------------------------------------------------------------------------------------------
		public override void Process(TagHelperContext Context, TagHelperOutput Output)
		{
			StringBuilder										SB=new StringBuilder();
			object												RawColor;

			// !!! Nacita sa hodnota COLOR z PROPERTY [TagHelperContext.Items].
			if (Context.Items.TryGetValue("MyColor",out RawColor)==true)
			{
				SB.Append($"color:{RawColor};");
			}

			object												RawFontSizeInPixels;

			// !!! Nacita sa hodnota FONT SIZE z PROPERTY [TagHelperContext.Items].
			if (Context.Items.TryGetValue("MyFontSizeInPixels",out RawFontSizeInPixels)==true)
			{
				SB.Append($"font-size:{RawFontSizeInPixels}px;");
			}

			object												RawFontFamily;

			// !!! Nacita sa hodnota FONT FAMILY z PROPERTY [TagHelperContext.Items].
			if (Context.Items.TryGetValue("MyFontFamily",out RawFontFamily)==true)
			{
				SB.Append($"font-family:{RawFontFamily};");
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