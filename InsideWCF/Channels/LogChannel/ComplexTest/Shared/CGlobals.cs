using System;
using System.Collections.Generic;
using System.Text;
using Log;
//-------------------------------------------------------------------------------------------------------
namespace ComplexTest
{
//-------------------------------------------------------------------------------------------------------
	class CGlobals
	{
//-------------------------------------------------------------------------------------------------------
		private static CLog										MLog=new CLog(true,"Log",@"..\..\..\..\Logs\Test.txt");
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static CLog										Log
		{
			get
			{
				return(MLog);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------