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
	public partial class Layout3 : LayoutComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		public string											Text1
		{
			get
			{
				return("START of LAYOUT 3 !!!");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											Text2
		{
			get
			{
				return("END of LAYOUT 3 !!!");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------