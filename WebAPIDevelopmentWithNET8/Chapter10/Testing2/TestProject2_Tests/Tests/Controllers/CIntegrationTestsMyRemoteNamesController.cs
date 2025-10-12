using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.Extensions.DependencyInjection;
using Newtonsoft.Json;
using Testing2;
//--------------------------------------------------------------------------------------------------------------------------------
namespace TestProject2_Tests
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CIntegrationTestsMyRemoteNamesController : IClassFixture<CWebApplicationFactoryCustomService>
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									CONTENT_TYPE_TEXT_JSON="application/json";
		private const string									CONTENT_TYPE_CHARSERT_UTF_8="utf-8";
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										CHAR_SET_UTF_8="utf-8";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly CWebApplicationFactoryCustomService	MFactory;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CIntegrationTestsMyRemoteNamesController(CWebApplicationFactoryCustomService Factory)
		{
			MFactory=Factory;

			Console.WriteLine($"CONSTRUCTOR [{nameof(CIntegrationTestsMyRemoteNamesController)}] CALLED.");
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestGetName1()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MyRemoteNames/GetName1");

				// !!! METHOD kontroluje ci HTTP RESPONSE CODE je v intervale <200,299>.
				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_JSON,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				CMyRemoteName									Name=JsonConvert.DeserializeObject<CMyRemoteName>(Content);
				
				Assert.NotNull(Name);

				CMyRemoteName									ExpectedName=new CMyRemoteName("TIMMY","ANDERSON",12,ESex.E_MALE);

				Assert.Equal(ExpectedName.FirstName,Name.FirstName);
				Assert.Equal(ExpectedName.LastName,Name.LastName);
				Assert.Equal(ExpectedName.Age,Name.Age);
				Assert.Equal(ExpectedName.Sex,Name.Sex);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestGetName2()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MyRemoteNames/GetName2");

				// !!! METHOD kontroluje ci HTTP RESPONSE CODE je v intervale <200,299>.
				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_JSON,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				CMyRemoteName									Name=JsonConvert.DeserializeObject<CMyRemoteName>(Content);
				
				Assert.NotNull(Name);

				CMyRemoteName									ExpectedName=new CMyRemoteName("JENNY","THOMPSON",13,ESex.E_FEMALE);

				Assert.Equal(ExpectedName.FirstName,Name.FirstName);
				Assert.Equal(ExpectedName.LastName,Name.LastName);
				Assert.Equal(ExpectedName.Age,Name.Age);
				Assert.Equal(ExpectedName.Sex,Name.Sex);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------