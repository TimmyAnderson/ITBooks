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
	public partial class CallCSharpStaticMethodFromJavaScriptCodeComponent : ComponentBase, IDisposable
	{
//----------------------------------------------------------------------------------------------------------------------
		private static object									MLock=new object();
		private static List<CallCSharpStaticMethodFromJavaScriptCodeComponent>	MObjects=new List<CallCSharpStaticMethodFromJavaScriptCodeComponent>();
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
		// !!!!! STATIC C# METHOD je volana z JAVASCRIPT CODE.
		[JSInvokable]
		public static void IncrementCounterCalledFromJavaScript(int Value)
		{
			CallCSharpStaticMethodFromJavaScriptCodeComponent[]	Objects;

			lock(MLock)
			{
				Objects=MObjects.ToArray();
			}

			// !!! Vyvola sa METHOD, ktora inkrementuje COUNTER.
			foreach(CallCSharpStaticMethodFromJavaScriptCodeComponent Object in Objects)
			{
				Object.IncrementCounter(Value);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void IncrementCounter(int Value)
		{
			MCounter+=Value;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void OnInitialized()
		{
			lock(MLock)
			{
				// !!! Prida sa THIS INSTANCE do STATIC COLLECTION.
				MObjects.Add(this);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			lock(MLock)
			{
				// !!! Odstrani sa THIS INSTANCE zo STATIC COLLECTION.
				MObjects.Remove(this);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task IncrementCounter1(MouseEventArgs E)
		{
			// !!! Zavola sa JAVASCRIPT FUNCTION, ktora nasledne vyvola C# METHOD.
			await MJSRuntime.InvokeVoidAsync("JSCallStaticCSharpMethod",1);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task IncrementCounter2(MouseEventArgs E)
		{
			// !!! Zavola sa JAVASCRIPT FUNCTION, ktora nasledne vyvola C# METHOD.
			await MJSRuntime.InvokeVoidAsync("JSCallStaticCSharpMethod",2);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------