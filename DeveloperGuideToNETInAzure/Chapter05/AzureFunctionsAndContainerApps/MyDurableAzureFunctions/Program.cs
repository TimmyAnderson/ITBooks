using Microsoft.Azure.Functions.Worker;
using Microsoft.Azure.Functions.Worker.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
//----------------------------------------------------------------------------------------------------------------------
internal class Program
{
//----------------------------------------------------------------------------------------------------------------------
	private static void Main(string[] args)
	{
		FunctionsApplicationBuilder								Builder=FunctionsApplication.CreateBuilder(args);

		Builder.ConfigureFunctionsWebApplication();

		Builder.Services.AddApplicationInsightsTelemetryWorkerService();
		Builder.Services.ConfigureFunctionsApplicationInsights();

		IHost													Host=Builder.Build();

		Host.Run();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------