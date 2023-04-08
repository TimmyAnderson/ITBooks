using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel.Channels;
using System.Xml;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace MessagesTest
{
//-------------------------------------------------------------------------------------------------------
	// CUSTOM implementacia BodyWriter.
	public class CBodyWriter : BodyWriter
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFileName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CBodyWriter(string FileName)
			: base(true)
		{
			MFileName=FileName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Metoda zodpovedna za zapis MESSAGE BODY.
		protected override void OnWriteBodyContents(XmlDictionaryWriter Writer)
		{
			using (FileStream FS=File.Open(MFileName,FileMode.Open))
			{
				XmlDictionaryReader		XDR=XmlDictionaryReader.CreateTextReader(FS,new XmlDictionaryReaderQuotas());

				XDR.ReadStartElement();

				while(XDR.NodeType!=XmlNodeType.EndElement)
				{
					Writer.WriteNode(XDR,true);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------