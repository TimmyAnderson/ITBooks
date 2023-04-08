using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace OptionalAndDefault
{
//-------------------------------------------------------------------------------------------------------
	public class CTestClass
	{
//-------------------------------------------------------------------------------------------------------
		public string											this[string Value]
		{
			get
			{
				return(Value.ToUpper());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! DEFAULT HODNOTY MUSIA BYT KONSTANTY.
		public void Test1(string FirstName, string LastName="Anderson", int Age=12, Guid ID=new Guid(), int Code=default(int))
		{
			Console.WriteLine(string.Format("FirstName: [{0}], LastName: [{1}], Age: [{2}], ID: [{3}], Code: [{4}] !",FirstName,LastName,Age,ID,Code));
		}
//-------------------------------------------------------------------------------------------------------
		public void Test2(string FirstName, string LastName, int Age, out string FullName)
		{
			FullName=string.Format("{0} {1}",FirstName,LastName);

			Console.WriteLine(string.Format("FirstName: [{0}], LastName: [{1}], Age: [{2}] !",FirstName,LastName,Age));
		}
//-------------------------------------------------------------------------------------------------------
		public void Test3(string FirstName, string LastName, int Age)
		{
			Console.WriteLine(string.Format("FirstName: [{0}], LastName: [{1}], Age: [{2}] !",FirstName,LastName,Age));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------