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
	public class ResponseCachingController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("ResponseCaching")]
		[ResponseCache(Duration=60)]
		public IActionResult ResponseCaching()
		{
			Random												RND=new Random();
			int													IntValue=RND.Next();

			string												Value=$"VALUE [{IntValue}].";
			DateTime											DateTime=DateTime.Now;

			CMyCachedData										MyCachedData=new CMyCachedData(Value,DateTime);

			IActionResult										Result=Ok(MyCachedData);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------