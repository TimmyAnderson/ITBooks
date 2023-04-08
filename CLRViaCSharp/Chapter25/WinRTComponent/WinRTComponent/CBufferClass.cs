using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Runtime.InteropServices.WindowsRuntime;
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
	public sealed class CBufferClass
	{
//-------------------------------------------------------------------------------------------------------
		private static readonly string							FILENAME="BUFFER.TXT";
//-------------------------------------------------------------------------------------------------------
		private ListView										MListView;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CBufferClass(ListView ListView)
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
		public async void BufferTest()
		{
			string												WriteText="My name is Timmy Anderson !";
			byte[]												WriteTextAsBytes=Encoding.Unicode.GetBytes(WriteText);
			byte[]												ReadTextAsBytes=new byte[WriteTextAsBytes.Length];

			try
			{
				StorageFile										Storage=await KnownFolders.DocumentsLibrary.CreateFileAsync(FILENAME,CreationCollisionOption.ReplaceExisting);
				// !!! Ziskam WinRT STREAM.
				IRandomAccessStream								WinRTStream=await Storage.OpenAsync(FileAccessMode.ReadWrite);
				// !!! CLR BUFFER sa obali IBuffer INTERFACE.
				IBuffer											Buffer=WriteTextAsBytes.AsBuffer();

				await WinRTStream.WriteAsync(Buffer);

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
				// !!! CLR BUFFER sa obali IBuffer INTERFACE.
				IBuffer											Buffer=ReadTextAsBytes.AsBuffer();

				await WinRTStream.ReadAsync(Buffer,Buffer.Length,InputStreamOptions.None);

				WinRTStream.Dispose();

				// SPATNA konverzia z IBuffer na BYTE[].
				byte[]											BufferAsByteArray=Buffer.ToArray();
				string											ReadText=Encoding.Unicode.GetString(BufferAsByteArray,0,BufferAsByteArray.Length);

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