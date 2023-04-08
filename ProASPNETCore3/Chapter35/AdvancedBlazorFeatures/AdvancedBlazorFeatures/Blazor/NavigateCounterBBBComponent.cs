﻿using System;
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
	public partial class NavigateCounterBBBComponent : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private NavigationManager								MNavigationManager;
		private int												MCounter=1;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Inject]
		public NavigationManager								NavigationManager
		{
			get
			{
				return(MNavigationManager);
			}
			set
			{
				MNavigationManager=value;
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
		public void IncrementCounter(MouseEventArgs E)
		{
			MCounter++;
		}
//----------------------------------------------------------------------------------------------------------------------
		public void NavigateToDifferentBlazorComponent(MouseEventArgs E)
		{
			MNavigationManager.NavigateTo("/CounterAAA");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------