using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using Moq;
using Testing2;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject2_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! CLASS implementuje CUSTOM TEST HTTP SERVER, ktory pouzije MOCK SERVICE, ako nahradu za realny SERVICE.
	public sealed class CWebApplicationFactoryCustomService : WebApplicationFactory<Program>
	{
//----------------------------------------------------------------------------------------------------------------------
		public CWebApplicationFactoryCustomService()
		{
			Console.WriteLine($"CONSTRUCTOR [{nameof(CWebApplicationFactoryCustomService)}] CALLED.");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureServices(IServiceCollection Services)
		{
			ServiceDescriptor									ServiceDescriptorRemoteService=Services.Where(P => P.ServiceType==typeof(IMyRemoteNamesService)).FirstOrDefault();

			if (ServiceDescriptorRemoteService!=null)
			{
				Services.Remove(ServiceDescriptorRemoteService);
			}

			Mock<IMyRemoteNamesService>							MockMyRemoteNamesService=new Mock<IMyRemoteNamesService>();

			CMyRemoteName										MyRemoteName1=new CMyRemoteName("TIMMY","ANDERSON",12,ESex.E_MALE);

			MockMyRemoteNamesService.Setup(P => P.GetName1()).Returns(MyRemoteName1).Verifiable();

			CMyRemoteName										MyRemoteName2=new CMyRemoteName("JENNY","THOMPSON",13,ESex.E_FEMALE);

			MockMyRemoteNamesService.Setup(P => P.GetName2()).Returns(MyRemoteName2).Verifiable();

			Services.AddSingleton<IMyRemoteNamesService>(MockMyRemoteNamesService.Object);
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