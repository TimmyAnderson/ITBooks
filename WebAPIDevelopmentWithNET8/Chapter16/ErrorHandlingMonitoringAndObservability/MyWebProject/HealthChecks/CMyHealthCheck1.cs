using System.Threading;
using System.Threading.Tasks;
using Microsoft.Extensions.Diagnostics.HealthChecks;
//----------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CMyHealthCheck1 : IHealthCheck
	{
//----------------------------------------------------------------------------------------------------------------------
		private static object									MLock=new object();
		private static HealthStatus								MCurrentStatus=HealthStatus.Healthy;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static HealthStatus GetCurrentStatus()
		{
			lock(MLock)
			{
				return(MCurrentStatus);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public static void SetCurrentStatus(HealthStatus Status)
		{
			lock(MLock)
			{
				MCurrentStatus=Status;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public Task<HealthCheckResult> CheckHealthAsync(HealthCheckContext Context, CancellationToken CancellationToken)
		{
			HealthStatus										CurrentStatus=GetCurrentStatus();

			if (CurrentStatus==HealthStatus.Healthy)
			{
				HealthCheckResult								Result=HealthCheckResult.Healthy("CHECK 1 - STATUS [HEALTHY].");
				Task<HealthCheckResult>							ResultTask=Task.FromResult<HealthCheckResult>(Result);

				return(ResultTask);
			}
			else if (CurrentStatus==HealthStatus.Degraded)
			{
				HealthCheckResult								Result=HealthCheckResult.Degraded("CHECK 1 - STATUS [DEGRADED].");
				Task<HealthCheckResult>							ResultTask=Task.FromResult<HealthCheckResult>(Result);

				return(ResultTask);
			}
			else if (CurrentStatus==HealthStatus.Unhealthy)
			{
				HealthCheckResult								Result=HealthCheckResult.Unhealthy("CHECK 1 - STATUS [UNHEALTHY].");
				Task<HealthCheckResult>							ResultTask=Task.FromResult<HealthCheckResult>(Result);

				return(ResultTask);
			}
			else
			{
				HealthCheckResult								Result=HealthCheckResult.Unhealthy("CHECK 1 - UNKNOWN STATUS.");
				Task<HealthCheckResult>							ResultTask=Task.FromResult<HealthCheckResult>(Result);

				return(ResultTask);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------