using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CLR0Rule
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CNonterminal							MNonterminal;
		private readonly CLR0Item[]								MChoices;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLR0Rule(CNonterminal Nonterminal)
		{
			MNonterminal=Nonterminal;

			CPeriodLRItemSymbol				Period=new CPeriodLRItemSymbol(".");
			List<CLR0Item>					Choices=new List<CLR0Item>();

			foreach(CChoice Choice in Nonterminal.Choices)
			{
				// Choice DOESN'T contain EMPTY TERMINAL.
				if (Choice.IsEmptyChoice==false)
				{
					for (int i=0;i<(Choice.Symbols.Length+1);i++)
					{
						List<CSymbol>		Symbols=new List<CSymbol>();

						Symbols.AddRange(Choice.Symbols);
						Symbols.Insert(i,Period);

						CLR0Item			Item=new CLR0Item(Nonterminal,Symbols.ToArray());

						Choices.Add(Item);
					}
				}
				else
				{
					CLR0Item				Item=new CLR0Item(Nonterminal,new CSymbol[]{Period});

					Choices.Add(Item);
				}
			}

			MChoices=Choices.ToArray();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNonterminal										Nonterminal
		{
			get
			{
				return(MNonterminal);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CLR0Item[]										Choices
		{
			get
			{
				return(MChoices);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLR0Item[] GetLR0ItemsWithPeriodAsFirstSymbol()
		{
			List<CLR0Item>			Items=new List<CLR0Item>();

			foreach(CLR0Item Item in MChoices)
			{
				if (Item.BeginsWithPeriod==true)
				{
					Items.Add(Item);
				}
			}

			return(Items.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(MNonterminal.Name);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------