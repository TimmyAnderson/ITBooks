﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingCoreIdentity.Security
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CCustomUser : IdentityUser
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MDescription;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											Description
		{
			get
			{
				return(MDescription);
			}
			set
			{
				MDescription=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------