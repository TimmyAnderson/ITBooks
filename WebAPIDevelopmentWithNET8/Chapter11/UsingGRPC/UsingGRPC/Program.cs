using UsingGRPC.Services;
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
			Application.MapGrpcService<GreeterService>();
			Application.MapGrpcService<NamesService>();

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