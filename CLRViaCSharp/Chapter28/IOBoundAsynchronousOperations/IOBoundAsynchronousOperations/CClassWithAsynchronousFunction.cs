using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace IOBoundAsynchronousOperations
{
//-------------------------------------------------------------------------------------------------------
	class CClassWithAsynchronousFunction
	{
//-------------------------------------------------------------------------------------------------------
		// !!! ASYNCHRONOUS FUNCTION MUSI vraciat Task<RETURN_VALUE>, kde RETURN_VALUE je TYPE RETURN VALUE, ktoru ASYNCHRONOUS FUNCTION vracia.
		public async Task<string> MyAsynchronousFunction()
		{
			string												Result="";

			// !!!!! CODE sa vykonava v THREADE, ktory ZAVOLAL MyAsynchronousFunction().
			Console.WriteLine(string.Format("THREAD: [{0}] - MyAsynchronousFunction() STARTED !",Thread.CurrentThread.ManagedThreadId));

			using(FileStream FS=new FileStream(@"Files\SomeFile.txt",FileMode.Open))
			{
				int												Length=(int) FS.Length;
				byte[]											Buffer=new byte[Length];

				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE FIRST READ !",Thread.CurrentThread.ManagedThreadId));

				// !!! Nacita prvych 10 BYTES.
				// !!!!! Kedze sa pouzil KEYWORD 'await', tak sa IO OPERATION vykona ASYNCHRONNE.
				await FS.ReadAsync(Buffer,0,10);

				// !!!!! CODE sa vykona v NOVOM TASKU.
				Console.WriteLine(string.Format("THREAD: [{0}] - AFTER FIRST READ !",Thread.CurrentThread.ManagedThreadId));

				Thread.Sleep(1000);
				
				// !!! Nacita prvych 10 BYTES.
				// !!!!! Kedze sa pouzil KEYWORD 'await', tak sa IO OPERATION vykona ASYNCHRONNE.
				Console.WriteLine(string.Format("THREAD: [{0}] - BEFORE SECOND READ !",Thread.CurrentThread.ManagedThreadId));

				await FS.ReadAsync(Buffer,10,Length-10);

				// !!!!! CODE sa vykona v NOVOM TASKU.
				Console.WriteLine(string.Format("THREAD: [{0}] - AFTER SECOND READ !",Thread.CurrentThread.ManagedThreadId));

				Result=Encoding.UTF8.GetString(Buffer);
			}

			Console.WriteLine(string.Format("THREAD: [{0}] - MyAsynchronousFunction() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			return(Result);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------