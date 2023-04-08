﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace ControllersAndViews.Models
{
//----------------------------------------------------------------------------------------------------------------------
	public interface INameRepository
	{
//----------------------------------------------------------------------------------------------------------------------
		public void AddName(CName Name);
		public CName[] GetNames();
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------