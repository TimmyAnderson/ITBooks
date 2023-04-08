using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public static class CXMLParserDeserializer
	{
//-------------------------------------------------------------------------------------------------------
		public static void DeserializeFromXML(string XML, out CNonterminalCollection NonterminalCollection, out CTerminalCollection TerminalCollection)
		{
			NonterminalCollection=new CNonterminalCollection();
			TerminalCollection=new CTerminalCollection();

			XDocument							Document=XDocument.Parse(XML);
			XElement							BNFElement=Document.Element("BNF");
			XElement							TerminalsElement=BNFElement.Element("Terminals");

			foreach(XElement TerminalElement in TerminalsElement.Elements("Terminal"))
			{
				XAttribute						TypeAttribute=TerminalElement.Attribute("Type");
				string							TypeAttributeValue=(string) TypeAttribute;

				XAttribute						NameAttribute=TerminalElement.Attribute("Name");
				string							NameAttributeValue=(string) NameAttribute;

				XAttribute						ScanerTokenIDAttribute=TerminalElement.Attribute("ScanerTokenID");
				string							ScanerTokenIDAttributeValue=(string) ScanerTokenIDAttribute;

				XAttribute						TerminalValueAttribute=TerminalElement.Attribute("TerminalValue");
				string							TerminalValueAttributeValue=(string) TerminalValueAttribute;

				if (TypeAttributeValue==typeof(CTerminal_Keyword).Name)
				{
					XAttribute					KeywordLexemaAttribute=TerminalElement.Attribute("KeywordLexema");
					string						KeywordLexemaAttributeValue=(string) KeywordLexemaAttribute;

					CTerminal_Keyword			Terminal=new CTerminal_Keyword(NameAttributeValue,ScanerTokenIDAttributeValue,TerminalValueAttributeValue,KeywordLexemaAttributeValue);

					TerminalCollection.AddTerminal(Terminal);
				}
				else if (TypeAttributeValue==typeof(CTerminal_Regular).Name)
				{
					CTerminal_Regular			Terminal=new CTerminal_Regular(NameAttributeValue,ScanerTokenIDAttributeValue,TerminalValueAttributeValue);

					TerminalCollection.AddTerminal(Terminal);
				}
				else if (TypeAttributeValue==typeof(CTerminal_EMPTY).Name)
				{
					CTerminal_EMPTY				Terminal=new CTerminal_EMPTY(NameAttributeValue,ScanerTokenIDAttributeValue,TerminalValueAttributeValue);

					TerminalCollection.AddTerminal(Terminal);
				}
				else if (TypeAttributeValue==typeof(CTerminal_EOF).Name)
				{
					CTerminal_EOF				Terminal=new CTerminal_EOF(NameAttributeValue,ScanerTokenIDAttributeValue,TerminalValueAttributeValue);

					TerminalCollection.AddTerminal(Terminal);
				}
				else
					throw(new Exception(string.Format("INVALID TERMINAL TYPE [{0}] !",TypeAttributeValue)));
			}


			XElement							NonterminalsElement=BNFElement.Element("Nonterminals");

			foreach(XElement NonterminalElement in NonterminalsElement.Elements("Nonterminal"))
			{
				XAttribute						NameAttribute=NonterminalElement.Attribute("Name");
				string							NameAttributeValue=(string) NameAttribute;

				CNonterminal					Nonterminal=new CNonterminal(NameAttributeValue);

				NonterminalCollection.AddNonterminal(Nonterminal);
			}

			foreach(XElement NonterminalElement in NonterminalsElement.Elements("Nonterminal"))
			{
				XAttribute						NameAttribute=NonterminalElement.Attribute("Name");
				string							NameAttributeValue=(string) NameAttribute;

				XElement						ChoicesElement=NonterminalElement.Element("Choices");
				CNonterminal					Nonterminal=NonterminalCollection.FindNonterminalByName(NameAttributeValue);
			
				foreach(XElement ChoiceElement in ChoicesElement.Elements("Choice"))
				{
					CChoice						Choice=new CChoice(Nonterminal);
					
					foreach(XElement SymbolElement in ChoiceElement.Elements())
					{
						XAttribute				ValueAttribute=SymbolElement.Attribute("Value");
						string					ValueAttributeValue=(string) ValueAttribute;
						CSymbol					Symbol;

						if (SymbolElement.Name=="Nonterminal")
						{
							Symbol=NonterminalCollection.FindNonterminalByName(ValueAttributeValue);
							Choice.AddChoice(Symbol);
						}
						else
						{
							Symbol=TerminalCollection.FindTerminalByTerminalValue(ValueAttributeValue);
							Choice.AddChoice(Symbol);
						}
					}

					Nonterminal.AddChoice(Choice);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------