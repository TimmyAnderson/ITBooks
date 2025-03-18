// <auto-generated>
//     Generated by the protocol buffer compiler.  DO NOT EDIT!
//     source: Protos/ServicesUnary.proto
// </auto-generated>
// Original file comments:
// --------------------------------------------------------------------------------------------------------------------------------
#pragma warning disable 0414, 1591, 8981, 0612
#region Designer generated code

using grpc = global::Grpc.Core;

namespace UsingGRPC {
  /// <summary>
  ///--------------------------------------------------------------------------------------------------------------------------------
  ///--------------------------------------------------------------------------------------------------------------------------------
  ///--------------------------------------------------------------------------------------------------------------------------------
  /// </summary>
  public static partial class ServicesUnary
  {
    static readonly string __ServiceName = "UsingGRPCPackage.ServicesUnary";

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static void __Helper_SerializeMessage(global::Google.Protobuf.IMessage message, grpc::SerializationContext context)
    {
      #if !GRPC_DISABLE_PROTOBUF_BUFFER_SERIALIZATION
      if (message is global::Google.Protobuf.IBufferMessage)
      {
        context.SetPayloadLength(message.CalculateSize());
        global::Google.Protobuf.MessageExtensions.WriteTo(message, context.GetBufferWriter());
        context.Complete();
        return;
      }
      #endif
      context.Complete(global::Google.Protobuf.MessageExtensions.ToByteArray(message));
    }

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static class __Helper_MessageCache<T>
    {
      public static readonly bool IsBufferMessage = global::System.Reflection.IntrospectionExtensions.GetTypeInfo(typeof(global::Google.Protobuf.IBufferMessage)).IsAssignableFrom(typeof(T));
    }

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static T __Helper_DeserializeMessage<T>(grpc::DeserializationContext context, global::Google.Protobuf.MessageParser<T> parser) where T : global::Google.Protobuf.IMessage<T>
    {
      #if !GRPC_DISABLE_PROTOBUF_BUFFER_SERIALIZATION
      if (__Helper_MessageCache<T>.IsBufferMessage)
      {
        return parser.ParseFrom(context.PayloadAsReadOnlySequence());
      }
      #endif
      return parser.ParseFrom(context.PayloadAsNewBuffer());
    }

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static readonly grpc::Marshaller<global::UsingGRPC.ServicesUnaryRequest> __Marshaller_UsingGRPCPackage_ServicesUnaryRequest = grpc::Marshallers.Create(__Helper_SerializeMessage, context => __Helper_DeserializeMessage(context, global::UsingGRPC.ServicesUnaryRequest.Parser));
    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static readonly grpc::Marshaller<global::UsingGRPC.ServicesUnaryResponse> __Marshaller_UsingGRPCPackage_ServicesUnaryResponse = grpc::Marshallers.Create(__Helper_SerializeMessage, context => __Helper_DeserializeMessage(context, global::UsingGRPC.ServicesUnaryResponse.Parser));

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static readonly grpc::Method<global::UsingGRPC.ServicesUnaryRequest, global::UsingGRPC.ServicesUnaryResponse> __Method_ProcessServicesUnary1 = new grpc::Method<global::UsingGRPC.ServicesUnaryRequest, global::UsingGRPC.ServicesUnaryResponse>(
        grpc::MethodType.Unary,
        __ServiceName,
        "ProcessServicesUnary1",
        __Marshaller_UsingGRPCPackage_ServicesUnaryRequest,
        __Marshaller_UsingGRPCPackage_ServicesUnaryResponse);

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static readonly grpc::Method<global::UsingGRPC.ServicesUnaryRequest, global::UsingGRPC.ServicesUnaryResponse> __Method_ProcessServicesUnary2 = new grpc::Method<global::UsingGRPC.ServicesUnaryRequest, global::UsingGRPC.ServicesUnaryResponse>(
        grpc::MethodType.Unary,
        __ServiceName,
        "ProcessServicesUnary2",
        __Marshaller_UsingGRPCPackage_ServicesUnaryRequest,
        __Marshaller_UsingGRPCPackage_ServicesUnaryResponse);

    /// <summary>Service descriptor</summary>
    public static global::Google.Protobuf.Reflection.ServiceDescriptor Descriptor
    {
      get { return global::UsingGRPC.ServicesUnaryReflection.Descriptor.Services[0]; }
    }

