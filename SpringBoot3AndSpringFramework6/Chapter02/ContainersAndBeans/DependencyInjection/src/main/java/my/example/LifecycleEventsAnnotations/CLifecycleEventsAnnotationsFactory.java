package my.example.LifecycleEventsAnnotations;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CLifecycleEventsAnnotationsFactory
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@Bean] umoznuje definovat POST CONSTRUCT a PRE CREATE CALLBACKS.
	@Bean(initMethod="Bean3Create",destroyMethod="Bean3Destory")
	public CLifecycleEventsAnnotationsBean3 MyBean3()
	{
		CLifecycleEventsAnnotationsBean3						bean=new CLifecycleEventsAnnotationsBean3();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CLifecycleEventsAnnotationsBean4 MyBean4()
	{
		CLifecycleEventsAnnotationsBean4						bean=new CLifecycleEventsAnnotationsBean4();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CLifecycleEventsAnnotationsBean5 MyBean5()
	{
		CLifecycleEventsAnnotationsBean5						bean=new CLifecycleEventsAnnotationsBean5();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CLifecycleEventsAnnotationsBean6 MyBean6()
	{
		CLifecycleEventsAnnotationsBean6						bean=new CLifecycleEventsAnnotationsBean6();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean(initMethod="BaseClassBean2Create",destroyMethod="BaseInterfaceBean2Destory")
	public CLifecycleEventsAnnotationsDerivedClassBean2 MyDerivedClassBean2()
	{
		CLifecycleEventsAnnotationsDerivedClassBean2			bean=new CLifecycleEventsAnnotationsDerivedClassBean2();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------