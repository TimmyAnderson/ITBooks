using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ParallelSort
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		static void ParallelFor(int Lo, int Hi, Action<int> Body, int P)
		{
			const int		Chunk=1;

			for (int i=0;i<P;i++)
			{
				ThreadPool.QueueUserWorkItem(delegate(object PID)
				{
					int		Start=Lo+(int)PID*Chunk;

					//for (int j=Start;j<Hi;j+=Chunk*(P-1))
					for (int j=Start;j<Hi;j+=Chunk*(P-0))
					{
						for (int k=0;k<Chunk && (j+k)<Hi;k++)
						{
							Body((j+k));
						}
					}
				}, i);
			}

			// !!! Musim to tu pridat, lebo ParallelFor() NESMIE SKONCIT SKOR, ako skoncia VSETKY JEHO THREADS. INAK DOJDE k PROBLEMOM SO SYNCHRONIZACIOU DAT a ROZPADOM ALGORIMU.
			Console.WriteLine("Press any key to CONTINUE !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
		private static T[] ParallelSort<T>(T[] Input, int P) where T : IComparable<T>
		{
			T[][]				Chunks=new T[P][];

			// Step 1: Sort the p chunks of the input.
			int					Chunk=Input.Length/P;

			ParallelFor(0, P, delegate(int Idx)
			{
				// Compute the bounds.
				int				Start=Idx*Chunk;
				int				Size;

				if (Idx==P-1)
					Size=Input.Length-Start;
				else
					Size=Chunk;

				// Copy.
				Chunks[Idx]=new T[Size];
				Array.Copy(Input,Idx*Chunk,Chunks[Idx],0,Size);

				// And then actually sort.
				Array.Sort(Chunks[Idx]);
			},
			P);

			// 2. Merge. Spajam vzdy 2 vedla stojace CHUNKS do jedneho az pokym neostane iba jeden jediny CHUNK.
			int					Remaining=P;

			while (Remaining>1)
			{
				T[][]			RChunks=new T[Remaining][];

				for (int i=0;i<Remaining;i+=2)
				{
					if (i==(Remaining-1) && (Remaining&1)==1)
						RChunks[i]=Chunks[i];
					else
						RChunks[i]=new T[Chunks[i].Length+Chunks[i+1].Length];
				}

				T[][]			OutChunks=new T[(Remaining+1)/2][];

				ParallelFor(0, Remaining, delegate(int Idx)
				{
					// If an odd number, we just propagate the sorted chunk.
					if (Idx==(Remaining-1) && (Remaining&1)==1)
					{
						OutChunks[(Idx+1)/2]=RChunks[Idx];
						return;
					}

					T[]			Dest=RChunks[Idx&~1];
					T[]			Left=Chunks[Idx&~1];
					T[]			Right=Chunks[Idx|1];
					int			Mid=(Dest.Length+1)/2;

					if ((Idx&1)==0)
					{
						// Even participants merge from left to right.
						int		Lix = 0; // Left index.
						int		Rix = 0; // Right index.
						int		Mix = 0; // Merge index.

						for (int j=0;j<Mid;j++)
						{
							if (Lix<Left.Length && Left[Lix].CompareTo(Right[Rix])<=0)
								Dest[Mix++]=Left[Lix++];
							else
								Dest[Mix++]=Right[Rix++];
						}
					}
					else
					{
						// Odd participants merge from right to left.
						int		Lix=Left.Length-1; // Left index.
						int		Rix=Right.Length-1; // Right index.
						int		Mix=Dest.Length-1; // Merge index.

						for (int j=0;j<Mid;j++)
						{
							if (Lix>=0 && Left[Lix].CompareTo(Right[Rix])>0)
								Dest[Mix--]=Left[Lix--];
							else
								Dest[Mix--]=Right[Rix--];
						}
					}

					if ((Idx&1)==0)
					{
						// One of the partners propagates the result.
						OutChunks[Idx/2]=Dest;
					}
				}, Remaining);

				// Lastly, we know all threads are finished; propagate output.
				for (int i=0;i<OutChunks.Length;i++)
					Chunks[i]=OutChunks[i];

				Remaining=(Remaining+1)/2;
			}

			return(Chunks[0]);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void TestSort()
		{
			Random			RND=new Random();
			int[]			Input=new int[20];

			for (int i=0;i<Input.Length;i++)
			{
				Input[i]=RND.Next(1,100);
				Console.WriteLine(string.Format("Value: [{0}] !",Input[i]));
			}

			int[]			Output=ParallelSort<int>(Input,4);

			Console.WriteLine("Press any key to CONTINUE !");
			Console.ReadLine();

			for (int i=0;i<Output.Length;i++)
				Console.WriteLine(string.Format("SORTED Value: [{0}] !",Output[i]));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			TestSort();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------