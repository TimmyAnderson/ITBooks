using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.Extensions.DependencyInjection;
using Testing2;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject2_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CWebApplicationFactoryAuthenticationHandler : WebApplicationFactory<Program>
	{
//----------------------------------------------------------------------------------------------------------------------
		public const string										DEFAULT_USER_NAME="Jenny";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureCustomOptions(CAuthenticationHandlerTestOptions Options)
		{
			Options.TestUserName=DEFAULT_USER_NAME;
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureAuthentication(AuthenticationOptions Options)
		{
            Options.DefaultAuthenticateScheme=CAuthenticationHandlerTest.AUTHENTICATION_SCHEME;
            Options.DefaultChallengeScheme=CAuthenticationHandlerTest.AUTHENTICATION_SCHEME;
            Options.DefaultScheme=CAuthenticationHandlerTest.AUTHENTICATION_SCHEME;
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureAuthenticationScheme(CAuthenticationHandlerTestOptions Options)
		{
			// EMPTY.
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureTestServices(IServiceCollection Services)
		{
			Services.Configure<CAuthenticationHandlerTestOptions>(ConfigureCustomOptions);

			AuthenticationBuilder								AuthenticationBuilder=Services.AddAuthentication(ConfigureAuthentication);

			AuthenticationBuilder.AddScheme<CAuthenticationHandlerTestOptions,CAuthenticationHandlerTest>(CAuthenticationHandlerTest.AUTHENTICATION_SCHEME,ConfigureAuthenticationScheme);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void ConfigureWebHost(IWebHostBuilder Builder)
		{
			Builder.ConfigureServices(ConfigureTestServices);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------