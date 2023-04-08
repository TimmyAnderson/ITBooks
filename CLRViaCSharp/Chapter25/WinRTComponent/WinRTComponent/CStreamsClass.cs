using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.IO;
using Windows.Foundation;
using Windows.Storage;
using Windows.UI.Core;
using Windows.UI.Xaml.Controls;
using Windows.Storage.Streams;
//-------------------------------------------------------------------------------------------------------
namespace WinRTComponent
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CStreamsClass
	{
//-------------------------------------------------------------------------------------------------------
		private static readonly string							FILENAME="STREAMS.TXT";
//-------------------------------------------------------------------------------------------------------
		private ListView										MListView;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CStreamsClass(ListView ListView)
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
		public async void StreamsTest1()
		{
			string												WriteText="My name is Timmy Anderson !";
			byte[]												WriteTextAsBytes=Encoding.Unicode.GetBytes(WriteText);
			byte[]												ReadTextAsBytes=new byte[WriteTextAsBytes.Length];

			try
			{
				StorageFile										Storage=await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.ReplaceExisting);

				using(Stream Stream=await Storage.OpenStreamForWriteAsync())
				{
					// SYNCHRONNA OPERACIA.
					Stream.Write(WriteTextAsBytes,0,WriteTextAsBytes.Length);
				}

				WriteLog("DATA SUCCESSFULLY WRITTEN to FILE !");
			}
			// !!! Kedze NEBOLA pouzita METHOD AsTask() so CancellationTokenSource, OPERATION NEMOZE byt CANCELLED.
			catch(OperationCanceledException)
			{
				WriteLog("SOME WRITE OPERATION CANCELLED !");
			}
			catch(Exception)
			{
				WriteLog("SOME WRITE OPERATION FAILED !");
			}

			try
			{
				StorageFile										Storage=await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.OpenIfExists);

				using(Stream Stream=await Storage.OpenStreamForReadAsync())
				{
					// SYNCHRONNA OPERACIA.
					Stream.Read(ReadTextAsBytes,0,ReadTextAsBytes.Length);
				}

				string											ReadText=Encoding.Unicode.GetString(ReadTextAsBytes,0,ReadTextAsBytes.Length);

				WriteLog(string.Format("DATA [{0}] SUCCESSFULLY READ from FILE !",ReadText));
			}
			// !!! Kedze NEBOLA pouzita METHOD AsTask() so CancellationTokenSource, OPERATION NEMOZE byt CANCELLED.
			catch(OperationCanceledException)
			{
				WriteLog("SOME READ OPERATION CANCELLED !");
			}
			catch(Exception)
			{
				WriteLog("SOME READ OPERATION FAILED !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		public async void StreamsTest2()
		{
			string												WriteText="My name is Timmy Anderson !";
			byte[]												WriteTextAsBytes=Encoding.Unicode.GetBytes(WriteText);
			byte[]												ReadTextAsBytes=new byte[WriteTextAsBytes.Length];

			try
			{
				StorageFile										Storage=await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.ReplaceExisting);

				using(Stream Stream=await Storage.OpenStreamForWriteAsync())
				{
					// ASYNCHRONNA OPERACIA.
					await Stream.WriteAsync(WriteTextAsBytes,0,WriteTextAsBytes.Length);
				}

				WriteLog("DATA SUCCESSFULLY WRITTEN to FILE !");
			}
			// !!! Kedze NEBOLA pouzita METHOD AsTask() so CancellationTokenSource, OPERATION NEMOZE byt CANCELLED.
			catch(OperationCanceledException)
			{
				WriteLog("SOME WRITE OPERATION CANCELLED !");
			}
			catch(Exception)
			{
				WriteLog("SOME WRITE OPERATION FAILED !");
			}

			try
			{
				StorageFile										Storage=await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.OpenIfExists);

				using(Stream Stream=await Storage.OpenStreamForReadAsync())
				{
					// ASYNCHRONNA OPERACIA.
					await Stream.ReadAsync(ReadTextAsBytes,0,ReadTextAsBytes.Length);
				}

				string											ReadText=Encoding.Unicode.GetString(ReadTextAsBytes,0,ReadTextAsBytes.Length);

				WriteLog(string.Format("DATA [{0}] SUCCESSFULLY READ from FILE !",ReadText));
			}
			// !!! Kedze NEBOLA pouzita METHOD AsTask() so CancellationTokenSource, OPERATION NEMOZE byt CANCELLED.
			catch(OperationCanceledException)
			{
				WriteLog("SOME READ OPERATION CANCELLED !");
			}
			catch(Exception)
			{
				WriteLog("SOME READ OPERATION FAILED !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		public async void StreamsTest3()
		{
			string												WriteText="My name is Timmy Anderson !";
			byte[]												WriteTextAsBytes=Encoding.Unicode.GetBytes(WriteText);
			byte[]												ReadTextAsBytes=new byte[WriteTextAsBytes.Length];

			try
			{
				StorageFile										Storage=await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.ReplaceExisting);
				// !!! Ziskam WinRT STREAM.
				IRandomAccessStream								WinRTStream=await Storage.OpenAsync(FileAccessMode.ReadWrite);

				using(Stream Stream=WinRTStream.AsStreamForWrite())
				{
					// SYNCHRONNA OPERACIA.
					Stream.Write(WriteTextAsBytes,0,WriteTextAsBytes.Length);
				}

				WinRTStream.Dispose();

				WriteLog("DATA SUCCESSFULLY WRITTEN to FILE !");
			}
			// !!! Kedze NEBOLA pouzita METHOD AsTask() so CancellationTokenSource, OPERATION NEMOZE byt CANCELLED.
			catch(OperationCanceledException)
			{
				WriteLog("SOME WRITE OPERATION CANCELLED !");
			}
			catch(Exception)
			{
				WriteLog("SOME WRITE OPERATION FAILED !");
			}

			try
			{
				StorageFile										Storage=await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.OpenIfExists);
				// !!! Ziskam WinRT STREAM.
				IRandomAccessStream								WinRTStream=await Storage.OpenAsync(FileAccessMode.Read);

				using(Stream Stream=WinRTStream.AsStreamForRead())
				{
					// SYNCHRONNA OPERACIA.
					Stream.Read(ReadTextAsBytes,0,ReadTextAsBytes.Length);
				}

				WinRTStream.Dispose();

				string											ReadText=Encoding.Unicode.GetString(ReadTextAsBytes,0,ReadTextAsBytes.Length);

				WriteLog(string.Format("DATA [{0}] SUCCESSFULLY READ from FILE !",ReadText));
			}
			// !!! Kedze NEBOLA pouzita METHOD AsTask() so CancellationTokenSource, OPERATION NEMOZE byt CANCELLED.
			catch(OperationCanceledException)
			{
				WriteLog("SOME READ OPERATION CANCELLED !");
			}
			catch(Exception)
			{
				WriteLog("SOME READ OPERATION FAILED !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		public async void StreamsTest4()
		{
			string												WriteText="My name is Timmy Anderson !";
			byte[]												WriteTextAsBytes=Encoding.Unicode.GetBytes(WriteText);
			byte[]												ReadTextAsBytes=new byte[WriteTextAsBytes.Length];

			try
			{
				StorageFile										Storage=await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.ReplaceExisting);
				// !!! Ziskam WinRT STREAM.
				IRandomAccessStream								WinRTStream=await Storage.OpenAsync(FileAccessMode.ReadWrite);

				using(Stream Stream=WinRTStream.AsStreamForWrite())
				{
					// ASYNCHRONNA OPERACIA.
					await Stream.WriteAsync(WriteTextAsBytes,0,WriteTextAsBytes.Length);
				}

				WinRTStream.Dispose();

				WriteLog("DATA SUCCESSFULLY WRITTEN to FILE !");
			}
			// !!! Kedze NEBOLA pouzita METHOD AsTask() so CancellationTokenSource, OPERATION NEMOZE byt CANCELLED.
			catch(OperationCanceledException)
			{
				WriteLog("SOME WRITE OPERATION CANCELLED !");
			}
			catch(Exception)
			{
				WriteLog("SOME WRITE OPERATION FAILED !");
			}

			try
			{
				StorageFile										Storage=await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.OpenIfExists);
				// !!! Ziskam WinRT STREAM.
				IRandomAccessStream								WinRTStream=await Storage.OpenAsync(FileAccessMode.Read);

				using(Stream Stream=WinRTStream.AsStreamForRead())
				{
					// ASYNCHRONNA OPERACIA.
					await Stream.ReadAsync(ReadTextAsBytes,0,ReadTextAsBytes.Length);
				}

				WinRTStream.Dispose();

				string											ReadText=Encoding.Unicode.GetString(ReadTextAsBytes,0,ReadTextAsBytes.Length);

				WriteLog(string.Format("DATA [{0}] SUCCESSFULLY READ from FILE !",ReadText));
			}
			// !!! Kedze NEBOLA pouzita METHOD AsTask() so CancellationTokenSource, OPERATION NEMOZE byt CANCELLED.
			catch(OperationCanceledException)
			{
				WriteLog("SOME READ OPERATION CANCELLED !");
			}
			catch(Exception)
			{
				WriteLog("SOME READ OPERATION FAILED !");
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------