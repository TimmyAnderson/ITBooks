//----------------------------------------------------------------------------------------------------------------------
using Newtonsoft.Json;

namespace AzureAppConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CFeatureFlagsResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private bool											MMyFeatureEnabled1;
		private bool											MMyFeatureEnabled2;
		private bool											MMyAzureFeatureEnabled1;
		private bool											MMyAzureFeatureEnabled2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CFeatureFlagsResponse()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CFeatureFlagsResponse(bool MyFeatureEnabled1, bool MyFeatureEnabled2, bool MyAzureFeatureEnabled1, bool MyAzureFeatureEnabled2)
		{
			MMyFeatureEnabled1=MyFeatureEnabled1;
			MMyFeatureEnabled2=MyFeatureEnabled2;
			MMyAzureFeatureEnabled1=MyAzureFeatureEnabled1;
			MMyAzureFeatureEnabled2=MyAzureFeatureEnabled2;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[JsonProperty("myFeatureEnabled1")]
		public bool												MyFeatureEnabled1
		{
			get
			{
				return(MMyFeatureEnabled1);
			}
			set
			{
				MMyFeatureEnabled1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[JsonProperty("myFeatureEnabled2")]
		public bool												MyFeatureEnabled2
		{
			get
			{
				return(MMyFeatureEnabled2);
			}
			set
			{
				MMyFeatureEnabled2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[JsonProperty("myAzureFeatureEnabled1")]
		public bool												MyAzureFeatureEnabled1
		{
			get
			{
				return(MMyAzureFeatureEnabled1);
			}
			set
			{
				MMyAzureFeatureEnabled1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[JsonProperty("myAzureFeatureEnabled2")]
		public bool												MyAzureFeatureEnabled2
		{
			get
			{
				return(MMyAzureFeatureEnabled2);
			}
			set
			{
				MMyAzureFeatureEnabled2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------