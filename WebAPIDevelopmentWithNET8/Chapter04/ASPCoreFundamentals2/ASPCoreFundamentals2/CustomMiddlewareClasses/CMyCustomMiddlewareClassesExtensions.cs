using System;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals2
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CMyCustomMiddlewareClassesExtensions
	{
//----------------------------------------------------------------------------------------------------------------------
		public static IApplicationBuilder UseMyCustomMiddlewareClasses(this IApplicationBuilder Builder)
		{
			// !!! Prida sa CUSTOM MIDDLEWARE COMPONENT CLASS do REQUEST PIPELINE.
			IApplicationBuilder									Result=Builder.UseMiddleware<CMyCustomMiddlewareClasses>();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------