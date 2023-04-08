using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using UsingFormTagHelpers.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBuiltInTagHelpers.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class UseInputTagHelpersController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
		private readonly IPersonProvider						MPersonProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public UseInputTagHelpersController(INameProvider NameProvider, IPersonProvider PersonProvider)
		{
			MNameProvider=NameProvider;
			MPersonProvider=PersonProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseInputAttributes()
		{
			ViewResult											Result=View("UseInputAttributes");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult UseInputAttributesCallback(CName Name)
		{
			MNameProvider.AddName(Name);

			CName[]												Model=MNameProvider.GetNames();
			IActionResult										Result=View("ViewNames",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseFormattedInput()
		{
			// !!! Umyselne sa nastavi MODEL OBJECT, aby sa demonstrovala funkcionalita FORMATTING.
			CPerson												Model=new CPerson(0,"Josh","Hurt",12,5649873,1.48);
			ViewResult											Result=View("UseFormattedInput",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Kedze VALUE 'Psi' je FORMATTED INTEGER obsahujuci znaky ',', standardne ho ASP.NET NEVIE PARSOVAT ako INTEGER. Preto ho je NUTNE prenasat ako STRING a nasledne ho MANUALNE PARSOVAT.
		[HttpPost]
		public IActionResult UseFormattedInputCallback(string FirstName, string LastName, int Age, string Psi, double Height)
		{
			string												ModifiedPsi=Psi.Replace(",","");
			double												DoubelePsi=double.Parse(ModifiedPsi);
			int													IntPsi=(int) DoubelePsi;
			CPerson												Person=new CPerson(0,FirstName,LastName,Age,IntPsi,Height);

			MPersonProvider.AddPerson(Person);

			CPerson[]											Model=MPersonProvider.GetPersons();
			IActionResult										Result=View("ViewPersons",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------