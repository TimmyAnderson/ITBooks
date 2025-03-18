using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using UsingGRPCNames.Services;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPC
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			// !!! METHOD vklada gRPC FRAMEWORK SERVICE do DEPENDENCY INJECTION CONTAINER.
			Builder.Services.AddGrpc();

			WebApplication										Application=Builder.Build();

			// !!! Pridaju sa gRPC SERVICES do PROGRAMU.
			Application.MapGrpcService<NamesService>();
			Application.MapGrpcService<ScalarTypesService>();
			Application.MapGrpcService<ExtensionTypesService>();
			Application.MapGrpcService<EnumTypesService>();
			Application.MapGrpcService<NullableTypesService>();
			Application.MapGrpcService<RepeatedTypesService>();
			Application.MapGrpcService<MapTypesService>();
			Application.MapGrpcService<ServicesUnaryService>();
			Application.MapGrpcService<ParallelCallsService>();
			Application.MapGrpcService<ServicesServerStreamingService>();
			Application.MapGrpcService<ServicesClientStreamingService>();
			Application.MapGrpcService<ServicesBidirectionalStreamingService>();
			Application.MapGrpcService<ReservedFieldsService>();

			// !!!!! Tento CODE zabezpecuje zobrazenie ERROR MESSAGE, ak k SERVER pokusi pripojit CLIENT, ktory nepodporuje gRPC, ako napriklad WEB BROSER.
			Application.MapGet("/", () => "COMMUNICATION with gRPC ENDPOINTS must be MADE through a gRPC CLIENT.");

			Application.StartAsync().Wait();

			CMenuProgram										Menu=new CMenuProgram();

			Menu.Execute();

			Application.StopAsync().Wait();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------