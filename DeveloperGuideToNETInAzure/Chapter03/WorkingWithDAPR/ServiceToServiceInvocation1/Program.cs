//----------------------------------------------------------------------------------------------------------------------
using System.Net.Http;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Dapr.Client;
//----------------------------------------------------------------------------------------------------------------------
namespace ServiceToServiceInvocation1
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! VALUE [false] znamena, ze sa pouziva DOCKER a je potrebne vytvorit HTTP CLIENT pre DOCKER.
		public static readonly bool								RUN_LOCALLY=false;
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! VALUE urcuje APPLICATION ID s ktorym bol SERVICE 2 spusteny.
		private const string									SERVICE_2_APPLICATION_ID="SERVICE_2";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			Builder.Services.AddControllers();

			Builder.Services.AddEndpointsApiExplorer();
			Builder.Services.AddSwaggerGen();

			if (RUN_LOCALLY==true)
			{
				// !!! Prida sa standardny HTTP CLIENT.
				Builder.Services.AddHttpClient();
			}
			else
			{
				// !!! Vytvori sa DAPR HTTP CLIENT.
				HttpClient										HttpClient=DaprClient.CreateInvokeHttpClient(SERVICE_2_APPLICATION_ID);

				Builder.Services.AddSingleton(HttpClient);
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