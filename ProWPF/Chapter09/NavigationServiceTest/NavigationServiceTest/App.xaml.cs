using System;
using System.Windows;
using System.Data;
using System.Xml;
using System.Diagnostics;
using System.Configuration;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace NavigationServiceTest
{
//------------------------------------------------------------------------
	public partial class App:System.Windows.Application
	{
		public App()
		{
			Navigating+=new NavigatingCancelEventHandler(App_Navigating);
			Navigated+=new NavigatedEventHandler(App_Navigated);
			NavigationProgress+=new NavigationProgressEventHandler(App_NavigationProgress);
			LoadCompleted+=new LoadCompletedEventHandler(App_LoadCompleted);
			FragmentNavigation+=new FragmentNavigationEventHandler(App_FragmentNavigation);
			NavigationStopped+=new NavigationStoppedEventHandler(App_NavigationStopped);
			NavigationFailed+=new NavigationFailedEventHandler(App_NavigationFailed);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void App_Navigating(object Sender, NavigatingCancelEventArgs E)
		{
			Debug.WriteLine(string.Format("Navigated - IsNavigationInitiator: {0}, ExtraData: {1}, Uri: {2}, NavigationMode: {3}, ContentStateToSave: {4}, Cancel: {5} !",E.IsNavigationInitiator,E.ExtraData,E.Uri,E.NavigationMode,E.ContentStateToSave,E.Cancel));
		}
//------------------------------------------------------------------------
		private void App_Navigated(object Sender, NavigationEventArgs E)
		{
			Debug.WriteLine(string.Format("Navigated - IsNavigationInitiator: {0}, ExtraData: {1}, Uri: {2} !",E.IsNavigationInitiator,E.ExtraData,E.Uri));
		}
//------------------------------------------------------------------------
		private void App_NavigationProgress(object Sender, NavigationProgressEventArgs E)
		{
			Debug.WriteLine(string.Format("NavigationProgress - BytesRead: {0}, MaxBytes: {1}, Uri: {2} !",E.BytesRead,E.MaxBytes,E.Uri));
		}
//------------------------------------------------------------------------
		private void App_LoadCompleted(object Sender, NavigationEventArgs E)
		{
			Debug.WriteLine(string.Format("LoadCompleted - IsNavigationInitiator: {0}, ExtraData: {1}, Uri: {2} !",E.IsNavigationInitiator,E.ExtraData,E.Uri));
		}
//------------------------------------------------------------------------
		private void App_FragmentNavigation(object Sender, FragmentNavigationEventArgs E)
		{
			Debug.WriteLine(string.Format("FragmentNavigation - Fragment: {0} !",E.Fragment));
		}
//------------------------------------------------------------------------
		private void App_NavigationStopped(object Sender, NavigationEventArgs E)
		{
			Debug.WriteLine(string.Format("NavigationStopped - IsNavigationInitiator: {0}, ExtraData: {1}, Uri: {2} !",E.IsNavigationInitiator,E.ExtraData,E.Uri));
		}
//------------------------------------------------------------------------
		private void App_NavigationFailed(object Sender, NavigationFailedEventArgs E)
		{
			Debug.WriteLine(string.Format("NavigationFailed - Exception: {0}, ExtraData: {1}, Uri: {2} !",E.Exception,E.ExtraData,E.Uri));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------