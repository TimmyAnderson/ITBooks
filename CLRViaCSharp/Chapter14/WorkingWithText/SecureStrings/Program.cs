using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Security;
//-------------------------------------------------------------------------------------------------------
// Program MUSI byt prekompilovany s /unsafe priznakom.
//-------------------------------------------------------------------------------------------------------
namespace Chars
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// UNSAFE METODA.
		private unsafe static void DisplaySecureString(SecureString SS)
		{
			char*												PC=null;
		
			try
			{
				// Dekryptujem SecureString do UNMANAGED BUFFERA.
				PC=(char*) Marshal.SecureStringToCoTaskMemUnicode(SS);

				// Vypisem obsah SecureString.
				for (int Index=0;PC[Index]!=0;Index++)
				{
					Console.Write(PC[Index]);
				}
			}
			finally
			{
				// Odstranim UNAMAGED BUFFER a zaroven VYMAZEM PAMET na 0.
				if (PC!=null)
				{
					Marshal.ZeroFreeCoTaskMemUnicode((IntPtr) PC);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			// SecureString implementuje IDisposable, lebo interne pouziva UNMANAGED BUFFER.
			using (SecureString SS=new SecureString())
			{
				Console.Write("Please enter password: ");

				while (true)
				{
					ConsoleKeyInfo								CKI=Console.ReadKey(true);

					if (CKI.Key==ConsoleKey.Enter)
					{
						break;
					}

					// Pridavam znak do SecureString.
					SS.AppendChar(CKI.KeyChar);
					Console.Write("*");
				}

				Console.WriteLine();

				// Vypisem obsah SecureString.

				Console.Write("Password: [");
				DisplaySecureString(SS);
				Console.WriteLine("] !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			// SecureString implementuje IDisposable, lebo interne pouziva UNMANAGED BUFFER.
			using (SecureString SS=new SecureString())
			{
				Console.Write("Please enter password: ");

				while (true)
				{
					ConsoleKeyInfo								CKI=Console.ReadKey(true);

					if (CKI.Key==ConsoleKey.Enter)
					{
						break;
					}

					// Pridavam znak do SecureString.
					SS.AppendChar(CKI.KeyChar);

					// Spravim z CHARACTED UPPER CASE.
					SS.SetAt(SS.Length-1,Char.ToUpper(CKI.KeyChar));

					Console.Write("*");
				}

				Console.WriteLine();

				// Vypisem obsah SecureString.

				Console.Write("Password: [");
				DisplaySecureString(SS);
				Console.WriteLine("] !");

				Console.WriteLine(string.Format("LENGTH [{0}] !",SS.Length));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------