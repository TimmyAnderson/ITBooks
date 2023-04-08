using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace WCFSerializersTest
{
//-------------------------------------------------------------------------------------------------------
    // Tento helper class zjednodusit pouzivanie SERIALIZERA pouzitim TEMPLATE na ziskanie STRONGLY TYPED OPERACII nad SERIALIZER.
	class CXmlObjectSerializerHelper<T> : XmlObjectSerializer
	{
//-------------------------------------------------------------------------------------------------------
		private DataContractSerializer							MDataContractSerializer;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CXmlObjectSerializerHelper()
		{
			MDataContractSerializer=new DataContractSerializer(typeof(T));
		}      
//-------------------------------------------------------------------------------------------------------
		public CXmlObjectSerializerHelper(IList<Type> KnownTypes)
		{
			MDataContractSerializer= new DataContractSerializer(typeof(T), KnownTypes);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override object ReadObject(XmlDictionaryReader Reader)
		{
			return(MDataContractSerializer.ReadObject(Reader));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool IsStartObject(XmlDictionaryReader Reader)
		{
			return(MDataContractSerializer.IsStartObject(Reader));
		}
//-------------------------------------------------------------------------------------------------------
		public override object ReadObject(XmlDictionaryReader Reader, bool VerifyObjectName)
		{
			return(MDataContractSerializer.ReadObject(Reader, VerifyObjectName));
		}
//-------------------------------------------------------------------------------------------------------
		public override void WriteEndObject(XmlDictionaryWriter Writer)
		{
			MDataContractSerializer.WriteEndObject(Writer);
		}
//-------------------------------------------------------------------------------------------------------
		public override void WriteObjectContent(XmlDictionaryWriter Writer, object Graph)
		{
			MDataContractSerializer.WriteObjectContent(Writer, Graph);
		}
//-------------------------------------------------------------------------------------------------------
		public override void WriteStartObject(XmlDictionaryWriter Writer, object Graph)
		{
			MDataContractSerializer.WriteStartObject(Writer, Graph);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public new T ReadObject(Stream Stream)
		{
			return((T) MDataContractSerializer.ReadObject(Stream));
		}
//-------------------------------------------------------------------------------------------------------
		public new T ReadObject(XmlReader Reader)
		{
			return((T) MDataContractSerializer.ReadObject(Reader));
		}
//-------------------------------------------------------------------------------------------------------
		public new bool IsStartObject(XmlReader Reader)
		{
			return(MDataContractSerializer.IsStartObject(Reader));
		}
//-------------------------------------------------------------------------------------------------------
		public new T ReadObject(XmlReader Reader, bool VerifyObjectName)
		{
			return((T) MDataContractSerializer.ReadObject(Reader, VerifyObjectName));
		}
//-------------------------------------------------------------------------------------------------------
		public new void WriteEndObject(XmlWriter Writer)
		{
			MDataContractSerializer.WriteEndObject(Writer);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void WriteObject(Stream Stream, T Graph)
		{
			MDataContractSerializer.WriteObject(Stream, Graph);
		}
//-------------------------------------------------------------------------------------------------------
		public void WriteObject(XmlDictionaryWriter Writer, T Graph)
		{
			MDataContractSerializer.WriteObject(Writer, Graph);
		}
//-------------------------------------------------------------------------------------------------------
		public void WriteObject(XmlWriter Writer, T Graph)
		{
			MDataContractSerializer.WriteObject(Writer, Graph);
		}
//-------------------------------------------------------------------------------------------------------
		public void WriteObjectContent(XmlWriter Writer, T Graph)
		{
			MDataContractSerializer.WriteObjectContent(Writer, Graph);
		}
//-------------------------------------------------------------------------------------------------------
		public void WriteStartObject(XmlWriter Writer, T Graph)
		{
			MDataContractSerializer.WriteStartObject(Writer, Graph);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------