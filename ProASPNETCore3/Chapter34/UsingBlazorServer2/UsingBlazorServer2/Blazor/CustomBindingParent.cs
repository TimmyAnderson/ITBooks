using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Web;
using UsingBlazorServer2.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBlazorServer2.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	public partial class CustomBindingParent : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private IChildProvider									MChildProvider;
		private string											MSelectedSex="";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Inject]
		public IChildProvider									ChildProvider
		{
			get
			{
				return(MChildProvider);
			}
			set
			{
				MChildProvider=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CChild[]											Children
		{
			get
			{
				CChild[]										Value=MChildProvider.GetChildren();

				return(Value);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Tato PROPERTY PARENT BLAZOR COMPONENT je BOUND na PROPERTY 'SelectedValue' CHILD BLAZOR COMPONENT.
		public string											SelectedSex
		{
			get
			{
				return(MSelectedSex);
			}
			set
			{
				MSelectedSex=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string[] GetSexes()
		{
			string[]											Sexes=Enum.GetNames(typeof(ESex));

			return(Sexes);
		}
//----------------------------------------------------------------------------------------------------------------------
		public string GetClass(ESex Sex)
		{
			if (Sex.ToString()==MSelectedSex)
			{
				return("bg-info text-white");
			}
			else
			{
				return("");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void SetSexToMale(MouseEventArgs E)
		{
			// !!! Zmeni sa VALUE C# PROPERTY PARENT BLAZOR COMPONENT, ktora je BOUND na C# PROPERTY CHILD BLAZOR COMPONENT.
			// !!!!! Zmena VALUE C# PROPERTY PARENT BLAZOR COMPONENT sposobi AUTOMATICKE PRENESENIE ZMENY do C# PROPERTY CHILD BLAZOR COMPONENT.
			MSelectedSex=ESex.Male.ToString();
		}
//----------------------------------------------------------------------------------------------------------------------
		public void SetSexToFemale(MouseEventArgs E)
		{
			// !!! Zmeni sa VALUE C# PROPERTY PARENT BLAZOR COMPONENT, ktora je BOUND na C# PROPERTY CHILD BLAZOR COMPONENT.
			// !!!!! Zmena VALUE C# PROPERTY PARENT BLAZOR COMPONENT sposobi AUTOMATICKE PRENESENIE ZMENY do C# PROPERTY CHILD BLAZOR COMPONENT.
			MSelectedSex=ESex.Female.ToString();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------