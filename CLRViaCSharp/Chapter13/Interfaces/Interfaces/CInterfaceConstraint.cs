using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Interfaces
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CInterfaceConstraint
	{
//-------------------------------------------------------------------------------------------------------
		public void DoTestWithoutConstraints1(int Param1, int Param2)
		{
			// !!!!! Tiez sa nepouziva BOXING.
			/*
				ldarga											Param1
				ldarg											Param2
				call											instance int32 [mscorlib]System.Int32::CompareTo(int32)
			*/
			if (Param1.CompareTo(Param2)<=0)
			{
				Console.WriteLine(string.Format("VALUE1 [{0}] <= VALUE2 [{1}] !",Param1,Param2));
			}
			else
			{
				Console.WriteLine(string.Format("VALUE1 [{0}] > VALUE2 [{1}] !",Param1,Param2));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void DoTestWithoutConstraints2(int Param1, int Param2)
		{
			// !!!!! Pouziva sa BOXING.
			/*
				ldarga											Param1
				ldarg											Param2
				call											instance bool [mscorlib]System.Int32::Equals(int32)
			*/
			if (Param1.Equals(Param2)==true)
			{
				Console.WriteLine(string.Format("VALUE1 [{0}] == VALUE2 [{1}] !",Param1,Param2));
			}
			else
			{
				Console.WriteLine(string.Format("VALUE1 [{0}] != VALUE2 [{1}] !",Param1,Param2));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void DoTestWithConstraints<TParameter>(TParameter Param1, TParameter Param2) where TParameter : IComparable<TParameter>, IEquatable<TParameter>
		{
			// !!!!! Kedze sa definovali CONSTRAINTS, tak sa pre VALUE TYPES NEPOUZIJE BOXING.
			/*
				ldarga											Param1
				ldarg											Param2
				constrained.									!!TParameter
				callvirt										instance int32 class [mscorlib]System.IComparable`1<!!TParameter>::CompareTo(!0)
			*/
			if (Param1.CompareTo(Param2)<=0)
			{
				Console.WriteLine(string.Format("VALUE1 [{0}] <= VALUE2 [{1}] !",Param1,Param2));
			}
			else
			{
				Console.WriteLine(string.Format("VALUE1 [{0}] > VALUE2 [{1}] !",Param1,Param2));
			}

			// !!!!! Kedze sa definovali CONSTRAINTS, tak sa pre VALUE TYPES NEPOUZIJE BOXING.
			/*
				ldarga											Param1
				ldarg											Param2
				constrained.									!!TParameter
				callvirt										instance bool class [mscorlib]System.IEquatable`1<!!TParameter>::Equals(!0)
			*/
			if (Param1.Equals(Param2)==true)
			{
				Console.WriteLine(string.Format("VALUE1 [{0}] == VALUE2 [{1}] !",Param1,Param2));
			}
			else
			{
				Console.WriteLine(string.Format("VALUE1 [{0}] != VALUE2 [{1}] !",Param1,Param2));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------