using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using AdvancedControllersAndViews.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedControllersAndViews.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class TestController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameRepository						MNameRepository;
//----------------------------------------------------------------------------------------------------------------------
		private string											MLastName;
		private int												MAge;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public TestController(INameRepository NameRepository)
		{
			MNameRepository=NameRepository;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY je sucastou TEMP DATA.
		[TempData]
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
			set
			{
				MLastName=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY je sucastou TEMP DATA.
		[TempData]
		public int												Age
		{
			get
			{
				return(MAge);
			}
			set
			{
				MAge=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseViewBag()
		{
			// !!! MODEL obsahuje DATA, ktore ma VIEW zobrazit.
			CName[]												Names=MNameRepository.GetNames();

			// !!! Pomocou [ViewBag] je mozne prenasat do VIEWS lubovolne data.
			ViewBag.TableClass="table table-bordered table-striped";

			// !!! Zobrazi sa VIEW.
			IActionResult										Result=View("UseViewBag",Names);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Zobrazi sa FORM, kde je mozne zadat NAME.
		public IActionResult UseTempDataEdit()
		{
			CName												Name=new CName();
			IActionResult										Result=View("UseTempDataEdit",Name);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Spravi sa REDIRECT, pricom na prenos dat sa pouzije TEMP DATA.
		public IActionResult UseTempDataEditCallback(CName Name)
		{
			// !!! Do TEMP DATA sa ulozia jednotlive PROPERTIES NAME.
			TempData["FirstName"]=Name.FirstName;

			// !!! TEMP DATA su ulozene do TEMP DATA PROPERTIES.
			LastName=Name.LastName;
			Age=Name.Age;

			TempData["Sex"]=Name.Sex;

			IActionResult										Result=RedirectToAction("UseTempDataView");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Zobrazi sa VIEW s datami nacitanymi z TEMP DATA.
		public IActionResult UseTempDataView()
		{
			// NAME PROPERTIES na nacitaju z TEMP DATA.
			string												FirstName=(string) TempData["FirstName"];

			// !!! TEMP DATA su ulozene do TEMP DATA PROPERTIES.
			string												LastName=this.LastName;
			int													Age=this.Age;

			ESex												Sex=(ESex) TempData["Sex"];
			CName												Name=new CName(0,FirstName,LastName,Age,Sex);
			IActionResult										Result=View("UseTempDataView",Name);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------