using System;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCClientASPNET
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			Builder.Services.AddControllers();

			Builder.Services.AddEndpointsApiExplorer();
			Builder.Services.AddSwaggerGen();

			Builder.Logging.AddConsole();

			// !!! Do DEPENDENCY INJECTION CONTAINER sa vlozi GPRC CLIENT OBJECT.
			Builder.Services.AddGrpcClient<Names.NamesClient>(P => P.Address=new Uri("https://localhost:7000"));

			WebApplication										Application=Builder.Build();

			if (Application.Environment.IsDevelopment()==true)
			{
				Application.UseSwagger();
				Application.UseSwaggerUI();
			}

			Application.UseHttpsRedirection();

			Application.UseAuthorization();

			Application.MapControllers();

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