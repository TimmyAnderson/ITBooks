﻿//--------------------------------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.42
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//--------------------------------------------------------------------------------------------------------
namespace DCUsingAttributesAutomaticClient.CDCUsingAttributesProxy
{
    using System.Runtime.Serialization;
    using System;
    
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "3.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Namespace="http://schemas.datacontract.org/2004/07/DCUsingAttributesLibrary")]
    [System.SerializableAttribute()]
    public partial class CNameDC : object, System.Runtime.Serialization.IExtensibleDataObject
    {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private int AgeField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string LastNameField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string MFirstNameField;
        
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData
        {
            get
            {
                return this.extensionDataField;
            }
            set
            {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public int Age
        {
            get
            {
                return this.AgeField;
            }
            set
            {
                this.AgeField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string LastName
        {
            get
            {
                return this.LastNameField;
            }
            set
            {
                this.LastNameField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public string MFirstName
        {
            get
            {
                return this.MFirstNameField;
            }
            set
            {
                this.MFirstNameField = value;
            }
        }
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="DCUsingAttributesAutomaticClient.CDCUsingAttributesProxy.IDCUsingAttributesContra" +
        "ct")]
    public interface IDCUsingAttributesContract
    {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IDCUsingAttributesContract/SayYourName", ReplyAction="http://tempuri.org/IDCUsingAttributesContract/SayYourNameResponse")]
        DCUsingAttributesAutomaticClient.CDCUsingAttributesProxy.CNameDC SayYourName();
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IDCUsingAttributesContract/ThisIsMyName", ReplyAction="http://tempuri.org/IDCUsingAttributesContract/ThisIsMyNameResponse")]
        void ThisIsMyName(DCUsingAttributesAutomaticClient.CDCUsingAttributesProxy.CNameDC NameDC);
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface IDCUsingAttributesContractChannel : DCUsingAttributesAutomaticClient.CDCUsingAttributesProxy.IDCUsingAttributesContract, System.ServiceModel.IClientChannel
    {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class DCUsingAttributesContractClient : System.ServiceModel.ClientBase<DCUsingAttributesAutomaticClient.CDCUsingAttributesProxy.IDCUsingAttributesContract>, DCUsingAttributesAutomaticClient.CDCUsingAttributesProxy.IDCUsingAttributesContract
    {
        
        public DCUsingAttributesContractClient()
        {
        }
        
        public DCUsingAttributesContractClient(string endpointConfigurationName) : 
                base(endpointConfigurationName)
        {
        }
        
        public DCUsingAttributesContractClient(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress)
        {
        }
        
        public DCUsingAttributesContractClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress)
        {
        }
        
        public DCUsingAttributesContractClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress)
        {
        }
        
        public DCUsingAttributesAutomaticClient.CDCUsingAttributesProxy.CNameDC SayYourName()
        {
            return base.Channel.SayYourName();
        }
        
        public void ThisIsMyName(DCUsingAttributesAutomaticClient.CDCUsingAttributesProxy.CNameDC NameDC)
        {
            base.Channel.ThisIsMyName(NameDC);
        }
    }
}
//--------------------------------------------------------------------------------------------------------