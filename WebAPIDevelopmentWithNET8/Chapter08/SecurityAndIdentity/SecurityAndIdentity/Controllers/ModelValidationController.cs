using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace SecurityAndIdentity
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class ModelValidationController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult PostValue([FromBody] CMyModelValidation Value)
		{
			if (Value.FirstName.Length>0 && char.IsUpper(Value.FirstName[0])==false)
			{
				ModelState.AddModelError("FirstName","Name doesn't start with UPPER CASE CHARACTER.");
			}

			if (Value.LastName.Length>0 && char.IsUpper(Value.LastName[0])==false)
			{
				ModelState.AddModelError("LastName","Name doesn't start with UPPER CASE CHARACTER.");
			}

			if (ModelState.IsValid==true)
			{
				IActionResult									Result=Ok($"Hello [{Value.FirstName} {Value.LastName}] !");

				return(Result);
			}
			else
			{
				IActionResult									Result=BadRequest(ModelState);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------