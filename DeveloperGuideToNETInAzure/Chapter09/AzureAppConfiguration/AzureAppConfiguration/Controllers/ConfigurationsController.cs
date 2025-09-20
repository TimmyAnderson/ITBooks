using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Options;
//----------------------------------------------------------------------------------------------------------------------
namespace AzureAppConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class ConfigurationsController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IConfiguration							MConfiguration;
		private readonly IOptionsSnapshot<CComplexConfiguration>	MComplexConfiguration;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ConfigurationsController(IConfiguration Configuration, IOptionsSnapshot<CComplexConfiguration> ComplexConfiguration)
		{
			MComplexConfiguration=ComplexConfiguration;
			MConfiguration=Configuration;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetConfigurations")]
		public IActionResult GetConfigurations()
		{
			CComplexConfiguration								ComplexConfiguration=MComplexConfiguration.Value;

			string												Value1=MConfiguration.GetValue<string>("value1") ?? "";
			int													Value2=MConfiguration.GetValue<int>("value2");
			string												ComplexConfigurationValue1=ComplexConfiguration?.Value1 ?? "";
			int													ComplexConfigurationValue2=ComplexConfiguration?.Value2 ?? 0;

			CReadConfigurationResponse							ResponseValue=new CReadConfigurationResponse(Value1,Value2,ComplexConfigurationValue1,ComplexConfigurationValue2);
			IActionResult										Result=Ok(ResponseValue);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------