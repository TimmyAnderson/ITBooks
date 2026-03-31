package my.example.IntroductionToSpringBoot;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
//----------------------------------------------------------------------------------------------------------------------
@SpringBootApplication
public class IntroductionToSpringBootApplication
{
//----------------------------------------------------------------------------------------------------------------------
	private static void PrintSeparator()
	{
		System.out.println("--------------------------------------------------------------------------------");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public static void main(String[] args)
	{
		PrintSeparator();
	        System.out.println("HELLO WORLD - STEP 1 !!!");
		
		SpringApplication.run(IntroductionToSpringBootApplication.class,args);

	        System.out.println("HELLO WORLD - STEP 2 !!!");
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------