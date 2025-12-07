using System;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
//--------------------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
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
			Client.BaseAddress=new Uri("https://localhost:8000/");
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
		public async Task<string> ExecuteMyService1DoSomething1()
		{
			string												URL=$"MyService1/DoSomething1";

			using(HttpRequestMessage RequestMessage=new HttpRequestMessage(HttpMethod.Get,URL))
			{
				using(HttpResponseMessage ResponseMessage=await MClient.SendAsync(RequestMessage))
				{
					ResponseMessage.EnsureSuccessStatusCode();

					string										Content=await ResponseMessage.Content.ReadAsStringAsync();

					return(Content);
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public async Task<string> ExecuteMyService2DoSomething2()
		{
			string												URL=$"MyService2/DoSomething2";

			using(HttpRequestMessage RequestMessage=new HttpRequestMessage(HttpMethod.Get,URL))
			{
				using(HttpResponseMessage ResponseMessage=await MClient.SendAsync(RequestMessage))
				{
					ResponseMessage.EnsureSuccessStatusCode();

					string										Content=await ResponseMessage.Content.ReadAsStringAsync();

					return(Content);
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------