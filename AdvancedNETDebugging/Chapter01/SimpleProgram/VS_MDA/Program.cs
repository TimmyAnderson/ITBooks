﻿using System;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace MDA
{
//-------------------------------------------------------------------------------------------------------
    class Program 
    {
//-------------------------------------------------------------------------------------------------------
        public static void Main(string[] args) 
        {
            Thread		T=new Thread(delegate() 
            {
                while (true) 
                { 
                    Thread.Sleep(500); 
                }
            });

            T.Start();

			// !!! Vykona ABORT threadu, co je potencialne NEBEZPECNA OPERACIE a preto bude monitorovana cez MDA.
            T.Abort();

            Console.WriteLine("Done !");
        }
//-------------------------------------------------------------------------------------------------------
    }
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------