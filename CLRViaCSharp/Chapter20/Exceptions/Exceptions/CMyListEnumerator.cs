﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Exceptions
{
//-------------------------------------------------------------------------------------------------------
	public class CMyListEnumerator : IEnumerator<string>, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private List<string>									MData;
		private int												MPosition;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyListEnumerator(List<string> Data)
		{
			MData=Data;
			MPosition=-1;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											Current
		{
			get
			{
				if (MPosition==-1)
				{
					throw(new Exception("Invalid INDEX !"));
				}

				return(MData[MPosition]);
			}
		}
//-------------------------------------------------------------------------------------------------------
		object													System.Collections.IEnumerator.Current
		{
			get
			{
				if (MPosition==-1)
				{
					throw(new Exception("Invalid INDEX !"));
				}

				return(MData[MPosition]);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool MoveNext()
		{
			MPosition++;

			if (MPosition<MData.Count)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void Reset()
		{
			MPosition=-1;
		}
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CMyListEnumerator DISPOSED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------