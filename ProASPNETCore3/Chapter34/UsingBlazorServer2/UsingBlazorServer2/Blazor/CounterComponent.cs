﻿using System;
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
	public partial class CounterComponent : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MCounter=1;
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
//----------------------------------------------------------------------------------------------------------------------
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