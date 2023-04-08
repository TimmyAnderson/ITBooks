using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace Arrays
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void ChangeArray(int[] Array)
		{
			for (int Index=0;Index<Array.Length;Index++)
			{
				Array[Index]+=100;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			int[]												SingleDimensionArray=new int[]{10,5,2};

			Console.WriteLine("SingleDimensionArray:");

			foreach(int Item in SingleDimensionArray)
			{
				Console.WriteLine(string.Format("\tItem: [{0}]",Item));
			}

			int[,]												MultiDimensionArray=new int[,]{{11,12,13},{21,22,23}};

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine("MultiDimensionArray:");

			for (int Dimension1=0;Dimension1<MultiDimensionArray.GetLength(0);Dimension1++)
			{
				for (int Dimension2=0;Dimension2<MultiDimensionArray.GetLength(1);Dimension2++)
				{
					Console.Write(string.Format("\tItem: [{0}]",MultiDimensionArray[Dimension1,Dimension2]));
				}

				Console.WriteLine();
			}

			int[][]												JaggedArray=new int[2][];

			JaggedArray[0]=new int[3]{11,12,13};
			JaggedArray[1]=new int[4]{21,22,23,24};

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine("JaggedArray:");

			for (int Dimension1=0;Dimension1<JaggedArray.GetLength(0);Dimension1++)
			{
				int[]											TempArray=JaggedArray[Dimension1];

				for (int Dimension2=0;Dimension2<TempArray.GetLength(0);Dimension2++)
				{
					Console.Write(string.Format("\tItem: [{0}]",TempArray[Dimension2]));
				}

				Console.WriteLine();
			}

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		// SIZEOF STRUCTURES je mozne pouzit iba v UNSAFE CODE.
		private static unsafe void Test2()
		{
			Console.WriteLine(string.Format("int[100]: [{0}] !",100*sizeof(int)));
			Console.WriteLine(string.Format("SBigStruct[100]: [{0}] !",100*sizeof(SBigStruct)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			int[]												SingleDimensionArray=new int[10];

			try
			{
				// Umyselne sa pokusim o pristup k ITEM, ktory neexistuje.
				for(int Index=0;Index<20;Index++)
				{
					SingleDimensionArray[Index]=Index;

					Console.WriteLine(string.Format("ITEM [{0}] was SET !",Index));
				}
			}
			catch(IndexOutOfRangeException E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			// Klasicky sposob inicializacie ARRAY.
			int[]												Array1=new int[]{10,5,2};

			Console.WriteLine("Array1:");

			foreach(int Item in Array1)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			// Inicializacia ARRAY BEZ DEFINOVANIA TYPU pri VYTVARANI ARRAY.
			int[]												Array2=new[]{10,5,2};

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine("Array2:");

			foreach(int Item in Array2)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			// Inicializacia ARRAY BEZ DEFINOVANIA TYPU i KLUCOVEHO SLOVA NEW pri VYTVARANI ARRAY.
			int[]												Array3={10,5,2};

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine("Array3:");

			foreach(int Item in Array3)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			// Inicializacia ARRAY BEZ DEFINOVANIA TYPU ako pri DEKLARACII, tak i pri VYTVARANI.
			var													Array4=new[]{10,5,2};

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine("Array4:");

			foreach(int Item in Array4)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			/*
			// // Hodi KOMPILACNU CHYBU.
			var													Array5={10,5,2};

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine("Array5:");

			foreach(int Item in Array5)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();
			*/

			/*
			// Hodi KOMPILACNU CHYBU.
			var													Array6=new[]{10,5,"Timmy"};

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine("Array6:");

			foreach(int Item in Array6)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();
			*/

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			string[]											Array1=new string[]{"Timmy","Jenny","Atreyu"};

			// IMPLICITNA konverzia.
			object[]											ConvertedArray1=Array1;

			Console.WriteLine("ConvertedArray1:");

			foreach(object Item in ConvertedArray1)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");

			object[]											Array2=new string[]{"Timmy","Jenny","Atreyu"};

			// EXPLICITNA konverzia.
			string[]											ConvertedArray2=(string[]) Array2;

			Console.WriteLine("ConvertedArray2:");

			foreach(object Item in ConvertedArray2)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");

			/*
			int[]												Array3=new int[]{10,5,2};

			// !!!!! KOMPILATOR hodi CHYBU, pretoze NEUMOZNUJE KONVERZIU ARRAYS pre VALUE TYPES.
			object[]											ConvertedArray3=Array3;

			Console.WriteLine("ConvertedArray3:");

			foreach(object Item in ConvertedArray3)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}
			*/

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				object[]										Array4=new object[]{"Timmy","Anderson",12};

				// EXPLICITNA konverzia sice prebehne, ale HODI EXCEPTION, pretoze nie vsetky ARRAY ITEMS su STRINGS.
				string[]										ConvertedArray4=(string[]) Array4;

				Console.WriteLine("ConvertedArray4:");

				foreach(object Item in ConvertedArray4)
				{
					Console.Write(string.Format("\tItem: [{0}]",Item));
				}

				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("\nEXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			/*
			try
			{
				string[]										Array5=new string[]{"Timmy","Anderson"};

				// COMPILER hodi ERROR, pretoze konverzia SINGLE DIMENSION ARRAYS na MULTIDIMENSIONS ARRAYS nie je mozna.
				string[,]										ConvertedArray5=(string[,]) Array5;

				Console.WriteLine("ConvertedArray5:");

				foreach(object Item in ConvertedArray5)
				{
					Console.Write(string.Format("\tItem: [{0}]",Item));
				}

				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("\nEXCEPTION: [{0}] !",E.Message));
			}
			*/

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				object[,]										Array6=new string[2,2]{{"Timmy","Anderson"},{"Jenny","Thompson"}};

				// Explicitna konverzia 2 DIMENSIONALS ARRAYS prebehne korektne.
				string[,]										ConvertedArray6=(string[,]) Array6;

				Console.WriteLine("ConvertedArray6:");

				for (int Dimension1=0;Dimension1<ConvertedArray6.GetLength(0);Dimension1++)
				{
					for (int Dimension2=0;Dimension2<ConvertedArray6.GetLength(1);Dimension2++)
					{
						Console.Write(string.Format("\tItem: [{0}]",ConvertedArray6[Dimension1,Dimension2]));
					}

					Console.WriteLine();
				}

				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("\nEXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				string[,]										Array7=new string[2,2]{{"Timmy","Anderson"},{"Jenny","Thompson"}};

				// Implicitna konverzia 2 DIMENSIONALS ARRAYS prebehne korektne.
				object[,]										ConvertedArray7=Array7;

				Console.WriteLine("ConvertedArray7:");

				for (int Dimension1=0;Dimension1<ConvertedArray7.GetLength(0);Dimension1++)
				{
					for (int Dimension2=0;Dimension2<ConvertedArray7.GetLength(1);Dimension2++)
					{
						Console.Write(string.Format("\tItem: [{0}]",ConvertedArray7[Dimension1,Dimension2]));
					}

					Console.WriteLine();
				}

				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("\nEXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				FileStream[,]									Array8=new FileStream[2,2];

				// Implicitna konverzia 2 DIMENSIONALS ARRAYS prebehne korektne.
				object[,]										ConvertedArray8=Array8;

				Console.WriteLine("ConvertedArray8:");

				for (int Dimension1=0;Dimension1<ConvertedArray8.GetLength(0);Dimension1++)
				{
					for (int Dimension2=0;Dimension2<ConvertedArray8.GetLength(1);Dimension2++)
					{
						Console.Write(string.Format("\tItem: [{0}]",ConvertedArray8[Dimension1,Dimension2]));
					}

					Console.WriteLine();
				}

				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("\nEXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				object[,]										Array9=new FileStream[2,2];

				// Explicitna konverzia 2 DIMENSIONALS ARRAYS prebehne korektne.
				Stream[,]										ConvertedArray9=(Stream[,])Array9;

				Console.WriteLine("ConvertedArray9:");

				for (int Dimension1=0;Dimension1<ConvertedArray9.GetLength(0);Dimension1++)
				{
					for (int Dimension2=0;Dimension2<ConvertedArray9.GetLength(1);Dimension2++)
					{
						Console.Write(string.Format("\tItem: [{0}]",ConvertedArray9[Dimension1,Dimension2]));
					}

					Console.WriteLine();
				}

				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("\nEXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				object[,]										Array10=new object[2,2]{{"Timmy","Anderson"},{"Jenny","Thompson"}};

				// !!!!! Explicitna konverzia 2 DIMENSIONALS ARRAYS hodi RUNTIME ERROR, pretoze ARRAY nie je STRING[,], alebo OBJECT[,]. Konverzia by prebehla OK, ak by ARRAY Array10 bol vytvoreny ako [Array10=new string[2,2]{{"Timmy","Anderson"},{"Jenny","Thompson"}};].
				string[,]										ConvertedArray10=(string[,]) Array10;

				Console.WriteLine("ConvertedArray10:");

				for (int Dimension1=0;Dimension1<ConvertedArray10.GetLength(0);Dimension1++)
				{
					for (int Dimension2=0;Dimension2<ConvertedArray10.GetLength(1);Dimension2++)
					{
						Console.Write(string.Format("\tItem: [{0}]",ConvertedArray10[Dimension1,Dimension2]));
					}

					Console.WriteLine();
				}

				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("\nEXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			int[]												Array1=new int[]{10,5,2};
			double[]											ConvertedArray1=new double[Array1.Length];

			// Pouzitie Array.Copy() na konverziu VALUE TYPES.
			Array.Copy(Array1,ConvertedArray1,Array1.Length);

			Console.WriteLine(string.Format("ConvertedArray1 [{0}]:",ConvertedArray1.GetType()));

			foreach(object Item in ConvertedArray1)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");

			SNumber[]											Array2=new SNumber[]{new SNumber(10),new SNumber(5),new SNumber(2)};
			IComparable[]										ConvertedArray2=new IComparable[Array2.Length];

			// Pouzitie Array.Copy() na konverziu z VALUE TYPES na INTERFACE ARRAY.
			Array.Copy(Array2,ConvertedArray2,Array2.Length);

			Console.WriteLine(string.Format("ConvertedArray2 [{0}]:",ConvertedArray2.GetType()));

			foreach(object Item in ConvertedArray2)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");

			CNumber[]											Array3=new CNumber[]{new CNumber(10),new CNumber(5),new CNumber(2)};
			IComparable[]										ConvertedArray3=new IComparable[Array3.Length];

			// Pouzitie Array.Copy() na konverziu z REFERENCE TYPES na INTERFACE ARRAY.
			Array.Copy(Array3,ConvertedArray3,Array3.Length);

			Console.WriteLine(string.Format("ConvertedArray3 [{0}]:",ConvertedArray3.GetType()));

			foreach(object Item in ConvertedArray3)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");

			object[]											Array4=new object[]{10,5,"Timmy"};
			double[]											ConvertedArray4=new double[Array4.Length];

			ConvertedArray4[0]=1.1;
			ConvertedArray4[1]=2.2;
			ConvertedArray4[2]=3.3;

			Console.WriteLine(string.Format("BEFORE CHANGE - ConvertedArray4 [{0}]:",ConvertedArray4.GetType()));

			foreach(object Item in ConvertedArray4)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// Pouzitie Array.Copy() na konverziu VALUE TYPES.
				Array.Copy(Array4,ConvertedArray4,Array4.Length);

				Console.WriteLine(string.Format("ConvertedArray4 [{0}]:",ConvertedArray4.GetType()));

				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("\nEXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine(string.Format("AFTER CHANGE - ConvertedArray4 [{0}]:",ConvertedArray4.GetType()));

			foreach(object Item in ConvertedArray4)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");

			object[]											Array5=new object[]{10,5,"Timmy"};
			double[]											ConvertedArray5=new double[Array5.Length];

			ConvertedArray5[0]=1.1;
			ConvertedArray5[1]=2.2;
			ConvertedArray5[2]=3.3;

			Console.WriteLine(string.Format("BEFORE CHANGE - ConvertedArray5 [{0}]:",ConvertedArray5.GetType()));

			foreach(object Item in ConvertedArray5)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!!!! Pouzitie Array.ConstrainedCopy() na konverziu VALUE TYPES.
				Array.ConstrainedCopy(Array5,0,ConvertedArray5,0,Array5.Length);

				Console.WriteLine(string.Format("ConvertedArray5 [{0}]:",ConvertedArray4.GetType()));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("\nEXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine(string.Format("AFTER CHANGE - ConvertedArray5 [{0}]:",ConvertedArray5.GetType()));

			foreach(object Item in ConvertedArray5)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			SNumber												ValueItem1=new SNumber(10);
			SNumber												ValueItem2=new SNumber(5);
			SNumber												ValueItem3=new SNumber(2);

			SNumber[]											Array1=new SNumber[]{ValueItem1,ValueItem2,ValueItem3};
			
			// !!! ARRAY pre VALUE TYPES implementuje IList<SNumber>.
			IList<SNumber>										List1=Array1;

			Console.WriteLine(string.Format("IList<SNumber>.IndexOf(): [{0}] !",List1.IndexOf(ValueItem3)));

			// ARRAY pre VALUE TYPES implementuje IList.
			IList												List2=Array1;

			Console.WriteLine(string.Format("IList.IndexOf(): [{0}] !",List2.IndexOf(ValueItem3)));

			CDerivedNumber										ReferenceItem1=new CDerivedNumber(10);
			CDerivedNumber										ReferenceItem2=new CDerivedNumber(5);
			CDerivedNumber										ReferenceItem3=new CDerivedNumber(2);

			CDerivedNumber[]									Array2=new CDerivedNumber[]{ReferenceItem1,ReferenceItem2,ReferenceItem3};

			// !!! ARRAY pre REFERENCE TYPES implementuje IList<CDerivedNumber>.
			IList<CDerivedNumber>								List3=Array2;

			Console.WriteLine(string.Format("IList<CDerivedNumber>.IndexOf(): [{0}] !",List3.IndexOf(ReferenceItem3)));

			// !!!!! ARRAY pre REFERENCE TYPES implementuje IList<CNumber>, lebo CDerivedNumber je DERIVED CLASS voci CNumber.
			IList<CNumber>										List4=Array2;

			Console.WriteLine(string.Format("IList<CNumber>.IndexOf(): [{0}] !",List4.IndexOf(ReferenceItem3)));

			// !!!!! ARRAY pre REFERENCE TYPES implementuje IList<Object>.
			IList<object>										List5=Array2;

			Console.WriteLine(string.Format("IList<object>.IndexOf(): [{0}] !",List5.IndexOf(ReferenceItem3)));

			// ARRAY pre REFERENCE TYPES implementuje aj IList.
			IList												List6=Array2;

			Console.WriteLine(string.Format("IList.IndexOf(): [{0}] !",List6.IndexOf(ReferenceItem3)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			int[]												Array=new int[]{1,2,3};

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine("ARRAY BEFORE METHOD CALL:");

			foreach(int Item in Array)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			ChangeArray(Array);

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine("ARRAY AFTER METHOD CALL:");

			foreach(int Item in Array)
			{
				Console.Write(string.Format("\tItem: [{0}]",Item));
			}

			Console.WriteLine();

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			// Vytvorim ARRAY, ktory ZACINA INDEXOM 0.
			int[,]												ZeroIndexMultiDimensionArray=new int[2,3];

			ZeroIndexMultiDimensionArray[0,0]=11;
			ZeroIndexMultiDimensionArray[0,1]=12;
			ZeroIndexMultiDimensionArray[0,2]=13;
			ZeroIndexMultiDimensionArray[1,0]=21;
			ZeroIndexMultiDimensionArray[1,1]=22;
			ZeroIndexMultiDimensionArray[1,2]=23;

			Console.WriteLine(string.Format("ZeroIndexMultiDimensionArray - [{0}], Length [{1}]:",ZeroIndexMultiDimensionArray.GetType(),ZeroIndexMultiDimensionArray.Length));

			for (int Dimension1=ZeroIndexMultiDimensionArray.GetLowerBound(0);Dimension1<=ZeroIndexMultiDimensionArray.GetUpperBound(0);Dimension1++)
			{
				for (int Dimension2=ZeroIndexMultiDimensionArray.GetLowerBound(1);Dimension2<=ZeroIndexMultiDimensionArray.GetUpperBound(1);Dimension2++)
				{
					Console.Write(string.Format("\tItem [{0},{1}]: [{2}]",Dimension1,Dimension2,ZeroIndexMultiDimensionArray[Dimension1,Dimension2]));
				}

				Console.WriteLine();
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Vytvorim ARRAY, ktory NEZACINA INDEXOM 0.
			// !!!!! Tuto konverziu CLR POVOLI, pretoze pre MULTI-DIMENSIONS ARRAYS - BEZ ohladu na to s akym INDEXOM zacinaju su VZDY obsluhovane cez METHODS Array.GetValue() a Array.SetValue() a NIKDY sa pre ne nepouzivaju specializovane MSIL INSTRUCTIONS.
			int[,]												Non0IndexMultiDimensionArray1=(int[,]) Array.CreateInstance(typeof(int),new int[]{2,3},new int[]{-2,5});

			Non0IndexMultiDimensionArray1[-2,5]=11;
			Non0IndexMultiDimensionArray1[-2,6]=12;
			Non0IndexMultiDimensionArray1[-2,7]=13;
			Non0IndexMultiDimensionArray1[-1,5]=21;
			Non0IndexMultiDimensionArray1[-1,6]=22;
			Non0IndexMultiDimensionArray1[-1,7]=23;

			Console.WriteLine(string.Format("Non0IndexMultiDimensionArray1 - [{0}], Length [{1}]:",Non0IndexMultiDimensionArray1.GetType(),Non0IndexMultiDimensionArray1.Length));

			for (int Dimension1=Non0IndexMultiDimensionArray1.GetLowerBound(0);Dimension1<=Non0IndexMultiDimensionArray1.GetUpperBound(0);Dimension1++)
			{
				for (int Dimension2=Non0IndexMultiDimensionArray1.GetLowerBound(1);Dimension2<=Non0IndexMultiDimensionArray1.GetUpperBound(1);Dimension2++)
				{
					Console.Write(string.Format("\tItem [{0},{1}]: [{2}]",Dimension1,Dimension2,Non0IndexMultiDimensionArray1[Dimension1,Dimension2]));
				}

				Console.WriteLine();
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Vytvorim ARRAY, ktory NEZACINA INDEXOM 0.
			// !!!!! Tuto konverziu CLR POVOLI, pretoze pre MULTI-DIMENSIONS ARRAYS - BEZ ohladu na to s akym INDEXOM zacinaju su VZDY obsluhovane cez METHODS Array.GetValue() a Array.SetValue() a NIKDY sa pre ne nepouzivaju specializovane MSIL INSTRUCTIONS.
			Array												Non0IndexMultiDimensionArray2=(int[,]) Array.CreateInstance(typeof(int),new int[]{2,3},new int[]{-2,5});

			Non0IndexMultiDimensionArray2.SetValue(11,-2,5);
			Non0IndexMultiDimensionArray2.SetValue(12,-2,6);
			Non0IndexMultiDimensionArray2.SetValue(13,-2,7);
			Non0IndexMultiDimensionArray2.SetValue(21,-1,5);
			Non0IndexMultiDimensionArray2.SetValue(22,-1,6);
			Non0IndexMultiDimensionArray2.SetValue(23,-1,7);

			Console.WriteLine(string.Format("Non0IndexMultiDimensionArray2 - [{0}], Length [{1}]:",Non0IndexMultiDimensionArray2.GetType(),Non0IndexMultiDimensionArray2.Length));

			for (int Dimension1=Non0IndexMultiDimensionArray2.GetLowerBound(0);Dimension1<=Non0IndexMultiDimensionArray2.GetUpperBound(0);Dimension1++)
			{
				for (int Dimension2=Non0IndexMultiDimensionArray2.GetLowerBound(1);Dimension2<=Non0IndexMultiDimensionArray2.GetUpperBound(1);Dimension2++)
				{
					Console.Write(string.Format("\tItem [{0},{1}]: [{2}]",Dimension1,Dimension2,Non0IndexMultiDimensionArray2.GetValue(Dimension1,Dimension2)));
				}

				Console.WriteLine();
			}

			Console.WriteLine("-------------------------------------------------------------------------------");

			/*
			try
			{
				// !!! Hodi EXCEPTION, pretoze ARRAYS zacinajuce od INEHO INDEXU ako 0 NIE JE MOZNE ulozit do SINGLE DIMENSION ARRAYS. SINGLE DIMENSION ARRAYS s pociatocnym INDEXOM 0 maju SPECIALIZOVANE MSIL INSTRUCTIONS, a preto su NEKOMPATIBILNE so SINGLE DIMENSION ARRAYS, ktore maju pociatocny INDEX INY ako 0.
				int[]											Non0IndexSingleDimensionArray1=(int[]) Array.CreateInstance(typeof(int),new int[]{3},new int[]{-2});

				// !!! Hodi pri kompilacii WARINING, pretoze C# NEPODPORUJE ZAPORNY INDEX. K zapornym indexom je mozne pristupova IBA pomocou METHODS Array.SetValue() a Array.GetValue().
				Non0IndexSingleDimensionArray1[-2]=11;
				Non0IndexSingleDimensionArray1[-1]=12;
				Non0IndexSingleDimensionArray1[0]=13;

				Console.WriteLine(string.Format("Non0IndexSingleDimensionArray1 - [{0}], Length [{1}]:",Non0IndexSingleDimensionArray1.GetType(),Non0IndexSingleDimensionArray1.Length));

				for (int Dimension=Non0IndexSingleDimensionArray1.GetLowerBound(0);Dimension<=Non0IndexSingleDimensionArray1.GetUpperBound(0);Dimension++)
				{
					Console.Write(string.Format("\tItem [{0}]: [{1}]",Dimension,Non0IndexSingleDimensionArray1[Dimension]));
				}

				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("\nEXCEPTION: [{0}] !",E.Message));
			}
			*/

			Console.WriteLine("-------------------------------------------------------------------------------");

			try
			{
				// !!! SINGLE DIMENSION ARRAYS s pociatocnym INDEXOM ROZNYM ako 0 NEMOZU byt konverovane na SINGLE DIMENSION ARRAYS s pociatocnym INDEXOM 0 - pretoze tieto pouzivaju SPECIALIZOVANE MSIL INSTRUCTIONS.
				Array											Non0IndexSingleDimensionArray2=Array.CreateInstance(typeof(int),new int[]{3},new int[]{-2});

				// !!! Zapis do ARRAY ITEMS je mozny IBA cez METHOD Array.SetValue().
				Non0IndexSingleDimensionArray2.SetValue(10,-2);
				Non0IndexSingleDimensionArray2.SetValue(5,-1);
				Non0IndexSingleDimensionArray2.SetValue(2,0);

				// Pole je typu Int32[*], kde znak '*' charakterizuje to, ze ARRAY NEZACINA INDEXOM 0.
				Console.WriteLine(string.Format("Non0IndexSingleDimensionArray2 - [{0}], Length [{1}]:",Non0IndexSingleDimensionArray2.GetType(),Non0IndexSingleDimensionArray2.Length));

				for (int Dimension=Non0IndexSingleDimensionArray2.GetLowerBound(0);Dimension<=Non0IndexSingleDimensionArray2.GetUpperBound(0);Dimension++)
				{
					// !!! Citanie ARRAY ITEMS je mozne IBA cez METHOD Array.GetValue().
					Console.Write(string.Format("\tItem [{0}]: [{1}]",Dimension,Non0IndexSingleDimensionArray2.GetValue(Dimension)));
				}

				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("\nEXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		// UNSAFE METODA.
		private unsafe static void Test10()
		{
			int[]												UnsafeAccessedArray=new int[]{10,5,2};

			Console.WriteLine("UnsafeAccessedArray:");

			fixed(int* Pointer=UnsafeAccessedArray)
			{
				for (int Index=0;Index<UnsafeAccessedArray.Length;Index++)
				{
					int											Value=Pointer[Index];

					Console.Write(string.Format("\tItem [{0}]: [{1}]",Index,Value));
				}
			}

			Console.WriteLine();
		}
//-------------------------------------------------------------------------------------------------------
		// UNSAFE METODA.
		private unsafe static void Test11()
		{
			// !!!!! Tento objekt sa alokuje na STACK a NIE na HEAP.
			SStackArray											StackArray=new SStackArray();
			string												Text="Timmy Anderson";

			for (int Index=0;Index<Text.Length;Index++)
			{
				StackArray.MArrayOnStack[Index]=Text[Index];
			}

			// Z BUFFERA CHARS na STACKU vytvorim STRING.
			string												Output=new string(StackArray.MArrayOnStack,0,Text.Length);

			Console.WriteLine(string.Format("Output: [{0}] !",Output));
		}
//-------------------------------------------------------------------------------------------------------
		// UNSAFE METODA.
		private unsafe static void Test12()
		{
			// Alokujem BUFFER na STACK.
			// !!! FIXED netreba pouzivat, pretoze je pamat je alokovana na STACK a NIE na HEAP.
			char*												Buffer=stackalloc char[1000];
			string												Text="Timmy Anderson";

			for (int Index=0;Index<Text.Length;Index++)
			{
				Buffer[Index]=Text[Index];
			}

			// Z BUFFERA CHARS na STACKU vytvorim STRING.
			string												Output=new string(Buffer,0,Text.Length);

			Console.WriteLine(string.Format("Output: [{0}] !",Output));
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
			Test12();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------