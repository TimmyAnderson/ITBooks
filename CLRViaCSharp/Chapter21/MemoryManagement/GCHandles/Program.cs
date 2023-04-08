using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace GCHandles
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		public delegate void DMyCallbackDelegate([In,Out] [MarshalAs(UnmanagedType.LPWStr)] string Param);
//-------------------------------------------------------------------------------------------------------
		public delegate void DMyPTRCallbackDelegate([In,Out] IntPtr CallbackID);
//-------------------------------------------------------------------------------------------------------
		public delegate void DMyPTRCallbackDelegateWithWrite([In,Out] IntPtr CallbackID, [In,Out] [MarshalAs(UnmanagedType.LPWStr)]  string Value);
//-------------------------------------------------------------------------------------------------------
		[DllImport("MyUnmanagedLibrary.dll")]
		public static extern int PrintStringAndGetLength([MarshalAs(UnmanagedType.LPWStr)] string Text);
		[DllImport("MyUnmanagedLibrary.dll")]
		public static extern int FillString([In,Out] [MarshalAs(UnmanagedType.LPArray)] byte[] StringToBuild, int Size);
		[DllImport("MyUnmanagedLibrary.dll")]
		public static extern void DoCallback(DMyCallbackDelegate MyCallback, [In,Out] [MarshalAs(UnmanagedType.LPWStr)] string Text);
		[DllImport("MyUnmanagedLibrary.dll")]
		public static extern void DoCallbackAsPTR(DMyPTRCallbackDelegate MyCallback, [In,Out] IntPtr CallbackID);
		[DllImport("MyUnmanagedLibrary.dll")]
		public static extern void DoCallbackAsPTRWithWrite(DMyPTRCallbackDelegateWithWrite MyCallback, [In,Out] IntPtr CallbackID, [In,Out] IntPtr Text, [In] int TextSize);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!!!! DELEGATE MUSI BYT ROOTED pocas CELEHO VYKONAVANIA - AZ KYM SA NEZAVOLA CALLBACK.
		// !!! Idealne je preto pouzit FIELD a NIE LOKALNU PREMENNU, ak by CALLBACK MOHOL BYT ZAVOLANY i PO SKONCENI Test11() a Test12().
		private static DMyPTRCallbackDelegate					MPTRCallbackDelegate=new DMyPTRCallbackDelegate(MyPTRCallbackHandler);
		// !!!!! DELEGATE MUSI BYT ROOTED pocas CELEHO VYKONAVANIA - AZ KYM SA NEZAVOLA CALLBACK.
		// !!! Idealne je preto pouzit FIELD a NIE LOKALNU PREMENNU, ak by CALLBACK MOHOL BYT ZAVOLANY i PO SKONCENI Test13().
		private static DMyPTRCallbackDelegateWithWrite			MMyPTRCallbackHandlerWithWrite=new DMyPTRCallbackDelegateWithWrite(MyPTRCallbackHandlerWithWrite);
		// !!!!! DELEGATE MUSI BYT ROOTED pocas CELEHO VYKONAVANIA - AZ KYM SA NEZAVOLA CALLBACK.
		// !!! Idealne je preto pouzit FIELD a NIE LOKALNU PREMENNU, ak by CALLBACK MOHOL BYT ZAVOLANY i PO SKONCENI Test14().
		private static DMyCallbackDelegate						MCallbackDelegate=new DMyCallbackDelegate(MyCallbackHandler);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void MyCallbackHandler(string Param)
		{
			Console.WriteLine(string.Format("MANAGED CALLBACK - Param: [{0}] !",Param));
		}
//-------------------------------------------------------------------------------------------------------
		private static void MyPTRCallbackHandler(IntPtr Param)
		{
			// !!!!! Konvertujem IntPtr na GCHandle.
			GCHandle											Handle=(GCHandle) Param;

			Console.WriteLine(string.Format("MANAGED CALLBACK - Param: [{0}] !",Handle.Target));
		}
