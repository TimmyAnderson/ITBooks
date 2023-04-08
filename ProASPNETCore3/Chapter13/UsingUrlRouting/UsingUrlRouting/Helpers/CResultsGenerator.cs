using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UsingUrlRouting.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingUrlRouting.Helpers
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CResultsGenerator
	{
//----------------------------------------------------------------------------------------------------------------------
		public static string ShowResults(CResult Result)
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendLine("<!DOCTYPE html>");
			SB.AppendLine("<html>");

			SB.AppendLine("<head>");
			SB.AppendLine("<meta name=\"viewport\" content=\"width=device-width\" />");
			SB.AppendLine("<link rel=\"stylesheet\" href=\"http://localhost:50000/StaticFiles/Styles/Styles.css\" />");
			SB.AppendLine("<link rel=\"stylesheet\" href=\"http://localhost:50000/StaticFiles/ClientLibraries/Bootstrap/css/bootstrap.css\" />");
			SB.AppendLine("<title>Result</title>");
			SB.AppendLine("</head>");

			SB.AppendLine("<body>");

			SB.AppendLine("<div class=\"OUTER_BOX\">");
			
			SB.AppendLine("<table class=\"table table-bordered table-striped\">");
			SB.AppendLine("<tr>");
			SB.AppendLine("<th>Url:</th>");
			SB.AppendLine("<td>");
			SB.AppendLine($"[{Result.Url}] !");
			SB.AppendLine("</td>");
			SB.AppendLine("</tr>");

			SB.AppendLine("<tr>");
			SB.AppendLine("<th>Endpoint:</th>");
			SB.AppendLine("<td>");
			SB.AppendLine($"[{Result.Endpoint}] !");
			SB.AppendLine("</td>");
			SB.AppendLine("</tr>");

			foreach(KeyValuePair<string,object> KeyValue in Result.Data)
			{
				SB.AppendLine("<tr>");
				SB.AppendLine("<th>");
				SB.AppendLine($"{KeyValue.Key}");
				SB.AppendLine("</th>");

				SB.AppendLine("<td>");
				SB.AppendLine($"[{KeyValue.Value}] !");
				SB.AppendLine("</td>");
				SB.AppendLine("</tr>");
			}

			SB.AppendLine("</table>");

			SB.AppendLine("</div>");

			SB.AppendLine("</body>");
			SB.AppendLine("</html>");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------