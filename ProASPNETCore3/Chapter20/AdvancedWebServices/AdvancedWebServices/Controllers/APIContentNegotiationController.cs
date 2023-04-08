using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using AdvancedWebServices.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedWebServices.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	[Route("api/[controller]")]
	public class APIContentNegotiationController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Pri pouziti DEFAULT CONTENT POLICY CONFIGURATION je OBJECT TYPE [string] vrateny ako PLAIN TEXT.
		[HttpGet("ReturnString")]
		public string ReturnString()
		{
			return("My name is TIMMY ANDERSON !");
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pri pouziti DEFAULT CONTENT POLICY CONFIGURATION je OBJECT TYPE [int] vrateny ako JSON.
		[HttpGet("ReturnInt")]
		public int ReturnInt()
		{
			return(100);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pri pouziti DEFAULT CONTENT POLICY CONFIGURATION je OBJECT TYPE [CName] vrateny ako JSON.
		[HttpGet("ReturnName")]
		public CName ReturnName()
		{
			return(new CName(0,"Timmy","Anderson",12));
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! VZDY generuje JSON OBJECT.
		[HttpGet("ReturnNameProducesJSON")]
		[Produces("application/json")]
		public CName ReturnNameProducesJSON()
		{
			return(new CName(0,"Timmy","Anderson",12));
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! VZDY generuje XML.
		[HttpGet("ReturnNameProducesXML")]
		[Produces("application/xml")]
		public CName ReturnNameProducesXML()
		{
			return(new CName(0,"Timmy","Anderson",12));
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ROUTE obsahuje ako OPTIONAL VARIABLE ROUTE VARIABLE [{Format}], ktora ked je nastavena, tak urcuje aky FORMAT sa ma POUZIT na formatovanie CONTENT HTTP RESPOSNE.
		// !!!!! V pripade, ze ROUTE VARIABLE [{Format}] nebola nastavena, FILTER [FormatFilterFilter] kontroluje ci QUERY STRING NEOBSAHUJE PARAMETER [Format]. Ak ako, tak jeho hodnota urcuje aky FORMAT sa ma POUZIT na formatovanie CONTENT HTTP RESPOSNE.
		// !!!!! Hodnoty ROUTE VARIABLE [{Format}], alebo QUERY STRING PARAMETER [Format] MUSIA mat mapovanie v STARTUP CLASS.
		[HttpGet("ReturnNameFormatThroughRouteOrQueryString/{Format?}")]
		[FormatFilter]
		public CName ReturnNameFormatThroughRouteOrQueryString()
		{
			return(new CName(0,"Timmy","Anderson",12));
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! HTTP POST ACTION METHOD akceptuje HTTP REQUEST CONTENT, ktory je FORMATTED ako JSON.
		[HttpPost]
		[Consumes("application/json")]
		public CName ReceiveJSON([FromBody] CName Name)
		{
			return(Name);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! HTTP POST ACTION METHOD akceptuje HTTP REQUEST CONTENT, ktory je FORMATTED ako XML.
		[HttpPost]
		[Consumes("application/xml")]
		public CName ReceiveXML([FromBody] CName Name)
		{
			return(Name);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------