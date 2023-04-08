using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Rendering;
using Microsoft.AspNetCore.Components.Web;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedBlazorFeatures.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! BLAZOR COMPONENTS mozu implementovat INTERFACE [IDisposible].
	public partial class CounterWithLifecycleMethods1 : ComponentBase, IDisposable
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MCounter=1;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
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
		// !!! Vola sa pri vytvoreni instancie BLAZOR COMPONENT. Ak doslo k NAVIGATION na WEB PAGE, ktora obsahuje tuto COMPONENT, tak sa METHOD zavola.
		protected override Task OnInitializedAsync()
		{
			Console.WriteLine("!!!!! CounterWithLifecycleMethods1.OnInitializedAsync() CALLED !!!!!");

			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
		protected override Task OnParametersSetAsync()
		{
			Console.WriteLine("!!!!! CounterWithLifecycleMethods1.OnParametersSetAsync() CALLED !!!!!");

			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
		protected override bool ShouldRender()
		{
			Console.WriteLine("!!!!! CounterWithLifecycleMethods1.ShouldRender() CALLED !!!!!");

			return(true);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD sa vola pri KAZDEJ ZMENE HTML CONTENT. To znaci, ze pri KAZDOM zvyseni hodnoty COUNTER sa METHOD vola ZNOVA.
		protected override Task OnAfterRenderAsync(bool FirstRender)
		{
			Console.WriteLine($"!!!!! CounterWithLifecycleMethods1.OnAfterRenderAsync({FirstRender.ToString().ToUpper()}) CALLED !!!!!");

			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD sa vola, ak dojde k NAVIGATION na INU BLAZOR COMPONENT.
		public void Dispose()
		{
			Console.WriteLine("!!!!! CounterWithLifecycleMethods1.Dispose() CALLED !!!!!");
		}
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