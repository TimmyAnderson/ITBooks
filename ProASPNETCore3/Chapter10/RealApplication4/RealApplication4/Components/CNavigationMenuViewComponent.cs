using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using RealApplication4.Models;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication4.Components
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! VIEW COMPONENTS su DERIVED z CLASS [ViewComponent].
	public sealed class CNavigationMenuViewComponent : ViewComponent
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IStoreRepository						MStoreRepository;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CNavigationMenuViewComponent(IStoreRepository StoreRepository)
		{
			MStoreRepository=StoreRepository;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vracia CONTENT, ktory VIEW COMPONENT zobrazuje.
		public IViewComponentResult Invoke()
		{
			// !!! Z ROUTE DATA sa vycita VALUE ROUTE VARIABLE 'Category'.
			ViewBag.SelectedCategory=RouteData?.Values["Category"];

			string[]											Categories=MStoreRepository.Products.Select(P => P.Category).Distinct().OrderBy(P => P).ToArray();
			IViewComponentResult 								Result=View("CategoryView",Categories);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------