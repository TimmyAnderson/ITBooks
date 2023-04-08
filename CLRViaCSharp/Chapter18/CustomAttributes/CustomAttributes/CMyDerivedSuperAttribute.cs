using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CustomAttributes
{
//-------------------------------------------------------------------------------------------------------
	// CUSTOM ATTRIBUTE MUSI BYT ZDEDENY z triedy Attribute.
	// ATTRIBUTE je INHERITED.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Parameter | AttributeTargets.ReturnValue,AllowMultiple=false,Inherited=true)]
	public class CMyDerivedSuperAttribute : CMySuperAttribute
	{
//-------------------------------------------------------------------------------------------------------
		public CMyDerivedSuperAttribute(string LastName)
			: base(LastName)
		{
			Console.WriteLine("!!!!! CMyDerivedSuperAttribute CONSTRUCTOR CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------