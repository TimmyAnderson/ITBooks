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
	// !!!!! Kedze CONTROLLER [CIntegrationTestsTestConnectionController2] testuje DATABASE OPERATIONS a tie vyzaduju zavedenie TEST DATABASE. Preto je nutne definovat CUSTOM CLASS [WebApplicationFactory<Program>], ktore vytvori TEST DATABASE.
	// !!!!! INTEGRATION TEST [CIntegrationTestsNamesController1] a INTEGRATION TEST [CIntegrationTestsNamesController2] pouzivaju SHARED DATABASE, a preto musia byt v tej istej TEST COLLECTION, aby TESTS bezali SEKVENCNE, a NIE PARALELNE.
	[Collection("SharedFixtureCollection")]
	public sealed class CIntegrationTestsNamesController2 : IClassFixture<CWebApplicationFactoryCustomDB>
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
		public CIntegrationTestsNamesController2(CWebApplicationFactoryCustomDB Factory)
		{
			MFactory=Factory;

			Console.WriteLine($"CONSTRUCTOR [{nameof(CIntegrationTestsNamesController2)}] CALLED.");
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		[Theory]
		[InlineData("Anderson")]
		[InlineData("Thompson")]
		public async Task TestDeleteNameOK(string LastName)
		{
			int													ID;

			using(IServiceScope Scope=MFactory.Services.CreateScope())
			{
				IServiceProvider								ServiceProvider=Scope.ServiceProvider;

				using(CDBContext DBContext=ServiceProvider.GetRequiredService<CDBContext>())
				{
					CEntityName									Name=DBContext.EntitiesNames.Where(P => P.LastName==LastName).FirstOrDefault();

					if (Name!=null)
					{
						ID=Name.ID;
					}
					else
					{
						return;
					}
				}
			}

			using(HttpClient Client=MFactory.CreateClient())
			{
				HttpResponseMessage								ResponseMessage=await Client.DeleteAsync($"Names/DeleteName?ID={ID}");

				// !!! METHOD kontroluje ci HTTP RESPONSE CODE je v intervale <200,299>.
				ResponseMessage.EnsureSuccessStatusCode();
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
		[Fact]
		public async Task TestDeleteNameError()
		{
			int													ID=0;

			using(HttpClient Client=MFactory.CreateClient())
			{
				HttpResponseMessage								ResponseMessage=await Client.DeleteAsync($"Names/DeleteName?ID={ID}");

				Assert.Equal(HttpStatusCode.NotFound,ResponseMessage.StatusCode);
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