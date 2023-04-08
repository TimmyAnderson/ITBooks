using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace StreamingLibrary
{
//-------------------------------------------------------------------------------------------------------
	public static class CStreamHelper
	{
//-------------------------------------------------------------------------------------------------------
		private const int										PACKET_COUNT=10;
		private const int										PACKET_SIZE=10000;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Stream sa MUSI uzatvarat.
		private static void ReadStreamThread(object Param)
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static void FillStream(Stream S)
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
		public static void ReadStream(Stream S)
		{
			try
			{
				Console.WriteLine("ReadStreamThread() STARTED !");

				for (int i=0,j=PACKET_COUNT*PACKET_SIZE;i<j;i++)
				{
					int				Value=S.ReadByte();

					Console.WriteLine(string.Format("Pos: {0}, Value: {1} read!",i,Value));
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