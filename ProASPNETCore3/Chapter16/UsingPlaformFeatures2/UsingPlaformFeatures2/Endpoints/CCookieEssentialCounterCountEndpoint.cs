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
	public static class CCookieEssentialCounterCountEndpoint
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
			int													Counter1=0;
			int													Counter2=0;
			string												StringCounter1;
			string												StringCounter2;

			// !!! Nacita sa COOKIE VALUE.
			if (Context.Request.Cookies.TryGetValue("ESSENTIAL_COUNTER_1",out StringCounter1)==true)
			{
				int.TryParse(StringCounter1,out Counter1);
			}

			// !!! Nacita sa COOKIE VALUE.
			if (Context.Request.Cookies.TryGetValue("ESSENTIAL_COUNTER_2",out StringCounter2)==true)
			{
				int.TryParse(StringCounter2,out Counter2);
			}

			if (StringCounter1!=null)
			{
				Counter1+=1;
			}

			if (StringCounter2!=null)
			{
				Counter2+=2;
			}

			CookieOptions										Counter1Options=new CookieOptions();
			CookieOptions										Counter2Options=new CookieOptions();

			// !!! Zivotnost COOKIE sa nastavi na 30 sekund.
			Counter1Options.MaxAge=TimeSpan.FromSeconds(30);

			// !!! COOKIE sa nastavi ako ESSENTIAL.
			Counter1Options.IsEssential=true;

			// !!! Zivotnost COOKIE sa nastavi na 60 sekund.
			Counter2Options.MaxAge=TimeSpan.FromSeconds(60);

			// !!! COOKIE sa nastavi ako NON-ESSENTIAL.
			Counter2Options.IsEssential=false;

			DateTime											Now=DateTime.Now;
			DateTime											Cookie1ExpirationTime=Now.Add(Counter1Options.MaxAge.Value);
			DateTime											Cookie2ExpirationTime=Now.Add(Counter2Options.MaxAge.Value);

			// !!! COOKIE VALUE sa ulozi do COOKIES HTTP RESPONSE MESSAGE.
			Context.Response.Cookies.Append("ESSENTIAL_COUNTER_1",Counter1.ToString(),Counter1Options);

			// !!! COOKIE VALUE sa ulozi do COOKIES HTTP RESPONSE MESSAGE.
			Context.Response.Cookies.Append("ESSENTIAL_COUNTER_2",Counter2.ToString(),Counter2Options);

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

			Content.Append($" COUNTER 1 (ESSENTIAL) [{Counter1}] will EXPIRE at [{CreateTime(Cookie1ExpirationTime)}] !");
			Content.Append($"<br/>");
			Content.Append($" COUNTER 2 (NON-ESSENTIAL) [{Counter2}] will EXPIRE at [{CreateTime(Cookie2ExpirationTime)}] !");
			Content.Append($"<br/>");
			Content.Append($"<a href=\"/CookieEssentialCounterCount\">Reload PAGE !</a>");
			Content.Append($"<br/>");
			Content.Append($"<a href=\"/CookieEssentialCounterDelete\">Delete COOKIES !</a>");
			Content.Append($"<br/>");
			Content.Append($"<a href=\"/CookieEssentialCounterGrantConsent\">Grant CONSENT !</a>");
			Content.Append($"<br/>");
			Content.Append($"<a href=\"/CookieEssentialCounterWithdrawConsent\">Withdraw CONSENT !</a>");

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