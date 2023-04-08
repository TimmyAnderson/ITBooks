using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Rendering;
using Microsoft.AspNetCore.Components.Web;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedBlazorFeatures.Blazor
{
//----------------------------------------------------------------------------------------------------------------------
	public partial class CallFromExternalCodeComponentParent : ComponentBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private CallFromExternalCodeComponentChild				MChild;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CallFromExternalCodeComponentChild				Child
		{
			get
			{
				return(MChild);
			}
			set
			{
				MChild=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Tento CODE bezi v SEPARATNOM TASK, MIMO BLAZOR FRAMEWORK.
		private void ChangeColor(object Parameter)
		{
			string												CSSClassName=(string) Parameter;

			Thread.Sleep(1000);

			// !!!!! Zavola sa CODE BLAZOR COMPONENT z EXTERNAL TASK, ktory bezi MIMO BLAZOR FRAMEWORK.
			Child.SetCSSClass(CSSClassName);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ChangeColorToRed()
		{
			// !!!!! Spusti sa EXTERNY CODE v SEPARATNOM TASKU.
			Task												ChangeColorTask=new Task(ChangeColor,"SOLID_RED",TaskCreationOptions.LongRunning);

			ChangeColorTask.Start();
		}
//----------------------------------------------------------------------------------------------------------------------
		public void ChangeColorToGreen()
		{
			// !!!!! Spusti sa EXTERNY CODE v SEPARATNOM TASKU.
			Task												ChangeColorTask=new Task(ChangeColor,"SOLID_GREEN",TaskCreationOptions.LongRunning);

			ChangeColorTask.Start();
		}
//----------------------------------------------------------------------------------------------------------------------
		public void ChangeColorToBlue()
		{
			// !!!!! Spusti sa EXTERNY CODE v SEPARATNOM TASKU.
			Task												ChangeColorTask=new Task(ChangeColor,"SOLID_BLUE",TaskCreationOptions.LongRunning);

			ChangeColorTask.Start();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------