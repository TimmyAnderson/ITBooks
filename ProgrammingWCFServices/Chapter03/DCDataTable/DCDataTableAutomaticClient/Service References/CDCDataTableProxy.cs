﻿//--------------------------------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.42
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//--------------------------------------------------------------------------------------------------------
namespace DCDataTableAutomaticClient.CDCDataTableProxy
{
    
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="DCDataTableAutomaticClient.CDCDataTableProxy.IDCDataTableContract")]
    public interface IDCDataTableContract
    {
        
        // CODEGEN: Parameter 'GetDataTableResult' requires additional schema information that cannot be captured using the parameter mode. The specific attribute is 'System.Xml.Serialization.XmlElementAttribute'.
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IDCDataTableContract/GetDataTable", ReplyAction="http://tempuri.org/IDCDataTableContract/GetDataTableResponse")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        DCDataTableAutomaticClient.CDCDataTableProxy.GetDataTableResponse GetDataTable(DCDataTableAutomaticClient.CDCDataTableProxy.GetDataTableRequest request);
        
        // CODEGEN: Parameter 'Table' requires additional schema information that cannot be captured using the parameter mode. The specific attribute is 'System.Xml.Serialization.XmlElementAttribute'.
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IDCDataTableContract/SendDataTable", ReplyAction="http://tempuri.org/IDCDataTableContract/SendDataTableResponse")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        DCDataTableAutomaticClient.CDCDataTableProxy.SendDataTableResponse SendDataTable(DCDataTableAutomaticClient.CDCDataTableProxy.SendDataTableRequest request);
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("svcutil", "3.0.4506.30")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
    public partial class GetDataTableResponseGetDataTableResult
    {
        
        private System.Xml.XmlElement[] anyField;
        
        private System.Xml.XmlElement any1Field;
        
        /// <remarks/>
        [System.Xml.Serialization.XmlAnyElementAttribute(Namespace="http://www.w3.org/2001/XMLSchema", Order=0)]
        public System.Xml.XmlElement[] Any
        {
            get
            {
                return this.anyField;
            }
            set
            {
                this.anyField = value;
            }
        }
        
        /// <remarks/>
        [System.Xml.Serialization.XmlAnyElementAttribute(Namespace="urn:schemas-microsoft-com:xml-diffgram-v1", Order=1)]
        public System.Xml.XmlElement Any1
        {
            get
            {
                return this.any1Field;
            }
            set
            {
                this.any1Field = value;
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName="GetDataTable", WrapperNamespace="http://tempuri.org/", IsWrapped=true)]
    public partial class GetDataTableRequest
    {
        
        public GetDataTableRequest()
        {
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName="GetDataTableResponse", WrapperNamespace="http://tempuri.org/", IsWrapped=true)]
    public partial class GetDataTableResponse
    {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Namespace="http://tempuri.org/", Order=0)]
        [System.Xml.Serialization.XmlElementAttribute(IsNullable=true)]
        public DCDataTableAutomaticClient.CDCDataTableProxy.GetDataTableResponseGetDataTableResult GetDataTableResult;
        
        public GetDataTableResponse()
        {
        }
        
        public GetDataTableResponse(DCDataTableAutomaticClient.CDCDataTableProxy.GetDataTableResponseGetDataTableResult GetDataTableResult)
        {
            this.GetDataTableResult = GetDataTableResult;
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("svcutil", "3.0.4506.30")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
    public partial class SendDataTableTable
    {
        
        private System.Xml.XmlElement[] anyField;
        
        private System.Xml.XmlElement any1Field;
        
        /// <remarks/>
        [System.Xml.Serialization.XmlAnyElementAttribute(Namespace="http://www.w3.org/2001/XMLSchema", Order=0)]
        public System.Xml.XmlElement[] Any
        {
            get
            {
                return this.anyField;
            }
            set
            {
                this.anyField = value;
            }
        }
        
        /// <remarks/>
        [System.Xml.Serialization.XmlAnyElementAttribute(Namespace="urn:schemas-microsoft-com:xml-diffgram-v1", Order=1)]
        public System.Xml.XmlElement Any1
        {
            get
            {
                return this.any1Field;
            }
            set
            {
                this.any1Field = value;
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName="SendDataTable", WrapperNamespace="http://tempuri.org/", IsWrapped=true)]
    public partial class SendDataTableRequest
    {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Namespace="http://tempuri.org/", Order=0)]
        [System.Xml.Serialization.XmlElementAttribute(IsNullable=true)]
        public DCDataTableAutomaticClient.CDCDataTableProxy.SendDataTableTable Table;
        
        public SendDataTableRequest()
        {
        }
        
        public SendDataTableRequest(DCDataTableAutomaticClient.CDCDataTableProxy.SendDataTableTable Table)
        {
            this.Table = Table;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName="SendDataTableResponse", WrapperNamespace="http://tempuri.org/", IsWrapped=true)]
    public partial class SendDataTableResponse
    {
        
        public SendDataTableResponse()
        {
        }
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface IDCDataTableContractChannel : DCDataTableAutomaticClient.CDCDataTableProxy.IDCDataTableContract, System.ServiceModel.IClientChannel
    {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class DCDataTableContractClient : System.ServiceModel.ClientBase<DCDataTableAutomaticClient.CDCDataTableProxy.IDCDataTableContract>, DCDataTableAutomaticClient.CDCDataTableProxy.IDCDataTableContract
    {
        
        public DCDataTableContractClient()
        {
        }
        
        public DCDataTableContractClient(string endpointConfigurationName) : 
                base(endpointConfigurationName)
        {
        }
        
        public DCDataTableContractClient(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress)
        {
        }
        
        public DCDataTableContractClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress)
        {
        }
        
        public DCDataTableContractClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress)
        {
        }
        
        DCDataTableAutomaticClient.CDCDataTableProxy.GetDataTableResponse DCDataTableAutomaticClient.CDCDataTableProxy.IDCDataTableContract.GetDataTable(DCDataTableAutomaticClient.CDCDataTableProxy.GetDataTableRequest request)
        {
            return base.Channel.GetDataTable(request);
        }
        
        public DCDataTableAutomaticClient.CDCDataTableProxy.GetDataTableResponseGetDataTableResult GetDataTable()
        {
            DCDataTableAutomaticClient.CDCDataTableProxy.GetDataTableRequest inValue = new DCDataTableAutomaticClient.CDCDataTableProxy.GetDataTableRequest();
            DCDataTableAutomaticClient.CDCDataTableProxy.GetDataTableResponse retVal = ((DCDataTableAutomaticClient.CDCDataTableProxy.IDCDataTableContract)(this)).GetDataTable(inValue);
            return retVal.GetDataTableResult;
        }
        
        DCDataTableAutomaticClient.CDCDataTableProxy.SendDataTableResponse DCDataTableAutomaticClient.CDCDataTableProxy.IDCDataTableContract.SendDataTable(DCDataTableAutomaticClient.CDCDataTableProxy.SendDataTableRequest request)
        {
            return base.Channel.SendDataTable(request);
        }
        
        public void SendDataTable(DCDataTableAutomaticClient.CDCDataTableProxy.SendDataTableTable Table)
        {
            DCDataTableAutomaticClient.CDCDataTableProxy.SendDataTableRequest inValue = new DCDataTableAutomaticClient.CDCDataTableProxy.SendDataTableRequest();
            inValue.Table = Table;
            DCDataTableAutomaticClient.CDCDataTableProxy.SendDataTableResponse retVal = ((DCDataTableAutomaticClient.CDCDataTableProxy.IDCDataTableContract)(this)).SendDataTable(inValue);
        }
    }
}
//--------------------------------------------------------------------------------------------------------