using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace AdvancedStreamingHost
{
//-------------------------------------------------------------------------------------------------------
	public static class CStreamHelper
	{
//-------------------------------------------------------------------------------------------------------
		private const int					PACKET_COUNT=10;
		private const int					PACKET_SIZE=10000;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static void SlowFillStream(CMyTestStream S)
		{
			try
			{
				Console.WriteLine("WriteStream() STARTED !");

				for (int i=0;i<PACKET_COUNT;i++)
				{
					for (int j=0;j<PACKET_SIZE;j++)
					{
						byte		Value=(byte) (j % 256);

						S.WriteByte(Value);
					}

					// Simulacia pomaleho zapisu.
					Thread.Sleep(3*1000);
				}

				Console.WriteLine("WriteStream() FINISHED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("WriteStream()EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void FastFillStream(CMyTestStream S)
		{
			try
			{
				Console.WriteLine("WriteStream() STARTED !");

				for (int i=0;i<PACKET_COUNT;i++)
				{
					for (int j=0;j<PACKET_SIZE;j++)
					{
						byte		Value=(byte) (j % 256);

						S.WriteByte(Value);
					}
				}

				Console.WriteLine("WriteStream() FINISHED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("WriteStream()EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void FastReadStream(CMyTestStream S)
		{
			try
			{
				Console.WriteLine("ReadStreamThread() STARTED !");

				for (int i=0,j=PACKET_COUNT;i<j;i++)
				{
					byte[]			Buffer=new byte[PACKET_SIZE];
					int				Num=S.Read(Buffer,0,PACKET_SIZE);

					Console.WriteLine(string.Format("Pos: {0}, Value[5]: {1} read, Number of BYTE READ: {2} !",i,(Buffer.Length<10) ? "NULL" : Buffer[5].ToString(),Num));
				}

				Console.WriteLine("ReadStreamThread() FINISHED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ReadStreamThread()EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void SlowReadStream(CMyTestStream S)
		{
			try
			{
				Console.WriteLine("ReadStreamThread() STARTED !");

				for (int i=0,j=PACKET_COUNT;i<j;i++)
				{
					byte[]			Buffer=new byte[PACKET_SIZE];
					int				Num=S.Read(Buffer,0,PACKET_SIZE);

					Console.WriteLine(string.Format("Pos: {0}, Value[5]: {1} read, Number of BYTE READ: {2} !",i,(Buffer.Length<10) ? "NULL" : Buffer[5].ToString(),Num));

					// Spomalim citanie.
					Thread.Sleep(3*1000);
				}

				Console.WriteLine("ReadStreamThread() FINISHED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ReadStreamThread()EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------