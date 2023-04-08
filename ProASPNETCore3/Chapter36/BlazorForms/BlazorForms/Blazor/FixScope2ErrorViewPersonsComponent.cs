using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Web;
using Microsoft.Extensions.DependencyInjection;
using BlazorForms.Model;
using BlazorForms.Database;
using BlazorForms.Services;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorForms.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! BLAZOR COMPONENT je DERIVED z CLASS [OwningComponentBase<IDBOperations>], vdaka comu ziska pristup k DEPENDENCY INJECTION FRAMEWORK.
    public partial class FixScope2ErrorViewPersonsComponent : OwningComponentBase<IDBOperations>
    {
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
		public CEntityPerson[]									Persons
		{
			get
			{
				CEntityPerson[]									Value=DBOperations.GetPersons();

				return(Value);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string GetEditPersonLinkScopeFix2(CEntityPerson Person)
		{
			string												Link=$"/FixScope2ErrorEditPerson/{Person.ID}";

			return(Link);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------