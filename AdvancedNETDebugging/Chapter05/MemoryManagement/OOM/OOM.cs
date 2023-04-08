using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using System.Xml.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace OOM
{
//-------------------------------------------------------------------------------------------------------
	class OOM
	{
//-------------------------------------------------------------------------------------------------------
        public void Run1()
        {
            XmlRootAttribute		Root=new XmlRootAttribute();

            Root.ElementName="MyPersonRoot";
            Root.Namespace="http://www.contoso.com";
            Root.IsNullable=true;

            while(true)
            {
                CPerson				P=new CPerson();

                P.Name="Timmy Anderson";
                P.SocialSecurity="xxx-xx-xxxx";
                P.Age=12;

				// !!!!! Problem sposobuje tento riadok.
				// !!!!! XmlSerializer totizto pre VSETKY KONSTURKTORY okrem DVOCH - DYNAMICKY GENERUJE SERIALIZACNU ASSEMBLY, na ktoru sa tie OSTATNE 2 CONTRUCTORS pri pouziti dotazuju a ked sa takato assembly uz nachadza v procese, tak ju VYUZIJU.
				// !!!!! Kvadraticka DEBILITA tohto pristupu ju, ze KAZDA INSTANCIA XmlSerializer (okrem 2 konstruktorov) VYTVORI NOVU ASSEMBLY v PROCESE a to samozrejme vedie k MEMORY LEAKS.
				// !!!!! Riesenim je mat iba JEDNU INSTANCIU XmlSerializer, alebo pouzivat konstruktory, ktore vyuzivaju REUSING existujucej generovanej ASSEMBLY.
                XmlSerializer		Ser=new XmlSerializer(typeof(CPerson), Root);
                Stream				S=new FileStream("c:\\Ser.txt", FileMode.Create);

                Ser.Serialize(S, P);
                S.Close();
            }
        }
//-------------------------------------------------------------------------------------------------------
        public void Run2()
		{
			List<byte[]>		BigList=new List<byte[]>();

			while(true)
			{
				byte[]			MemBlock=new byte[1024*1024];

				// 1. V .NET ak dam alokovane velke pole (vacsie ako PAGE SIZE) - povedzme 1 GB, tak v skutocnosti pamate pre sice je COMMITED, ale iba v PAGE FILE. Ziadnu RAM PAMAT taketo pole NEZABERA.
				// !!! 2. To vedie k tomu, ze ak napriklad v Task Manager pozriem na velkost pamate, tak v stlpci 'Commit Size' budem mat 1 GB COMMITED MEMORY, aj ked stlpec 'Working Set' bude obsahovat iba povedzme par MB.
				// !!! 3. V .NET totizto plati, ze BUNKAM POLA sa rezervuje pamat AZ po PRVOM READ/WRITE do MEMORY PAGE v ktorej sa BUNKA NACHADZA. Az pri prvom pristupe do tejto MEMORY PAGE sa SKUTOCNE ALOKUJE cela PAGE RAM PAMATE.
				// !!!!! 4. Ak chcem aby pole o velkosti 1 GB bolo OKAMZITE v RAM, je treba pristupit ku KAZDEMU N-temu zaznamu (kde N je PAGE SIZE - standardne 4096 bytes) a citat z neho, alebo do zapisat. V tomto pripade, kedze pristupim ku KAZDEJ PAGE, vsetky PAGES su OKAMZITE ALOKOVANE na RAM.
				/*
				for (int i=0;i<MemBlock.Length;i+=Environment.SystemPageSize)
					MemBlock[i]=(byte) (i % 256);
				*/

				BigList.Add(MemBlock);

				//Thread.Sleep(0);

				if (BigList.Count==0)
					break;
			}

			Console.WriteLine(string.Format("Big list size: [{0}] !",BigList.Count));
		}
//-------------------------------------------------------------------------------------------------------
        public void Run3()
        {
            XmlRootAttribute		Root=new XmlRootAttribute();

            Root.ElementName="MyPersonRoot";
            Root.Namespace="http://www.contoso.com";
            Root.IsNullable=true;

			// !!!!! Vytvori sa IBA 1 INSTANICA XmlSerializer a generuje sa iba 1 DYNAMICKA ASSEMBLY. Vysledkom je, ze NEDOCHADZA ku neustalemu generovaniu novych ASSEMBLIES a tym padom ani k MEMORY LEAKS.
            XmlSerializer		Ser=new XmlSerializer(typeof(CPerson), Root);

			while(true)
            {
                CPerson				P=new CPerson();

                P.Name="Timmy Anderson";
                P.SocialSecurity="xxx-xx-xxxx";
                P.Age=12;

                Stream				S=new FileStream("c:\\Ser.txt", FileMode.Create);

                Ser.Serialize(S, P);
                S.Close();
            }
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.WriteLine("Press any key to start !");
			Console.ReadKey();

            OOM						O=new OOM();

            //O.Run1();
            O.Run2();
            //O.Run3();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------