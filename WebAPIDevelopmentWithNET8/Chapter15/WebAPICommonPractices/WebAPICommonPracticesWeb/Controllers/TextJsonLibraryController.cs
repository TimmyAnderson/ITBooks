using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace WebAPICommonPracticesWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class TextJsonLibraryController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("SerializeDeserialize1")]
		public IActionResult SerializeDeserialize1()
		{
			CMySerializeDeserializeType1						Object=new CMySerializeDeserializeType1("VALUE [111].",111);

			JsonSerializerOptions								Options=new JsonSerializerOptions();

			Options.PropertyNamingPolicy=JsonNamingPolicy.CamelCase;
			Options.WriteIndented=true;

			string												SezializedObject=JsonSerializer.Serialize(Object,Options);

			CMySerializeDeserializeType1						Content=JsonSerializer.Deserialize<CMySerializeDeserializeType1>(SezializedObject,Options);

			IActionResult										Result=Ok(Content);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("SerializeDeserialize2")]
		public IActionResult SerializeDeserialize2()
		{
			CMySerializeDeserializeType2						Object=new CMySerializeDeserializeType2("VALUE [222].",222,222.222);

			JsonSerializerOptions								Options=new JsonSerializerOptions();

			Options.PropertyNamingPolicy=JsonNamingPolicy.CamelCase;
			Options.WriteIndented=true;

			string												SezializedObject=JsonSerializer.Serialize(Object,Options);

			CMySerializeDeserializeType2						Content=JsonSerializer.Deserialize<CMySerializeDeserializeType2>(SezializedObject,Options);

			IActionResult										Result=Ok(Content);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------