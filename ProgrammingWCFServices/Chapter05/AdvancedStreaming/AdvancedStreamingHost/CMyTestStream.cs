using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace AdvancedStreamingHost
{
//-------------------------------------------------------------------------------------------------------
	[Serializable]
	public class CMyTestStream : Stream
	{
//-------------------------------------------------------------------------------------------------------
		private object					MLock=new object();
		private List<byte>				MBytes=new List<byte>();
		private int						MPosition=0;
		private	string					MName="NOT DEFINED";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyTestStream(string Name)
		{
			MName=Name;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool			CanRead
		{
			get
			{
				Console.WriteLine(string.Format("Name: {0}, CMyTestStream.CanRead GET !"));

				return(true);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override bool			CanSeek
		{
			get
			{ 
				Console.WriteLine(string.Format("Name: {0}, CMyTestStream.CanSeek GET !",MName));

				return(true);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override bool			CanWrite
		{
			get
			{ 
				Console.WriteLine(string.Format("Name: {0}, CMyTestStream.CanWrite GET !",MName));

				return(true);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override long			Length
		{
			get 
			{ 
				lock(MLock)
				{
					if ((MBytes.Count % 10000)==0)
						Console.WriteLine(string.Format("Name: {0}, CMyTestStream.Length GET !",MName));

					return(MBytes.Count);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override long			Position
		{
			get
			{
				lock(MLock)
				{
					if ((MBytes.Count % 10000)==0)
						Console.WriteLine(string.Format("Name: {0}, CMyTestStream.Position GET !",MName));

					return(MPosition);
				}
			}
			set
			{
				lock(MLock)
				{
					Console.WriteLine(string.Format("Name: {0}, CMyTestStream.Position SET !",MName));

					MPosition=(int) value;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override long Seek(long Offset, SeekOrigin Origin)
		{
			lock(MLock)
			{
				Console.WriteLine(string.Format("Name: {0}, CMyTestStream.Seek() !",MName));

				if (Origin==SeekOrigin.Begin)
					MPosition=(int) Offset;
				else if (Origin==SeekOrigin.End)
					MPosition=(int) (Length-Offset);
				else
					MPosition+=(int) Offset;
				
				return(MPosition);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override void SetLength(long Value)
		{
			lock(MLock)
			{
				Console.WriteLine(string.Format("Name: {0}, CMyTestStream.SetLength() !",MName));

				// Nechce sa mi to implementovat.
				throw(new NotImplementedException("THIS OPERATION IS NOT IMPLEMENTED BECAUSE I'M LAZY !!!"));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override void Flush()
		{
			lock(MLock)
			{
				Console.WriteLine(string.Format("Name: {0}, CMyTestStream.Flush() !"));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override int Read(byte[] Buffer, int Offset, int Count)
		{
			// Na simulaciu pomaleho citania.
			//Thread.Sleep(1*1000);

			lock(MLock)
			{
				Console.WriteLine(string.Format("Name: {0}, CMyTestStream.Read() - Pos: {1} !",MName,Position));

				int			Ret=Math.Min(Count,(int) (Length-Position));

				for (int i=0;i<Ret;i++)
					Buffer[Offset+i]=MBytes[MPosition++];

				return(Ret);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override void Write(byte[] Buffer, int Offset, int Count)
		{
			lock(MLock)
			{
				if ((Length % 10000)==0)
					Console.WriteLine(string.Format("Name: {0}, CMyTestStream.Write() - Pos: {1} !",MName,Length));

				for (int i=0;i<Count;i++)
				{
					MBytes.Add(Buffer[Offset+i]);

					// NEBUDEM ZVYSOVAT Position, aby som mal WRITE NEZAVISLY NA READ.
					//MPosition++;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
        protected override void Dispose(bool Disposing)
        {
			Console.WriteLine(string.Format("Name: {0}, CMyTestStream DISPOSED !!!",MName));
			base.Dispose(Disposing);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------