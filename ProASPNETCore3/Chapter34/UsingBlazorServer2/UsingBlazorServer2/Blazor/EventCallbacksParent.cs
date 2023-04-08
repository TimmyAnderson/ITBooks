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
	public partial class EventCallbacksParent : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private const int										NUMBER_OF_CHILD_COMPONENTS=3;
//----------------------------------------------------------------------------------------------------------------------
		private EventCallbacksChild[]							MChildComponents=new EventCallbacksChild[NUMBER_OF_CHILD_COMPONENTS];
		private int												MTotalCounter;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public EventCallbacksChild[]							ChildComponents
		{
			get
			{
				return(MChildComponents);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												TotalCounter
		{
			get
			{
				return(MTotalCounter);
			}
			set
			{
				MTotalCounter=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Vyvolanie DELEGATE [Action] NESPOSOBI vykonanie RENDERING BLAZOR COMPONENT a teda hodnota TOTAL COUNTER sa NEZMENI.
		public void EventAction()
		{
			int													Counter=0;

			foreach(EventCallbacksChild EventCallbacksChild in ChildComponents)
			{
				Counter+=EventCallbacksChild.Counter;
			}

			TotalCounter=Counter;
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Vyvolanie DELEGATE [Action] sice NESPOSOBI vykonanie RENDERING BLAZOR COMPONENT, ale volanie METHOD [void StateHasChanged()] VYNUTI vykonanie RENDERINGU BLAZOR COMPONENT a teda hodnota TOTAL COUNTER sa ZMENI.
		public void EventActionWithStateHasChanged()
		{
			int													Counter=0;

			foreach(EventCallbacksChild EventCallbacksChild in ChildComponents)
			{
				Counter+=EventCallbacksChild.Counter;
			}

			TotalCounter=Counter;

			// !!!!! Volanie METHOD VYNUTI vykonanie RENDERING BLAZOR COMPONENT a teda hodnota TOTAL COUNTER sa ZMENI.
			StateHasChanged();
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Vyvolanie DELEGATE [EventCallback] SPOSOBI vykonanie RENDERING BLAZOR COMPONENT a teda hodnota TOTAL COUNTER sa ZMENI.
		public void EventEventCallback(object Param)
		{
			int													Counter=0;

			foreach(EventCallbacksChild EventCallbacksChild in ChildComponents)
			{
				Counter+=EventCallbacksChild.Counter;
			}

			TotalCounter=Counter;
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------