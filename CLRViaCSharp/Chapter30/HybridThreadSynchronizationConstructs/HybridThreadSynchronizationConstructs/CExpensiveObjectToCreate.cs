using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace HybridThreadSynchronizationConstructs
{
//-------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje OBJECT, ktory berie pri vytvarani VELA RESOURCES, a preto by sa mal vytvarat az ked je ho skutocne treba.
	public sealed class CExpensiveObjectToCreate
	{
//-------------------------------------------------------------------------------------------------------
		public volatile bool									MVariable1;
		public int[]											MExpensiveArray;
		public volatile bool									MVariable2;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CExpensiveObjectToCreate()
		{
			MVariable1=true;

			MExpensiveArray=new int[1024*1024];

			for(int Index=0;Index<MExpensiveArray.Length;Index++)
			{
				MExpensiveArray[Index]=Index;
			}

			MVariable2=true;
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------