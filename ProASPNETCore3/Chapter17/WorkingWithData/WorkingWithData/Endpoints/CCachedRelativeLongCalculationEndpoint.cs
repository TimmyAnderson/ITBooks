﻿using System;
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
	public static class CCachedRelativeLongCalculationEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		private static string CreateTime()
		{
			DateTime											Time=DateTime.Now;
			string												TextTime=$"{Time.Hour.ToString("00")}:{Time.Minute.ToString("00")}:{Time.Second.ToString("00")}.{Time.Millisecond.ToString("000")}";

			return(TextTime);
		}
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
			IDistributedCache									Cache=(IDistributedCache) Context.RequestServices.GetService(typeof(IDistributedCache));
			string												Key=nameof(CCachedRelativeLongCalculationEndpoint);

			// !!! Nacita sa VALUE z CACHE.
			string												CachedValue=await Cache.GetStringAsync(Key);

			await Context.Response.WriteAsync($"CURRENT TIME [{CreateTime()}] !");

			if (CachedValue==null)
			{
				StringBuilder									SB=new StringBuilder();

				SB.Append($" TIME [{CreateTime()}] - LONG CALCULATION STARTED !");

				await Task.Delay(5000);

				Random											RND=new Random();
				double											CalculatedValue=RND.NextDouble();

				SB.Append($" TIME [{CreateTime()}] - CALCULATED VALUE [{CalculatedValue}] !");
				SB.Append($" TIME [{CreateTime()}] - LONG CALCULATION FINISHED !");

				TimeSpan										RelativeTime=TimeSpan.FromSeconds(30);

				SB.Append($" TIME [{CreateTime()}] - CACHED for RELATIVE TIME [{RelativeTime} SECONDS] !");

				string											Content=SB.ToString();

				await Context.Response.WriteAsync(Content);

				DistributedCacheEntryOptions					CacheOptions=new DistributedCacheEntryOptions();

				// !!! Nastavi sa RELATIVE CACHE EXPIRATION TIME.
				CacheOptions.AbsoluteExpirationRelativeToNow=RelativeTime;

				// !!! VALUE sa zapise do CACHE.
				await Cache.SetStringAsync(Key,Content,CacheOptions);
			}
			else
			{
				await Context.Response.WriteAsync(CachedValue);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------