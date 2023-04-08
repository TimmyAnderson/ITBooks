using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace TestExceptionHandler.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CThrowUnhandledExcepionEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public static Task Endpoint(HttpContext Context)
		{
			// !!! Umyselne sa generuje UNHANDLED EXCEPTION.
			throw(new InvalidOperationException("SOMETHING BAD HAPPENED !!!"));
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------