using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using ModelBinding.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class PageBindNestedComplexTypeModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChildProvider							MChildProvider;
//----------------------------------------------------------------------------------------------------------------------
		private CChild											MChild;
		private CChildAddress									MChildAddress;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageBindNestedComplexTypeModel(IChildProvider ChildProvider)
		{
			MChildProvider=ChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[BindProperty(SupportsGet=true)]
		public CChild											Child
		{
			get
			{
				return(MChild);
			}
			set
			{
				MChild=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! PROPERTY sluzi na demonstraciu, ze pomocou PROPERTY [Name] je mozne vykonat MODEL BINDING na NESTED TYPE COMPLEX TYPE.
		[BindProperty(Name="Child.Address",SupportsGet=true)]
		public CChildAddress									ChildAddress
		{
			get
			{
				return(MChildAddress);
			}
			set
			{
				MChildAddress=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        public void OnGet()
        {
			MChild=new CChild();
        }
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! POSTFIX 'MyHandler' je definovany pomocou HTML ATTRIBUTE [asp-page-handler].
		public IActionResult OnPostMyHandler()
		{
			// !!! Len kvoli demonstracnym ucelom sa vytvori novy OBJECT s ADDRESS zobratou s PROPERTY 'ChildAddress', aby sa ukazalo, ze tato PROPERTY bola SPRAVNE BOUND.
			// !!!!! Kludne sa mohol pouzit OBJECT z PROPERTY 'Child', pretoze aj ten obsahuje spravne naplnenu ADDRESS.
			CChild												NewChild=new CChild(0,Child.FirstName,Child.LastName,Child.Age,Child.Sex,ChildAddress);

			MChildProvider.AddChild(NewChild);

			IActionResult										Result=RedirectToPage("PageViewChildren");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------