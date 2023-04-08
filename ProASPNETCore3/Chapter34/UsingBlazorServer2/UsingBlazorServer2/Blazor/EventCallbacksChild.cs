using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Rendering;
using Microsoft.AspNetCore.Components.Web;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBlazorServer2.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	public partial class EventCallbacksChild : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MCounter=1;
		// !!! Ako DELEGATE sa pouzije TYPE [Action].
		private Action											MCallbackAction;
		// !!! Ako DELEGATE sa pouzije TYPE [Action].
		private Action											MCallbackActionWithStateHasChanged;
		// !!! Ako DELEGATE sa pouzije TYPE [EventCallback].
		private EventCallback									MCallbackEventCallback;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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
		[Parameter]
		public Action											CallbackAction
		{
			get
			{
				return(MCallbackAction);
			}
			set
			{
				MCallbackAction=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public Action											CallbackActionWithStateHasChanged
		{
			get
			{
				return(MCallbackActionWithStateHasChanged);
			}
			set
			{
				MCallbackActionWithStateHasChanged=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public EventCallback									CallbackEventCallback
		{
			get
			{
				return(MCallbackEventCallback);
			}
			set
			{
				MCallbackEventCallback=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void IncrementCounter1(MouseEventArgs E)
		{
			MCounter++;

			if (MCallbackAction!=null)
			{
				// !!! Vyvola sa PARENT BLAZOR COMPONENT CALLBACK TYPE [Action].
				MCallbackAction();
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public void IncrementCounter2(MouseEventArgs E)
		{
			MCounter++;

			if (MCallbackActionWithStateHasChanged!=null)
			{
				// !!! Vyvola sa PARENT BLAZOR COMPONENT CALLBACK TYPE [Action].
				MCallbackActionWithStateHasChanged();
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async void IncrementCounter3(MouseEventArgs E)
		{
			MCounter++;

			// !!! Vyvola sa PARENT BLAZOR COMPONENT CALLBACK TYPE [EventCallback].
			await MCallbackEventCallback.InvokeAsync(null);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------