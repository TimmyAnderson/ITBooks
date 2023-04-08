using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingPlaformFeatures1.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CShowCurrentEnvironmentEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task Endpoint(HttpContext Context)
		{
			IConfiguration										Configuration=(IConfiguration) Context.RequestServices.GetService(typeof(IConfiguration));
			IWebHostEnvironment									WebHostEnvironment=(IWebHostEnvironment) Context.RequestServices.GetService(typeof(IWebHostEnvironment));

			// !!! Nastavi sa CONTENT TYPE.
			Context.Response.ContentType="text/html; charset=utf-8";

			StringBuilder										Content=new StringBuilder();
			
			Content.Append("<!DOCTYPE html>");
			Content.Append("<html>");
			Content.Append("<head>");
			Content.Append("<meta name=\"viewport\" content=\"width=device-width\" />");
			Content.Append("<link rel=\"stylesheet\" href=\"/StaticFiles/Styles/Styles.css\" />");
			Content.Append("<link rel=\"stylesheet\" href=\"/StaticFiles/ClientLibraries/Bootstrap/css/bootstrap.css\" />");
			Content.Append("</head>");
			Content.Append("<body>");
			Content.Append("<div class=\"OUTER_BOX\">");

			// !!! Nacita sa ENVIRONMENT z ENVIRONMENT VARIABLES.
			string												EnvironmentFromConfiguration=Configuration["ASPNETCORE_ENVIRONMENT"];

			Content.Append($"ENVIRONMENT from CONFIGURATION [{EnvironmentFromConfiguration}] !");
			Content.Append($"<br/>");
			Content.Append($"IS ENVIRONMENT 'XXX' [{WebHostEnvironment.IsEnvironment("XXX")}] !");
			Content.Append($"<br/>");
			Content.Append($"IS ENVIRONMENT 'DEVELOPMENT' [{WebHostEnvironment.IsDevelopment()}] !");
			Content.Append($"<br/>");
			Content.Append($"IS ENVIRONMENT 'STAGING' [{WebHostEnvironment.IsStaging()}] !");
			Content.Append($"<br/>");
			Content.Append($"IS ENVIRONMENT 'PRODUCTION' [{WebHostEnvironment.IsProduction()}] !");

			Content.Append("</div>");
			Content.Append("</body>");
			Content.Append("</html>");

			await Context.Response.WriteAsync(Content.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------