using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace WorkingWithData.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CLongCalculationEndpoint
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
		public static async Task Endpoint(HttpContext Context)
		{
			await Context.Response.WriteAsync($"TIME [{CreateTime()}] - LONG CALCULATION STARTED !");

			await Task.Delay(5000);

			Random												RND=new Random();
			double												CalculatedValue=RND.NextDouble();

			await Context.Response.WriteAsync($" TIME [{CreateTime()}] - CALCULATED VALUE [{CalculatedValue}] !");

			await Context.Response.WriteAsync($" TIME [{CreateTime()}] - LONG CALCULATION FINISHED !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------