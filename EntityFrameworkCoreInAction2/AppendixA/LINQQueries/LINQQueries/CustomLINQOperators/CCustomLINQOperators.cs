using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace LINQQueries
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CCustomLINQOperators
	{
//----------------------------------------------------------------------------------------------------------------------
		public static IEnumerable<TType> ToLog<TType>(this IEnumerable<TType> This, string Text)
		{
			CLogIterator<TType>									Iterator=new CLogIterator<TType>(This,Text);

			return(Iterator);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static IEnumerable<TType> ToLog<TType>(this IQueryable<TType> This, string Text)
		{
			CLogIterator<TType>									Iterator=new CLogIterator<TType>(This,Text);

			return(Iterator);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static IEnumerable<int> MyBigNumbersWhere(this IEnumerable<int> This)
		{
			IEnumerable<int>									Result=This.Where(P => P>3);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public static IEnumerable<int> MyCustomOrderByOperator(this IEnumerable<int> This, bool SortAscending)
		{
			if (SortAscending==true)
			{
				IEnumerable<int>							Result=This.OrderBy(P => P);

				return(Result);
			}
			else
			{
				IEnumerable<int>							Result=This.OrderByDescending(P => P);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public static IQueryable<int> MyCustomOrderByOperator(this IQueryable<int> This, bool SortAscending)
		{
			if (SortAscending==true)
			{
				IQueryable<int>								Result=This.OrderBy(P => P);

				return(Result);
			}
			else
			{
				IQueryable<int>								Result=This.OrderByDescending(P => P);

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------