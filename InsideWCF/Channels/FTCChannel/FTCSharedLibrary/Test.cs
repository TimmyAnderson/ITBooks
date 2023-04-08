using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.IO;
using System.Threading;
using CAsyncStatePair1=FTCSharedLibrary.CPair<FTCSharedLibrary.CTryReceiveChannelThread, string>;
using CAsyncStatePair2=FTCSharedLibrary.CPair<FTCSharedLibrary.CChannelAcceptChannelThread, string>;
using CChannelSessionPair=FTCSharedLibrary.CPair<System.ServiceModel.Channels.IDuplexSessionChannel, FTCSharedLibrary.CFTCSessionID>;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	internal class Test
	{
//-------------------------------------------------------------------------------------------------------
		public static List<CChannelSessionPair>					MChannels=new List<CChannelSessionPair>();
		public static MessageEncoder							MMessageEncoder=new CFTCMessageEncoder(CSettings.MessageVersion,ESOAPEncoder.E_SE_TEXT);
//-------------------------------------------------------------------------------------------------------
		public static void MessageText()
		{
			try
			{
				Message			MOut=Message.CreateMessage(CSettings.MessageVersion,"Test Action","Test Body !!!");
				CFTCPacket		PacketOut=new CFTCPacket(DateTime.Now,new CFTCSessionID(),"Some Address","123",EMessageType.E_MT_MESSAGE,MOut);

				MemoryStream	MS1=PacketOut.WriteMessageWithEncoder(MMessageEncoder);

				CFileHelper.WriteFileFromStream(@"..\..\..\!Packets1\Message.ftc",MS1);


				MemoryStream	MS2=CFileHelper.ReadFileToStream(@"..\..\..\!Packets1\Message.ftc");

				CFTCPacket		PacketIn=new CFTCPacket();

				PacketIn.ReadMessageWithEncoder(MS2,MMessageEncoder);

				// Headers mozem citat aj viac krat, lebo nezmeni stav M.
				string			Action=PacketIn.MessageHeaders.Action;
				// Body sa da citat iba raz, kedz zmeni stav M na Read a potom sa uz citat neda.
				string			Body=PacketIn.Message.GetBody<string>();

				Console.WriteLine(string.Format("Action: '{0}' !",Action));
				Console.WriteLine(string.Format("Body: '{0}' !",Body));
				Console.WriteLine(string.Format("SessionID: '{0}' !",PacketIn.SessionID.SessionID));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void FinishTryReceive(IAsyncResult Result)
		{
			CFTCTryReceiveAsyncResult	FTCAsyncResult=(CFTCTryReceiveAsyncResult) Result;
			CAsyncStatePair1			AsyncStatePair=(CAsyncStatePair1) FTCAsyncResult.AsyncState;
			Message						M;
			bool						HasMessage;

			HasMessage=AsyncStatePair.First.EndTryReceive(Result,out M);

			Console.WriteLine(string.Format("!!!!!! TryReceive RESPONSE: {0} !",AsyncStatePair.Second));
			Console.WriteLine(string.Format("RESULT: {0} !",HasMessage.ToString().ToUpper()));

			if (M!=null)
			{
				Console.WriteLine(string.Format("!!! MESSAGE: {0} !",M.ToString()));
				Console.WriteLine(string.Format("!!! MESSAGE-BODY: {0} !",M.GetBody<string>()));
			}
			else
			{
				Console.WriteLine("NO MESSAGE !");

				if (HasMessage==true)
				{
					// Close.
					for (int i=0;i<MChannels.Count;i++)
					{
						CTempChannel	TC=(CTempChannel) MChannels[i].First;

						if (TC.TRCT==AsyncStatePair.First)
						{
							TC.ShouldClose=true;
							break;
						}
					}
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void TryReceive()
		{
			try
			{
				CFTCSessionID				SessionID=new CFTCSessionID("XXX");
				CTryReceiveChannelThread	TRCT=new CTryReceiveChannelThread(SessionID,@"..\..\..\!Packets1",MMessageEncoder,null);

				Console.WriteLine("Press any key to START THREAD !");
				Console.ReadLine();

				TRCT.Start();
				Thread.Sleep(100);

				while(true)
				{
					Console.WriteLine();
					Console.WriteLine("Press any key: 'T' - TryReceive, 'M' - Message, 'B' - Begin Session message, 'E' - Exit Session message, 'C' - Clear screen, 'Enter' - Exit !");
					
					string					Input=Console.ReadLine();
					int						Count=1;

					if (Input.Length==0)
						break;

					char					Char=(Input.ToUpper())[0];

					if (Char!='T' && Char!='B' && Char!='M' && Char!='E' && Char!='C')
					{
						Console.WriteLine("INVALID COMMAND !");
						continue;
					}

					if (Char=='C')
					{
						Console.Clear();
					}
					else if (Char=='M')
					{
						string			FileID=CDebugHelper.GetIntID(6);
						Message			MOut=Message.CreateMessage(CSettings.MessageVersion,"Test Action",string.Format("Test Body {0} !!!",FileID));
						CFTCPacket		PacketOut=new CFTCPacket(DateTime.Now,new CFTCSessionID(),"Some Address",FileID,EMessageType.E_MT_MESSAGE,MOut);
						MemoryStream	MS=PacketOut.WriteMessageWithEncoder(MMessageEncoder);

						CFileHelper.WriteFileFromStream(string.Format(@"..\..\..\!Packets1\SESSION_XXX_{0}.ftc",FileID),MS);
					}
					else if (Char=='B')
					{
						string			FileID=CDebugHelper.GetIntID(6);
						Message			MOut=Message.CreateMessage(CSettings.MessageVersion,"Test Action",string.Format("Test Body {0} !!!",FileID));
						CFTCPacket		PacketOut=new CFTCPacket(DateTime.Now,new CFTCSessionID(),"Some Address",FileID,EMessageType.E_MT_START,MOut);
						MemoryStream	MS=PacketOut.WriteMessageWithEncoder(MMessageEncoder);

						CFileHelper.WriteFileFromStream(string.Format(@"..\..\..\!Packets1\SESSION_XXX_{0}.ftc",FileID),MS);
					}
					if (Char=='E')
					{
						string			FileID=CDebugHelper.GetIntID(6);
						Message			MOut=Message.CreateMessage(CSettings.MessageVersion,"Test Action",string.Format("Test Body {0} EXIT PACKET !!!",FileID));
						CFTCPacket		PacketOut=new CFTCPacket(DateTime.Now,new CFTCSessionID(),"Some Address",FileID,EMessageType.E_MT_STOP,MOut);
						MemoryStream	MS=PacketOut.WriteMessageWithEncoder(MMessageEncoder);

						CFileHelper.WriteFileFromStream(string.Format(@"..\..\..\!Packets1\SESSION_XXX_{0}.ftc",FileID),MS);
					}
					else if (Char=='T')
					{
						string				AsyncState=string.Format("TRY: {0}",Count++);
						CAsyncStatePair1	Pair=new CAsyncStatePair1(TRCT,AsyncState);

						TRCT.BeginTryReceive(TimeSpan.FromMinutes(10),Test.FinishTryReceive,Pair);
					}
				}

				Console.WriteLine("Press any key to STOP THREAD !");
				Console.ReadLine();

				TRCT.Stop();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void FinishAcceptChannel(IAsyncResult Result)
		{
			CFTCAcceptChannelAsyncResult	FTCAcceptChannelAsyncResult=(CFTCAcceptChannelAsyncResult) Result;
			CAsyncStatePair2				AsyncStatePair=(CAsyncStatePair2) FTCAcceptChannelAsyncResult.AsyncState;
			CTempChannelCreator				TempChannelCreator=new CTempChannelCreator(AsyncStatePair.First);
			IDuplexSessionChannel			Channel;

			Channel=AsyncStatePair.First.EndAcceptChannel(Result,TempChannelCreator);

			CChannelSessionPair				Pair=new CChannelSessionPair(Channel,FTCAcceptChannelAsyncResult.SessionID);

			Console.WriteLine(string.Format("!!!!!! Accept RESPONSE: {0} !",AsyncStatePair.Second));

			if (Channel!=null)
				MChannels.Add(Pair);
		}
//-------------------------------------------------------------------------------------------------------
		public static void AcceptChannel()
		{
			try
			{
				CChannelAcceptChannelThread	CACT=new CChannelAcceptChannelThread(@"..\..\..\!Packets1",TimeSpan.FromMilliseconds(10*1000),MMessageEncoder);

				Console.WriteLine("Press any key to START THREAD !");
				Console.ReadLine();

				CACT.Start();
				Thread.Sleep(100);

				while(true)
				{
					// Zistujem ci niektory CH sa nema skoncit - musim to dat tu kvoli deadlocku pri Close(), ktory vznikal ked som to dal do FinishTryReceive().
					for (int i=0;i<MChannels.Count;i++)
					{
						CTempChannel	TC=(CTempChannel) MChannels[i].First;

						if (TC.ShouldClose==true)
						{
							TC.Close(TimeSpan.Zero);
							MChannels.RemoveAt(i);
						}
					}

					Console.WriteLine();
					// !!!!!!!!! Ak sa ma skutocne uzavreit CH tak musim po EXIT SESSION packete dat este jeden prikaz - trebars Clear screen, kedze az potom sa kontroluje ci sa CH ukoncil a vola Close().
					// !!! CH je mozne ukoncit aj cez 'S' - Stop Channel.
					Console.WriteLine("Press any key: 'A' - Accept, 'M' - Message, 'B' - Begin Session message, 'E' - Exit Session message (insert one more command to close), 'L' - List Channels, 'R' - Start Channel, 'S' - Stop Channel, 'T' - TryReceive, 'C' - Clear screen, 'Enter' - Exit !");
					Console.WriteLine();
					
					string					Input=Console.ReadLine();
					int						Count=1;

					if (Input.Length==0)
						break;

					char					Char=(Input.ToUpper())[0];

					if (Char!='A' && Char!='M' && Char!='B' && Char!='E' && Char!='C' && Char!='L' && Char!='R' && Char!='S' && Char!='T')
					{
						Console.WriteLine("INVALID COMMAND !");
						continue;
					}

					if (Char=='C')
					{
						Console.Clear();
						continue;
					}
					if (Char=='L')
					{
						Console.WriteLine();

						for (int i=0;i<MChannels.Count;i++)
							Console.WriteLine(string.Format("{0}. '{1}' !",i+1,MChannels[i].Second.SessionID));

						Console.WriteLine();
						continue;
					}
					else if (Char=='A')
					{
						string				AsyncState=string.Format("TRY: {0}",Count++);
						CAsyncStatePair2	Pair=new CAsyncStatePair2(CACT,AsyncState);

						CACT.BeginAcceptChannel(TimeSpan.FromMinutes(10),Test.FinishAcceptChannel,Pair);
						continue;
					}

					string					SessionID;
					string					FileID=CDebugHelper.GetIntID(6);

					while(true)
					{
						Console.WriteLine("Write SESSION ID !");

						SessionID=Console.ReadLine();

						if (SessionID.Length==0)
							continue;
						else
							break;
					}

					if (Char=='M')
					{
						Message				MOut=Message.CreateMessage(CSettings.MessageVersion,"Test Action",string.Format("Test Body {0} !!!",FileID));
						CFTCPacket			PacketOut=new CFTCPacket(DateTime.Now,new CFTCSessionID(SessionID),"Some Address",FileID,EMessageType.E_MT_MESSAGE,MOut);
						MemoryStream		MS=PacketOut.WriteMessageWithEncoder(MMessageEncoder);

						CFileHelper.WriteFileFromStream(string.Format(@"..\..\..\!Packets1\PACKET_{0}.ftc",FileID),MS);
					}
					if (Char=='B')
					{
						Message				MOut=Message.CreateMessage(CSettings.MessageVersion,"Test Action",string.Format("Test Body {0} !!!",FileID));
						CFTCPacket			PacketOut=new CFTCPacket(DateTime.Now,new CFTCSessionID(SessionID),"Some Address",FileID,EMessageType.E_MT_START,MOut);
						MemoryStream		MS=PacketOut.WriteMessageWithEncoder(MMessageEncoder);

						CFileHelper.WriteFileFromStream(string.Format(@"..\..\..\!Packets1\PACKET_{0}.ftc",FileID),MS);
					}
					else if (Char=='E')
					{
						Message				MOut=Message.CreateMessage(CSettings.MessageVersion,"Test Action",string.Format("Test Body {0} EXIT PACKET !!!",FileID));
						CFTCPacket			PacketOut=new CFTCPacket(DateTime.Now,new CFTCSessionID(SessionID),"Some Address",FileID,EMessageType.E_MT_STOP,MOut);
						MemoryStream		MS=PacketOut.WriteMessageWithEncoder(MMessageEncoder);

						CFileHelper.WriteFileFromStream(string.Format(@"..\..\..\!Packets1\PACKET_{0}.ftc",FileID),MS);
					}
					else if (Char=='R')
					{
						bool		Found=false;

						for (int i=0;i<MChannels.Count;i++)
							if (MChannels[i].Second.CompareTo(new CFTCSessionID(SessionID))==true)
							{
								MChannels[i].First.Open(TimeSpan.Zero);
								Found=true;
								break;
							}

						if (Found==false)
							Console.WriteLine("CHANNEL DOESN'T EXIST !");
					}
					else if (Char=='S')
					{
						bool		Found=false;

						for (int i=0;i<MChannels.Count;i++)
							if (MChannels[i].Second.CompareTo(new CFTCSessionID(SessionID))==true)
							{
								MChannels[i].First.Close(TimeSpan.Zero);
								MChannels.RemoveAt(i);
								Found=true;
								break;
							}

						if (Found==false)
							Console.WriteLine("CHANNEL DOESN'T EXIST !");
					}
					else if (Char=='T')
					{
						bool		Found=false;

						for (int i=0;i<MChannels.Count;i++)
							if (MChannels[i].Second.CompareTo(new CFTCSessionID(SessionID))==true)
							{
								CTempChannel		TC=(CTempChannel) MChannels[i].First;
								string				AsyncState=string.Format("TRY: {0}",Count++);
								CAsyncStatePair1	Pair=new CAsyncStatePair1(TC.TRCT,AsyncState);

								TC.BeginTryReceive(TimeSpan.FromMinutes(10),Test.FinishTryReceive,Pair);

								Found=true;
								break;
							}

						if (Found==false)
							Console.WriteLine("CHANNEL DOESN'T EXIST !");
					}

					Count++;
				}

				Console.WriteLine("Press any key to STOP THREAD !");
				Console.ReadLine();

				CACT.Stop();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void Main(string[] Args)
		{
			Console.Title="Test";

			//MessageText();
			//TryReceive();
			AcceptChannel();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------