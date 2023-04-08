using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Globalization;
//-------------------------------------------------------------------------------------------------------
namespace MemberInfoTest
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CMySimpleBinder : Binder
	{
//-------------------------------------------------------------------------------------------------------
		public override FieldInfo BindToField(BindingFlags BindingAttr, FieldInfo[] Match, object Value, CultureInfo Culture)
		{
			Console.WriteLine("!!!!! BindToField() CALLED !");

			return(Type.DefaultBinder.BindToField(BindingAttr,Match,Value,Culture));
		}
//-------------------------------------------------------------------------------------------------------
		public override MethodBase BindToMethod(BindingFlags BindingAttr, MethodBase[] Match, ref object[] Args, ParameterModifier[] Modifiers, CultureInfo Culture, string[] Names, out object State)
		{
			Console.WriteLine("!!!!! BindToMethod() CALLED !");

			foreach(MethodBase SingleMatch in Match)
			{
				Console.WriteLine(string.Format("\tMATCH [{0}] !",SingleMatch));
			}

			State=null;

			if ((BindingAttr & BindingFlags.CreateInstance)!=0 && Match[0].DeclaringType==typeof(CName) && Match[0].Name==".ctor")
			{
				Type											T=Match[0].DeclaringType;

				// Najdem ConstructorInfo pre CName.
				ConstructorInfo									CI=T.GetConstructor(Args.Select(P => P.GetType()).ToArray());

				return(CI);
			}
			else if ((BindingAttr & BindingFlags.InvokeMethod)!=0 && Match[0].DeclaringType==typeof(CName) && Match[0].Name=="PrintName")
			{
				Type											T=Match[0].DeclaringType;

				// Najdem MethodInfo CName.PrintName().
				MethodInfo										MI=T.GetMethod(Match[0].Name,Args.Select(P => P.GetType()).ToArray());

				return(MI);
			}
			else
				return(Type.DefaultBinder.BindToMethod(BindingAttr,Match,ref Args,Modifiers,Culture,Names,out State));
		}
//-------------------------------------------------------------------------------------------------------
		public override object ChangeType(object Value, Type Type, CultureInfo Culture)
		{
			Console.WriteLine("!!!!! ChangeType() CALLED !");

			return(Type.DefaultBinder.ChangeType(Value,Type,Culture));
		}
//-------------------------------------------------------------------------------------------------------
		public override void ReorderArgumentArray(ref object[] Args, object State)
		{
			Console.WriteLine("!!!!! ReorderArgumentArray() CALLED !");

			Type.DefaultBinder.ReorderArgumentArray(ref Args,State);
		}
//-------------------------------------------------------------------------------------------------------
		public override MethodBase SelectMethod(BindingFlags BindingAttr, MethodBase[] Match, Type[] Types, ParameterModifier[] Modifiers)
		{
			Console.WriteLine("!!!!! SelectMethod() CALLED !");

			return(Type.DefaultBinder.SelectMethod(BindingAttr,Match,Types,Modifiers));
		}
//-------------------------------------------------------------------------------------------------------
		public override PropertyInfo SelectProperty(BindingFlags BindingAttr, PropertyInfo[] Match, Type ReturnType, Type[] Indexes, ParameterModifier[] Modifiers)
		{
			Console.WriteLine("!!!!! SelectProperty() CALLED !");

			return(Type.DefaultBinder.SelectProperty(BindingAttr,Match,ReturnType,Indexes,Modifiers));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------