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
	public partial class CallCSharpNonStaticMethodFromJavaScriptCodeComponent : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private IJSRuntime										MJSRuntime;
		private int												MCounter=1;
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! NON-STATIC C# METHOD je volana z JAVASCRIPT CODE.
		[JSInvokable]
		public void IncrementCounterCalledFromJavaScript(int Value)
		{
			MCounter+=Value;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task IncrementCounter1(MouseEventArgs E)
		{
			// !!! Ziska sa REFERENCE na THIS OBJECT, ktoru je mozne poslat do JAVASCRIPT CODE.
			DotNetObjectReference<CallCSharpNonStaticMethodFromJavaScriptCodeComponent>	Reference=DotNetObjectReference.Create(this);

			// !!! Zavola sa JAVASCRIPT FUNCTION, ktora nasledne vyvola C# METHOD.
			await MJSRuntime.InvokeVoidAsync("JSCallNonStaticCSharpMethod",Reference,1);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task IncrementCounter2(MouseEventArgs E)
		{
			// !!! Ziska sa REFERENCE na THIS OBJECT, ktoru je mozne poslat do JAVASCRIPT CODE.
			DotNetObjectReference<CallCSharpNonStaticMethodFromJavaScriptCodeComponent>	Reference=DotNetObjectReference.Create(this);

			// !!! Zavola sa JAVASCRIPT FUNCTION, ktora nasledne vyvola C# METHOD.
			await MJSRuntime.InvokeVoidAsync("JSCallNonStaticCSharpMethod",Reference,2);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------