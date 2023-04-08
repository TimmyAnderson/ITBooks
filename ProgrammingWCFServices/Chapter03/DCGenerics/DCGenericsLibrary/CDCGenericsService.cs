using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace DCGenericsLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CDCGenericsService<T> : IDCGenericsContract<T>
	{
//-------------------------------------------------------------------------------------------------------
		public void SendInt(CGenericClass1<int> Value)
		{
			Console.WriteLine(string.Format("SendInt(): {0} !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendGenerics(CGenericClass1<T> Value)
		{
			Console.WriteLine(string.Format("SendGenerics(): {0} !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		/*
		public void SendGenericsMethod<M>(CGenericClass1<M> Value)
		{
			Console.WriteLine(string.Format("SendGenericsMethod<M>(): {0} !",Value));
		}
		*/
//-------------------------------------------------------------------------------------------------------
		public void SendCName1(CGenericClass1<CName> Value)
		{
			Console.WriteLine(string.Format("SendCName1(): {0} !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCName2(CGenericClass2<CName> Value)
		{
			Console.WriteLine(string.Format("SendCName2(): {0} !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCName3(CGenericClass3<CName> Value)
		{
			Console.WriteLine(string.Format("SendCName3(): {0} !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCName4(CGenericClass4<CName> Value)
		{
			Console.WriteLine(string.Format("SendCName4(): {0} !",Value));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------