using System;
using System.IO;
using System.Net.Http;
using System.Reflection;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.OutputCaching;
using Microsoft.Extensions.Caching.StackExchangeRedis;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.OpenApi;
using Swashbuckle.AspNetCore.SwaggerGen;
//--------------------------------------------------------------------------------------------------------------------------------
namespace WebAPICommonPracticesWeb
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										OUTPUT_CACHING_POLICY_1="Expire30";
		public const string										OUTPUT_CACHING_POLICY_2="Expire60";
//--------------------------------------------------------------------------------------------------------------------------------
		public const string										NAMED_HTTP_CLIENT_NAME="MyClientWithBaseAddress";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static void SwaggerSettings(SwaggerGenOptions Options)
		{
			OpenApiInfo											Info=new OpenApiInfo();

			Info.Title="My API API";
			Info.Version="v1";

			Options.SwaggerDoc("v1",Info);

			string												XmlPath=(Path.Combine(AppContext.BaseDirectory,$"{Assembly.GetExecutingAssembly().GetName().Name}.xml"));

			// !!! Povoli sa generovanie DOCUMENTATION z COMMENTS [///].
			Options.IncludeXmlComments(XmlPath);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureRedisCache(RedisCacheOptions Options)
		{
			// !!! REDIS CACHE SERVER DOCKER CONTAINER musi byt spusteny s tymto PORT.
			Options.Configuration="localhost:6379";
			Options.InstanceName="MyCachingDemo";
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureOutputCache(OutputCacheOptions Options)
		{
			Options.AddBasePolicy(P => P.Cache());

			// !!! Vlozia sa CUSTOM POLICIES.
			Options.AddPolicy(OUTPUT_CACHING_POLICY_1,P => P.Expire(TimeSpan.FromSeconds(30)));
		    Options.AddPolicy(OUTPUT_CACHING_POLICY_2,P => P.Expire(TimeSpan.FromSeconds(60)));
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureNamedHttpClient(HttpClient Client)
		{
			// !!! Nastavi sa BASE ADDRESS.
			Client.BaseAddress=new Uri("https://localhost:7000/");
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			Builder.Services.AddControllers();

			Builder.Services.AddEndpointsApiExplorer();

			// !!! SWAGGER bude generovat DOCUMENTATION z COMMENTS [///].
			Builder.Services.AddSwaggerGen(SwaggerSettings);

			// !!! Povoli sa pouzitie IN MEMORY CACHE.
			Builder.Services.AddMemoryCache();

			// !!! Povoli sa pouzitie REDIS DISTRIBUTED CACHE.
			Builder.Services.AddStackExchangeRedisCache(ConfigureRedisCache);

			// !!! Povoli sa pouzitie OUTPUT CACHE.
			Builder.Services.AddOutputCache(ConfigureOutputCache);

			// !!! Pridaju sa SERVICES potrebne pre HTTP CLIENT FACTORY.
			Builder.Services.AddHttpClient();

			// !!! Pridaju sa SERVICES potrebne pre NAMED HTTP CLIENT FACTORY.
			Builder.Services.AddHttpClient(NAMED_HTTP_CLIENT_NAME,ConfigureNamedHttpClient);

			// !!! Pridaju sa SERVICES potrebne pre TYPED HTTP CLIENT.
			Builder.Services.AddHttpClient<CMyTypedHttpClient>();

			WebApplication										Application=Builder.Build();

			if (Application.Environment.IsDevelopment()==true)
			{
				Application.UseSwagger();
				Application.UseSwaggerUI();
			}

			Application.UseHttpsRedirection();

			Application.UseAuthorization();

			// !!! Vlozi sa OUTPUT CACHING MIDDLEWARE.
			Application.UseOutputCache();

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