using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using WinRTComponent;
//-------------------------------------------------------------------------------------------------------
// !!!!! PROJECT reprezentuje [WINDOWS STORE APP], a preto pre PUBLIC TYPES sa NEVZTAHUJU obmedzenia WinRT TYPE SYSTEM.
//-------------------------------------------------------------------------------------------------------
namespace WinRTApplication
{
//-------------------------------------------------------------------------------------------------------
    public sealed partial class MainPage : Page
    {
//-------------------------------------------------------------------------------------------------------
        public MainPage()
        {
            this.InitializeComponent();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void PrintArray(string Prefix, int[] Array)
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat("[{0}] - {1} - [",DateTime.Now,Prefix);

			for(int Index=0;Index<Array.Length;Index++)
			{
				if (Index!=0)
				{
					SB.Append(",");
				}

				SB.Append(Array[Index]);
			}

			SB.AppendLine("] !");

			MLSTLog.Items.Add(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		private void PrintCollection(string Prefix, IEnumerable<int> Collection)
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat("[{0}] - {1} - [",DateTime.Now,Prefix);

			int													Counter=0;

			foreach(int Value in Collection)
			{
				if (Counter++!=0)
				{
					SB.Append(",");
				}

				SB.Append(Value);
			}

			SB.AppendLine("] !");

			MLSTLog.Items.Add(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		private void PrintCollection(string Prefix, IDictionary<int,int> Collection)
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat("[{0}] - {1} - [",DateTime.Now,Prefix);

			int													Counter=0;

			foreach(int Key in Collection.Keys)
			{
				if (Counter++!=0)
				{
					SB.Append(",");
				}

				SB.Append(Key);
				SB.Append(" ");
				SB.Append(Collection[Key]);
			}

			SB.AppendLine("] !");

			MLSTLog.Items.Add(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		private void PrintCollection(string Prefix, PropertySet Collection)
		{
			StringBuilder										SB=new StringBuilder();

			SB.AppendFormat("[{0}] - {1} - [",DateTime.Now,Prefix);

			int													Counter=0;

			foreach(string Key in Collection.Keys)
			{
				if (Counter++!=0)
				{
					SB.Append(",");
				}

				SB.Append(Key);
				SB.Append(" ");
				SB.Append(Collection[Key]);
			}

			SB.AppendLine("] !");

			MLSTLog.Items.Add(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestComponent_Click(object Sender, RoutedEventArgs E)
        {
			CName												Name=new CName("Timmy","Anderson",12);							
			string												Text=string.Format("[{0}] - {1} !",DateTime.Now,Name);

            MLSTLog.Items.Add(Text);
        }
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestException1_Click(object Sender, RoutedEventArgs E)
        {
			CExceptionClass										ExceptionClass=new CExceptionClass();

			try
			{
				int												Return=ExceptionClass.GenerateExcepion1(100);
				string											Text=string.Format("[{0}] - RETURN VALUE [{1}] !",DateTime.Now,Return);

				MLSTLog.Items.Add(Text);
			}
			catch(Exception Ex)
			{
				string											Text=string.Format("[{0}] - EXCEPTION [{1}] !",DateTime.Now,Ex);

				MLSTLog.Items.Add(Text);
			}

			try
			{
				int												Return=ExceptionClass.GenerateExcepion1(0);
				string											Text=string.Format("[{0}] - RETURN VALUE [{1}] !",DateTime.Now,Return);

				MLSTLog.Items.Add(Text);
			}
			catch(Exception Ex)
			{
				string											Text=string.Format("[{0}] - EXCEPTION [{1}] !",DateTime.Now,Ex);

				MLSTLog.Items.Add(Text);
			}
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestException2_Click(object Sender, RoutedEventArgs E)
        {
			CExceptionClass										ExceptionClass=new CExceptionClass();

			try
			{
				int												Return=ExceptionClass.GenerateExcepion2(100);
				string											Text=string.Format("[{0}] - RETURN VALUE [{1}] !",DateTime.Now,Return);

				MLSTLog.Items.Add(Text);
			}
			catch(Exception Ex)
			{
				string											Text=string.Format("[{0}] - EXCEPTION [{1}] !",DateTime.Now,Ex);

				MLSTLog.Items.Add(Text);
			}

			try
			{
				int												Return=ExceptionClass.GenerateExcepion2(0);
				string											Text=string.Format("[{0}] - RETURN VALUE [{1}] !",DateTime.Now,Return);

				MLSTLog.Items.Add(Text);
			}
			catch(Exception Ex)
			{
				string											Text=string.Format("[{0}] - EXCEPTION [{1}] !",DateTime.Now,Ex);

				MLSTLog.Items.Add(Text);
			}
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestException3_Click(object Sender, RoutedEventArgs E)
        {
			CExceptionClass										ExceptionClass=new CExceptionClass();

			try
			{
				ExceptionClass.GenerateExcepion3();

				string											Text=string.Format("[{0}] - METHOD PASSED !",DateTime.Now);

				MLSTLog.Items.Add(Text);
			}
			catch(Exception Ex)
			{
				string											Text=string.Format("[{0}] - EXCEPTION [{1}] !",DateTime.Now,Ex);

				MLSTLog.Items.Add(Text);
			}
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestString_Click(object Sender, RoutedEventArgs E)
        {
			CStringTest											StringTest=new CStringTest();

			StringTest.SetString("Timmy Anderson");

			{
				string											String=StringTest.GetString();
				string											Text=string.Format("[{0}] - STRING [{1}] !",DateTime.Now,String);

				MLSTLog.Items.Add(Text);
			}

			try
			{
				// !!! CLR UMOZNUJE prenasat do WinRT COMPONENTS aj NULL STRINGS.
				StringTest.SetString(null);

				string											String=StringTest.GetString();
				string											Text=string.Format("[{0}] - STRING [{1}] !",DateTime.Now,String);

				MLSTLog.Items.Add(Text);
			}
			catch(Exception Ex)
			{
				string											Text=string.Format("[{0}] - EXCEPTION [{1}] !",DateTime.Now,Ex);

				MLSTLog.Items.Add(Text);
			}
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestDisposable_Click(object Sender, RoutedEventArgs E)
        {
			using(CDisposable Disposable=new CDisposable(MLSTLog))
			{
				string											Text=string.Format("[{0}] - DISPOSABLE !",DateTime.Now);

				MLSTLog.Items.Add(Text);
			}
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestArray1_Click(object Sender, RoutedEventArgs E)
        {
			CArraysTest											ArraysTest=new CArraysTest(MLSTLog);
			int[]												TestArray=new int[]{11,22,33};

			PrintArray("BEFORE CALL",TestArray);

			ArraysTest.InArray(TestArray);

			PrintArray("AFTER CALL",TestArray);
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestArray2_Click(object Sender, RoutedEventArgs E)
        {
			CArraysTest											ArraysTest=new CArraysTest(MLSTLog);
			int[]												TestArray=new int[]{11,22,33};

			PrintArray("BEFORE CALL",TestArray);

			ArraysTest.OutArray(out TestArray);

			PrintArray("AFTER CALL",TestArray);
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestArray3_Click(object Sender, RoutedEventArgs E)
        {
			CArraysTest											ArraysTest=new CArraysTest(MLSTLog);
			int[]												TestArray=new int[]{11,22,33};

			PrintArray("BEFORE CALL",TestArray);

			TestArray=ArraysTest.ReturnArray();

			PrintArray("AFTER CALL",TestArray);
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestArray4_Click(object Sender, RoutedEventArgs E)
        {
			CArraysTest											ArraysTest=new CArraysTest(MLSTLog);
			int[]												TestArray=new int[]{11,22,33};

			PrintArray("BEFORE CALL",TestArray);

			// !!! METHOD interne MODIFIKUJE ARRAY. To sa sice v tomto pripade podarilo, ale vo vseobecnosti to NIE JE STANDARDNE a NEEXISTUJE ISTOTA, ze modifikacia ARRAY bude skutocne zrealizovana VZDY.
			ArraysTest.InOutArray(TestArray);

			PrintArray("AFTER CALL",TestArray);
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestCollection1_Click(object Sender, RoutedEventArgs E)
        {
			CCollectionTest										CollectionTest=new CCollectionTest(MLSTLog);
			List<int>											Collection=new List<int>();

			Collection.Add(1);
			Collection.Add(2);
			Collection.Add(3);

			PrintCollection("BEFORE CALL",Collection);

			CollectionTest.Collection1(Collection);

			PrintCollection("AFTER CALL",Collection);
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestCollection2_Click(object Sender, RoutedEventArgs E)
        {
			CCollectionTest										CollectionTest=new CCollectionTest(MLSTLog);
			List<int>											Collection=new List<int>();

			Collection.Add(1);
			Collection.Add(2);
			Collection.Add(3);

			PrintCollection("BEFORE CALL",Collection);

			CollectionTest.Collection2(Collection);

			PrintCollection("AFTER CALL",Collection);
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestCollection3_Click(object Sender, RoutedEventArgs E)
        {
			CCollectionTest										CollectionTest=new CCollectionTest(MLSTLog);
			Dictionary<int,int>									Collection=new Dictionary<int,int>();

			Collection.Add(1,1);
			Collection.Add(2,2);
			Collection.Add(3,3);

			PrintCollection("BEFORE CALL",Collection);

			CollectionTest.Collection3(Collection);

			PrintCollection("AFTER CALL",Collection);
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTTestCollection4_Click(object Sender, RoutedEventArgs E)
        {
			CCollectionTest										CollectionTest=new CCollectionTest(MLSTLog);
			// WinRT COLLECTION.
			PropertySet											Collection=new PropertySet();

			Collection.Add("Timmy Anderson",12);
			Collection.Add("Atreyu",12);

			PrintCollection("BEFORE CALL",Collection);

			CollectionTest.Collection4(Collection);

			PrintCollection("AFTER CALL",Collection);
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTAsynchronousOperationSuccess_Click(object Sender, RoutedEventArgs E)
        {
			CAsynchronousOperations								AsynchronousOperations=new CAsynchronousOperations(MLSTLog);

			AsynchronousOperations.CreateFile();
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTAsynchronousOperationFailure_Click(object Sender, RoutedEventArgs E)
        {
			CAsynchronousOperations								AsynchronousOperations=new CAsynchronousOperations(MLSTLog);

			AsynchronousOperations.CreateFileOrFailIfFileExists();
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTAsynchronousOperationCancel_Click(object Sender, RoutedEventArgs E)
        {
			CAsynchronousOperations								AsynchronousOperations=new CAsynchronousOperations(MLSTLog);

			AsynchronousOperations.CreateFileWithCancellation();
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTAsynchronousOperationAwaitSuccess_Click(object Sender, RoutedEventArgs E)
        {
			CAsynchronousOperations								AsynchronousOperations=new CAsynchronousOperations(MLSTLog);

			AsynchronousOperations.CreateFileAwait();
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTAsynchronousOperationAwaitFailure_Click(object Sender, RoutedEventArgs E)
        {
			CAsynchronousOperations								AsynchronousOperations=new CAsynchronousOperations(MLSTLog);

			AsynchronousOperations.CreateFileOrFailIfFileExistsAwait();
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTAsynchronousOperationAwaitCancel_Click(object Sender, RoutedEventArgs E)
        {
			CAsynchronousOperations								AsynchronousOperations=new CAsynchronousOperations(MLSTLog);

			AsynchronousOperations.CreateFileWithCancellationAwait();
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTStreamsTest1_Click(object Sender, RoutedEventArgs E)
        {
			CStreamsClass										StreamsClass=new CStreamsClass(MLSTLog);

			StreamsClass.StreamsTest1();
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTStreamsTest2_Click(object Sender, RoutedEventArgs E)
        {
			CStreamsClass										StreamsClass=new CStreamsClass(MLSTLog);

			StreamsClass.StreamsTest2();
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTStreamsTest3_Click(object Sender, RoutedEventArgs E)
        {
			CStreamsClass										StreamsClass=new CStreamsClass(MLSTLog);

			StreamsClass.StreamsTest3();
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTStreamsTest4_Click(object Sender, RoutedEventArgs E)
        {
			CStreamsClass										StreamsClass=new CStreamsClass(MLSTLog);

			StreamsClass.StreamsTest4();
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTBufferTest_Click(object Sender, RoutedEventArgs E)
        {
			CBufferClass										BufferClass=new CBufferClass(MLSTLog);

			BufferClass.BufferTest();
		}
//-------------------------------------------------------------------------------------------------------
        private void MBUTClear_Click(object Sender, RoutedEventArgs E)
        {
            MLSTLog.Items.Clear();
        }
//-------------------------------------------------------------------------------------------------------
        private void MBUTExit_Click(object Sender, RoutedEventArgs E)
        {
            Application.Current.Exit();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        protected override void OnNavigatedTo(NavigationEventArgs E)
        {
        }
//-------------------------------------------------------------------------------------------------------
    }
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------