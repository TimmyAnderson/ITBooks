#pragma once
//-------------------------------------------------------------------------------------------------------
#include "MainPage.g.h"
//-------------------------------------------------------------------------------------------------------
namespace WinRTCPPAplication
{
//-------------------------------------------------------------------------------------------------------
	public ref class MainPage sealed
	{
		private:
			void PrintArray(Platform::String^ Prefix, const Platform::Array<int,1U>^ Array);
			void PrintCollection(Platform::String^ Prefix, Platform::Collections::Vector<int>^ Collection);
			void PrintCollection(Platform::String^ Prefix, Platform::Collections::Map<int,int>^ Collection);
			void PrintCollection(Platform::String^ Prefix, Windows::Foundation::Collections::PropertySet^ Collection);

		private:
			void MBUTTestComponent_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestException1_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestException2_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestException3_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestString_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestDisposable1_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestDisposable2_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestArray1_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestArray2_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestArray3_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestArray4_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestCollection1_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestCollection2_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestCollection3_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTTestCollection4_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTAsynchronousOperationSuccess_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTAsynchronousOperationFailure_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTAsynchronousOperationCancel_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTAsynchronousOperationAwaitSuccess_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTAsynchronousOperationAwaitFailure_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTAsynchronousOperationAwaitCancel_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTStreamsTest1_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTStreamsTest2_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTStreamsTest3_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
			void MBUTStreamsTest4_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);

		private:
	        void MBUTClear_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);
		    void MBUTExit_Click(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ E);

		protected:
			// !!!!! PARAMETER sa MUSI volat 'e' a NIE 'E', kedze BASE METHOD ma PARAMETER pomenovany ako 'e'.
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

		public:
			MainPage();
	};
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------