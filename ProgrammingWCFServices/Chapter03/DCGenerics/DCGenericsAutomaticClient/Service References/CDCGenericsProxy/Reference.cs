﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.1
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace DCGenericsAutomaticClient.CDCGenericsProxy {
    using System.Runtime.Serialization;
    using System;
    
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="CGenericClass1Ofint", Namespace="http://schemas.datacontract.org/2004/07/DCGenericsLibrary")]
    [System.SerializableAttribute()]
    public partial class CGenericClass1Ofint : object, System.Runtime.Serialization.IExtensibleDataObject, System.ComponentModel.INotifyPropertyChanged {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private int DataField;
        
        [global::System.ComponentModel.BrowsableAttribute(false)]
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData {
            get {
                return this.extensionDataField;
            }
            set {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public int Data {
            get {
                return this.DataField;
            }
            set {
                if ((this.DataField.Equals(value) != true)) {
                    this.DataField = value;
                    this.RaisePropertyChanged("Data");
                }
            }
        }
        
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;
        
        protected void RaisePropertyChanged(string propertyName) {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if ((propertyChanged != null)) {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="CGenericClass1Ofstring", Namespace="http://schemas.datacontract.org/2004/07/DCGenericsLibrary")]
    [System.SerializableAttribute()]
    public partial class CGenericClass1Ofstring : object, System.Runtime.Serialization.IExtensibleDataObject, System.ComponentModel.INotifyPropertyChanged {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string DataField;
        
        [global::System.ComponentModel.BrowsableAttribute(false)]
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData {
            get {
                return this.extensionDataField;
            }
            set {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string Data {
            get {
                return this.DataField;
            }
            set {
                if ((object.ReferenceEquals(this.DataField, value) != true)) {
                    this.DataField = value;
                    this.RaisePropertyChanged("Data");
                }
            }
        }
        
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;
        
        protected void RaisePropertyChanged(string propertyName) {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if ((propertyChanged != null)) {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="CGenericClass1OfCNamemd1vdT_PP", Namespace="http://schemas.datacontract.org/2004/07/DCGenericsLibrary")]
    [System.SerializableAttribute()]
    public partial class CGenericClass1OfCNamemd1vdT_PP : object, System.Runtime.Serialization.IExtensibleDataObject, System.ComponentModel.INotifyPropertyChanged {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private DCGenericsAutomaticClient.CDCGenericsProxy.CName DataField;
        
        [global::System.ComponentModel.BrowsableAttribute(false)]
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData {
            get {
                return this.extensionDataField;
            }
            set {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public DCGenericsAutomaticClient.CDCGenericsProxy.CName Data {
            get {
                return this.DataField;
            }
            set {
                if ((object.ReferenceEquals(this.DataField, value) != true)) {
                    this.DataField = value;
                    this.RaisePropertyChanged("Data");
                }
            }
        }
        
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;
        
        protected void RaisePropertyChanged(string propertyName) {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if ((propertyChanged != null)) {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="CName", Namespace="http://schemas.datacontract.org/2004/07/DCGenericsLibrary")]
    [System.SerializableAttribute()]
    public partial class CName : object, System.Runtime.Serialization.IExtensibleDataObject, System.ComponentModel.INotifyPropertyChanged {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string FirstNameField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string LastNameField;
        
        [global::System.ComponentModel.BrowsableAttribute(false)]
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData {
            get {
                return this.extensionDataField;
            }
            set {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string FirstName {
            get {
                return this.FirstNameField;
            }
            set {
                if ((object.ReferenceEquals(this.FirstNameField, value) != true)) {
                    this.FirstNameField = value;
                    this.RaisePropertyChanged("FirstName");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string LastName {
            get {
                return this.LastNameField;
            }
            set {
                if ((object.ReferenceEquals(this.LastNameField, value) != true)) {
                    this.LastNameField = value;
                    this.RaisePropertyChanged("LastName");
                }
            }
        }
        
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;
        
        protected void RaisePropertyChanged(string propertyName) {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if ((propertyChanged != null)) {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="CGenericClass2", Namespace="http://schemas.datacontract.org/2004/07/DCGenericsLibrary")]
    [System.SerializableAttribute()]
    public partial class CGenericClass2 : object, System.Runtime.Serialization.IExtensibleDataObject, System.ComponentModel.INotifyPropertyChanged {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private DCGenericsAutomaticClient.CDCGenericsProxy.CName DataField;
        
        [global::System.ComponentModel.BrowsableAttribute(false)]
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData {
            get {
                return this.extensionDataField;
            }
            set {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public DCGenericsAutomaticClient.CDCGenericsProxy.CName Data {
            get {
                return this.DataField;
            }
            set {
                if ((object.ReferenceEquals(this.DataField, value) != true)) {
                    this.DataField = value;
                    this.RaisePropertyChanged("Data");
                }
            }
        }
        
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;
        
        protected void RaisePropertyChanged(string propertyName) {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if ((propertyChanged != null)) {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="CGenericClass3_CName", Namespace="http://schemas.datacontract.org/2004/07/DCGenericsLibrary")]
    [System.SerializableAttribute()]
    public partial class CGenericClass3_CName : object, System.Runtime.Serialization.IExtensibleDataObject, System.ComponentModel.INotifyPropertyChanged {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private DCGenericsAutomaticClient.CDCGenericsProxy.CName DataField;
        
        [global::System.ComponentModel.BrowsableAttribute(false)]
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData {
            get {
                return this.extensionDataField;
            }
            set {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public DCGenericsAutomaticClient.CDCGenericsProxy.CName Data {
            get {
                return this.DataField;
            }
            set {
                if ((object.ReferenceEquals(this.DataField, value) != true)) {
                    this.DataField = value;
                    this.RaisePropertyChanged("Data");
                }
            }
        }
        
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;
        
        protected void RaisePropertyChanged(string propertyName) {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if ((propertyChanged != null)) {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="CGenericClass4_CName_Hash_md1vdT_PP", Namespace="http://schemas.datacontract.org/2004/07/DCGenericsLibrary")]
    [System.SerializableAttribute()]
    public partial class CGenericClass4_CName_Hash_md1vdT_PP : object, System.Runtime.Serialization.IExtensibleDataObject, System.ComponentModel.INotifyPropertyChanged {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private DCGenericsAutomaticClient.CDCGenericsProxy.CName DataField;
        
        [global::System.ComponentModel.BrowsableAttribute(false)]
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData {
            get {
                return this.extensionDataField;
            }
            set {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public DCGenericsAutomaticClient.CDCGenericsProxy.CName Data {
            get {
                return this.DataField;
            }
            set {
                if ((object.ReferenceEquals(this.DataField, value) != true)) {
                    this.DataField = value;
                    this.RaisePropertyChanged("Data");
                }
            }
        }
        
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;
        
        protected void RaisePropertyChanged(string propertyName) {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if ((propertyChanged != null)) {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="CDCGenericsProxy.IDCGenericsContractOf_String")]
    public interface IDCGenericsContractOf_String {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IDCGenericsContractOf_String/SendInt", ReplyAction="http://tempuri.org/IDCGenericsContractOf_String/SendIntResponse")]
        void SendInt(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass1Ofint Value);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IDCGenericsContractOf_String/SendGenerics", ReplyAction="http://tempuri.org/IDCGenericsContractOf_String/SendGenericsResponse")]
        void SendGenerics(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass1Ofstring Value);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IDCGenericsContractOf_String/SendCName1", ReplyAction="http://tempuri.org/IDCGenericsContractOf_String/SendCName1Response")]
        void SendCName1(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass1OfCNamemd1vdT_PP Value);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IDCGenericsContractOf_String/SendCName2", ReplyAction="http://tempuri.org/IDCGenericsContractOf_String/SendCName2Response")]
        void SendCName2(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass2 Value);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IDCGenericsContractOf_String/SendCName3", ReplyAction="http://tempuri.org/IDCGenericsContractOf_String/SendCName3Response")]
        void SendCName3(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass3_CName Value);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IDCGenericsContractOf_String/SendCName4", ReplyAction="http://tempuri.org/IDCGenericsContractOf_String/SendCName4Response")]
        void SendCName4(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass4_CName_Hash_md1vdT_PP Value);
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public interface IDCGenericsContractOf_StringChannel : DCGenericsAutomaticClient.CDCGenericsProxy.IDCGenericsContractOf_String, System.ServiceModel.IClientChannel {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public partial class DCGenericsContractOf_StringClient : System.ServiceModel.ClientBase<DCGenericsAutomaticClient.CDCGenericsProxy.IDCGenericsContractOf_String>, DCGenericsAutomaticClient.CDCGenericsProxy.IDCGenericsContractOf_String {
        
        public DCGenericsContractOf_StringClient() {
        }
        
        public DCGenericsContractOf_StringClient(string endpointConfigurationName) : 
                base(endpointConfigurationName) {
        }
        
        public DCGenericsContractOf_StringClient(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public DCGenericsContractOf_StringClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public DCGenericsContractOf_StringClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress) {
        }
        
        public void SendInt(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass1Ofint Value) {
            base.Channel.SendInt(Value);
        }
        
        public void SendGenerics(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass1Ofstring Value) {
            base.Channel.SendGenerics(Value);
        }
        
        public void SendCName1(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass1OfCNamemd1vdT_PP Value) {
            base.Channel.SendCName1(Value);
        }
        
        public void SendCName2(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass2 Value) {
            base.Channel.SendCName2(Value);
        }
        
        public void SendCName3(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass3_CName Value) {
            base.Channel.SendCName3(Value);
        }
        
        public void SendCName4(DCGenericsAutomaticClient.CDCGenericsProxy.CGenericClass4_CName_Hash_md1vdT_PP Value) {
            base.Channel.SendCName4(Value);
        }
    }
}