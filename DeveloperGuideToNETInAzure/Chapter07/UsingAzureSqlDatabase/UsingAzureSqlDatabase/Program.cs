using System;
using Microsoft.AspNetCore.Builder;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingAzureSqlDatabase
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

			Builder.Services.AddDbContext<CDBContext>(P => P.UseSqlServer(Builder.Configuration.GetConnectionString("MyConnection")));

			WebApplication										Application=Builder.Build();

			// !!!!! Aplikuju sa MIGRATIONS.
			using (IServiceScope Scope=Application.Services.CreateScope())
		    {
		        ILogger<Program>								Logger=Scope.ServiceProvider.GetRequiredService<ILogger<Program>>();

				try
				{
					Logger.LogInformation("MIGRATION STARTED.");

					using(CDBContext Context=Scope.ServiceProvider.GetRequiredService<CDBContext>())
					{
						Context.Database.Migrate();
					}

					Logger.LogInformation("MIGRATION FINISHED.");
				}
				catch(Exception E)
				{
					Logger.LogError(E,"MIGRATION FAILED.");
				}
			}

			
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