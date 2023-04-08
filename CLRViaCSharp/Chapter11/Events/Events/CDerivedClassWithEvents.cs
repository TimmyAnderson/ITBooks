using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Events
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CDerivedClassWithEvents : CBaseClassWithEvents
	{
//-------------------------------------------------------------------------------------------------------
		// !!! EVENT je OVERRIDEN EVENT.
		public override event EventHandler						VirtualEvent
		{
			add
			{
				Console.WriteLine("METHOD CDerivedClassWithEvents.add_VirtualEvent() CALLED !");

				lock(MLock)
				{
					MVirtualEvent+=value;
				}
			}
			remove
			{
				Console.WriteLine("METHOD CDerivedClassWithEvents.remove_VirtualEvent() CALLED !");

				lock(MLock)
				{
					MVirtualEvent-=value;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------