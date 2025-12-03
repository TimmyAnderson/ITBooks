using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Caching.Distributed;
using Microsoft.Extensions.Caching.Memory;
//----------------------------------------------------------------------------------------------------------------------
namespace WebAPICommonPracticesWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class DistributedCachingController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									CACHE_RECORD_KEY_1="MyRecord1";
		private const string									CACHE_RECORD_KEY_2="MyRecord2";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private readonly IDistributedCache						MCache;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public DistributedCachingController(IDistributedCache Cache)
		{
			MCache=Cache;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private CMyCachedData GetCachedData(string Key)
		{
			string												SerializedCachedData=MCache.GetString(Key);

			if (SerializedCachedData!=null)
			{
				CMyCachedData									CachedData=JsonSerializer.Deserialize<CMyCachedData>(SerializedCachedData);

				return(CachedData);
			}

			return(null);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void SetCachedData(string Key, CMyCachedData CachedData, DistributedCacheEntryOptions Options)
		{
			string												SerializedCachedData=JsonSerializer.Serialize(CachedData);

			MCache.SetString(Key,SerializedCachedData,Options);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("AbsoluteExpiration")]
		public IActionResult AbsoluteExpiration()
		{
			CMyCachedData										MyCachedData=GetCachedData(CACHE_RECORD_KEY_1);

			if (MyCachedData!=null)
			{
				CMyCacheResponse								Response=new CMyCacheResponse(MyCachedData,true);
				IActionResult									Result=Ok(Response);

				return(Result);
			}
			else
			{
				Random											RND=new Random();
				int												IntValue=RND.Next();

				string											Value=$"VALUE [{IntValue}].";
				DateTime										DateTime=DateTime.Now;

				MyCachedData=new CMyCachedData(Value,DateTime);

				DistributedCacheEntryOptions					CacheEntryOptions=new DistributedCacheEntryOptions();

				// !!! Nastavi sa EXPIRATION POLICY [ABSOLUTE EXPIRATION].
				CacheEntryOptions.SetAbsoluteExpiration(TimeSpan.FromSeconds(60));

				// !!! CACHE RECORD sa vlozi do CACHE.
				SetCachedData(CACHE_RECORD_KEY_1,MyCachedData,CacheEntryOptions);

				CMyCacheResponse								Response=new CMyCacheResponse(MyCachedData,false);

				IActionResult									Result=Ok(Response);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("SlidingExpiration")]
		public IActionResult SlidingExpiration()
		{
			CMyCachedData										MyCachedData=GetCachedData(CACHE_RECORD_KEY_2);

			if (MyCachedData!=null)
			{
				CMyCacheResponse								Response=new CMyCacheResponse(MyCachedData,true);
				IActionResult									Result=Ok(Response);

				return(Result);
			}
			else
			{
				Random											RND=new Random();
				int												IntValue=RND.Next();

				string											Value=$"VALUE [{IntValue}].";
				DateTime										DateTime=DateTime.Now;

				MyCachedData=new CMyCachedData(Value,DateTime);

				DistributedCacheEntryOptions					CacheEntryOptions=new DistributedCacheEntryOptions();
				
				// !!! Nastavi sa EXPIRATION POLICY [SLIDING EXPIRATION].
				CacheEntryOptions.SetSlidingExpiration(TimeSpan.FromSeconds(60));

				// !!! Nastavi sa maximalny cas po ktorom sa CACHE RECORD odstrani z CACHE.
				CacheEntryOptions.SetAbsoluteExpiration(TimeSpan.FromSeconds(180));

				// !!! CACHE RECORD sa vlozi do CACHE.
				SetCachedData(CACHE_RECORD_KEY_2,MyCachedData,CacheEntryOptions);

				CMyCacheResponse								Response=new CMyCacheResponse(MyCachedData,false);

				IActionResult									Result=Ok(Response);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("CleanCache")]
		public IActionResult CleanCache()
		{
			MCache.Remove(CACHE_RECORD_KEY_1);
			MCache.Remove(CACHE_RECORD_KEY_2);

			IActionResult										Result=Ok("CACHE CLEANED.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------