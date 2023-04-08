using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Xml;
//-------------------------------------------------------------------------------------------------------
namespace MessagesTest
{
//-------------------------------------------------------------------------------------------------------
	// Implementujem CUSTOM HEADER.
	public class CCustomMessageHeader : MessageHeader
	{
//-------------------------------------------------------------------------------------------------------
		private string											MName;
		private string											MNamespace;
		private string											MValue;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCustomMessageHeader(string Name, string Namespace, string Value)
		{
			MName=Name;
			MNamespace=Namespace;
			MValue=Value;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string									Name
		{
			get
			{
				return(MName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override string									Namespace
		{
			get
			{
				return(MNamespace);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Metoda je zodpovedna za zapis XML HLAVICKY HEADER.
		protected override void OnWriteStartHeader(XmlDictionaryWriter Writer, MessageVersion MessageVersion)
		{
			Console.WriteLine("OnWriteStartHeader() CALLED !");

			base.OnWriteStartHeader(Writer,MessageVersion);
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda je zodpovedna za zapis TELA HEADER.
		protected override void OnWriteHeaderContents(XmlDictionaryWriter Writer, MessageVersion MessageVersion)
		{
			Console.WriteLine("OnWriteHeaderContents() CALLED !");

			Writer.WriteAttributeString("CUSTOM_VALUE",MValue);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------