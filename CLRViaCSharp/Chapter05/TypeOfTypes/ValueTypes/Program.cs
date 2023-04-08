using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace ValueTypes
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void PrintValueType(CNameStruct NameStruct)
		{
			NameStruct.Print();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CNameStruct											Name=new CNameStruct("Timmy","Anderson",12);

			Console.WriteLine(string.Format("Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			int													Value=100;
			string												Name="Timmy";
			object												Obj=new object();

			Console.WriteLine(string.Format("int.GetHashCode(): [{0}] !",Value.GetHashCode()));
			Console.WriteLine(string.Format("RuntimeHelpers.GetHashCode(int): [{0}] !",RuntimeHelpers.GetHashCode(Value)));
			Console.WriteLine();
			Console.WriteLine(string.Format("string.GetHashCode(): [{0}] !",Name.GetHashCode()));
			Console.WriteLine(string.Format("RuntimeHelpers.GetHashCode(string): [{0}] !",RuntimeHelpers.GetHashCode(Name)));
			Console.WriteLine();
			Console.WriteLine(string.Format("object.GetHashCode(): [{0}] !",Obj.GetHashCode()));
			Console.WriteLine(string.Format("RuntimeHelpers.GetHashCode(object): [{0}] !",RuntimeHelpers.GetHashCode(Obj)));
			Console.WriteLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			// VALUE TYPE implementuje INTERFACES.
			CStructWithInterfaces								StructWithInterfaces=new CStructWithInterfaces();
			IInterface1											Interface1=StructWithInterfaces;
			IInterface2											Interface2=StructWithInterfaces;

			Interface1.Method1();
			Interface2.Method2();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			// MInt bude obsahovat hodnotu 10*256+2.
			CUnion												Union1=new CUnion(2,10);
			// MByte1 bude obsahovat hodnotu 4 a MByte2 hodnotu 1.
			CUnion												Union2=new CUnion(260);

			Console.WriteLine(string.Format("Union1: [{0}] !",Union1));
			Console.WriteLine(string.Format("Union2: [{0}] !",Union2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			CNameStruct											ValueType=new CNameStruct("Timmy","Anderson",12);

			ValueType.Print();

			// Dochadza k BOXING.
			/*
				ldloc											ValueType
				// !!!!! BOXING vytvori instanciu REFERENCE TYPE na HEAP a ZAROVEN SKOPIRUJE vsetky FIELDS z VALUE TYPE na STACK do novovytvoreneho REFERENCE TYPE na HEAP.
				box												ValueTypes.CNameStruct
				stloc											ReferenceType
			*/
			object												ReferenceType=ValueType;

			// !!! Dochadza k UNBOXING a ZAROVEN aj ku KOPIROVANIU FIELDS.
			/*
				ldloc											ReferenceType
				// !!!!! UNBOXING iba vrati ADDRESS na 1. FIELDS VALUE TYPE ulozeneho na HEAP.
				unbox.any										ValueTypes.CNameStruct
				// !!!!! Tu dochadza ku KOPIROVANIU FIELDS. To vsak NIE JE SUCASTOU UNBOXING, ale je to OSOBITNA OPERACIA.
				stloc											NewValueType
			*/
			CNameStruct											NewValueType=(CNameStruct) ReferenceType;

			NewValueType.Print();

			// !!! Dochadza k UNBOXING a ZAROVEN aj ku KOPIROVANIU FIELDS, pretoze pri PRETYPOVANI na VALUE TYPE sa vytvara TEMPORARY VARIABLE na STACK do ktorej su nakopirovane FIELDS.
			/*
				ldloc											ReferenceType
				unbox.any										ValueTypes.CNameStruct
				stloc											Temp
				ldloca											Temp
				call											instance void ValueTypes.CNameStruct::Print()
			*/
			((CNameStruct) ReferenceType).Print();

			// !!!!! DOCHADZA k UNBOXING, pretoze INTERFACE je REFERENCE TYPE.
			/*
				ldloc											ValueType
				box												ValueTypes.CNameStruct
				callvirt										instance void ValueTypes.IPrint::Print()
			*/
			((IPrint) ValueType).Print();

			// !!!!! NEDOCHADZA ANI k UNBOXING a ANI ku KOPIROVANIU FIELDS, pretoze INTERFACE je REFERENCE TYPE.
			/*
				ldloc											ReferenceType
				castclass										ValueTypes.IPrint
				callvirt										instance void ValueTypes.IPrint::Print()
			*/
			((IPrint) ReferenceType).Print();

			// !!!!! Vykona UNBOXING a nasledne BOXING, avsak NEDOCHADZA ku KOPIROVANIU FIELDS. Avsak INSTRUCTION [box] interne KOPIROVANIE FIELDS VYKONAVA, takze k nemu NEPRIAMO DOCHADZA.
			/*
				ldstr											"NAME: [{0}] !"
				ldloc											ReferenceType
				// !!! Ziska ADDRESS na BOXED ReferenceType.
				unbox.any										ValueTypes.CNameStruct
				// !!!!! Kedze String.Format() pozaduje OBJECT ako PARAMETER, tak musi sa znova vykonat BOXING, pretoze na EVALUATION STACK prechadzajuca MSIL INSTRUCTION [unbox] zanechala ADDRESS na UNBOXED VALUE TYPE.
				box												ValueTypes.CNameStruct
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("NAME: [{0}] !",(CNameStruct)ReferenceType));

			// !!!!! Vykona UNBOXING po ktorom NENASLEDUJE EXPLICITNE KOPIROVANIE FIELDS.
			/*
				ldloc											ReferenceType
				unbox.any										ValueTypes.CNameStruct
				// !!!!! Volanie METHOD vsak SPOSOBI KOPIROVANIE FIELDS, pretoze VALUE TYPES su prenasane BY-VALUE a tie su VZDY prenasane cez STACK (aby boli NEZAVISLE na POVODNEJ HODNOTE).
				call											void ValueTypes.Program::PrintValueType(valuetype ValueTypes.CNameStruct)
			*/
			PrintValueType((CNameStruct)ReferenceType);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			Console.WriteLine("Calculating...");

			DateTime											Start;
			TimeSpan											Diff;
			CNameStruct											ValueType;
			object												ReferenceType;

			ValueType=new CNameStruct("Timmy","Anderson",12);

			Start=DateTime.Now;

			for(int Index=0;Index<1000*1000*250;Index++)
			{
				ReferenceType=ValueType;
			}

			Diff=DateTime.Now-Start;

			Console.WriteLine("BOXING - TIME: [{0}] !",Diff.TotalMilliseconds);

			ReferenceType=new CNameStruct("Timmy","Anderson",12);

			Start=DateTime.Now;

			for(int Index=0;Index<1000*1000*250;Index++)
			{
				// !!! Vykonava 2 operacie.
				// 1. CODE [(CNameStruct) ReferenceType] vykonava UNBOXING - ziskanie POINTER na FIELDS BOXED VALUE TYPE.
				// 2. CODE [ValueType=XXX] vykonava kopirovanie VSETKYCH FIELDS daneho VALUE TYPE do NOVEJ INSTANCIE VALUE TYPE.
				ValueType=(CNameStruct) ReferenceType;
			}

			Diff=DateTime.Now-Start;

			Console.WriteLine("UNBOXING and FULL COPY - TIME: [{0}] !",Diff.TotalMilliseconds);
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda je urcena na prezeranie cez ILDASM.exe.
		private static void Test7()
		{
			/*
				ldc.i4.s										100
				stloc											Value
			*/
			int													Value=100;

			// DOCHADZA ku BOXING.
			/*
				ldloc											Value
				box												[mscorlib]System.Int32
				stloc											Reference
			*/
			object												Reference=Value;

			// NEDOCHADZA k BOXING ani UNBOXING.
			/*
				ldloca.s										Value
				call											instance string [mscorlib]System.Int32::ToString()
				pop
			*/
			Value.ToString();
			/*
				ldloca.s										Value
				ldc.i4.s										100
				call											instance bool [mscorlib]System.Int32::Equals(int32)
				pop
			*/
			Value.Equals(100);
			/*
				ldloca.s										Value
				ldloc											Reference
				call											instance bool [mscorlib]System.Int32::Equals(object)
				pop
			*/
			Value.Equals(Reference);
			/*
				ldloca.s										Value
				call											instance int32 [mscorlib]System.Int32::GetHashCode()
				pop
			*/
			Value.GetHashCode();
			/*
				ldloca.s										Value
				ldc.i4.s										100
				call											instance int32 [mscorlib]System.Int32::CompareTo(int32)
				pop
			*/
			Value.CompareTo(100);
			/*
				ldloca.s										Value
				ldloc											Reference
				call											instance int32 [mscorlib]System.Int32::CompareTo(object)
				pop
			*/
			Value.CompareTo(Reference);

			// DOCHADZA k BOXING.
			/*
				ldloc											Value
				box												[mscorlib]System.Int32
				call											instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
				pop
			*/
			Value.GetType();

			// DOCHADZA k UNBOXING aj ku KOPIROVANIU FIELDS do TEMPORARY VALUE TYPE VARIABLE.
			/*
				ldloc											Reference
				unbox.any										[mscorlib]System.Int32
				stloc.s											TempInt
				ldloca.s										TempInt
				call											instance string [mscorlib]System.Int32::ToString()
				pop
			*/
			((int) Reference).ToString();

			// !!! Nedochadza k BOXING, lebo sa pouzivaju IBA REFERENCE TYPES.
			/*
				ldstr											"1 ---> INT [{0}] !"
				ldloc											Reference
				callvirt										instance string [mscorlib]System.Object::ToString()
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("1 ---> INT [{0}] !",Reference.ToString()));
			// !!! Dochadza k BOXING, lebo Format() vyzaduje ako PARAMETER Object co je REFERENCE TYPE.
			/*
				ldstr											"2 ---> INT [{0}] !"
				ldloc											Value
				box												[mscorlib]System.Int32
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("2 ---> INT [{0}] !",Value));
			// !!! NEDOCHADZA k BOXING ANI k UNBOXING, lebo Format() vyzaduje ako PARAMETER Object a STRING vrateni volanim ToString() je REFERENCE TYPE.
			/*
				ldstr											"3 ---> INT [{0}] !"
				ldloca.s										Value
				call											instance string [mscorlib]System.Int32::ToString()
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("3 ---> INT [{0}] !",Value.ToString()));
			// !!! DOCHADZA k UNBOXING a nasledne k BOXING - BEZ KOPIROVANIA FIELDS. BOXING je NUTNY, pretoze METHOD String.Format() vyzaduje Object ako PARAMETER.
			/*
				ldstr											"4 ---> INT [{0}] !"
				ldloc											Reference
				unbox.any										[mscorlib]System.Int32
				// BOXING je NUTNY, pretoze METHOD String.Format() vyzaduje Object ako PARAMETER.
				box												[mscorlib]System.Int32
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("4 ---> INT [{0}] !",(int) Reference));

			/*
				ldloca.s										Name
				ldstr											"Timmy"
				ldstr											"Anderson"
				ldc.i4.s										12
				call											instance void ValueTypes.CNameStruct::.ctor(string,string,int32)
			*/
			CNameStruct											Name=new CNameStruct("Timmy","Anderson",12);
			// Dochadza k BOXING.
			/*
				ldloc											Name
				box												ValueTypes.CNameStruct
				stloc											NameReference
			*/
			object												NameReference=Name;

			// NEDOCHADZA k BOXING ani UNBOXING.
			/*
				ldloca.s										Name
				constrained.									ValueTypes.CNameStruct
				callvirt										instance string [mscorlib]System.Object::ToString()
				pop
			*/
			Name.ToString();
			/*
				ldloca.s										Name
				ldloc											NameReference
				constrained.									ValueTypes.CNameStruct
				callvirt										instance bool [mscorlib]System.Object::Equals(object)
				pop
			*/
			Name.Equals(NameReference);
			/*
				ldloca.s										Name
				constrained.									ValueTypes.CNameStruct
				callvirt										instance int32 [mscorlib]System.Object::GetHashCode()
				pop
			*/
			Name.GetHashCode();

			// DOCHADZA k BOXING.
			/*
				ldloc											Name
				box												ValueTypes.CNameStruct
				call											instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
				pop
			*/
			Name.GetType();

			/*
			*/
			Console.WriteLine(string.Format("5 ---> NAME BEFORE NoChange(): [{0}] !",Name.ToString()));

			// NEDOCHADZA k BOXING ani UNBOXING.
			/*
				ldstr											"5 ---> NAME BEFORE NoChange(): [{0}] !"
				ldloca.s										Name
				constrained.									ValueTypes.CNameStruct
				callvirt										instance string [mscorlib]System.Object::ToString()
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
				ldloca.s										Name
				ldstr											"Jenny"
				ldstr											"Thompson"
				ldc.i4.s										13
				call											instance void ValueTypes.CNameStruct::NoChange(string,string,int32)
			*/
			Name.NoChange("Jenny","Thompson",13);
			/*
				ldstr											"6 ---> NAME BEFORE Change(): [{0}] !"
				ldloca.s										Name
				constrained.									ValueTypes.CNameStruct
				callvirt										instance string [mscorlib]System.Object::ToString()
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("6 ---> NAME BEFORE Change(): [{0}] !",Name.ToString()));

			// NEDOCHADZA k BOXING ani UNBOXING.
			/*
				ldloca.s										Name
				ldstr											"Jenny"
				ldstr											"Thompson"
				ldc.i4.s										13
				call											instance void ValueTypes.CNameStruct::Change(string,string,int32)
			*/
			Name.Change("Jenny","Thompson",13);
			/*
				ldstr											"7 ---> NAME AFTER Change(): [{0}] !"
				ldloca.s										Name
				constrained.									ValueTypes.CNameStruct
				callvirt										instance string [mscorlib]System.Object::ToString()
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("7 ---> NAME AFTER Change(): [{0}] !",Name.ToString()));

			// DOCHADZA k UNBOXING a vytvoreniu TEMPORARY VARIABLE na STACK do ktorej sa SKOPIRUJU FIELDS z BOXED VALUE TYPE.
			/*
				ldloc											NameReference
				unbox.any										ValueTypes.CNameStruct
				// !!! TEMPORARY VARIABLE.
				stloc.s											TempName
				ldloca.s										TempName
				ldstr											"Bubu"
				ldstr											""
				ldc.i4.s										15
				call											instance void ValueTypes.CNameStruct::NoChange(string,string,int32)
			*/
			((CNameStruct) NameReference).NoChange("Bubu","",15);
			// Nedochadza k BOXING, ani k UNBOXING.
			/*
				ldstr											"8 ---> NAME: [{0}] !"
				ldloca.s										Name
				constrained.									ValueTypes.CNameStruct
				callvirt										instance string [mscorlib]System.Object::ToString()
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("8 ---> NAME: [{0}] !",Name.ToString()));

			// DOCHADZA k UNBOXING a zmena sa urobi na TEMPORARY VARIABLE, ktora sa vytvori na STACKU.
			/*
				ldloc											NameReference
				unbox.any										ValueTypes.CNameStruct
				stloc.s											TempName
				ldloca.s										TempName
				ldstr											"Bubu"
				ldstr											""
				ldc.i4.s										15
				call											instance void ValueTypes.CNameStruct::Change(string,string,int32)
			*/
			((CNameStruct) NameReference).Change("Bubu","",15);
			// !!!!! Zmena volanim METHOD Change() NEMA VPLYV na INSTANCIU Name na STACKU, kedze sa jedna o 2 ROZDIELNE INSTANCIE.
			// Nedochadza k BOXING, ani k UNBOXING.
			/*
				ldstr											"9 ---> NAME: [{0}] !"
				ldloca.s										Name
				constrained.									ValueTypes.CNameStruct
				callvirt										instance string [mscorlib]System.Object::ToString()
				call											string [mscorlib]System.String::Format(string, object)
				call											void [mscorlib]System.Console::WriteLine(string)
				nop
			*/
			Console.WriteLine(string.Format("9 ---> NAME: [{0}] !",Name.ToString()));

			// DOCHADZA k UNBOXING a nasledne k BOXING.
			/*
				ldloc											NameReference
				unbox.any										ValueTypes.CNameStruct
				box												ValueTypes.CNameStruct
				callvirt										instance string [mscorlib]System.Object::ToString()
				pop
			*/
			((object) (CNameStruct) NameReference).ToString();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			CNameStruct											ValueType=new CNameStruct("Timmy","Anderson",12);

			// !!! INTERFACE METHOD sa vola PRIAMO, a preto sa BOXING NEROBI.
			/*
				ldloca.s										ValueType
				call											instance void ValueTypes.CNameStruct::Print()
			*/
			ValueType.Print();

			// !!! INTERFACE METHOD sa vola NEPRIAMO, a preto sa BOXING VYKONA.
			/*
				ldloc											ValueType
				box												ValueTypes.CNameStruct
				callvirt										instance void ValueTypes.IPrint::Print()
			*/
			((IPrint)ValueType).Print();

			// !!! Pri volani VIRTUAL METHODS nad VALUE TYPES, aj ked su volane VIRTUALNE v skutocnosti ich JIT COMPILER pri preklade konveruje na NON-VIRTUAL volanie.
			/*
				ldstr											"VALUE [{0}] !"
				ldloca.s										ValueType
				constrained.									ValueTypes.CNameStruct
				callvirt										instance string [mscorlib]System.Object::ToString()
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("VALUE [{0}] !",ValueType.ToString()));
			/*
				ldstr											"EQUALS [{0}] !"
				ldloca.s										ValueType
				ldloc											ValueType
				// BOXING PARAMETER METHOD ValueType.Equals().
				box												ValueTypes.CNameStruct
				constrained.									ValueTypes.CNameStruct
				callvirt										instance bool [mscorlib]System.Object::Equals(object)
				// BOXING RETURN VALUE.
				box												[mscorlib]System.Boolean
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("EQUALS [{0}] !",ValueType.Equals(ValueType)));
			/*
				ldstr											"HASH CODE [{0}] !"
				ldloca.s										ValueType
				constrained.									ValueTypes.CNameStruct
				callvirt										instance int32 [mscorlib]System.Object::GetHashCode()
				// BOXING RETURN VALUE.
				box												[mscorlib]System.Int32
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("HASH CODE [{0}] !",ValueType.GetHashCode()));

			// !!! Volanie NON-VIRTUAL METHOD ValueType.GetType() vyzaduje vykonanie BOXING.
			/*
				ldstr											"TYPE [{0}] !"
				ldloc											ValueType
				box												ValueTypes.CNameStruct
				call											instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			Console.WriteLine(string.Format("TYPE [{0}] !",ValueType.GetType()));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			try
			{
				int												Variable=10;
				object											BoxedVariable=Variable;
				// !!!!! Pri UNBOXING sa NEROBIA ZIADNE CONVERSION a tom dokonca ani CONVERSIONS INT na DOUBLE. Aj tieto CONVERSIONS sposobia generovanie EXCEPTIONS.
				double											UnboxedVariable=(double) BoxedVariable;

				Console.WriteLine(string.Format("UNBOXED VARIABLE [{0}] !",UnboxedVariable));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			CNameStruct											Name1=new CNameStruct("Timmy","Anderson",12);
			CNameStruct											Name2=new CNameStruct("Timmy","Anderson",12);
			CNameStruct											Name3=new CNameStruct("Timmy","Anderson",13);

			Console.WriteLine(string.Format("Name1.Equals(Name1): [{0}] !",Name1.Equals(Name1)));
			Console.WriteLine(string.Format("Name1.Equals(Name2): [{0}] !",Name1.Equals(Name2)));
			Console.WriteLine(string.Format("Name1.Equals(Name3): [{0}] !",Name1.Equals(Name3)));
			Console.WriteLine(string.Format("Name1.Equals(new object()): [{0}] !",Name1.Equals(new object())));

			Console.WriteLine(string.Format("Name1==Name2: [{0}] !",Name1==Name2));
			Console.WriteLine(string.Format("Name1==Name3: [{0}] !",Name1==Name3));

			Console.WriteLine(string.Format("Name1!=Name2: [{0}] !",Name1!=Name2));
			Console.WriteLine(string.Format("Name1!=Name3: [{0}] !",Name1!=Name3));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			CNameStruct											Name1=new CNameStruct("Timmy","Anderson",12);
			CNameStruct											Name2=new CNameStruct("Timmy","Anderson",12);
			CNameStruct											Name3=new CNameStruct("Timmy","Anderson",13);

			// !!! Zaujimave je, ze CNameStruct.GetHashCode(), ktora interne vola Object.GetHashCode() vratila pre VSETKY 3 NAMES ROVNAKE VALUES.
			Console.WriteLine(string.Format("HASH Name1: [{0}] !",Name1.GetHashCode()));
			Console.WriteLine(string.Format("HASH Name2: [{0}] !",Name2.GetHashCode()));
			Console.WriteLine(string.Format("HASH Name3: [{0}] !",Name3.GetHashCode()));
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
			Test11();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------