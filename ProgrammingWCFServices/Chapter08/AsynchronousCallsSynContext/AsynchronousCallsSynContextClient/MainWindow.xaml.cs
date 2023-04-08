using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace AsynchronousCallsSynContextClient
{
//-------------------------------------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//-------------------------------------------------------------------------------------------------------
		private MyProxy.MyAsyncServiceClient					MProxy;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public MainWindow()
		{
			// !!!!! Tu uz je vytvoreny SYNCHRONIZATION CONTEXT, teda Thread.CurrentContext UZ NIE JE NULL.
			// !!!!! Je to preto, lebo SYNCHRONIZATION CONTEXT je vytvoreny UZ V KONSTUKTORE PRVEHO CONTROL OBJEKTU, ktory je vo WPF aplikacii vytvoreny.

			InitializeComponent();

			MessageBox.Show("Press OK if HOST is started !");

			try
			{
				MProxy=new AsynchronousCallsSynContextClient.MyProxy.MyAsyncServiceClient();

				// !!! Prihlasim sa na odber Eventu volaneho pri skonceni ASYCHRONNEHO VOLANIA OPERACIE.
				MProxy.ToUpperCompleted+=new EventHandler<AsynchronousCallsSynContextClient.MyProxy.ToUpperCompletedEventArgs>(MProxy_ToUpperCompleted);

				MProxy.Open();
			}
			catch(Exception E)
			{
				MessageBox.Show("EXCEPTION: {0} !",E.Message);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private void MProxy_ToUpperCompleted(object Sender, AsynchronousCallsSynContextClient.MyProxy.ToUpperCompletedEventArgs E)
		{
			// !!!!! Tento kod je volany vdaka SynchronizationContext v TOM ISTOM THREAD ako GUI a preto mozem PRIAMO UPDATEOVAT GUI.
			// Ziskam vysledok volania operacie Service.
			MLABResult.Content=E.Result;
		}
//-------------------------------------------------------------------------------------------------------
		private void MBUTSynchronousCall_Click(object Sender, RoutedEventArgs E)
		{
			try
			{
				string			Ret=MProxy.ToUpper(MTXTText.Text);

				MLABResult.Content=Ret;
			}
			catch(Exception Ex)
			{
				MessageBox.Show("EXCEPTION: {0} !",Ex.Message);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private void MBUTAsynchronousCall_Click(object Sender, RoutedEventArgs E)
		{
			try
			{
				// !!! Volam ASYCNHRONNE DANU OPEACIU.
				// !!!!! PRAVE TERAZ SA NACITA AKTUALNY SYCNHRONIZACNY CONTEXT, KTORY JE PRIRADENY VOLAJUCEMU (GUI) THREADU.
				MProxy.ToUpperAsync(MTXTText.Text);
			}
			catch(Exception Ex)
			{
				MessageBox.Show("EXCEPTION: {0} !",Ex.Message);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private void Window_Closed(object Sender, EventArgs E)
		{
			try
			{
				// Uzatvorim Proxy.
				MProxy.Close();
			}
			catch(Exception Ex)
			{
				MessageBox.Show("EXCEPTION: {0} !",Ex.Message);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------