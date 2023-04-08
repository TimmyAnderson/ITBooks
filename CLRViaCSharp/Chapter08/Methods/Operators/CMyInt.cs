using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Operators
{
//-------------------------------------------------------------------------------------------------------
	public class CMyInt
	{
//-------------------------------------------------------------------------------------------------------
		private int												MInt;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyInt(int Int)
		{
			MInt=Int;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int												Int
		{
			get
			{
				return(MInt);
			}
			set
			{
				MInt=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static CMyInt operator+(CMyInt MyInt1, CMyInt MyInt2)
		{
			CMyInt												ReturnValue=new CMyInt(MyInt1.MInt+MyInt2.MInt);

			Console.WriteLine("Operator+ CALLED !");

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		public static CMyInt operator+(CMyInt MyInt, int Int)
		{
			CMyInt												ReturnValue=new CMyInt(MyInt.MInt+Int);

			Console.WriteLine("Operator+ CALLED !");

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Ked je pretazeny OPERATOR== MUSI sa pretazit aj OPERATOR!=, inak COMPILER hodi ERROR.
		public static bool operator==(CMyInt MyInt1, CMyInt MyInt2)
		{
			object												ObjectMyInt1=MyInt1;
			object												ObjectMyInt2=MyInt2;

			if (ObjectMyInt1==null && ObjectMyInt2==null)
			{
				return(true);
			}
			else if (ObjectMyInt1!=null && ObjectMyInt2==null)
			{
				return(false);
			}
			else if (ObjectMyInt1==null && ObjectMyInt2!=null)
			{
				return(false);
			}
			else
			{
				if (MyInt1.MInt==MyInt2.MInt)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Ked je pretazeny OPERATOR== MUSI sa pretazit aj OPERATOR!=, inak COMPILER hodi ERROR.
		public static bool operator!=(CMyInt MyInt1, CMyInt MyInt2)
		{
			object												ObjectMyInt1=MyInt1;
			object												ObjectMyInt2=MyInt2;

			if (ObjectMyInt1==null && ObjectMyInt2==null)
			{
				return(false);
			}
			else if (ObjectMyInt1!=null && ObjectMyInt2==null)
			{
				return(true);
			}
			else if (ObjectMyInt1==null && ObjectMyInt2!=null)
			{
				return(true);
			}
			else
			{
				if (MyInt1.MInt==MyInt2.MInt)
				{
					return(false);
				}
				else
				{
					return(true);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Konvertuje CMyInt na Int32.
		public static implicit operator Int32(CMyInt Value)
		{
			Console.WriteLine("IMPLICIT CASTING operator CALLED !");

			return(Value.Int);
		}
//-------------------------------------------------------------------------------------------------------
		// Konvertuje Int32 na CMyInt.
		public static explicit operator CMyInt(int Value)
		{
			Console.WriteLine("EXPLICIT CASTING operator CALLED !");

			return(new CMyInt(Value));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Ked je pretazeny OPERATOR== a OPERATOR!= C# hodi WARNING ak nie je pretazena METHOD Object.Equals().
		public override bool Equals(object Object)
		{
			CMyInt												Value=Object as CMyInt;

			if (MInt==Value.MInt)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Ked je pretazeny OPERATOR== a OPERATOR!= C# hodi WARNING ak nie je pretazena METHOD Object.GetHashCode().
		public override int GetHashCode()
		{
 			return(MInt.GetHashCode());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------