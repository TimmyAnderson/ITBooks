using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public enum EMyHttpClientHttpMethod
	{
//--------------------------------------------------------------------------------------------------------------------------------
		E_GET=1,
		E_POST=2,
		E_PUT=3,
		E_DELETE=4,
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
	public static class CMyHttpClientHttpMethodExtensions
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public static HttpMethod EXT_ConvertHttpMethod(this EMyHttpClientHttpMethod Method)
		{
			if (Method==EMyHttpClientHttpMethod.E_GET)
			{
				return(HttpMethod.Get);
			}
			else if (Method==EMyHttpClientHttpMethod.E_POST)
			{
				return(HttpMethod.Post);
			}
			else if (Method==EMyHttpClientHttpMethod.E_PUT)
			{
				return(HttpMethod.Put);
			}
			else if (Method==EMyHttpClientHttpMethod.E_DELETE)
			{
				return(HttpMethod.Delete);
			}
			else
			{
				throw(new InvalidOperationException($"UNSUPPORTED METHOD [{Method}]."));
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public static string EXT_ToString(this EMyHttpClientHttpMethod Method)
		{
			if (Method==EMyHttpClientHttpMethod.E_GET)
			{
				return("GET");
			}
			else if (Method==EMyHttpClientHttpMethod.E_POST)
			{
				return("POST");
			}
			else if (Method==EMyHttpClientHttpMethod.E_PUT)
			{
				return("PUT");
			}
			else if (Method==EMyHttpClientHttpMethod.E_DELETE)
			{
				return("DELETE");
			}
			else
			{
				throw(new InvalidOperationException($"UNSUPPORTED METHOD [{Method}]."));
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------