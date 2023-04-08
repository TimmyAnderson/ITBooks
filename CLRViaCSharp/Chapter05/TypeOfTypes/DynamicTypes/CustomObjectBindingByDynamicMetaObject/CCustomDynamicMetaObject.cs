using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Linq.Expressions;
using System.Dynamic;
//-------------------------------------------------------------------------------------------------------
namespace DynamicTypes
{
//-------------------------------------------------------------------------------------------------------
	// !!!!! CLASS implementuje CUSTOM OBJECT BINDER dedim z CLASS DynamicMetaObject.
	// !!! CLASS CCustomDynamicMetaObject sluzi ako CUSTOM OBJECT BINDER pre CLASS CDynamicNameByDynamicMetaObject.
	// !!!!! CLASS implementuje jednoduchy CUSTOM OBJECT BINDING, kedy VACSINA BINDINGS skonci vratenim CONSTANT 3.
	public sealed class CCustomDynamicMetaObject : DynamicMetaObject
	{
//-------------------------------------------------------------------------------------------------------
        public CCustomDynamicMetaObject(Expression Expression, object Object)
            : base(Expression,BindingRestrictions.Empty,Object)
        {
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private DynamicMetaObject ReturnConstant()
        {
            // Vracia VZDY hodnotu 3.
			DynamicMetaObject									DMO=new DynamicMetaObject(Expression.Convert(Expression.Constant(3),typeof(object)),BindingRestrictions.GetExpressionRestriction(Expression.Constant(true)));

            return(DMO);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindConvert(ConvertBinder Binder)
        {
            Console.WriteLine(string.Format("BindConvert() CALLED for [{0}] !",Binder.ReturnType));

			DynamicMetaObject									DMO=new DynamicMetaObject(Expression.Constant(3, typeof(int)),BindingRestrictions.GetExpressionRestriction(Expression.Constant(true)));

            return(DMO);
        }
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindInvoke(InvokeBinder Binder, DynamicMetaObject[] Args)
        {
            Console.WriteLine(string.Format("BindInvoke() CALLED for [{0}] !",Binder.ReturnType));
            
			DynamicMetaObject									DMO=ReturnConstant();

            return(DMO);
        }
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindInvokeMember(InvokeMemberBinder Binder, DynamicMetaObject[] Args)
        {
            Console.WriteLine(string.Format("BindInvokeMember() CALLED for [{0}] !",Binder.ReturnType));

			CDynamicNameByDynamicMetaObject						TypedObject=Value as CDynamicNameByDynamicMetaObject;

			if (TypedObject!=null)
			{
				Type											T=typeof(CDynamicNameByDynamicMetaObject);
				MethodInfo										MI=T.GetMethod(Binder.Name,BindingFlags.Instance | BindingFlags.Public);

				if (MI!=null)
				{
					Expression									Instance=Expression.Constant(TypedObject,typeof(CDynamicNameByDynamicMetaObject));
					Expression[]								Arguments=Args.Select(P => P.Expression).ToArray();
					Expression									Call=Expression.Call(Instance,MI,Arguments);

					if (MI.ReturnType==typeof(void))
					{
						// !!!!! Kedze BINDER pozaduje aby EXPRESSION vratila Object, aj ked METHOD NEMA RETURN VALUE, tak je nutne PODHODIT UMELU HODNOTU NULL.
						Expression								ReturnValue=Expression.Default(Binder.ReturnType);
						Expression								Code=Expression.Block(Call,ReturnValue);

						DynamicMetaObject						DMO=new DynamicMetaObject(Code,BindingRestrictions.GetExpressionRestriction(Expression.Constant(true)));

						return(DMO);
					}
					else
					{
						DynamicMetaObject						DMO=new DynamicMetaObject(Call,BindingRestrictions.GetExpressionRestriction(Expression.Constant(true)));

						return(DMO);
					}
				}
				else
				{
					DynamicMetaObject							DMO=ReturnConstant();

					return(DMO);
				}
			}
			else
			{
				DynamicMetaObject								DMO=ReturnConstant();

				return(DMO);
			}
        }
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindCreateInstance(CreateInstanceBinder Binder, DynamicMetaObject[] Args)
        {
            Console.WriteLine(string.Format("BindCreateInstance() CALLED for [{0}] !",Binder.ReturnType));

			DynamicMetaObject									DMO=ReturnConstant();

            return(DMO);
        }
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindUnaryOperation(UnaryOperationBinder Binder)
        {
            Console.WriteLine(string.Format("BindUnaryOperation() CALLED for [{0}] !",Binder.ReturnType));

			DynamicMetaObject									DMO=ReturnConstant();

            return(DMO);
        }
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindBinaryOperation(BinaryOperationBinder Binder, DynamicMetaObject Arg)
        {
            Console.WriteLine(string.Format("BindBinaryOperation() CALLED for [{0}] !",Binder.ReturnType));

			DynamicMetaObject									DMO=ReturnConstant();

            return(DMO);
        }
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindDeleteIndex(DeleteIndexBinder Binder, DynamicMetaObject[] Indexes)
        {
            Console.WriteLine(string.Format("BindDeleteIndex() CALLED for [{0}] !",Binder.ReturnType));

			DynamicMetaObject									DMO=ReturnConstant();

            return(DMO);
        }
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindDeleteMember(DeleteMemberBinder Binder)
        {
            Console.WriteLine(string.Format("BindDeleteMember() CALLED for [{0}] !",Binder.ReturnType));

			DynamicMetaObject									DMO=ReturnConstant();

            return(DMO);
        }
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindSetIndex(SetIndexBinder Binder, DynamicMetaObject[] Indexes, DynamicMetaObject Value)
        {
            Console.WriteLine(string.Format("BindSetIndex() CALLED for [{0}] !",Binder.ReturnType));

			DynamicMetaObject									DMO=ReturnConstant();

            return(DMO);
        }
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindGetIndex(GetIndexBinder Binder, DynamicMetaObject[] Indexes)
        {
            Console.WriteLine(string.Format("BindGetIndex() CALLED for [{0}] !",Binder.ReturnType));

			DynamicMetaObject									DMO=ReturnConstant();

            return(DMO);
        }
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindGetMember(GetMemberBinder Binder)
        {
            Console.WriteLine(string.Format("BindGetMember() CALLED for [{0}] !",Binder.ReturnType));

			CDynamicNameByDynamicMetaObject						TypedObject=Value as CDynamicNameByDynamicMetaObject;

			if (TypedObject!=null)
			{
				if (Binder.Name=="FirstName")
				{
					DynamicMetaObject							DMO=new DynamicMetaObject(Expression.Convert(Expression.Constant(TypedObject.FirstName),typeof(object)),BindingRestrictions.GetExpressionRestriction(Expression.Constant(true)));

					return(DMO);
				}
				else if (Binder.Name=="LastName")
				{
					DynamicMetaObject							DMO=new DynamicMetaObject(Expression.Convert(Expression.Constant(TypedObject.LastName),typeof(object)),BindingRestrictions.GetExpressionRestriction(Expression.Constant(true)));

					return(DMO);
				}
				else if (Binder.Name=="Age")
				{
					DynamicMetaObject							DMO=new DynamicMetaObject(Expression.Convert(Expression.Constant(TypedObject.Age),typeof(object)),BindingRestrictions.GetExpressionRestriction(Expression.Constant(true)));

					return(DMO);
				}
			}

			// !!!!! DEFAULT BINDING, ktory sa pouzije, ak hladany MEMBER NEEXISTUJE.
			DynamicMetaObject									DefaultDMO=ReturnConstant();

            return(DefaultDMO);
        }
//-------------------------------------------------------------------------------------------------------
        public override DynamicMetaObject BindSetMember(SetMemberBinder Binder, DynamicMetaObject Value)
        {
            Console.WriteLine(string.Format("BindSetMember() CALLED for [{0}] !",Binder.ReturnType));

			DynamicMetaObject									DMO=ReturnConstant();

            return(DMO);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------