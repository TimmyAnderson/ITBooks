using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Authorization;
using Microsoft.AspNetCore.Components.Rendering;
using Microsoft.AspNetCore.Components.Web;
using Microsoft.AspNetCore.Identity;
using ApplyingCoreIdentity.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace ApplyingCoreIdentity.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! K BLAZOR COMPONENT maju pristu USERS, ktori su clenmi ROLE 'Administrators'.
	[Authorize(Roles="Administrators")]
	public partial class AllowAdministratorsCounterComponent : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [AuthenticationStateProvider] poskytuje informaciu o AUTHENTICATED USER.
		private AuthenticationStateProvider						MAuthenticationState;
		private string											MUserName;
		private int												MCounter=1;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Inject]
		public AuthenticationStateProvider						AuthenticationState
		{
			get
			{
				return(MAuthenticationState);
			}
			set
			{
				MAuthenticationState=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											UserName
		{
			get
			{
				return(MUserName);
			}
			set
			{
				MUserName=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												Counter
		{
			get
			{
				return(MCounter);
			}
			set
			{
				MCounter=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected async override Task OnInitializedAsync()
		{
			ClaimsPrincipal										Principal=(await MAuthenticationState.GetAuthenticationStateAsync()).User;

			if (Principal!=null)
			{
				if (Principal.Identity!=null)
				{
					MUserName=Principal.Identity.Name;
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void IncrementCounter(MouseEventArgs E)
		{
			MCounter++;
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------