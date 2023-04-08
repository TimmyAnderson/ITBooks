using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
//------------------------------------------------------------------------
namespace SharedLibrary
{
//------------------------------------------------------------------------
	public class CMyCustomClassSlaveConverter1 : TypeConverter
	{
//-----------------------------------------------------------------------------
		public static string GetTypeNameWOArity(string Name)
		{
			int		Position;

			if ((Position=Name.LastIndexOf('`'))!=-1)
				return(Name.Remove(Position));
			else
				return(Name);
		}
//-----------------------------------------------------------------------------
		// Vrati meno triedy s generic parametrami, alebo iba do urovne 1.
		public static string GetTypeName(Type Type)
		{
			Type[]				GenericTypes=Type.GetGenericArguments();

			if (GenericTypes.Length==0)
				return(Type.Name);

			StringBuilder		SB=new StringBuilder();

			SB.Append(GetTypeNameWOArity(Type.Name));
			SB.Append("<");

			for (int i=0;i<GenericTypes.Length;i++)
			{
				if (i!=0)
					SB.Append(",");

				SB.Append(GenericTypes[i].Name);
			}

			SB.Append(">");

			return(SB.ToString());
		}
//------------------------------------------------------------------------
		private void ShowMethodName()
		{
			StackFrame		SF=new StackFrame(1);

			Debug.WriteLine(string.Format("!!! {0}.{1}() CALLED !",GetTypeName(SF.GetMethod().DeclaringType),SF.GetMethod().Name));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public override bool CanConvertFrom(ITypeDescriptorContext Context,Type SourceType)
		{
			ShowMethodName();
			return(base.CanConvertFrom(Context,SourceType));
		}
//------------------------------------------------------------------------
		public override bool CanConvertTo(ITypeDescriptorContext Context,Type DestinationType)
		{
			ShowMethodName();
			return(base.CanConvertTo(Context,DestinationType));
		}
//------------------------------------------------------------------------
		public override object ConvertFrom(ITypeDescriptorContext Context, CultureInfo Culture,object Value)
		{
			ShowMethodName();

			Debug.WriteLine(string.Format("!!! Value to CONVERT: ({0}) !",Value));

			return(new CMyCustomClassSlave1((string) Value));
		}
//------------------------------------------------------------------------
		public override object ConvertTo(ITypeDescriptorContext Context, CultureInfo Culture,object Value,Type DestinationType)
		{
			ShowMethodName();
			return(base.ConvertTo(Context,Culture,Value,DestinationType));
		}
//------------------------------------------------------------------------
		public override object CreateInstance(ITypeDescriptorContext Context,System.Collections.IDictionary PropertyValues)
		{
			ShowMethodName();
			return(base.CreateInstance(Context,PropertyValues));
		}
//------------------------------------------------------------------------
		public override bool Equals(object Obj)
		{
			ShowMethodName();
			return(base.Equals(Obj));
		}
//------------------------------------------------------------------------
		public override bool GetCreateInstanceSupported(ITypeDescriptorContext Context)
		{
			ShowMethodName();
			return(base.GetCreateInstanceSupported(Context));
		}
//------------------------------------------------------------------------
		public override int GetHashCode()
		{
			ShowMethodName();
			return(base.GetHashCode());
		}
//------------------------------------------------------------------------
		public override PropertyDescriptorCollection GetProperties(ITypeDescriptorContext Context,object Value,Attribute[] Attributes)
		{
			ShowMethodName();
			return(base.GetProperties(Context,Value,Attributes));
		}
//------------------------------------------------------------------------
		public override bool GetPropertiesSupported(ITypeDescriptorContext Context)
		{
			ShowMethodName();
			return(base.GetPropertiesSupported(Context));
		}
//------------------------------------------------------------------------
		public override StandardValuesCollection GetStandardValues(ITypeDescriptorContext Context)
		{
			ShowMethodName();
			return(base.GetStandardValues(Context));
		}
//------------------------------------------------------------------------
		public override bool GetStandardValuesExclusive(ITypeDescriptorContext Context)
		{
			ShowMethodName();
			return(base.GetStandardValuesExclusive(Context));
		}
//------------------------------------------------------------------------
		public override bool GetStandardValuesSupported(ITypeDescriptorContext Context)
		{
			ShowMethodName();
			return(base.GetStandardValuesSupported(Context));
		}
//------------------------------------------------------------------------
		public override bool IsValid(ITypeDescriptorContext Context,object Value)
		{
			ShowMethodName();
			return(base.IsValid(Context,Value));
		}
//------------------------------------------------------------------------
		public override string ToString()
		{
			ShowMethodName();
			return(base.ToString());
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------