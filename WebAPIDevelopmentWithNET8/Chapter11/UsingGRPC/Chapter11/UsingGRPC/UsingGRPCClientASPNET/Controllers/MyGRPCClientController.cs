using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using UsingGRPC;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCClientASPNET
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public sealed class MyGRPCClientController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly Names.NamesClient						MClient;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLIENT sa vlozi cez DEPENDENTY INJECTION.
		public MyGRPCClientController(Names.NamesClient Client)
		{
			MClient=Client;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost("TestGRPCClient")]
		public async Task<IActionResult> TestGRPCClient([FromBody] NamesRequest Parameter)
		{
			Console.WriteLine("GRPC METHOD is CALLING.");

			// !!! Vola sa GPRC SERVER.
			NamesResponse										Response=await MClient.ProcessNamesAsync(Parameter);

			Console.WriteLine("GRPC METHOD is CALLED.");

			IActionResult										Result=Ok(Response);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------