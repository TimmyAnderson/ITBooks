using System;
using System.Collections.Generic;
using System.Linq;
using ASPCoreFundamentals2.LogCategories;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using MyNamespace;
using MyNamespace.MySubNamespace;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals2
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class LoggingController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<LoggingController>				MLogger;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public LoggingController(ILogger<LoggingController> Logger)
		{
			MLogger=Logger;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ThrowException()
		{
			throw(new InvalidOperationException("My EXCEPTION !"));
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public LogLevel GetLogLevel(ILogger Logger)
		{
			LogLevel[]											LogLevels=Enum.GetValues<LogLevel>().OrderBy(P => P).ToArray();

			foreach(LogLevel LogLevel in LogLevels)
			{
				if (Logger.IsEnabled(LogLevel)==true)
				{
					return(LogLevel);
				}
			}

			return(LogLevel.None);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("SimpleLogging")]
		public string SimpleLogging()
		{
			MLogger.LogInformation("SIMPLE LOG MESSAGE !!!");

			return("LOG MESSAGE WRITTEN !");
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("LoggingLevels")]
		public string LoggingLevels()
		{
			MLogger.LogTrace("LEVEL [Trace] MESSAGE !!!");
			MLogger.LogDebug("LEVEL [Debug] MESSAGE !!!");
			MLogger.LogInformation("LEVEL [Information] MESSAGE !!!");
			MLogger.LogWarning("LEVEL [Warning] MESSAGE !!!");
			MLogger.LogError("LEVEL [Error] MESSAGE !!!");
			MLogger.LogCritical("LEVEL [Critical] MESSAGE !!!");

			return("LOG MESSAGE WRITTEN !");
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("CustomLogCategory1")]
		public string CustomLogCategory1([FromServices] ILogger<CLogCategory1> Logger)
		{
			LogLevel									CurrentLogLevel=GetLogLevel(Logger);
			string										Category=nameof(CLogCategory1);

			Logger.LogTrace($"CATEGORY [{Category}] LEVEL [{LogLevel.Trace}] MESSAGE !!!");
			Logger.LogDebug($"CATEGORY [{Category}] LEVEL [{LogLevel.Debug}] MESSAGE !!!");
			Logger.LogInformation($"CATEGORY [{Category}] LEVEL [{LogLevel.Information}] MESSAGE !!!");
			Logger.LogWarning($"CATEGORY [{Category}] LEVEL [{LogLevel.Warning}] MESSAGE !!!");
			Logger.LogError($"CATEGORY [{Category}] LEVEL [{LogLevel.Error}] MESSAGE !!!");
			Logger.LogCritical($"CATEGORY [{Category}] LEVEL [{LogLevel.Critical}] MESSAGE !!!");

			string										Result=$"CATEGORY [{Category}] has LOG CATEGORY [{CurrentLogLevel}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("CustomLogCategory2")]
		public string CustomLogCategory2([FromServices] ILogger<CLogCategory2> Logger)
		{
			LogLevel									CurrentLogLevel=GetLogLevel(Logger);
			string										Category=nameof(CLogCategory2);

			Logger.LogTrace($"CATEGORY [{Category}] LEVEL [{LogLevel.Trace}] MESSAGE !!!");
			Logger.LogDebug($"CATEGORY [{Category}] LEVEL [{LogLevel.Debug}] MESSAGE !!!");
			Logger.LogInformation($"CATEGORY [{Category}] LEVEL [{LogLevel.Information}] MESSAGE !!!");
			Logger.LogWarning($"CATEGORY [{Category}] LEVEL [{LogLevel.Warning}] MESSAGE !!!");
			Logger.LogError($"CATEGORY [{Category}] LEVEL [{LogLevel.Error}] MESSAGE !!!");
			Logger.LogCritical($"CATEGORY [{Category}] LEVEL [{LogLevel.Critical}] MESSAGE !!!");

			string										Result=$"CATEGORY [{Category}] has LOG CATEGORY [{CurrentLogLevel}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("CustomLogCategory3")]
		public string CustomLogCategory3([FromServices] ILogger<CLogCategory3> Logger)
		{
			LogLevel									CurrentLogLevel=GetLogLevel(Logger);
			string										Category=nameof(CLogCategory3);

			Logger.LogTrace($"CATEGORY [{Category}] LEVEL [{LogLevel.Trace}] MESSAGE !!!");
			Logger.LogDebug($"CATEGORY [{Category}] LEVEL [{LogLevel.Debug}] MESSAGE !!!");
			Logger.LogInformation($"CATEGORY [{Category}] LEVEL [{LogLevel.Information}] MESSAGE !!!");
			Logger.LogWarning($"CATEGORY [{Category}] LEVEL [{LogLevel.Warning}] MESSAGE !!!");
			Logger.LogError($"CATEGORY [{Category}] LEVEL [{LogLevel.Error}] MESSAGE !!!");
			Logger.LogCritical($"CATEGORY [{Category}] LEVEL [{LogLevel.Critical}] MESSAGE !!!");

			string										Result=$"CATEGORY [{Category}] has LOG CATEGORY [{CurrentLogLevel}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("CustomLogCategory4")]
		public string CustomLogCategory4([FromServices] ILogger<CLogCategory4> Logger)
		{
			LogLevel									CurrentLogLevel=GetLogLevel(Logger);
			string										Category=nameof(CLogCategory4);

			Logger.LogTrace($"CATEGORY [{Category}] LEVEL [{LogLevel.Trace}] MESSAGE !!!");
			Logger.LogDebug($"CATEGORY [{Category}] LEVEL [{LogLevel.Debug}] MESSAGE !!!");
			Logger.LogInformation($"CATEGORY [{Category}] LEVEL [{LogLevel.Information}] MESSAGE !!!");
			Logger.LogWarning($"CATEGORY [{Category}] LEVEL [{LogLevel.Warning}] MESSAGE !!!");
			Logger.LogError($"CATEGORY [{Category}] LEVEL [{LogLevel.Error}] MESSAGE !!!");
			Logger.LogCritical($"CATEGORY [{Category}] LEVEL [{LogLevel.Critical}] MESSAGE !!!");

			string										Result=$"CATEGORY [{Category}] has LOG CATEGORY [{CurrentLogLevel}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("LogComplexMessage")]
		public string LogComplexMessage()
		{
			try
			{
				ThrowException();
			}
			catch(Exception E)
			{
				// !!! VALUE [1000] je EVENT ID.
				MLogger.LogError(1000,E,"This is COMPLEX MESSAGE with PARAMETER 1 [{Parameter1}] PARAMETER 2 [{Parameter2}].","My PARAM A","My PARAM B");
			}

			return("LOG MESSAGE WRITTEN !");
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("LogToSerilog")]
		public string LogToSerilog()
		{
			MLogger.LogCritical("This MESSAGE will be WRITTEN to SERILOG.");

			return("LOG MESSAGE WRITTEN !");
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("LogStructuredLogMessage")]
		public string LogStructuredLogMessage()
		{
			MLogger.LogCritical($"This is UNSTRUCTURED LOG with PARAMETER 1 [{100}] and PARAMETER 2 [{200}].");

			// !!! Toto je STRUCUTRED LOG MESSAGE.
			MLogger.LogCritical("This is STRUCTURED LOG with PARAMETER 1 [{MY_PARAM_1}] and PARAMETER 2 [{MY_PARAM_2}].",100,200);

			return("LOG MESSAGE WRITTEN !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------