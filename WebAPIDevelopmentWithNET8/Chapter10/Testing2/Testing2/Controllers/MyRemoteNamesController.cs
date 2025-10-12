using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace Testing2
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class MyRemoteNamesController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<NamesController>				MLogger;
		private readonly IMyRemoteNamesService					MMyRemoteNamesService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public MyRemoteNamesController(ILogger<NamesController> Logger, IMyRemoteNamesService MyRemoteNamesService)
		{
			MLogger=Logger;
			MMyRemoteNamesService=MyRemoteNamesService;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetName1")]
		public ActionResult GetName1()
		{
			try
			{
				CMyRemoteName									Name=MMyRemoteNamesService.GetName1();

				ActionResult									Response=Ok(Name);

				return(Response);
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetName2")]
		public ActionResult GetName2()
		{
			try
			{
				CMyRemoteName									Name=MMyRemoteNamesService.GetName2();

				ActionResult									Response=Ok(Name);

				return(Response);
			}
			catch(Exception E)
			{
				MLogger.LogError(E,"OPERATION FAILED.");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------