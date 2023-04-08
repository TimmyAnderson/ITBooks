using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace FineGrainedContainers
{
//------------------------------------------------------------------------------
	public class FineGrainedHashtable<K, V>
	{
//------------------------------------------------------------------------------
		class Node
		{
			internal K							MKey;
			internal V							MValue;
			internal volatile Node				MNext;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private const int						BUCKET_COUNT=1024;
//------------------------------------------------------------------------------
		private Node[]							MBuckets;
		private object[]						MLocks;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public FineGrainedHashtable()
			: this(Environment.ProcessorCount)
		{
		}
//------------------------------------------------------------------------------
		public FineGrainedHashtable(int ConcurrencyLevel)
		{
			MLocks=new object[Math.Min(ConcurrencyLevel, BUCKET_COUNT)];

			for (int i=0;i<MLocks.Length;i++)
				MLocks[i]=new object();

			MBuckets=new Node[BUCKET_COUNT];
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Vypocitava cislo Bucket a Lock pre dany kluc.
		private void GetBucketAndLockNo(K K, out int BucketNo, out int LockNo)
		{
			if (K==null)
				throw(new ArgumentNullException());

			BucketNo=(K.GetHashCode()&0x7fffffff)%MBuckets.Length;
			LockNo=BucketNo%MLocks.Length;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void Add(K K, V V)
		{
			int					BucketNo;
			int					LockNo;

			GetBucketAndLockNo(K, out BucketNo, out LockNo);

			Node				N=new Node();

			N.MKey=K;
			N.MValue=V;

			// Ziskam Lock asociovany s danym bucketom. (Pocet Locks je mensi, alebo rovny poctu Buckets.)
			lock (MLocks[LockNo])
			{
				N.MNext=MBuckets[BucketNo];
				MBuckets[BucketNo]=N;
			}
		}
//------------------------------------------------------------------------------
		// LOCK FREE algoritmus ziskania Itemu s dany Key.
		public bool TryGet(K K, out V V)
		{
			int					BucketNo;
			int					LockNoUnused;

			GetBucketAndLockNo(K, out BucketNo, out LockNoUnused);

			// Item ziskavame LOCK FREE sposobom.
			Node				N=MBuckets[BucketNo];

			// Kedze pouzivam LOCK FREE MUSIM POSTAVIT Memory Barrier kvoli moznost Memory Reordering napriklad na architekture IA64.
			Thread.MemoryBarrier();

			// V danom Bucket hladam Item s Key K.
			while (N!=null)
			{
				if (N.MKey.Equals(K)==true)
				{
					V = N.MValue;
					return(true);
				}

				N=N.MNext;
			}

			// Item sa nenasiel.
			V=default(V);

			return(false);
		}
//------------------------------------------------------------------------------
		// LOCK FREE algoritmus.
		public V								this[K K]
		{
			get
			{
				V				V;

				if (TryGet(K, out V)==false)
					throw(new Exception());

				return(V);
			}
		}
//------------------------------------------------------------------------------
		public bool Remove(K K, out V V)
		{
			int					BucketNo;
			int					LockNo;

			GetBucketAndLockNo(K, out BucketNo, out LockNo);

			// Rychla kontrola ci Bucket vobec existuje.
			if (MBuckets[BucketNo]==null)
			{
				V=default(V);
				return(false);
			}

			// Ziskam Lock asociovany s danym bucketom. (Pocet Locks je mensi, alebo rovny poctu Buckets.)
			lock (MLocks[LockNo])
			{
				Node			NPrev=null;
				Node			NCurr=MBuckets[BucketNo];

				while (NCurr!=null)
				{
					if (NCurr.MKey.Equals(K)==true)
					{
						if (NPrev==null)
							MBuckets[BucketNo]=NCurr.MNext;
						else
							NPrev.MNext=NCurr.MNext;

						V=NCurr.MValue;
						return(true);
					}

					NPrev = NCurr;
					NCurr = NCurr.MNext;
				}
			}

			V=default(V);
			return(false);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------