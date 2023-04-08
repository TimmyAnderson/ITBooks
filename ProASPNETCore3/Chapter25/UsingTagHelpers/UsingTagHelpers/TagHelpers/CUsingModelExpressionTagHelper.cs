using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using Microsoft.AspNetCore.Razor.TagHelpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingTagHelpers.TagHelpers
{
//----------------------------------------------------------------------------------------------------------------------
	[HtmlTargetElement("div",Attributes="my-model-expression")]
	public sealed class CUsingModelExpressionTagHelper : TagHelper
	{
//----------------------------------------------------------------------------------------------------------------------
		private ModelExpression									MMyModelExpression;
//----------------------------------------------------------------------------------------------------------------------
		private int												MMyFontSizeInPixels;
		private bool											MMyFontSizeInPixelsIsSet;
		private string											MMyFontFamily;
		private bool											MMyFontFamilyIsSet;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Instancia CLASS [ModelExpression] obsahuje informacie o MODEL OBJECT PROPERTY na ktoru je PROPERTY 'MyModelExpression' mapovana.
		public ModelExpression									MyModelExpression
		{
			get
			{
				return(MMyModelExpression);
			}
			set
			{
				MMyModelExpression=value;
			}
		}
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

			if (MMyModelExpression!=null)
			{
				// !!! Pouzije sa instancia CLASS [ModelExpression].
				Output.PostContent.AppendHtml($"<br/>MODEL TYPE [{MMyModelExpression.Metadata.ModelType.Name}] !");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------