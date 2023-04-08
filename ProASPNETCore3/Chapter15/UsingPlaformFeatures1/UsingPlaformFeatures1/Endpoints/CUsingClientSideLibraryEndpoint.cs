using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingPlaformFeatures1.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CUsingClientSideLibraryEndpoint
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

			Content.Append($"CLIENT SIDE LIBRARY is USED !");
			Content.Append($"<br/>");
			Content.Append($"TIME [{CreateTime(DateTime.Now)}] !");
			Content.Append($"<br/>");

			// !!! Pouzije sa STYLE z CLIENT SIDE LIBRARY.
			Content.Append($"<a href=\"/UsingClientSideLibrary\" class=\"btn btn-sm btn-primary\">Reload PAGE !</a>");

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