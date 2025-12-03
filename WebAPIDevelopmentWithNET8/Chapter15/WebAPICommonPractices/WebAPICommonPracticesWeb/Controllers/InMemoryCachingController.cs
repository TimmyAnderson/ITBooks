using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Caching.Memory;
//----------------------------------------------------------------------------------------------------------------------
namespace WebAPICommonPracticesWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class InMemoryCachingController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									CACHE_RECORD_KEY_1="MyRecord1";
		private const string									CACHE_RECORD_KEY_2="MyRecord2";
		private const string									CACHE_RECORD_KEY_3="MyRecord3";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private readonly IMemoryCache							MCache;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public InMemoryCachingController(IMemoryCache Cache)
		{
			MCache=Cache;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static CMyCachedData CreateCacheRecord(ICacheEntry CacheEntry)
		{
			Random												RND=new Random();
			int													IntValue=RND.Next();

			string												Value=$"VALUE [{IntValue}].";
			DateTime											DateTime=DateTime.Now;

			CMyCachedData										MyCachedData=new CMyCachedData(Value,DateTime);
			
			// !!! Nastavi sa EXPIRATION POLICY [ABSOLUTE EXPIRATION].
			CacheEntry.SetAbsoluteExpiration(TimeSpan.FromSeconds(20));

			return(MyCachedData);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("AbsoluteExpiration")]
		public IActionResult AbsoluteExpiration()
		{
			CMyCachedData										MyCachedData;

			if (MCache.TryGetValue<CMyCachedData>(CACHE_RECORD_KEY_1,out MyCachedData)==true)
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

				MemoryCacheEntryOptions							CacheEntryOptions=new MemoryCacheEntryOptions();

				// !!! Nastavi sa EXPIRATION POLICY [ABSOLUTE EXPIRATION].
				CacheEntryOptions.SetAbsoluteExpiration(TimeSpan.FromSeconds(20));

				// !!! CACHE RECORD sa vlozi do CACHE.
				MCache.Set(CACHE_RECORD_KEY_1,MyCachedData,CacheEntryOptions);

				CMyCacheResponse								Response=new CMyCacheResponse(MyCachedData,false);

				IActionResult									Result=Ok(Response);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("SlidingExpiration")]
		public IActionResult SlidingExpiration()
		{
			CMyCachedData										MyCachedData;

			if (MCache.TryGetValue<CMyCachedData>(CACHE_RECORD_KEY_2,out MyCachedData)==true)
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

				MemoryCacheEntryOptions							CacheEntryOptions=new MemoryCacheEntryOptions();

				// !!! Nastavi sa EXPIRATION POLICY [SLIDING EXPIRATION].
				CacheEntryOptions.SetSlidingExpiration(TimeSpan.FromSeconds(20));

				// !!! Nastavi sa maximalny cas po ktorom sa CACHE RECORD odstrani z CACHE.
				CacheEntryOptions.SetAbsoluteExpiration(TimeSpan.FromSeconds(60));

				// !!! CACHE RECORD sa vlozi do CACHE.
				MCache.Set(CACHE_RECORD_KEY_2,MyCachedData,CacheEntryOptions);

				CMyCacheResponse								Response=new CMyCacheResponse(MyCachedData,false);

				IActionResult									Result=Ok(Response);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetOrCreateInCache")]
		public IActionResult GetOrCreateInCache()
		{
			CMyCachedData										MyCachedData=MCache.GetOrCreate<CMyCachedData>(CACHE_RECORD_KEY_3,CreateCacheRecord);
			CMyCacheResponse									Response=new CMyCacheResponse(MyCachedData,null);
			IActionResult										Result=Ok(Response);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("CleanCache")]
		public IActionResult CleanCache()
		{
			MCache.Remove(CACHE_RECORD_KEY_1);
			MCache.Remove(CACHE_RECORD_KEY_2);
			MCache.Remove(CACHE_RECORD_KEY_3);

			IActionResult										Result=Ok("CACHE CLEANED.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------