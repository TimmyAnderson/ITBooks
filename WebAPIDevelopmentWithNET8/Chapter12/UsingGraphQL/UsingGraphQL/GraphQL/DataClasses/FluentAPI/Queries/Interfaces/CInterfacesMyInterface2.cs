﻿//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CInterfacesMyInterface2 : IInterfacesMyInterface
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly int									MID;
		private readonly string									MSharedValue1;
		private readonly string									MSharedValue2;
		private readonly string									MClass2Value1;
		private readonly string									MClass2Value2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CInterfacesMyInterface2(int ID, string SharedValue1, string SharedValue2, string Class2Value1, string Class2Value2)
		{
			MID=ID;
			MSharedValue1=SharedValue1;
			MSharedValue2=SharedValue2;
			MClass2Value1=Class2Value1;
			MClass2Value2=Class2Value2;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public int												ID
		{
			get
			{
				return(MID);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											SharedValue1
		{
			get
			{
				return(MSharedValue1);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											SharedValue2
		{
			get
			{
				return(MSharedValue2);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											Class2Value1
		{
			get
			{
				return(MClass2Value1);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											Class2Value2
		{
			get
			{
				return(MClass2Value2);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------