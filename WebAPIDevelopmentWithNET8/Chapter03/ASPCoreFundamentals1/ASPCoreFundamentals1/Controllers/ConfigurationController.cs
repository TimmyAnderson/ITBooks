using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Options;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals1
{
//----------------------------------------------------------------------------------------------------------------------
    [ApiController]
    [Route("[controller]")]
    public class ConfigurationController : ControllerBase
    {
//----------------------------------------------------------------------------------------------------------------------
		private static object									MLock=new object();
		private static bool										MIsInitialized=false;
//----------------------------------------------------------------------------------------------------------------------
		private readonly IConfiguration							MConfiguration;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ConfigurationController(IConfiguration Configuration)
		{
			MConfiguration=Configuration;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigurationValueChanged(CConfigurationSectionComplex Value)
		{
			Console.WriteLine("!!!!! CONFIGURATION CHANGED. !!!!!");
			Console.WriteLine($"FIRST - [{Value.FirstValue.FirstName},{Value.FirstValue.LastName},{Value.FirstValue.Age}] SECOND - [{Value.SecondValue.FirstName},{Value.SecondValue.LastName},{Value.SecondValue.Age}].");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("SimpleValue")]
        public string GetSimpleValue()
        {
			string												Key="MySimpleValue";
			string												Value=MConfiguration[Key];

			return($"KEY [{Key}] VALUE [{Value}].");
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("NestedValues")]
        public string GetNestedValues()
        {
			// !!! Na ziskanie NESTED KEYS je mozne pouzit SYNTAX [KEY_1:...:KEY_N].
			string												Key1="MyParentKey:MyChildKey1";
			string												Key2="MyParentKey:MyChildKey2";
			string												Value1=MConfiguration[Key1];
			string												Value2=MConfiguration[Key2];

			return($"KEY 1 [{Key1}] VALUE 1 [{Value1}] KEY 2 [{Key2}] VALUE 2 [{Value2}].");
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("OptionsPattern1")]
        public CConfigurationSectionSimple GetOptionsPattern1()
        {
			string												Key="MySection1";
			CConfigurationSectionSimple							Value=new CConfigurationSectionSimple();

			// !!! CONFIGURATIONS sa namapuju na PROPERTIES daneho OBJECT.
			MConfiguration.Bind(Key,Value);

			return(Value);
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("OptionsPattern2")]
        public CConfigurationSectionComplex GetOptionsPattern2()
        {
			string												Key="MySection2";
			CConfigurationSectionComplex						Value=new CConfigurationSectionComplex();

			// !!! CONFIGURATIONS sa REKURZIVNE namapuju na PROPERTIES daneho OBJECT.
			MConfiguration.Bind(Key,Value);

			return(Value);
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("OptionsPattern3")]
        public CConfigurationSectionComplex GetOptionsPattern3()
        {
			string												Key="MySection2";

			// !!! Ziska sa CONFIGURATION SECTION.
			IConfigurationSection								Section=MConfiguration.GetSection(Key);

			// !!! CONFIGURATIONS sa REKURZIVNE namapuju na PROPERTIES daneho OBJECT.
			CConfigurationSectionComplex						Value=Section.Get<CConfigurationSectionComplex>();

			return(Value);
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("OptionsPattern4")]
		// !!! CONFIGURATION COMPLEX CLASS sa nacita pomocou DEPENDENCY INJECTION.
		// !!!!! CONFIGURATIONS sa NEZMENI, ked dojde k zmene CONFIGURATION FILE pocas behu PROGRAMU.
        public CConfigurationSectionComplex GetOptionsPattern4([FromServices] IOptions<CConfigurationSectionComplex> OptionsValue)
        {
			CConfigurationSectionComplex						Value=OptionsValue.Value;

			return(Value);
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("OptionsPattern5")]
		// !!! CONFIGURATION COMPLEX CLASS sa nacita pomocou DEPENDENCY INJECTION.
		// !!!!! CONFIGURATIONS sa ZMENI, ked dojde k zmene CONFIGURATION FILE pocas behu PROGRAMU.
        public CConfigurationSectionComplex GetOptionsPattern5([FromServices] IOptionsSnapshot<CConfigurationSectionComplex> OptionsValue)
        {
			CConfigurationSectionComplex						Value=OptionsValue.Value;

			return(Value);
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("OptionsPattern6")]
		// !!! CONFIGURATION COMPLEX CLASS sa nacita pomocou DEPENDENCY INJECTION.
		// !!!!! CONFIGURATIONS sa ZMENI, ked dojde k zmene CONFIGURATION FILE pocas behu PROGRAMU.
        public CConfigurationSectionComplex GetOptionsPattern6([FromServices] IOptionsMonitor<CConfigurationSectionComplex> OptionsValue)
        {
			lock(MLock)
			{
				if (MIsInitialized==false)
				{
					// !!! Zaregistruje sa odber CHANGES pri zmene CONFIGURATIONS v CONFIGURATION FILES.
					OptionsValue.OnChange<CConfigurationSectionComplex>(ConfigurationValueChanged);

					MIsInitialized=true;
				}
			}

			CConfigurationSectionComplex						Value=OptionsValue.CurrentValue;
			
			return(Value);
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("OptionsPattern7")]
		// !!! CONFIGURATION COMPLEX CLASS sa nacita pomocou DEPENDENCY INJECTION.
		// !!!!! CONFIGURATIONS sa ZMENI, ked dojde k zmene CONFIGURATION FILE pocas behu PROGRAMU.
        public CConfigurationSectionNamedComplex GetOptionsPattern7([FromServices] IOptionsSnapshot<CConfigurationSectionNamedComplex> OptionsValue)
        {
			// !!! Ziska sa NAMED CONFIGURATION.
			CConfigurationSectionNamedComplex					Value=OptionsValue.Get("MyNamedSection1");

			return(Value);
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("OptionsPattern8")]
		// !!! CONFIGURATION COMPLEX CLASS sa nacita pomocou DEPENDENCY INJECTION.
		// !!!!! CONFIGURATIONS sa ZMENI, ked dojde k zmene CONFIGURATION FILE pocas behu PROGRAMU.
        public CConfigurationSectionNamedComplex GetOptionsPattern8([FromServices] IOptionsSnapshot<CConfigurationSectionNamedComplex> OptionsValue)
        {
			// !!! Ziska sa NAMED CONFIGURATION.
			CConfigurationSectionNamedComplex					Value=OptionsValue.Get("MyNamedSection2");

			return(Value);
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("EnvironmentFileValues")]
        public string GetEnvironmentFileValues()
        {
			// !!! CONFIGURATION sa cita z CUSTOM JSON FILE, ktory je asociovany s aktualny ENVIRONEMENT.
			string												Key1="MySharedKeyEnvironment";
			string												Key2="MyKeyDevelopmentEnvironment";

			string												Value1=MConfiguration[Key1];
			string												Value2=MConfiguration[Key2];

			return($"KEY 1 [{Key1}] VALUE 1 [{Value1}] KEY 2 [{Key2}] VALUE 2 [{Value2}].");
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("CustomFileValue")]
        public string GetCustomFileValue()
        {
			// !!! CONFIGURATION sa cita z CUSTOM JSON FILE.
			string												Key="ValueFromCustomFile";
			string												Value=MConfiguration[Key];

			return($"KEY [{Key}] VALUE [{Value}].");
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("ValuesFromUserSecretFile")]
        public string GetValuesFromUserSecretFile()
        {
			// !!! CONFIGURATION sa cita z USER SECRET JSON FILE.
			string												Key1="MySharedKey1";
			string												Key2="MySecret:SuperSecret";

			string												Value1=MConfiguration[Key1];
			string												Value2=MConfiguration[Key2];

			return($"KEY 1 [{Key1}] VALUE 1 [{Value1}] KEY 2 [{Key2}] VALUE 2 [{Value2}].");
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("ValuesFromEnvironmentVariables")]
        public string GetValuesFromEnvironmentVariables()
        {
			// !!! CONFIGURATION sa cita z ENVIRONMENT VARIABLES.
			string												Key1="MySharedKey2";
			string												Key2="MyName:FirstName";
			string												Key3="MyName:LastName";
			string												Key4="MyName:Age";

			string												Value1=MConfiguration[Key1];
			string												Value2=MConfiguration[Key2];
			string												Value3=MConfiguration[Key3];
			string												Value4=MConfiguration[Key4];

			return($"KEY 1 [{Key1}] VALUE 1 [{Value1}] KEY 2 [{Key2}] VALUE 2 [{Value2}] KEY 3 [{Key3}] VALUE 3 [{Value3}] KEY 4 [{Key4}] VALUE 4 [{Value4}].");
        }
//----------------------------------------------------------------------------------------------------------------------
        [HttpGet("ValuesFromCommandLine")]
        public string GetValuesFromCommandLine()
        {
			// !!! CONFIGURATION sa cita z COMMAND LINE.
			string												Key1="MySharedKey3";
			string												Key2="MyCommandLine:MyValue";

			string												Value1=MConfiguration[Key1];
			string												Value2=MConfiguration[Key2];

			return($"KEY 1 [{Key1}] VALUE 1 [{Value1}] KEY 2 [{Key2}] VALUE 2 [{Value2}].");
        }
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------