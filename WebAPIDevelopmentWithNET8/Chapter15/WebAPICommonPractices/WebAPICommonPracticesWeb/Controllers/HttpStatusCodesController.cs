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
	public class HttpStatusCodesController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("Return200")]
		public IActionResult Return200()
		{
			IActionResult										Result=Ok("Hello 200.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("Return201")]
		public IActionResult Return201()
		{
			IActionResult										Result=Created("http://MyUrl.http","Hello 201.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("Return202")]
		public IActionResult Return202()
		{
			IActionResult										Result=Accepted("Hello 202.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("Return204")]
		public IActionResult Return204()
		{
			IActionResult										Result=NoContent();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("Return400")]
		public IActionResult Return400()
		{
			IActionResult										Result=BadRequest("Hello 400.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("Return401")]
		public IActionResult Return401()
		{
			IActionResult										Result=Unauthorized("Hello 401.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("Return405")]
		public IActionResult Return405()
		{
			IActionResult										Result=NotFound("Hello 405.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("Return409")]
		public IActionResult Return409()
		{
			IActionResult										Result=Conflict("Hello 409.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("Return422")]
		public IActionResult Return422()
		{
			IActionResult										Result=UnprocessableEntity("Hello 422.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("Return500")]
		public IActionResult Return500()
		{
			IActionResult										Result=StatusCode(500,"Hello 500.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------