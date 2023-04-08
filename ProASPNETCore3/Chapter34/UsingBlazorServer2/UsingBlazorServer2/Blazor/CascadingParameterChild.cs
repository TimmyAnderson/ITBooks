using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBlazorServer2.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	public partial class CascadingParameterChild : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MText="UNSPECIFIED";
		private string											MTheme="";
		private string											MTextAlignment="";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public string											Text
		{
			get
			{
				return(MText);
			}
			set
			{
				MText=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER sa nastavi ako CASCADING PARAMETER, ktoreho VALUE sa bude brat z HTML ELEMENT [<CascadingValue>].
		[CascadingParameter(Name="ChildTheme")]
		public string											Theme
		{
			get
			{
				return(MTheme);
			}
			set
			{
				MTheme=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER sa nastavi ako CASCADING PARAMETER, ktoreho VALUE sa bude brat z HTML ELEMENT [<CascadingValue>].
		[CascadingParameter(Name="ChildTextAlignment")]
		public string											TextAlignment
		{
			get
			{
				return(MTextAlignment);
			}
			set
			{
				MTextAlignment=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------