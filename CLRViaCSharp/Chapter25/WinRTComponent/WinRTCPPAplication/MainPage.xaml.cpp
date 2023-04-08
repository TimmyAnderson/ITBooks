#include "pch.h"
#include "MainPage.xaml.h"
//-------------------------------------------------------------------------------------------------------
using namespace WinRTCPPAplication;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Globalization;
using namespace Windows::Globalization::DateTimeFormatting;
using namespace WinRTComponent;
//-------------------------------------------------------------------------------------------------------
MainPage::MainPage()
{
	InitializeComponent();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void MainPage::PrintArray(String^ Prefix, const Platform::Array<int,1U>^ Array)
{
	Calendar													MyCalendar;

	MyCalendar.SetToNow();

	DateTime													Time=MyCalendar.GetDateTime();
	DateTimeFormatter											Formatter("hour minute second");
	
	String^														Temp1=String::Concat(Prefix," - [");
	String^														Temp2=String::Concat(Temp1,Formatter.Format(Time));
	String^														Temp3=String::Concat(Temp2,"] - [");
	String^														ArrayText="";
	
	for(unsigned int Index=0;Index<Array->Length;Index++)
	{
		if (Index!=0)
		{
			ArrayText=String::Concat(ArrayText,",");
		}

		ArrayText=String::Concat(ArrayText,Array[Index]);
	}

	String^														Temp4=String::Concat(Temp3,ArrayText);
	String^														Text=String::Concat(Temp4,"] !");

	MLSTLog->Items->Append(Text);
}
//-------------------------------------------------------------------------------------------------------
void MainPage::PrintCollection(String^ Prefix, Vector<int>^ Collection)
{
	Calendar													MyCalendar;

	MyCalendar.SetToNow();

	DateTime													Time=MyCalendar.GetDateTime();
	DateTimeFormatter											Formatter("hour minute second");
	
	String^														Temp1=String::Concat(Prefix," - [");
	String^														Temp2=String::Concat(Temp1,Formatter.Format(Time));
	String^														Temp3=String::Concat(Temp2,"] - [");
	String^														ArrayText="";
	
	for(unsigned int Index=0;Index<Collection->Size;Index++)
	{
		if (Index!=0)
		{
			ArrayText=String::Concat(ArrayText,",");
		}

		ArrayText=String::Concat(ArrayText,Collection->GetAt(Index));
	}

	String^														Temp4=String::Concat(Temp3,ArrayText);
	String^														Text=String::Concat(Temp4,"] !");

	MLSTLog->Items->Append(Text);
}
//-------------------------------------------------------------------------------------------------------
void MainPage::PrintCollection(String^ Prefix, Map<int,int>^ Collection)
{
	Calendar													MyCalendar;

	MyCalendar.SetToNow();

	DateTime													Time=MyCalendar.GetDateTime();
	DateTimeFormatter											Formatter("hour minute second");
	
	String^														Temp1=String::Concat(Prefix," - [");
	String^														Temp2=String::Concat(Temp1,Formatter.Format(Time));
	String^														Temp3=String::Concat(Temp2,"] - [");
	String^														ArrayText="";

	IIterator<IKeyValuePair<int,int>^>^							CollectionIterator=Collection->First();

	for(unsigned int Index=0;Index<Collection->Size;Index++)
	{
		if (Index!=0)
		{
			ArrayText=String::Concat(ArrayText,",");
		}
		
		ArrayText=String::Concat(ArrayText,CollectionIterator->Current->Key);
		ArrayText=String::Concat(ArrayText," ");
		ArrayText=String::Concat(ArrayText,CollectionIterator->Current->Value);

		CollectionIterator->MoveNext();
	}

	String^														Temp4=String::Concat(Temp3,ArrayText);
	String^														Text=String::Concat(Temp4,"] !");

	MLSTLog->Items->Append(Text);
}
//-------------------------------------------------------------------------------------------------------
void MainPage::PrintCollection(String^ Prefix, PropertySet^ Collection)
{
	Calendar													MyCalendar;

	MyCalendar.SetToNow();

	DateTime													Time=MyCalendar.GetDateTime();
	DateTimeFormatter											Formatter("hour minute second");
	
	String^														Temp1=String::Concat(Prefix," - [");
	String^														Temp2=String::Concat(Temp1,Formatter.Format(Time));
	String^														Temp3=String::Concat(Temp2,"] - [");
	String^														ArrayText="";

	IIterator<IKeyValuePair<String^,Object^>^>^					CollectionIterator=Collection->First();

	for(unsigned int Index=0;Index<Collection->Size;Index++)
	{
		if (Index!=0)
		{
			ArrayText=String::Concat(ArrayText,",");
		}
		
		ArrayText=String::Concat(ArrayText,CollectionIterator->Current->Key);
		ArrayText=String::Concat(ArrayText," ");
		ArrayText=String::Concat(ArrayText,CollectionIterator->Current->Value);

		CollectionIterator->MoveNext();
	}

	String^														Temp4=String::Concat(Temp3,ArrayText);
	String^														Text=String::Concat(Temp4,"] !");

	MLSTLog->Items->Append(Text);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestComponent_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	Calendar													MyCalendar;

	MyCalendar.SetToNow();

	DateTime													Time=MyCalendar.GetDateTime();
	DateTimeFormatter											Formatter("hour minute second");
	CName														Name("Timmy","Anderson",12);
	String^														Temp1="[";
	String^														Temp2=String::Concat(Temp1,Formatter.Format(Time));
	String^														Temp3=String::Concat(Temp2,"] - ");
	String^														Temp4=String::Concat(Temp3,Name.ToString());
	String^														Text=String::Concat(Temp4," !");

	MLSTLog->Items->Append(Text);
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestException1_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CExceptionClass												ExceptionClass;
	Calendar													MyCalendar;

	MyCalendar.SetToNow();

	DateTime													Time=MyCalendar.GetDateTime();
	DateTimeFormatter											Formatter("hour minute second");
	
	try
	{
		int														Return=ExceptionClass.GenerateExcepion1(100);
		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - RETURN VALUE - [");
		String^													Temp4=String::Concat(Temp3,Return);
		String^													Text=String::Concat(Temp4,"] !");

		MLSTLog->Items->Append(Text);
	}
	catch(Exception^ Ex)
	{
		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - EXCEPTION - [");
		String^													Temp4=String::Concat(Temp3,Ex->Message);
		String^													Temp5=String::Concat(Temp4,"] - HRESULT - [");
		String^													Temp6=String::Concat(Temp5,Ex->HResult);
		String^													Text=String::Concat(Temp6,"] !");

		MLSTLog->Items->Append(Text);
	}

	try
	{
		int														Return=ExceptionClass.GenerateExcepion1(0);
		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - RETURN VALUE - [");
		String^													Temp4=String::Concat(Temp3,Return);
		String^													Text=String::Concat(Temp4,"] !");

		MLSTLog->Items->Append(Text);
	}
	catch(Exception^ Ex)
	{
		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - EXCEPTION - [");
		String^													Temp4=String::Concat(Temp3,Ex->Message);
		String^													Temp5=String::Concat(Temp4,"] - HRESULT - [");
		String^													Temp6=String::Concat(Temp5,Ex->HResult);
		String^													Text=String::Concat(Temp6,"] !");

		MLSTLog->Items->Append(Text);
	}
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestException2_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CExceptionClass												ExceptionClass;
	Calendar													MyCalendar;

	MyCalendar.SetToNow();

	DateTime													Time=MyCalendar.GetDateTime();
	DateTimeFormatter											Formatter("hour minute second");

	try
	{
		int														Return=ExceptionClass.GenerateExcepion2(100);
		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - RETURN VALUE - [");
		String^													Temp4=String::Concat(Temp3,Return);
		String^													Text=String::Concat(Temp4,"] !");

		MLSTLog->Items->Append(Text);
	}
	catch(Exception^ Ex)
	{
		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - EXCEPTION - [");
		String^													Temp4=String::Concat(Temp3,Ex->Message);
		String^													Temp5=String::Concat(Temp4,"] - HRESULT - [");
		String^													Temp6=String::Concat(Temp5,Ex->HResult);
		String^													Text=String::Concat(Temp6,"] !");

		MLSTLog->Items->Append(Text);
	}

	try
	{
		int														Return=ExceptionClass.GenerateExcepion2(0);
		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - RETURN VALUE - [");
		String^													Temp4=String::Concat(Temp3,Return);
		String^													Text=String::Concat(Temp4,"] !");

		MLSTLog->Items->Append(Text);
	}
	catch(Exception^ Ex)
	{
		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - EXCEPTION - [");
		String^													Temp4=String::Concat(Temp3,Ex->Message);
		String^													Temp5=String::Concat(Temp4,"] - HRESULT - [");
		String^													Temp6=String::Concat(Temp5,Ex->HResult);
		String^													Text=String::Concat(Temp6,"] !");

		MLSTLog->Items->Append(Text);
	}
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestException3_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CExceptionClass												ExceptionClass;
	Calendar													MyCalendar;

	MyCalendar.SetToNow();

	DateTime													Time=MyCalendar.GetDateTime();
	DateTimeFormatter											Formatter("hour minute second");

	try
	{
		ExceptionClass.GenerateExcepion3();

		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Text=String::Concat(Temp2,"] - METHOD PASSED !");

		MLSTLog->Items->Append(Text);
	}
	catch(Exception^ Ex)
	{
		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - EXCEPTION - [");
		String^													Temp4=String::Concat(Temp3,Ex->Message);
		String^													Temp5=String::Concat(Temp4,"] - HRESULT - [");
		String^													Temp6=String::Concat(Temp5,Ex->HResult);
		String^													Text=String::Concat(Temp6,"] !");

		MLSTLog->Items->Append(Text);
	}
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestString_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CStringTest													StringTest;
	Calendar													MyCalendar;

	MyCalendar.SetToNow();

	DateTime													Time=MyCalendar.GetDateTime();
	DateTimeFormatter											Formatter("hour minute second");

	{
		StringTest.SetString("Timmy Anderson");

		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - STRING [");
		String^													Temp4=String::Concat(Temp3,StringTest.GetString());
		String^													Text=String::Concat(Temp4,"] !");

		MLSTLog->Items->Append(Text);
	}

	try
	{
		// !!! Aj ked NULL STRING by WinRT COMPONENTS NEMALI AKCEPTOVAT, program NEHODIL EXCEPTION.
		StringTest.SetString(nullptr);

		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - STRING [");
		String^													Temp4=String::Concat(Temp3,StringTest.GetString());
		String^													Text=String::Concat(Temp4,"] !");

		MLSTLog->Items->Append(Text);
	}
	catch(Exception^ Ex)
	{
		String^													Temp1="[";
		String^													Temp2=String::Concat(Temp1,Formatter.Format(Time));
		String^													Temp3=String::Concat(Temp2,"] - EXCEPTION - [");
		String^													Temp4=String::Concat(Temp3,Ex->Message);
		String^													Temp5=String::Concat(Temp4,"] - HRESULT - [");
		String^													Temp6=String::Concat(Temp5,Ex->HResult);
		String^													Text=String::Concat(Temp6,"] !");

		MLSTLog->Items->Append(Text);
	}
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestDisposable1_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CDisposable													Disposable(MLSTLog);
	CStringTest													StringTest;
	Calendar													MyCalendar;

	MyCalendar.SetToNow();

	DateTime													Time=MyCalendar.GetDateTime();
	DateTimeFormatter											Formatter("hour minute second");

	String^														Temp1="[";
	String^														Temp2=String::Concat(Temp1,Formatter.Format(Time));
	String^														Text=String::Concat(Temp2,"] - CLOSABLE CREATED !");

	MLSTLog->Items->Append(Text);

	// !!! Toto COMPILER oznaci za ERROR, pretoze CDisposable, aj ked implementuje IDisposable, tak v skutocnosti je IDisposable MAPPED na IClosable.
	//Disposable.Dispose();

	// !!! Aj toto COMPILER oznaci za ERROR.
	//Disposable.Close();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestDisposable2_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CDisposable^												Disposable=ref new CDisposable(MLSTLog);
	CStringTest													StringTest;
	Calendar													MyCalendar;

	MyCalendar.SetToNow();

	DateTime													Time=MyCalendar.GetDateTime();
	DateTimeFormatter											Formatter("hour minute second");

	String^														Temp1="[";
	String^														Temp2=String::Concat(Temp1,Formatter.Format(Time));
	String^														Text=String::Concat(Temp2,"] - CLOSABLE CREATED !");

	MLSTLog->Items->Append(Text);

	// !!! Toto COMPILER oznaci za ERROR, pretoze CDisposable, aj ked implementuje IDisposable, tak v skutocnosti je IDisposable MAPPED na IClosable.
	//Disposable->Dispose();

	// !!! Aj toto COMPILER oznaci za ERROR.
	//Disposable->Close();

	// ????? PROGRAM SPADNE.
	//delete(Disposable);

	// ????? METHOD IDisposable.Dispose() sa NEZAVOLA.
	Disposable=nullptr;
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestArray1_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CArraysTest													ArraysTest(MLSTLog);
	int															Data[]={11,22,33};
	Array<int,1U>												TestArray(Data,3);
	
	PrintArray("BEFORE ARRAY",%TestArray);

	ArraysTest.InArray(%TestArray);

	PrintArray("AFTER ARRAY",%TestArray);
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestArray2_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CArraysTest													ArraysTest(MLSTLog);
	int															Data[]={11,22,33};
	Array<int,1U>^												TestArray=ref new Array<int,1U>(Data,3);
	
	PrintArray("BEFORE ARRAY",TestArray);

	ArraysTest.OutArray(&TestArray);

	PrintArray("AFTER ARRAY",TestArray);

	TestArray=nullptr;
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestArray3_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CArraysTest													ArraysTest(MLSTLog);
	int															Data[]={11,22,33};
	Array<int,1U>^												TestArray=ref new Array<int,1U>(Data,3);
	
	PrintArray("BEFORE ARRAY",TestArray);

	TestArray=ArraysTest.ReturnArray();

	PrintArray("AFTER ARRAY",TestArray);

	TestArray=nullptr;
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestArray4_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CArraysTest													ArraysTest(MLSTLog);
	int															Data[]={11,22,33};
	Array<int,1U>												TestArray(Data,3);
	
	PrintArray("BEFORE ARRAY",%TestArray);

	// !!!!! METHOD interne MODIFIKUJE ARRAY. Tato modifikacia sa vsak NEPRENESIE do C++ CODE.
	ArraysTest.InOutArray(%TestArray);

	PrintArray("AFTER ARRAY",%TestArray);
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestCollection1_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CCollectionTest												CollectionTest(MLSTLog);
	Vector<int>													Collection;

	Collection.Append(1);
	Collection.Append(2);
	Collection.Append(3);

	PrintCollection("BEFORE CALL",%Collection);

	CollectionTest.Collection1(%Collection);

	PrintCollection("AFTER CALL",%Collection);
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestCollection2_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CCollectionTest												CollectionTest(MLSTLog);
	Vector<int>													Collection;

	Collection.Append(1);
	Collection.Append(2);
	Collection.Append(3);

	PrintCollection("BEFORE CALL",%Collection);

	CollectionTest.Collection2(%Collection);

	PrintCollection("AFTER CALL",%Collection);
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestCollection3_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CCollectionTest												CollectionTest(MLSTLog);
	Map<int,int>												Collection;

	Collection.Insert(1,1);
	Collection.Insert(2,2);
	Collection.Insert(3,3);

	PrintCollection("BEFORE CALL",%Collection);

	CollectionTest.Collection3(%Collection);

	PrintCollection("AFTER CALL",%Collection);
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTTestCollection4_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CCollectionTest												CollectionTest(MLSTLog);
	PropertySet													Collection;

	Collection.Insert("Timmy Anderson",12);
	Collection.Insert("Atreyu",12);

	PrintCollection("BEFORE CALL",%Collection);

	CollectionTest.Collection4(%Collection);

	PrintCollection("AFTER CALL",%Collection);
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTAsynchronousOperationSuccess_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CAsynchronousOperations										AsynchronousOperations(MLSTLog);
	
	AsynchronousOperations.CreateFile();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTAsynchronousOperationFailure_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CAsynchronousOperations										AsynchronousOperations(MLSTLog);
	
	AsynchronousOperations.CreateFileOrFailIfFileExists();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTAsynchronousOperationCancel_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CAsynchronousOperations										AsynchronousOperations(MLSTLog);
	
	AsynchronousOperations.CreateFileWithCancellation();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTAsynchronousOperationAwaitSuccess_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CAsynchronousOperations										AsynchronousOperations(MLSTLog);
	
	AsynchronousOperations.CreateFileAwait();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTAsynchronousOperationAwaitFailure_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CAsynchronousOperations										AsynchronousOperations(MLSTLog);
	
	AsynchronousOperations.CreateFileOrFailIfFileExistsAwait();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTAsynchronousOperationAwaitCancel_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CAsynchronousOperations										AsynchronousOperations(MLSTLog);
	
	AsynchronousOperations.CreateFileWithCancellationAwait();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTStreamsTest1_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CStreamsClass												StreamsClass(MLSTLog);

	StreamsClass.StreamsTest1();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTStreamsTest2_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CStreamsClass												StreamsClass(MLSTLog);

	StreamsClass.StreamsTest2();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTStreamsTest3_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CStreamsClass												StreamsClass(MLSTLog);

	StreamsClass.StreamsTest3();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTStreamsTest4_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
	CStreamsClass												StreamsClass(MLSTLog);

	StreamsClass.StreamsTest4();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTClear_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
    MLSTLog->Items->Clear();
}
//-------------------------------------------------------------------------------------------------------
void MainPage::MBUTExit_Click(Platform::Object^ Sender, RoutedEventArgs^ E)
{
    Application::Current->Exit();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! PARAMETER sa MUSI volat 'e' a NIE 'E', kedze BASE METHOD ma PARAMETER pomenovany ako 'e'.
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;
}
//-------------------------------------------------------------------------------------------------------