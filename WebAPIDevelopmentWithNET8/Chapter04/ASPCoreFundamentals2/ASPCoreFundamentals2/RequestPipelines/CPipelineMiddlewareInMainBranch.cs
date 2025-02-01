using System;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals2
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CPipelineMiddlewareInMainBranch
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task MyMiddlewareInMainBranch(HttpContext Context, RequestDelegate NextMiddleware)
		{
			Console.WriteLine("MIDDLEWARE [MyMiddlewareInMainBranch] - START.");

			await NextMiddleware(Context);

			Console.WriteLine("MIDDLEWARE [MyMiddlewareInMainBranch] - END.");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------