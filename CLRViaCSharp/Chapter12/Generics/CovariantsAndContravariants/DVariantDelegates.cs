using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CovariantsAndContravariants
{
//-------------------------------------------------------------------------------------------------------
	// NEDEFINUJEM ZIADNU COVARIANCE ani CONTRAVARIANCE - pouzivam teda INVARIANCE.
	public delegate TReturn DSum_Invariance<TParameter,TReturn>(TParameter[] Parameter);
	// Definujem COVARIANCE a CONTRAVARIANCE.
	public delegate TReturn DSum_CovarianceAndContravariance<in TParameter,out TReturn>(TParameter[] Parameter);
//-------------------------------------------------------------------------------------------------------
	// Priklad VYUZITIA COVARIANCE pre EventArgs.
	public delegate void DMyEventHandler<in TParameter>(TParameter Parameter);
//-------------------------------------------------------------------------------------------------------
	/*
	// COMPILER hodi ERROR. 'IN' TYPE PARAMETER NEMOZE byt pouzity ako 'REF' METHOD PARAMETER.
	public delegate void DError1<in TParameter>(ref TParameter Parameter);
	// COMPILER hodi ERROR. 'IN' TYPE PARAMETER NEMOZE byt pouzity ako 'OUT' METHOD PARAMETER.
	public delegate void DError2<in TParameter>(out TParameter Parameter);
	// COMPILER hodi ERROR. 'OUT' TYPE PARAMETER NEMOZE byt pouzity ako 'REF' METHOD PARAMETER.
	public delegate void DError3<out TParameter>(ref TParameter Parameter);
	// COMPILER hodi ERROR. 'OUT' TYPE PARAMETER NEMOZE byt pouzity ako 'OUT' METHOD PARAMETER.
	public delegate void DError4<out TParameter>(out TParameter Parameter);
	*/
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------