    /// <summary>Client for ServicesUnary</summary>
    public partial class ServicesUnaryClient : grpc::ClientBase<ServicesUnaryClient>
    {
      /// <summary>Creates a new client for ServicesUnary</summary>
      /// <param name="channel">The channel to use to make remote calls.</param>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public ServicesUnaryClient(grpc::ChannelBase channel) : base(channel)
      {
      }
      /// <summary>Creates a new client for ServicesUnary that uses a custom <c>CallInvoker</c>.</summary>
      /// <param name="callInvoker">The callInvoker to use to make remote calls.</param>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public ServicesUnaryClient(grpc::CallInvoker callInvoker) : base(callInvoker)
      {
      }
      /// <summary>Protected parameterless constructor to allow creation of test doubles.</summary>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      protected ServicesUnaryClient() : base()
      {
      }
      /// <summary>Protected constructor to allow creation of configured clients.</summary>
      /// <param name="configuration">The client configuration.</param>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      protected ServicesUnaryClient(ClientBaseConfiguration configuration) : base(configuration)
      {
      }

      /// <summary>
      ///--------------------------------------------------------------------------------------------------------------------------------
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The response received from the server.</returns>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual global::UsingGRPC.ServicesUnaryResponse ProcessServicesUnary1(global::UsingGRPC.ServicesUnaryRequest request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return ProcessServicesUnary1(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      ///--------------------------------------------------------------------------------------------------------------------------------
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The response received from the server.</returns>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual global::UsingGRPC.ServicesUnaryResponse ProcessServicesUnary1(global::UsingGRPC.ServicesUnaryRequest request, grpc::CallOptions options)
      {
        return CallInvoker.BlockingUnaryCall(__Method_ProcessServicesUnary1, null, options, request);
      }
      /// <summary>
      ///--------------------------------------------------------------------------------------------------------------------------------
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual grpc::AsyncUnaryCall<global::UsingGRPC.ServicesUnaryResponse> ProcessServicesUnary1Async(global::UsingGRPC.ServicesUnaryRequest request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return ProcessServicesUnary1Async(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      ///--------------------------------------------------------------------------------------------------------------------------------
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual grpc::AsyncUnaryCall<global::UsingGRPC.ServicesUnaryResponse> ProcessServicesUnary1Async(global::UsingGRPC.ServicesUnaryRequest request, grpc::CallOptions options)
      {
        return CallInvoker.AsyncUnaryCall(__Method_ProcessServicesUnary1, null, options, request);
      }
      /// <summary>
      ///--------------------------------------------------------------------------------------------------------------------------------
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The response received from the server.</returns>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual global::UsingGRPC.ServicesUnaryResponse ProcessServicesUnary2(global::UsingGRPC.ServicesUnaryRequest request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return ProcessServicesUnary2(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      ///--------------------------------------------------------------------------------------------------------------------------------
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The response received from the server.</returns>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual global::UsingGRPC.ServicesUnaryResponse ProcessServicesUnary2(global::UsingGRPC.ServicesUnaryRequest request, grpc::CallOptions options)
      {
        return CallInvoker.BlockingUnaryCall(__Method_ProcessServicesUnary2, null, options, request);
      }
      /// <summary>
      ///--------------------------------------------------------------------------------------------------------------------------------
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="headers">The initial metadata to send with the call. This parameter is optional.</param>
      /// <param name="deadline">An optional deadline for the call. The call will be cancelled if deadline is hit.</param>
      /// <param name="cancellationToken">An optional token for canceling the call.</param>
      /// <returns>The call object.</returns>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual grpc::AsyncUnaryCall<global::UsingGRPC.ServicesUnaryResponse> ProcessServicesUnary2Async(global::UsingGRPC.ServicesUnaryRequest request, grpc::Metadata headers = null, global::System.DateTime? deadline = null, global::System.Threading.CancellationToken cancellationToken = default(global::System.Threading.CancellationToken))
      {
        return ProcessServicesUnary2Async(request, new grpc::CallOptions(headers, deadline, cancellationToken));
      }
      /// <summary>
      ///--------------------------------------------------------------------------------------------------------------------------------
      /// </summary>
      /// <param name="request">The request to send to the server.</param>
      /// <param name="options">The options for the call.</param>
      /// <returns>The call object.</returns>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual grpc::AsyncUnaryCall<global::UsingGRPC.ServicesUnaryResponse> ProcessServicesUnary2Async(global::UsingGRPC.ServicesUnaryRequest request, grpc::CallOptions options)
      {
        return CallInvoker.AsyncUnaryCall(__Method_ProcessServicesUnary2, null, options, request);
      }
      /// <summary>Creates a new instance of client from given <c>ClientBaseConfiguration</c>.</summary>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      protected override ServicesUnaryClient NewInstance(ClientBaseConfiguration configuration)
      {
        return new ServicesUnaryClient(configuration);
      }
    }

  }
}
#endregion
