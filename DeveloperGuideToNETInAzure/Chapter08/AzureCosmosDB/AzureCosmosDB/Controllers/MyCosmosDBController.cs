using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.Cosmos;
//----------------------------------------------------------------------------------------------------------------------
namespace AzureCosmosDB
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class MyCosmosDBController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CCosmosDBService						MCosmosDBService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public MyCosmosDBController(CCosmosDBService CosmosDBService)
		{
			MCosmosDBService=CosmosDBService;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetNames")]
		public IActionResult GetNames()
		{
			try
			{
				CItemName[]										ResultValue=MCosmosDBService.GetNames();
				IActionResult									Response=Ok(ResultValue);

				return(Response);
			}
			catch(CosmosException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				IActionResult									Result=StatusCode((int) E.StatusCode,E.Message);

				return(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				IActionResult									Result=Problem(E.Message);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetName")]
		public async Task<IActionResult> GetName(string ID, string Sex)
		{
			try
			{
				CItemName										ResultValue=await MCosmosDBService.GetName(ID,Sex);

				IActionResult									Response=Ok(ResultValue);

				return(Response);
			}
			catch(CosmosException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				IActionResult									Result=StatusCode((int) E.StatusCode,E.Message);

				return(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				IActionResult									Result=Problem(E.Message);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost("InsertName")]
		public async Task<IActionResult> InsertName(CItemName Name)
		{
			try
			{
				CItemName										ResultValue=await MCosmosDBService.InsertName(Name);
				IActionResult									Result=CreatedAtAction(nameof(InsertName),ResultValue);
				
				return(Result);
			}
			catch(CosmosException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				IActionResult									Result=StatusCode((int) E.StatusCode,E.Message);

				return(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				IActionResult									Result=Problem(E.Message);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPut("UpdateName")]
		public async Task<IActionResult> UpdateName(CItemName Name)
		{
			try
			{
				CItemName										Item=await MCosmosDBService.UpdateName(Name);

				IActionResult									Result=Ok(Item);

				return(Result);
			}
			catch(CosmosException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				IActionResult									Result=StatusCode((int) E.StatusCode,E.Message);

				return(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				IActionResult									Result=Problem(E.Message);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpDelete("DeleteName")]
		public async Task<IActionResult> DeleteName(string ID, string Sex)
		{
			try
			{
				await MCosmosDBService.DeleteName(ID,Sex);

				ActionResult									Response=NoContent();

				return(Response);
			}
			catch(CosmosException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				IActionResult									Result=StatusCode((int) E.StatusCode,E.Message);

				return(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				IActionResult									Result=Problem(E.Message);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------