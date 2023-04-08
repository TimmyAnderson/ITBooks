using System;
using System.Reflection;
using System.Text;
using SharedNamespace;
//-------------------------------------------------------------------------------------------------------
namespace TwoAssembliesWithSameType_EXE
{
//-------------------------------------------------------------------------------------------------------
    class TypeCast
    {
//-------------------------------------------------------------------------------------------------------
        static void Main(string[] args)
        {
			// Assembly citana z LOAD CONTEXT.
            Assembly		AsmLoadFromContext=null;

            Console.WriteLine("Press any key to load into load from context !");
            Console.ReadKey();

			// Nacitam TwoAssembliesWithSameType_DLL s ROVNAKO POMENOVANYM TYPOM CSimpleType, ktory je TAKTIEZ ako v assembly TwoAssembliesWithSameType_EXE je v ROVNAKO NAMESPACE SharedNamespace.
			// !!!!! Aj ked ASSEMBLY TwoAssembliesWithSameType_DLL ma ROVNAKU IDENTITY ako TwoAssembliesWithSameType_EXE, take je NACITANA do procesu ako NOVA ASSEMBLY, pretoze bola nacitana cez LOAD-FROM CONTEXT a NIE DEFAULT LOAD CONTEXT ako TwoAssembliesWithSameType_EXE.
			// !!!!! Vysledok je, ze mam dve IDENTICKE ASSEMBLIES, ktore obsahuju ROVNAKE TYPES CSimpleType, ktore kompilator povazuje za ZHODNE. AVSAK RUNTIME ich bude povazovat za ROZDIELNE, pretoze KAZDA ASSEMBLY ma OKREM IDENTITY este i GUID na zaklade ktorej sa ODLISUJE ako assembly, tak i vsetky jej TYPES.
            AsmLoadFromContext=Assembly.LoadFrom(@"..\..\..\..\TwoAssembliesWithSameType_DLL\bin\x64\Debug\TwoAssembliesWithSameType_DLL.dll");

			try
			{
				// !!! HODI EXCEPTION, pretoze aj ked TYP SharedNamespace.CSimpleType z TwoAssembliesWithSameType_EXE ma TO ISTE MENO ako SharedNamespaceCSimpleType z TwoAssembliesWithSameType_DLL, v skutocnosti su to UPLNE ODLISNE TYPY z ROZDIELNYCH ASSEMBLIES.
				// !!!!! Pre kompilator su to ROVNAKE TYPES, kedze maju ROVNAKE FULLY QUALIFIED NAME, ale realne NIE SU a RUNTIME hodi EXCEPTION.
				CSimpleType		ST=(CSimpleType) AsmLoadFromContext.CreateInstance("SharedNamespace.CSimpleType");

				ST.ToString();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("!!! EXCEPTION: [{0}] !",E.Message));
			}

            Console.WriteLine("Press any key to exit !");
            Console.ReadKey();
        }
    }
}
