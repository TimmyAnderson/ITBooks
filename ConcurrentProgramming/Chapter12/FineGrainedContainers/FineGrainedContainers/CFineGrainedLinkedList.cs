using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace FineGrainedContainers
{
//------------------------------------------------------------------------------
	public class CFineGrainedLinkedList<T>
	{
//------------------------------------------------------------------------------
		class Node
		{
			internal T								MValue;
			internal Node							MNext;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private Node								MHead;
		private Node								MTail;
//------------------------------------------------------------------------------
		public CFineGrainedLinkedList()
		{
			MHead=MTail=new Node();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private delegate void FindAction(Node Pred, Node Curr);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Realizuje PESIMISTICKY algoritmus prechod Linked List.
		private bool TryFindAndPerform(T Obj, FindAction Action)
		{
			Node				Pred=MHead;
			Node				Curr;

			// Lock na predchazajuci Item.
			Monitor.Enter(Pred);

			while ((Curr=Pred.MNext) != null)
			{
				// Lock na aktualny Item.
				Monitor.Enter(Curr);

				if (EqualityComparer<T>.Default.Equals(Curr.MValue, Obj)==true)
				{
					Action(Pred, Curr);
					Monitor.Exit(Pred);
					Monitor.Exit(Curr);
					return true;
				}

				Monitor.Exit(Pred);
				Pred=Curr;
			}

			Monitor.Exit(Pred);

			return(false);
		}
//------------------------------------------------------------------------------
		// Realizuje OPTIMISTICKY algoritmus prechod Linked List.
		private bool TryFindAndPerformOptimistic(T Obj, FindAction Action)
		{
			// Opakuje optimisticky algoritmus az kym sa mu nepodari prejst cely Linked List bez toho aby bol zmeneny inym threadom.
			while (true)
			{
				Node			Pred=MHead;
				Node			Curr;

				while ((Curr=Pred.MNext)!=null)
				{
					if (EqualityComparer<T>.Default.Equals(Curr.MValue, Obj)==true)
					{
						lock (Pred)
						{
							lock (Curr)
							{
								// Ak next pointer bol zmeneny Curr bol ZMAZANY.
								if (Pred.MNext!=Curr)
									break;

								// If random access updates are allowed, we must // revalidate that equals still holds.
								if (EqualityComparer<T>.Default.Equals(Curr.MValue, Obj)==false)
									break;

								Action(Pred, Curr);
								return(true);
							}
						}
					}

					Pred=Curr;
				}

				if (Curr==null)
					return(false);
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void AddHead(T Obj)
		{
			Node				N=new Node();

			N.MValue = Obj;

			while (true)
			{
				Node			H=MHead;

				lock (H)
				{
					if (MHead!=H)
						continue;

					N.MNext=H.MNext;
					H.MNext=N;
					break;
				}
			}
		}
//------------------------------------------------------------------------------
		public T RemoveHead()
		{
			T					Val;

			while (true)
			{
				Node			H=MHead;

				lock(H)
				{
					if (MHead!=H)
						continue;

					if (H.MNext == null)
						throw(new Exception("Empty !!!"));

					Node		Next=H.MNext;

					Val=Next.MValue;
					MHead=Next;
					break;
				}
			}

			return(Val);
		}
//------------------------------------------------------------------------------
		public void AddTail(T Obj)
		{
			Node				N=new Node();

			N.MValue=Obj;

			while (true)
			{
				Node			T=MTail;

				lock(T)
				{
					if (MTail!=T)
						continue;

					T.MNext=N;
					MTail=N;
					break;
				}
			}
		}
//------------------------------------------------------------------------------
		public bool TryInsertAfter(T Search, T ToAdd)
		{
			return TryFindAndPerform(Search, delegate(Node Pred, Node Curr)
			{
				Node			N=new Node();

				N.MValue=ToAdd;
				N.MNext=Curr.MNext;
				Curr.MNext=N;
			});
		}
//------------------------------------------------------------------------------
		public bool TryInsertBefore(T Search, T ToAdd)
		{
			return TryFindAndPerform(Search, delegate(Node Pred, Node Curr)
			{
				Node			N=new Node();

				N.MValue=ToAdd;
				N.MNext=Curr;
				Pred.MNext=N;
			});
		}
//------------------------------------------------------------------------------
		public bool TryRemove(T Obj)
		{
			return TryFindAndPerform(Obj, delegate(Node Pred, Node Curr)
			{
				Pred.MNext=Curr.MNext;

				if (MTail==Curr)
					MTail=Pred;
			});
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------