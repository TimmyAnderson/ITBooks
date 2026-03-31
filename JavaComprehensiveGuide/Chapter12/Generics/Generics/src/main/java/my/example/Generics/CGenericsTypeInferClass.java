package my.example.Generics;

import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
//----------------------------------------------------------------------------------------------------------------------
public abstract class CGenericsTypeInferClass<TType>
{
//----------------------------------------------------------------------------------------------------------------------
	public Type GetGenericsTypeTypeInformation()
	{
		Class<?>												classObject=this.getClass();
		Type													superClassObject=classObject.getGenericSuperclass();
		ParameterizedType										typedSuperClassObject=(ParameterizedType) superClassObject;
		Type[]													typeArguments=typedSuperClassObject.getActualTypeArguments();

		if (typeArguments.length>0)
		{
			Type												firstTypeArgument=typeArguments[0];

			return(firstTypeArgument);
		}
		else
		{
			return(null);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------