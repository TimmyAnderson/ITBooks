using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
//--------------------------------------------------------------------------------------------------------------------------------
namespace MySharedLibrary
{
//--------------------------------------------------------------------------------------------------------------------------------
	public static class CMyHttpClient
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private static void WriteRequestAndResponseToFiles(string Name, string DirectoryName, string RequestContent, string ResponseContent)
		{
			if (DirectoryName!=null)
			{
				string											RequestFile=$"REQUEST_{Name}.txt";
				string											ResponseFile=$"RESPONSE_{Name}.txt";
				string											RequestPath=Path.Combine(DirectoryName,RequestFile);
				string											ResponsePath=Path.Combine(DirectoryName,ResponseFile);

				File.WriteAllText(RequestPath,RequestContent);
				File.WriteAllText(ResponsePath,ResponseContent);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static CMyHttpClientOperationResponse InternalExecuteMessage(CMyHttpClientOperationRequest Request, HttpClient Client, bool WriteToCosole)
		{
			Client.Timeout=Request.Timeout;

			using(HttpRequestMessage RequestMessage=new HttpRequestMessage(Request.Method.EXT_ConvertHttpMethod(),Request.Url))
			{
				if (Request.Headers!=null)
				{
					foreach(CMyHttpClientHeader Header in Request.Headers.Headers)
					{
						RequestMessage.Headers.Add(Header.Key,Header.Values);
					}
				}

				RequestMessage.Content=Request?.Content?.ConvertToHttpContent();

				using(HttpResponseMessage ResponseMessage=Client.SendAsync(RequestMessage).Result)
				{
					string										ResponseMessageID=Request.MessageID;
					EMyHttpClientHttpMethod						ResponseMethod=Request.Method;
					string										ResponseUrl=Request.Url;
					HttpStatusCode								ResponseStatusCode=ResponseMessage.StatusCode;
					CMyHttpClientHeaders						ResponseHeaders=new CMyHttpClientHeaders(ResponseMessage.Headers);
					CMyHttpClientContent						ResponseContent=new CMyHttpClientContent(ResponseMessage?.Content);
					CMyHttpClientOperationResponse				Response=new CMyHttpClientOperationResponse(ResponseMessageID,ResponseMethod,ResponseUrl,ResponseStatusCode,ResponseHeaders,ResponseContent);
					string										ResponseText=Response.GetMessageAsText();

					if (WriteToCosole==true)
					{
						Console.WriteLine(ResponseText);
					}

					return(Response);
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public static CMyHttpClientOperationResponse ExecuteMessage(CMyHttpClientOperationRequest Request, bool WriteToCosole=true)
		{
			using(HttpClient Client=new HttpClient())
			{
				CMyHttpClientOperationResponse					Response=InternalExecuteMessage(Request,Client,WriteToCosole);

				return(Response);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public static CMyHttpClientOperationResponse ExecuteMessage(CMyHttpClientOperationRequest Request, HttpClientHandler Handler, bool WriteToCosole=true)
		{
			using(HttpClient Client=new HttpClient(Handler))
			{
				CMyHttpClientOperationResponse					Response=InternalExecuteMessage(Request,Client,WriteToCosole);

				return(Response);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------