using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingPlaformFeatures2.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CCookieEssentialCounterDeleteEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task Endpoint(HttpContext Context)
		{
			string												StringCounter1;
			string												StringCounter2;

			// !!! Nacita sa COOKIE VALUE.
			Context.Request.Cookies.TryGetValue("ESSENTIAL_COUNTER_1",out StringCounter1);

			// !!! Nacita sa COOKIE VALUE.
			Context.Request.Cookies.TryGetValue("ESSENTIAL_COUNTER_2",out StringCounter2);

			// !!! COOKIE sa VYMAZE.
			Context.Response.Cookies.Delete("ESSENTIAL_COUNTER_1");

			// !!! COOKIE sa VYMAZE.
			Context.Response.Cookies.Delete("ESSENTIAL_COUNTER_2");

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

			Content.Append($"COUNTER 1 (ESSENTIAL) [{StringCounter1}] was DELETED !");
			Content.Append($"<br/>");
			Content.Append($"COUNTER 2 (NON-ESSENTIAL) [{StringCounter2}] was DELETED !");
			Content.Append($"<br/>");
			Content.Append($"<a href=\"/CookieEssentialCounterCount\">Go to COUNTER PAGE !</a>");

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