//----------------------------------------------------------------------------------------------------------------------
using System.Net.Http;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Dapr.Client;
using System;
//----------------------------------------------------------------------------------------------------------------------
namespace AzureServiceToServiceInvocation1
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! VALUE [E_LOCAL_WITH_DAPR] znamena, ze sa pouziva DOCKER a je potrebne vytvorit HTTP CLIENT pre DOCKER.
		public static readonly ERunConfiguration				RUN_CONFIGURATION=ERunConfiguration.E_AZURE_WITH_DAPR;
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! VALUE urcuje APPLICATION ID s ktorym bol SERVICE 2 spusteny.
		private const string									SERVICE_2_APPLICATION_ID_LOCAL="SERVICE_2";
		private const string									SERVICE_2_APPLICATION_ID_AZURE="my-service-2";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			Builder.Services.AddControllers();

			Builder.Services.AddEndpointsApiExplorer();
			Builder.Services.AddSwaggerGen();

			if (RUN_CONFIGURATION==ERunConfiguration.E_LOCAL_NO_DAPR)
			{
				// !!! Prida sa standardny HTTP CLIENT.
				Builder.Services.AddHttpClient();
			}
			else if (RUN_CONFIGURATION==ERunConfiguration.E_LOCAL_WITH_DAPR)
			{
				// !!! Vytvori sa DAPR HTTP CLIENT.
				HttpClient										HttpClient=DaprClient.CreateInvokeHttpClient(SERVICE_2_APPLICATION_ID_LOCAL);

				Builder.Services.AddSingleton(HttpClient);
			}
			else if (RUN_CONFIGURATION==ERunConfiguration.E_AZURE_WITH_DAPR)
			{
				// !!! Vytvori sa DAPR HTTP CLIENT.
				HttpClient										HttpClient=DaprClient.CreateInvokeHttpClient(SERVICE_2_APPLICATION_ID_AZURE);

				Builder.Services.AddSingleton(HttpClient);
			}
			else
			{
				throw(new InvalidOperationException($"UNSUPPORTED VALUE [{RUN_CONFIGURATION}]."));
			}

			WebApplication										Application=Builder.Build();

			if(Application.Environment.IsDevelopment()==true)
			{
				Application.UseSwagger();
				Application.UseSwaggerUI();
			}

			// !!!!! Pri pouziti DAPR je NUTNE tento MIDDLEWARE zakomentovat.
			//app.UseHttpsRedirection();

			Application.UseAuthorization();

			Application.MapControllers();

			Application.Run();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------