using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using ModelBinding.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class ManualBindingController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChildProvider							MChildProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ManualBindingController(IChildProvider ChildProvider)
		{
			MChildProvider=ChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult AddName()
		{
			ViewResult											Result=View("EditChild");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult EditChildCallback()
		{
			// !!! Vytvori sa instancia OBJECT do ktorej sa bude robit MANUAL BINDING.
			CChild												Child=new CChild();

			// !!! Vykona sa MANUAL BINDING CLASS 'CChild'.
			// !!!!! MANUAL BINDING NEPODPORUJE BINDING CHAINED PROPERTIES ako napriklad 'P.Address.Country' a preto PROPERTY 'Address' musi byt BOUND OSOBITNE.
			TryUpdateModelAsync<CChild>(Child,"",P => P.ID,P => P.FirstName,P => P.LastName,P => P.Age,P => P.Sex).Wait();

			// !!! Vytvori sa instancia OBJECT do ktorej sa bude robit MANUAL BINDING.
			Child.Address=new CChildAddress();

			// !!! Vykona sa MANUAL BINDING CLASS 'CChildAddress'.
			TryUpdateModelAsync<CChildAddress>(Child.Address,"Address",P => P.City,P => P.Country).Wait();

			MChildProvider.AddChild(Child);

			IActionResult										Result=RedirectToAction("ShowNames");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult ShowNames()
		{
			CChild[]											Model=MChildProvider.GetChildren();
			ViewResult											Result=View("ViewChildren",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------