//-------------------------------------------------------------------------------------------------------
		private static void MyPTRCallbackHandlerWithWrite(IntPtr Param, string Value)
		{
			// !!!!! Konvertujem IntPtr na GCHandle.
			GCHandle											Handle=(GCHandle) Param;

			Console.WriteLine(string.Format("MANAGED CALLBACK - Param: [{0}], Data: [{1}] !",Handle.Target,Value));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static string PrintGCHandleState(string Text, GCHandle Handle)
		{
			if (Handle.IsAllocated==true)
			{
				if (Handle.Target!=null)
				{
					return(string.Format("[{0}] IsAllocated: [{1}], Target [{2}] !",Text,Handle.IsAllocated,Handle.Target));
				}
				else
				{
					return(string.Format("[{0}] IsAllocated: [{1}], Target [{2}] !",Text,Handle.IsAllocated,"NULL"));
				}
			}
			else
			{
				return(string.Format("[{0}] IsAllocated: [{1}], Target [{2}] !",Text,Handle.IsAllocated,"NOT EXISTS"));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static string PrintGCHandleState(string Text, WeakReference<CName> WR)
		{
			CName												Name;
			
			if (WR.TryGetTarget(out Name)==true)
			{
				return(string.Format("[{0}] IsAllocated: [{1}], Target [{2}] !",Text,"TRUE",Name));
			}
			else
			{
				return(string.Format("[{0}] IsAllocated: [{1}], Target [{2}] !",Text,"FALSE","NOT EXISTS"));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static GCHandle GetHandle(object Object, GCHandleType HandleType)
		{
			GCHandle											Handle=GCHandle.Alloc(Object,HandleType);

			return(Handle);
		}
//-------------------------------------------------------------------------------------------------------
		private unsafe static IntPtr GetAddress(byte[] Bytes)
		{
			// !!! Ziskam adresu pola Bytes.
			fixed(byte* PBytes=Bytes)
			{
				IntPtr											MemoryAddress=(IntPtr) PBytes;

				return(MemoryAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CName												Name=new CName("Timmy","Anderson",12);
			GCHandle											Handle=GCHandle.Alloc(Name,GCHandleType.Weak);

			// !!! IsAllocated vracia informaciu IBA O TOM ci GCHandle je platny, ale NIE O TOM, ci OBJECT, ktory REPREZENTUJE ESTE EXISTUJE v HEAP, ALEBO UZ NIE.
			Console.WriteLine(PrintGCHandleState("OBJECT CREATED",Handle));

			GC.Collect();

			// !!! OBJECT este EXISTUJE, lebo ma ROOT.
			Console.WriteLine(PrintGCHandleState("AFTER GC - OBJECT STILL has ROOT",Handle));

			Name=null;

			Console.WriteLine(PrintGCHandleState("OBJECT HAS NO ROOT",Handle));

			GC.Collect();

			// !!!!! OBJECT uz bol ODSTRANENY, alebo HANDLE este EXISTUJE.
			Console.WriteLine(PrintGCHandleState("AFTER GC - OBJECT HAS NO ROOT",Handle));

			Handle.Free();

			// !!!!! OBJECT uz bol ODSTRANENY, alebo HANDLE uz je NEPLATNY.
			Console.WriteLine(PrintGCHandleState("AFTER HANDLE FREE",Handle));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			GCHandle											Handle=GetHandle(new CName("Timmy","Anderson",12),GCHandleType.Weak);

			Console.WriteLine(PrintGCHandleState("AFTER CREATED - OBJECT has NO ROOT",Handle));

			GC.Collect();

			// !!!!! OBJECT uz bol ODSTRANENY, alebo HANDLE este EXISTUJE.
			Console.WriteLine(PrintGCHandleState("AFTER GC - OBJECT has NO ROOT",Handle));

			Handle.Free();

			Console.WriteLine(PrintGCHandleState("AFTER HANDLE FREE",Handle));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			GCHandle											Handle=GetHandle(new CName("Timmy","Anderson",12),GCHandleType.Weak);

			Console.WriteLine(PrintGCHandleState("AFTER CREATED - OBJECT has NO ROOT",Handle));

			GC.Collect();

			Console.WriteLine(PrintGCHandleState("AFTER GC - OBJECT has NO ROOT",Handle));

			CName												Name=(CName) Handle.Target;

			if (Name!=null)
			{
				Console.WriteLine(string.Format("Name: [{0}] !",Name));
			}
			else
			{
				Console.WriteLine(string.Format("Name IS NULL !!!"));
			}

			Handle.Free();

			Console.WriteLine(PrintGCHandleState("AFTER HANDLE FREE",Handle));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			// Pouzijem GCHandleType.Normal co ZABRANI GC aby zlikvidoval OBJECT.
			GCHandle											Handle=GetHandle(new CName("Timmy","Anderson",12),GCHandleType.Normal);

			// !!!!! OBJECT NEBUDE ZLIKVIDOVANY, pretoze sa pouzil FLAG [Normal].
			GC.Collect();

			Console.WriteLine(PrintGCHandleState("AFTER CREATED and GC - OBJECT has NO ROOT",Handle));

			CName												Name=(CName) Handle.Target;

			if (Name!=null)
			{
				Console.WriteLine(string.Format("Name: [{0}] !",Name));
			}
			else
			{
				Console.WriteLine(string.Format("Name IS NULL !!!"));
			}

			Handle.Free();

			Console.WriteLine(PrintGCHandleState("AFTER HANDLE FREE",Handle));
		}
//-------------------------------------------------------------------------------------------------------
		private unsafe static void Test5()
		{
			// Alokujem OBJECTS, aby som naplnil HEAP.
			for (int Index=0;Index<100000;Index++)
			{
				new object();
			}

			byte[]												Bytes=new byte[1000];

			// !!! Ziskam adresu pola Bytes.
			IntPtr												OriginalMemoryAddress=GetAddress(Bytes);

			// Vykonam GC, ktory vdaka velkemu poctu odstranovanych OBJECTS spravi KOMPAKCIU PAMATE.
			GC.Collect();

			// !!! Ziskam adresu pola Bytes po vykonani GC.
			IntPtr												NewMemoryAddress=GetAddress(Bytes);

			Console.WriteLine(string.Format("ADDRESS BEFORE GC:\t[{0}] !",OriginalMemoryAddress));
			Console.WriteLine(string.Format("ADDRESS AFTER GC:\t[{0}] !",NewMemoryAddress));
		}
//-------------------------------------------------------------------------------------------------------
		private unsafe static void Test6()
		{
			// Alokujem OBJECTS, aby som naplnil HEAP.
			for (int Index=0;Index<100000;Index++)
			{
				new object();
			}

			byte[]												Bytes=new byte[1000];

			// Teraz NESPRAVIM PINNING, lebo pouzivam GCHandleType.Normal.
			GCHandle											Handle=GetHandle(Bytes,GCHandleType.Normal);

			// !!! Ziskam adresu pola Bytes.
			IntPtr												OriginalMemoryAddress=GetAddress(Bytes);

			// Vykonam GC, ktory vdaka velkemu poctu odstranovanych OBJECTS spravi KOMPAKCIU PAMATE.
			GC.Collect();

			// !!! Ziskam adresu pola Bytes po vykonani GC.
			IntPtr												NewMemoryAddress=GetAddress(Bytes);

			// !!!!! ADDRESSES su ROZDIELNE, pretoze sa NEPOUZIL PINNING.
			Console.WriteLine(string.Format("ADDRESS BEFORE GC:\t[{0}] !",OriginalMemoryAddress));
			Console.WriteLine(string.Format("ADDRESS AFTER GC:\t[{0}] !",NewMemoryAddress));

			Handle.Free();
		}
//-------------------------------------------------------------------------------------------------------
		private unsafe static void Test7()
		{
			// Alokujem OBJECTS, aby som naplnil HEAP.
			for (int Index=0;Index<100000;Index++)
			{
				new object();
			}

			byte[]												Bytes=new byte[1000];

			// !!! Spravim PINNING.
			GCHandle											Handle=GetHandle(Bytes,GCHandleType.Pinned);

			// !!! Ziskam adresu pola Bytes.
			IntPtr												OriginalMemoryAddress=GetAddress(Bytes);

			// Vykonam GC, ktory vdaka velkemu poctu odstranovanych OBJECTS spravi KOMPAKCIU PAMATE.
			GC.Collect();

			// !!! Ziskam adresu pola Bytes po vykonani GC.
			IntPtr												NewMemoryAddress=GetAddress(Bytes);

			// !!!!! ADDRESSES su ROVNAKE, pretoze sa POUZIL PINNING, ktory ZABRANUJE, aby bol OBJECT presunuty na INU ADDRESS.
			Console.WriteLine(string.Format("ADDRESS BEFORE GC:\t[{0}] !",OriginalMemoryAddress));
			Console.WriteLine(string.Format("ADDRESS AFTER GC:\t[{0}] !",NewMemoryAddress));

			Handle.Free();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			// !!!!! CNameWithFinalize MA FINALIZER METHOD.
			// !!! Pouzije sa FLAG [Weak], ktory NEKONTROLUJE ci FINALIZER METHOD bola volana.
			GCHandle											Handle=GetHandle(new CNameWithFinalize("Timmy","Anderson",12),GCHandleType.Weak);

			Console.WriteLine(PrintGCHandleState("OBJECT CREATED - NO ROOT",Handle));

			GC.Collect();

			// !!!!! Kedze OBJECT NEMA ROOT a bol GC, TARGET je NULL a to BEZ OHLADU na to ci uz bola FINALIZER METHOD volana.
			Console.WriteLine(PrintGCHandleState("GC CALLED - NO ROOT",Handle));

			// !!!!! Kedze OBJECT NEMA ROOT a bol GC, TARGET je NULL ak bol OBJECT ODSTRANENY z MEMORY a to BEZ OHLADU na to ci uz bola FINALIZER METHOD volana.
			CNameWithFinalize									Name=(CNameWithFinalize) Handle.Target;

			if (Name!=null)
			{
				Console.WriteLine(string.Format("Name: [{0}] !",Name));
			}
			else
			{
				Console.WriteLine(string.Format("Name IS NULL !!!"));
			}

			Handle.Free();

			Console.WriteLine(PrintGCHandleState("AFTER HANDLE FREE",Handle));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			// !!!!! CNameWithFinalize MA FINALIZER METHOD.
			// !!! Pouzije sa FLAG [Weak], ktory nastavuje TARGET na NULL BEZ OHLADU NA TO CI FINALIZER METHOD bola zavolana.
			GCHandle											Handle=GetHandle(new CNameWithFinalize("Timmy","Anderson",12),GCHandleType.Weak);

			Console.WriteLine(PrintGCHandleState("OBJECT CREATED - NO ROOT",Handle));

			GC.Collect();
			GC.WaitForPendingFinalizers();

			// !!!!! Kedze OBJECT NEMA ROOT a bol GC, TARGET je NULL a to BEZ OHLADU na to ci uz bola FINALIZER METHOD volana.
			Console.WriteLine(PrintGCHandleState("GC CALLED and FINALIZER EXECUTED - NO ROOT",Handle));

			// !!!!! Kedze OBJECT NEMA ROOT a bol GC, TARGET je NULL ak bol OBJECT ODSTRANENY z MEMORY a to BEZ OHLADU na to ci uz bola FINALIZER METHOD volana.
			CNameWithFinalize									Name=(CNameWithFinalize) Handle.Target;

			if (Name!=null)
			{
				Console.WriteLine(string.Format("Name: [{0}] !",Name));
			}
			else
			{
				Console.WriteLine(string.Format("Name IS NULL !!!"));
			}

			Handle.Free();

			Console.WriteLine(PrintGCHandleState("AFTER HANDLE FREE",Handle));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			// !!!!! CNameWithFinalize MA FINALIZER METHOD.
			// !!! Pouzije sa FLAG [WeakTrackResurrection], ktory nastavuje TARGET na NULL AZ ked bola FINALIZER METHOD zavolana.
			GCHandle											Handle=GetHandle(new CNameWithFinalize("Timmy","Anderson",12),GCHandleType.WeakTrackResurrection);

			Console.WriteLine(PrintGCHandleState("OBJECT CREATED - NO ROOT",Handle));

			GC.Collect();

			Console.WriteLine(PrintGCHandleState("AFTER 1. GC - NO ROOT",Handle));

			// Pocka sa na vykonanie FINALIZER METHODS.
			GC.WaitForPendingFinalizers();

			Console.WriteLine(PrintGCHandleState("AFTER 1. GC and FINALIZATION - NO ROOT",Handle));

			// !!!!! OBJECT este STALE ZIJE, lebo PRVA GC ho presunula iba do F-REACHABLE a nasledne sa zavolal Finalize(). OBJECT teraz NEMA ROOT, ale STALE je v HEAP.
			CNameWithFinalize									Name1=(CNameWithFinalize) Handle.Target;

			if (Name1!=null)
			{
				Console.WriteLine(string.Format("!!! AFTER 1. GC - Name: [{0}] !",Name1));
			}
			else
			{
				Console.WriteLine(string.Format("!!! AFTER 1. GC - Name IS NULL !!!"));
			}

			Name1=null;

			// !!! ZNOVA SPUSTIM GC.
			GC.Collect();

			Console.WriteLine(PrintGCHandleState("AFTER 2. GC and FINALIZATION - NO ROOT",Handle));

			// OBJECT uz NEZIJE, pretoze GC ho ZLIKVIDOVAL.
			CNameWithFinalize									Name2=(CNameWithFinalize) Handle.Target;

			if (Name2!=null)
			{
				Console.WriteLine(string.Format("!!! AFTER 2. GC - Name: [{0}] !",Name1));
			}
			else
			{
				Console.WriteLine(string.Format("!!! AFTER 2. GC - Name IS NULL !!!"));
			}

			Name2=null;

			Handle.Free();

			Console.WriteLine(PrintGCHandleState("AFTER HANDLE FREE",Handle));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			// Alokujem OBJECTS, aby som naplnil HEAP.
			for (int Index=0;Index<100000;Index++)
			{
				new object();
			}

			string												CallbackID="SUPER ID";

			// Alokujem OBJECTS, aby som naplnil HEAP.
			for (int Index=0;Index<100000;Index++)
			{
				new object();
			}

			// !!!!! NESPRAVIM PINNING, lebo NATIVE CODE k predanemu parameter NEPRISTUPUJE, iba ho PRENASA do CALLBACK.
			GCHandle											CallbackIDHandle=GCHandle.Alloc(CallbackID,GCHandleType.Normal);

			// !!!!! NEMUSIM spravit IMPLICITNY PINNING, pretoze POKIAL DELEGATE OBJECT je ROOTED OBJECT, tak CLR DRZI STUB CODE, ktory vytovri pri MARSHALINGU a ktory je v PINNED MEMORY.
			// !!!!! Hodi EXCEPTION, lebo DELEGATES NIE JE MOZNE TAKTO zmenit na PINNED.
			//GCHandle											CallbackHandle=GCHandle.Alloc(MPTRCallbackDelegate,GCHandleType.Pinned);

			Console.WriteLine("PARAMETER will be COLLECTED - try 1 !");

			// !!!!! Z Param spravim ROOT-LESS OBJECT a GC HO ODSTRANI.
			CallbackID=null;

			// Spravim GC.
			GC.Collect();
			GC.Collect();
			GC.Collect();

			// !!! Konvertujem GCHandle na IntPtr.
			// !!!!! CALLBACK METHOD sa vyvola az po nejakom case zo SEKUNDARNEHO THREADU.
			DoCallbackAsPTR(MPTRCallbackDelegate,(IntPtr) CallbackIDHandle);

			Console.WriteLine("PARAMETER will be COLLECTED - try 2 !");

			// !!!!! Z Param spravim ROOT-LESS OBJECT a GC HO ODSTRANI.
			CallbackID=null;

			// Spravim GC.
			GC.Collect();
			GC.Collect();
			GC.Collect();

			Console.WriteLine("\nPress any key to STOP WAITING !");
			Console.ReadLine();

			// !!! METHOD GCHandle.Free() uvolni RECORDS z GARBAGE COLLECTOR HANDLE TABLE vdaka comu moze byt prisluchajuci OBJECT ODSTRANENY z MEMORY pomocou GARBAGE COLLECTOR.
			// !!!!! Ak sa METHOD GCHandle.Free() zavola SKOR ako sa vrati CALLBACK METHOD, tak PARAMETER v CALLBACK METHOD bude PRAZDNY.
			CallbackIDHandle.Free();

			//CallbackHandle.Free();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			// Alokujem OBJECTS, aby som naplnil HEAP.
			for (int Index=0;Index<100000;Index++)
			{
				new object();
			}

			string												CallbackID="SUPER ID";

			// Alokujem OBJECTS, aby som naplnil HEAP.
			for (int Index=0;Index<100000;Index++)
			{
				new object();
			}

			// !!!!! SPRAVIM PINNING, aj ked NATIVE CODE k predanemu parameter NEPRISTUPUJE, iba ho PRENASA do CALLBACK. PINNING teda NIE JE NEVYHNUTNY.
			GCHandle											CallbackIDHandle=GCHandle.Alloc(CallbackID,GCHandleType.Pinned);

			// !!!!! NEMUSIM spravit IMPLICITNY PINNING, pretoze POKIAL DELEGATE OBJECT je ROOTED OBJECT, tak CLR DRZI STUB CODE, ktory vytovri pri MARSHALINGU a ktory je v PINNED MEMORY.
			// !!!!! Hodi EXCEPTION, lebo DELEGATES NIE JE MOZNE TAKTO zmenit na PINNED.
			//GCHandle											CallbackHandle=GCHandle.Alloc(MPTRCallbackDelegate,GCHandleType.Pinned);

			Console.WriteLine("PARAMETER will be COLLECTED - try 1 !");

			// !!!!! Z Param spravim ROOT-LESS OBJECT a GC HO ODSTRANI.
			CallbackID=null;

			// Spravim GC.
			GC.Collect();
			GC.Collect();
			GC.Collect();

			// !!! Konvertujem GCHandle na IntPtr.
			// !!!!! CALLBACK METHOD sa vyvola az po nejakom case zo SEKUNDARNEHO THREADU.
			DoCallbackAsPTR(MPTRCallbackDelegate,(IntPtr) CallbackIDHandle);

			Console.WriteLine("PARAMETER will be COLLECTED - try 2 !");

			// !!!!! Z Param spravim ROOT-LESS OBJECT a GC HO ODSTRANI.
			CallbackID=null;

			// Spravim GC.
			GC.Collect();
			GC.Collect();
			GC.Collect();

			Console.WriteLine("\nPress any key to STOP WAITING !");
			Console.ReadLine();

			// !!! METHOD GCHandle.Free() uvolni RECORDS z GARBAGE COLLECTOR HANDLE TABLE vdaka comu moze byt prisluchajuci OBJECT ODSTRANENY z MEMORY pomocou GARBAGE COLLECTOR.
			// !!!!! Ak sa METHOD GCHandle.Free() zavola SKOR ako sa vrati CALLBACK METHOD, tak PARAMETER v CALLBACK METHOD bude PRAZDNY.
			CallbackIDHandle.Free();

			//CallbackHandle.Free();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			// Alokujem OBJECTS, aby som naplnil HEAP.
			for (int Index=0;Index<100000;Index++)
			{
				new object();
			}

			string												CallbackID="SUPER ID";
			string												ArrayText="EMPTY !!!";
			char[]												Array=new char[100];

			ArrayText.CopyTo(0,Array,0,ArrayText.Length);

			Console.WriteLine(string.Format("START - ARRAY [{0}] !",new string(Array)));

			// Alokujem OBJECTS, aby som naplnil HEAP.
			for (int Index=0;Index<100000;Index++)
			{
				new object();
			}

			// !!!!! Kedze CallbackID sa pouziva iba ako ID a NATIVE CODE k nemu pristupuje ako OPAQUE HANDLE, staci pouzit hodnotu GCHandleType.Normal.
			GCHandle											CallbackIDHandle=GCHandle.Alloc(CallbackID,GCHandleType.Normal);

			// !!!!! Kedze Array sa pouziva v NATIVE CODE na ZAPIS DATA je NUTNE pouzit hodnotu GCHandleType.Pinned.
			GCHandle											ArrayHandle=GCHandle.Alloc(Array,GCHandleType.Pinned);

			Console.WriteLine("PARAMETER will be COLLECTED - try 1 !");

			// !!!!! Z Param spravim ROOT-LESS OBJECT a GC HO ODSTRANI.
			CallbackID=null;

			// Spravim GC.
			GC.Collect();
			GC.Collect();
			GC.Collect();

			// !!! Konvertujem GCHandle na IntPtr.
			// !!!!! CALLBACK METHOD sa vyvola az po nejakom case zo SEKUNDARNEHO THREADU.
			DoCallbackAsPTRWithWrite(MMyPTRCallbackHandlerWithWrite,(IntPtr) CallbackIDHandle,ArrayHandle.AddrOfPinnedObject(),Array.Length);

			Console.WriteLine("PARAMETER will be COLLECTED - try 2 !");

			// !!!!! Z Param spravim ROOT-LESS OBJECT a GC HO ODSTRANI.
			CallbackID=null;

			// Spravim GC.
			GC.Collect();
			GC.Collect();
			GC.Collect();

			Console.WriteLine("\nPress any key to STOP WAITING !");
			Console.ReadLine();

			// !!! METHOD GCHandle.Free() uvolni RECORDS z GARBAGE COLLECTOR HANDLE TABLE vdaka comu moze byt prisluchajuci OBJECT ODSTRANENY z MEMORY pomocou GARBAGE COLLECTOR.
			// !!!!! Ak sa METHOD GCHandle.Free() zavola SKOR ako sa vrati CALLBACK METHOD, tak PARAMETER v CALLBACK METHOD bude PRAZDNY.
			CallbackIDHandle.Free();

			// !!! METHOD GCHandle.Free() uvolni RECORDS z GARBAGE COLLECTOR HANDLE TABLE vdaka comu moze byt prisluchajuci OBJECT ODSTRANENY z MEMORY pomocou GARBAGE COLLECTOR.
			ArrayHandle.Free();

			// Spravim GC.
			GC.Collect();
			GC.Collect();
			GC.Collect();

			Console.WriteLine(string.Format("END - ARRAY [{0}] !",new string(Array)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			// Alokujem OBJECTS, aby som naplnil HEAP.
			for (int Index=0;Index<100000;Index++)
			{
				new object();
			}

			string												Param="Timmy Anderson";

			// Alokujem OBJECTS, aby som naplnil HEAP.
			for (int Index=0;Index<100000;Index++)
			{
				new object();
			}

			// !!!!! MUSIM spravit IMPLICITNY PINNING - ak NIE, tak sa Param ODSTRANI z PAMATE a v CALLBACK sa NEVYPISE NIC.
			GCHandle											ParamHandle=GCHandle.Alloc(Param,GCHandleType.Pinned);

			// !!!!! NEMUSIM spravit IMPLICITNY PINNING, pretoze POKIAL DELEGATE OBJECT je ROOTED OBJECT, tak CLR DRZI STUB CODE, ktory vytovri pri MARSHALINGU a ktory je v PINNED MEMORY.
			// !!!!! Hodi EXCEPTION, lebo DELEGATES NIE JE MOZNE TAKTO zmenit na PINNED.
			//GCHandle											CallbackHandle=GCHandle.Alloc(MCallbackDelegate,GCHandleType.Pinned);

			/*
			// !!!!! Param tu NEMOZE BYT VYMAZANY, pretoze do UNMANAGED METHOD sa NEPRENASA jeho OPAQUE HANDLER (IntPtr), ale samotna hodnota Param.
			Param=null;

			// Spravim GC.
			GC.Collect();
			GC.Collect();
			GC.Collect();
			*/

			// !!!!! Do UNMANAGED METHOD sa PRENASA samotna hodnota Param a NIE IntPtr hodnota ako v prechadzajucom priklade.
			DoCallback(MCallbackDelegate,Param);

			// !!!!! Z Param spravim ROOT-LESS OBJECT a GC HO ODSTRANI.
			Param=null;

			// Spravim GC.
			GC.Collect();
			GC.Collect();
			GC.Collect();

			Console.WriteLine("\nPress any key to STOP WAITING !");
			Console.ReadLine();

			ParamHandle.Free();

			//CallbackHandle.Free();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			string												Param="Timmy Anderson";
			int													ReturnValue;

			// Volam UNMANAGED CODE - IMPLICITNE sa robi PINNING.
			ReturnValue=PrintStringAndGetLength(Param);

			Console.WriteLine(string.Format("Text: [{0}], Size: [{1}] !",Param,ReturnValue));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test16()
		{
			// !!! Vytvorim dostatocne dlhy buffer na data.
			byte[]												Chars=new byte[300];
			int													Size=Chars.Length/sizeof(char);
			int													OutSize;

			// Volam UNMANAGED CODE - IMPLICITNE sa robi PINNING.
			OutSize=FillString(Chars,Size);

			string												Text=UnicodeEncoding.Unicode.GetString(Chars,0,OutSize*sizeof(char));

			Console.WriteLine(string.Format("Text RECEIVED from UNMANAGED CODE: [{0}] !",Text));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			CName												Name=new CName("Timmy","Anderson",12);
			// CLASS WeakReference<T> je WRAPPED okolo VALUE TYPE GCHandle.
			WeakReference<CName>								WR=new WeakReference<CName>(Name);

			// !!! IsAllocated vracia informaciu IBA O TOM ci GCHandle je platny, ale NIE O TOM, ci OBJECT, ktory REPREZENTUJE ESTE EXISTUJE v HEAP, ALEBO UZ NIE.
			Console.WriteLine(PrintGCHandleState("OBJECT CREATED",WR));

			GC.Collect();

			// !!! OBJECT este EXISTUJE, lebo ma ROOT.
			Console.WriteLine(PrintGCHandleState("AFTER GC - OBJECT STILL has ROOT",WR));

			Name=null;

			Console.WriteLine(PrintGCHandleState("OBJECT HAS NO ROOT",WR));

			GC.Collect();

			// !!!!! OBJECT uz bol ODSTRANENY, alebo HANDLE este EXISTUJE.
			Console.WriteLine(PrintGCHandleState("AFTER GC - OBJECT HAS NO ROOT",WR));

			WR=null;

			GC.Collect();
			GC.Collect();
			GC.Collect();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			ConditionalWeakTable<CName,string>					CWT=new ConditionalWeakTable<CName,string>();
			CName												Name1=new CName("Timmy","Anderson",12);
			CName												Name2=new CName("Atreyu","",12);
			CName												Name3=new CName("Jenny","Thompson",13);

			// Asociujem si s kazdym OBJECT CName nejaky STRING.
			CWT.Add(Name1,"111");
			CWT.Add(Name2,"222");
			CWT.Add(Name3,"333");

			string												Value1;
			string												Value2;
			string												Value3;

			CWT.TryGetValue(Name1,out Value1);
			CWT.TryGetValue(Name2,out Value2);
			CWT.TryGetValue(Name3,out Value3);

			Console.WriteLine(string.Format("Name1: [{0}] !",Name1));
			Console.WriteLine(string.Format("Name2: [{0}] !",Name2));
			Console.WriteLine(string.Format("Name3: [{0}] !",Name3));

			// Vytvorim WEAK REFERENCES.
			GCHandle											Handle1=GCHandle.Alloc(Name1,GCHandleType.Weak);
			// Tuto refrenciu NEUMOZNIM ZRUSIT, lebo je Normal a GC ju TAK NEZRUSI.
			GCHandle											Handle2=GCHandle.Alloc(Name2,GCHandleType.Normal);
			GCHandle											Handle3=GCHandle.Alloc(Name3,GCHandleType.Weak);

			// ZRUSIM SKUTOCNE REFERENCES.
			Name1=null;
			Name2=null;
			Name3=null;

			Value1=null;
			Value2=null;
			Value3=null;

			// Skusim ci TABULKA este STALE OBSAHUJE HODNOTY.
			CWT.TryGetValue((CName) Handle1.Target,out Value1);
			CWT.TryGetValue((CName) Handle2.Target,out Value2);
			CWT.TryGetValue((CName) Handle3.Target,out Value3);

			// !!! Kedze este NEZBEHOL GC, tak referencie este STALE EXISTUJU.
			Console.WriteLine(string.Format("Value1: [{0}] !",Value1));
			Console.WriteLine(string.Format("Value2: [{0}] !",Value2));
			Console.WriteLine(string.Format("Value3: [{0}] !",Value3));

			// Vykonam GC.
			GC.Collect();

			Name1=(CName) Handle1.Target;
			Name2=(CName) Handle2.Target;
			Name3=(CName) Handle3.Target;

			if (Name1==null)
			{
				Console.WriteLine("Name1 is NULL !");
			}
			else
			{
				Console.WriteLine(string.Format("Name1: [{0}] !",Name1));
			}

			if (Name2==null)
			{
				Console.WriteLine("Name2 is NULL !");
			}
			else
			{
				Console.WriteLine(string.Format("Name2: [{0}] !",Name2));
			}

			if (Name3==null)
			{
				Console.WriteLine("Name3 is NULL !");
			}
			else
			{
				Console.WriteLine(string.Format("Name3: [{0}] !",Name3));
			}

			Handle1.Free();
			Handle2.Free();
			Handle3.Free();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			//Test6();
			//Test7();
			//Test8();
			//Test9();
			//Test10();
			//Test11();
			//Test12();
			//Test13();
			//Test14();
			//Test15();
			//Test16();
			//Test17();
			Test18();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------