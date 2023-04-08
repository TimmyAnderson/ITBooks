using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionReleaseInstanceOnCompleteService
{
//-------------------------------------------------------------------------------------------------------
	public class CServiceHostWrapperCollection
	{
//-------------------------------------------------------------------------------------------------------
		private object											MSyn;
		private List<IServiceHostWrapper>						MList;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CServiceHostWrapperCollection()
		{
			MSyn=new object();
			MList=new List<IServiceHostWrapper>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void StartServices()
		{
			lock(MSyn)
			{
				foreach(IServiceHostWrapper ServiceHostWrapper in MList)
					ServiceHostWrapper.StartService();
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void StopServices()
		{
			lock(MSyn)
			{
				foreach(IServiceHostWrapper ServiceHostWrapper in MList)
					ServiceHostWrapper.StopService();
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void AddServiceHostWrapper(IServiceHostWrapper ServiceHostWrapper)
		{
			lock(MSyn)
			{
				MList.Add(ServiceHostWrapper);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool RemoveServiceHostWrapper(int Index)
		{
			lock(MSyn)
			{
				if (Index>=MList.Count)
					return(false);

				MList.RemoveAt(Index);
				return(true);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------