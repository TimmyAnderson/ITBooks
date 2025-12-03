//--------------------------------------------------------------------------------------------------------------------------------
using System;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace WebAPICommonPracticesWeb
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMyTypedHttpClient
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly HttpClient						MClient;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		// !!! HTTP CLIENT naplna DEPENDENCY INJECTION.
		public CMyTypedHttpClient(HttpClient Client)
		{
			MClient=Client;

			// !!! Nastavi sa BASE ADDRESS.
			Client.BaseAddress=new Uri("https://localhost:7000/");
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static string Serialize<TRequest>(TRequest Value) where TRequest : class
		{
			JsonSerializerOptions						Options=new JsonSerializerOptions();

			Options.PropertyNamingPolicy=JsonNamingPolicy.CamelCase;
			Options.DictionaryKeyPolicy=JsonNamingPolicy.CamelCase;

			string										Request=JsonSerializer.Serialize<TRequest>(Value);

			return(Request);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static TResponse Deserialize<TResponse>(string Value) where TResponse : class
		{
			JsonSerializerOptions						Options=new JsonSerializerOptions();

			Options.PropertyNamingPolicy=JsonNamingPolicy.CamelCase;
			Options.DictionaryKeyPolicy=JsonNamingPolicy.CamelCase;

			TResponse									Response=JsonSerializer.Deserialize<TResponse>(Value,Options);

			return(Response);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public async Task<CMyGetResponseType> ExecuteGetNamedHttpClient(int Parameter)
		{
			string												URL=$"RemoteWebAPI/ExecuteGet?Parameter={Parameter}";

			using(HttpRequestMessage RequestMessage=new HttpRequestMessage(HttpMethod.Get,URL))
			{
				using(HttpResponseMessage ResponseMessage=await MClient.SendAsync(RequestMessage))
				{
					ResponseMessage.EnsureSuccessStatusCode();

					string										RawContent=await ResponseMessage.Content.ReadAsStringAsync();
					CMyGetResponseType							Content=Deserialize<CMyGetResponseType>(RawContent);

					return(Content);
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public async Task<CMyGetResponseType> ExecutePostNamedHttpClient(CMyPostRequestType Request)
		{
			string												URL="RemoteWebAPI/ExecutePost";

			using(HttpRequestMessage RequestMessage=new HttpRequestMessage(HttpMethod.Post,URL))
			{
				string											RawRequestContent=Serialize<CMyPostRequestType>(Request);
				StringContent									RequestContent=new StringContent(RawRequestContent,Encoding.UTF8,"application/json");

				RequestMessage.Content=RequestContent;

				using(HttpResponseMessage ResponseMessage=await MClient.SendAsync(RequestMessage))
				{
					ResponseMessage.EnsureSuccessStatusCode();

					string										RawResponseContent=await ResponseMessage.Content.ReadAsStringAsync();
					CMyGetResponseType							ResponseContent=Deserialize<CMyGetResponseType>(RawResponseContent);

					return(ResponseContent);
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------