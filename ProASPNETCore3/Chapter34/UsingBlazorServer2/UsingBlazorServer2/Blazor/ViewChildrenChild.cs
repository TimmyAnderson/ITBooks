using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBlazorServer2.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	public partial class ViewChildrenChild : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MValueName="UNSPECIFIED";
		private string[]										MValues=new string[0];
		private Dictionary<string,object>						MUnmatchedParameters=new Dictionary<string,object>();
		private EventCallback<string>							MCallbackValueChanged;
		private string											MSelectedValue="";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY demonstruje, ze LUBOVOLNU PROPERTY TYPE [Dictionary<string,object>] je mozne rozvinut ako HTML ATTRIBUTES pomocou KEYWORD [@attributes="CSHARP_PROPERTY"].
		public Dictionary<string,object>						DivParameters
		{
			get
			{
				Dictionary<string,object>						Value=new Dictionary<string,object>();

				Value.Add("class","BLUE_BOX");

				return(Value);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETERS je mozne nastavovat z PARENT BLAZOR COMPONENTS.
		[Parameter]
		public string											ValueName
		{
			get
			{
				return(MValueName);
			}
			set
			{
				MValueName=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETERS je mozne nastavovat z PARENT BLAZOR COMPONENTS.
		[Parameter]
		public string[]											Values
		{
			get
			{
				return(MValues);
			}
			set
			{
				MValues=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Do tohto CATCH ALL PARAMETER sa ulozia VALUES vsetky HTML ATTRIBUTES, ktore boli aplikovane na HTML ELEMENT reprezentujuci CHILD BLAZOR COMPONENT, ale neboli namapovane na C# PROPERTIES oznacene ATTRIBUTE [ParameterAttribute].
		[Parameter(CaptureUnmatchedValues=true)]
		public Dictionary<string,object>						UnmatchedParameters
		{
			get
			{
				return(MUnmatchedParameters);
			}
			set
			{
				MUnmatchedParameters=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Toto je EVENT PARAMETER, ktory moze pouzit PARENT BLAZOR COMPONENT na registraciu svojho CALLBACK.
		[Parameter]
		public EventCallback<string>							CallbackValueChanged
		{
			get
			{
				return(MCallbackValueChanged);
			}
			set
			{
				MCallbackValueChanged=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											SelectedValue
		{
			get
			{
				return(MSelectedValue);
			}
			set
			{
				MSelectedValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! CALLBACK je vhodnejsie (aj ked nie nutne) robit ako ASYNCHRONOUS METHOD.
		public async Task HandleChangeSelectValue(ChangeEventArgs E)
		{
			// !!! Najprv sa vykona UPDATE PROPERTY 'SelectedValue'.
			MSelectedValue=(E.Value as string);

			// !!! EVENT sa odosle do PARENT BLAZOR COMPONENT.
			// !!! NETREBA kontrolovat na NULL, pretoze TYPE [EventCallback<TType>] je STRUCTURE.
			await MCallbackValueChanged.InvokeAsync(MSelectedValue);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------