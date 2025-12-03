using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Caching.Distributed;
using Microsoft.Extensions.Caching.Memory;
//----------------------------------------------------------------------------------------------------------------------
namespace WebAPICommonPracticesWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class RemoteWebAPIController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("ExecuteGet")]
		public IActionResult ExecuteGet(int Parameter)
		{
			if (Parameter==1)
			{
				CMyGetResponseType								MyCachedData=new CMyGetResponseType("aaa",100);
				IActionResult									Result=Ok(MyCachedData);

				return(Result);
			}
			else if (Parameter==2)
			{
				CMyGetResponseType								MyCachedData=new CMyGetResponseType("bbb",200);
				IActionResult									Result=Ok(MyCachedData);

				return(Result);
			}
			else
			{
				IActionResult									Result=NotFound();

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost("ExecutePost")]
		public IActionResult ExecutePost(CMyPostRequestType Request)
		{
			CMyPostResponseType									Response=new CMyPostResponseType(Request.Value1.ToUpper(),Request.Value2+1000);
			IActionResult										Result=Ok(Response);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------