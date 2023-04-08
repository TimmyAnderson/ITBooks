using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace WinRTComponent
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CExceptionClass
	{
//-------------------------------------------------------------------------------------------------------
		public int GenerateExcepion1(int Param)
		{
			if (Param==0)
			{
				throw(new OutOfMemoryException("This is OutOfMemoryException !"));
			}
			else
			{
				return(Param);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int GenerateExcepion2(int Param)
		{
			if (Param==0)
			{
				throw(new RankException("This is RankException !"));
			}
			else
			{
				return(Param);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void GenerateExcepion3()
		{
			throw(new OutOfMemoryException("This is OutOfMemoryException !"));
		}
//-------------------------------------------------------------------------------------------------------
		/*
		// !!!!! WinRT COMPONENTS NEPODPORUJU export CUSTOM EXCEPTIONS.
		public int GenerateExcepion4(int Param)
		{
			if (Param==0)
			{
				throw(new CCustomException("This is CCustomException !"));
			}
			else
			{
				return(Param);
			}
		}
		*/
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------