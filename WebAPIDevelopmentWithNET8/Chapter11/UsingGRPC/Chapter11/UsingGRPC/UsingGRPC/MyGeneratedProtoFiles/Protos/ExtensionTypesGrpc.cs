// <auto-generated>
//     Generated by the protocol buffer compiler.  DO NOT EDIT!
//     source: Protos/ExtensionTypes.proto
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
  public static partial class ExtensionTypes
  {
    static readonly string __ServiceName = "UsingGRPCPackage.ExtensionTypes";

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
    static readonly grpc::Marshaller<global::UsingGRPC.ExtensionTypesRequest> __Marshaller_UsingGRPCPackage_ExtensionTypesRequest = grpc::Marshallers.Create(__Helper_SerializeMessage, context => __Helper_DeserializeMessage(context, global::UsingGRPC.ExtensionTypesRequest.Parser));
    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static readonly grpc::Marshaller<global::UsingGRPC.ExtensionTypesResponse> __Marshaller_UsingGRPCPackage_ExtensionTypesResponse = grpc::Marshallers.Create(__Helper_SerializeMessage, context => __Helper_DeserializeMessage(context, global::UsingGRPC.ExtensionTypesResponse.Parser));

    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    static readonly grpc::Method<global::UsingGRPC.ExtensionTypesRequest, global::UsingGRPC.ExtensionTypesResponse> __Method_ProcessExtensionTypes = new grpc::Method<global::UsingGRPC.ExtensionTypesRequest, global::UsingGRPC.ExtensionTypesResponse>(
        grpc::MethodType.Unary,
        __ServiceName,
        "ProcessExtensionTypes",
        __Marshaller_UsingGRPCPackage_ExtensionTypesRequest,
        __Marshaller_UsingGRPCPackage_ExtensionTypesResponse);

    /// <summary>Service descriptor</summary>
    public static global::Google.Protobuf.Reflection.ServiceDescriptor Descriptor
    {
      get { return global::UsingGRPC.ExtensionTypesReflection.Descriptor.Services[0]; }
    }

    /// <summary>Base class for server-side implementations of ExtensionTypes</summary>
    [grpc::BindServiceMethod(typeof(ExtensionTypes), "BindService")]
    public abstract partial class ExtensionTypesBase
    {
      /// <summary>
      ///--------------------------------------------------------------------------------------------------------------------------------
      /// </summary>
      /// <param name="request">The request received from the client.</param>
      /// <param name="context">The context of the server-side call handler being invoked.</param>
      /// <returns>The response to send back to the client (wrapped by a task).</returns>
      [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
      public virtual global::System.Threading.Tasks.Task<global::UsingGRPC.ExtensionTypesResponse> ProcessExtensionTypes(global::UsingGRPC.ExtensionTypesRequest request, grpc::ServerCallContext context)
      {
        throw new grpc::RpcException(new grpc::Status(grpc::StatusCode.Unimplemented, ""));
      }

    }

    /// <summary>Creates service definition that can be registered with a server</summary>
    /// <param name="serviceImpl">An object implementing the server-side handling logic.</param>
    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    public static grpc::ServerServiceDefinition BindService(ExtensionTypesBase serviceImpl)
    {
      return grpc::ServerServiceDefinition.CreateBuilder()
          .AddMethod(__Method_ProcessExtensionTypes, serviceImpl.ProcessExtensionTypes).Build();
    }

    /// <summary>Register service method with a service binder with or without implementation. Useful when customizing the service binding logic.
    /// Note: this method is part of an experimental API that can change or be removed without any prior notice.</summary>
    /// <param name="serviceBinder">Service methods will be bound by calling <c>AddMethod</c> on this object.</param>
    /// <param name="serviceImpl">An object implementing the server-side handling logic.</param>
    [global::System.CodeDom.Compiler.GeneratedCode("grpc_csharp_plugin", null)]
    public static void BindService(grpc::ServiceBinderBase serviceBinder, ExtensionTypesBase serviceImpl)
    {
      serviceBinder.AddMethod(__Method_ProcessExtensionTypes, serviceImpl == null ? null : new grpc::UnaryServerMethod<global::UsingGRPC.ExtensionTypesRequest, global::UsingGRPC.ExtensionTypesResponse>(serviceImpl.ProcessExtensionTypes));
    }

  }
}
#endregion
