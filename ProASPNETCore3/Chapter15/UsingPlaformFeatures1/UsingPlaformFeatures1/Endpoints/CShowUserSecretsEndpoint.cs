using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Configuration;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingPlaformFeatures1.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CShowUserSecretsEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task Endpoint(HttpContext Context)
		{
			IConfiguration										Configuration=(IConfiguration) Context.RequestServices.GetService(typeof(IConfiguration));

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

			// !!! Nacitaju sa USER SECRETS.
			string												Secret1=Configuration["MySecrets:Secret1"];
			string												Secret2=Configuration["MySecrets:Secret2"];

			Content.Append($"SECRET 1 [{Secret1}] !");
			Content.Append($"<br/>");
			Content.Append($"SECRET 2 [{Secret2}] !");

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