﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public abstract class CSymbol : IEquatable<CSymbol>
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbol(string Name)
		{
			MName=Name;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											Name
		{
			get
			{
				return(MName);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override int GetHashCode()
		{
			return(MName.GetHashCode());
		}
//-------------------------------------------------------------------------------------------------------
		public override bool Equals(object Obj)
		{
			CSymbol												Other=Obj as CSymbol;

			if (Other==null)
			{
				return(false);
			}

			if (MName==Other.MName)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public virtual bool Equals(CSymbol Other)
		{
			if (Other==null)
			{
				return(false);
			}

			if (MName==Other.MName)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(MName);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------