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
	// !!!!! Kedze CONTROLLER [CIntegrationTestsTestConnectionController] testuje DATABASE OPERATIONS a tie vyzaduju zavedenie TEST DATABASE. Preto je nutne definovat CUSTOM CLASS [WebApplicationFactory<Program>], ktore vytvori TEST DATABASE.
	// !!!!! INTEGRATION TEST [CIntegrationTestsNamesController1] a INTEGRATION TEST [CIntegrationTestsNamesController2] pouzivaju SHARED DATABASE, a preto musia byt v tej istej TEST COLLECTION, aby TESTS bezali SEKVENCNE, a NIE PARALELNE.
	[Collection("SharedFixtureCollection")]
	public sealed class CIntegrationTestsNamesController1 : IClassFixture<CWebApplicationFactoryCustomDB>
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									CONTENT_TYPE_TEXT_JSON="application/json";
		private const string									CONTENT_TYPE_CHARSERT_UTF_8="utf-8";
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										CHAR_SET_UTF_8="utf-8";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [CWebApplicationFactoryCustomDB] vytvori WEB HOST, ktoru bude mat CUSTOM CONFIGURATION obsahujucu vytvorenie TEST DATABASE.
		// !!! Kedze CLASS [CWebApplicationFactoryCustomDB] je FIXTURE CLASS je SHARED medzi vsetkymi TESTS, ktore sa vykonaju v ramci tejto CLASS.
		private readonly CWebApplicationFactoryCustomDB			MFactory;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CIntegrationTestsNamesController1(CWebApplicationFactoryCustomDB Factory)
		{
			MFactory=Factory;

			Console.WriteLine($"CONSTRUCTOR [{nameof(CIntegrationTestsNamesController1)}] CALLED.");
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
		public async Task TestGetNames()
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				HttpResponseMessage								ResponseMessage=await Client.GetAsync("Names/GetNames");

				// !!! METHOD kontroluje ci HTTP RESPONSE CODE je v intervale <200,299>.
				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_JSON,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				CEntityName[]									Names=JsonConvert.DeserializeObject<CEntityName[]>(Content);
				
				Assert.NotNull(Names);

				CEntityName[]									ExpectedNames=new CEntityName[]{new CEntityName("Timmy","Anderson",12,ESex.E_MALE),new CEntityName("Jenny","Thompson",13,ESex.E_FEMALE),new CEntityName("Josh","Hurt",12,ESex.E_MALE),new CEntityName("Lucas","Jones",13,ESex.E_MALE)};

				Assert.Equal(ExpectedNames.Length,Names.Length);

				for(int Index=0;Index<ExpectedNames.Length;Index++)
				{
					CEntityName									Name=Names[Index];
					CEntityName									ExpectedName=ExpectedNames[Index];

					Assert.NotNull(Name);

					Assert.True(Name.ID!=0);
					Assert.Equal(ExpectedName.FirstName,Name.FirstName);
					Assert.Equal(ExpectedName.LastName,Name.LastName);
					Assert.Equal(ExpectedName.Age,Name.Age);
					Assert.Equal(ExpectedName.Sex,Name.Sex);
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		[Theory]
		[InlineData("Joshua","Foley",13,ESex.E_MALE)]
		[InlineData("Connor","Phills",15,ESex.E_MALE)]
		public async Task TestInsertName(string FirstName, string LastName, int Age, ESex Sex)
		{
			using(HttpClient Client=MFactory.CreateClient())
			{
				CEntityName										InputName=new CEntityName(FirstName,LastName,Age,Sex);

				Encoding										Encoding=Encoding.UTF8;
				string											ContentText=JsonConvert.SerializeObject(InputName);
				StringContent									InputContent=new StringContent(ContentText,Encoding);
				
				InputContent.Headers.ContentType=CreateMediaTypeHeaderValue(CONTENT_TYPE_TEXT_JSON,CHAR_SET_UTF_8);

				HttpResponseMessage								ResponseMessage=await Client.PostAsync("Names/InsertName",InputContent);

				// !!! METHOD kontroluje ci HTTP RESPONSE CODE je v intervale <200,299>.
				ResponseMessage.EnsureSuccessStatusCode();

				MediaTypeHeaderValue							ContentType=ResponseMessage?.Content?.Headers?.ContentType;

				Assert.NotNull(ContentType);

				Assert.Equal(CONTENT_TYPE_TEXT_JSON,ContentType.MediaType);
				Assert.Equal(CONTENT_TYPE_CHARSERT_UTF_8,ContentType.CharSet);

				string											Content=await ResponseMessage?.Content?.ReadAsStringAsync();

				Assert.NotNull(Content);

				CEntityName										Name=JsonConvert.DeserializeObject<CEntityName>(Content);
				
				Assert.NotNull(Name);

				Assert.True(Name.ID!=0);
				Assert.Equal(InputName.FirstName,Name.FirstName);
				Assert.Equal(InputName.LastName,Name.LastName);
				Assert.Equal(InputName.Age,Name.Age);
				Assert.Equal(InputName.Sex,Name.Sex);
			}

			// !!! Vycisti sa TEST DATABASE.
			using(IServiceScope Scope=MFactory.Services.CreateScope())
			{
				IServiceProvider								ServiceProvider=Scope.ServiceProvider;

				using(CDBContext DBContext=ServiceProvider.GetRequiredService<CDBContext>())
				{
					CDBContextHelpers.CleanupDatabase(DBContext);

					int											NamesCount=DBContext.EntitiesNames.Count();

					Console.WriteLine($"NUMBER of NAMES is [{NamesCount}].");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------