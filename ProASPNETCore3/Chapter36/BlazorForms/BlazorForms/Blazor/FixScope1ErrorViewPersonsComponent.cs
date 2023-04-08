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
	// !!!!! BLAZOR COMPONENT je DERIVED z CLASS [OwningComponentBase], vdaka comu ziska pristup k DEPENDENCY INJECTION FRAMEWORK.
    public partial class FixScope1ErrorViewPersonsComponent : OwningComponentBase
    {
//----------------------------------------------------------------------------------------------------------------------
		public IDBOperations									DBOperations
		{
			get
			{
				// !!!!! ENTITY FRAMEWORK CONTEXT OBJECT sa ziska EXPLICITNE z DEPENDENCY INJECTION FRAMEWORK a ma SCOPED LIFETIME.
				IDBOperations									Service=ScopedServices.GetService<IDBOperations>();

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
		public string GetEditPersonLinkScopeFix1(CEntityPerson Person)
		{
			string												Link=$"/FixScope1ErrorEditPerson/{Person.ID}";

			return(Link);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------