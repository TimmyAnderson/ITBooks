using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBlazorServer2.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	public partial class CustomBindingChild : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MValueName="UNSPECIFIED";
		private string[]										MValues=new string[0];
		private EventCallback<string>							MSelectedValueChanged;
		private string											MSelectedValue="";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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
		// !!! Na implementaciu CUSTOM BINDING je NUTNE definovat C# PROPERTY, ktora je oznacena ATTRIBUTE [ParameterAttribute] a ktora obsahuje VALUE na ktoru bude PARENT BLAZOR COMPONENT BOUND.
		[Parameter]
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
		// !!! Na implementaciu CUSTOM BINDING je NUTNE definovat C# PROPERTY TYPE [EventCallback<TType>], ktorej NAME MUSI splnat KONVENCIU [XXX], kde VALUE 'XXX' obsahuje nazov C# PROPERTY na ktoru bude PARENT BLAZOR COMPONENT BOUND.
		[Parameter]
		public EventCallback<string>							SelectedValueChanged
		{
			get
			{
				return(MSelectedValueChanged);
			}
			set
			{
				MSelectedValueChanged=value;
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
			await MSelectedValueChanged.InvokeAsync(MSelectedValue);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------