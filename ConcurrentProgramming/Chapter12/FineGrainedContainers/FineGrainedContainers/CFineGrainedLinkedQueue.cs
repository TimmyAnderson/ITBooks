﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//------------------------------------------------------------------------------
namespace FineGrainedContainers
{
//------------------------------------------------------------------------------
	public class CFineGrainedLinkedQueue<T>
	{
//------------------------------------------------------------------------------
		class Node
		{
			internal T							MValue;
			internal Node						MNext;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private Node							MHead;
		private Node							MTail;
		private object							MEnqLock=new object();
		private object							MDeqLock=new object();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CFineGrainedLinkedQueue()
		{
			MHead=MTail=new Node();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void Enqueue(T Obj)
		{
			Node			N=new Node();

			N.MValue=Obj;

			lock (MEnqLock)
			{
				MTail.MNext=N;
				MTail=N;
			}
		}
//------------------------------------------------------------------------------
		public T Dequeue()
		{
			T				Val;

			lock (MDeqLock)
			{
				Node		Next=MHead.MNext;

				if (Next==null)
					throw(new Exception("Empty !!!"));

				Val=Next.MValue;
				MHead=Next;
			}

			return(Val);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------