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
	public sealed class CIntegrationTestsMySecureController : IClassFixture<CWebApplicationFactorySecureAPI>
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									CONTENT_TYPE_TEXT_JSON="application/json";
		private const string									CONTENT_TYPE_CHARSERT_UTF_8="utf-8";
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										CHAR_SET_UTF_8="utf-8";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly CWebApplicationFactorySecureAPI		MFactory;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CIntegrationTestsMySecureController(CWebApplicationFactorySecureAPI Factory)
		{
			MFactory=Factory;

			Console.WriteLine($"CONSTRUCTOR [{nameof(CIntegrationTestsMySecureController)}] CALLED.");
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestAnonymous()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MySecure/Anonymous");

				// !!! METHOD kontroluje ci HTTP RESPONSE CODE je v intervale <200,299>.
				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_JSON,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				CSecureName										Name=JsonConvert.DeserializeObject<CSecureName>(Content);
				
				Assert.NotNull(Name);

				CSecureName										ExpectedName=new CSecureName("Connor","Phills",15,ESex.E_MALE);

				Assert.Equal(ExpectedName.FirstName,Name.FirstName);
				Assert.Equal(ExpectedName.LastName,Name.LastName);
				Assert.Equal(ExpectedName.Age,Name.Age);
				Assert.Equal(ExpectedName.Sex,Name.Sex);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestForRole1OKGeneratedToken()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				string											UserName="timmy";
				string[]										Roles=new string[]{CRoles.ROLE_1};

				// !!! Vygeneruje sa ACCESS TOKEN tym istym ALGORITHM, aky je pouzity na SERVERI.
				string											AccessToken=MFactory.GenerateToken(UserName,Roles);

				// !!! TOKEN sa vlozi do AUTHORIZATION HEADER.
				Client.DefaultRequestHeaders.Authorization=new AuthenticationHeaderValue("Bearer",AccessToken);

				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MySecure/ForRole1");

				// !!! METHOD kontroluje ci HTTP RESPONSE CODE je v intervale <200,299>.
				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_JSON,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				CSecureName										Name=JsonConvert.DeserializeObject<CSecureName>(Content);
				
				Assert.NotNull(Name);

				CSecureName										ExpectedName=new CSecureName("Timmy","Anderson",12,ESex.E_MALE);

				Assert.Equal(ExpectedName.FirstName,Name.FirstName);
				Assert.Equal(ExpectedName.LastName,Name.LastName);
				Assert.Equal(ExpectedName.Age,Name.Age);
				Assert.Equal(ExpectedName.Sex,Name.Sex);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestForRole1Error401()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MySecure/ForRole1");

				Assert.True(ResponseMessage.StatusCode==HttpStatusCode.Unauthorized);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestForRole2OKGeneratedToken()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				string											UserName="timmy";
				string[]										Roles=new string[]{CRoles.ROLE_2};

				// !!! Vygeneruje sa ACCESS TOKEN tym istym ALGORITHM, aky je pouzity na SERVERI.
				string											AccessToken=MFactory.GenerateToken(UserName,Roles);

				// !!! TOKEN sa vlozi do AUTHORIZATION HEADER.
				Client.DefaultRequestHeaders.Authorization=new AuthenticationHeaderValue("Bearer",AccessToken);

				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MySecure/ForRole2");

				// !!! METHOD kontroluje ci HTTP RESPONSE CODE je v intervale <200,299>.
				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_JSON,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				CSecureName										Name=JsonConvert.DeserializeObject<CSecureName>(Content);
				
				Assert.NotNull(Name);

				CSecureName										ExpectedName=new CSecureName("Jenny","Thompson",13,ESex.E_FEMALE);

				Assert.Equal(ExpectedName.FirstName,Name.FirstName);
				Assert.Equal(ExpectedName.LastName,Name.LastName);
				Assert.Equal(ExpectedName.Age,Name.Age);
				Assert.Equal(ExpectedName.Sex,Name.Sex);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestForRole2Error401()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MySecure/ForRole2");

				Assert.True(ResponseMessage.StatusCode==HttpStatusCode.Unauthorized);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestForRole3OKGeneratedToken()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				string											UserName="timmy";
				string[]										Roles=new string[]{CRoles.ROLE_3};

				// !!! Vygeneruje sa ACCESS TOKEN tym istym ALGORITHM, aky je pouzity na SERVERI.
				string											AccessToken=MFactory.GenerateToken(UserName,Roles);

				// !!! TOKEN sa vlozi do AUTHORIZATION HEADER.
				Client.DefaultRequestHeaders.Authorization=new AuthenticationHeaderValue("Bearer",AccessToken);

				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MySecure/ForRole3");

				// !!! METHOD kontroluje ci HTTP RESPONSE CODE je v intervale <200,299>.
				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_JSON,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				CSecureName										Name=JsonConvert.DeserializeObject<CSecureName>(Content);
				
				Assert.NotNull(Name);

				CSecureName										ExpectedName=new CSecureName("Josh","Hurt",12,ESex.E_MALE);

				Assert.Equal(ExpectedName.FirstName,Name.FirstName);
				Assert.Equal(ExpectedName.LastName,Name.LastName);
				Assert.Equal(ExpectedName.Age,Name.Age);
				Assert.Equal(ExpectedName.Sex,Name.Sex);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestForRole3Error401()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				HttpResponseMessage								ResponseMessage=await Client.GetAsync("MySecure/ForRole3");

				Assert.True(ResponseMessage.StatusCode==HttpStatusCode.Unauthorized);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------