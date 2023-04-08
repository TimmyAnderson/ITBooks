using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Newtonsoft.Json;
//-----------------------------------------------------------------------------
namespace RealApplication4.Infrastructure
{
//-----------------------------------------------------------------------------
	public static class CSessionExtensions
	{
//-----------------------------------------------------------------------------
		public static void SetJson(this ISession Session, string Key, object Value)
		{
            Session.SetString(Key,JsonConvert.SerializeObject(Value));
		}
//-----------------------------------------------------------------------------
		public static TType GetJson<TType>(this ISession Session, string Key)
		{
			string												SessionData=Session.GetString(Key);

			if (SessionData==null)
			{
				return(default(TType));
			}
			else
			{
				TType											Value=JsonConvert.DeserializeObject<TType>(SessionData);

				return(Value);
			}
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------