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
    public partial class ViewPersonsComponent : ComponentBase
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! VALUE MUSI byt INICIALIZOVANA inak dojde k UNHANDLED EXCEPTION.
		private CPerson[]										MPersons=new CPerson[0];
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPerson[]										Persons
		{
			get
			{
				return(MPersons);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Ak FIELD 'MPersons' NEBOL inicializovany v CONSTRUCTOR na PRAZDNU INSTANCIU CLASS 'CPerson[]', tak PROGRAM hodil UNHANDLED EXCEPTION.
		protected async override Task OnParametersSetAsync()
		{
			MPersons=await CWebClientService.GetPersons();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string GetAddPersonLink()
		{
			string												Link=$"AddPerson";

			return(Link);
		}
//----------------------------------------------------------------------------------------------------------------------
		public string GetEditPersonLink(CPerson Person)
		{
			string												Link=$"EditPerson/{Person.ID}";

			return(Link);
		}
//----------------------------------------------------------------------------------------------------------------------
		public string GetDeletePersonLink(CPerson Person)
		{
			string												Link=$"DeletePerson/{Person.ID}";

			return(Link);
		}
//----------------------------------------------------------------------------------------------------------------------
		public string GetViewPersonDetailsLink(CPerson Person)
		{
			string												Link=$"ViewPersonDetails/{Person.ID}";

			return(Link);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------