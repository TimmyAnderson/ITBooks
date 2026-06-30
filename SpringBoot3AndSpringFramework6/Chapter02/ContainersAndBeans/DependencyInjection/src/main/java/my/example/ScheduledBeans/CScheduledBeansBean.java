package my.example.ScheduledBeans;
//----------------------------------------------------------------------------------------------------------------------
import java.time.LocalDateTime;

import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CScheduledBeansBean
{
//----------------------------------------------------------------------------------------------------------------------
	//@Scheduled(fixedDelay=1000)
	// !!! Pouzitie SPRING EXPRESSION LANGUAGE EXPRESSION.
	@Scheduled(fixedDelayString = "#{1==1 ? 1000 : 2000}")	
	public void MyScheduledMethod()
	{
		LocalDateTime											currentDateTime=LocalDateTime.now();
		String													result=currentDateTime.toString();
		
		System.out.printf("!!!!! CURRENT TIME [%s].\n",result);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------