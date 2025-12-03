using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace WebAPICommonPracticesWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class ProducesResponseTypeController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[ProducesResponseType(typeof(CMyType1),200)]
		[HttpGet("ReturnType1")]
		public IActionResult ReturnType1()
		{
			CMyType1											Content=new CMyType1("VALUE [111].",111);
			IActionResult										Result=Ok(Content);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[ProducesResponseType(typeof(CMyType1),200)]
		[ProducesResponseType(typeof(CMyType2),200)]
		[ProducesResponseType(404)]
		[HttpGet("ReturnType1OrType2")]
		public IActionResult ReturnType1OrType2(int TypeID)
		{
			if (TypeID==1)
			{
				CMyType1										Content=new CMyType1("VALUE [111].",111);
				IActionResult									Result=Ok(Content);

				return(Result);
			}
			if (TypeID==2)
			{
				CMyType2										Content=new CMyType2("VALUE [222].",222,222.222);
				IActionResult									Result=Ok(Content);

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