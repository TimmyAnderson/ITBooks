using System.IdentityModel.Tokens.Jwt;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.OpenIdConnect;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Authorization;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Identity.Web;
using Microsoft.Identity.Web.UI;
//--------------------------------------------------------------------------------------------------------------------------------
namespace EntraExternalIDWebPages
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureMvcOptions(MvcOptions Options)
		{
			AuthorizationPolicyBuilder							PolicyBuilder=new AuthorizationPolicyBuilder();

			PolicyBuilder.RequireAuthenticatedUser();

			AuthorizationPolicy									Policy=PolicyBuilder.Build();

			AuthorizeFilter										Filter=new AuthorizeFilter(Policy);

			Options.Filters.Add(Filter);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			Builder.Services.AddControllersWithViews();

			JwtSecurityTokenHandler.DefaultMapInboundClaims=false;

			// !!! Pridaju sa SERVICES, ktore su potrebne na vykonanie AUTHENTICATION.
			AuthenticationBuilder								AuthenticationBuilderObject=Builder.Services.AddAuthentication(OpenIdConnectDefaults.AuthenticationScheme);

			// !!! METHOD nacita SETTINGS z CONFIGURATION.
			MicrosoftIdentityWebAppAuthenticationBuilderWithConfiguration	IdentityConfiguration=AuthenticationBuilderObject.AddMicrosoftIdentityWebApp(Builder.Configuration);

			MicrosoftIdentityAppCallsWebApiAuthenticationBuilder	WebApiAuthenticationBuilder=IdentityConfiguration.EnableTokenAcquisitionToCallDownstreamApi();

			WebApiAuthenticationBuilder.AddInMemoryTokenCaches();

			IMvcBuilder											MvcBuilder=Builder.Services.AddControllersWithViews(ConfigureMvcOptions);

			MvcBuilder.AddMicrosoftIdentityUI();

			WebApplication										Application=Builder.Build();

			if (Application.Environment.IsDevelopment()==false)
			{
				Application.UseExceptionHandler("/Home/Error");

				Application.UseHsts();
			}

			Application.UseHttpsRedirection();

			Application.UseStaticFiles();

			Application.UseRouting();

			Application.UseAuthorization();

			Application.MapControllerRoute(name:"default",pattern:"{controller=Home}/{action=Index}/{id?}");

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