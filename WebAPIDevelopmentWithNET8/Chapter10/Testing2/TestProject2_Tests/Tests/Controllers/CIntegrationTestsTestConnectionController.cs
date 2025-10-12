using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Testing;
using Newtonsoft.Json;
using Testing2;
//--------------------------------------------------------------------------------------------------------------------------------
namespace TestProject2_Tests
{
//--------------------------------------------------------------------------------------------------------------------------------
	// !!!!! Kedze CONTROLLER [TestConnectionController] nema ziadne DEPENDENCIES, CLASS [WebApplicationFactory<Program>] je mozne pouzit priamo, bez nutnosti definovat CUSTOM DEPENDENCIES.
	public sealed class CIntegrationTestsTestConnectionController : IClassFixture<WebApplicationFactory<Program>>
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									CONTENT_TYPE_TEXT_PLAIN="text/plain";
		private const string									CONTENT_TYPE_TEXT_JSON="application/json";
		private const string									CONTENT_TYPE_CHARSERT_UTF_8="utf-8";
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										CHAR_SET_UTF_8="utf-8";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [WebApplicationFactory<Program>] vytvori WEB HOST v ktorom spusti konfiguraciu ASP.NET PROGRAM, ako ju nakonfigurovala CLASS [Program].
		// !!! Kedze CLASS [WebApplicationFactory<Program>] je FIXTURE CLASS je SHARED medzi vsetkymi TESTS, ktore sa vykonaju v ramci tejto CLASS.
		private readonly WebApplicationFactory<Program>			MFactory;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CIntegrationTestsTestConnectionController(WebApplicationFactory<Program> Factory)
		{
			MFactory=Factory;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static MediaTypeHeaderValue CreateMediaTypeHeaderValue(string MediaType, string CharSet)
		{
			MediaTypeHeaderValue								MediaTypeObject=new MediaTypeHeaderValue(MediaType);

			if (CharSet!=null)
			{
				MediaTypeObject.CharSet=CharSet;
			}

			return(MediaTypeObject);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestGet()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				HttpResponseMessage								ResponseMessage=await Client.GetAsync("TestConnection");

				// !!! METHOD kontroluje ci HTTP RESPONSE CODE je v intervale <200,299>.
				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_PLAIN,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				Assert.Equal("Hello WORLD !",Content);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Fact]
		public async Task TestPost()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				Encoding										Encoding=Encoding.UTF8;
				string											ContentText=JsonConvert.SerializeObject("Timmy");
				StringContent									InputContent=new StringContent(ContentText,Encoding);
				
				InputContent.Headers.ContentType=CreateMediaTypeHeaderValue(CONTENT_TYPE_TEXT_JSON,CHAR_SET_UTF_8);

				HttpResponseMessage								ResponseMessage=await Client.PostAsync("TestConnection",InputContent);

				// !!! METHOD kontroluje ci HTTP RESPONSE CODE je v intervale <200,299>.
				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_PLAIN,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				Assert.Equal("Hello [Timmy] !",Content);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------