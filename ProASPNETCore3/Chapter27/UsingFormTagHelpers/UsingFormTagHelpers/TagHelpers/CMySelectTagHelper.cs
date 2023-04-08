using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using Microsoft.AspNetCore.Razor.TagHelpers;
using UsingFormTagHelpers.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFormTagHelpers.TagHelpers
{
//----------------------------------------------------------------------------------------------------------------------
	[HtmlTargetElement("select",Attributes="my-model-property")]
	public sealed class CMySelectTagHelper : TagHelper
	{
//----------------------------------------------------------------------------------------------------------------------
		private ModelExpression									MMyModelProperty;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ModelExpression									MyModelProperty
		{
			get
			{
				return(MMyModelProperty);
			}
			set
			{
				MMyModelProperty=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async override Task ProcessAsync(TagHelperContext Context, TagHelperOutput Output)
		{
			// !!! Ziska sa povodny CONTENT HTML ELEMENT [<select>]. To znaci, ze ak napriklad v HTML ELEMENT [<select>] boli explicitne definovane HTML ELEMENTS [<option>], tak sa tieto ulozia do instancie CLASS [TagHelperContent].
			TagHelperContent									OriginalContent=await Output.GetChildContentAsync(false);

			// !!! Nastavi sa HTML ATTRIBUTE [Name].
			Output.Attributes.SetAttribute("Name",MyModelProperty.Name);

			// !!! Nastavi sa HTML ATTRIBUTE [Id].
			Output.Attributes.SetAttribute("Id",MyModelProperty.Name);

			// !!! Prida sa POVODNY CONTENT. To znaci, ze ak napriklad bol explicitne pridany nejaky HTML ELEMENT [<option>] tak sa prida do CONTENT HTML ELEMENT [<select>].
			Output.Content.AppendHtml(OriginalContent.GetContent());

			// !!! Ziska sa PROPERTY na ktoru odkazuje HTML ATTRIBUTE [my-model-property].
			PropertyInfo										Property=typeof(CChild).GetProperty(MyModelProperty.Name);
			Type												PropertyType=Property.PropertyType;

			// !!! OPTIONS sa naplnia IBA ak PROPERTY obsahuje ENUM TYPE.
			if (PropertyType.IsEnum==true)
			{
				string[]										EnumValues=Enum.GetNames(PropertyType);
				
				foreach(string EnumValue in EnumValues)
				{
					string										OptionHtmlElement=$"<option>{EnumValue}</option>";

					// !!! Prida sa HTML ELEMENT [<option>].
					Output.Content.AppendHtml(OptionHtmlElement);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------