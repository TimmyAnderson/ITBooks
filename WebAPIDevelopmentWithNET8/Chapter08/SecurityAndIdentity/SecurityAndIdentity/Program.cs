using System;
using System.Text;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.IdentityModel.Tokens;
using Microsoft.OpenApi.Models;
using Swashbuckle.AspNetCore.SwaggerGen;
//--------------------------------------------------------------------------------------------------------------------------------
namespace SecurityAndIdentity
{
//--------------------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										MY_POLICY_ADMINISTRATORS_OR_VIPS="MyPolicyAdministratorsOrVIPs";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static bool CreateDatabase(WebApplication Application)
		{
			using(IServiceScope ServiceScope=Application.Services.CreateScope())
			{
				using(CIdentityContextDB Context=ServiceScope.ServiceProvider.GetRequiredService<CIdentityContextDB>())
				{
					try
					{
						if (Context.Database.CanConnect()==false)
						{
							Context.Database.EnsureCreated();
						}

					    RoleManager<CIdentityRole>				RoleManager=ServiceScope.ServiceProvider.GetRequiredService<RoleManager<CIdentityRole>>();
						string[]								RoleNames=new string[]{CIdentityRoles.ADMINISTRATORS,CIdentityRoles.VIPS,CIdentityRoles.USERS};

						foreach(string RoleName in RoleNames)
						{
							bool								RoleExists=RoleManager.RoleExistsAsync(RoleName).Result;

							if (RoleExists==false)
							{
								RoleManager.CreateAsync(new CIdentityRole(RoleName)).Wait();
							}
						}

						return(true);
					}
					catch(Exception E)
					{
						Console.WriteLine($"EXCEPTION [{E.Message}] !");
						return(false);
					}
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void MyConfigureSwaggerGenOptions(SwaggerGenOptions Options)
		{
			OpenApiSecurityScheme								SecurityScheme=new OpenApiSecurityScheme();

			SecurityScheme.Description="JWT Authorization header using the Bearer scheme.";
			SecurityScheme.Name="Authorization";
			SecurityScheme.In=ParameterLocation.Header;
			SecurityScheme.Type=SecuritySchemeType.ApiKey;
			SecurityScheme.Scheme="Bearer";

			Options.AddSecurityDefinition("Bearer",SecurityScheme);

			OpenApiSecurityRequirement							SecurityRequirement=new OpenApiSecurityRequirement();
			OpenApiSecurityScheme								Scheme=new OpenApiSecurityScheme();

			Scheme.Reference=new OpenApiReference();

			Scheme.Reference.Type=ReferenceType.SecurityScheme;
			Scheme.Reference.Id="Bearer";

			SecurityRequirement.Add(Scheme,new string[0]);

			Options.AddSecurityRequirement(SecurityRequirement);
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
		private static void MyConfigureAuthorizationPolicy(AuthorizationPolicyBuilder Builder)
		{
			// !!! USER musi byt ASPON v 1 ROLE.
			Builder.RequireRole(CIdentityRoles.ADMINISTRATORS,CIdentityRoles.VIPS);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void MyConfigureAuthorizationOptions(AuthorizationOptions Options)
		{
			// !!! Prida sa CUSTOM POLICY.
			Options.AddPolicy(MY_POLICY_ADMINISTRATORS_OR_VIPS,MyConfigureAuthorizationPolicy);
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
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
        public static void Main(string[] args)
        {
            WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

            Builder.Services.AddControllers();

            Builder.Services.AddEndpointsApiExplorer();

			// !!! Do SWAGGER sa prida nutnost AUTHENTICATION.
            Builder.Services.AddSwaggerGen(MyConfigureSwaggerGenOptions);

			// !!! Prida sa DB CONTEXT pre IDENTITY DB.
			Builder.Services.AddDbContext<CIdentityContextDB>();

			// !!! Pridaju sa SERVICES pre IDENTITY FRAMEWORK.
			IdentityBuilder										IdentityBuilder=Builder.Services.AddIdentityCore<CIdentityUser>();
				
			// !!! Pridaju sa ROLES.
			IdentityBuilder.AddRoles<CIdentityRole>();

			// !!! Do DB CONTEXT sa pridaju TABLES pre ukladanie IDENTITY.
			IdentityBuilder.AddEntityFrameworkStores<CIdentityContextDB>();
				
			// !!! Pridaju sa DEFAULT TOKEN PROVIDERS, ktore generuju TOKENS.
			IdentityBuilder.AddDefaultTokenProviders();

			// !!! Pridaju sa SERVICES pre AUTHENTICATION.
			AuthenticationBuilder								AuthenticationBuilder=Builder.Services.AddAuthentication(MyConfigureAuthenticationOptions);

			AuthenticationBuilder.AddJwtBearer(P => MyConfigureJwtBearerOptions(Builder,P));

			// !!! Pridaju sa SERVICES pre AUTHORIZATION.
			Builder.Services.AddAuthorization(MyConfigureAuthorizationOptions);

            WebApplication										Application=Builder.Build();

			if (CreateDatabase(Application)==false)
			{
				return;
			}

            if (Application.Environment.IsDevelopment()==true)
            {
                Application.UseSwagger();
                Application.UseSwaggerUI();
            }

            Application.UseHttpsRedirection();

			// !!! Do REQUEST PIPELINE sa pridaju AUTHENTICATION MIDDLEWARE COMPONENTS.
            Application.UseAuthorization();

			// !!! Do REQUEST PIPELINE sa pridaju AUTHORIZATION MIDDLEWARE COMPONENTS.
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