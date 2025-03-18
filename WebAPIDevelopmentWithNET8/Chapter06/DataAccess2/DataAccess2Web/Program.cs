using System.Text.Json.Serialization;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
//----------------------------------------------------------------------------------------------------------------------
namespace DataAccess2Web
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Povoli sa odosielanie cyklickych objektov.
		private static void ConfigureJSON(JsonOptions OptionsBuilder)
		{
			OptionsBuilder.JsonSerializerOptions.ReferenceHandler=ReferenceHandler.IgnoreCycles;
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureDbContext(DbContextOptionsBuilder OptionsBuilder, string ConnectionString)
		{
			OptionsBuilder.UseSqlite(ConnectionString);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			IMvcBuilder											MvcBuilder=Builder.Services.AddControllers();

			MvcBuilder.AddJsonOptions(ConfigureJSON);

			Builder.Services.AddEndpointsApiExplorer();
			Builder.Services.AddSwaggerGen();

			string												ConnectionString=Builder.Configuration.GetConnectionString("MyConnection");

			// !!! DB CONTEXT sa prida do DEPENDENCY INJECTION CONTAINER.
			Builder.Services.AddDbContext<CDBContext>(P => ConfigureDbContext(P,ConnectionString));

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
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------