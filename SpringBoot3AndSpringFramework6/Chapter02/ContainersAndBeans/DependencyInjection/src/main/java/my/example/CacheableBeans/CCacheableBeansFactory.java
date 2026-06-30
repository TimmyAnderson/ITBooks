package my.example.CacheableBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.cache.CacheManager;
import org.springframework.cache.annotation.EnableCaching;
import org.springframework.cache.concurrent.ConcurrentMapCacheManager;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
// !!!!! Tato ANNOTATION MUSI byt aplikovana, aby sa povolil CACHING.
@EnableCaching
public class CCacheableBeansFactory
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Tento BEAN MUSI byt vytvoreny, aby sa povolil CACHING.
    @Bean
    public CacheManager cacheManager()
    {
    	ConcurrentMapCacheManager								concurrentMapCacheManager=new ConcurrentMapCacheManager("MyCachableMethod");
    	
        return(concurrentMapCacheManager);
    }	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------