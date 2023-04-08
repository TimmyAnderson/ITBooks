using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace CSharpEssentialFeatures
{
//----------------------------------------------------------------------------------------------------------------------
	class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		private static SemaphoreSlim							MSemaphoreSlimAsync=new SemaphoreSlim(1,1);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestStringOperators()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			CClass1												Object1=new CClass1("AAA",100,new CClass2("BBB",200));
			CClass1												Object2=new CClass1("AAA",100,new CClass2(null,200));
			CClass1												Object3=new CClass1(null,100,new CClass2("BBB",200));

			// !!! Na OPERATOR?. je mozne aplikovat aj OPERATOR CHAINING.
			Console.WriteLine($"OBJECT 1 - VALUE 1 [{Object1?.GetValue1()}] VALUE 2 [{Object1?.Value2}] VALUE 3 [VALUE 1 [{Object1?.Value3?.Value1}] VALUE 2 [{Object1?.Value3?.Value2}]] !");

			Console.WriteLine($"OBJECT 2 - VALUE 1 [{Object2?.GetValue1()}] VALUE 2 [{Object2?.Value2}] VALUE 3 [VALUE 1 [{Object2?.Value3?.Value1}] VALUE 2 [{Object2?.Value3?.Value2}]] !");

			Console.WriteLine($"OBJECT 3 - VALUE 1 [{Object3?.GetValue1()}] VALUE 2 [{Object3?.Value2}] VALUE 3 [VALUE 1 [{Object3?.Value3?.Value1}] VALUE 2 [{Object3?.Value3?.Value2}]] !");

			// !!! Aplikuje sa OPERATOR??.
			Console.WriteLine($"OBJECT 3 - VALUE 1 [{Object3?.GetValue1() ?? "NULL"}] VALUE 2 [{Object3?.Value2 ?? 0}] VALUE 3 [VALUE 1 [{Object3?.Value3?.Value1 ?? "NULL"}] VALUE 2 [{Object3?.Value3?.Value2 ?? 0}]] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			CClass1[]											Array=new CClass1[]{Object1,null};

			Console.WriteLine($"ARRAY[0] - VALUE 1 [{Array?[0].GetValue1()}] VALUE 2 [{Array?[0].Value2}] VALUE 3 [VALUE 1 [{Array?[0].Value3?.Value1}] VALUE 2 [{Array?[0].Value3?.Value2}]] !");

			Console.WriteLine($"ARRAY[1] - VALUE 1 [{Array?[1]?.GetValue1()}] VALUE 2 [{Array?[1]?.Value2}] VALUE 3 [VALUE 1 [{Array?[1]?.Value3?.Value1}] VALUE 2 [{Array?[1]?.Value3?.Value2}]] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			Array=null;

			Console.WriteLine($"ARRAY[0] - VALUE 1 [{Array?[0].GetValue1()}] VALUE 2 [{Array?[0].Value2}] VALUE 3 [VALUE 1 [{Array?[0].Value3?.Value1}] VALUE 2 [{Array?[0].Value3?.Value2}]] !");

			Console.WriteLine($"ARRAY[1] - VALUE 1 [{Array?[1]?.GetValue1()}] VALUE 2 [{Array?[1]?.Value2}] VALUE 3 [VALUE 1 [{Array?[1]?.Value3?.Value1}] VALUE 2 [{Array?[1]?.Value3?.Value2}]] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAutomaticProperties()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			CAutomaticProperties								Object1=new CAutomaticProperties();

			Console.WriteLine($"OBJECT 1 - FIELD 1 [{Object1.Field1.Value}] FIELD 2 [{Object1.Field2.Value}] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			CAutomaticProperties								Object2=new CAutomaticProperties("AAA");

			// !!! Pre PROPERTY 'Field1' sa 2 krat vola CONSTRUCTOR.
			Console.WriteLine($"OBJECT 2 - FIELD 1 [{Object2.Field1.Value}] FIELD 2 [{Object2.Field2.Value}] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// !!! Pre PROPERTY 'Field1' a PROPERTY 'Field2' sa 2 krat vola CONSTRUCTOR.
			CAutomaticProperties								Object3=new CAutomaticProperties("AAA","BBB");

			Console.WriteLine($"OBJECT 3 - FIELD 1 [{Object3.Field1.Value}] FIELD 2 [{Object3.Field2.Value}] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			string[]											Strings=new string[3];

			Strings[0]="Timmy";
			Strings[1]=null;
			Strings[2]="Anderson";

			for(int Index=0;Index<Strings.Length;Index++)
			{
				string											String=Strings[Index];

				// !!! Pouzije sa OPERATOR ?[].
				Console.WriteLine($"STRING [{Index}] - VALUE [{Strings?[Index]}] !");
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestStringInterpolation()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			string												Value1="AAA";
			int													Value2=100;

			Console.WriteLine($"VALUE 1 [{Value1}] VALUE 2 [{Value2}] !");

			// !!! STRING INTERPOLATION umoznuje CUSTOM formatovanie.
			Console.WriteLine($"VALUE 1 [{Value1}] VALUE 2 [{Value2:X4}] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestObjectInitializers()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// !!! Pouziva sa OBJECT INITIALIZER SYNTAX.
			CClass1												Object=new CClass1{Value1="AAA",Value2=100,Value3=new CClass2{Value1="BBB",Value2=200}};

			Console.WriteLine($"OBJECT - VALUE 1 [{Object?.GetValue1()}] VALUE 2 [{Object?.Value2}] VALUE 3 [VALUE 1 [{Object?.Value3?.Value1}] VALUE 2 [{Object?.Value3?.Value2}]] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestArrayInitializers()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// !!! Pouziva sa ARRAY INITIALIZER SYNTAX.
			string[]											Array=new string[]{"AAA","BBB","CCC"};

			foreach(string Item in Array)
			{
				Console.WriteLine($"ITEM [{Item}] !");
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestCollectionInitializers()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// !!! Pouziva sa COLLECTION INITIALIZER SYNTAX.
			List<string>										Collection=new List<string>{"AAA","BBB","CCC"};

			foreach(string Item in Collection)
			{
				Console.WriteLine($"ITEM [{Item}] !");
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestIndexerInitializers()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// !!! Pouziva sa INDEXER INITIALIZER SYNTAX.
			Dictionary<string,CClass2>							Collection1=new Dictionary<string,CClass2>{{"AAA",new CClass2("AAA",100)},{"BBB",new CClass2("BBB",200)},{"CCC",new CClass2("CCC",300)}};

			Console.WriteLine($"COLLECTION 1 - ITEM 1 - VALUE 1 [{Collection1["AAA"].Value1}] VALUE 2 [{Collection1["AAA"].Value2}] !");
			Console.WriteLine($"COLLECTION 1 - ITEM 2 - VALUE 1 [{Collection1["BBB"].Value1}] VALUE 2 [{Collection1["BBB"].Value2}] !");
			Console.WriteLine($"COLLECTION 1 - ITEM 3 - VALUE 1 [{Collection1["CCC"].Value1}] VALUE 2 [{Collection1["CCC"].Value2}] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// !!! Pouziva sa INDEXER INITIALIZER SYNTAX.
			Dictionary<string,CClass2>							Collection2=new Dictionary<string,CClass2>{["AAA"]=new CClass2("AAA",100),["BBB"]=new CClass2("BBB",200),["CCC"]=new CClass2("CCC",300)};

			Console.WriteLine($"COLLECTION 2 - ITEM 1 - VALUE 1 [{Collection2["AAA"].Value1}] VALUE 2 [{Collection2["AAA"].Value2}] !");
			Console.WriteLine($"COLLECTION 2 - ITEM 2 - VALUE 1 [{Collection2["BBB"].Value1}] VALUE 2 [{Collection2["BBB"].Value2}] !");
			Console.WriteLine($"COLLECTION 2 - ITEM 3 - VALUE 1 [{Collection2["CCC"].Value1}] VALUE 2 [{Collection2["CCC"].Value2}] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// !!! Pouziva sa INDEXER INITIALIZER SYNTAX.
			CIndexerCollection									Collection3=new CIndexerCollection{["AAA"]=new CClass2("AAA",100),["BBB"]=new CClass2("BBB",200),["CCC"]=new CClass2("CCC",300)};

			Console.WriteLine($"COLLECTION 3 - ITEM 1 - VALUE 1 [{Collection3["AAA"].Value1}] VALUE 2 [{Collection3["AAA"].Value2}] !");
			Console.WriteLine($"COLLECTION 3 - ITEM 2 - VALUE 1 [{Collection3["BBB"].Value1}] VALUE 2 [{Collection3["BBB"].Value2}] !");
			Console.WriteLine($"COLLECTION 3 - ITEM 3 - VALUE 1 [{Collection3["CCC"].Value1}] VALUE 2 [{Collection3["CCC"].Value2}] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOperatorIs()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			object[]											Objects=new object[5];

			Objects[0]=100;
			Objects[1]=200;
			Objects[2]=123.456;
			Objects[3]=234.567;
			Objects[4]="Timmy Anderson";

			foreach(object Object in Objects)
			{
				if (Object is int TypedObject1)
				{
					Console.WriteLine($"INT - VALUE [{TypedObject1}] !");
				}
				// !!! Nezmyslom tejto SYNTAXE je, ze SCOPE VARIABLE 'TypedObject2' je na urovni PARENT COMMAND a tym padom pri viacerych 'if' je nutne mat vzdy ROZDIELNY NAZOV VARIABLES pre VSETKY 'if'.
				else if (Object is double TypedObject2)
				{
					Console.WriteLine($"DOUBLE - VALUE [{TypedObject2}] !");
				}
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestOperatorCaseWhen()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			object[]											Objects=new object[5];

			Objects[0]=100;
			Objects[1]=200;
			Objects[2]=123.456;
			Objects[3]=234.567;
			Objects[4]="Timmy Anderson";

			foreach(object Object in Objects)
			{
				switch(Object)
				{
					case int TypedObject when TypedObject<=100:
					{
						Console.WriteLine($"INT + WHEN - VALUE [{TypedObject}] !");
					}
					break;

					case int TypedObject:
					{
						Console.WriteLine($"INT - VALUE [{TypedObject}] !");
					}
					break;

					case double TypedObject when TypedObject<=200.0:
					{
						Console.WriteLine($"DOUBLE + WHEN - VALUE [{TypedObject}] !");
					}
					break;

					case double TypedObject:
					{
						Console.WriteLine($"DOUBLE - VALUE [{TypedObject}] !");
					}
					break;
				}
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestExtensionMethods()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			CClass1												Object=new CClass1{Value1="AAA",Value2=100,Value3=new CClass2{Value1="BBB",Value2=200}};

			// Vola sa EXTENSION METHOD.
			Console.WriteLine($"OBJECT - {Object.Print()} !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			List<string>										Strings=new List<string>();

			Strings.Add("My");
			Strings.Add("name");
			Strings.Add("is");
			Strings.Add("Timmy");
			Strings.Add("Anderson");
			Strings.Add("!");

			// Vola sa EXTENSION METHOD.
			Console.WriteLine($"COLLECTION - {Strings.Print()} !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			List<int>											Integers=new List<int>();

			Integers.Add(100);
			Integers.Add(200);
			Integers.Add(300);
			Integers.Add(400);

			// Vola sa EXTENSION METHOD.
			foreach(int Value in Integers.Filter(250))
			{
				Console.WriteLine($"FILTER - [{Value}] !");
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestLambdaExpressions()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			int[]												Array=new int[]{1,2,3,4,5,6,7,8,9,10};

			// !!! Pouzije sa LAMBDA EXPRESSION.
			foreach(int Value in Array.Where(P => P>5))
			{
				Console.WriteLine($"VALUE [{Value}] !");
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestTypeInference()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// !!! COMPILER si odvodi TYPE VARIABLE na zaklade inicializacnych VALUES.
			var													Object=new []{new CClass2("AAA",100),new CClass2("BBB",200),new CClass2("CCC",300)};

			foreach(CClass2 Value in Object)
			{
				Console.WriteLine($"VALUE - VALUE 1 [{Value.Value1}] VALUE 2 [{Value.Value2}] !");
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAnonymousTypes()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// !!! Definuje sa ANONYMOUS TYPE.
			var													Object1=new {Field1="AAA",Field2=100};

			Console.WriteLine($"OBJECT 1 - FIELD 1 [{Object1.Field1}] FIELD 2 [{Object1.Field2}] !");

			// !!! Definuje sa ANONYMOUS TYPE.
			var													Object2=new {Field1="BBB",Field2=200};

			Console.WriteLine($"OBJECT 2 - FIELD 1 [{Object2.Field1}] FIELD 2 [{Object2.Field2}] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// !!! Kedze instancie oboch OBJECTS obsahuju rovnake PROPERTY NAMES a PROPERTY TYPES, su priradene do JEDNEHO ANONYMOUS TYPE.
			if (Object1.GetType()==Object2.GetType())
			{
				Console.WriteLine("TYPES are EQUAL !");
			}
			else
			{
				Console.WriteLine("TYPES are DIFFERENT !");
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// !!! Definuje sa ANONYMOUS TYPE typu ARRAY.
			var													Array=new []{new {Field1="AAA",Field2=100},new {Field1="BBB",Field2=200},new {Field1="CCC",Field2=300}};

			foreach(var Value in Array)
			{
				Console.WriteLine($"ITEM - FIELD 1 [{Object2.Field1}] FIELD 2 [{Object2.Field2}] !");
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestInterfaceMembersImplementation()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			IPersonSource										PersonSource=new CPersonSource();

			Console.WriteLine("PERSONS:");

			foreach(CPerson Person in PersonSource.GetPersons())
			{
				Console.WriteLine($"\tID [{Person.ID}] FIRST NAME [{Person.FirstName}] LAST NAME [{Person.LastName}] AGE [{Person.Age}] SEX [{Person.Sex}] !");
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
			
			Console.WriteLine("MALES:");

			// !!! Vola sa INTERFACE DEFAULT METHOD.
			foreach(CPerson Person in PersonSource.GetMales())
			{
				Console.WriteLine($"\tID [{Person.ID}] FIRST NAME [{Person.FirstName}] LAST NAME [{Person.LastName}] AGE [{Person.Age}] SEX [{Person.Sex}] !");
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			Console.WriteLine("FEMALES:");

			// !!! Vola sa INTERFACE DEFAULT METHOD.
			foreach(CPerson Person in PersonSource.GetFemales())
			{
				Console.WriteLine($"\tID [{Person.ID}] FIRST NAME [{Person.FirstName}] LAST NAME [{Person.LastName}] AGE [{Person.Age}] SEX [{Person.Sex}] !");
			}

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static int SumChildTask(object Param)
		{
			int													To=(int) Param;

			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK STARTED CALCULATION !",Thread.CurrentThread.ManagedThreadId));

			int													Ret=0;
			
			for (int Index=0;Index<To;Index++)
			{
				Thread.Sleep(10);

				Ret++;
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK FINISHED CALCULATION !",Thread.CurrentThread.ManagedThreadId));

			return(Ret);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static int[] SumParentTask(object Param)
		{
			Console.WriteLine(string.Format("!!!!!!!!!! THREAD: [{0}] - PARENT TASK STARTED !",Thread.CurrentThread.ManagedThreadId));

			int[]												Results=new int[3];

			// !!! Pouzijem KLAUZURY na prenos RESULTS.
			Task<int>											ChildTask1=new Task<int>(() => Results[0]=SumChildTask(200),TaskCreationOptions.AttachedToParent);
			Task<int>											ChildTask2=new Task<int>(() => Results[1]=SumChildTask(300),TaskCreationOptions.AttachedToParent);
			Task<int>											ChildTask3=new Task<int>(() => Results[2]=SumChildTask(400),TaskCreationOptions.AttachedToParent);

			// Tento PARENT TASK spusti dalsie 3 CHILDREN TASKS.
			ChildTask1.Start();
			ChildTask2.Start();
			ChildTask3.Start();

			Console.WriteLine(string.Format("!!!!!!!!!! THREAD: [{0}] - PARENT TASK FINISHED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! Kedze PARENT TASK SKONCI OKAMZITE zatial pole Results je PRAZDNE a NAPLNI SA AZ PO VYKONANI VSETKYCH TASKS.
			return(Results);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void TestTask()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			// Vytvorim PARENT TASK, ktory SPUSTI 3 CHILD TASKS.
			Task<int[]>											ParentTask=new Task<int[]>(SumParentTask,null);

			Console.WriteLine(string.Format("THREAD: [{0}] - PARENT TASK CREATED !",Thread.CurrentThread.ManagedThreadId));

			ParentTask.Start();

			Console.WriteLine(string.Format("THREAD: [{0}] - PARENT TASK STARTED !",Thread.CurrentThread.ManagedThreadId));

			// !!!!! PARENT TASK skonci az ked skoncia VSETKY CHILD TASKS.
			ParentTask.Wait();

			int[]												Results=ParentTask.Result;

			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK 1 RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Results[0]));
			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK 2 RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Results[1]));
			Console.WriteLine(string.Format("THREAD: [{0}] - CHILD TASK 3 RESULT: [{1}] !",Thread.CurrentThread.ManagedThreadId,Results[2]));

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private async static Task TestAsynchronousSynchronization(int Index)
		{
			// !!!!! BEZ OHLADU na to ci SEMAPHORE ma namiesto INITIAL a MAX COUNT hodnotu 2 a viac, VZDY je prepusteny za OPERATOR AWAIT IBA 1 THREAD.
			await MSemaphoreSlimAsync.WaitAsync();

			Console.WriteLine(string.Format("THREAD [{0}] - TASK: [{1}] is INSIDE LOCK !",Thread.CurrentThread.ManagedThreadId,Index+1));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("THREAD [{0}] - TASK: [{1}] is GOING to LEAVE LOCK !",Thread.CurrentThread.ManagedThreadId,Index+1));

			MSemaphoreSlimAsync.Release();
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAsynchronousFunction()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			Console.WriteLine("TEST STARTED !");

			Task[]												Tasks=new Task[10];
			
			for (int Index=0;Index<Tasks.Length;Index++)
			{
				Tasks[Index]=TestAsynchronousSynchronization(Index);
			}

			Task.WaitAll(Tasks);

			Console.WriteLine("TEST FINISHED !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static string CreateTime()
		{
			DateTime											Time=DateTime.Now;
			string												TextTime=$"{Time.Hour.ToString("00")}:{Time.Minute.ToString("00")}:{Time.Second.ToString("00")}.{Time.Millisecond.ToString("000")}";

			return(TextTime);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Vytvori sa RESULT, ktory moze byt spracovavany ASYNCHRONNE.
		private static async IAsyncEnumerable<int> CreateResults()
		{
			for(int Index=0;Index<5;Index++)
			{
				int												Value=(Index+1);

				Console.WriteLine($"RECORD [{Value}] is PRODUCING at TIME [{CreateTime()}] in THREAD [{Thread.CurrentThread.ManagedThreadId}] !");

				await Task.Delay(1000);

				Console.WriteLine($"RECORD [{Value}] is PRODUCED at TIME [{CreateTime()}] in THREAD [{Thread.CurrentThread.ManagedThreadId}] !");

				yield return(Value);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async Task ProcessResults()
		{
			IAsyncEnumerable<int>								Results=CreateResults();

			await foreach(int Value in Results)
			{
				Console.WriteLine($"RECORD [{Value}] is CONSUMED at TIME [{CreateTime()}] in THREAD [{Thread.CurrentThread.ManagedThreadId}] !");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void TestAsynchronousEnumerable()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			Task												Results=ProcessResults();

			Results.Wait();

			Console.WriteLine("TEST COMPLETED !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void TestNameofOperator()
		{
			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));

			CClass1												Object=new CClass1();

			Console.WriteLine($"NAMEOF [{nameof(MSemaphoreSlimAsync)}] !");
			Console.WriteLine($"NAMEOF [{nameof(Object)}] !");
			Console.WriteLine($"NAMEOF [{nameof(Object.Value1)}] !");
			Console.WriteLine($"NAMEOF [{nameof(Object.Value2)}] !");

			// !!! OPERATOR [nameof()] umoznuje ziskat aj nazov METHOD.
			Console.WriteLine($"NAMEOF [{nameof(Object.GetValue1)}] !");
			Console.WriteLine($"NAMEOF [{nameof(CClass1)}] !");

			Console.WriteLine("".PadLeft(Console.WindowWidth-1,'-'));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//TestStringOperators();
			//TestAutomaticProperties();
			//TestStringInterpolation();
			//TestObjectInitializers();
			//TestArrayInitializers();
			//TestCollectionInitializers();
			//TestIndexerInitializers();
			//TestOperatorIs();
			//TestOperatorCaseWhen();
			//TestExtensionMethods();
			//TestLambdaExpressions();
			//TestTypeInference();
			//TestAnonymousTypes();
			//TestInterfaceMembersImplementation();
			//TestTask();
			//TestAsynchronousFunction();
			//TestAsynchronousEnumerable();
			TestNameofOperator();

			Console.ReadLine();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------