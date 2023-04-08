using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Diagnostics;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingPlaformFeatures2.StatusCodePages
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CStatusCodePage
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task GenerateStatusCodePage(StatusCodeContext Context)
		{
			if (Context.HttpContext.Request.Path=="/XXX/YYY/ZZZ")
			{
				// !!! Nastavi sa CONTENT TYPE.
				Context.HttpContext.Response.ContentType="text/html; charset=utf-8";

				StringBuilder									Content=new StringBuilder();
			
				Content.Append("<!DOCTYPE html>");
				Content.Append("<html>");
				Content.Append("<head>");
				Content.Append("<meta name=\"viewport\" content=\"width=device-width\" />");
				Content.Append("<link rel=\"stylesheet\" href=\"/StaticFiles/Styles/Styles.css\" />");
				Content.Append("</head>");
				Content.Append("<body>");
				Content.Append("<div class=\"OUTER_BOX\">");

				Content.Append($"ERROR STATUS CODE [{Context.HttpContext.Response.StatusCode}] DETECTED !!!!!");

				Content.Append("</div>");
				Content.Append("</body>");
				Content.Append("</html>");

				byte[]											RawBytes=Encoding.UTF8.GetBytes(Content.ToString());

				await Context.HttpContext.Response.Body.WriteAsync(RawBytes);
			}
			else
			{
				// !!! Ak sa nejedna o spracovanie ERROR HTTP STATUS CODE, tak sa posle HTTP REQUEST MESSAGE na spracovanie do nasledujuceho MIDDLEWARE COMPONENT.
				await Context.Next(Context.HttpContext);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------