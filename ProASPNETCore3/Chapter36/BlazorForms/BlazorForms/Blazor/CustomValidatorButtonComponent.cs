using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using BlazorForms.Model;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Forms;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorForms.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS implementuje CUSTOM BUTTON VALIDATOR BLAZOR COMPONENT.
    public partial class CustomValidatorButtonComponent : ComponentBase
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [EditContext] osahuje MEMBERS, ktore umoznuju vykonat CUSTOM VALIDATION.
		// !!!!! PARAMETER je naplneny BLAZOR COMPONENT [EditForm].
		private EditContext										MCurrentEditContext;
		private RenderFragment									MChildContent;
		private Dictionary<string,object>						MAttributes;
		private bool											MDisabled;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! NAZOV PARAMETER moze byt LUBOVOLNY.
		[CascadingParameter]
		public EditContext										CurrentEditContext
		{
			get
			{
				return(MCurrentEditContext);
			}
			set
			{
				MCurrentEditContext=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public RenderFragment									ChildContent
		{
			get
			{
				return(MChildContent);
			}
			set
			{
				MChildContent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Parameter(CaptureUnmatchedValues=true)]
		public Dictionary<string,object>						Attributes
		{
			get
			{
				return(MAttributes);
			}
			set
			{
				MAttributes=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											ButtonClass
		{
			get
			{
				if (MDisabled==true)
				{
					return("btn btn-primary btn-outline-dark disabled");
				}
				else
				{
					return("btn btn-primary");
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public bool												Disabled
		{
			get
			{
				return(MDisabled);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void SetButtonState()
		{
			// !!! Ak existuje nejaka ERROR MESSAGE, tak sa nastavi BUTTON STATE na DISABLED.
			if (MCurrentEditContext.GetValidationMessages().Count()>0)
			{
				MDisabled=true;
			}
			else
			{
				MDisabled=false;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private void OnValidationStateChanged(object Sender, ValidationStateChangedEventArgs E)
		{
			SetButtonState();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnInitialized()
		{
			SetButtonState();

			// !!! Pri zmene VALIDATION STATE sa zmeni BUTTON STATE.
			MCurrentEditContext.OnValidationStateChanged+=OnValidationStateChanged;

			// !!!!! Po spusteni BLAZOR COMPONENT sa HNED spravi VALIDATION, aby sa overilo ci data nie su INVALID.
			MCurrentEditContext.Validate();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------