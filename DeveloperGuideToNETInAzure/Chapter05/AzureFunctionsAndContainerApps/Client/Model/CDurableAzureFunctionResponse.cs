using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CDurableAzureFunctionResponse
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private string											MID;
		private string											MStatusQueryGetUri;
		private string											MSendEventPostUri;
		private string											MTerminatePostUri;
		private string											MRewindPostUri;
		private string											MPurgeHistoryDeleteUri;
		private string											MRestartPostUri;
		private string											MSuspendPostUri;
		private string											MResumePostUri;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CDurableAzureFunctionResponse()
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public CDurableAzureFunctionResponse(string ID, string StatusQueryGetUri, string SendEventPostUri, string TerminatePostUri, string RewindPostUri, string PurgeHistoryDeleteUri, string RestartPostUri, string SuspendPostUri, string ResumePostUri)
		{
			MID=ID;
			MStatusQueryGetUri=StatusQueryGetUri;
			MSendEventPostUri=SendEventPostUri;
			MTerminatePostUri=TerminatePostUri;
			MRewindPostUri=RewindPostUri;
			MPurgeHistoryDeleteUri=PurgeHistoryDeleteUri;
			MRestartPostUri=RestartPostUri;
			MSuspendPostUri=SuspendPostUri;
			MResumePostUri=ResumePostUri;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		[JsonProperty("Id")]
		public string											ID
		{
			get
			{
				return(MID);
			}
			set
			{
				MID=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[JsonProperty("StatusQueryGetUri")]
		public string											StatusQueryGetUri
		{
			get
			{
				return(MStatusQueryGetUri);
			}
			set
			{
				MStatusQueryGetUri=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[JsonProperty("SendEventPostUri")]
		public string											SendEventPostUri
		{
			get
			{
				return(MSendEventPostUri);
			}
			set
			{
				MSendEventPostUri=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[JsonProperty("TerminatePostUri")]
		public string											TerminatePostUri
		{
			get
			{
				return(MTerminatePostUri);
			}
			set
			{
				MTerminatePostUri=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[JsonProperty("RewindPostUri")]
		public string											RewindPostUri
		{
			get
			{
				return(MRewindPostUri);
			}
			set
			{
				MRewindPostUri=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[JsonProperty("PurgeHistoryDeleteUri")]
		public string											PurgeHistoryDeleteUri
		{
			get
			{
				return(MPurgeHistoryDeleteUri);
			}
			set
			{
				MPurgeHistoryDeleteUri=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[JsonProperty("RestartPostUri")]
		public string											RestartPostUri
		{
			get
			{
				return(MRestartPostUri);
			}
			set
			{
				MRestartPostUri=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[JsonProperty("SuspendPostUri")]
		public string											SuspendPostUri
		{
			get
			{
				return(MSuspendPostUri);
			}
			set
			{
				MSuspendPostUri=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[JsonProperty("ResumePostUri")]
		public string											ResumePostUri
		{
			get
			{
				return(MResumePostUri);
			}
			set
			{
				MResumePostUri=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------