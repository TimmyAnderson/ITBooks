using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMyHttpClientOperationResponse : CMyHttpClientOperation
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly EMyHttpClientHttpMethod				MMethod;
		private readonly string									MUrl;
		private readonly HttpStatusCode							MStatusCode;
		private readonly CMyHttpClientHeaders					MHeaders;
		private readonly CMyHttpClientContent					MContent;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMyHttpClientOperationResponse(string MessageID, EMyHttpClientHttpMethod Method, string Url, HttpStatusCode StatusCode, CMyHttpClientHeaders Headers, CMyHttpClientContent Content)
			: base(MessageID)
		{
			MMethod=Method;
			MUrl=Url;
			MStatusCode=StatusCode;
			MHeaders=Headers;
			MContent=Content;
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
		public HttpStatusCode									StatusCode
		{
			get
			{
				return(MStatusCode);
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
			SB.AppendLine($"STATUS\t[{((int)MStatusCode)} - {MStatusCode}].");
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