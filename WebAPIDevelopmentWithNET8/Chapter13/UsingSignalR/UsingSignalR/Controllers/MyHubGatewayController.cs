using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.SignalR;
using Microsoft.Extensions.Configuration;
using Microsoft.IdentityModel.Tokens;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingSignalR
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CONTROLLER umoznuje posielat REST CLIENTS MESSAGES cez SignalR.
	[ApiController]
	[Route("[controller]")]
	[Authorize]
	public class MyHubGatewayController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IHubContext<CMyStronlyTypedHub,IMyClientInterface>	MHubContext;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public MyHubGatewayController(IHubContext<CMyStronlyTypedHub,IMyClientInterface> HubContext)
		{
			MHubContext=HubContext;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("SendMessageViaSignalR")]
		public async Task<IActionResult> SendMessageViaSignalR(string Sender, string Message)
		{
			IMyClientInterface									Proxy=MHubContext.Clients.All;

			await Proxy.MyReceiveMessage(Sender,Message);

			OkResult											OkResult=Ok();

			return(OkResult);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------