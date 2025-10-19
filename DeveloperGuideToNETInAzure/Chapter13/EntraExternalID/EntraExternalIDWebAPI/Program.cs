using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Builder;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Identity.Web;
//--------------------------------------------------------------------------------------------------------------------------------
namespace EntraExternalIDWebAPI
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! VALUE sa da ziskat z MENU [App registrations], kde sa vyberie dana APP REGISTRATION a nasledne sa v MENU [Overview] vyberie TAB [Endpoints] a v nej VALUE VALUE [Authority URL]. Z URL je treba vyhodit TENENT ID, ktory je na konci URL.
		public const string										INSTANCE_ID="https://MyEntraExternalID.ciamlogin.com/";
//----------------------------------------------------------------------------------------------------------------------
		// !!! VALUE sa da ziskat z MENU [Overview -> Overview], kde sa vyberie VALUE [Tenant ID].
		public const string										TENANT_ID="ce01cc41-baa9-4e92-b2a0-10d891c18c5a";
//----------------------------------------------------------------------------------------------------------------------
		// !!! VALUE sa da ziskat z MENU [App registrations], kde sa vyberie dana APP REGISTRATION a nasledne sa v MENU [Overview] vyberie VALUE [Application (client) ID].
		public const string										CLIENT_ID="44cbea37-c6ee-4877-aa3b-8563198c769e";
//----------------------------------------------------------------------------------------------------------------------
		// !!! SCOPES s tymito NAMES musia byt vytvorene v APP REGISTRATION.
		public const string										SCOPE_READ="EntraExternalIDWebAPI.Read";
		public const string										SCOPE_READ_WRITE="EntraExternalIDWebAPI.ReadWrite";
//----------------------------------------------------------------------------------------------------------------------
		// !!! APP PERMISIONS s tymito NAMES musia byt vytvorene vi APP REGISTRATION.
		public const string										APP_PERMISION_READ="EntraExternalIDWebAPI.Read.All";
		public const string										APP_PERMISION_READ_WRITE="EntraExternalIDWebAPI.ReadWrite.All";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureDbContext(DbContextOptionsBuilder OptionsBuilder, string ConnectionString)
		{
			OptionsBuilder.UseSqlite(ConnectionString);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureJWTBearerOptions(JwtBearerOptions Options)
		{
			// EMPTY.
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureMicrosoftIdentityOptions(MicrosoftIdentityOptions Options)
		{
			Options.Instance=INSTANCE_ID;
			Options.TenantId=TENANT_ID;
			Options.ClientId=CLIENT_ID;
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

			string												ConnectionString=Builder.Configuration.GetConnectionString("MyConnection");

			// !!! DB CONTEXT sa prida do DEPENDENCY INJECTION CONTAINER.
			Builder.Services.AddDbContext<CDBContext>(P => ConfigureDbContext(P,ConnectionString));

			// !!! CUSTOM SERVICE sa prida do DEPENDENCY INJECTION CONTAINER.
			Builder.Services.AddScoped<IDBOperationsService,CDBOperationsService>();

			// !!! Pridaju sa SERVICES pre ENTRA EXTERNAL ID AUTHENTICATION.
			AuthenticationBuilder								AuthenticationBuilder=Builder.Services.AddAuthentication(JwtBearerDefaults.AuthenticationScheme);

			// !!!!! METHOD nacita CONFIGURATION z CONFIGURATION ELEMENT [AzureAd].
			/*
				!!! Tato METHOD vyzaduje nasledujucu CONFIGURATION vo FILE [appsettings.json].

				"AzureAd":
				{
					"Instance": "https://MyEntraExternalID.ciamlogin.com/",
					"TenantId": "ce01cc41-baa9-4e92-b2a0-10d891c18c5a",
					"ClientId": "44cbea37-c6ee-4877-aa3b-8563198c769e",

					"Scopes":
					{
						"Read": ["EntraExternalIDWebAPI.Read", "EntraExternalIDWebAPI.ReadWrite"],
						"Write": ["EntraExternalIDWebAPI.ReadWrite"]
					},
		
					"AppPermissions":
					{
						"Read": ["EntraExternalIDWebAPI.Read.All", "EntraExternalIDWebAPI.ReadWrite.All"],
						"Write": ["EntraExternalIDWebAPI.ReadWrite.All"]
					}
				}
			*/
			//AuthenticationBuilder.AddMicrosoftIdentityWebApi(Builder.Configuration);

			// !!!!! METHOD nacita CONFIGURATION z CONFIGURATION ELEMENT [AzureAd].
			AuthenticationBuilder.AddMicrosoftIdentityWebApi(ConfigureJWTBearerOptions,ConfigureMicrosoftIdentityOptions);

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