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
	public static class CSessionCounterDeleteEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task Endpoint(HttpContext Context)
		{
			// !!! Nacita sa VALUE zo SESSION.
			int?												Counter1=Context.Session.GetInt32("SESSION_COUNTER_1");

			// !!! Nacita sa VALUE zo SESSION.
			int?												Counter2=Context.Session.GetInt32("SESSION_COUNTER_2");

			// !!! VALUE sa VYMAZE zo SESSION.
			Context.Session.Remove("SESSION_COUNTER_1");

			// !!! VALUE sa VYMAZE zo SESSION.
			Context.Session.Remove("SESSION_COUNTER_2");

			// !!!!! Vsetky zmeny sa zapisu do SESSION STORAGE.
			await Context.Session.CommitAsync();

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

			Content.Append($"COUNTER 1 [{Counter1}] was DELETED from SESSION !");
			Content.Append($"<br/>");
			Content.Append($"COUNTER 2 [{Counter2}] was DELETED from SESSION !");
			Content.Append($"<br/>");
			Content.Append($"<a href=\"/SessionCounterCount\">Go to COUNTER PAGE !</a>");

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