using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
//----------------------------------------------------------------------------------------------------------------------
namespace WebServiceWithControllers
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

			Builder.Services.AddTransient<INameService,CNameService>();

			// !!! Vola sa CUSTOM EXTENSION METHOD, ktora prida SERVICES.
			Builder.Services.AddMyServices();

			// !!! Zaregistruju sa KEYED SERVICES identifikovane pomocou KEYS.
			Builder.Services.AddKeyedTransient<IMyKeyedService,CMyKeyedService1>("MY_SERVICE_1");
			Builder.Services.AddKeyedTransient<IMyKeyedService,CMyKeyedService2>("MY_SERVICE_2");

			WebApplication										Application=Builder.Build();

			if (Application.Environment.IsDevelopment()==true)
			{
				Application.UseSwagger();
				Application.UseSwaggerUI();
			}

			Application.UseHttpsRedirection();

			Application.UseAuthorization();

			Application.MapControllers();

			Application.Run();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------