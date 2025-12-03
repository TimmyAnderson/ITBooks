using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Caching.Distributed;
using Microsoft.Extensions.Caching.Memory;
//----------------------------------------------------------------------------------------------------------------------
namespace WebAPICommonPracticesWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class MyHttpClientFactoryController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IHttpClientFactory						MHttpClientFactory;
		private readonly CMyTypedHttpClient						MTypedHttpClient;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public MyHttpClientFactoryController(IHttpClientFactory HttpClientFactory, CMyTypedHttpClient TypedHttpClient)
		{
			MHttpClientFactory=HttpClientFactory;
			MTypedHttpClient=TypedHttpClient;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("ExecuteGet")]
		public async Task<IActionResult> ExecuteGet(int Parameter)
		{
			HttpClient											Client=MHttpClientFactory.CreateClient();
			string												URL=$"https://localhost:7000/RemoteWebAPI/ExecuteGet?Parameter={Parameter}";

			using(HttpRequestMessage RequestMessage=new HttpRequestMessage(HttpMethod.Get,URL))
			{
				using(HttpResponseMessage ResponseMessage=await Client.SendAsync(RequestMessage))
				{
					ResponseMessage.EnsureSuccessStatusCode();

					string										RawContent=await ResponseMessage.Content.ReadAsStringAsync();
					CMyGetResponseType							Content=Deserialize<CMyGetResponseType>(RawContent);

					IActionResult								Result=Ok(Content);

					return(Result);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("ExecutePost")]
		public async Task<IActionResult> ExecutePost(CMyPostRequestType Request)
		{
			HttpClient											Client=MHttpClientFactory.CreateClient();
			string												URL="https://localhost:7000/RemoteWebAPI/ExecutePost";

			using(HttpRequestMessage RequestMessage=new HttpRequestMessage(HttpMethod.Post,URL))
			{
				string											RawRequestContent=Serialize<CMyPostRequestType>(Request);
				StringContent									RequestContent=new StringContent(RawRequestContent,Encoding.UTF8,"application/json");

				RequestMessage.Content=RequestContent;

				using(HttpResponseMessage ResponseMessage=await Client.SendAsync(RequestMessage))
				{
					ResponseMessage.EnsureSuccessStatusCode();

					string										RawResponseContent=await ResponseMessage.Content.ReadAsStringAsync();
					CMyGetResponseType							ResponseContent=Deserialize<CMyGetResponseType>(RawResponseContent);

					IActionResult								Result=Ok(ResponseContent);

					return(Result);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("ExecuteGetNamedHttpClient")]
		public async Task<IActionResult> ExecuteGetNamedHttpClient(int Parameter)
		{
			// !!! Pouzije sa NAMED HTTP CLIENT, ktory ma nastavenu BASE ADDRESS.
			HttpClient											Client=MHttpClientFactory.CreateClient(Program.NAMED_HTTP_CLIENT_NAME);
			string												URL=$"RemoteWebAPI/ExecuteGet?Parameter={Parameter}";

			using(HttpRequestMessage RequestMessage=new HttpRequestMessage(HttpMethod.Get,URL))
			{
				using(HttpResponseMessage ResponseMessage=await Client.SendAsync(RequestMessage))
				{
					ResponseMessage.EnsureSuccessStatusCode();

					string										RawContent=await ResponseMessage.Content.ReadAsStringAsync();
					CMyGetResponseType							Content=Deserialize<CMyGetResponseType>(RawContent);

					IActionResult								Result=Ok(Content);

					return(Result);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("ExecutePostNamedHttpClient")]
		public async Task<IActionResult> ExecutePostNamedHttpClient(CMyPostRequestType Request)
		{
			// !!! Pouzije sa NAMED HTTP CLIENT, ktory ma nastavenu BASE ADDRESS.
			HttpClient											Client=MHttpClientFactory.CreateClient(Program.NAMED_HTTP_CLIENT_NAME);
			string												URL="RemoteWebAPI/ExecutePost";

			using(HttpRequestMessage RequestMessage=new HttpRequestMessage(HttpMethod.Post,URL))
			{
				string											RawRequestContent=Serialize<CMyPostRequestType>(Request);
				StringContent									RequestContent=new StringContent(RawRequestContent,Encoding.UTF8,"application/json");

				RequestMessage.Content=RequestContent;

				using(HttpResponseMessage ResponseMessage=await Client.SendAsync(RequestMessage))
				{
					ResponseMessage.EnsureSuccessStatusCode();

					string										RawResponseContent=await ResponseMessage.Content.ReadAsStringAsync();
					CMyGetResponseType							ResponseContent=Deserialize<CMyGetResponseType>(RawResponseContent);

					IActionResult								Result=Ok(ResponseContent);

					return(Result);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("ExecuteGetTypedHttpClient")]
		public async Task<IActionResult> ExecuteGetTypedHttpClient(int Parameter)
		{
			CMyGetResponseType									ResponseContent=await MTypedHttpClient.ExecuteGetNamedHttpClient(Parameter);
			IActionResult										Result=Ok(ResponseContent);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("ExecutePostTypedHttpClient")]
		public async Task<IActionResult> ExecutePostTypedHttpClient(CMyPostRequestType Request)
		{
			CMyGetResponseType									ResponseContent=await MTypedHttpClient.ExecutePostNamedHttpClient(Request);
			IActionResult										Result=Ok(ResponseContent);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------