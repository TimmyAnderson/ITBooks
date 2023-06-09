﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ObjTypes
{
//-------------------------------------------------------------------------------------------------------
	public class Comparer<T> where T: IComparable
	{
//-------------------------------------------------------------------------------------------------------
        public T GreaterThan(T D1, T D2)
        {
            int			Ret=D1.CompareTo(D2);

            if (Ret>0)
                return(D1);
            else
                return(D2);
        }
//-------------------------------------------------------------------------------------------------------
        public T LessThan(T D1, T D2)
        {
            int			Ret=D1.CompareTo(D2);

            if (Ret<0)
                return(D1);
            else
                return(D2);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------