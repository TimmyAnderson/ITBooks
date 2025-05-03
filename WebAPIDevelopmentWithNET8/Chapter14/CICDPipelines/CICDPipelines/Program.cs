using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
//--------------------------------------------------------------------------------------------------------------------------------
namespace CICDPipelines
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

            WebApplication										Application=Builder.Build();

            if (Application.Environment.IsDevelopment()==true)
            {
                Application.UseSwagger();
                Application.UseSwaggerUI();
            }

            Application.UseHttpsRedirection();

            Application.UseAuthorization();

            Application.MapControllers();

			// !!!!! Pri nasadeni v DOCKER CONTAINER sa NESMIE pouzivat interaktivne MENU, kedze CONTAINER nedokaze vykonat ziadnu interakciu s USERS, ale sposobi generovanie obrovskeho mnozstva LOGS.
			Application.Run();

			/*
			Application.StartAsync().Wait();

			CMenuProgram										Menu=new CMenuProgram();

			Menu.Execute();

			Application.StopAsync().Wait();
			*/
        }
//--------------------------------------------------------------------------------------------------------------------------------
    }
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------