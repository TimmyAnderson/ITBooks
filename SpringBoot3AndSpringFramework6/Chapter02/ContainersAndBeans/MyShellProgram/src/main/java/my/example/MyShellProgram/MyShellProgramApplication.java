package my.example.MyShellProgram;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.Banner;
//----------------------------------------------------------------------------------------------------------------------
@SpringBootApplication
public class MyShellProgramApplication
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
		
		System.out.println("MAIN START.");
		
		SpringApplication										springApplication=new SpringApplication(MyShellProgramApplication.class);

		springApplication.setBannerMode(Banner.Mode.OFF);
		springApplication.setLogStartupInfo(false);
		
		springApplication.run(args);
		
		System.out.println("MAIN END.");
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------