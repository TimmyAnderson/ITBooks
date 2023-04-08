using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace MySynchronizationContextClient
{
//-------------------------------------------------------------------------------------------------------
	public class CPair<T1, T2>
	{
//-------------------------------------------------------------------------------------------------------
		private	T1												MFirst;
		private	T2												MSecond;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CPair(T1 First, T2 Second)
		{
			MFirst=First;
			MSecond=Second;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public	T1												First
		{
			get
			{
				return(MFirst);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public	T2												Second
		{
			get
			{
				return(MSecond);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------