// <auto-generated>
//     Generated by the protocol buffer compiler.  DO NOT EDIT!
//     source: Protos/MapTypes.proto
// </auto-generated>
#pragma warning disable 1591, 0612, 3021, 8981
#region Designer generated code

using pb = global::Google.Protobuf;
using pbc = global::Google.Protobuf.Collections;
using pbr = global::Google.Protobuf.Reflection;
using scg = global::System.Collections.Generic;
namespace UsingGRPC {

  /// <summary>Holder for reflection information generated from Protos/MapTypes.proto</summary>
  public static partial class MapTypesReflection {

    #region Descriptor
    /// <summary>File descriptor for Protos/MapTypes.proto</summary>
    public static pbr::FileDescriptor Descriptor {
      get { return descriptor; }
    }
    private static pbr::FileDescriptor descriptor;

    static MapTypesReflection() {
      byte[] descriptorData = global::System.Convert.FromBase64String(
          string.Concat(
            "ChVQcm90b3MvTWFwVHlwZXMucHJvdG8SEFVzaW5nR1JQQ1BhY2thZ2UiOgoR",
            "TWFwVHlwZXNWYWx1ZVR5cGUSEAoIRmllbGRJbnQYASABKAUSEwoLRmllbGRT",
            "dHJpbmcYAiABKAkiuAIKD01hcFR5cGVzUmVxdWVzdBISCgpOb01hcEZpZWxk",
            "GAEgASgFEkMKCU1hcEZpZWxkMRgCIAMoCzIwLlVzaW5nR1JQQ1BhY2thZ2Uu",
            "TWFwVHlwZXNSZXF1ZXN0Lk1hcEZpZWxkMUVudHJ5EkMKCU1hcEZpZWxkMhgD",
            "IAMoCzIwLlVzaW5nR1JQQ1BhY2thZ2UuTWFwVHlwZXNSZXF1ZXN0Lk1hcEZp",
            "ZWxkMkVudHJ5GjAKDk1hcEZpZWxkMUVudHJ5EgsKA2tleRgBIAEoBRINCgV2",
            "YWx1ZRgCIAEoCToCOAEaVQoOTWFwRmllbGQyRW50cnkSCwoDa2V5GAEgASgF",
            "EjIKBXZhbHVlGAIgASgLMiMuVXNpbmdHUlBDUGFja2FnZS5NYXBUeXBlc1Zh",
            "bHVlVHlwZToCOAEiKwoQTWFwVHlwZXNSZXNwb25zZRIXCg9SZXNwb25zZU1l",
            "c3NhZ2UYASABKAkyZAoITWFwVHlwZXMSWAoPUHJvY2Vzc01hcFR5cGVzEiEu",
            "VXNpbmdHUlBDUGFja2FnZS5NYXBUeXBlc1JlcXVlc3QaIi5Vc2luZ0dSUENQ",
            "YWNrYWdlLk1hcFR5cGVzUmVzcG9uc2VCDKoCCVVzaW5nR1JQQ2IGcHJvdG8z"));
      descriptor = pbr::FileDescriptor.FromGeneratedCode(descriptorData,
          new pbr::FileDescriptor[] { },
          new pbr::GeneratedClrTypeInfo(null, null, new pbr::GeneratedClrTypeInfo[] {
            new pbr::GeneratedClrTypeInfo(typeof(global::UsingGRPC.MapTypesValueType), global::UsingGRPC.MapTypesValueType.Parser, new[]{ "FieldInt", "FieldString" }, null, null, null, null),
            new pbr::GeneratedClrTypeInfo(typeof(global::UsingGRPC.MapTypesRequest), global::UsingGRPC.MapTypesRequest.Parser, new[]{ "NoMapField", "MapField1", "MapField2" }, null, null, null, new pbr::GeneratedClrTypeInfo[] { null, null, }),
            new pbr::GeneratedClrTypeInfo(typeof(global::UsingGRPC.MapTypesResponse), global::UsingGRPC.MapTypesResponse.Parser, new[]{ "ResponseMessage" }, null, null, null, null)
          }));
    }
    #endregion

  }
  #region Messages
  /// <summary>
  ///--------------------------------------------------------------------------------------------------------------------------------
  ///--------------------------------------------------------------------------------------------------------------------------------
  ///--------------------------------------------------------------------------------------------------------------------------------
  /// </summary>
  [global::System.Diagnostics.DebuggerDisplayAttribute("{ToString(),nq}")]
  public sealed partial class MapTypesValueType : pb::IMessage<MapTypesValueType>
  #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      , pb::IBufferMessage
  #endif
  {
    private static readonly pb::MessageParser<MapTypesValueType> _parser = new pb::MessageParser<MapTypesValueType>(() => new MapTypesValueType());
    private pb::UnknownFieldSet _unknownFields;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pb::MessageParser<MapTypesValueType> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::UsingGRPC.MapTypesReflection.Descriptor.MessageTypes[0]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public MapTypesValueType() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public MapTypesValueType(MapTypesValueType other) : this() {
      fieldInt_ = other.fieldInt_;
      fieldString_ = other.fieldString_;
      _unknownFields = pb::UnknownFieldSet.Clone(other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public MapTypesValueType Clone() {
      return new MapTypesValueType(this);
    }

    /// <summary>Field number for the "FieldInt" field.</summary>
    public const int FieldIntFieldNumber = 1;
    private int fieldInt_;
    /// <summary>
    ///--------------------------------------------------------------------------------------------------------------------------------
    /// </summary>
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int FieldInt {
      get { return fieldInt_; }
      set {
        fieldInt_ = value;
      }
    }

    /// <summary>Field number for the "FieldString" field.</summary>
    public const int FieldStringFieldNumber = 2;
    private string fieldString_ = "";
    /// <summary>
    ///--------------------------------------------------------------------------------------------------------------------------------
    /// </summary>
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public string FieldString {
      get { return fieldString_; }
      set {
        fieldString_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override bool Equals(object other) {
      return Equals(other as MapTypesValueType);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public bool Equals(MapTypesValueType other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (FieldInt != other.FieldInt) return false;
      if (FieldString != other.FieldString) return false;
      return Equals(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override int GetHashCode() {
      int hash = 1;
      if (FieldInt != 0) hash ^= FieldInt.GetHashCode();
      if (FieldString.Length != 0) hash ^= FieldString.GetHashCode();
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
      if (FieldInt != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(FieldInt);
      }
      if (FieldString.Length != 0) {
        output.WriteRawTag(18);
        output.WriteString(FieldString);
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
      if (FieldInt != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(FieldInt);
      }
      if (FieldString.Length != 0) {
        output.WriteRawTag(18);
        output.WriteString(FieldString);
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
      if (FieldInt != 0) {
        size += 1 + pb::CodedOutputStream.ComputeInt32Size(FieldInt);
      }
      if (FieldString.Length != 0) {
        size += 1 + pb::CodedOutputStream.ComputeStringSize(FieldString);
      }
      if (_unknownFields != null) {
        size += _unknownFields.CalculateSize();
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(MapTypesValueType other) {
      if (other == null) {
        return;
      }
      if (other.FieldInt != 0) {
        FieldInt = other.FieldInt;
      }
      if (other.FieldString.Length != 0) {
        FieldString = other.FieldString;
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
            FieldInt = input.ReadInt32();
            break;
          }
          case 18: {
            FieldString = input.ReadString();
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
            FieldInt = input.ReadInt32();
            break;
          }
          case 18: {
            FieldString = input.ReadString();
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
  public sealed partial class MapTypesRequest : pb::IMessage<MapTypesRequest>
  #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      , pb::IBufferMessage
  #endif
  {
    private static readonly pb::MessageParser<MapTypesRequest> _parser = new pb::MessageParser<MapTypesRequest>(() => new MapTypesRequest());
    private pb::UnknownFieldSet _unknownFields;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pb::MessageParser<MapTypesRequest> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::UsingGRPC.MapTypesReflection.Descriptor.MessageTypes[1]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public MapTypesRequest() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public MapTypesRequest(MapTypesRequest other) : this() {
      noMapField_ = other.noMapField_;
      mapField1_ = other.mapField1_.Clone();
      mapField2_ = other.mapField2_.Clone();
      _unknownFields = pb::UnknownFieldSet.Clone(other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public MapTypesRequest Clone() {
      return new MapTypesRequest(this);
    }

    /// <summary>Field number for the "NoMapField" field.</summary>
    public const int NoMapFieldFieldNumber = 1;
    private int noMapField_;
    /// <summary>
    ///--------------------------------------------------------------------------------------------------------------------------------
    /// </summary>
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int NoMapField {
      get { return noMapField_; }
      set {
        noMapField_ = value;
      }
    }

    /// <summary>Field number for the "MapField1" field.</summary>
    public const int MapField1FieldNumber = 2;
    private static readonly pbc::MapField<int, string>.Codec _map_mapField1_codec
        = new pbc::MapField<int, string>.Codec(pb::FieldCodec.ForInt32(8, 0), pb::FieldCodec.ForString(18, ""), 18);
    private readonly pbc::MapField<int, string> mapField1_ = new pbc::MapField<int, string>();
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public pbc::MapField<int, string> MapField1 {
      get { return mapField1_; }
    }

    /// <summary>Field number for the "MapField2" field.</summary>
    public const int MapField2FieldNumber = 3;
    private static readonly pbc::MapField<int, global::UsingGRPC.MapTypesValueType>.Codec _map_mapField2_codec
        = new pbc::MapField<int, global::UsingGRPC.MapTypesValueType>.Codec(pb::FieldCodec.ForInt32(8, 0), pb::FieldCodec.ForMessage(18, global::UsingGRPC.MapTypesValueType.Parser), 26);
    private readonly pbc::MapField<int, global::UsingGRPC.MapTypesValueType> mapField2_ = new pbc::MapField<int, global::UsingGRPC.MapTypesValueType>();
    /// <summary>
    ///--------------------------------------------------------------------------------------------------------------------------------
    /// </summary>
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public pbc::MapField<int, global::UsingGRPC.MapTypesValueType> MapField2 {
      get { return mapField2_; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override bool Equals(object other) {
      return Equals(other as MapTypesRequest);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public bool Equals(MapTypesRequest other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (NoMapField != other.NoMapField) return false;
      if (!MapField1.Equals(other.MapField1)) return false;
      if (!MapField2.Equals(other.MapField2)) return false;
      return Equals(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public override int GetHashCode() {
      int hash = 1;
      if (NoMapField != 0) hash ^= NoMapField.GetHashCode();
      hash ^= MapField1.GetHashCode();
      hash ^= MapField2.GetHashCode();
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
      if (NoMapField != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(NoMapField);
      }
      mapField1_.WriteTo(output, _map_mapField1_codec);
      mapField2_.WriteTo(output, _map_mapField2_codec);
      if (_unknownFields != null) {
        _unknownFields.WriteTo(output);
      }
    #endif
    }

    #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    void pb::IBufferMessage.InternalWriteTo(ref pb::WriteContext output) {
      if (NoMapField != 0) {
        output.WriteRawTag(8);
        output.WriteInt32(NoMapField);
      }
      mapField1_.WriteTo(ref output, _map_mapField1_codec);
      mapField2_.WriteTo(ref output, _map_mapField2_codec);
      if (_unknownFields != null) {
        _unknownFields.WriteTo(ref output);
      }
    }
    #endif

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public int CalculateSize() {
      int size = 0;
      if (NoMapField != 0) {
        size += 1 + pb::CodedOutputStream.ComputeInt32Size(NoMapField);
      }
      size += mapField1_.CalculateSize(_map_mapField1_codec);
      size += mapField2_.CalculateSize(_map_mapField2_codec);
      if (_unknownFields != null) {
        size += _unknownFields.CalculateSize();
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public void MergeFrom(MapTypesRequest other) {
      if (other == null) {
        return;
      }
      if (other.NoMapField != 0) {
        NoMapField = other.NoMapField;
      }
      mapField1_.MergeFrom(other.mapField1_);
      mapField2_.MergeFrom(other.mapField2_);
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
            NoMapField = input.ReadInt32();
            break;
          }
          case 18: {
            mapField1_.AddEntriesFrom(input, _map_mapField1_codec);
            break;
          }
          case 26: {
            mapField2_.AddEntriesFrom(input, _map_mapField2_codec);
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
            NoMapField = input.ReadInt32();
            break;
          }
          case 18: {
            mapField1_.AddEntriesFrom(ref input, _map_mapField1_codec);
            break;
          }
          case 26: {
            mapField2_.AddEntriesFrom(ref input, _map_mapField2_codec);
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
  public sealed partial class MapTypesResponse : pb::IMessage<MapTypesResponse>
  #if !GOOGLE_PROTOBUF_REFSTRUCT_COMPATIBILITY_MODE
      , pb::IBufferMessage
  #endif
  {
    private static readonly pb::MessageParser<MapTypesResponse> _parser = new pb::MessageParser<MapTypesResponse>(() => new MapTypesResponse());
    private pb::UnknownFieldSet _unknownFields;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pb::MessageParser<MapTypesResponse> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::UsingGRPC.MapTypesReflection.Descriptor.MessageTypes[2]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public MapTypesResponse() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public MapTypesResponse(MapTypesResponse other) : this() {
      responseMessage_ = other.responseMessage_;
      _unknownFields = pb::UnknownFieldSet.Clone(other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public MapTypesResponse Clone() {
      return new MapTypesResponse(this);
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
      return Equals(other as MapTypesResponse);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    [global::System.CodeDom.Compiler.GeneratedCode("protoc", null)]
    public bool Equals(MapTypesResponse other) {
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
    public void MergeFrom(MapTypesResponse other) {
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
