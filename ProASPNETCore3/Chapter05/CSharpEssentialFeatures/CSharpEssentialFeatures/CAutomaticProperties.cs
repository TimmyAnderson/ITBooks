﻿using System;
using System.Collections.Generic;
using System.Text;
//----------------------------------------------------------------------------------------------------------------------
namespace CSharpEssentialFeatures
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CAutomaticProperties
	{
//----------------------------------------------------------------------------------------------------------------------
		public CAutomaticProperties()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CAutomaticProperties(string Field1)
		{
			this.Field1=new CField(Field1);
		}
//----------------------------------------------------------------------------------------------------------------------
		public CAutomaticProperties(string Field1, string Field2)
		{
			this.Field1=new CField(Field1);

			// !!! Aj READ ONLY PROPERTIES je mozne nastavit v CONSTRUCTORS.
			this.Field2=new CField(Field2);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CField											Field1
		{
			get;
			set;
		}=new CField("DEFUALT FIELD 1");
//----------------------------------------------------------------------------------------------------------------------
		public CField											Field2
		{
			get;
		}=new CField("DEFUALT FIELD 2");
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------