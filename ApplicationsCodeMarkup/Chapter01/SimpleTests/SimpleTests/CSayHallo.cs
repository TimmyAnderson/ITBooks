using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
//------------------------------------------------------------------------------
namespace SimpleTests
{
//------------------------------------------------------------------------------
	public class CSayHallo
	{
//------------------------------------------------------------------------------
		public static void Do1()
		{
            Window			Win=new Window();

            Win.Title="Say Hello";
            Win.Show();

            Application		App=new Application();

            App.Run();
		}
//------------------------------------------------------------------------------
		public static void Do2()
		{
            Window			Win=new Window();

            Win.Title="Say Hello";
            Win.Show();

			// Ked NEPOUZIJEM App.Run(), okno sa sice OTVORI, v Taskbar, ale VIZUALNE SA NEZOBRAZI, kedze Run() spusta Message Loop.
            //Application		App=new Application();

            //App.Run();
		}
//------------------------------------------------------------------------------
		public static void Do3()
		{
            Window			Win1=new Window();

            Win1.Title="Say Hello 1";
            Win1.Show();

            Application		App1=new Application();

            App1.Run();

			// Znova spustim dalsie okno.
            Window			Win2=new Window();

            Win2.Title="Say Hello 2";
            Win2.Show();

			// Vytvorim dalsi objekt Application.
			// !!! Hodi EXCEPTION, pretoze IBA JEDEN Application objekt je mozne vytvorit v jedne AppDomain.
            Application		App2=new Application();

            App2.Run();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------