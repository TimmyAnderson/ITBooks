using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Web;
using SharedClasses.Classes;
using BlazorApplication.Services;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorApplication.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
    public partial class AddPersonComponent : ComponentBase
    {
//----------------------------------------------------------------------------------------------------------------------
		private NavigationManager								MNavigationManager;
		// !!!!! VALUE MUSI byt INICIALIZOVANA inak dojde k UNHANDLED EXCEPTION.
		private CPerson											MPerson=new CPerson();
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Inject]
		public NavigationManager								NavigationManager
		{
			get
			{
				return(MNavigationManager);
			}
			set
			{
				MNavigationManager=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CPerson											Person
		{
			get
			{
				return(MPerson);
			}
			set
			{
				MPerson=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task HandleValidSubmit()
		{
			// !!! Vykona sa INSERT RECORD v DB.
			await CWebClientService.AddPerson(MPerson);

			// !!! Vykona sa NAVIGATION na URL 'ViewPersons'.
			MNavigationManager.NavigateTo("ViewPersons");
		}
//----------------------------------------------------------------------------------------------------------------------
		public void HandleInvalidSubmit()
		{
			// EMPTY.
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------