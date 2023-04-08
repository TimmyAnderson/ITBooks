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
	public partial class RefReferenceChild : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MCounter=1;
		private EventCallback									MCallback;
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
		public EventCallback									Callback
		{
			get
			{
				return(MCallback);
			}
			set
			{
				MCallback=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async void IncrementCounter(MouseEventArgs E)
		{
			MCounter++;

			await MCallback.InvokeAsync(null);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------