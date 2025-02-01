using System;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals2
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CPipelineShortCircuitsMiddlewareComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task ShortCircuitsMiddlewareComponent(HttpContext Context)
		{
			string												MethodName=nameof(ShortCircuitsMiddlewareComponent);

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - START.");

			// !!! Vytvori sa HTTP RESPONSE MESSAGE.
			Context.Response.Headers["Content-Type"]="text/plain;charset=utf-8";

			await Context.Response.WriteAsync($"RESPONSE from SHORT CIRCUIT MIDDLEWARE [{MethodName}].");

			Console.WriteLine($"MIDDLEWARE [{MethodName}] - STOP.");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------