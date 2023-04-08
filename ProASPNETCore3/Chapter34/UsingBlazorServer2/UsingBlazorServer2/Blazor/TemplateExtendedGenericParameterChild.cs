using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using UsingBlazorServer2.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBlazorServer2.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Ak BLAZOR COMPONENT pouziva GENERIC TYPE PARAMETERS, MUSI CLASS definovat tieto GENERIC TYPE PARAMETERS vo svojej definicii.
	public partial class TemplateExtendedGenericParameterChild<TRowType> : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private RenderFragment									MHeader;
		private RenderFragment<TRowType>						MRowTemplate;
		private IEnumerable<TRowType>							MRows;
		private string											MSelectedSex;
		private string											MSelectedOrder;
		private Func<TRowType,string>							MSexCallback;
		private Func<TRowType,string>							MSortValueCallback;
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
		// !!! CALLBACK FUNCTION vracia pre OBJECT 'TRowType' hodnotu jeho SEX.
		[Parameter]
		public Func<TRowType,string>							SexCallback
		{
			get
			{
				return(MSexCallback);
			}
			set
			{
				MSexCallback=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! CALLBACK FUNCTION vracia pre OBJECT 'TRowType' VALUE PROPERTY podla, ktorej ma byt vykonany SORTING.
		[Parameter]
		public Func<TRowType,string>							SortValueCallback
		{
			get
			{
				return(MSortValueCallback);
			}
			set
			{
				MSortValueCallback=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											SelectedSex
		{
			get
			{
				return(MSelectedSex);
			}
			set
			{
				MSelectedSex=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											SelectedOrder
		{
			get
			{
				return(MSelectedOrder);
			}
			set
			{
				MSelectedOrder=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string[] GetSexes()
		{
			string[]											Sexes=Enum.GetNames(typeof(ESex));

			return(Sexes);
		}
//----------------------------------------------------------------------------------------------------------------------
		public string[] GetSorts()
		{
			string[]											Sorts=new string[]{"Ascending","Descending"};

			return(Sorts);
		}
//----------------------------------------------------------------------------------------------------------------------
		public string GetClass(TRowType Value)
		{
			string												Sex;
				
			// !!! Vola sa CALLBACK METHOD PARENT BLAZOR COMPONENT, ktora vrati pre dany ROW OBJECT hodnotu jeho SEX.
			if (SexCallback!=null)
			{
				Sex=SexCallback(Value);
			}
			else
			{
				Sex="";
			}

			if (Sex==MSelectedSex)
			{
				return("bg-info text-white");
			}
			else
			{
				return("");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vracia ITEMS, ktore su ORDERED podla PROPERTY, ktoru definuje CALLBACK nastaveny PARENT BLAZOR COMPONENT a vybrateho SORT ORDER.
		public IEnumerable<TRowType> GetOrderedItems()
		{
			if (SortValueCallback==null)
			{
				return(MRows);
			}

			if (string.IsNullOrEmpty(SelectedOrder)==true)
			{
				return(MRows);
			}

			if (SelectedOrder=="Ascending")
			{
				// !!! ORDERING sa vykonava podla PROPERTY VALUE, ktoru vracia CALLBACK METHOD PARENT BLAZOR COMPONENT.
				IEnumerable<TRowType>							OrderedItems=MRows.OrderBy(P => SortValueCallback(P));

				return(OrderedItems);
			}
			else if (SelectedOrder=="Descending")
			{
				// !!! ORDERING sa vykonava podla PROPERTY VALUE, ktoru vracia CALLBACK METHOD PARENT BLAZOR COMPONENT.
				IEnumerable<TRowType>							OrderedItems=MRows.OrderByDescending(P => SortValueCallback(P));

				return(OrderedItems);
			}
			else
			{
				return(MRows);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------