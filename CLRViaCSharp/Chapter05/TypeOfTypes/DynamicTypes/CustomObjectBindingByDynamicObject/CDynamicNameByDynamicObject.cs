using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Dynamic;
//-------------------------------------------------------------------------------------------------------
namespace DynamicTypes
{
//-------------------------------------------------------------------------------------------------------
	// !!!!! CLASS implementuje CUSTOM OBJECT BINDER dedim z CLASS DynamicObject.
	// !!!!! CLASS DynamicObject implementuje IDynamicMetaObjectProvider, ktory vracia INTERNY (MS implementovany) OBJECT BINDER, ktory zjednodusuje implementaciu CUSTOM OBJECT BINDER.
	public sealed class CDynamicNameByDynamicObject : DynamicObject
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MFirstName;
		private readonly string									MLastName;
		private readonly int									MAge;
//-------------------------------------------------------------------------------------------------------
		private int												MPrivateField;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDynamicNameByDynamicObject(string FirstName, string LastName, int Age)
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
		private void SomeXXX()
		{
			Console.WriteLine("METHOD SomeXXX() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool TryBinaryOperation(BinaryOperationBinder Binder, object Arg, out object Result)
		{
			Console.WriteLine("TryBinaryOperation() CALLED !");

			return(base.TryBinaryOperation(Binder,Arg,out Result));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool TryConvert(ConvertBinder Binder, out object Result)
		{
			Console.WriteLine("TryConvert() CALLED !");

			return(base.TryConvert(Binder,out Result));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool TryCreateInstance(CreateInstanceBinder Binder, object[] Args, out object Result)
		{
			Console.WriteLine("TryCreateInstance() CALLED !");

			return(base.TryCreateInstance(Binder,Args,out Result));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool TryDeleteIndex(DeleteIndexBinder Binder, object[] Indexes)
		{
			Console.WriteLine("TryDeleteIndex() CALLED !");

			return(base.TryDeleteIndex(Binder,Indexes));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool TryDeleteMember(DeleteMemberBinder Binder)
		{
			Console.WriteLine("TryDeleteMember() CALLED !");

			return(base.TryDeleteMember(Binder));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool TryGetIndex(GetIndexBinder Binder, object[] Indexes, out object Result)
		{
			Console.WriteLine("TryGetIndex() CALLED !");

			return(base.TryGetIndex(Binder,Indexes,out Result));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool TryInvoke(InvokeBinder Binder, object[] Args, out object Result)
		{
			Console.WriteLine("TryInvoke() CALLED !");

			return(base.TryInvoke(Binder,Args,out Result));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool TrySetIndex(SetIndexBinder Binder, object[] Indexes, object Value)
		{
			Console.WriteLine("TrySetIndex() CALLED !");

			return(base.TrySetIndex(Binder,Indexes,Value));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool TrySetMember(SetMemberBinder Binder, object Value)
		{
			Console.WriteLine("TrySetMember() CALLED !");

			if (Binder.Name=="MField")
			{
				MPrivateField=(int) Value;

				return(true);
			}
			else
			{
				return(base.TrySetMember(Binder,Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override bool TryUnaryOperation(UnaryOperationBinder Binder, out object Result)
		{
			Console.WriteLine("TryUnaryOperation() CALLED !");

			return(base.TryUnaryOperation(Binder,out Result));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool TryGetMember(GetMemberBinder Binder, out object Result)
		{
			Console.WriteLine("TryGetMember() CALLED !");

			if (Binder.Name=="MField")
			{
				Result=MPrivateField;

				return(true);
			}
			else
			{
				return(base.TryGetMember(Binder,out Result));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override bool TryInvokeMember(InvokeMemberBinder Binder, object[] Args, out object Result)
		{
			Console.WriteLine("TryInvokeMember() CALLED !");

			if (Binder.Name=="XXX")
			{
				// Simuluje sa vyvolanie METHOD XXX().
				SomeXXX();

				Result=null;

				return(true);
			}
			else
			{
				return(base.TryInvokeMember(Binder,Args,out Result));
			}
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