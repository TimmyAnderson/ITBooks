﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------------------------------
namespace Roots
{
//------------------------------------------------------------------------------------------------------
	class Roots
	{
//------------------------------------------------------------------------------------------------------
        public static CName										CompleteName=new CName ("First", "Last");
//------------------------------------------------------------------------------------------------------
        private Thread											MThread;
        private bool											MShouldExit;
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
        public void Run()
        {
            MShouldExit = false;

            CName			Name=CompleteName;

            MThread=new Thread(this.Worker);
            MThread.Start(Name);

            Thread.Sleep(1000);

            Console.WriteLine("Press any key to run GC !");
            Console.ReadKey();

			GC.Collect();

            Console.WriteLine("Press any key to run exit !");
            Console.ReadKey();

            MShouldExit=true;
        }
//------------------------------------------------------------------------------------------------------
        public void Worker(object O)
        {
            CName			Name=(CName) O;

            Console.WriteLine(string.Format("Thread started [{0} {1}] !",Name.First,Name.Last));

            while (true)
            {
                // Do work.

                Thread.Sleep(500);

                if (MShouldExit==true)
                    break;
            }
        }
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
            Roots			R=new Roots();

            R.Run();
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------