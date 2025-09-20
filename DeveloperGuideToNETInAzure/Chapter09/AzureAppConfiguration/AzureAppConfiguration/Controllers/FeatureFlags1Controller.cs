using Microsoft.AspNetCore.Mvc;
using Microsoft.FeatureManagement;
//----------------------------------------------------------------------------------------------------------------------
namespace AzureAppConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class FeatureFlags1Controller : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IFeatureManager						MFeatureManager;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public FeatureFlags1Controller(IFeatureManager FeatureManager)
		{
			MFeatureManager=FeatureManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetListOfFeatures")]
		public IActionResult GetListOfFeatures()
		{
			bool												MyFeatureEnabled1=MFeatureManager.IsEnabledAsync("MyFeature1").Result;
			bool												MyFeatureEnabled2=MFeatureManager.IsEnabledAsync("MyFeature2").Result;
			bool												MyAzureFeatureEnabled1=MFeatureManager.IsEnabledAsync("MyAzureFeature1").Result;
			bool												MyAzureFeatureEnabled2=MFeatureManager.IsEnabledAsync("MyAzureFeature2").Result;
			CFeatureFlagsResponse								ResponseValue=new CFeatureFlagsResponse(MyFeatureEnabled1,MyFeatureEnabled2,MyAzureFeatureEnabled1,MyAzureFeatureEnabled2);
			IActionResult										Result=Ok(ResponseValue);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------