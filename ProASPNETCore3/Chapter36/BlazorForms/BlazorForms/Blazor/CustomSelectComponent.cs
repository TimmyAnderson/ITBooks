using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Forms;
//----------------------------------------------------------------------------------------------------------------------
namespace BlazorForms.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
    public partial class CustomSelectComponent<TValue> : InputBase<TValue>
    {
//----------------------------------------------------------------------------------------------------------------------
		private RenderFragment									MChildContent;
		private Dictionary<string,TValue>						MValues;
		private Func<string,TValue>								MParser;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Parameter]
		public RenderFragment									ChildContent
		{
			get
			{
				return(MChildContent);
			}
			set
			{
				MChildContent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! DICTIONARY obsahuje KEYS a VALUES, ktore sa zobrazuju v COMBOBOXE.
		[Parameter]
		public Dictionary<string,TValue>						Values
		{
			get
			{
				return(MValues);
			}
			set
			{
				MValues=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! FUNCTION vykonava PARSING VALUES.
		[Parameter]
		public Func<string,TValue>								Parser
		{
			get
			{
				return(MParser);
			}
			set
			{
				MParser=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vykona PARSING VALUES.
		protected override bool TryParseValueFromString(string Value, out TValue Result, out string ValidationErrorMessage)
		{
			try
			{
				Result=MParser(Value);
				ValidationErrorMessage=null;

				return(true);
			}
			catch
			{
				Result=default(TValue);
				ValidationErrorMessage="VALUE is INVALID !";

				return(false);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void OnChangeValue(ChangeEventArgs E)
		{
			string												TypedValue=(E.Value as string);

			CurrentValueAsString=TypedValue;
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------