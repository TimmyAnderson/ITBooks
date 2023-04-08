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
	public static class CSessionCounterCountEndpoint
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
			// !!! Nacita sa VALUE zo SESSION.
			int?												Counter1=Context.Session.GetInt32("SESSION_COUNTER_1");

			// !!! Nacita sa VALUE zo SESSION.
			int?												Counter2=Context.Session.GetInt32("SESSION_COUNTER_2");

			if (Counter1!=null)
			{
				Counter1+=1;
			}
			else
			{
				Counter1=0;
			}

			if (Counter2!=null)
			{
				Counter2+=2;
			}
			else
			{
				Counter2=0;
			}

			// !!! VALUE sa zapise do SESSION.
			Context.Session.SetInt32("SESSION_COUNTER_1",Counter1.Value);

			// !!! VALUE sa zapise do SESSION.
			Context.Session.SetInt32("SESSION_COUNTER_2",Counter2.Value);

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

			Content.Append($" COUNTER 1 [{Counter1}] !");
			Content.Append($"<br/>");
			Content.Append($" COUNTER 2 [{Counter2}] !");
			Content.Append($"<br/>");
			Content.Append($"<a href=\"/SessionCounterCount\">Reload PAGE !</a>");
			Content.Append($"<br/>");
			Content.Append($"<a href=\"/SessionCounterDelete\">Delete RECORDS from SESSION !</a>");

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