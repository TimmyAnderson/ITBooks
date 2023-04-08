using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Mvc.Routing;
using Microsoft.AspNetCore.Razor.TagHelpers;
using RealApplication2.Models.ViewModels;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication2.Infrastructure
{
//----------------------------------------------------------------------------------------------------------------------
	[HtmlTargetElement("div",Attributes="page-model")]
	public sealed class CPageLinkTagHelper : TagHelper
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IUrlHelperFactory						MUrlHelperFactory;
//----------------------------------------------------------------------------------------------------------------------
		private ViewContext										MViewContext;
		private CPagingInfo										MPageModel;
		private string											MPageAction;
		private Dictionary<string,object>						MPageUrlValues;
		private bool											MPageClassesEnabled;
		private string											MPageClass;
		private string											MPageClassNormal;
		private string											MPageClassSelected;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPageLinkTagHelper(IUrlHelperFactory HelperFactory)
		{
			MUrlHelperFactory=HelperFactory;
			MPageUrlValues=new Dictionary<string,object>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[ViewContext]
		[HtmlAttributeNotBound]
		public ViewContext										ViewContext
		{
			get
			{
				return(MViewContext);
			}
			set
			{
				MViewContext=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPagingInfo										PageModel
		{
			get
			{
				return(MPageModel);
			}
			set
			{
				MPageModel=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											PageAction
		{
			get
			{
				return(MPageAction);
			}
			set
			{
				MPageAction=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HtmlAttributeName(DictionaryAttributePrefix="page-url-")]
		public Dictionary<string,object>						PageUrlValues
		{
			get
			{
				return(MPageUrlValues);
			}
			set
			{
				MPageUrlValues=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public bool												PageClassesEnabled
		{
			get
			{
				return(MPageClassesEnabled);
			}
			set
			{
				MPageClassesEnabled=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											PageClass
		{
			get
			{
				return(MPageClass);
			}
			set
			{
				MPageClass=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											PageClassNormal
		{
			get
			{
				return(MPageClassNormal);
			}
			set
			{
				MPageClassNormal=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											PageClassSelected
		{
			get
			{
				return(MPageClassSelected);
			}
			set
			{
				MPageClassSelected=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public override void Process(TagHelperContext Context, TagHelperOutput Output)
		{
			IUrlHelper											UrlHelper=MUrlHelperFactory.GetUrlHelper(ViewContext);
			TagBuilder											Result=new TagBuilder("div");

			for (int Index=1;Index<=PageModel.TotalPages;Index++)
			{
				TagBuilder										Tag=new TagBuilder("a");

				PageUrlValues["ProductPage"]=Index;

                Tag.Attributes["href"]=UrlHelper.Action(PageAction,PageUrlValues);

				if (MPageClassesEnabled==true)
				{
					Tag.AddCssClass(PageClass);
					Tag.AddCssClass(Index==PageModel.CurrentPage ? PageClassSelected : PageClassNormal);
				}

				Tag.InnerHtml.Append(Index.ToString());

				Result.InnerHtml.AppendHtml(Tag);
			}

			Output.Content.AppendHtml(Result.InnerHtml);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------