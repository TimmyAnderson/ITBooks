using Microsoft.Extensions.DependencyInjection;
//----------------------------------------------------------------------------------------------------------------------
namespace WebServiceWithControllers
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CDependencyInjectionExtensions
	{
//----------------------------------------------------------------------------------------------------------------------
		public static void AddMyServices(this IServiceCollection Services)
		{
			Services.AddTransient<IServiceMyTransient,CServiceMyTransient>();
			Services.AddScoped<IServiceMyScoped,CServiceMyScoped>();
			Services.AddSingleton<IServiceMySingleton,CServiceMySingleton>();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------