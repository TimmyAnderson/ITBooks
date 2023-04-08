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
	public static class CShowConfigurationValuesEndpoint
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

			// !!! Nacitaju sa CONFIGURATION VALUES.
			// !!! VALUE je z FILE [appsettings.json].
			string												Value1=Configuration["MyValues:Value1"];
			// !!! VALUE je OVERRIDEN vo FILE [appsettings.Development.json].
			string												Value2=Configuration["MyValues:Value2"];

			// !!! Ziska sa CONFIGURATION SECTION [MyName].
			IConfigurationSection								MyNameConfigurationSection=Configuration.GetSection("MyName");

			// !!! VALUE je z KEY [MyName:FirstName].
			string												FirstName=MyNameConfigurationSection["FirstName"];
			// !!! VALUE je z KEY [MyName:LastName].
			string												LastName=MyNameConfigurationSection["LastName"];
			// !!! VALUE je z KEY [MyName:Age]. Pristup je pomocou METHOD [TType IConfiguration.GetValue<TType>(string Key, TType DefaultValue)].
			int													Age=MyNameConfigurationSection.GetValue<int>("Age");

			Content.Append($"VALUE 1 [{Value1}] !");
			Content.Append($"<br/>");
			Content.Append($"VALUE 2 [{Value2}] !");
			Content.Append($"<br/>");
			Content.Append($"SECTION [{MyNameConfigurationSection.Key}] FIRST NAME [{FirstName}] !");
			Content.Append($"<br/>");
			Content.Append($"SECTION [{MyNameConfigurationSection.Key}] LAST NAME [{LastName}] !");
			Content.Append($"<br/>");
			Content.Append($"SECTION [{MyNameConfigurationSection.Key}] AGE [{Age}] !");

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