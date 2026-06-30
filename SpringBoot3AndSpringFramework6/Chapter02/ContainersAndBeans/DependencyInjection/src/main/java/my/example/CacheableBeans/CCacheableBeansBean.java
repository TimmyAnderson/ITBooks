package my.example.CacheableBeans;
//----------------------------------------------------------------------------------------------------------------------
import java.time.LocalDateTime;

import org.springframework.cache.annotation.Cacheable;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CCacheableBeansBean
{
//----------------------------------------------------------------------------------------------------------------------
	@Cacheable(value="MyCachableMethod",key="#value",condition="#value<100")
	public String MyCachableMethod(Long value)
	{
		LocalDateTime											currentDateTime=LocalDateTime.now();
		String													result=currentDateTime.toString();
		
		return(result);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------