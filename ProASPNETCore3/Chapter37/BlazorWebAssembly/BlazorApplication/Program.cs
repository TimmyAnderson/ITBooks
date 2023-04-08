using System;
using System.Net.Http;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Text;
using Microsoft.AspNetCore.Components.WebAssembly.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorApplication
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task Main(string[] args)
		{
			WebAssemblyHostBuilder								Builder=WebAssemblyHostBuilder.CreateDefault(args);

			Builder.RootComponents.Add<App>("app");

			//Builder.Services.AddScoped(P => new HttpClient { BaseAddress = new Uri(Builder.HostEnvironment.BaseAddress) });

			await Builder.Build().RunAsync();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------