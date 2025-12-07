using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using FluentValidation;
using FluentValidation.Results;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Diagnostics.HealthChecks;
//----------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class SetHealthCheckStatusController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet(nameof(SetHealthCheckStatus))]
		public IActionResult SetHealthCheckStatus(int StatusID, int StatusValue)
		{
			if (StatusID<1 || StatusID>4)
			{
				IActionResult									Result=BadRequest("INVALID STATUS ID.");

				return(Result);
			}
			else if (StatusValue<1 || StatusValue>3)
			{
				IActionResult									Result=BadRequest("INVALID STATUS VALUE.");

				return(Result);
			}
			else
			{
				HealthStatus									Status=HealthStatus.Unhealthy;

				if (StatusValue==1)
				{
					Status=HealthStatus.Healthy;
				}
				else if (StatusValue==2)
				{
					Status=HealthStatus.Degraded;
				}
				else if (StatusValue==3)
				{
					Status=HealthStatus.Unhealthy;
				}
				else
				{
					Status=HealthStatus.Unhealthy;
				}

				if (StatusID==1)
				{
					CMyHealthCheck1.SetCurrentStatus(Status);
				}
				else if (StatusID==2)
				{
					CMyHealthCheck2.SetCurrentStatus(Status);
				}
				else if (StatusID==3)
				{
					CMyHealthCheck3.SetCurrentStatus(Status);
				}
				else if (StatusID==4)
				{
					CMyHealthCheck4.SetCurrentStatus(Status);
				}

				IActionResult									Result=Ok("STATUS SET.");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------