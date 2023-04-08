using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Web;
using BlazorForms.Model;
using BlazorForms.Services;
using BlazorForms.Database;
using Microsoft.EntityFrameworkCore;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorForms.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! BLAZOR COMPONENT demonstruje OPRAVU ERROR, ktoru demonstruje BLAZOR COMPONENT [ErrorEditPersonComponent].
    public partial class FixDisposeErrorEditPersonComponent : ComponentBase, IDisposable
    {
//----------------------------------------------------------------------------------------------------------------------
		private IDBOperations									MDBOperations;
		private NavigationManager								MNavigationManager;
		private int												MID;
		// !!!!! Zobrazuje sa ENTITY OBJECT, ktory sa nacita priamo z DB.
		private CEntityPerson									MPerson;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Inject]
		public IDBOperations									DBOperations
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
		// !!!!! Zobrazuje sa ENTITY OBJECT, ktory sa nacita priamo z DB.
		public CEntityPerson									Person
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
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void HandleValidSubmit()
		{
			// !!! Vykona sa UPDATE RECORD v DB.
			MDBOperations.UpdatePerson(MPerson);

			// !!! Vykona sa NAVIGATION na URL '/ErrorViewPersons'.
			MNavigationManager.NavigateTo("/ErrorViewPersons");
		}
//----------------------------------------------------------------------------------------------------------------------
		public void HandleInvalidSubmit()
		{
			// EMPTY.
		}
//----------------------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			// !!!!! Uvolnia sa zmeny vykonane nad ENTITY OBJECT, ak ten NEBOL zapisany do DB.
			MDBOperations.Context.Entry(MPerson).State=EntityState.Detached;
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------