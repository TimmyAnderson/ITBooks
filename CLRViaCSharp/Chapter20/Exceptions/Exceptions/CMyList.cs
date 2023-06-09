﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Exceptions
{
//-------------------------------------------------------------------------------------------------------
	public class CMyList : IEnumerable<string>
	{
//-------------------------------------------------------------------------------------------------------
		private List<string>									MData;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyList(string[] Strings)
		{
			MData=new List<string>(Strings);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IEnumerator<string> GetEnumerator()
		{
			return(new CMyListEnumerator(MData));
		}
//-------------------------------------------------------------------------------------------------------
		System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
		{
			return(new CMyListEnumerator(MData));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------