using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
//-------------------------------------------------------------------------------------------------------
namespace Scaner
{
//-------------------------------------------------------------------------------------------------------
	public static class CXMLDeserializer
	{
//-------------------------------------------------------------------------------------------------------
		public static void DeserializeFromXML(string XML, out CInputChar[] InputChars, out CState[] States)
		{
			string								TAB="TAB";
			string								CR="CR";
			string								NEW_LINE="NEW_LINE";

			States=null;
			InputChars=null;

			List<CInputChar>					InputCharsList=new List<CInputChar>();
			List<CState>						StatesList=new List<CState>();

			XDocument							Document=XDocument.Parse(XML);
			XElement							TableElement=Document.Element("Table");
			XElement							InputCharsElement=TableElement.Element("InputChars");
			XElement							StatesElement=TableElement.Element("States");

			foreach(XElement InputCharElement in InputCharsElement.Elements("InputChar"))
			{
				XAttribute						TypeAttribute=InputCharElement.Attribute("Type");
				string							TypeAttributeValue=(string) TypeAttribute;

				XAttribute						NameAttribute=InputCharElement.Attribute("Name");
				string							NameAttributeValue=(string) NameAttribute;

				CInputChar						InputChar=null;

				if (TypeAttributeValue==typeof(CInputChar_AnyLetter).Name)
				{
					XAttribute					AcceptUpperCaseLettersAttribute=InputCharElement.Attribute("AcceptUpperCaseLetters");
					bool						AcceptUpperCaseLettersValue=(bool) AcceptUpperCaseLettersAttribute;

					XAttribute					AcceptLowerCaseLettersAttribute=InputCharElement.Attribute("AcceptLowerCaseLetters");
					bool						AcceptLowerCaseLettersValue=(bool) AcceptLowerCaseLettersAttribute;

					InputChar=new CInputChar_AnyLetter(NameAttributeValue,AcceptUpperCaseLettersValue,AcceptLowerCaseLettersValue);
				}
				else if (TypeAttributeValue==typeof(CInputChar_AnyNumber).Name)
				{
					InputChar=new CInputChar_AnyNumber(NameAttributeValue);
				}
				else if (TypeAttributeValue==typeof(CInputChar_OneOrMoreCharacters).Name)
				{
					List<char>					Characters=new List<char>();

					foreach(XElement CharacterElement in InputCharElement.Elements("Character"))
					{
						XAttribute				ValueAttribute=CharacterElement.Attribute("Value");
						string					ValueValue=(string) ValueAttribute;
						char					C;

						if (ValueValue==TAB)
						{
							C='\t';
						}
						else if (ValueValue==CR)
						{
							C='\r';
						}
						else if (ValueValue==NEW_LINE)
						{
							C='\n';
						}
						else
						{
							if (ValueValue.Length==0)
								throw(new Exception("Value ATTRIBUTE for Character ELEMENT is EMPTY !"));

							C=ValueValue[0];
						}

						Characters.Add(C);
					}

					if (Characters.Count==0)
						throw(new Exception("At least ONE Character ELEMENT must be specified !"));

					InputChar=new CInputChar_OneOrMoreCharacters(NameAttributeValue,Characters.ToArray());
				}
				else if (TypeAttributeValue==typeof(CInputChar_EOF).Name)
				{
					InputChar=new CInputChar_EOF(NameAttributeValue);
				}
				else if (TypeAttributeValue==typeof(CInputChar_Other).Name)
				{
					InputChar=new CInputChar_Other(NameAttributeValue);
				}
				else
					throw(new Exception(string.Format("INVALID INPUT CHAR TYPE [{0}] !",TypeAttributeValue)));

				InputCharsList.Add(InputChar);
			}

			foreach(XElement StateElement in StatesElement.Elements("State"))
			{
				XAttribute						TypeAttribute=StateElement.Attribute("Type");
				string							TypeAttributeValue=(string) TypeAttribute;

				XAttribute						NameAttribute=StateElement.Attribute("Name");
				string							NameAttributeValue=(string) NameAttribute;

				CState							State=null;

				if (TypeAttributeValue==typeof(CState_NonAcceptingStart).Name)
				{
					State=new CState_NonAcceptingStart(NameAttributeValue);
				}
				else if (TypeAttributeValue==typeof(CState_NonAccepting).Name)
				{
					State=new CState_NonAccepting(NameAttributeValue);
				}
				else if (TypeAttributeValue==typeof(CState_AcceptingToken).Name)
				{
					XAttribute					TokenIDAttribute=StateElement.Attribute("TokenID");
					string						TokenIDAttributeValue=(string) TokenIDAttribute;

					State=new CState_AcceptingToken(NameAttributeValue,TokenIDAttributeValue);
				}
				else if (TypeAttributeValue==typeof(CState_AcceptingKeywordToken).Name)
				{
					XAttribute					KeywordTokenIDAttribute=StateElement.Attribute("KeywordTokenID");
					string						KeywordTokenIDAttributeValue=(string) KeywordTokenIDAttribute;

					XAttribute					NonKeywordTokenIDAttribute=StateElement.Attribute("NonKeywordTokenID");
					string						NonKeywordTokenIDAttributeValue=(string) NonKeywordTokenIDAttribute;

					List<string>				Keywords=new List<string>();

					foreach(XElement KeywordElement in StateElement.Elements("Keyword"))
					{
						XAttribute				ValueAttribute=KeywordElement.Attribute("Value");
						string					ValueAttributeValue=(string) ValueAttribute;

						Keywords.Add(ValueAttributeValue);
					}

					State=new CState_AcceptingKeywordToken(NameAttributeValue,KeywordTokenIDAttributeValue,NonKeywordTokenIDAttributeValue,Keywords.ToArray());
				}
				else if (TypeAttributeValue==typeof(CState_AcceptingError).Name)
				{
					State=new CState_AcceptingError(NameAttributeValue);
				}
				else
					throw(new Exception(string.Format("INVALID STATE TYPE [{0}] !",TypeAttributeValue)));

				StatesList.Add(State);
			}

			foreach(XElement StateElement in StatesElement.Elements("State"))
			{
				XAttribute						TypeAttribute=StateElement.Attribute("Type");
				string							TypeAttributeValue=(string) TypeAttribute;

				XAttribute						NameAttribute=StateElement.Attribute("Name");
				string							NameAttributeValue=(string) NameAttribute;

				CState							State=StatesList.Where(P => P.Name==NameAttributeValue).FirstOrDefault();

				if (State==null)
					throw(new Exception(string.Format("CAN'T FIND STATE [{0}] !",NameAttributeValue)));

				if (TypeAttributeValue==typeof(CState_NonAcceptingStart).Name || TypeAttributeValue==typeof(CState_NonAccepting).Name)
				{
					CState_NonAccepting			TypedState=(CState_NonAccepting) State;

					foreach(XElement TransitionElement in StateElement.Elements("Transition"))
					{
						XAttribute				InputCharAttribute=TransitionElement.Attribute("InputChar");
						string					InputCharAttributeValue=(string) InputCharAttribute;

						XAttribute				NewStateAttribute=TransitionElement.Attribute("NewState");
						string					NewStateAttributeValue=(string) NewStateAttribute;

						XAttribute				IsConsumingCharTransitionAttribute=TransitionElement.Attribute("IsConsumingCharTransition");
						bool					IsConsumingCharTransitionAttributeValue=(bool) IsConsumingCharTransitionAttribute;

						CInputChar				InputChar=InputCharsList.Where(P => P.Name==InputCharAttributeValue).FirstOrDefault();

						if (InputChar==null)
							throw(new Exception(string.Format("CAN'T FIND INPUT CHAR [{0}] !",InputCharAttributeValue)));

						CState					NewState=StatesList.Where(P => P.Name==NewStateAttributeValue).FirstOrDefault();

						if (NewState==null)
							throw(new Exception(string.Format("CAN'T FIND STATE [{0}] !",NewStateAttributeValue)));

						CTransition				Transition=new CTransition(InputChar,NewState,IsConsumingCharTransitionAttributeValue);

						TypedState.AddTransition(Transition);
					}
				}
			}

			InputChars=InputCharsList.ToArray();
			States=StatesList.ToArray();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------