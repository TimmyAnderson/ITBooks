using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace MethodCallTest
{
//-------------------------------------------------------------------------------------------------------
	public class CSomeClass : CBaseClass
	{
//-------------------------------------------------------------------------------------------------------
		public static void StaticMethod()
		{
			Console.WriteLine("DERIVED - STATIC method CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void NonVirtualMethod()
		{
			// !!!!! Metoda v svojom tele NEPOUZIVA 'this' - nepristupuje k ziadnemu FIELD, ani nevola inu metodu triedy. Ak ba bola volana cez 'CALL', ktory NEROBI KONTORLU ci 'this'==NULL, tak by AJ KEBY BOL 'this'==NULL - teda metodu volal cez OBJEKT, ktoreho hodnota by bola NULL, tak by NEBOLA GENEROVANA EXCEPTION NullReferenceException.
			// !!!!! Avsak kedze metoda je volana cez 'CALLVIRT', ktory ROBI KONTORLU, ci 'this'==NULL, tak ak zavolam metodu z OBJEKTU, ktoreho HODNOTA JE NULL, tak sa VDAKA 'CALLVIRT' HODI EXCEPTION NullReferenceException.

			Console.WriteLine("DERIVED - NON-VIRTUAL method CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		public virtual void VirtualMethod()
		{
			Console.WriteLine("DERIVED - VIRTUAL method CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		public override void OverridedMethod()
		{
			Console.WriteLine("DERIVED - OVERRIDED method CALLED !");

			// !!! Volanie base.OverridedMethod() je uz robene cez 'CALL', aby nedoslo k NEKONECNEJ REKURZII, ak by bola volana cez 'CALLVIRT'.
			/*
				ldarg											THIS
				call											instance void MethodCallTest.CBaseClass::OverridedMethod()
			*/
			base.OverridedMethod();
		}
//-------------------------------------------------------------------------------------------------------
		public sealed override void OverridedSealedMethod()
		{
			Console.WriteLine("DERIVED - OVERRIDED SEALED method CALLED !");
			
			// !!! Volanie base.OverridedSealedMethod() je uz robene cez 'CALL', aby nedoslo k NEKONECNEJ REKURZII, ak by bola volana cez 'CALLVIRT'.
			/*
				ldarg.0
				call											instance void MethodCallTest.CBaseClass::OverridedSealedMethod()
			*/
			base.OverridedSealedMethod();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------