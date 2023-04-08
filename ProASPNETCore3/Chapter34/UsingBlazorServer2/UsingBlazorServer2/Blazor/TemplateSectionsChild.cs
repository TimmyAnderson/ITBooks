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
	public partial class TemplateSectionsChild : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private RenderFragment									MSection1;
		private RenderFragment									MSection2;
		private RenderFragment									MSection3;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! C# PROPERTY reprezentuje SECTION.
		[Parameter]
		public RenderFragment									Section1
		{
			get
			{
				return(MSection1);
			}
			set
			{
				MSection1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! C# PROPERTY reprezentuje SECTION.
		[Parameter]
		public RenderFragment									Section2
		{
			get
			{
				return(MSection2);
			}
			set
			{
				MSection2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! C# PROPERTY reprezentuje SECTION.
		[Parameter]
		public RenderFragment									Section3
		{
			get
			{
				return(MSection3);
			}
			set
			{
				MSection3=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------