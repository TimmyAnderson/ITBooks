using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using Testing2;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject2_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! CLASS implementuje CUSTOM TEST HTTP SERVER, ktory pouzije namiesto standardnej, CUSTOM DB.
	// !!!!! CLASS je DERIVED z CLASS [WebApplicationFactory<Program>].
	public sealed class CWebApplicationFactoryCustomDB : WebApplicationFactory<Program>
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pouziva sa REALNA DB, nie IN MEMORY DATABASE.
		private const string									CONNECTION_STRING="Data Source=MyTestDatabase.db";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CWebApplicationFactoryCustomDB()
		{
			Console.WriteLine($"CONSTRUCTOR [{nameof(CWebApplicationFactoryCustomDB)}] CALLED.");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureDbContext(DbContextOptionsBuilder OptionsBuilder)
		{
			OptionsBuilder.UseSqlite(CONNECTION_STRING);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureServices(IServiceCollection Services)
		{
			ServiceDescriptor									ServiceDescriptorDBContext=Services.Where(P => P.ServiceType==typeof(CDBContext)).FirstOrDefault();

			if (ServiceDescriptorDBContext!=null)
			{
				Services.Remove(ServiceDescriptorDBContext);
			}

			Services.AddDbContext<CDBContext>(ConfigureDbContext);

			using(IServiceScope Scope=Services.BuildServiceProvider().CreateScope())
			{
				IServiceProvider								ServiceProvider=Scope.ServiceProvider;

				using(CDBContext DBContext=ServiceProvider.GetRequiredService<CDBContext>())
				{
					// !!! Vytvori sa TEST DATABASE sa naplni sa TEST DATA.
					CDBContextHelpers.InitializeDatabase(DBContext);
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Tato METHOD je volana az potom co bola instancia INTERFACE [] inicializovana v CLASS [Program]. To znamena, ze CLASS [Program] uz vytvorila DEFAULT CONFIGURATION, ktoru tato METHOD moze modifikovat.
		protected override void ConfigureWebHost(IWebHostBuilder Builder)
		{
			Builder.ConfigureServices(ConfigureServices);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------