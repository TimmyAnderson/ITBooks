using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace HybridThreadSynchronizationConstructs
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CDoubleCheckLockingAlgorithm
	{
//-------------------------------------------------------------------------------------------------------
		// Pouziva sa na realizaciu CRICITAL SECTION.
		private static readonly object							MLock=new object();
//-------------------------------------------------------------------------------------------------------
		// Instancia sa vytvori IBA na POZIADANIE.
		private static CExpensiveObjectToCreate					MExpensiveObjectToCreate;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static CExpensiveObjectToCreate GetExpensiveObjectToCreate()
		{
			// Ak uz bol OBJECT vytvoreny, tak sa vrati jeho referencia.
			if (MExpensiveObjectToCreate!=null)
			{
				return(MExpensiveObjectToCreate);
			}

			// !!! OBJECT este NEBOL VYTVORENY a BUDE VYTVORENY.

			// !!! MONITOR reprezentuje FULL FENCE.
			Monitor.Enter(MLock);
	
			// !!!!! Kedze MONITOR reprezentuje FULL FENCE, NEHROZI, ze by si METHOD ulozila MExpensiveObjectToCreate hodnotu do CPU REGISTER a v nasledujucej podmienke NAMIESTO SKUTOCNEJ HODNOTY MExpensiveObjectToCreate pouzila hodnotu z CPU REGISTER, cim by doslo k NESPRAVNEMU VYHODNOTENIU PODMIENKY.
			if (MExpensiveObjectToCreate==null)
			{
				// !!! Vytvoreny OBJECT sa UMYSELNE ulozi do TEMPORARY VARIABLE.
				CExpensiveObjectToCreate						Temp=new CExpensiveObjectToCreate();

				// !!!!! EXTREMNE DOLEZITE je pouzit Volatile.Write(). Dovod je nasledovny.
				// !!!!! Ak by sa Volatile.Write() NEPOUZIL, COMPILER by mohol generovat CODE v ktorom by sa NAJPRV priradila MEMORY VARIABLE 'MExpensiveObjectToCreate', nasledne by sa tato MEMORY priradila do VARIABLE 'MExpensiveObjectToCreate' A AZ POTOM by sa zavolal CONSTRUCTOR MExpensiveObjectToCreate.
				// !!!!! Vysledkom by bolo, ze EXTERNY CODE pouzivajuci VARIABLE MExpensiveObjectToCreate by mohol ziskat pristup k tejto VARIABLE v dobe ked este pre nu NEBOL ZAVOLANY jej CONSTRUCTOR.
				Volatile.Write(ref MExpensiveObjectToCreate,Temp);
			}

			Monitor.Exit(MLock);

			return(MExpensiveObjectToCreate);
		}
//-------------------------------------------------------------------------------------------------------
		public static CExpensiveObjectToCreate GetExpensiveObjectToCreateWithError()
		{
			// Ak uz bol OBJECT vytvoreny, tak sa vrati jeho referencia.
			if (MExpensiveObjectToCreate!=null)
			{
				return(MExpensiveObjectToCreate);
			}

			// !!! OBJECT este NEBOL VYTVORENY a BUDE VYTVORENY.

			// !!! MONITOR reprezentuje FULL FENCE.
			Monitor.Enter(MLock);
	
			// !!!!! Kedze MONITOR reprezentuje FULL FENCE, NEHROZI, ze by si METHOD ulozila MExpensiveObjectToCreate hodnotu do CPU REGISTER a v nasledujucej podmienke NAMIESTO SKUTOCNEJ HODNOTY MExpensiveObjectToCreate pouzila hodnotu z CPU REGISTER, cim by doslo k NESPRAVNEMU VYHODNOTENIU PODMIENKY.
			if (MExpensiveObjectToCreate==null)
			{
				// !!!!! TOTO je potencialne ERROR CODE, pretoze sa moze stat, ze COMPILER by mohol generovat CODE v ktorom by sa NAJPRV priradila MEMORY VARIABLE 'MExpensiveObjectToCreate', nasledne by sa tato MEMORY priradila do VARIABLE 'MExpensiveObjectToCreate' A AZ POTOM by sa zavolal CONSTRUCTOR MExpensiveObjectToCreate.
				// !!!!! Vysledkom by bolo, ze EXTERNY CODE pouzivajuci VARIABLE MExpensiveObjectToCreate by mohol ziskat pristup k tejto VARIABLE v dobe ked este pre nu NEBOL ZAVOLANY jej CONSTRUCTOR.
				// !!! Vytvoreny OBJECT sa UMYSELNE ulozi do TEMPORARY VARIABLE.
				MExpensiveObjectToCreate=new CExpensiveObjectToCreate();
			}

			Monitor.Exit(MLock);

			return(MExpensiveObjectToCreate);
		}
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD je len KVOLI TESTOVANIU a NIE JE SUCASTOU DOUBLE CHECK LOCKING ALGORITHM.
		public static void ResetExpensiveObjectToCreate()
		{
			MExpensiveObjectToCreate=null;
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------