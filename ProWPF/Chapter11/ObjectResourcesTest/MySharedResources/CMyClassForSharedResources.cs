using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
//------------------------------------------------------------------------
namespace MySharedResources
{
//------------------------------------------------------------------------
	// !!! Pre prvu variantu riesenia je to PRAZDNA TRIEDA, ktora sa pouziva ako TYP pre ComponentResourceKey.TypeInTargetAssembly.
	// !!! V druhej variante riesenia mam staticku preopoerty PRE KAZDY RESOURCE, ktore chcem vystavit.
	public class CMyClassForSharedResources
	{
//------------------------------------------------------------------------
		// Pre riesenie 2 nadefinujem tieto static properties.
		public static ComponentResourceKey	SharedRes1
		{
			get
			{
				return(new ComponentResourceKey(typeof(CMyClassForSharedResources), "MSharedRes1"));
			}
		}
//------------------------------------------------------------------------
		public static ComponentResourceKey	SharedRes2
		{
			get
			{
				return(new ComponentResourceKey(typeof(CMyClassForSharedResources), "MSharedRes2"));
			}
		}
//------------------------------------------------------------------------
		public static ComponentResourceKey	SharedRes3
		{
			get
			{
				return(new ComponentResourceKey(typeof(CMyClassForSharedResources), "MSharedRes3"));
			}
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------