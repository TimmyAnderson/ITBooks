using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Delegates
{
//-------------------------------------------------------------------------------------------------------
	public delegate object DToUpper(string Param);
	public delegate string DToUpperTyped(string Param);
	public delegate void DNoReturn(string Param);
	public delegate int DReturnSomething();
	public delegate void DToUpperRef(ref string Param);
	public delegate TReturn DSum_CovarianceAndContravariance<in TParameter,out TReturn>(TParameter[] Parameter);
	public delegate void DParameterRef(ref string Param);
	public delegate void DParameterOut(out string Param);
	public delegate void DParameterParams(params object[] Params);
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------