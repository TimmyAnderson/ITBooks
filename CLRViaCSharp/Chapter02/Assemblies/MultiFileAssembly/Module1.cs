using System;
//-------------------------------------------------------------------------------------------------------
namespace HelloWorld
{
//-------------------------------------------------------------------------------------------------------
	class CModule1Class
	{
//-------------------------------------------------------------------------------------------------------
		public static void SayHello()
		{
			// !!!!! Po VYTVORENI ASSEMBLY z MODULES je KLUDNE mozne ZMENIT MODULE - prekompilovat jeho CODE a tento NOVY MODULE sa POUZIJE NAMIESTO EXISTUJUCEHO a to AJ BEZ NUTNOSTI robit REKOMPILACIU CELEJ ASSEMBLY (obsahujucej tieto MODULES).
			Console.WriteLine("Hello from MODULE 1 !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------