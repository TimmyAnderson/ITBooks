using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//--------------------------------------------------------------------------------------------------------------------------------
namespace MySharedLibrary
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMyHttpClientOperationRequest : CMyHttpClientOperation
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly EMyHttpClientHttpMethod				MMethod;
		private readonly string									MUrl;
		private readonly CMyHttpClientHeaders					MHeaders;
		private readonly CMyHttpClientContent					MContent;
		private readonly TimeSpan								MTimeout;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientOperationRequest(string MessageID, EMyHttpClientHttpMethod Method, string Url, CMyHttpClientHeaders Headers, CMyHttpClientContent Content, TimeSpan Timeout)
			: base(MessageID)
		{
			MMethod=Method;
			MUrl=Url;
			MHeaders=Headers;
			MContent=Content;
			MTimeout=Timeout;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public EMyHttpClientHttpMethod							Method
		{
			get
			{
				return(MMethod);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public string											Url
		{
			get
			{
				return(MUrl);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientHeaders								Headers
		{
			get
			{
				return(MHeaders);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientContent								Content
		{
			get
			{
				return(MContent);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public TimeSpan											Timeout
		{
			get
			{
				return(MTimeout);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override string GetMessageAsText()
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendLine($"ID\t[{MessageID}].");
			SB.AppendLine();
			SB.AppendLine($"METHOD\t[{MMethod.EXT_ToString()}].");
			SB.AppendLine();
			SB.AppendLine($"URL\t[{MUrl}].");
			SB.AppendLine();
			SB.AppendLine($"CONTENT TYPE [{MContent?.ContentType?.ConvertToString()}].");
			SB.AppendLine();
			SB.AppendLine($"BODY LENGTH [{MContent?.Content?.Length}].");

			string												Body=MContent?.ConvertToString();

			SB.AppendLine();
			SB.AppendLine($"BODY:\n{Body}");

			string												Text=SB.ToString();

			return(Text);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------