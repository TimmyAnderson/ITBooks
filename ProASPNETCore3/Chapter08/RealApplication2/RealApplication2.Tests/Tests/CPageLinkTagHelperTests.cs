using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Routing;
using Microsoft.AspNetCore.Razor.TagHelpers;
using Moq;
using Xunit;
using RealApplication2.Infrastructure;
using RealApplication2.Models.ViewModels;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication2.Tests.Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CPageLinkTagHelperTests
	{
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public void Can_Generate_Page_Links()
		{
			Mock<IUrlHelper>									UrlHelper=new Mock<IUrlHelper>();

			UrlHelper.SetupSequence(P => P.Action(It.IsAny<UrlActionContext>())).Returns("Test/Page1").Returns("Test/Page2").Returns("Test/Page3");

			Mock<IUrlHelperFactory>								UrlHelperFactory=new Mock<IUrlHelperFactory>();

			UrlHelperFactory.Setup(P => P.GetUrlHelper(It.IsAny<ActionContext>())).Returns(UrlHelper.Object);

			CPageLinkTagHelper									Helper=new CPageLinkTagHelper(UrlHelperFactory.Object);

			Helper.PageModel=new CPagingInfo(28,10,2);
			Helper.PageAction="Test";

			TagHelperContext									Context=new TagHelperContext(new TagHelperAttributeList(),new Dictionary<object,object>(),"");
			Mock<TagHelperContent>								Content=new Mock<TagHelperContent>();
			TagHelperOutput										Output=new TagHelperOutput("div",new TagHelperAttributeList(),(Cache, Encoder) => Task.FromResult(Content.Object));

			Helper.Process(Context,Output);

			Assert.Equal(@"<a href=""Test/Page1"">1</a><a href=""Test/Page2"">2</a><a href=""Test/Page3"">3</a>",Output.Content.GetContent());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------