using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace StreamingLibrary
{
//-------------------------------------------------------------------------------------------------------
	[Serializable]
	public class CMyStream : Stream
	{
//-------------------------------------------------------------------------------------------------------
		private MemoryStream									MS=new MemoryStream();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool									CanRead
		{
			get
			{ 
				Console.WriteLine("CMyStream.CanRead GET !");

				return(MS.CanRead);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override bool									CanSeek
		{
			get
			{ 
				Console.WriteLine("CMyStream.CanSeek GET !");

				return(MS.CanSeek);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override bool									CanWrite
		{
			get
			{ 
				Console.WriteLine("CMyStream.CanWrite GET !");

				return(MS.CanWrite);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override long									Length
		{
			get 
			{ 
				Console.WriteLine("CMyStream.Length GET !");

				return(MS.Length);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override long									Position
		{
			get
			{
				Console.WriteLine("CMyStream.Position GET !");

				return(MS.Position);
			}
			set
			{
				Console.WriteLine("CMyStream.Position SET !");

				MS.Position=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override long Seek(long Offset, SeekOrigin Origin)
		{
			Console.WriteLine("CMyStream.Seek() !");

			return(MS.Seek(Offset,Origin));
		}
//-------------------------------------------------------------------------------------------------------
		public override void SetLength(long Value)
		{
			Console.WriteLine("CMyStream.SetLength() !");

			MS.SetLength(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public override void Flush()
		{
			MS.Flush();
		}
//-------------------------------------------------------------------------------------------------------
		public override int Read(byte[] Buffer, int Offset, int Count)
		{
			Console.WriteLine("CMyStream.Read() - Pos: {0} !",Position);

			// Na simulaciu.
			Thread.Sleep(10000);

			return(MS.Read(Buffer,Offset,Count));
		}
//-------------------------------------------------------------------------------------------------------
		public override void Write(byte[] Buffer, int Offset, int Count)
		{
			//Console.WriteLine("CMyStream.Write() - Pos: {0} !",Position);

			MS.Write(Buffer,Offset,Count);
		}
//-------------------------------------------------------------------------------------------------------
        protected override void Dispose(bool Disposing)
        {
            try
            {
				Console.WriteLine("CMyStream Disposed !!!");

                 MS.Dispose();
            }
            finally
            {
                 base.Dispose(Disposing);
            }
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------