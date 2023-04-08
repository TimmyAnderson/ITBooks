using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Caching.Distributed;
//----------------------------------------------------------------------------------------------------------------------
namespace WorkingWithData.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CResponseCacheLongCalculationEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		private static string CreateTime()
		{
			DateTime											Time=DateTime.Now;
			string												TextTime=$"{Time.Hour.ToString("00")}:{Time.Minute.ToString("00")}:{Time.Second.ToString("00")}.{Time.Millisecond.ToString("000")}";

			return(TextTime);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! RESPONSE CACHING je mozne demonstrovat iba ak WEB BROWSER NEBEZI v DEBUG MODE - tj. NIE JE SPUSTENY pomocou F5. Ak je totizto spusteny cez F5, tak CHROME zasiela HEADER [Cache-Control] s VALUE [no-cache] a RESPONSE CACHE sa NEAPLIKUJE. Riesenim je spustit APPLICATION a nezavisle spustit CHROME a v tejto istancii testovat RESPONSE CACHING kedy sa NEPOSIELA HEADER [Cache-Control].
		public static async Task Endpoint(HttpContext Context)
		{
			int													RelativeTime=30;
			StringBuilder										SB=new StringBuilder();
			
			SB.Append("<!DOCTYPE html>");
			SB.Append("<html>");
			SB.Append("<head>");
			SB.Append("<meta name=\"viewport\" content=\"width=device-width\" />");
			SB.Append("<link rel=\"stylesheet\" href=\"/StaticFiles/Styles/Styles.css\" />");
			SB.Append("</head>");
			SB.Append("<body>");
			SB.Append("<div class=\"OUTER_BOX\">");

			SB.Append($"TIME [{CreateTime()}] - LONG CALCULATION STARTED !");

			await Task.Delay(5000);

			Random												RND=new Random();
			double												CalculatedValue=RND.NextDouble();

			SB.Append($"<br/>");
			SB.Append($" TIME [{CreateTime()}] - CALCULATED VALUE [{CalculatedValue}] !");
			SB.Append($"<br/>");
			SB.Append($" TIME [{CreateTime()}] - LONG CALCULATION FINISHED !");
			SB.Append($"<br/>");
			SB.Append($" TIME [{CreateTime()}] - CACHED for RELATIVE TIME [{RelativeTime} SECONDS] !");

			SB.Append($"<br/>");
			SB.Append($"<a href=\"/ResponseCacheLongCalculation\">Reload PAGE !</a>");

			SB.Append("</div>");
			SB.Append("</body>");
			SB.Append("</html>");

			// !!! Nastavi sa CONTENT TYPE.
			Context.Response.ContentType="text/html; charset=utf-8";

			// !!!!! Na to aby RESPONSE CHACHING mohol fungovat, je NUTNE nastavit HEADER [Cache-Control].
			Context.Response.Headers["Cache-Control"]=$"public, max-age={RelativeTime}";

			await Context.Response.WriteAsync(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------