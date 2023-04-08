using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace Recursion
{
//------------------------------------------------------------------------------
	public class CParallelRecursion
	{
//------------------------------------------------------------------------------
		private readonly int				MCPUCount;
		private readonly int				MScaleUpTo;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CParallelRecursion(int CPUCount)
		{
			MCPUCount=CPUCount;
			MScaleUpTo=CPUCount*2;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Pomocna funkcia realizujuca PARALELNY BEH VIACERYCH ACTIONS.
		private AutoResetEvent[] CoBegin(params Action<object>[] Actions)
		{
			AutoResetEvent[]	Latches=new AutoResetEvent[Actions.Length];

			for (int i=0;i<Actions.Length;i++)
			{
				Latches[i]=new AutoResetEvent(false);

				ThreadPool.QueueUserWorkItem(delegate(object Obj)
				{
					int			Index=(int) Obj;

					try
					{
						Actions[Index](Index+1);
					}
					finally
					{
						Latches[Index].Set();
					}
				}, i);
			}

			return(Latches);
		}
//------------------------------------------------------------------------------
		// Pomocna funkcia realizujuca PARALELNY BEH VIACERYCH ACTIONS.
		private void DoAll(params Action<object>[] Actions)
		{
			Action<object>[]	ParallelActions=new Action<object>[Actions.Length-1];

			Array.Copy(Actions,ParallelActions,Actions.Length-1);

			AutoResetEvent[]	Latches=CoBegin(ParallelActions);

			try
			{
				// !!! Posledny task vykonam priamo v CALLER THREADE.
				Actions[Actions.Length-1](Actions.Length);
			}
			finally
			{
				WaitHandle.WaitAll(Latches);
			}
		}
//------------------------------------------------------------------------------
		private void ParallelMirror(CTreeNode Node, int Threshold, ref int Active)
		{
			if (Node==null)
				return;

			// !!! Ak som prekrocil maximalny pocet povolenych Threads - ZACNEM VYKONAVAT KOD SEKVENCNE.
			// !!!!! Avsak ak BOL UZ PREKROCENY maximlany pocet Threads a NIEKTORY Z NICH UZ SKONCIL - co je detekovane Active, ktory POKLESNE volanim Interlocked.Decrement(), tak JE AUTOMATICKY tento UVOLNENY THREAD VYUZITI NA PARLALENE SPRACOVANIE.
			if (Threshold==0 && Active>=MScaleUpTo)
			{
				Mirror(Node.Left, ref Active);
				Mirror(Node.Right, ref Active);
			}
			else
			{
				Interlocked.Increment(ref Active);

				int			NewThreshold=(Threshold==0) ? 0 : (Threshold-1);
				int			LocActive=Active;

				DoAll(	(P) => ParallelMirror(Node.Left, NewThreshold, ref LocActive),
						(P) => ParallelMirror(Node.Right, NewThreshold, ref LocActive));

				Active=LocActive;

				Interlocked.Decrement(ref Active);
			}

			CTreeNode		Tmp=Node.Left;

			Node.Left=Node.Right;
			Node.Right=Tmp;
		}
//------------------------------------------------------------------------------
		private void Mirror(CTreeNode Node, ref int Active)
		{
			if (Node==null)
				return;

			if (Active<MScaleUpTo)
			{
				ParallelMirror(Node, 0, ref Active);
			}
			else
			{
				CTreeNode		Tmp=Node.Left;

				Node.Left=Node.Right;
				Node.Right=Tmp;
			}
		}
//------------------------------------------------------------------------------
		private void PrintTree(CTreeNode Node, int Depth)
		{
			if (Node==null)
				return;

			Console.WriteLine(string.Format("{0}{1}","".PadRight(Depth,'\t'),Node.Value));

			PrintTree(Node.Left,Depth+1);
			PrintTree(Node.Right,Depth+1);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void ParallelMirror(CTreeNode Node)
		{
			int					Active=0;
    
			ParallelMirror(Node, (int)Math.Log(MCPUCount, 2), ref Active);
		}
//------------------------------------------------------------------------------
		public void PrintTree(CTreeNode Node)
		{
			PrintTree(Node,0);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------