using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace Exceptions
{
//-------------------------------------------------------------------------------------------------------
	// EXCEPTION trieda by mala byt serializovatelna.
	[Serializable]
	// EXCEPTION trieda by mala dedit z Exception.
	public class CGenericException<TExceptionParam> : Exception, ISerializable where TExceptionParam : CExceptionDetail
	{
//-------------------------------------------------------------------------------------------------------
		// Pre serializaciu/deserializaciu.
		private const string									EXCEPTION_PARAM_NAME="ExceptionParam";
//-------------------------------------------------------------------------------------------------------
		private readonly TExceptionParam						MExceptionParam;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CGenericException()
		{
		}
//-------------------------------------------------------------------------------------------------------
		public CGenericException(string Message=null, Exception InnerException=null)
			: this(null,Message,InnerException)
		{
		}
//-------------------------------------------------------------------------------------------------------
		public CGenericException(TExceptionParam ExceptionParam, string Message=null, Exception InnerException=null)
			: base(Message,InnerException)
		{
			MExceptionParam=ExceptionParam;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Deserializacny konstruktor.
		private CGenericException(SerializationInfo Info, StreamingContext Context)
			: base(Info,Context)
		{
			// Deserializujem MExceptionParam.
			MExceptionParam=(TExceptionParam) Info.GetValue(EXCEPTION_PARAM_NAME,typeof(TExceptionParam));

			Console.WriteLine("DESERIALIZATION !!!");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public TExceptionParam									ExceptionParam
		{
			get
			{
				return(MExceptionParam);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override void GetObjectData(SerializationInfo Info, StreamingContext Context)
		{
			// Serializujem MExceptionParam.
			Info.AddValue(EXCEPTION_PARAM_NAME,MExceptionParam);

			// Serailizujem ostatne FIELDS.
			base.GetObjectData(Info,Context);

			Console.WriteLine("SERIALIZATION !!!");
		}
//-------------------------------------------------------------------------------------------------------
		public override bool Equals(object Obj)
		{
			CGenericException<TExceptionParam>					Other=Obj as CGenericException<TExceptionParam>;

			if (Other==null)
			{
				return(false);
			}
			
			if (object.Equals(MExceptionParam,Other.MExceptionParam)==true && base.Equals(Obj)==true)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override int GetHashCode()
		{
			return(base.GetHashCode());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------