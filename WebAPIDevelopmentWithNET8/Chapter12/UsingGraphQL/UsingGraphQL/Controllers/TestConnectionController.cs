using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class TestConnectionController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public string GetValue()
		{
			return("Hello WORLD !");
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public string PostValue([FromBody] string Value)
		{
			return($"Hello [{Value}] !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------