using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
//------------------------------------------------------------------------------
namespace MemoryModels
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		[DllImport("kernel32.dll", SetLastError = true)]
		private unsafe static extern bool GetLogicalProcessorInformation(SYSTEM_LOGICAL_PROCESSOR_INFORMATION *Buffers, ref int ReturnLength);
//------------------------------------------------------------------------------
		[StructLayout(LayoutKind.Explicit)]
		struct SYSTEM_LOGICAL_PROCESSOR_INFORMATION
		{
			[FieldOffset(0)]
			internal UIntPtr						ProcessorMask;
			// Note! Works on 64-bit only [assume UIntPtr==64bits].
			[FieldOffset(8)]
			internal LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
			// !!!!! These fields are unioned together.
			[FieldOffset(16)]
			internal uint							Flags;
			[FieldOffset(16)]
			internal uint							NodeNumber;
			[FieldOffset(16)]
			internal CACHE_DESCRIPTOR				Cache;
			[FieldOffset(16)]
			internal ulong							Reserved1;
			[FieldOffset(24)]
			internal ulong							Reserved2;
		}
//------------------------------------------------------------------------------
		enum LOGICAL_PROCESSOR_RELATIONSHIP : int
		{
			RelationProcessorCore=0,
			RelationNumaNode=1,
			RelationCache=2,
			RelationProcessorPackage=3
		}
//------------------------------------------------------------------------------
		[StructLayout(LayoutKind.Explicit)]
		struct CACHE_DESCRIPTOR
		{
			[FieldOffset(0)]
			internal PROCESSOR_CACHE_LEVEL			Level;
			[FieldOffset(1)]
			internal PROCESSOR_CACHE_ASSOCIATIVITY	Associativity;
			[FieldOffset(2)]
			internal ushort							LineSize;
			[FieldOffset(4)]
			internal uint							Size;
			[FieldOffset(8)]
			internal PROCESSOR_CACHE_TYPE			Type;
		}
//------------------------------------------------------------------------------
		enum PROCESSOR_CACHE_LEVEL : byte
		{
			L0,
			L1,
			L2,
			L3
		}
//------------------------------------------------------------------------------
		enum PROCESSOR_CACHE_ASSOCIATIVITY : byte
		{
			FullyAssociative=0xff
		}
//------------------------------------------------------------------------------
		enum PROCESSOR_CACHE_TYPE : int
		{
			Unified=0,
			Instruction=1,
			Data=2,
			Trace=3
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public static unsafe void Main()
		{
			try
			{
				if (IntPtr.Size!=8)
				{
					Console.WriteLine("Only works on 64-bit.");
					return;
				}

				int					EntrySize=0;

				// Make a call to get the necessary size info. Success assumed.
				GetLogicalProcessorInformation(null, ref EntrySize);

				int					EntryCount=EntrySize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);

				SYSTEM_LOGICAL_PROCESSOR_INFORMATION*	PEntries=stackalloc SYSTEM_LOGICAL_PROCESSOR_INFORMATION[EntryCount];

				if (GetLogicalProcessorInformation(PEntries, ref EntrySize)==false)
				{
					Console.WriteLine("GLPI call failed: {0} !", Marshal.GetLastWin32Error());
					return;
				}

				string[]			RelationshipStrings=new string[]
				{
					"Processor Cores",
					"NUMA Nodes",
					"Caches",
					"Sockets"
				};

				for (int i=0;i<Enum.GetValues(typeof(LOGICAL_PROCESSOR_RELATIONSHIP)).Length;i++)
				{
					Console.WriteLine("{0}", RelationshipStrings[i]);

					for (int j=0;j<RelationshipStrings[i].Length; j++)
						Console.Write("=");

					Console.WriteLine();

					for (int j=0;j<EntryCount;j++)
					{
						SYSTEM_LOGICAL_PROCESSOR_INFORMATION	Entry=PEntries[j];

						if ((int)Entry.Relationship==i)
						{
							ulong	PMask=Entry.ProcessorMask.ToUInt64();
							ulong	TryMask=1;

							for (int k=0;k<Environment.ProcessorCount;k++)
							{
								if ((TryMask & PMask)!=0)
									Console.Write("*");
								else
									Console.Write("-");

								TryMask<<=1;
							}


							Console.Write("\t");


							switch (Entry.Relationship)
							{
								case LOGICAL_PROCESSOR_RELATIONSHIP.RelationProcessorCore:
								{
									if (Entry.Flags == 1)
										Console.Write("Hyperthreaded");
								}
								break;

								case LOGICAL_PROCESSOR_RELATIONSHIP.RelationNumaNode:
								{
									Console.Write("#{0}", Entry.NodeNumber);
								}
								break;

								case LOGICAL_PROCESSOR_RELATIONSHIP.RelationCache:
								{
									CACHE_DESCRIPTOR	Cache = Entry.Cache;

									Console.Write("{0}, {1}k, Assoc {2}, LineSize {3}, {4}", Cache.Level, Cache.Size / 1024, Cache.Associativity, Cache.LineSize, Cache.Type);
								}
								break;
							}

							Console.WriteLine();
						}
					}
				}

				Console.WriteLine();
			}
			finally
			{
				Console.WriteLine("Press any key to EXIT !");
				Console.ReadLine();
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------