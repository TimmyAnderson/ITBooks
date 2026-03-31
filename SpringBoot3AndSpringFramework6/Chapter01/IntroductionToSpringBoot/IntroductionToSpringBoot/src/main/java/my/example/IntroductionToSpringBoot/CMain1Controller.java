package my.example.IntroductionToSpringBoot;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
//----------------------------------------------------------------------------------------------------------------------
@RestController
@RequestMapping("/Main1")
public final class CMain1Controller
{
//----------------------------------------------------------------------------------------------------------------------
	private final Logger										MLogger;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CMain1Controller()
	{
		MLogger=LoggerFactory.getLogger(getClass());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@GetMapping("/HelloWorld")
	public String MyMethod()
	{
		MLogger.trace("TRACE - METHOD [{}] CALLED.","MyMethod");
		MLogger.debug("DEBUG - METHOD [{}] CALLED.","MyMethod");
		MLogger.info("INFO - METHOD [{}] CALLED.","MyMethod");
		MLogger.warn("WARNING - METHOD [{}] CALLED.","MyMethod");
		MLogger.error("ERROR - METHOD [{}] CALLED.","MyMethod");
		
		String													Response="HELLO WORLD 1 !";
		
		return(Response);
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------