using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Runtime.Remoting;
//-------------------------------------------------------------------------------------------------------
namespace NamespaceAppDomain
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
        public void Run()
        {
            while(true)
            {
                Console.WriteLine("1. Run in default app domain");
                Console.WriteLine("2. Run in dedicated app domain");
                Console.WriteLine("Q. To quit");
                Console.Write("> ");

                ConsoleKeyInfo			K=Console.ReadKey();

                Console.WriteLine();

                if (K.KeyChar=='1')
                    RunInDefault();
                else if (K.KeyChar=='2')
                    RunInDedicated();
                else if (K.KeyChar=='q' || K.KeyChar=='Q')
                    break;
            }

        }
//-------------------------------------------------------------------------------------------------------
        public AppDomain CreateDomain()
        {
            AppDomainSetup		DomainInfo=new AppDomainSetup();

			// !!! UMYSELNE SPRAVIM CHYBU a to tak, ze nastavim ApplicationBase na PATH, kde sa AppDomain.EXE NENACHADZA.
            DomainInfo.ApplicationBase="C:\\Windows\\System32";

            return(AppDomain.CreateDomain("MyDomain", null, DomainInfo));
        }
//-------------------------------------------------------------------------------------------------------
        public void RunInDefault()
        {
			// Objekt CEntityUtil sa vytvori na DEFAULT DOMAIN.
            CEntityUtil			Util=new CEntityUtil();

            CEntity				T=new CEntity();

            T.A=10;

            Util.Dump(T);
        }
//-------------------------------------------------------------------------------------------------------
        public void RunInDedicated()
        {
			// Vytvorim novu DOMAIN.
            AppDomain			Domain=CreateDomain();

			// Objekt CEntityUtil sa vytvori na CUSTOM DOMAIN.
            CEntityUtil			Util=new CEntityUtil();
            ObjectHandle		H=Domain.CreateInstance("MyAppDomainTest", "NamespaceAppDomain.CEntityUtil");

			// Objekt CEntityUtil sa PRENESIE do DEFAULT DOMAIN.
            CEntityUtil			UtilInDefaultDomain=(CEntityUtil) H.Unwrap();

            CEntity				T=new CEntity();

            T.A=10;

            UtilInDefaultDomain.Dump(T);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
            Program			P=new Program();

            P.Run();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------