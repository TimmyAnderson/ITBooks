using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using SharedClasses.Classes;
using BlazorApplication.Services;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorApplication.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
    public partial class EditPersonComponent : ComponentBase
    {
//----------------------------------------------------------------------------------------------------------------------
		private NavigationManager								MNavigationManager;
		private int												MID;
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
		[Parameter]
		public int												ID
		{
			get
			{
				return(MID);
			}
			set
			{
				MID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Ak FIELD 'MPerson' NEBOL inicializovany v CONSTRUCTOR na PRAZDNU INSTANCIU CLASS 'CPerson', tak PROGRAM hodil UNHANDLED EXCEPTION.
		protected async override Task OnParametersSetAsync()
		{
			// !!! FIELD 'MPerson' sa naplni datami z DB.
			MPerson=await CWebClientService.GetPerson(MID);

			// !!!!! Ak VALUE NEEXISTUJE, tak sa spravi navrat na MAIN PAGE.
			if (MPerson==null)
			{
				// !!!!! MUSI sa vytvorit PRAZDNA INSTANCIA, inak BLAZOR COMPONENT hodi UNHANDLED EXCEPTION.
				MPerson=new CPerson();

				// !!! Vykona sa NAVIGATION na URL 'ViewPersons'.
				MNavigationManager.NavigateTo("ViewPersons");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task HandleValidSubmit()
		{
			// !!! Vykona sa UPDATE RECORD v DB.
			await CWebClientService.UpdatePerson(MPerson);

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