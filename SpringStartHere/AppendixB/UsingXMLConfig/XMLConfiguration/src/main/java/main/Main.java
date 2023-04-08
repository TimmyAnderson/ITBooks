package main;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.support.ClassPathXmlApplicationContext;
//----------------------------------------------------------------------------------------------------------------------
public class Main
{
//----------------------------------------------------------------------------------------------------------------------
    public static void main(String[] args)
    {
        ClassPathXmlApplicationContext							Context=new ClassPathXmlApplicationContext("Config.xml");
        
        CMyTest													MyTest=Context.getBean(CMyTest.class);
        
        Context.close();

        System.out.format("VALUE [%s] !\n",MyTest.getValue());
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------