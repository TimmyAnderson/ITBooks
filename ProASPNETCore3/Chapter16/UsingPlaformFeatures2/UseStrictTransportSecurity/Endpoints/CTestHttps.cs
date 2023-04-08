using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace UseStrictTransportSecurity.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CTestHttps
	{
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
			Content.Append("</head>");
			Content.Append("<body>");
			Content.Append("<div class=\"OUTER_BOX\">");

			// !!! PROPERTY [IsHttps] urcuje ci HTTP REQUEST MESSAGE bola zaslana cez PROTOCOL HTTPS.
			Content.Append($" IS HTTPS [{Context.Request.IsHttps}] !");

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