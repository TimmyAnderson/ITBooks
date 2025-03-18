// <auto-generated>
//     Generated by the protocol buffer compiler.  DO NOT EDIT!
//     source: Protos/EnumTypes.proto
// </auto-generated>
#pragma warning disable 1591, 0612, 3021, 8981
#region Designer generated code

using pb = global::Google.Protobuf;
using pbc = global::Google.Protobuf.Collections;
using pbr = global::Google.Protobuf.Reflection;
using scg = global::System.Collections.Generic;
namespace UsingGRPC {

  /// <summary>Holder for reflection information generated from Protos/EnumTypes.proto</summary>
  public static partial class EnumTypesReflection {

    #region Descriptor
    /// <summary>File descriptor for Protos/EnumTypes.proto</summary>
    public static pbr::FileDescriptor Descriptor {
      get { return descriptor; }
    }
    private static pbr::FileDescriptor descriptor;

    static EnumTypesReflection() {
      byte[] descriptorData = global::System.Convert.FromBase64String(
          string.Concat(
            "ChZQcm90b3MvRW51bVR5cGVzLnByb3RvEhBVc2luZ0dSUENQYWNrYWdlIpAB",
            "ChBFbnVtVHlwZXNSZXF1ZXN0EigKBkZpZWxkMRgBIAEoDjIYLlVzaW5nR1JQ",
            "Q1BhY2thZ2UuTXlFbnVtEigKBkZpZWxkMhgCIAEoDjIYLlVzaW5nR1JQQ1Bh",
            "Y2thZ2UuTXlFbnVtEigKBkZpZWxkMxgDIAEoDjIYLlVzaW5nR1JQQ1BhY2th",
            "Z2UuTXlFbnVtIiwKEUVudW1UeXBlc1Jlc3BvbnNlEhcKD1Jlc3BvbnNlTWVz",
            "c2FnZRgBIAEoCSo1CgZNeUVudW0SDQoJRV9WQUxVRV8wEAASDQoJRV9WQUxV",
            "RV8xEAESDQoJRV9WQUxVRV8yEAIyaAoJRW51bVR5cGVzElsKEFByb2Nlc3NF",
            "bnVtVHlwZXMSIi5Vc2luZ0dSUENQYWNrYWdlLkVudW1UeXBlc1JlcXVlc3Qa",
            "Iy5Vc2luZ0dSUENQYWNrYWdlLkVudW1UeXBlc1Jlc3BvbnNlQgyqAglVc2lu",
            "Z0dSUENiBnByb3RvMw=="));
      descriptor = pbr::FileDescriptor.FromGeneratedCode(descriptorData,
          new pbr::FileDescriptor[] { },
          new pbr::GeneratedClrTypeInfo(new[] {typeof(global::UsingGRPC.MyEnum), }, null, new pbr::GeneratedClrTypeInfo[] {
            new pbr::GeneratedClrTypeInfo(typeof(global::UsingGRPC.EnumTypesRequest), global::UsingGRPC.EnumTypesRequest.Parser, new[]{ "Field1", "Field2", "Field3" }, null, null, null, null),
            new pbr::GeneratedClrTypeInfo(typeof(global::UsingGRPC.EnumTypesResponse), global::UsingGRPC.EnumTypesResponse.Parser, new[]{ "ResponseMessage" }, null, null, null, null)
          }));
    }
    #endregion

  }
  #region Enums
  /// <summary>
  ///--------------------------------------------------------------------------------------------------------------------------------
  ///--------------------------------------------------------------------------------------------------------------------------------
  ///--------------------------------------------------------------------------------------------------------------------------------
  /// </summary>
  public enum MyEnum {
    [pbr::OriginalName("E_VALUE_0")] EValue0 = 0,
    [pbr::OriginalName("E_VALUE_1")] EValue1 = 1,
    [pbr::OriginalName("E_VALUE_2")] EValue2 = 2,
  }

  #endregion

