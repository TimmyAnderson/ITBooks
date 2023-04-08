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
    public partial class ViewPersonDetailsComponent : ComponentBase
    {
//----------------------------------------------------------------------------------------------------------------------
		private int												MID;
		// !!!!! VALUE MUSI byt INICIALIZOVANA inak dojde k UNHANDLED EXCEPTION.
		private CPerson											MPerson=new CPerson();
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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
		// !!!!! Ak FIELD 'MPersons' NEBOL inicializovany v CONSTRUCTOR na PRAZDNU INSTANCIU CLASS 'CPerson[]', tak PROGRAM hodil UNHANDLED EXCEPTION.
		protected async override Task OnParametersSetAsync()
		{
			// !!! FIELD 'MPerson' sa naplni datami z DB.
			MPerson=await CWebClientService.GetPerson(MID);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------