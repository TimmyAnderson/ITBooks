using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingPlaformFeatures1.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public class CPerformLoggingEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		private static string CreateTime(DateTime Time)
		{
			string												TextTime=$"{Time.Hour.ToString("00")}:{Time.Minute.ToString("00")}:{Time.Second.ToString("00")}.{Time.Millisecond.ToString("000")}";

			return(TextTime);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static async Task Endpoint(HttpContext Context)
		{
			ILogger<CPerformLoggingEndpoint>					Logger=(ILogger<CPerformLoggingEndpoint>) Context.RequestServices.GetService(typeof(ILogger<CPerformLoggingEndpoint>));

			// !!! Nastavi sa CONTENT TYPE.
			Context.Response.ContentType="text/html; charset=utf-8";

			DateTime											Now=DateTime.Now;
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

			Content.Append($"LOG MESSAGE was WRITTEN !");
			Content.Append($"<br/>");
			Content.Append($"TIME [{CreateTime(Now)}] !");
			Content.Append($"<br/>");

			// !!! Pouzije sa STYLE z CLIENT SIDE LIBRARY.
			Content.Append($"<a href=\"/PerformLogging\" class=\"btn btn-sm btn-primary\">Reload PAGE !</a>");

			Content.Append("</div>");
			Content.Append("</body>");
			Content.Append("</html>");

			await Context.Response.WriteAsync(Content.ToString());

			// !!! Zapise sa INFORMATION LOG MESSAGE.
			Logger.LogInformation($"TIME [{CreateTime(Now)}] - CLASS [{nameof(CPerformLoggingEndpoint)}] WRITTEN its CONTENT !");

			// !!! Zapise sa DEBUG LOG MESSAGE.
			Logger.LogDebug($"TIME [{CreateTime(Now)}] - CLASS [{nameof(CPerformLoggingEndpoint)}] WRITTEN its CONTENT ! CONTENT [{Content.ToString()}] !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------