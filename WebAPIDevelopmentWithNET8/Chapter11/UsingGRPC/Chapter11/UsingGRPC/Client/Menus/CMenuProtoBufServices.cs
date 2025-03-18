using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Google.Protobuf;
using Grpc.Core;
using Grpc.Net.Client;
using MySharedLibrary;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuProtoBufServices : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuProtoBufServices()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static void CallServiceThread(object Parameter)
		{
			GrpcChannel									Channel=(GrpcChannel) Parameter;

			for(long Counter=0;Counter<2000;Counter++)
			{
				ParallelCalls.ParallelCallsClient				Client=new ParallelCalls.ParallelCallsClient(Channel);
				ParallelCallsRequest							Request=new ParallelCallsRequest();

				Client.ProcessParallelCalls(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static async Task ProcessServerStreamingResponseOK(IAsyncStreamReader<ServicesServerStreamingResponse> StreamReader)
		{
			await foreach(ServicesServerStreamingResponse Response in StreamReader.ReadAllAsync())
			{
				Console.WriteLine($"RESPONSE - COUNTER [{Response.Counter}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static async Task ProcessServerStreamingResponseCancel(IAsyncStreamReader<ServicesServerStreamingResponse> StreamReader, int Counter)
		{
			await foreach(ServicesServerStreamingResponse Response in StreamReader.ReadAllAsync())
			{
				Console.WriteLine($"RESPONSE - COUNTER [{Response.Counter}].");

				if (Counter==Response.Counter)
				{
					break;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static async Task ReadBidirectionalMessages(CancellationToken Token, IAsyncStreamReader<ServicesBidirectionalStreamingResponse> ResponseStream)
		{
			Console.WriteLine("READER TASK STARTED.");

			try
			{
				await foreach(ServicesBidirectionalStreamingResponse Response in ResponseStream.ReadAllAsync(Token))
				{
					Console.WriteLine($"RESPONSE - VALUE 1 [{Response.Value1}] VALUE 2 [{Response.Value2}].");
				}
			}
			catch(TaskCanceledException E)
			{
				Console.WriteLine($"MESSAGE READER was CANCELLED. EXCEPTION [{E.Message}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"READ MESSAGE EXCEPTION [{E.Message}].");
			}

			Console.WriteLine("READER TASK FINISHED.");
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSynchronousRequest(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				Names.NamesClient								Client=new Names.NamesClient(Channel);
				NamesRequest									Request=new NamesRequest();

				Request.FirstName="Timmy";
				Request.LastName="Anderson";
				Request.Age=12;

				NamesResponse									Response=Client.ProcessNames(Request);

				Console.WriteLine($"RESPONSE - RESPONSE MESSAGE [{Response.ResponseMessage}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandAsynchronousRequest(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				Names.NamesClient								Client=new Names.NamesClient(Channel);
				NamesRequest									Request=new NamesRequest();

				Request.FirstName="Timmy";
				Request.LastName="Anderson";
				Request.Age=12;

				AsyncUnaryCall<NamesResponse>					ResponseCall=Client.ProcessNamesAsync(Request);
				Task<NamesResponse>								ResponseTask=ResponseCall.ResponseAsync;
				NamesResponse									Response=ResponseTask.Result;

				Console.WriteLine($"RESPONSE - RESPONSE MESSAGE [{Response.ResponseMessage}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandScalarTypes(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				ScalarTypes.ScalarTypesClient					Client=new ScalarTypes.ScalarTypesClient(Channel);
				ScalarTypesRequest								Request=new ScalarTypesRequest();

				Request.FieldDouble=111.111;
				Request.FieldFloat=222.222f;
				Request.FieldInt32=100;
				Request.FieldInt64=-200;
				Request.FieldUInt32=300;
				Request.FieldUInt64=400;
				Request.FieldSInt32=-500;
				Request.FieldSInt64=600;
				Request.FieldFixed32=700;
				Request.FieldFixed64=800;
				Request.FieldSFixed32=-900;
				Request.FieldSFixed64=1000;
				Request.FieldBool=true;
				Request.FieldString="Some TEXT !!!";
				Request.FieldBytes=ByteString.CopyFromUtf8("Some BYTES.");

				ScalarTypesResponse								Response=Client.ProcessScalarTypes(Request);

				Console.WriteLine($"RESPONSE - RESPONSE MESSAGE [{Response.ResponseMessage}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandExtensionTypes(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				ExtensionTypes.ExtensionTypesClient				Client=new ExtensionTypes.ExtensionTypesClient(Channel);
				ExtensionTypesRequest							Request=new ExtensionTypesRequest();

				Request.FieldTimestamp=Google.Protobuf.WellKnownTypes.Timestamp.FromDateTime(new DateTime(10000000*40,DateTimeKind.Utc));
				Request.FieldDuration=Google.Protobuf.WellKnownTypes.Duration.FromTimeSpan(TimeSpan.FromSeconds(50));

				ExtensionTypesResponse							Response=Client.ProcessExtensionTypes(Request);

				Console.WriteLine($"RESPONSE - RESPONSE MESSAGE [{Response.ResponseMessage}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandEnumTypes(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				EnumTypes.EnumTypesClient						Client=new EnumTypes.EnumTypesClient(Channel);
				EnumTypesRequest								Request=new EnumTypesRequest();

				Request.Field1=UsingGRPC.MyEnum.EValue0;
				Request.Field2=UsingGRPC.MyEnum.EValue1;
				Request.Field3=UsingGRPC.MyEnum.EValue2;

				EnumTypesResponse								Response=Client.ProcessEnumTypes(Request);

				Console.WriteLine($"RESPONSE - RESPONSE MESSAGE [{Response.ResponseMessage}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandNullableTypes(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				NullableTypes.NullableTypesClient				Client=new NullableTypes.NullableTypesClient(Channel);
				NullableTypesRequest							Request=new NullableTypesRequest();

				Request.FieldDoubleValue=111.111;
				Request.FieldFloatValue=null;
				Request.FieldInt32Value=null;
				Request.FieldInt64Value=-200;
				Request.FieldUInt32Value=null;
				Request.FieldUInt64Value=400;
				Request.FieldBoolValue=null;
				Request.FieldStringValue=null;
				Request.FieldBytesValue=null;

				NullableTypesResponse							Response=Client.ProcessNullableTypes(Request);

				Console.WriteLine($"RESPONSE - RESPONSE MESSAGE [{Response.ResponseMessage}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRepeatedTypes(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				RepeatedTypes.RepeatedTypesClient				Client=new RepeatedTypes.RepeatedTypesClient(Channel);
				RepeatedTypesRequest							Request=new RepeatedTypesRequest();

				Request.NoRepeatedField=123;
				Request.RepeatedField1.Add(new int[]{100,200,300,400});
				Request.RepeatedField2.Add(new string[]{"Timmy","Jenny","Josh"});

				RepeatedTypesResponse							Response=Client.ProcessRepeatedTypes(Request);

				Console.WriteLine($"RESPONSE - RESPONSE MESSAGE [{Response.ResponseMessage}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandMapTypes(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				MapTypes.MapTypesClient							Client=new MapTypes.MapTypesClient(Channel);
				MapTypesRequest									Request=new MapTypesRequest();

				Request.NoMapField=123;

				Request.MapField1.Add(100,"VALUE 100");
				Request.MapField1.Add(200,"VALUE 200");
				Request.MapField1.Add(300,"VALUE 200");

				{
					MapTypesValueType							Value=new MapTypesValueType();

					Value.FieldInt=11;
					Value.FieldString="VALUE 11";

					Request.MapField2.Add(1000,Value);
				}

				{
					MapTypesValueType							Value=new MapTypesValueType();

					Value.FieldInt=12;
					Value.FieldString="VALUE 12";

					Request.MapField2.Add(2000,Value);
				}

				{
					MapTypesValueType							Value=new MapTypesValueType();

					Value.FieldInt=13;
					Value.FieldString="VALUE 13";

					Request.MapField2.Add(3000,Value);
				}

				MapTypesResponse								Response=Client.ProcessMapTypes(Request);

				Console.WriteLine($"RESPONSE - RESPONSE MESSAGE [{Response.ResponseMessage}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandParallelCalls(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				Thread											Thread1=new Thread(CallServiceThread);
				Thread											Thread2=new Thread(CallServiceThread);

				Thread1.Start(Channel);
				Thread2.Start(Channel);

				Thread1.Join();
				Thread2.Join();

				ParallelCalls.ParallelCallsClient				Client=new ParallelCalls.ParallelCallsClient(Channel);
				ParallelCallsResultRequest						Request=new ParallelCallsResultRequest();
				ParallelCallsResultResponse						Response=Client.ProcessParallelCallsResult(Request);

				Console.WriteLine($"COUNTER [{Response.Counter}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUnaryService(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				{
					ServicesUnary.ServicesUnaryClient			Client=new ServicesUnary.ServicesUnaryClient(Channel);
					ServicesUnaryRequest						Request=new ServicesUnaryRequest();

					Request.Field1="Timmy";
					Request.Field2="Anderson";
					Request.Field3=12;

					ServicesUnaryResponse						Response=Client.ProcessServicesUnary1(Request);

					Console.WriteLine($"RESPONSE - FIELD 1 [{Response.Field1}] FIELD 2 [{Response.Field2}].");
				}

				{
					ServicesUnary.ServicesUnaryClient			Client=new ServicesUnary.ServicesUnaryClient(Channel);
					ServicesUnaryRequest						Request=new ServicesUnaryRequest();

					Request.Field1="Lucas";
					Request.Field2="Jones";
					Request.Field3=13;

					ServicesUnaryResponse						Response=Client.ProcessServicesUnary2(Request);

					Console.WriteLine($"RESPONSE - FIELD 1 [{Response.Field1}] FIELD 2 [{Response.Field2}].");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandServerStreamingServiceOK(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				ServicesServerStreaming.ServicesServerStreamingClient	Client=new ServicesServerStreaming.ServicesServerStreamingClient(Channel);
				ServicesServerStreamingRequest					Request=new ServicesServerStreamingRequest();

				Request.NumberOfMessages=10;
				Request.Delay=1000;

				using(AsyncServerStreamingCall<ServicesServerStreamingResponse> StreamingCall=Client.ProcessServicesServerStreaming(Request))
				{
					IAsyncStreamReader<ServicesServerStreamingResponse>	StreamReader=StreamingCall.ResponseStream;

					ProcessServerStreamingResponseOK(StreamReader).Wait();
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandServerStreamingServiceCancel(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				ServicesServerStreaming.ServicesServerStreamingClient	Client=new ServicesServerStreaming.ServicesServerStreamingClient(Channel);
				ServicesServerStreamingRequest					Request=new ServicesServerStreamingRequest();

				Request.NumberOfMessages=10;
				Request.Delay=1000;

				// !!!!! Predcasne volanie METHOD [AsyncServerStreamingCall<ServicesServerStreamingResponse>.Dispose()] sposobi ukoncenie SERVER STREAMING.
				using(AsyncServerStreamingCall<ServicesServerStreamingResponse> StreamingCall=Client.ProcessServicesServerStreaming(Request))
				{
					IAsyncStreamReader<ServicesServerStreamingResponse>	StreamReader=StreamingCall.ResponseStream;

					ProcessServerStreamingResponseCancel(StreamReader,5).Wait();
				}

				Console.WriteLine("REQUEST was CANCELLED. Press any KEY.");
				Console.ReadLine();
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandClientStreamingService(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				ServicesClientStreaming.ServicesClientStreamingClient	Client=new ServicesClientStreaming.ServicesClientStreamingClient(Channel);

				// !!! Spusti sa CLIENT STREAMING.
				using(AsyncClientStreamingCall<ServicesClientStreamingRequest,ServicesClientStreamingResponse>	StreamingCall=Client.ProcessServicesClientStreaming())
				{
					IClientStreamWriter<ServicesClientStreamingRequest>	Stream=StreamingCall.RequestStream;
					
					for(int Index=0;Index<10;Index++)
					{
						ServicesClientStreamingRequest			Message=new ServicesClientStreamingRequest();

						Message.Value=(Index+1);

						Console.WriteLine($"SENDING MESSAGE with VALUE [{Message.Value}].");

						// !!! MESSAGE sa odosle na SERVER.
						Stream.WriteAsync(Message).Wait();

						Thread.Sleep(1000);
					}

					Console.WriteLine($"SENDING COMPLETE MESSAGE.");

					// !!!!! CLIENT signalizuje SERVERU ukoncenie odosielania MESSAGES.
					Stream.CompleteAsync().Wait();

					Console.WriteLine($"WAITING for RESPONSE MESSAGE.");

					// !!! Nacita sa RESPONSE zo SERVER.
					ServicesClientStreamingResponse				Response=StreamingCall.GetAwaiter().GetResult();

					Console.WriteLine($"RESPONSE - MESSAGE [{Response.Message}].");
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandBidirectionalStreamingService(string CommandID, object[] Parameters)
		{
			int													Value=0;

			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				ServicesBidirectionalStreaming.ServicesBidirectionalStreamingClient	Client=new ServicesBidirectionalStreaming.ServicesBidirectionalStreamingClient(Channel);

				// !!! Spusti sa STREAMING.
				using(AsyncDuplexStreamingCall<ServicesBidirectionalStreamingRequest,ServicesBidirectionalStreamingResponse> StreamingCall=Client.ProcessServicesBidirectionalStreaming())
				{
					IClientStreamWriter<ServicesBidirectionalStreamingRequest>	RequestStream=StreamingCall.RequestStream;
					IAsyncStreamReader<ServicesBidirectionalStreamingResponse>	ResponseStream=StreamingCall.ResponseStream;
					CancellationTokenSource						CancellationTokenSource=new CancellationTokenSource();
					Task										ReaderTask=Task.Run(() => ReadBidirectionalMessages(CancellationTokenSource.Token,ResponseStream).Wait());

					for(int Index=0;Index<10;Index++)
					{
						Thread.Sleep(1000);

						ServicesBidirectionalStreamingRequest	Request=new ServicesBidirectionalStreamingRequest();

						Request.Value=++Value;

						RequestStream.WriteAsync(Request).Wait();
					}

					CancellationTokenSource.Cancel();

					ReaderTask.Wait();

					// !!!!! CLIENT signalizuje SERVERU ukoncenie odosielania MESSAGES.
					RequestStream.CompleteAsync().Wait();
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandReservedFields(string CommandID, object[] Parameters)
		{
			using(GrpcChannel Channel=GrpcChannel.ForAddress(BASE_ADDRESS))
			{
				ReservedFields.ReservedFieldsClient				Client=new ReservedFields.ReservedFieldsClient(Channel);
				ReservedFieldsRequest							Request=new ReservedFieldsRequest();

				Request.Field1="Timmy";
				Request.Field2="Anderson";
				Request.Field3=12;

				ReservedFieldsResponse							Response=Client.ProcessReservedFields(Request);

				Console.WriteLine($"RESPONSE - FIELD 1 [{Response.Field1}] FIELD 2 [{Response.Field2}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","SYNCHRONOUS REQUEST",new EMenuCommandParameterType[0],ExecuteCommandSynchronousRequest));
			CommandsCollection.Add(new CMenuCommand("2","ASYNCHRONOUS REQUEST",new EMenuCommandParameterType[0],ExecuteCommandAsynchronousRequest));
			CommandsCollection.Add(new CMenuCommand("3","SCALAR TYPES",new EMenuCommandParameterType[0],ExecuteCommandScalarTypes));
			CommandsCollection.Add(new CMenuCommand("4","EXTENSION TYPES",new EMenuCommandParameterType[0],ExecuteCommandExtensionTypes));
			CommandsCollection.Add(new CMenuCommand("5","ENUM TYPES",new EMenuCommandParameterType[0],ExecuteCommandEnumTypes));
			CommandsCollection.Add(new CMenuCommand("6","NULLABLE TYPES",new EMenuCommandParameterType[0],ExecuteCommandNullableTypes));
			CommandsCollection.Add(new CMenuCommand("7","REPEATED TYPES",new EMenuCommandParameterType[0],ExecuteCommandRepeatedTypes));
			CommandsCollection.Add(new CMenuCommand("8","MAP TYPES",new EMenuCommandParameterType[0],ExecuteCommandMapTypes));
			CommandsCollection.Add(new CMenuCommand("9","PARALLEL CALLS",new EMenuCommandParameterType[0],ExecuteCommandParallelCalls));
			CommandsCollection.Add(new CMenuCommand("10","UNARY SERVICE",new EMenuCommandParameterType[0],ExecuteCommandUnaryService));
			CommandsCollection.Add(new CMenuCommand("11","SERVER STREAMING SERVICE OK",new EMenuCommandParameterType[0],ExecuteCommandServerStreamingServiceOK));
			CommandsCollection.Add(new CMenuCommand("12","SERVER STREAMING SERVICE CANCEL",new EMenuCommandParameterType[0],ExecuteCommandServerStreamingServiceCancel));
			CommandsCollection.Add(new CMenuCommand("13","CLIENT STREAMING SERVICE",new EMenuCommandParameterType[0],ExecuteCommandClientStreamingService));
			CommandsCollection.Add(new CMenuCommand("14","BIDIRECTIONAL STREAMING SERVICE",new EMenuCommandParameterType[0],ExecuteCommandBidirectionalStreamingService));
			CommandsCollection.Add(new CMenuCommand("15","RESERVED FIELDS",new EMenuCommandParameterType[0],ExecuteCommandReservedFields));


			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------