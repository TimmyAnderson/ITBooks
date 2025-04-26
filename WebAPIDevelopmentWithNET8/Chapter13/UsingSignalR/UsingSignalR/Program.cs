using System;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Cors.Infrastructure;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Http.Connections;
using Microsoft.AspNetCore.SignalR;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.IdentityModel.Tokens;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingSignalR
{
//--------------------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									HUB_URL="/MyHub";
		private const string									CORS_POLICY_NAME="/MyHub";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureHub(HubOptions Options)
		{
			Options.KeepAliveInterval=TimeSpan.FromSeconds(10);
			Options.ClientTimeoutInterval=TimeSpan.FromSeconds(20);
			Options.EnableDetailedErrors=true;

			// !!! Nastavi sa velkost BUFFER pre STATEFUL RECONNECT.
			Options.StatefulReconnectBufferSize=200000;
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureHub(HubOptions<CMyStronlyTypedHub> Options)
		{
			Options.KeepAliveInterval=TimeSpan.FromSeconds(10);
			Options.ClientTimeoutInterval=TimeSpan.FromSeconds(20);
			Options.EnableDetailedErrors=true;

			// !!! Nastavi sa velkost BUFFER pre STATEFUL RECONNECT.
			Options.StatefulReconnectBufferSize=200000;
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureHubConnection(HttpConnectionDispatcherOptions Options)
		{
			Options.Transports=(HttpTransportType.WebSockets | HttpTransportType.LongPolling);
			Options.LongPolling.PollTimeout=TimeSpan.FromSeconds(120);
			Options.WebSockets.CloseTimeout=TimeSpan.FromSeconds(10);

			// !!! Povoli sa STATEFUL RECONNECT.
			Options.AllowStatefulReconnects=true;
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void EnableCORS(CorsOptions Options)
		{
			CorsPolicyBuilder									CorsPolicyBuilder=new CorsPolicyBuilder();

			CorsPolicyBuilder.AllowAnyHeader();

			CorsPolicyBuilder.AllowAnyMethod();

			CorsPolicyBuilder.AllowCredentials();

			// !!! URL su vymyslene. No mali by to byt URL tych DOMAINS z ktorych BROSERS pristupuju k SERVER.
		    CorsPolicyBuilder.WithOrigins("http://127.0.0.1:12345","https://localhost:12345");

			CorsPolicy											CorsPolicy=CorsPolicyBuilder.Build();

		    Options.AddPolicy(CORS_POLICY_NAME,CorsPolicy);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD extrahuje ACCESS TOKEN z QUERY STRING.
		// !!!!! METHOD je potrebna IBA pre JAVA SCRIPT WEB SOCKET CLIENTS. .NET CLIENTS posielaju ACCESS TOKEN v AUTHORIZE HEADER.
		private static Task JWTEventOnMessageReceived(MessageReceivedContext Context)
		{
            PathString											Path=Context.HttpContext.Request.Path;

			if (Path.StartsWithSegments(HUB_URL)==true)
			{
				string											AccessToken=Context.Request.Query["access_token"];

				if (AccessToken!=null && AccessToken!="")
				{
					Context.Token=AccessToken;
				}
			}

			Task												CompletedTask=Task.CompletedTask;

			return(CompletedTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
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

			Options.Events=new JwtBearerEvents();
				
			// !!!!! Zaregistruje sa JWT EVENT, ktory vyberie ACCESS TOKEN nie z AUTHORIZE TOKEN, ako to ASP.NET CORE robi BY-DEFAULT, ale z QUERY STRING.
			Options.Events.OnMessageReceived=JWTEventOnMessageReceived;
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void MyConfigureAuthorizationOptions(AuthorizationOptions Options)
		{
			// Nie su tu ziadne POLICIES.
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

			// !!! Prida SERVICES, ktore vyuziva SINGAL R.
			//Builder.Services.AddSignalR(ConfigureHub);

			// !!! Prida SERVICES, ktore vyuziva SINGAL R.
			// !!! Alternativna CONFINGURATION konkretneho HUB.
			ISignalRServerBuilder								SignalRServerBuilder=Builder.Services.AddSignalR();
				
			// !!! Alternativna CONFINGURATION konkretneho HUB.
			SignalRServerBuilder.AddHubOptions<CMyStronlyTypedHub>(ConfigureHub);

			// !!! Prida sa USER ID PROVIDER pre SINGAL R ako SERIVCE.
			Builder.Services.AddSingleton<IUserIdProvider,CMyUserIdProvider>();

			// !!! Nastavi sa CORS POLICY pre WEB BROSERS pristupujuce z inej DOMAIN.
			Builder.Services.AddCors(EnableCORS);

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

			// !!!!! Ak sa k SERVER pristupuje aj z WEB BROSERS je nutne povolit CORS.
			Application.UseCors(CORS_POLICY_NAME);

            Application.UseAuthorization();

			// !!! Do PIPELINE sa prida SIGNAL R MIDDLEWARE, ktory je vystaveny na zadanej URL.

			// !!!!! UNTYPED HUB.
			//Application.MapHub<CMyHub>(HUB_URL);

			// !!!!! STRONGLY TYPED HUB.
			Application.MapHub<CMyStronlyTypedHub>(HUB_URL,ConfigureHubConnection);

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