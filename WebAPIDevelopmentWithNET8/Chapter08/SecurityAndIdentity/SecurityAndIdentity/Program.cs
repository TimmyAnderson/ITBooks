using System;
using System.Linq;
using System.Security.Claims;
using System.Text;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Identity;
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
						string[]								RoleNames=new string[]{CSecurityRoles.ADMINISTRATORS,CSecurityRoles.VIPS,CSecurityRoles.USERS};

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
		private static void MyConfigureIdentity(IdentityOptions Options)
		{
			Options.Password.RequiredLength=10;

			Options.Lockout.MaxFailedAccessAttempts=2;
			Options.Lockout.DefaultLockoutTimeSpan=TimeSpan.FromSeconds(10);
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
		private static void MyConfigureAuthorizationPolicyRoles(AuthorizationPolicyBuilder Builder)
		{
			// !!! USER musi byt ASPON v 1 ROLE.
			Builder.RequireRole(CSecurityRoles.ADMINISTRATORS,CSecurityRoles.VIPS);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void MyConfigureAuthorizationPolicyClaims1(AuthorizationPolicyBuilder Builder)
		{
			// !!! USER musi mat dany CLAIM s VALUE.
			Builder.RequireClaim(CSecurityClaims.MY_CLAIM_1,CSecurityUsers.VIP.ToLower());
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static bool MyConfigureAuthorizationPolicyClaims2HasClaim(Claim Claim)
		{
			if (Claim.Type==CSecurityClaims.MY_CLAIM_2)
			{
				if (Claim.Value==CSecurityUsers.ADMINISTRATOR.ToUpper())
				{
					return(true);
				}
				else if (Claim.Value==CSecurityUsers.VIP.ToUpper())
				{
					return(true);
				}
			}
			
			return(false);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static bool MyConfigureAuthorizationPolicyClaims2Assertion(AuthorizationHandlerContext Context)
		{
			bool												HasClaim=Context.User.HasClaim(MyConfigureAuthorizationPolicyClaims2HasClaim);

			return(HasClaim);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void MyConfigureAuthorizationPolicyClaims2(AuthorizationPolicyBuilder Builder)
		{
			// !!! USER musi mat splnat danu CONDITION.
			Builder.RequireAssertion(MyConfigureAuthorizationPolicyClaims2Assertion);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void MyConfigureAuthorizationPolicyPolicyAuthorization(AuthorizationPolicyBuilder Builder)
		{
			// !!!!! POLICY vyzaduje splnanie VSETKYCH REQUIREMENTS.

			string												StartsWith=CSecurityUsers.ADMINISTRATOR.Substring(0,3).ToLower();
			CSecurityAuthorizationRequirement1					Requirement1=new CSecurityAuthorizationRequirement1(StartsWith);

			Builder.Requirements.Add(Requirement1);

			string												EndsWith=CSecurityUsers.ADMINISTRATOR.Substring(Math.Max(CSecurityUsers.ADMINISTRATOR.Length-3,0),3).ToUpper();
			CSecurityAuthorizationRequirement2					Requirement2=new CSecurityAuthorizationRequirement2(EndsWith);

			Builder.Requirements.Add(Requirement2);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void MyConfigureAuthorizationPolicyPolicyAuthorizationMultiHandler(AuthorizationPolicyBuilder Builder)
		{
			// !!!!! POLICY vyzaduje splnanie VSETKYCH REQUIREMENTS.

			string												StartsWith=CSecurityUsers.ADMINISTRATOR.Substring(0,3).ToLower();
			CSecurityAuthorizationRequirement3					Requirement3=new CSecurityAuthorizationRequirement3(StartsWith);

			Builder.Requirements.Add(Requirement3);

			string												EndsWith=CSecurityUsers.ADMINISTRATOR.Substring(Math.Max(CSecurityUsers.ADMINISTRATOR.Length-3,0),3).ToUpper();
			CSecurityAuthorizationRequirement4					Requirement4=new CSecurityAuthorizationRequirement4(EndsWith);

			Builder.Requirements.Add(Requirement4);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void MyConfigureAuthorizationOptions(AuthorizationOptions Options)
		{
			// !!! Prida sa CUSTOM POLICY.
			Options.AddPolicy(CSecurityPolicies.MY_POLICY_ROLE_AUTHORIZATION_ADMINISTRATORS_OR_VIPS,MyConfigureAuthorizationPolicyRoles);

			// !!! Prida sa CUSTOM POLICY.
			Options.AddPolicy(CSecurityPolicies.MY_POLICY_CLAIMS_AUTHORIZATION_VIP_ONLY,MyConfigureAuthorizationPolicyClaims1);

			// !!! Prida sa CUSTOM POLICY.
			Options.AddPolicy(CSecurityPolicies.MY_POLICY_CLAIMS_AUTHORIZATION_ADMINISTRATOR_OR_VIP,MyConfigureAuthorizationPolicyClaims2);

			// !!! Prida sa CUSTOM POLICY.
			Options.AddPolicy(CSecurityPolicies.MY_POLICY_POLICY_AUTHORIZATION_ADMINISTRATOR,MyConfigureAuthorizationPolicyPolicyAuthorization);

			// !!! Prida sa CUSTOM POLICY.
			Options.AddPolicy(CSecurityPolicies.MY_POLICY_POLICY_AUTHORIZATION_ADMINISTRATOR_MULTI_HANDLER,MyConfigureAuthorizationPolicyPolicyAuthorizationMultiHandler);
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
				
			// !!! Pridaju sa SERVICES pre SING IN MANAGER.
			IdentityBuilder.AddSignInManager();

			// !!! Pridaju sa ROLES.
			IdentityBuilder.AddRoles<CIdentityRole>();

			// !!! Do DB CONTEXT sa pridaju TABLES pre ukladanie IDENTITY.
			IdentityBuilder.AddEntityFrameworkStores<CIdentityContextDB>();
				
			// !!! Pridaju sa DEFAULT TOKEN PROVIDERS, ktore generuju TOKENS.
			IdentityBuilder.AddDefaultTokenProviders();

			// !!! Nastavia sa poziadavky na silu PASSWORD a PASSWORD LOCKOUT POLICY.
			Builder.Services.Configure<IdentityOptions>(MyConfigureIdentity);

			// !!! Pridaju sa SERVICES pre AUTHENTICATION.
			AuthenticationBuilder								AuthenticationBuilder=Builder.Services.AddAuthentication(MyConfigureAuthenticationOptions);

			AuthenticationBuilder.AddJwtBearer(P => MyConfigureJwtBearerOptions(Builder,P));

			// !!! Pridaju sa SERVICES pre AUTHORIZATION.
			Builder.Services.AddAuthorization(MyConfigureAuthorizationOptions);

			// !!!!! Pridaju sa ako SERVICE CUSTOM AUTHORIZATION HANDLERS.
			Builder.Services.AddSingleton<IAuthorizationHandler,CSecurityAuthorizationHandler1>();
			Builder.Services.AddSingleton<IAuthorizationHandler,CSecurityAuthorizationHandler2>();
			Builder.Services.AddSingleton<IAuthorizationHandler,CSecurityAuthorizationHandler3And4>();

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