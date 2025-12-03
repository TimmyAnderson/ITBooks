using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace WebAPICommonPracticesWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class PaginationController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private static readonly CMyValue[]						MMyValues;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static PaginationController()
		{
			MMyValues=new CMyValue[35];

			for(int Index=0;Index<MMyValues.Length;Index++)
			{
				int												Value1=(Index+1);
				string											Value2=$"VALUE [{Value1}].";

				MMyValues[Index]=new CMyValue(Value1,Value2);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("ReturnPage")]
		public ActionResult<CPaginatedArray<CMyValue>> ReturnPage(int PageIndex, int PageSize)
		{
			CMyValue[]											Items=MMyValues.Skip((PageIndex-1)*PageSize).Take(PageSize).ToArray();
			int													TotalItems=MMyValues.Length;

			CPaginatedArray<CMyValue>							PaginatedArray=new CPaginatedArray<CMyValue>(Items,PageIndex,PageSize,TotalItems);

			ActionResult<CPaginatedArray<CMyValue>>				Result=Ok(PaginatedArray);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------