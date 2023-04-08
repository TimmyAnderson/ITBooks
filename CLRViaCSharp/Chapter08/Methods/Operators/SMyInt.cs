using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Operators
{
//-------------------------------------------------------------------------------------------------------
	public struct SMyInt
	{
//-------------------------------------------------------------------------------------------------------
		private int												MInt;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public SMyInt(int Int)
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
		public static SMyInt operator+(SMyInt MyInt1, SMyInt MyInt2)
		{
			SMyInt												ReturnValue=new SMyInt(MyInt1.MInt+MyInt2.MInt);

			Console.WriteLine("Operator+ CALLED !");

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		public static SMyInt operator+(SMyInt MyInt, int Int)
		{
			SMyInt												ReturnValue=new SMyInt(MyInt.MInt+Int);

			Console.WriteLine("Operator+ CALLED !");

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Ked je pretazeny OPERATOR== MUSI sa pretazit aj OPERATOR!=, inak COMPILER hodi ERROR.
		public static bool operator==(SMyInt MyInt1, SMyInt MyInt2)
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
		public static bool operator!=(SMyInt MyInt1, SMyInt MyInt2)
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
		// Konvertuje SMyInt na Int32.
		public static implicit operator Int32(SMyInt Value)
		{
			Console.WriteLine("IMPLICIT CASTING operator CALLED !");

			return(Value.Int);
		}
//-------------------------------------------------------------------------------------------------------
		// Konvertuje Int32 na SMyInt.
		public static explicit operator SMyInt(int Value)
		{
			Console.WriteLine("EXPLICIT CASTING operator CALLED !");

			return(new SMyInt(Value));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Ked je pretazeny OPERATOR== a OPERATOR!= C# hodi WARNING ak nie je pretazena METHOD Object.Equals().
		public override bool Equals(object Object)
		{
			if (Object==null || Object.GetType()!=typeof(SMyInt))
			{
				return(false);

			}

			SMyInt												Value=(SMyInt) Object;

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