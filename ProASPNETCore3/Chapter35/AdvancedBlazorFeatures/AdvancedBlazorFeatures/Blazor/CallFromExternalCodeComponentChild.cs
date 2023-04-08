using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Rendering;
using Microsoft.AspNetCore.Components.Web;
using Microsoft.JSInterop;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedBlazorFeatures.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	public partial class CallFromExternalCodeComponentChild : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MCSSClass="";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											CSSClass
		{
			get
			{
				return(MCSSClass);
			}
			set
			{
				MCSSClass=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Tato METHOD uz BEZI v BLAZOR EXECUTION CONTEXT.
		private void RunInBlazorFrameworkContext(string CSSClass)
		{
			MCSSClass=CSSClass;

			// !!!!! Po vykonani modifikacie BLAZOR COMPONENT je NUTNE zavolat METHOD [void StateHasChanged()], aby BLAZOR FRAMEWORK vedel, ze doslo k modifikacii BLAZOR COMPONENT z EXTERNAL ENVIRONMENT a vykonat RENDERING BLAZOR COMPONENT.
			StateHasChanged();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Tato METHOD je volana z EXTERNAL ENVIRONMENT.
		public void SetCSSClass(string CSSClass)
		{
			// !!!!! CODE BLAZOR COMPONENT, ktory je spustany z EXTERNAL ENVIRONMENT MUSI byt SYNCHRONIZOVANY do BLAZOR EXECUTION CONTEXT volanim METHOD [Task InvokeAsync(Action WorkItem)] resp. METHOD [Task InvokeAsync(Func<Task> WorkItem)].
			InvokeAsync(() => RunInBlazorFrameworkContext(CSSClass));
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------