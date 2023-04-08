using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Params
{
//-------------------------------------------------------------------------------------------------------
	public class CTestClass
	{
//-------------------------------------------------------------------------------------------------------
		public int Add(int Value1, int Value2)
		{
			Console.WriteLine("NON PARAMS method CALLED !");

			int													Sum=Value1+Value2;

			return(Sum);
		}
//-------------------------------------------------------------------------------------------------------
		public int Add(params int[] Values)
		{
			Console.WriteLine("PARAMS method CALLED !");

			int													Sum=0;

			foreach(int Value in Values)
			{
				Sum+=Value;
			}

			return(Sum);
		}
//-------------------------------------------------------------------------------------------------------
		public void AddAndPrint(string Prefix, params int[] Values)
		{
			Console.WriteLine("PARAMS method CALLED !");

			int													Sum=0;

			if (Values!=null)
			{
				foreach(int Value in Values)
				{
					Sum+=Value;
				}
			}

			Console.WriteLine(string.Format("{0} [{1}] !",Prefix,Sum));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------