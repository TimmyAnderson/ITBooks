using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using RealApplication5.Models;
//----------------------------------------------------------------------------------------------------------------------
// !!! CODE BEHIND CLASS MUSI byt definovana v ROVNAKOM NAMESPACE ako [OrderTable.razor].
namespace RealApplication5.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	public partial class OrderTable : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MTableTitle="Orders";
		private IEnumerable<COrder>								MOrders;
		private string											MButtonLabel="Ship";
		private EventCallback<int>								MOrderSelected;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public string											TableTitle
		{
			get
			{
				return(MTableTitle);
			}
			set
			{
				MTableTitle=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public IEnumerable<COrder>								Orders
		{
			get
			{
				return(MOrders);
			}
			set
			{
				MOrders=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public string											ButtonLabel
		{
			get
			{
				return(MButtonLabel);
			}
			set
			{
				MButtonLabel=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public EventCallback<int>								OrderSelected
		{
			get
			{
				return(MOrderSelected);
			}
			set
			{
				MOrderSelected=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------