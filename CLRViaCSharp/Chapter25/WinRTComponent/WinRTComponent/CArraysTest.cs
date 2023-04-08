using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.UI.Xaml.Controls;
//-------------------------------------------------------------------------------------------------------
namespace WinRTComponent
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CArraysTest
	{
//-------------------------------------------------------------------------------------------------------
		private ListView										MListView;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CArraysTest(ListView ListView)
		{
			MListView=ListView;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void PrintArray(string Prefix, int[] Array)
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat("[{0}] - {1} - [",DateTime.Now,Prefix);

			for(int Index=0;Index<Array.Length;Index++)
			{
				if (Index!=0)
				{
					SB.Append(",");
				}

				SB.Append(Array[Index]);
			}

			SB.AppendLine("] !");

			MListView.Items.Add(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void InArray([ReadOnlyArray] int[] Array)
		{
			PrintArray("IN ARRAY",Array);
		}
//-------------------------------------------------------------------------------------------------------
		public void OutArray([WriteOnlyArray] out int[] Array)
		{
			Array=new int[]{1,2,3};

			PrintArray("OUT ARRAY",Array);
		}
//-------------------------------------------------------------------------------------------------------
		public int[] ReturnArray()
		{
			int[]												Array=new int[]{1,2,3};

			PrintArray("RETURN ARRAY",Array);

			return(Array);
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! POTENCIALNE CHYBNY CODE.
		// !!! METHOD interne MODIFIKUJE ARRAY. To sa sice v tomto pripade podarilo, ale vo vseobecnosti to NIE JE STANDARDNE a NEEXISTUJE ISTOTA, ze modifikacia ARRAY bude skutocne zrealizovana VZDY.
		public void InOutArray([ReadOnlyArray] int[] Array)
		{
			PrintArray("IN-OUT ARRAY BEFORE CHANGE",Array);

			for(int Index=0;Index<Array.Length;Index++)
			{
				Array[Index]+=100;
			}

			PrintArray("IN-OUT ARRAY AFTER CHANGE",Array);
		}
//-------------------------------------------------------------------------------------------------------
		/*
		//JAGGED ARRAYS NIE SU v WinRT PODPOROVANE.
		public void InArray([ReadOnlyArray] int[][] Array)
		{
			// EMPTY.
		}
		*/
//-------------------------------------------------------------------------------------------------------
		/*
		//JAGGED-DIMENSIONS ARRAYS NIE SU v WinRT PODPOROVANE.
		public void InArray([ReadOnlyArray] int[,] Array)
		{
			// EMPTY.
		}
		*/
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------