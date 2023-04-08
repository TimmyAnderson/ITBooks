using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Threading;
using System.Windows.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje multithreading vo WPF.
// !!! 2. Dialog MOZEM mat spusteny v inom threade ALE MUSI TENTO THREAD BYT STA.
// !!!!! 3. Ak chcem z ineho threadu pristupovat ku GUI musim pouzit property Dispatcher a jeho metodu Invoke(), alebo BeginInvoke().
// !!!!! 4. Rozdiel medzi Invoke() a BeginInvoke() je v tom, ze Invoke() sa vykonava SYNCHORNNE a skonci, ked sa skonci vykonavnie metody delegatu, kde BeginInvoke() je zas ASYNCHRONNOU metodu a skonci sa okamzite zatial co telo metody sa vykonava paralelne.
// !!! 5. Invoke() vracia hodnotu, ktoru vrati delegat.
// !!! 6. BeginInvoke() vracia objekt typu DispatcherOperation, ktorym mozem sledovat priebeh ASYNCHRONNEJ operacie, zistit jej vysledok (hodnotu, ktoru vrati delegat) ci vykonat JEJ CANCEL.
//------------------------------------------------------------------------
namespace DispatcherAndThreadingTest
{
//------------------------------------------------------------------------
	public delegate object DMyCallCodeFromSecondThread(object Value);
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		private int					MCounter1=0;
		private int					MCounter2=0;
		private int					MCounter3=0;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void ThreadMethodCreateDialog(object Value)
		{
			MyCustomDialog			MCD=new MyCustomDialog(string.Format("Window: {0}",Value.ToString()));

			MCD.ShowDialog();
		}
//------------------------------------------------------------------------
		private void ThreadMethodSetTextSynchronous(object Control)
		{
			MainWindow		Win=(MainWindow) Control;

			Debug.WriteLine("!!! ThreadMethodSetTextSynchronous 111 !");

			// !!! Pouzijem Dispatcher na vyvolanie kodu z ineho threadu.
			// !!! Pouzivam Invoke(), ktora skonci az ked skonci kod v skundarnom threade.
			object			Ret=Win.Dispatcher.Invoke(DispatcherPriority.Normal,new DMyCallCodeFromSecondThread(Win.IncrementLabelFromSecondaryThread1),Win.MCounter2);

			Debug.WriteLine(string.Format("!!! ThreadMethodSetTextSynchronous RETURN: {0} !",Ret.ToString()));
			Debug.WriteLine("!!! ThreadMethodSetTextSynchronous 222 !");
		}
//------------------------------------------------------------------------
		private void ThreadMethodSetTextAsynchronous(object Control)
		{
			MainWindow				Win=(MainWindow) Control;

			Debug.WriteLine("!!! ThreadMethodSetTextAsynchronous 111 !");

			// !!! Pouzijem Dispatcher na vyvolanie kodu z ineho threadu.
			// !!! Pouzivam BeginInvoke(), ktora skonci OKAMZITE.
			DispatcherOperation		DO=Win.Dispatcher.BeginInvoke(DispatcherPriority.Normal,new DMyCallCodeFromSecondThread(Win.IncrementLabelFromSecondaryThread2),Win.MCounter3);

			DO.Completed+=new EventHandler(DO_Completed);

			while(DO.Status!=DispatcherOperationStatus.Completed)
			{
				Debug.WriteLine(string.Format("!!! ThreadMethodSetTextAsynchronous DO STAUTS: {0} !",DO.Status));
				Thread.Sleep(500);
			}

			object					Ret=DO.Result;

			Debug.WriteLine(string.Format("!!! ThreadMethodSetTextAsynchronous RETURN: {0} !",Ret.ToString()));
			Debug.WriteLine("!!! ThreadMethodSetTextAsynchronous 222 !");
		}
//------------------------------------------------------------------------
		// Je volana, ked sa skonci asynchronna operacia.
		void DO_Completed(object Sender, EventArgs E)
		{
			Debug.WriteLine("!!! DO_Completed FINISHED !");
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// !!! Je volana zo sekundarneho threadu.
		private object IncrementLabelFromSecondaryThread1(object Value)
		{
			Thread.Sleep(3*1000);

			MLabel1.Content=string.Format("Clicked from thread: {0} !",Value.ToString());

			return("Hello World !");
		}
//------------------------------------------------------------------------
		// !!! Je volana zo sekundarneho threadu.
		private object IncrementLabelFromSecondaryThread2(object Value)
		{
			Thread.Sleep(3*1000);

			MLabel2.Content=string.Format("Clicked from thread: {0} !",Value.ToString());

			return("Hello World !");
		}
//------------------------------------------------------------------------
		private void OnCreateNewWindow(object Sender, RoutedEventArgs E)
		{
			MCounter1++;

			Thread			T=new Thread(new ParameterizedThreadStart(this.ThreadMethodCreateDialog));

			// !!! Musim nastavit STA.
			T.SetApartmentState(ApartmentState.STA);
			T.Start(MCounter1);
		}
//------------------------------------------------------------------------
		private void OnSynchronousCreateNewWindow(object Sender, RoutedEventArgs E)
		{
			MCounter2++;

			Thread			T=new Thread(new ParameterizedThreadStart(this.ThreadMethodSetTextSynchronous));

			// !!! Musim nastavit STA.
			T.SetApartmentState(ApartmentState.STA);
			T.Start(this);
		}
//------------------------------------------------------------------------
		private void OnAsynchronousCreateNewWindow(object Sender, RoutedEventArgs E)
		{
			MCounter3++;

			Thread			T=new Thread(new ParameterizedThreadStart(this.ThreadMethodSetTextAsynchronous));

			// !!! Musim nastavit STA.
			T.SetApartmentState(ApartmentState.STA);
			T.Start(this);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------