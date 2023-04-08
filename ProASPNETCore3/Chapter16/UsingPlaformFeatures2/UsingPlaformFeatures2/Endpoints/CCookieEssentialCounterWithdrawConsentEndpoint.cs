using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Http.Features;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingPlaformFeatures2.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CCookieEssentialCounterWithdrawConsentEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task Endpoint(HttpContext Context)
		{
			ITrackingConsentFeature								TrackingConsentFeature=Context.Features.Get<ITrackingConsentFeature>();

			TrackingConsentFeature.WithdrawConsent();

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

			Content.Append($"CONSENT was WITHDRAWN !");
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