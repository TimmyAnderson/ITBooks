using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Globalization;
using System.Windows.Markup;
using System.Windows.Controls;
//------------------------------------------------------------------------
namespace RoutedEventsTestLibrary
{
//------------------------------------------------------------------------
	public class CREPatent : ContentControl
	{
//------------------------------------------------------------------------
		public static RoutedEvent			REBubbleEvent;
		public static RoutedEvent			RETunnelEvent;
		public static RoutedEvent			REDirectEvent;
//------------------------------------------------------------------------
		public static RoutedEvent			RESharedBaseEvent;
		public static RoutedEvent			RESharedReferenceEvent;
//------------------------------------------------------------------------
		static CREPatent()
		{
			REBubbleEvent=EventManager.RegisterRoutedEvent("REBubble",RoutingStrategy.Bubble,typeof(RoutedEventHandler),typeof(CREPatent));
			RETunnelEvent=EventManager.RegisterRoutedEvent("RETunnel",RoutingStrategy.Tunnel,typeof(RoutedEventHandler),typeof(CREPatent));
			REDirectEvent=EventManager.RegisterRoutedEvent("REDirect",RoutingStrategy.Direct,typeof(RoutedEventHandler),typeof(CREPatent));

			RESharedBaseEvent=EventManager.RegisterRoutedEvent("RESharedBase",RoutingStrategy.Bubble,typeof(RoutedEventHandler),typeof(CREPatent));
			// !!! Vytvaram Shared RE.
			RESharedReferenceEvent=RESharedBaseEvent.AddOwner(typeof(CREChild));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public event RoutedEventHandler		REBubble
		{
			add
			{
				base.AddHandler(CREPatent.REBubbleEvent, value);
			}
			remove
			{
				base.RemoveHandler(CREPatent.REBubbleEvent, value);
			}
		}
//------------------------------------------------------------------------
		public event RoutedEventHandler		RETunnel
		{
			add
			{
				base.AddHandler(CREPatent.RETunnelEvent, value);
			}
			remove
			{
				base.RemoveHandler(CREPatent.RETunnelEvent, value);
			}
		}
//------------------------------------------------------------------------
		public event RoutedEventHandler		REDirect
		{
			add
			{
				base.AddHandler(CREPatent.REDirectEvent, value);
			}
			remove
			{
				base.RemoveHandler(CREPatent.REDirectEvent, value);
			}
		}
//------------------------------------------------------------------------
		public event RoutedEventHandler		RESharedBase
		{
			add
			{
				base.AddHandler(CREPatent.RESharedBaseEvent, value);
			}
			remove
			{
				base.RemoveHandler(CREPatent.RESharedBaseEvent, value);
			}
		}
//------------------------------------------------------------------------
		public event RoutedEventHandler		RESharedReference
		{
			add
			{
				base.AddHandler(CREPatent.RESharedReferenceEvent, value);
			}
			remove
			{
				base.RemoveHandler(CREPatent.RESharedReferenceEvent, value);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		protected override void OnRender(DrawingContext DrawingContext)
		{
			// Nic nerenderujem.
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public void FireBubbleEvent()
		{
			this.RaiseEvent(new RoutedEventArgs(CREPatent.REBubbleEvent,this));
		}
//------------------------------------------------------------------------
		public void FireTunnelEvent()
		{
			this.RaiseEvent(new RoutedEventArgs(CREPatent.RETunnelEvent,this));
		}
//------------------------------------------------------------------------
		public void FireDirectEvent()
		{
			this.RaiseEvent(new RoutedEventArgs(CREPatent.REDirectEvent,this));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------