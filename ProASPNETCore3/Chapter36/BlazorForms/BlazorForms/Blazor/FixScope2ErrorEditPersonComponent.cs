using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Web;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using BlazorForms.Model;
using BlazorForms.Services;
using BlazorForms.Database;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorForms.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! BLAZOR COMPONENT demonstruje OPRAVU ERROR, ktoru demonstruje BLAZOR COMPONENT [ErrorEditPersonComponent].
	// !!!!! BLAZOR COMPONENT je DERIVED z CLASS [OwningComponentBase<IDBOperations>], vdaka comu ziska pristup k DEPENDENCY INJECTION FRAMEWORK.
    public partial class FixScope2ErrorEditPersonComponent : OwningComponentBase<IDBOperations>
    {
//----------------------------------------------------------------------------------------------------------------------
		private NavigationManager								MNavigationManager;
		private int												MID;
		// !!!!! Zobrazuje sa ENTITY OBJECT, ktory sa nacita priamo z DB.
		private CEntityPerson									MPerson;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IDBOperations									DBOperations
		{
			get
			{
				// !!!!! ENTITY FRAMEWORK CONTEXT OBJECT sa ziska EXPLICITNE z BASE CLASS a ma SCOPED LIFETIME.
				return(Service);
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
			MPerson=DBOperations.GetPerson(MID);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void HandleValidSubmit()
		{
			// !!! Vykona sa UPDATE RECORD v DB.
			DBOperations.UpdatePerson(MPerson);

			// !!! Vykona sa NAVIGATION na URL '/FixScope2ErrorViewPersons'.
			MNavigationManager.NavigateTo("/FixScope2ErrorViewPersons");
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