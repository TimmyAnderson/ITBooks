using Microsoft.AspNetCore.Mvc;
using Microsoft.FeatureManagement;
using Microsoft.FeatureManagement.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace AzureAppConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class FeatureFlags2Controller : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[FeatureGate("MyFeature3")]
		[HttpGet("IsRunning1")]
		public IActionResult IsRunning1()
		{
			IActionResult										Result=Ok("FEATURE FLAG 2 is IS RUNNIG 1 !");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[FeatureGate("MyFeature4")]
		[HttpGet("IsRunning2")]
		public IActionResult IsRunning2()
		{
			IActionResult										Result=Ok("FEATURE FLAG 2 is IS RUNNIG 2 !");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------