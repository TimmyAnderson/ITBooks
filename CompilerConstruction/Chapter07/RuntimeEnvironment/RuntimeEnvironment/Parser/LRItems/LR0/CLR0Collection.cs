﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CLR0Collection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CLR0Item[]								MItems;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLR0Collection(CRuleCollection RuleCollection)
		{
			List<CLR0Item>				Items=new List<CLR0Item>();

			foreach(CLR0Rule Rule in RuleCollection.Rules)
			{
				foreach(CLR0Item Item in Rule.Choices)
				{
					Items.Add(Item);
				}
			}

			MItems=Items.ToArray();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLR0Item[]										Items
		{
			get
			{
				return(MItems);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------