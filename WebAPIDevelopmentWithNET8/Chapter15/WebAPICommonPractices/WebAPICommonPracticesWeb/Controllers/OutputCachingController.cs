using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.OutputCaching;
using Microsoft.Extensions.Caching.Distributed;
using Microsoft.Extensions.Caching.Memory;
//----------------------------------------------------------------------------------------------------------------------
namespace WebAPICommonPracticesWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class OutputCachingController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("CachingPolicy1")]
		[OutputCache(PolicyName=Program.OUTPUT_CACHING_POLICY_1)]
		public IActionResult CachingPolicy1(int Parameter)
		{
			if (Parameter==1)
			{
				Random											RND=new Random();
				int												IntValue=RND.Next();

				string											Value=$"VALUE 1 [{IntValue}].";
				DateTime										DateTime=DateTime.Now;

				CMyCachedData									MyCachedData=new CMyCachedData(Value,DateTime);

				IActionResult									Result=Ok(MyCachedData);

				return(Result);
			}
			else if (Parameter==2)
			{
				Random											RND=new Random();
				int												IntValue=RND.Next();

				string											Value=$"VALUE 2 [{IntValue}].";
				DateTime										DateTime=DateTime.Now;

				CMyCachedData									MyCachedData=new CMyCachedData(Value,DateTime);

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
		[HttpGet("CachingPolicy2")]
		[OutputCache(PolicyName=Program.OUTPUT_CACHING_POLICY_2)]
		public IActionResult CachingPolicy2(int Parameter)
		{
			if (Parameter==1)
			{
				Random											RND=new Random();
				int												IntValue=RND.Next();

				string											Value=$"VALUE 1 [{IntValue}].";
				DateTime										DateTime=DateTime.Now;

				CMyCachedData									MyCachedData=new CMyCachedData(Value,DateTime);

				IActionResult									Result=Ok(MyCachedData);

				return(Result);
			}
			else if (Parameter==2)
			{
				Random											RND=new Random();
				int												IntValue=RND.Next();

				string											Value=$"VALUE 2 [{IntValue}].";
				DateTime										DateTime=DateTime.Now;

				CMyCachedData									MyCachedData=new CMyCachedData(Value,DateTime);

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
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------