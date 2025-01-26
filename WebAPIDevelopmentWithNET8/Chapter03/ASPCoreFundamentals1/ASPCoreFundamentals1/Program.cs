using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals1
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
        public static void Main(string[] args)
        {
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			// !!! Zaregistruje sa CUSTOM JSON CONFIGURATION FILE.
			Builder.Configuration.AddJsonFile("MyConfigurations.json",false,true);

            Builder.Services.AddControllers();
            
            Builder.Services.AddEndpointsApiExplorer();
            Builder.Services.AddSwaggerGen();

			// !!! METHOD umoznuje nastavit GLOBAL SETTINGS pre ROUTING SYSTEM.
			Builder.Services.AddRouting(P => P.LowercaseUrls=false);

			IConfiguration										ConfigurationSection=Builder.Configuration.GetSection("MySection2");

			// !!! CUSTOM CLASS [CConfigurationSectionComplex] sa vlozi do DEPENDENCY INJECTION, pricom sa bude citat z CONFIGURATION.
			Builder.Services.Configure<CConfigurationSectionComplex>(ConfigurationSection);

			IConfiguration										ConfigurationSectionMyNamedSection1=Builder.Configuration.GetSection("MyNamedSections:MyNamedSection1");
			IConfiguration										ConfigurationSectionMyNamedSection2=Builder.Configuration.GetSection("MyNamedSections:MyNamedSection2");

			// !!! CUSTOM CLASSES [CConfigurationSectionNamedComplex] sa vlozia do DEPENDENCY INJECTION, pricom sa budu citat z CONFIGURATION.
			Builder.Services.Configure<CConfigurationSectionNamedComplex>("MyNamedSection1",ConfigurationSectionMyNamedSection1);
			Builder.Services.Configure<CConfigurationSectionNamedComplex>("MyNamedSection2",ConfigurationSectionMyNamedSection2);

			// !!! Nastavenie ENVIRONMENT NAME v CODE.
			//Builder.Environment.EnvironmentName="MY ENVIRONMENT";

			WebApplication										Application=Builder.Build();

			// !!! ENVIRONMENT NAME je mozne v CODE zistit volanim METHOD [bool IsEnvironment(this IHostEnvironment HostEnvironment, string EnvironmentName)].
            if (Application.Environment.IsEnvironment("Development")==true)
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