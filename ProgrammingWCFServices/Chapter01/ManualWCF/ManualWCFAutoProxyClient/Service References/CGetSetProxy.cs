﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.42
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace ManualWCFAutoProxyClient.CGetSetProxy
{
    
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="ManualWCFAutoProxyClient.CGetSetProxy.IIntGetSetContract")]
    public interface IIntGetSetContract
    {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IIntGetSetContract/GetIntValue", ReplyAction="http://tempuri.org/IIntGetSetContract/GetIntValueResponse")]
        int GetIntValue();
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IIntGetSetContract/SetIntValue", ReplyAction="http://tempuri.org/IIntGetSetContract/SetIntValueResponse")]
        void SetIntValue(int Value);
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface IIntGetSetContractChannel : ManualWCFAutoProxyClient.CGetSetProxy.IIntGetSetContract, System.ServiceModel.IClientChannel
    {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class IntGetSetContractClient : System.ServiceModel.ClientBase<ManualWCFAutoProxyClient.CGetSetProxy.IIntGetSetContract>, ManualWCFAutoProxyClient.CGetSetProxy.IIntGetSetContract
    {
        
        public IntGetSetContractClient()
        {
        }
        
        public IntGetSetContractClient(string endpointConfigurationName) : 
                base(endpointConfigurationName)
        {
        }
        
        public IntGetSetContractClient(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress)
        {
        }
        
        public IntGetSetContractClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress)
        {
        }
        
        public IntGetSetContractClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress)
        {
        }
        
        public int GetIntValue()
        {
            return base.Channel.GetIntValue();
        }
        
        public void SetIntValue(int Value)
        {
            base.Channel.SetIntValue(Value);
        }
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="ManualWCFAutoProxyClient.CGetSetProxy.IStringGetSetContract")]
    public interface IStringGetSetContract
    {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IStringGetSetContract/GetStringValue", ReplyAction="http://tempuri.org/IStringGetSetContract/GetStringValueResponse")]
        string GetStringValue();
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IStringGetSetContract/SetStringValue", ReplyAction="http://tempuri.org/IStringGetSetContract/SetStringValueResponse")]
        void SetStringValue(string Value);
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface IStringGetSetContractChannel : ManualWCFAutoProxyClient.CGetSetProxy.IStringGetSetContract, System.ServiceModel.IClientChannel
    {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class StringGetSetContractClient : System.ServiceModel.ClientBase<ManualWCFAutoProxyClient.CGetSetProxy.IStringGetSetContract>, ManualWCFAutoProxyClient.CGetSetProxy.IStringGetSetContract
    {
        
        public StringGetSetContractClient()
        {
        }
        
        public StringGetSetContractClient(string endpointConfigurationName) : 
                base(endpointConfigurationName)
        {
        }
        
        public StringGetSetContractClient(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress)
        {
        }
        
        public StringGetSetContractClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress)
        {
        }
        
        public StringGetSetContractClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress)
        {
        }
        
        public string GetStringValue()
        {
            return base.Channel.GetStringValue();
        }
        
        public void SetStringValue(string Value)
        {
            base.Channel.SetStringValue(Value);
        }
    }
}