using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using StartingWithNetCore.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace StartingWithNetCore.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class ShowContentController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private static string CreateTime()
		{
			DateTime											Time=DateTime.Now;
			string												TextTime=$"{Time.Hour.ToString("00")}:{Time.Minute.ToString("00")}:{Time.Second.ToString("00")}.{Time.Millisecond.ToString("000")}";

			return(TextTime);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowStaticContent()
		{
			IActionResult										Result=View("ShowStaticContent");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowDynamicContent()
		{
			CTime												Model=new CTime(CreateTime());
			IActionResult										Result=View("ShowDynamicContent",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------