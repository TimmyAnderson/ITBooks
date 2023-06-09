﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Service
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CLifeCycleTransient : ILifeCycleTransient
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly Guid									MID;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CLifeCycleTransient()
		{
			MID=Guid.NewGuid();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public Guid												ID
		{
			get
			{
				return(MID);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------