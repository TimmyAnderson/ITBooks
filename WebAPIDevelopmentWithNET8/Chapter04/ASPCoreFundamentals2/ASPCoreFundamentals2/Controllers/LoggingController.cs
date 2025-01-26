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
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------