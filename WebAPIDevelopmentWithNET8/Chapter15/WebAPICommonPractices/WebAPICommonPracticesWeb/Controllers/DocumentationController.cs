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
	public class DocumentationController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		/// <summary>
		/// METHOD returns MY TYPE [CMyDocumentationType1].
		/// </summary>
		/// <returns>Returns TYPE [CMyDocumentationType1].</returns>
		[ProducesResponseType(typeof(CMyDocumentationType1),200)]
		[HttpGet("ReturnType1")]
		public IActionResult ReturnType1()
		{
			CMyDocumentationType1								Content=new CMyDocumentationType1("VALUE [111].",111);
			IActionResult										Result=Ok(Content);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		/// <summary>
		/// METHOD returns TYPE base on INPUT PARAMETER.
		/// </summary>
		/// <param name="TypeID">Parameter specifies RETURN TYPE.</param>
		/// <returns>Returns TYPE [CMyDocumentationType1], TYPE [CMyDocumentationType2], or NOT FOUND ERROR.</returns>
		[ProducesResponseType(typeof(CMyDocumentationType1),200)]
		[ProducesResponseType(typeof(CMyDocumentationType2),200)]
		[ProducesResponseType(404)]
		[HttpGet("ReturnType1OrType2")]
		public IActionResult ReturnType1OrType2(int TypeID)
		{
			if (TypeID==1)
			{
				CMyDocumentationType1							Content=new CMyDocumentationType1("VALUE [111].",111);
				IActionResult									Result=Ok(Content);

				return(Result);
			}
			if (TypeID==2)
			{
				CMyDocumentationType2							Content=new CMyDocumentationType2("VALUE [222].",222,222.222);
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