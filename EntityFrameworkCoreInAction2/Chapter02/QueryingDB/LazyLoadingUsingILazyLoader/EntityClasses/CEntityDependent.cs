﻿using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using Microsoft.EntityFrameworkCore.Infrastructure;
//----------------------------------------------------------------------------------------------------------------------
namespace LazyLoadingUsingILazyLoader
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CEntityDependent
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Instancia CLASS implementujucej INTERFACE [ILazyLoader], ktora sa pouziva na vykonanie LAZY LOADING.
		private readonly ILazyLoader							MLazyLoader;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityDependentID;
//----------------------------------------------------------------------------------------------------------------------
		private string											MEntityDependentValue;
//----------------------------------------------------------------------------------------------------------------------
		private int												MEntityPrincipalID;
//----------------------------------------------------------------------------------------------------------------------
		private CEntityPrincipal								MEntityPrincipal;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! CONSTRUCTOR vola ENTITY FRAMEWORK, ktory zasle instanciu LAZY LOADER.
		public CEntityDependent(ILazyLoader LazyLoader)
		{
			MLazyLoader=LazyLoader;
			MEntityDependentID=default(int);
			MEntityDependentValue=default(string);
			MEntityPrincipalID=default(int);
			MEntityPrincipal=default(CEntityPrincipal);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CEntityDependent(string EntityDependentValue)
		{
			MLazyLoader=default(ILazyLoader);
			MEntityDependentID=default(int);
			MEntityDependentValue=EntityDependentValue;
			MEntityPrincipalID=default(int);
			MEntityPrincipal=default(CEntityPrincipal);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												EntityDependentID
		{
			get
			{
				return(MEntityDependentID);
			}
			set
			{
				MEntityDependentID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											EntityDependentValue
		{
			get
			{
				return(MEntityDependentValue);
			}
			set
			{
				MEntityDependentValue=value;
			}
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
		public CEntityPrincipal									EntityPrincipal
		{
			get
			{
				if (MLazyLoader!=null)
				{
					// !!! Volanim METHOD [ILazyLoader.Load()] sa vykona LAZY LOADING, ak OBJECT este NEBOL NACITANY.
					MLazyLoader.Load(this,ref MEntityPrincipal);
				}

				return(MEntityPrincipal);
			}
			set
			{
				MEntityPrincipal=value;
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
				SB.AppendLine($"ENTITY DEPENDENT [{Index}]:");
			}
			else
			{
				SB.AppendLine($"ENTITY DEPENDENT:");
			}

			SB.AppendLine($"\tENTITY DEPENDENT ID [{MEntityDependentID}] !");
			SB.AppendLine($"\tENTITY DEPENDENT VALUE [{MEntityDependentValue}] !");
			SB.AppendLine($"\tENTITY PRINCIPAL ID [{MEntityPrincipalID}] !");

			return(SB.ToString());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------