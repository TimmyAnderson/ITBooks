using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParseTreeNodeData_ParamTypes : CParseTreeNodeData
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CParseTreeNodeData_Type>			MParamTypes;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParseTreeNodeData_ParamTypes()
		{
			MParamTypes=new List<CParseTreeNodeData_Type>();
		}
//-------------------------------------------------------------------------------------------------------
		public CParseTreeNodeData_ParamTypes(CParseTreeNodeData_Type ParamType)
		{
			MParamTypes=new List<CParseTreeNodeData_Type>();

			MParamTypes.Add(ParamType);
		}
//-------------------------------------------------------------------------------------------------------
		public CParseTreeNodeData_ParamTypes(CParseTreeNodeData_ParamTypes ParamTypes)
		{
			MParamTypes=new List<CParseTreeNodeData_Type>();

			MParamTypes.AddRange(ParamTypes.MParamTypes);
		}
//-------------------------------------------------------------------------------------------------------
		public CParseTreeNodeData_ParamTypes(CParseTreeNodeData_ParamTypes ParamTypes, CParseTreeNodeData_Type ParamType)
		{
			MParamTypes=new List<CParseTreeNodeData_Type>();

			MParamTypes.AddRange(ParamTypes.MParamTypes);
			MParamTypes.Add(ParamType);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParseTreeNodeData_Type[]						ParamTypes
		{
			get
			{
				return(MParamTypes.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int GetSizeof(EVariableType VariableType)
		{
			int													Sizeof=0;

			foreach(CParseTreeNodeData_Type ParamType in MParamTypes)
			{
				Sizeof+=ParamType.GetSizeof(VariableType);
			}

			return(Sizeof);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------