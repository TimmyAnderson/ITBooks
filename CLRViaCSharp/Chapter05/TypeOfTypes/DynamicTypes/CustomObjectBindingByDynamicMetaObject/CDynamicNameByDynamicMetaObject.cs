using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Dynamic;
using System.Linq.Expressions;
//-------------------------------------------------------------------------------------------------------
namespace DynamicTypes
{
//-------------------------------------------------------------------------------------------------------
	// !!! Implementacia IDynamicMetaObjectProvider umoznuje CLASS CDynamicNameUsingDynamicMetaObject definovat CUSTOM OBJECT BINDER.
	public sealed class CDynamicNameByDynamicMetaObject : IDynamicMetaObjectProvider
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MFirstName;
		private readonly string									MLastName;
		private readonly int									MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDynamicNameByDynamicMetaObject(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												Age
		{
			get
			{
				return(MAge);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!!!! METHOD musi vracat implementaciu CUSTOM OBJECT BINDER. V tomto pripade je to CLASS CCustomDynamicMetaObject, ktora dedi z CLASS DynamicMetaObject.
		public DynamicMetaObject GetMetaObject(Expression Parameter)
		{
			Console.WriteLine("GetMetaObject() CALLED !");

			// !!! CLASS CCustomMetaObject sluzi ako CUSTOM OBJECT BINDER pre CLASS CDynamicName.
			CCustomDynamicMetaObject							MetaObject=new CCustomDynamicMetaObject(Parameter,this);

			return(MetaObject);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Print()
		{
			Console.WriteLine(string.Format("First name: [{0}], Last name: [{1}], Age: [{2}] !",MFirstName,MLastName,MAge));
		}
//-------------------------------------------------------------------------------------------------------
		public string PrintWithParamsAndReturnValue(string Param)
		{
			string												Text=string.Format("{0} - First name: [{1}], Last name: [{2}], Age: [{3}] !",Param,MFirstName,MLastName,MAge);

			Console.WriteLine(Text);

			return("SOME RETURN VALUE !!!!");
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("First name: [{0}], Last name: [{1}], Age: [{2}]",MFirstName,MLastName,MAge));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------