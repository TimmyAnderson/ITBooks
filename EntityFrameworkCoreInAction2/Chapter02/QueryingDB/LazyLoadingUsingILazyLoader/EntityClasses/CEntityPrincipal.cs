using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using Microsoft.EntityFrameworkCore.Infrastructure;
//----------------------------------------------------------------------------------------------------------------------
namespace LazyLoadingUsingILazyLoader
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityPrincipal
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Instancia CLASS implementujucej INTERFACE [ILazyLoader], ktora sa pouziva na vykonanie LAZY LOADING.
		private readonly ILazyLoader							MLazyLoader;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityPrincipalValue;
//----------------------------------------------------------------------------------------------------------------------
		private ICollection<CEntityDependent>					MEntitiesDependent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! CONSTRUCTOR vola ENTITY FRAMEWORK, ktory zasle instanciu LAZY LOADER.
		public CEntityPrincipal(ILazyLoader LazyLoader)
		{
			MLazyLoader=LazyLoader;
			MEntityPrincipalID=default(int);
			MEntityPrincipalValue=default(string);
			MEntitiesDependent=default(ICollection<CEntityDependent>);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityPrincipal(string EntityPrincipalValue, ICollection<CEntityDependent> EntitiesDependent)
		{
			MLazyLoader=default(ILazyLoader);
			MEntityPrincipalID=default(int);
			MEntityPrincipalValue=EntityPrincipalValue;
			MEntitiesDependent=EntitiesDependent;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityPrincipalID
		{
			get
			{
				return(MEntityPrincipalID);
			}
			set
			{
				MEntityPrincipalID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityPrincipalValue
		{
			get
			{
				return(MEntityPrincipalValue);
			}
			set
			{
				MEntityPrincipalValue=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PROPERTY, ktora v GETTER vykonava LAZY LOADING.
		public ICollection<CEntityDependent>					EntitiesDependent
		{
			get
			{
				if (MLazyLoader!=null)
				{
					// !!! Volanim METHOD [ILazyLoader.Load()] sa vykona LAZY LOADING, ak OBJECT este NEBOL NACITANY.
					MLazyLoader.Load(this,ref MEntitiesDependent);
				}
				
				return(MEntitiesDependent);
			}
			set
			{
				MEntitiesDependent=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string Print(int? Index)
		{
			StringBuilder										SB=new StringBuilder();

			if (Index!=null)
			{
				SB.AppendLine($"ENTITY PRINCIPAL [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY PRINCIPAL:");
			}

			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL VALUE [{MEntityPrincipalValue}] !");

			if (MEntitiesDependent!=null)
			{
				SB.AppendLine($"\tENTITIES N:");

				int												EntityDependentIndex=1;

				foreach(CEntityDependent EntityDependent in MEntitiesDependent)
				{
					SB.AppendLine($"\t\tENTITY DEPENDENT [{EntityDependentIndex}]:");

					SB.AppendLine($"\t\t\tENTITY DEPENDENT ID [{EntityDependent.EntityDependentID}] !");
					SB.AppendLine($"\t\t\tENTITY DEPENDENT VALUE [{EntityDependent.EntityDependentValue}] !");

					EntityDependentIndex++;
				}
			}
			else
			{
				SB.AppendLine($"\t--- ENTITIES DEPENDENT is NULL ! ---");
			}

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------