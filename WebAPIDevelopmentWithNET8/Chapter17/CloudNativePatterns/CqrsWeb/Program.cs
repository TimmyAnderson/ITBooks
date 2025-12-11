using CqrsCore;
using CqrsInfrastructure;
using Microsoft.AspNetCore.Builder;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
//----------------------------------------------------------------------------------------------------------------------
namespace CqrsWeb
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureDbContext(DbContextOptionsBuilder OptionsBuilder, string ConnectionString)
		{
			OptionsBuilder.UseSqlite(ConnectionString);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureMediatR(MediatRServiceConfiguration OptionsBuilder)
		{
			// !!! Prida vsetky MEDIAT HANDLERS, ktore najde v danej ASSEMBLY.
			OptionsBuilder.RegisterServicesFromAssembly(typeof(CHandlerGetNames).Assembly);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			Builder.Services.AddControllers();

			Builder.Services.AddEndpointsApiExplorer();
			Builder.Services.AddSwaggerGen();

			// !!! Prida sa CUSTOM SERVICE.
			Builder.Services.AddScoped<INameRepository,CNameRepository>();

			Builder.Services.AddMediatR(ConfigureMediatR);

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