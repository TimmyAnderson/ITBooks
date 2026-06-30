package my.example.LifecycleEventsAnnotations;
//----------------------------------------------------------------------------------------------------------------------
public interface ILifecycleEventsAnnotationsBaseInterfaceBean2
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD je oznacena ako PRE DESTROY CALLBACK v ANNOTATION [@Bean].
	default void BaseInterfaceBean2Destory()
	{
		System.out.printf("!!!!! BASE INTERFACE BEAN 2 - PRE DESTROY CALLED.\n");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------