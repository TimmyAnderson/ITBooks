using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace HelloWCFLibrary
{
//-------------------------------------------------------------------------------------------------------
	public static class CInsideWCFHelper
	{
//-------------------------------------------------------------------------------------------------------
		public static void ClearMessageDirectory()
		{
			string			DirectoryName=GetMessageDirectory();

			if (Directory.Exists(DirectoryName)==true)
			{
				DirectoryInfo	DI=new DirectoryInfo(DirectoryName);
				FileInfo[]		FI=DI.GetFiles();

				for (int i=0;i<FI.Length;i++)
				{
					try
					{
						FI[i].Delete();
					}
					catch
					{
					}
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetMessageDirectory()
		{
			DirectoryInfo	WorkingDir=new DirectoryInfo(AppDomain.CurrentDomain.BaseDirectory);
			string			ParentDir=WorkingDir.Parent.Parent.Parent.FullName;
			string			DestinationDir=string.Format("{0}\\Messages",ParentDir);

			return(DestinationDir);
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetMessageFile(string Name, string Extension)
		{
			return(string.Format("{0}\\{1}.{2}",GetMessageDirectory(),Name,Extension));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetServiceMessageFile(string Name, string Extension)
		{
			if (Name!=null)
				return(string.Format("{0}\\Service_{1}.{2}",GetMessageDirectory(),Name,Extension));
			else
				return(string.Format("{0}\\Service.{1}",GetMessageDirectory(),Extension));
		}
//-------------------------------------------------------------------------------------------------------
		public static string GetClientMessageFile(string Name, string Extension)
		{
			if (Name!=null)
				return(string.Format("{0}\\Client_{1}.{2}",GetMessageDirectory(),Name,Extension));
			else
				return(string.Format("{0}\\Client.{1}",GetMessageDirectory(),Extension));
		}
//-------------------------------------------------------------------------------------------------------
		public static void WriteServiceMessageToFile(string MessageName, Message Msg)
		{
			string						FileName=CInsideWCFHelper.GetServiceMessageFile(MessageName,"xml");
			XmlDictionaryWriter			Writer=null;
			
			try
			{
				Writer=XmlDictionaryWriter.CreateTextWriter(new FileStream(FileName, FileMode.Create));

				Msg.WriteMessage(Writer);
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			finally
			{
				if (Writer!=null)
				{
					Writer.Close();
					Writer=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void WriteClientMessageToFile(string MessageName, Message Msg)
		{
			string						FileName=CInsideWCFHelper.GetClientMessageFile(MessageName,"xml");
			XmlDictionaryWriter			Writer=null;
			
			try
			{
				Writer=XmlDictionaryWriter.CreateTextWriter(new FileStream(FileName, FileMode.Create));

				Msg.WriteMessage(Writer);
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			finally
			{
				if (Writer!=null)
				{
					Writer.Close();
					Writer=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void WriteMessageToConsole(string MessageName, Message Msg)
		{
			XmlDictionaryWriter			Writer=null;
			MemoryStream				MS=null;
			StreamReader				SR=null;
			string						Line;

			try
			{
				MS=new MemoryStream();
				Writer=XmlDictionaryWriter.CreateTextWriter(MS);

				Msg.WriteMessage(Writer);

				// Je potrebny aby sa to prehodilo do MS.
				Writer.Flush();

				MS.Seek(0,SeekOrigin.Begin);

				SR=new StreamReader(MS);

				while((Line=SR.ReadLine())!=null)
					Console.WriteLine(Line);
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			finally
			{
				if (Writer!=null)
				{
					Writer.Close();
					Writer=null;
				}

				if (MS!=null)
				{
					MS.Close();
					MS=null;
				}

				if (SR!=null)
				{
					SR.Close();
					SR=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void WriteMessageAsStringToFile(string MessageName, Message Msg)
		{
			string						FileName=CInsideWCFHelper.GetMessageFile(MessageName,"xml");
			StreamWriter				Writer=null;
			
			try
			{
				Writer=new StreamWriter(FileName);
				Writer.Write(Msg.ToString());
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			finally
			{
				if (Writer!=null)
				{
					Writer.Close();
					Writer=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------