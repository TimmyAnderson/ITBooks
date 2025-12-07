using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using FluentValidation;
using FluentValidation.Results;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class ObservabilityController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CMyObservabilityService				MObservabilityService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ObservabilityController(CMyObservabilityService ObservabilityService)
		{
			MObservabilityService=ObservabilityService;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet(nameof(TestMethod1))]
		public async Task<IActionResult> TestMethod1(int ID, int MaxWaitTimeoutInMS)
		{
			MObservabilityService.IncrementUpDownCounter1();

			Stopwatch											Stopwatch=Stopwatch.StartNew();

			double												StartCpuUsage=Process.GetCurrentProcess().TotalProcessorTime.TotalMicroseconds;

			Random												RND=new Random();
			int													WaitTimeoutInMS=RND.Next(MaxWaitTimeoutInMS);

			await Task.Delay(WaitTimeoutInMS);

			string												Content=$"ID [{ID}] - METHOD 1 EXECUTED.";
			IActionResult										Result=Ok(Content);

			Stopwatch.Stop();

			double												TotalMicroseconds=Stopwatch.Elapsed.TotalMicroseconds;

			double												EndCpuUsage=Process.GetCurrentProcess().TotalProcessorTime.TotalMicroseconds;

			double												CpuUsageInMS=(EndCpuUsage-StartCpuUsage);
			double												CpuUsagePerAllCPUs=(CpuUsageInMS/TotalMicroseconds);
			double												CpuUsagePerSingleCPU=(CpuUsagePerAllCPUs/Environment.ProcessorCount);
			double												CpuUsagePerSingleCPUInPercent=(CpuUsagePerSingleCPU*100.0);

			MObservabilityService.IncrementCounter1();
			MObservabilityService.DecrementUpDownCounter1();
			MObservabilityService.RecordGauge1(CpuUsagePerSingleCPUInPercent);
			MObservabilityService.RecordHistogram1(TotalMicroseconds);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet(nameof(TestMethod2))]
		public async Task<IActionResult> TestMethod2(int ID, int MaxWaitTimeoutInMS)
		{
			MObservabilityService.IncrementUpDownCounter2();

			Stopwatch											Stopwatch=Stopwatch.StartNew();

			double												StartCpuUsage=Process.GetCurrentProcess().TotalProcessorTime.TotalMicroseconds;

			Random												RND=new Random();
			int													WaitTimeoutInMS=RND.Next(MaxWaitTimeoutInMS);

			await Task.Delay(WaitTimeoutInMS);

			string												Content=$"ID [{ID}] - METHOD 2 EXECUTED.";
			IActionResult										Result=Ok(Content);

			Stopwatch.Stop();

			double												TotalMicroseconds=Stopwatch.Elapsed.TotalMicroseconds;

			double												EndCpuUsage=Process.GetCurrentProcess().TotalProcessorTime.TotalMicroseconds;

			double												CpuUsageInMS=(EndCpuUsage-StartCpuUsage);
			double												CpuUsagePerAllCPUs=(CpuUsageInMS/TotalMicroseconds);
			double												CpuUsagePerSingleCPU=(CpuUsagePerAllCPUs/Environment.ProcessorCount);
			double												CpuUsagePerSingleCPUInPercent=(CpuUsagePerSingleCPU*100.0);

			MObservabilityService.IncrementCounter2();
			MObservabilityService.DecrementUpDownCounter2();
			MObservabilityService.RecordGauge2(CpuUsagePerSingleCPUInPercent);
			MObservabilityService.RecordHistogram2(TotalMicroseconds);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------