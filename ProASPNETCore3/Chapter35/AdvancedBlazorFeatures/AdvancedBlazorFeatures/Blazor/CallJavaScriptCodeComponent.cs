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
	public partial class CallJavaScriptCodeComponent : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private IJSRuntime										MJSRuntime;
		private int												MCounter=1;
		private ElementReference								MArea;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Inject]
		public IJSRuntime										JSRuntime
		{
			get
			{
				return(MJSRuntime);
			}
			set
			{
				MJSRuntime=value;
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
		public ElementReference									Area
		{
			get
			{
				return(MArea);
			}
			set
			{
				MArea=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task IncrementCounter(MouseEventArgs E)
		{
			// !!! Zavola sa JAVASCRIPT FUNCTION, ktora inkrementuje COUNTER. JAVASCRIPT FUNCTION vracia RETURN VALUE.
			int													Result=await MJSRuntime.InvokeAsync<int>("JSIncrementCounter",MCounter);

			MCounter=Result;
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task DoAlert(MouseEventArgs E)
		{
			// !!! Zavola sa JAVASCRIPT FUNCTION, ktora zobrazi ALERT. JAVASCRIPT FUNCTION nevracia RETURN VALUE.
			await MJSRuntime.InvokeVoidAsync("JSShowAlert","Hello World !!!");
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task SetText1(MouseEventArgs E)
		{
			// !!! Zavola sa JAVASCRIPT FUNCTION, ktora zobrazi nastavi VALUE HTML ELEMENT. JAVASCRIPT FUNCTION nevracia RETURN VALUE.
			// !!! REFERENCE na HTML ELEMENT je zaslany ako 2. PARAMETER.
			await MJSRuntime.InvokeVoidAsync("JSSetElementText",MArea,"Timmy Anderson");
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task SetText2(MouseEventArgs E)
		{
			// !!! Zavola sa JAVASCRIPT FUNCTION, ktora zobrazi nastavi VALUE HTML ELEMENT. JAVASCRIPT FUNCTION nevracia RETURN VALUE.
			// !!! REFERENCE na HTML ELEMENT je zaslany ako 2. PARAMETER.
			await MJSRuntime.InvokeVoidAsync("JSSetElementText",MArea,"Jenny Thompson");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------