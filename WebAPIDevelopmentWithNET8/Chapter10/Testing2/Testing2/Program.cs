using System;
using System.Text;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Builder;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.IdentityModel.Tokens;
//----------------------------------------------------------------------------------------------------------------------
namespace Testing2
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureDbContext(DbContextOptionsBuilder OptionsBuilder, string ConnectionString)
		{
			OptionsBuilder.UseSqlite(ConnectionString);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void MyConfigureAuthenticationOptions(AuthenticationOptions Options)
		{
			// !!! AUTHENTICATION SCHEME sa nastavi na VALUE [Bearer].
			Options.DefaultAuthenticateScheme=JwtBearerDefaults.AuthenticationScheme;

			Options.DefaultChallengeScheme=JwtBearerDefaults.AuthenticationScheme;

			Options.DefaultScheme=JwtBearerDefaults.AuthenticationScheme;
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void MyConfigureJwtBearerOptions(WebApplicationBuilder Builder, JwtBearerOptions Options)
		{
			string												Secret=Builder.Configuration["JwtConfig:Secret"];
			string												Issuer=Builder.Configuration["JwtConfig:ValidIssuer"];
			string												Audience=Builder.Configuration["JwtConfig:ValidAudiences"];

			if (Secret==null || Issuer==null || Audience==null)
			{
				throw(new InvalidOperationException("JWT is not SET in the CONFIGURATION."));
			}

			Options.SaveToken=true;
			Options.RequireHttpsMetadata=false;

			Options.TokenValidationParameters=new TokenValidationParameters();

			Options.TokenValidationParameters.ValidateIssuer=true;
			Options.TokenValidationParameters.ValidateAudience=true;
			Options.TokenValidationParameters.ValidAudience=Audience;
			Options.TokenValidationParameters.ValidIssuer=Issuer;
			Options.TokenValidationParameters.IssuerSigningKey=new SymmetricSecurityKey(Encoding.UTF8.GetBytes(Secret));
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void MyConfigureAuthorizationOptions(AuthorizationOptions Options)
		{
			// Nie su tu ziadne POLICIES.
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

			string												ConnectionString=Builder.Configuration.GetConnectionString("MyConnection");

			// !!! DB CONTEXT sa prida do DEPENDENCY INJECTION CONTAINER.
			Builder.Services.AddDbContext<CDBContext>(P => ConfigureDbContext(P,ConnectionString));

			// !!! CUSTOM SERVICE sa prida do DEPENDENCY INJECTION CONTAINER.
			Builder.Services.AddScoped<IDBOperationsService,CDBOperationsService>();

			// !!! CUSTOM SERVICE sa prida do DEPENDENCY INJECTION CONTAINER.
			Builder.Services.AddSingleton<IMyRemoteNamesService,CMyRemoteNamesService>();

			// !!! Pridaju sa SERVICES pre AUTHENTICATION.
			AuthenticationBuilder								AuthenticationBuilder=Builder.Services.AddAuthentication(MyConfigureAuthenticationOptions);

			AuthenticationBuilder.AddJwtBearer(P => MyConfigureJwtBearerOptions(Builder,P));

			// !!! Pridaju sa SERVICES pre AUTHORIZATION.
			Builder.Services.AddAuthorization(MyConfigureAuthorizationOptions);

			WebApplication										Application=Builder.Build();

			if (Application.Environment.IsDevelopment()==true)
			{
				Application.UseSwagger();
				Application.UseSwaggerUI();
			}

			Application.UseHttpsRedirection();

			// !!! Do REQUEST PIPELINE sa pridaju AUTHORIZATION MIDDLEWARE COMPONENTS.
			Application.UseAuthorization();

			Application.MapControllers();

			// !!!!! NEPOUZIVA sa MENU, ale METHOD [void Run(string Url)], pretoze tento CODE vola aj TEST ENVIRONMENT. Ten sice bezal korektne aj pri pouziti MENU, ale cistejsie je MENU nepouzit.
			Application.Run();

			/*
			Application.StartAsync().Wait();

			CMenuProgram										Menu=new CMenuProgram();

			Menu.Execute();

			Application.StopAsync().Wait();
			*/
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------