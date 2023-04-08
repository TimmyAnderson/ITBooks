using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using ModelBinding.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class BindAttribute1Controller : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult EditChild()
		{
			ViewResult											Result=View("EditChild");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY s PREFIX 'CChild.ID' je MAPPED na VARIABLE 'SuperID'.
		// !!! PROPERTY s PREFIX 'CChild.FirstName' je MAPPED na VARIABLE 'SuperFirstName'.
		// !!! PROPERTY s PREFIX 'CChild.LastName' je MAPPED na VARIABLE 'SuperLastName'.
		// !!! PROPERTY s PREFIX 'CChild.Age' je MAPPED na VARIABLE 'SuperAge'.
		// !!! PROPERTY s PREFIX 'CChild.Sex' je MAPPED na VARIABLE 'SuperSex'.
		// !!! PROPERTIES s PREFIX 'CChild.Address' su MAPPED na PROPERTIES CLASS 'CSuperChildAddress'.
		[HttpPost]
		public IActionResult EditChildCallback([Bind(Prefix=nameof(CChild.ID))] int SuperID, [Bind(Prefix=nameof(CChild.FirstName))] string SuperFirstName, [Bind(Prefix=nameof(CChild.LastName))] string SuperLastName, [Bind(Prefix=nameof(CChild.Age))] int SuperAge, [Bind(Prefix=nameof(CChild.Sex))] ESex SuperSex, [Bind(Prefix=nameof(CChild.Address))] CSuperChildAddress SuperAddress)
		{
			CSuperChild											Model=new CSuperChild(SuperID,SuperFirstName,SuperLastName,SuperAge,SuperSex,SuperAddress);
			ViewResult											Result=View("ViewSuperChild",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------