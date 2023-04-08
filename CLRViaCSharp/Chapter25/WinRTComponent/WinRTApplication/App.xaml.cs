using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
//-------------------------------------------------------------------------------------------------------
namespace WinRTApplication
{
//-------------------------------------------------------------------------------------------------------
    sealed partial class App : Application
    {
//-------------------------------------------------------------------------------------------------------
        public App()
        {
            this.InitializeComponent();
            this.Suspending+=OnSuspending;
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void OnSuspending(object Sender, SuspendingEventArgs E)
        {
            SuspendingDeferral									Deferral=E.SuspendingOperation.GetDeferral();
            
            Deferral.Complete();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        protected override void OnLaunched(LaunchActivatedEventArgs Args)
        {
            Frame												RootFrame=Window.Current.Content as Frame;

            if (RootFrame==null)
            {
                RootFrame=new Frame();

                if (Args.PreviousExecutionState==ApplicationExecutionState.Terminated)
                {
                }

                Window.Current.Content=RootFrame;
            }

            if (RootFrame.Content==null)
            {
                if (RootFrame.Navigate(typeof(MainPage),Args.Arguments)==false)
                {
                    throw(new Exception("Failed to create initial page !"));
                }
            }
            
            Window.Current.Activate();
        }
//-------------------------------------------------------------------------------------------------------
    }
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------