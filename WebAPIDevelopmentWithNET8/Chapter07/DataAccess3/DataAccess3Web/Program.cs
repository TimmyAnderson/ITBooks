using Microsoft.AspNetCore.Builder;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
//--------------------------------------------------------------------------------------------------------------------------------
namespace DataAccess3Web
{
//--------------------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureDbContext1(DbContextOptionsBuilder OptionsBuilder, string ConnectionString)
		{
			OptionsBuilder.UseSqlite(ConnectionString);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureDbContext2(DbContextOptionsBuilder OptionsBuilder, string ConnectionString)
		{
			OptionsBuilder.UseSqlite(ConnectionString);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
        public static void Main(string[] args)
        {
            WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

            Builder.Services.AddControllers();
            
            Builder.Services.AddEndpointsApiExplorer();

            Builder.Services.AddSwaggerGen();

			string												ConnectionString1=Builder.Configuration.GetConnectionString("MyConnection1");

			// !!! DB CONTEXT sa prida do DEPENDENCY INJECTION CONTAINER.
			Builder.Services.AddDbContext<CDBContext1>(P => ConfigureDbContext1(P,ConnectionString1));

			string												ConnectionString2=Builder.Configuration.GetConnectionString("MyConnection2");

			// !!! DB CONTEXT POOL sa prida do DEPENDENCY INJECTION CONTAINER.
			Builder.Services.AddDbContextPool<CDBContext2>(P => ConfigureDbContext2(P,ConnectionString2));

            WebApplication										Application = Builder.Build();
            
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