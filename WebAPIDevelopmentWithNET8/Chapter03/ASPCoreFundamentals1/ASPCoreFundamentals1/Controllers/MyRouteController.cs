using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals1
{
//----------------------------------------------------------------------------------------------------------------------
    [ApiController]
    [Route("[controller]")]
	// !!! CONTROLLERS a ACTION METHODS mozu mat aj VIACERO ROUTES.
    [Route("[controller]/Alternative")]
    public class MyRouteController : ControllerBase
    {
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet]
		[Route("Value1")]
        public string GetValue1()
        {
			return("This is VALUE 1.");
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet]
		[Route("Value2")]
		[Route("Value2/Alternative")]
        public string GetValue2()
        {
			return("This is VALUE 2.");
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("Route/{ID}/Parameter")]
        public string GetValueRouteParameter(string ID)
        {
			return($"This is VALUE [{ID}].");
        }
//----------------------------------------------------------------------------------------------------------------------
		// !!! CONSTRAINT NIE je aplikovany. Ak sa zasle NON-INTEGER VALUE, ASP.NET CORE vrati HTTP RESPONSE STATUS CODE [400].
        [HttpGet("{ID}/NoConstraint")]
        public string GetValueNoConstraint(int ID)
        {
			return($"This is VALUE [{ID}].");
        }
//----------------------------------------------------------------------------------------------------------------------
		// !!! CONSTRAINT NIE je aplikovany. Ak sa zasle NON-INTEGER VALUE, ASP.NET CORE vrati HTTP RESPONSE STATUS CODE [404].
        [HttpGet("{ID:int}/SingleConstraint")]
        public string GetValueSingleConstraint(int ID)
        {
			return($"This is VALUE [{ID}].");
        }
//----------------------------------------------------------------------------------------------------------------------
		// !!! Aplikuje sa viacero CONSTRAINTS.
        [HttpGet("{ID:int:min(10):max(20)}/MultipleConstraints")]
        public string GetValueMultipleConstraints(int ID)
        {
			return($"This is VALUE [{ID}].");
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpPost("{FromURLRoute:int}/Binding1")]
		// !!! Na PARAMETERS nie je potrebne aplikovat BINDING ATTRIBUTES, pretoze tie su INFERRED.
        public string GetValueBinding1(int FromURLRoute, string FromQueryString, CName Name)
        {
			return($"FROM URL ROUTE [{FromURLRoute}]. FROM QUERY STRING [{FromQueryString}]. NAME.FirstName [{Name.FirstName}] NAME.LastName [{Name.LastName}] NAME.Age [{Name.Age}].");
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpPost("{FromURLRoute:int}/Binding2")]
        public string GetValueBinding2([FromRoute] int FromURLRoute, [FromQuery] string FromQueryString, [FromBody] CName Name)
        {
			return($"FROM URL ROUTE [{FromURLRoute}]. FROM QUERY STRING [{FromQueryString}]. NAME.FirstName [{Name.FirstName}] NAME.LastName [{Name.LastName}] NAME.Age [{Name.Age}].");
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------