using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
//----------------------------------------------------------------------------------------------------------------------
namespace PublishSubscribeSubscriber2
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			Builder.Services.AddControllers();

			Builder.Services.AddEndpointsApiExplorer();
			Builder.Services.AddSwaggerGen();

			WebApplication										Application=Builder.Build();

			if (Application.Environment.IsDevelopment()==true)
			{
				Application.UseSwagger();
				Application.UseSwaggerUI();
			}

			// !!!!! Pri pouziti DAPR je NUTNE tento MIDDLEWARE zakomentovat.
			//Application.UseHttpsRedirection();

			Application.UseAuthorization();

			Application.MapControllers();

			// !!!!! Prida sa podpora pre CLOUD EVENTS.
			Application.UseCloudEvents();

			// !!!!! Prida ENDPOINT pre PUBLISHER SUBSCRIBER SYSTEM.
			Application.MapSubscribeHandler();

			Application.Run();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------