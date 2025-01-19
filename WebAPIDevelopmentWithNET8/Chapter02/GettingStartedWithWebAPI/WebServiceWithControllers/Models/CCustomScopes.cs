﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
//--------------------------------------------------------------------------------------------------------------------------------
namespace WebServiceWithControllers
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CCustomScopes
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private int												MMyScoped1;
		private int												MMyScoped2;
		private int												MMyScopedInCustomScope1;
		private int												MMyScopedInCustomScope2;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CCustomScopes()
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public CCustomScopes(int MyScoped1, int MyScoped2, int MyScopedInCustomScope1, int MyScopedInCustomScope2)
		{
			MMyScoped1=MyScoped1;
			MMyScoped2=MyScoped2;
			MMyScopedInCustomScope1=MyScopedInCustomScope1;
			MMyScopedInCustomScope2=MyScopedInCustomScope2;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public int												MyScoped1
		{
			get
			{
				return(MMyScoped1);
			}
			set
			{
				MMyScoped1=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public int												MyScoped2
		{
			get
			{
				return(MMyScoped2);
			}
			set
			{
				MMyScoped2=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public int												MyScopedInCustomScope1
		{
			get
			{
				return(MMyScopedInCustomScope1);
			}
			set
			{
				MMyScopedInCustomScope1=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public int												MyScopedInCustomScope2
		{
			get
			{
				return(MMyScopedInCustomScope2);
			}
			set
			{
				MMyScopedInCustomScope2=value;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------