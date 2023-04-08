using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using System.Runtime.InteropServices;
using Microsoft.WindowsErrorReporting.Services.Data.API;
//-------------------------------------------------------------------------------------------------------
namespace WERConsole
{
//-------------------------------------------------------------------------------------------------------
	class WerConsole
	{
//-------------------------------------------------------------------------------------------------------
        public void Run()
        {
            int					EventID;
            string				Product;
			string				File;
			string				CabLoc;
			string				UserName;
			string				Password;
            Login				LLogin;

            Console.Write("Enter user name: ");
            UserName=Console.ReadLine();

            Console.Write("Enter password: ");
            Password=Console.ReadLine();

            Console.WriteLine("Login into WER...");

            LLogin=WerLogin(UserName, Password);
            Console.WriteLine("Login succeeded !");

            Console.Write("Enter Product: ");
            Product=Console.ReadLine();

            Console.Write("Enter File: ");
            File=Console.ReadLine();
            
            Console.Write("Enter Event ID: ");
            EventID=int.Parse(Console.ReadLine());

            Console.Write("Enter Location to store CABs: ");
            CabLoc=Console.ReadLine();

            if (Directory.Exists(CabLoc)==false)
                Directory.CreateDirectory(CabLoc);

            Event				E=GetEvent(Product,File,EventID,ref LLogin);

            Console.WriteLine("Event successfully retrieved !");
            Console.WriteLine(string.Format("Event ID: [{0}] !",E.ID));
            Console.WriteLine(string.Format("Event Total Hits: [{0}] !", E.TotalHits.ToString()));
            Console.WriteLine("Storing CABs...");

            foreach (Cab C in E.GetCabs(ref LLogin))
            {
                try
                {
                    C.SaveCab(CabLoc, true, ref LLogin);
                }
                catch(Exception)
                {
                }
            }

            Console.WriteLine(string.Format("CABs stored to: [{0}] !", CabLoc));
        }
//-------------------------------------------------------------------------------------------------------
        public Login WerLogin(string UserName, string Password)
        {
            Login				Login=new Login(UserName, Password);

            Login.Validate();
            return(Login);
        }
//-------------------------------------------------------------------------------------------------------
        public Event GetEvent(string Pr, string Fi, int EventID, ref Login LLogin)
        {
            foreach (Product P in Product.GetProducts(ref LLogin))
            {
                if (P.Name == Pr)
                {
                    ApplicationFileCollection		AC= P.GetApplicationFiles(ref LLogin);

                    foreach (ApplicationFile File in AC)
                    {
                        if (File.Name==Fi)
                        {
                            EventPageReader			Epr=File.GetEvents();

                            while(Epr.Read(ref LLogin)==true)
                            {
                                EventReader			ER=Epr.Events;

                                while (ER.Read()==true)
                                {
                                    Event			E=ER.Event;

                                    return(E);
                                }
                            }
                        }
                    }
                }
            }

            throw(new Exception("Event Not Found !"));
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
            WerConsole		S=new WerConsole();

            S.Run();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------