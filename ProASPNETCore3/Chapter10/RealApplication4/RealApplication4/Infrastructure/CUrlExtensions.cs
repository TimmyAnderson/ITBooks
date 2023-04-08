using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication4.Infrastructure
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CUrlExtensions
	{
//----------------------------------------------------------------------------------------------------------------------
		public static string PathAndQuery(this HttpRequest Request)
		{
			if (Request.QueryString.HasValue==true)
			{
				string											PathAndQuery=$"{Request.Path}{Request.QueryString}";

				return(PathAndQuery);
			}
			else
			{
				string											PathAndQuery=Request.Path.ToString();

				return(PathAndQuery);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------