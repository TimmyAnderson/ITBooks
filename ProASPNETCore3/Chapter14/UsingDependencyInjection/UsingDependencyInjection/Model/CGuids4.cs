﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CGuids4
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly Guid									MID1;
		private readonly Guid									MID2;
		private readonly Guid									MID3;
		private readonly Guid									MID4;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CGuids4(Guid ID1, Guid ID2, Guid ID3, Guid ID4)
		{
			MID1=ID1;
			MID2=ID2;
			MID3=ID3;
			MID4=ID4;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public Guid												ID1
		{
			get
			{
				return(MID1);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public Guid												ID2
		{
			get
			{
				return(MID2);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public Guid												ID3
		{
			get
			{
				return(MID3);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public Guid												ID4
		{
			get
			{
				return(MID4);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------