﻿using System;
using System.Net.Http;
using System.Text;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			//CMenuWebServiceWithControllers					Menu=new CMenuWebServiceWithControllers();
			CMenuWebServiceMinimalAPI							Menu=new CMenuWebServiceMinimalAPI();

			Menu.Execute();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------