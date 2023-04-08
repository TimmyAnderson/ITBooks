#pragma once
//-------------------------------------------------------------------------------------------------------
#include "App.g.h"
//-------------------------------------------------------------------------------------------------------
namespace WinRTCPPAplication
{
//-------------------------------------------------------------------------------------------------------
	ref class App sealed
	{
		private:
			void OnSuspending(Platform::Object^ Sender, Windows::ApplicationModel::SuspendingEventArgs^ E);

		public:
			virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ Args) override;

		public:
			App();
	};
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------