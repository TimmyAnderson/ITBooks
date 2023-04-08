using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBlazorServer2.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Ak BLAZOR COMPONENT pouziva GENERIC TYPE PARAMETERS, MUSI CLASS definovat tieto GENERIC TYPE PARAMETERS vo svojej definicii.
	public partial class TemplateGenericParameterChild<TRowType> : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private RenderFragment									MHeader;
		private RenderFragment<TRowType>						MRowTemplate;
		private IEnumerable<TRowType>							MRows;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public RenderFragment									Header
		{
			get
			{
				return(MHeader);
			}
			set
			{
				MHeader=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER predstavuje TEMPLATE na zobrazenie kazdeho GENERIC TYPE ITEM. TEMPLATE zasiela PARENT BLAZOR COMPONENT.
		[Parameter]
		public RenderFragment<TRowType>							RowTemplate
		{
			get
			{
				return(MRowTemplate);
			}
			set
			{
				MRowTemplate=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER obsahuje zoznam GENERIC TYPE ITEMS, ktore ma CHILD BLAZOR COMPONENT zobrazit.
		// !!!!! TYPE MUSI byt TYPE [IEnumerable<TRowType>] a NIE TYPE [TRowType[]], lebo pri ARRAY C# NEDOKAZE vykonat CONVERSION z ARRAY konkretnehy TYPE na ARRAY GENERIC TYPE.
		[Parameter]
		public IEnumerable<TRowType>							Rows
		{
			get
			{
				return(MRows);
			}
			set
			{
				MRows=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------