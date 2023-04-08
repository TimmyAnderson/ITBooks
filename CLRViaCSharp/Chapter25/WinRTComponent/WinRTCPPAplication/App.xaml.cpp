#include "pch.h"
#include "MainPage.xaml.h"
//-------------------------------------------------------------------------------------------------------
using namespace WinRTCPPAplication;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
//-------------------------------------------------------------------------------------------------------
App::App()
{
	InitializeComponent();
	Suspending+=ref new SuspendingEventHandler(this,&App::OnSuspending);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void App::OnSuspending(Object^ Sender, SuspendingEventArgs^ E)
{
	(void) Sender;
	(void) E;
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ Args)
{
	Frame^														RootFrame=dynamic_cast<Frame^>(Window::Current->Content);

	if (RootFrame==nullptr)
	{
		RootFrame=ref new Frame();

		if (RootFrame->Content==nullptr)
		{
			if (RootFrame->Navigate(TypeName(MainPage::typeid),Args->Arguments)==false)
			{
				throw(ref new FailureException("Failed to create initial page !"));
			}
		}

		Window::Current->Content=RootFrame;
		Window::Current->Activate();
	}
	else
	{
		if (RootFrame->Content==nullptr)
		{
			if (RootFrame->Navigate(TypeName(MainPage::typeid),Args->Arguments)==false)
			{
				throw(ref new FailureException("Failed to create initial page !"));
			}
		}

		Window::Current->Activate();
	}
}
//-------------------------------------------------------------------------------------------------------