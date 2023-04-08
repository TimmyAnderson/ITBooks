using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.Xml;
using System.IO;
using System.Xml.Linq;
//-------------------------------------------------------------------------------------------------------
namespace DataContractSerializerWrapper
{
//-------------------------------------------------------------------------------------------------------
	public class DataContractSerializer<T> : XmlObjectSerializer
	{
//-------------------------------------------------------------------------------------------------------
		private DataContractSerializer							MDataContractSerializer;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public DataContractSerializer()
		{
			MDataContractSerializer=new DataContractSerializer(typeof(T));
		}      
//-------------------------------------------------------------------------------------------------------
		public DataContractSerializer(IList<Type> KnownTypes)
		{
			MDataContractSerializer=new DataContractSerializer(typeof(T),KnownTypes);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public new bool IsStartObject(XmlReader Reader)
		{
			return(MDataContractSerializer.IsStartObject(Reader));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool IsStartObject(XmlDictionaryReader Reader)
		{
			return(MDataContractSerializer.IsStartObject(Reader));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public new T ReadObject(Stream Stream)
		{
			return((T)MDataContractSerializer.ReadObject(Stream));
		}
//-------------------------------------------------------------------------------------------------------
		public new T ReadObject(XmlReader Reader)
		{
			return((T)MDataContractSerializer.ReadObject(Reader));
		}
//-------------------------------------------------------------------------------------------------------
		public new T ReadObject(XmlReader Reader, bool VerifyObjectName)
		{
			return((T)MDataContractSerializer.ReadObject(Reader, VerifyObjectName));
		}
//-------------------------------------------------------------------------------------------------------
		public override object ReadObject(XmlDictionaryReader Reader)
		{
			return(MDataContractSerializer.ReadObject(Reader));
		}
//-------------------------------------------------------------------------------------------------------
		public override object ReadObject(XmlDictionaryReader Reader, bool VerifyObjectName)
		{
			return(MDataContractSerializer.ReadObject(Reader, VerifyObjectName));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void WriteStartObject(XmlWriter Writer, T Graph)
		{
			MDataContractSerializer.WriteStartObject(Writer, Graph);
		}
//-------------------------------------------------------------------------------------------------------
		public override void WriteStartObject(XmlDictionaryWriter Writer, object Graph)
		{
			MDataContractSerializer.WriteStartObject(Writer, Graph);
		}
//-------------------------------------------------------------------------------------------------------
		public void WriteObjectContent(XmlWriter Writer, T Graph)
		{
			MDataContractSerializer.WriteObjectContent(Writer, Graph);
		}
//-------------------------------------------------------------------------------------------------------
		public override void WriteObjectContent(XmlDictionaryWriter Writer, object Graph)
		{
			MDataContractSerializer.WriteObjectContent(Writer,Graph);
		}
//-------------------------------------------------------------------------------------------------------
		public new void WriteEndObject(XmlWriter Writer)
		{
			MDataContractSerializer.WriteEndObject(Writer);
		}
//-------------------------------------------------------------------------------------------------------
		public override void WriteEndObject(XmlDictionaryWriter Writer)
		{
			MDataContractSerializer.WriteEndObject(Writer);
		}
//-------------------------------------------------------------------------------------------------------
		public void WriteObject(Stream Stream, T Graph)
		{
			MDataContractSerializer.WriteObject(Stream, Graph);
		}
//-------------------------------------------------------------------------------------------------------
		public void WriteObject(XmlWriter Writer, T Graph)
		{
			MDataContractSerializer.WriteObject(Writer, Graph);
		}
//-------------------------------------------------------------------------------------------------------
		public void WriteObject(XmlDictionaryWriter Writer, T Graph)
		{
			MDataContractSerializer.WriteObject(Writer, Graph);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string Dump(T Graph, bool WithFormatting)
		{
			MemoryStream			MS=new MemoryStream(1000);

			MDataContractSerializer.WriteObject(MS, Graph);

			MS.Seek(0,SeekOrigin.Begin);

			using(StreamReader SR=new StreamReader(MS))
			{
				string				Text=SR.ReadToEnd();

				if (WithFormatting==true)
				{
					XElement			Element=XElement.Parse(Text);

					Text=Element.ToString(SaveOptions.None);
				}

				return(Text);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------