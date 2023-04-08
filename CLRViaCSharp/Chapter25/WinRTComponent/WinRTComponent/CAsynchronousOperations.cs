using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Storage;
using Windows.UI.Core;
using Windows.UI.Xaml.Controls;
using Windows.Storage.Streams;
//-------------------------------------------------------------------------------------------------------
namespace WinRTComponent
{
//-------------------------------------------------------------------------------------------------------
	// !!! Na to aby CODE fungoval MUSI byt MANIFEST APPLICATION, ktora tuto WinRT COMPONENT pouziva nastaveny na akceptaciu .TXT FILES v DIRECTORY KnownFolders.DocumentsLibrary.
	public sealed class CAsynchronousOperations
	{
//-------------------------------------------------------------------------------------------------------
		private static readonly string							FILENAME="TEST.TXT";
//-------------------------------------------------------------------------------------------------------
		private ListView										MListView;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CAsynchronousOperations(ListView ListView)
		{
			MListView=ListView;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private async void WriteLog(string Text)
		{
			DispatchedHandler									Handler=() =>
			{
				MListView.Items.Add(Text);
			};

			await MListView.Dispatcher.RunAsync(CoreDispatcherPriority.Normal,Handler);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void CreateFileOperationCompleted(IAsyncOperation<StorageFile> AsyncInfo, AsyncStatus Status)
		{
			if (Status==AsyncStatus.Started)
			{
				WriteLog("FILE CREATION STARTED !");
			}
			else if (Status==AsyncStatus.Completed)
			{
				WriteLog("FILE CREATION COMPLETED !");
			}
			else if (Status==AsyncStatus.Canceled)
			{
				WriteLog("FILE CREATION CANCELLED !");
			}
			else if (Status==AsyncStatus.Error)
			{
				WriteLog("FILE CREATION FAILED !");
			}
			
			AsyncInfo.Close();
		}
//-------------------------------------------------------------------------------------------------------
		private void CreateFileOperationWithCancellationCompleted(IAsyncOperation<StorageFile> AsyncInfo, AsyncStatus Status)
		{
			if (Status==AsyncStatus.Started)
			{
				WriteLog("FILE CREATION STARTED !");
			}
			else if (Status==AsyncStatus.Completed)
			{
				WriteLog("FILE CREATION COMPLETED !");

				StorageFile										File=AsyncInfo.GetResults();
				IAsyncAction									AsyncAction=FileIO.WriteTextAsync(File,"My name is Timmy Anderson !");

				AsyncAction.Cancel();

				AsyncAction.Completed+=WriteTextOperationCompleted;
			}
			else if (Status==AsyncStatus.Canceled)
			{
				WriteLog("FILE CREATION CANCELLED !");
			}
			else if (Status==AsyncStatus.Error)
			{
				WriteLog("FILE CREATION FAILED !");
			}
			
			AsyncInfo.Close();
		}
//-------------------------------------------------------------------------------------------------------
		private void WriteTextOperationCompleted(IAsyncAction AsyncInfo, AsyncStatus Status)
		{
			if (Status==AsyncStatus.Started)
			{
				WriteLog("WRITE TEXT to FILE STARTED !");
			}
			else if (Status==AsyncStatus.Completed)
			{
				WriteLog("WRITE TEXT to FILE COMPLETED !");
			}
			else if (Status==AsyncStatus.Canceled)
			{
				WriteLog("WRITE TEXT to FILE CANCELLED !");
			}
			else if (Status==AsyncStatus.Error)
			{
				WriteLog("WRITE TEXT to FILE FAILED !");
			}
			
			AsyncInfo.Close();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void CreateFile()
		{
			IAsyncOperation<StorageFile>						AsyncOperation=KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.ReplaceExisting);

			AsyncOperation.Completed+=CreateFileOperationCompleted;
		}
//-------------------------------------------------------------------------------------------------------
		public void CreateFileOrFailIfFileExists()
		{
			IAsyncOperation<StorageFile>						AsyncOperation=KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.FailIfExists);

			AsyncOperation.Completed+=CreateFileOperationCompleted;
		}
//-------------------------------------------------------------------------------------------------------
		// !!! NEPODARILO sa mi nasimulovat CANCELLATION.
		public void CreateFileWithCancellation()
		{
			IAsyncOperation<StorageFile>						AsyncOperation=KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.OpenIfExists);

			AsyncOperation.Cancel();

			AsyncOperation.Completed+=CreateFileOperationWithCancellationCompleted;
		}
//-------------------------------------------------------------------------------------------------------
		public async void CreateFileAwait()
		{
			try
			{
				WriteLog("ASYNCHRONOUS OPERATION STARTING !");

				await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.ReplaceExisting);
			}
			// !!! Kedze NEBOLA pouzita METHOD AsTask() so CancellationTokenSource, OPERATION NEMOZE byt CANCELLED.
			catch(OperationCanceledException)
			{
				WriteLog("FILE CREATION CANCELLED !");
			}
			catch(Exception)
			{
				WriteLog("FILE CREATION FAILED !");
			}

			WriteLog("ASYNCHRONOUS OPERATION FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		public async void CreateFileOrFailIfFileExistsAwait()
		{
			try
			{
				WriteLog("ASYNCHRONOUS OPERATION STARTING !");

				await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.FailIfExists);
			}
			// !!! Kedze NEBOLA pouzita METHOD AsTask() so CancellationTokenSource, OPERATION NEMOZE byt CANCELLED.
			catch(OperationCanceledException)
			{
				WriteLog("FILE CREATION CANCELLED !");
			}
			catch(Exception)
			{
				WriteLog("FILE CREATION FAILED !");
			}

			WriteLog("ASYNCHRONOUS OPERATION FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! NEPODARILO sa mi nasimulovat CANCELLATION.
		public async void CreateFileWithCancellationAwait()
		{
			try
			{
				// !!! OPERATION bude OKAMZITE CANCELLED.
				CancellationTokenSource							CTS=new CancellationTokenSource(1);

				WriteLog("ASYNCHRONOUS OPERATION STARTING !");

				await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.ReplaceExisting).AsTask(CTS.Token);
			}
			// !!! Kedze BOLA pouzita METHOD AsTask() so CancellationTokenSource, OPERATION MOZE byt CANCELLED.
			catch(OperationCanceledException)
			{
				WriteLog("FILE CREATION CANCELLED !");
			}
			catch(Exception)
			{
				WriteLog("FILE CREATION FAILED !");
			}

			WriteLog("ASYNCHRONOUS OPERATION FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------