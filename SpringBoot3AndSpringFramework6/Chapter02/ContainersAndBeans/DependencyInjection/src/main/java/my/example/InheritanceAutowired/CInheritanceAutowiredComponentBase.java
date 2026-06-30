package my.example.InheritanceAutowired;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public abstract class CInheritanceAutowiredComponentBase
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@Autowired] sa aplikuje aj v BASE CLASSES.
	@Autowired
	protected CInheritanceAutowiredBean1						bean1;
	protected CInheritanceAutowiredBean2						bean2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@Autowired] sa aplikuje aj v BASE CLASSES.
	@Autowired
	public void MySetter1(CInheritanceAutowiredBean2 bean2)
	{
		System.out.printf("BEAN SETTER 1 CALLED.\n");
		
		this.bean2=bean2;
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@Autowired] sa aplikuje aj v BASE CLASSES.
	@Autowired
	public abstract void MySetter2(CInheritanceAutowiredBean3 bean3);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------