using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda zodpovedna za logovanie a typ logu aby sa dali log records filtrovat.
	Ma iba jedno rozsirenie a to doplnenie mena metody pri kazdom log record.
*/
//-------------------------------------------------------------------------------------------------------
	public class CLog
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFileName=@"..\..\..\..\Logs\Test.txt";
		private string											MDefaultSource="UNK";
		private FileStream										MFS=null;
		private StreamWriter									MSW=null;
		private Mutex											MMutex=new Mutex(false,"CLog");
		private bool											MConsole;
		private ELogRecordType									MLogRecordTypes;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLog()
		{
			MConsole=false;
		}
//-------------------------------------------------------------------------------------------------------
		public CLog(bool Console)
		{
			MConsole=Console;
		}
//-------------------------------------------------------------------------------------------------------
		public CLog(string Source)
		{
			MDefaultSource=Source;
			MConsole=false;
		}
//-------------------------------------------------------------------------------------------------------
		public CLog(bool Console, string Source)
		{
			MDefaultSource=Source;
			MConsole=Console;
		}
//-------------------------------------------------------------------------------------------------------
		public CLog(string Source, string FileName)
		{
			MDefaultSource=Source;
			MFileName=FileName;
			MConsole=false;
		}
//-------------------------------------------------------------------------------------------------------
		public CLog(bool Console, string Source, string FileName, ELogRecordType LogRecordTypes)
		{
			MDefaultSource=Source;
			MFileName=FileName;
			MConsole=Console;
			MLogRecordTypes=LogRecordTypes;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void OpenInternal()
		{
			CloseInternal();

			try
			{
				MFS=new FileStream(MFileName,FileMode.Append,FileAccess.Write);
				MSW=new StreamWriter(MFS);
			}
			catch(Exception E)
			{
				CloseInternal();
				throw(E);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private void CloseInternal()
		{
			if (MSW!=null)
			{
				MSW.Close();
				MSW=null;
			}

			if (MFS!=null)
			{
				MFS.Close();
				MFS=null;
			}
		}
//-------------------------------------------------------------------------------------------------------
		private void WriteInternal(string Source, string Message1, string Message2)
		{
			if (MFS==null || MSW==null)
				return;

			if (Message2==null)
			{
				string	S=string.Format("T: {0}, S: {1}, MN: {2}, M: '{3}' !",DateTime.Now.ToString(),Source,CDebugHelper.GetMethodName(4),Message1);

				MSW.WriteLine(S);

				if (MConsole==true)
					Console.WriteLine(S);
			}
			else
			{
				string	S=string.Format("T: {0}, S: {1}, MN: {2}, M1: '{3}', M2: '{4}'",DateTime.Now.ToString(),Source,CDebugHelper.GetMethodName(4),Message1,Message2);

				MSW.WriteLine(S);

				if (MConsole==true)
					Console.WriteLine(S);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private void WriteSeparatorInternal(int NumberOfSeparators)
		{
			if (MFS==null || MSW==null)
				return;

			for (int i=0;i<NumberOfSeparators;i++)
			{
				MSW.WriteLine();

				if (MConsole==true)
					Console.WriteLine();
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool CheckLogTypeRecord(ELogRecordType LogRecordType)
		{
			if ((MLogRecordTypes & LogRecordType)!=0)
				return(true);
			else
				return(false);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void WriteWithSource(string Source, string Message1, string Message2, ELogRecordType LogRecordType)
		{
			try
			{
				MMutex.WaitOne();

				if (CheckLogTypeRecord(LogRecordType)==false)
					return;

				try
				{
					OpenInternal();
					WriteInternal(Source, Message1, Message2);
				}
				finally
				{
					CloseInternal();
				}
			}
			finally
			{
				MMutex.ReleaseMutex();
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void WriteWithSource(string Source, string Message, ELogRecordType LogRecordType)
		{
			try
			{
				MMutex.WaitOne();

				if (CheckLogTypeRecord(LogRecordType)==false)
					return;

				WriteWithSource(Source, Message, null, LogRecordType);
			}
			finally
			{
				MMutex.ReleaseMutex();
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void Write(string Message1, string Message2, ELogRecordType LogRecordType)
		{
			try
			{
				MMutex.WaitOne();

				if (CheckLogTypeRecord(LogRecordType)==false)
					return;

				WriteWithSource(MDefaultSource, Message1, Message2, LogRecordType);
			}
			finally
			{
				MMutex.ReleaseMutex();
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void Write(string Message, ELogRecordType LogRecordType)
		{
			try
			{
				MMutex.WaitOne();

				if (CheckLogTypeRecord(LogRecordType)==false)
					return;

				WriteWithSource(MDefaultSource, Message, null, LogRecordType);
			}
			finally
			{
				MMutex.ReleaseMutex();
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void WriteSeparator(int NumberOfSeparators)
		{
			try
			{
				MMutex.WaitOne();

				try
				{
					OpenInternal();
					WriteSeparatorInternal(NumberOfSeparators);
				}
				finally
				{
					CloseInternal();
				}
			}
			finally
			{
				MMutex.ReleaseMutex();
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------