using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals2
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
        public static void Main(string[] args)
        {
            WebApplicationBuilder								Builder = WebApplication.CreateBuilder(args);

            Builder.Services.AddControllers();

            Builder.Services.AddEndpointsApiExplorer();
            Builder.Services.AddSwaggerGen();

			// !!! Odstrania sa DEFAULT LOGGING PROVIDERS.
			Builder.Logging.ClearProviders();

			Builder.Logging.AddConsole();
			Builder.Logging.AddDebug();

#pragma warning disable CA1416
			// !!! EVENT LOG LOGGING PROVIDER funguje IBA na WINDOWS.
			// !!! Na to aby zapisoval EVENT LOG LOGGING PROVIDER LOG MESSAGES s LOGGING LEVEL [Information], musi byt v CONFIGURATION FILE povoleny tento LOGGING LEVEL.
			//Builder.Logging.AddEventLog();
#pragma warning restore CA1416

			WebApplication										Application = Builder.Build();

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