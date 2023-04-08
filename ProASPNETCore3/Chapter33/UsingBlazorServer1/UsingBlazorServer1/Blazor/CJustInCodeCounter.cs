using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Rendering;
using Microsoft.AspNetCore.Components.Web;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBlazorServer1.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! BLAZOR COMPONENT MUSI byt DERIVED z CLASS [ComponentBase].
	public sealed class CJustInCodeCounter : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private int												MCounter=1;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! C# PROPERTY sa mapuje na HTML ELEMENT.
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
		// !!! V METHOD sa definuju HTML ELEMENTS a ich HTML ATTRIBUTES, ktore zobrazuje BLAZOR COMPONENT.
		protected override void BuildRenderTree(RenderTreeBuilder Builder)
		{
			Builder.OpenElement(1,"div");
			Builder.AddAttribute(2,"class","OUTER_BOX");

			Builder.OpenElement(3,"div");
			Builder.AddAttribute(4,"class","INNER_BOX");

			Builder.OpenElement(5,"label");
			Builder.AddContent(6,$"Counter value [{Counter.ToString()}] !");
			// !!! Uzatvori sa HTML ELEMET [<label>] s SEQUENCE NUMBER 5.
			Builder.CloseElement();

			Builder.OpenElement(7,"br");
			// !!! Uzatvori sa HTML ELEMET [<br>] s SEQUENCE NUMBER 7.
			Builder.CloseElement();

			Builder.OpenElement(8,"button");
			Builder.AddAttribute(9,"class","btn btn-primary");
			Builder.AddAttribute(10,"onclick",EventCallback.Factory.Create<MouseEventArgs>(this,IncrementCounter));
			Builder.AddContent(11,"Increment counter");
			// !!! Uzatvori sa HTML ELEMET [<button>] s SEQUENCE NUMBER 8.
			Builder.CloseElement();

			// !!! Uzatvori sa HTML ELEMET [<div>] s SEQUENCE NUMBER 3.
			Builder.CloseElement();

			// !!! Uzatvori sa HTML ELEMET [<div>] s SEQUENCE NUMBER 1.
			Builder.CloseElement();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! EVENT METHOD, ktoru pouziva HTML ELEMENT.
		public void IncrementCounter(MouseEventArgs E)
		{
			MCounter++;
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------