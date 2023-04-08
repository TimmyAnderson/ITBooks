using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Web;
using BlazorForms.Model;
using BlazorForms.Services;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorForms.Blazor.Persons
{
//----------------------------------------------------------------------------------------------------------------------
    public partial class DeletePersonComponent : ComponentBase
    {
//----------------------------------------------------------------------------------------------------------------------
		private IDBOperationsInMemory							MDBOperations;
		private NavigationManager								MNavigationManager;
		private int												MID;
		private CPerson											MPerson;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Inject]
		public IDBOperationsInMemory							DBOperations
		{
			get
			{
				return(MDBOperations);
			}
			set
			{
				MDBOperations=value;
			}
		}
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
		protected override void OnParametersSet()
		{
			// !!! FIELD 'MPerson' sa naplni datami z DB.
			MPerson=MDBOperations.GetPerson(MID);

			// !!!!! Ak VALUE NEEXISTUJE, tak sa spravi navrat na MAIN PAGE.
			if (MPerson==null)
			{
				// !!!!! MUSI sa vytvorit PRAZDNA INSTANCIA, inak BLAZOR COMPONENT hodi UNHANDLED EXCEPTION.
				MPerson=new CPerson();

				// !!! Vykona sa NAVIGATION na URL '/ViewPersons'.
				MNavigationManager.NavigateTo("/ViewPersons");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void DeletePerson(MouseEventArgs E)
		{
			// !!! Vykona sa DELETE RECORD z DB.
			MDBOperations.RemovePerson(MID);

			// !!! Vykona sa NAVIGATION na URL '/ViewPersons'.
			MNavigationManager.NavigateTo("/ViewPersons");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------