  #region Messages
  /// <summary>
  ///--------------------------------------------------------------------------------------------------------------------------------
  ///--------------------------------------------------------------------------------------------------------------------------------
  ///--------------------------------------------------------------------------------------------------------------------------------
  /// </summary>
  [global::System.Diagnostics.DebuggerDisplayAttribute("{ToString(),nq}")]
  public sealed partial class EnumTypesRequest : pb::IMessage<EnumTypesRequest>
  #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      , pb::IBufferMessage
  #endif
  {
    private static readonly pb::MessageParser<EnumTypesRequest> _parser = new pb::MessageParser<EnumTypesRequest>(() => new EnumTypesRequest());
    private pb::UnknownFieldSet _unknownFields;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pb::MessageParser<EnumTypesRequest> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::UsingGRPC.EnumTypesReflection.Descriptor.MessageTypes[0]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public EnumTypesRequest() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public EnumTypesRequest(EnumTypesRequest other) : this() {
      field1_ = other.field1_;
      field2_ = other.field2_;
      field3_ = other.field3_;
      _unknownFields = pb::UnknownFieldSet.Clone(other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public EnumTypesRequest Clone() {
      return new EnumTypesRequest(this);
    }

    /// <summary>Field number for the "Field1" field.</summary>
    public const int Field1FieldNumber = 1;
    private global::UsingGRPC.MyEnum field1_ = global::UsingGRPC.MyEnum.EValue0;
    /// <summary>
    ///--------------------------------------------------------------------------------------------------------------------------------
    /// </summary>
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public global::UsingGRPC.MyEnum Field1 {
      get { return field1_; }
      set {
        field1_ = value;
      }
    }

    /// <summary>Field number for the "Field2" field.</summary>
    public const int Field2FieldNumber = 2;
    private global::UsingGRPC.MyEnum field2_ = global::UsingGRPC.MyEnum.EValue0;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public global::UsingGRPC.MyEnum Field2 {
      get { return field2_; }
      set {
        field2_ = value;
      }
    }

    /// <summary>Field number for the "Field3" field.</summary>
    public const int Field3FieldNumber = 3;
    private global::UsingGRPC.MyEnum field3_ = global::UsingGRPC.MyEnum.EValue0;
    /// <summary>
    ///--------------------------------------------------------------------------------------------------------------------------------
    /// </summary>
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public global::UsingGRPC.MyEnum Field3 {
      get { return field3_; }
      set {
        field3_ = value;
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override bool Equals(object other) {
      return Equals(other as EnumTypesRequest);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public bool Equals(EnumTypesRequest other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (Field1 != other.Field1) return false;
      if (Field2 != other.Field2) return false;
      if (Field3 != other.Field3) return false;
      return Equals(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override int GetHashCode() {
      int hash = 1;
      if (Field1 != global::UsingGRPC.MyEnum.EValue0) hash ^= Field1.GetHashCode();
      if (Field2 != global::UsingGRPC.MyEnum.EValue0) hash ^= Field2.GetHashCode();
      if (Field3 != global::UsingGRPC.MyEnum.EValue0) hash ^= Field3.GetHashCode();
      if (_unknownFields != null) {
        hash ^= _unknownFields.GetHashCode();
      }
      return hash;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override string ToString() {
      return pb::JsonFormatter.ToDiagnosticString(this);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void WriteTo(pb::CodedOutputStream output) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      output.WriteRawMessage(this);
    #else
      if (Field1 != global::UsingGRPC.MyEnum.EValue0) {
        output.WriteRawTag(8);
        output.WriteEnum((int) Field1);
      }
      if (Field2 != global::UsingGRPC.MyEnum.EValue0) {
        output.WriteRawTag(16);
        output.WriteEnum((int) Field2);
      }
      if (Field3 != global::UsingGRPC.MyEnum.EValue0) {
        output.WriteRawTag(24);
        output.WriteEnum((int) Field3);
      }
      if (_unknownFields != null) {
        _unknownFields.WriteTo(output);
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalWriteTo(ref pb::WriteContext output) {
      if (Field1 != global::UsingGRPC.MyEnum.EValue0) {
        output.WriteRawTag(8);
        output.WriteEnum((int) Field1);
      }
      if (Field2 != global::UsingGRPC.MyEnum.EValue0) {
        output.WriteRawTag(16);
        output.WriteEnum((int) Field2);
      }
      if (Field3 != global::UsingGRPC.MyEnum.EValue0) {
        output.WriteRawTag(24);
        output.WriteEnum((int) Field3);
      }
      if (_unknownFields != null) {
        _unknownFields.WriteTo(ref output);
      }
    }
    #endif

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int CalculateSize() {
      int size = 0;
      if (Field1 != global::UsingGRPC.MyEnum.EValue0) {
        size += 1 + pb::CodedOutputStream.ComputeEnumSize((int) Field1);
      }
      if (Field2 != global::UsingGRPC.MyEnum.EValue0) {
        size += 1 + pb::CodedOutputStream.ComputeEnumSize((int) Field2);
      }
      if (Field3 != global::UsingGRPC.MyEnum.EValue0) {
        size += 1 + pb::CodedOutputStream.ComputeEnumSize((int) Field3);
      }
      if (_unknownFields != null) {
        size += _unknownFields.CalculateSize();
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(EnumTypesRequest other) {
      if (other == null) {
        return;
      }
      if (other.Field1 != global::UsingGRPC.MyEnum.EValue0) {
        Field1 = other.Field1;
      }
      if (other.Field2 != global::UsingGRPC.MyEnum.EValue0) {
        Field2 = other.Field2;
      }
      if (other.Field3 != global::UsingGRPC.MyEnum.EValue0) {
        Field3 = other.Field3;
      }
      _unknownFields = pb::UnknownFieldSet.MergeFrom(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(pb::CodedInputStream input) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      input.ReadRawMessage(this);
    #else
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
      if ((tag & 7) == 4) {
        // Abort on any end group tag.
        return;
      }
      switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, input);
            break;
          case 8: {
            Field1 = (global::UsingGRPC.MyEnum) input.ReadEnum();
            break;
          }
          case 16: {
            Field2 = (global::UsingGRPC.MyEnum) input.ReadEnum();
            break;
          }
          case 24: {
            Field3 = (global::UsingGRPC.MyEnum) input.ReadEnum();
            break;
          }
        }
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalMergeFrom(ref pb::ParseContext input) {
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
      if ((tag & 7) == 4) {
        // Abort on any end group tag.
        return;
      }
      switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, ref input);
            break;
          case 8: {
            Field1 = (global::UsingGRPC.MyEnum) input.ReadEnum();
            break;
          }
          case 16: {
            Field2 = (global::UsingGRPC.MyEnum) input.ReadEnum();
            break;
          }
          case 24: {
            Field3 = (global::UsingGRPC.MyEnum) input.ReadEnum();
            break;
          }
        }
      }
    }
    #endif

  }

  /// <summary>
  ///--------------------------------------------------------------------------------------------------------------------------------
  ///--------------------------------------------------------------------------------------------------------------------------------
  ///--------------------------------------------------------------------------------------------------------------------------------
  /// </summary>
  [global::System.Diagnostics.DebuggerDisplayAttribute("{ToString(),nq}")]
  public sealed partial class EnumTypesResponse : pb::IMessage<EnumTypesResponse>
  #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      , pb::IBufferMessage
  #endif
  {
    private static readonly pb::MessageParser<EnumTypesResponse> _parser = new pb::MessageParser<EnumTypesResponse>(() => new EnumTypesResponse());
    private pb::UnknownFieldSet _unknownFields;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pb::MessageParser<EnumTypesResponse> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::UsingGRPC.EnumTypesReflection.Descriptor.MessageTypes[1]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public EnumTypesResponse() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public EnumTypesResponse(EnumTypesResponse other) : this() {
      responseMessage_ = other.responseMessage_;
      _unknownFields = pb::UnknownFieldSet.Clone(other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public EnumTypesResponse Clone() {
      return new EnumTypesResponse(this);
    }

    /// <summary>Field number for the "ResponseMessage" field.</summary>
    public const int ResponseMessageFieldNumber = 1;
    private string responseMessage_ = "";
    /// <summary>
    ///--------------------------------------------------------------------------------------------------------------------------------
    /// </summary>
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public string ResponseMessage {
      get { return responseMessage_; }
      set {
        responseMessage_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override bool Equals(object other) {
      return Equals(other as EnumTypesResponse);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public bool Equals(EnumTypesResponse other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (ResponseMessage != other.ResponseMessage) return false;
      return Equals(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override int GetHashCode() {
      int hash = 1;
      if (ResponseMessage.Length != 0) hash ^= ResponseMessage.GetHashCode();
      if (_unknownFields != null) {
        hash ^= _unknownFields.GetHashCode();
      }
      return hash;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override string ToString() {
      return pb::JsonFormatter.ToDiagnosticString(this);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void WriteTo(pb::CodedOutputStream output) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      output.WriteRawMessage(this);
    #else
      if (ResponseMessage.Length != 0) {
        output.WriteRawTag(10);
        output.WriteString(ResponseMessage);
      }
      if (_unknownFields != null) {
        _unknownFields.WriteTo(output);
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalWriteTo(ref pb::WriteContext output) {
      if (ResponseMessage.Length != 0) {
        output.WriteRawTag(10);
        output.WriteString(ResponseMessage);
      }
      if (_unknownFields != null) {
        _unknownFields.WriteTo(ref output);
      }
    }
    #endif

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int CalculateSize() {
      int size = 0;
      if (ResponseMessage.Length != 0) {
        size += 1 + pb::CodedOutputStream.ComputeStringSize(ResponseMessage);
      }
      if (_unknownFields != null) {
        size += _unknownFields.CalculateSize();
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(EnumTypesResponse other) {
      if (other == null) {
        return;
      }
      if (other.ResponseMessage.Length != 0) {
        ResponseMessage = other.ResponseMessage;
      }
      _unknownFields = pb::UnknownFieldSet.MergeFrom(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(pb::CodedInputStream input) {
    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      input.ReadRawMessage(this);
    #else
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
      if ((tag & 7) == 4) {
        // Abort on any end group tag.
        return;
      }
      switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, input);
            break;
          case 10: {
            ResponseMessage = input.ReadString();
            break;
          }
        }
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalMergeFrom(ref pb::ParseContext input) {
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
      if ((tag & 7) == 4) {
        // Abort on any end group tag.
        return;
      }
      switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, ref input);
            break;
          case 10: {
            ResponseMessage = input.ReadString();
            break;
          }
        }
      }
    }
    #endif

  }

  #endregion

}

#endregion Designer generated code
