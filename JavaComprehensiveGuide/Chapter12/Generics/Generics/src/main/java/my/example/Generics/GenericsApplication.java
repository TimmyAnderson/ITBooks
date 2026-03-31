package my.example.Generics;

import java.util.ArrayList;
import java.util.List;
import java.lang.constant.Constable;
import java.lang.constant.ConstantDesc;
import java.lang.reflect.Array;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Type;
//----------------------------------------------------------------------------------------------------------------------
public class GenericsApplication
{
//----------------------------------------------------------------------------------------------------------------------
	private static void PrintSeparator()
	{
		System.out.println("--------------------------------------------------------------------------------");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestTypeCastException()
	{
		try
		{
			Object													Object1="OBJECT 1";
			String													TypedObject=(String) Object1;
			
			System.out.printf("OBJECT 1 [%s].\n",TypedObject);
		}
		catch(ClassCastException E)
		{
			System.out.printf("EXCEPTION [%s].\n",E.getMessage());
		}

		PrintSeparator();
		
		try
		{
			Object													Object1=Integer.valueOf(100);
			String													TypedObject=(String) Object1;
			
			System.out.printf("OBJECT 2 [%s].\n",TypedObject);
		}
		catch(ClassCastException E)
		{
			System.out.printf("EXCEPTION [%s].\n",E.getMessage());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericClass()
	{
		CGenericsClass<String,Long>								genericsClass=new CGenericsClass<String,Long>("TIMMY",12l);

		System.out.printf("CLASS - VALUE 1 [%s].\n",genericsClass.getValue1());
		System.out.printf("CLASS - VALUE 2 [%s].\n",genericsClass.getValue2());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericInterfaces()
	{
		{
			IGenericsInterface<String,Long>						genericsInterface=new CNonGenericsClassImplementingGenericInterface("TIMMY",12l);

			System.out.printf("INTERFACE - NON-GENERIC TYPE - VALUE 1 [%s] VALUE 2 [%s].\n",genericsInterface.getValue1(),genericsInterface.getValue2());
		}

		PrintSeparator();
		
		{
			IGenericsInterface<String,Long>						genericsInterface=new CGenericsClassImplementingGenericInterface<String,Long>("TIMMY",12l);

			System.out.printf("INTERFACE - GENERIC TYPE - VALUE 1 [%s] VALUE 2 [%s].\n",genericsInterface.getValue1(),genericsInterface.getValue2());
		}
		
		PrintSeparator();
		
		{
			// !!! TYPE [Void] sa pouziva ako GENERIC TYPE nie je v TYPE pouzity.
			IGenericsInterface<Void,Void>						genericsInterface=new CVoidClassImplementingGenericInterface();

			System.out.printf("INTERFACE - GENERIC TYPE - VALUE 1 [%s] VALUE 2 [%s].\n",genericsInterface.getValue1(),genericsInterface.getValue2());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericRecord()
	{
		CGenericsRecord<String,Long>							genericsRecord=new CGenericsRecord<String,Long>("TIMMY",12l);

		System.out.printf("RECORD - VALUE 1 [%s].\n",genericsRecord.value1());
		System.out.printf("RECORD - VALUE 2 [%s].\n",genericsRecord.value2());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestNestedGenericTypes()
	{
		// !!! JAVA umoznuje pouzitie GENERICS TYPES ako TYPE ARGUMENTS GENERIC TYPES.
		CGenericsClass<CGenericsClass<String,Long>,CGenericsClass<Long,String>>	genericsClass=new CGenericsClass<CGenericsClass<String,Long>,CGenericsClass<Long,String>>(new CGenericsClass<String,Long>("TIMMY",12l),new CGenericsClass<Long,String>(13l,"JENNY"));

		System.out.printf("NESTED TYPE - VALUE 1 - VALUE 1 [%s].\n",genericsClass.getValue1().getValue1());
		System.out.printf("NESTED TYPE - VALUE 1 - VALUE 2 [%s].\n",genericsClass.getValue1().getValue2());
		System.out.printf("NESTED TYPE - VALUE 2 - VALUE 1 [%s].\n",genericsClass.getValue2().getValue1());
		System.out.printf("NESTED TYPE - VALUE 2 - VALUE 2 [%s].\n",genericsClass.getValue2().getValue2());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestArraysAsTypeArguments()
	{
		// !!! ARRAYS je mozne pouzit ako TYPE ARGUMENTS.
		CGenericsClass<String[],Long>							genericsClass=new CGenericsClass<String[],Long>(new String[]{"TIMMY","ANDERSON"},12l);
		
		for(int index=0;index<genericsClass.getValue1().length;index++)
		{
			System.out.printf("ARRAYS AS TYPE ARGUMENTS - INDEX [%d] VALUE 1 [%s].\n",(index+1),genericsClass.getValue1()[index]);
		}
		
		System.out.printf("ARRAYS AS TYPE ARGUMENTS - VALUE 2 [%s].\n",genericsClass.getValue2());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	/*
	private static void TestGenericsArrays()
	{
		// !!! JAVA umoznuje deklaraciu GENERICS ARRAYS.
		CGenericsClass<String,Long>[]							genericsArray;
		
		// !!!!! JAVA vsak NEPODPORUJE vytvaranie instancii GENERICS ARRAYS.
		genericsArray=new CGenericsClass<String,Long>[2];
		
		for(int index=0;index<genericsArray.length;index++)
		{
			CGenericsClass<String,Long>							arrayItem=genericsArray[index];
		
			System.out.printf("GENERICS ARRAYS - INDEX [%d] VALUE 1 [%s].\n",(index+1),arrayItem.getValue1());
			System.out.printf("GENERICS ARRAYS - INDEX [%d] VALUE 2 [%s].\n",(index+1),arrayItem.getValue2());
		}
	}
	*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void DiamondOperatorParameter(CGenericsClass<String,Long> genericsClass)
	{
		System.out.printf("METHOD PARAMETER - VALUE 1 [%s] VALUE 2 [%s].\n",genericsClass.getValue1(),genericsClass.getValue2());
	}
//----------------------------------------------------------------------------------------------------------------------
	private static CGenericsClass<String,Long> DiamondOperatorReturnValue()
	{
		// !!! DIAMOND OPERATOR je mozne pouzit v TYPES pouzitych ako METHOD RETURN VALUES.
		return(new CGenericsClass<>("TIMMY",12l));
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestDiamondOperator()
	{
		{
			// !!! DIAMOND OPERATOR je mozne pouzit v OPERATOR NEW pre INITIALIZATION.
			CGenericsClass<String,Long>							genericsClass=new CGenericsClass<>("TIMMY",12l);
			
			System.out.printf("NEW 1 - VALUE 1 [%s] VALUE 2 [%s].\n",genericsClass.getValue1(),genericsClass.getValue2());
		}

		PrintSeparator();
		
		{
			CGenericsClass<String,Long>							genericsClass;
			
			// !!! DIAMOND OPERATOR je mozne pouzit v OPERATOR NEW MIMO INITIALIZATION.
			genericsClass=new CGenericsClass<>("TIMMY",12l);
			
			System.out.printf("NEW 2 - VALUE 1 [%s] VALUE 2 [%s].\n",genericsClass.getValue1(),genericsClass.getValue2());
		}

		PrintSeparator();
		
		{
			// !!! DIAMOND OPERATOR je mozne pouzit v TYPES pouzitych ako METHOD PARAMETERS.
			DiamondOperatorParameter(new CGenericsClass<>("TIMMY",12l));
		}

		PrintSeparator();

		{
			CGenericsClass<String,Long>							genericsClass=DiamondOperatorReturnValue();
			
			System.out.printf("METHOD RETURN VALUE - VALUE 1 [%s] VALUE 2 [%s].\n",genericsClass.getValue1(),genericsClass.getValue2());
		}

		PrintSeparator();
		
		{
			// !!!!! OPERATOR DIAMOND JE mozne pouzit aj v NESTED GENERICS TYPES, ak sa OPERATOR DIAMOND pouzije na definiciu celeho TYPE. 
			CGenericsClass<CGenericsClass<String,Long>,CGenericsClass<Long,String>>	genericsClass=new CGenericsClass<>(new CGenericsClass<>("TIMMY",12l),new CGenericsClass<>(13l,"JENNY"));
		
			System.out.printf("NESTED TYPE FULL TYPE - VALUE 1 ([%s],[%s]) VALUE 2 ([%s],[%s]).\n",genericsClass.getValue1().getValue1(),genericsClass.getValue1().getValue2(),genericsClass.getValue2().getValue1(),genericsClass.getValue2().getValue2());
			
			// !!!!! OPERATOR DIAMOND JE mozne pouzit aj v NESTED GENERICS TYPES, ak sa OPERATOR DIAMOND pouzije na definiciu celeho TYPE. 
			ArrayList<ArrayList<String>>  						list=new ArrayList<ArrayList<String>>();
			
			System.out.printf("NESTED TYPE FULL TYPE - LIST SIZE [%s].\n",list.size());
		}

		/*
		PrintSeparator();
	
		{
			// !!!!! OPERATOR DIAMOND NIE JE mozne pouzit v NESTED GENERICS TYPES, ak sa DIAMOND OPERATOR pouzije na definiciu INTERNEHO TYPE. 
			CGenericsClass<CGenericsClass<String,Long>,CGenericsClass<Long,String>>	genericsClass=new CGenericsClass<CGenericsClass<>,CGenericsClass<>>(new CGenericsClass<String,Long>("TIMMY",12l),new CGenericsClass<Long,String>(13l,"JENNY"));
			
			System.out.printf("NESTED TYPE INTERNAL TYPE - VALUE 1 ([%s],[%s]) VALUE 2 ([%s],[%s]).\n",genericsClass.getValue1().getValue1(),genericsClass.getValue1().getValue2(),genericsClass.getValue2().getValue1(),genericsClass.getValue2().getValue2());
			
			// !!!!! OPERATOR DIAMOND NIE JE mozne pouzit v NESTED GENERICS TYPES, ak sa DIAMOND OPERATOR pouzije na definiciu INTERNEHO TYPE. 
			ArrayList<ArrayList<String>>  						list=new ArrayList<ArrayList<>>();
			
			System.out.printf("NESTED TYPE FULL TYPE - LIST SIZE [%s].\n",list.size());
		}
		*/

		PrintSeparator();
		
		{
			CGenericsClass<String,Long>							genericsClass=new CGenericsClass<String,Long>("TIMMY",12l).CreateCopy();
			
			System.out.printf("CALLING METHOD NO DIMANOD OPERATOR - VALUE 1 [%s] VALUE 2 [%s].\n",genericsClass.getValue1(),genericsClass.getValue2());
		}

		PrintSeparator();
		
		{
			// !!!!! OPERATOR DIAMOND JE mozne pouzit ak sa za OPERATOR NEW vola dalsia METHOD, ak CONSTRUCTOR ma definovane PARAMETERS z ktorych je mozne zistit jeho TYPE.
			CGenericsClass<String,Long>							genericsClass=new CGenericsClass<>("TIMMY",12l).CreateCopy();
			
			System.out.printf("CALLING METHOD WITH DIMANOD OPERATOR - OK - VALUE 1 [%s] VALUE 2 [%s].\n",genericsClass.getValue1(),genericsClass.getValue2());
		}

		/*
		PrintSeparator();
		
		{
			// !!!!! OPERATOR DIAMOND NIE JE mozne pouzit ak sa za OPERATOR NEW vola dalsia METHOD, pricom sa pouzije DEFAULT CONSTRUCTOR.
			CGenericsClass<String,Long>							genericsClass=new CGenericsClass<>().CreateCopy();
			
			System.out.printf("CALLING METHOD WITH DIMANOD OPERATOR - ERROR - VALUE 1 [%s] VALUE 2 [%s].\n",genericsClass.getValue1(),genericsClass.getValue2());
		}
		*/
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static <TType> TType MethodGenericsClassGenericsMethods()
	{
		System.out.println("STATIC GENERICS METHOD CALLED.");
		
		return(null);
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericsClassGenericsMethods()
	{
		{
			// !!! Vola sa NON-GENERICS CONSTRUCTOR.
			CGenericsClassGenericsMethods<String>				object=new CGenericsClassGenericsMethods<String>("TIMMY");
			
			System.out.printf("CLASS VALUE [%s].\n",object.getClassValue());
		}
		
		PrintSeparator();

		{
			// !!! Vola sa GENERICS CONSTRUCTOR.
			// !!! METHOD TYPE PARAMETER je EXPLICITNE zadany.
			CGenericsClassGenericsMethods<String>				object=new <Long>CGenericsClassGenericsMethods<String>("TIMMY",12l);
			
			System.out.printf("CLASS VALUE [%s].\n",object.getClassValue());
		}
		
		PrintSeparator();

		{
			CGenericsClassGenericsMethods<String>				object=new CGenericsClassGenericsMethods<String>("TIMMY");
			
			// !!! Vola sa NON-STATIC NON-GENERICS METHOD.
			String												returnValue=object.NonStaticNonGenericsMethod();
			
			System.out.printf("GENERICS CLASS - NON-STATIC NON-GENERICS METHOD - RETURN VALUE [%s].\n",returnValue);
			
			System.out.printf("CLASS VALUE [%s].\n",object.getClassValue());
		}

		PrintSeparator();

		{
			CGenericsClassGenericsMethods<String>				object=new CGenericsClassGenericsMethods<String>("TIMMY");
			
			// !!! Vola sa NON-STATIC GENERICS METHOD.
			// !!! METHOD TYPE PARAMETER je INFERED.
			String												returnValueInfered=object.NonStaticGenericsMethod(12l);
			
			System.out.printf("GENERICS CLASS - NON-STATIC GENERICS METHOD - RETURN VALUE INFERED [%s].\n",returnValueInfered);

			// !!! Vola sa NON-STATIC GENERICS METHOD.
			// !!! METHOD TYPE PARAMETER je zadany EXPLICITNE.
			String												returnValueExplicit=object.<Long>NonStaticGenericsMethod(12l);
			
			System.out.printf("GENERICS CLASS - NON-STATIC GENERICS METHOD - RETURN VALUE EXPLICIT [%s].\n",returnValueExplicit);
			
			System.out.printf("CLASS VALUE [%s].\n",object.getClassValue());
		}

		PrintSeparator();

		{
			// !!! Vola sa STATIC NON-GENERICS METHOD.
			CGenericsClassGenericsMethods.StaticNonGenericsMethod("TIMMY");
			
			/*
			// !!! Vola sa STATIC NON-GENERICS METHOD.
			// !!!!! JAVA NEUMOZNUJE v STATIC METHODS pouzit CLASS TYPE ARGUMENTS.
			CGenericsClassGenericsMethods.StaticNonGenericsMethodClassValue("TIMMY");
			*/
		}

		PrintSeparator();

		{
			// !!! Vola sa STATIC GENERICS METHOD.
			CGenericsClassGenericsMethods.StaticGenericsMethod("JENNY");
		}

		PrintSeparator();
		
		{
			// !!! Pri volani STATIC GENERICS METHOD s EXPLICITNE zadanymi TYPE ARGUMENTS, MUSI byt najprv zadany TYPE NAME.
			GenericsApplication.<CInteger>MethodGenericsClassGenericsMethods();			
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestNonGenericsClassGenericsMethods()
	{
		{
			// !!! Vola sa NON-GENERICS CONSTRUCTOR.
			CNonGenericsClassGenericsMethods					object=new CNonGenericsClassGenericsMethods("TIMMY");
			
			System.out.printf("CLASS VALUE [%s].\n",object.getClassValue());
		}
		
		PrintSeparator();

		{
			// !!! Vola sa GENERICS CONSTRUCTOR.
			// !!! METHOD TYPE PARAMETER je EXPLICITNE zadany.
			CNonGenericsClassGenericsMethods					object=new <Long>CNonGenericsClassGenericsMethods("TIMMY",12l);
			
			System.out.printf("CLASS VALUE [%s].\n",object.getClassValue());
		}
		
		PrintSeparator();

		{
			CNonGenericsClassGenericsMethods					object=new CNonGenericsClassGenericsMethods("TIMMY");
			
			// !!! Vola sa NON-STATIC NON-GENERICS METHOD.
			String												returnValue=object.NonStaticNonGenericsMethod();
			
			System.out.printf("NON-GENERICS CLASS - NON-STATIC NON-GENERICS METHOD - RETURN VALUE [%s].\n",returnValue);
			
			System.out.printf("CLASS VALUE [%s].\n",object.getClassValue());
		}

		PrintSeparator();

		{
			CNonGenericsClassGenericsMethods					object=new CNonGenericsClassGenericsMethods("TIMMY");
			
			// !!! Vola sa NON-STATIC GENERICS METHOD.
			// !!! METHOD TYPE PARAMETER je INFERED.
			String												returnValueInfered=object.NonStaticGenericsMethod(12l);
			
			System.out.printf("NON-GENERICS CLASS - NON-STATIC GENERICS METHOD - RETURN VALUE INFERED [%s].\n",returnValueInfered);

			// !!! Vola sa NON-STATIC GENERICS METHOD.
			// !!! METHOD TYPE PARAMETER je zadany EXPLICITNE.
			String												returnValueExplicit=object.<Long>NonStaticGenericsMethod(12l);
			
			System.out.printf("NON-GENERICS CLASS - NON-STATIC GENERICS METHOD - RETURN VALUE EXPLICIT [%s].\n",returnValueExplicit);
			
			System.out.printf("CLASS VALUE [%s].\n",object.getClassValue());
		}
	
		PrintSeparator();

		{
			// !!! Vola sa STATIC NON-GENERICS METHOD.
			CNonGenericsClassGenericsMethods.StaticNonGenericsMethod("TIMMY");
		}

		PrintSeparator();

		{
			// !!! Vola sa STATIC GENERICS METHOD.
			CNonGenericsClassGenericsMethods.StaticGenericsMethod("JENNY");
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericsMethodTypeInference()
	{
		{
			// !!! Spolocny TYPE je TYPE [String].
			String												returnValue=CGenericsMethodTypeInference.GenericsMethod("TIMMY","JENNY",true);

			System.out.printf("(\"TIMMY\",\"JENNY\") - RETURN VALUE [%s].\n",returnValue);
		}

		PrintSeparator();

		{
			// !!! TYPE [String] je DERIVED z TYPE [Object] a implementuje INTERFACE [Serializable], INTERFACE [Comparable<String>], INTERFACE [CharSequence], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			// !!! TYPE [Long] je DERIVED z TYPE [Object] a implementuje INTERFACE [Comparable<Long>], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			// !!! Spolocny TYPE je TYPE [Number], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			Object												returnValue=CGenericsMethodTypeInference.GenericsMethod("TIMMY",12l,false);

			System.out.printf("(\"TIMMY\",12l) - RETURN VALUE [%s].\n",returnValue);
		}

		PrintSeparator();

		{
			// !!! TYPE [String] je DERIVED z TYPE [Object] a implementuje INTERFACE [Serializable], INTERFACE [Comparable<String>], INTERFACE [CharSequence], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			// !!! TYPE [Long] je DERIVED z TYPE [Object] a implementuje INTERFACE [Comparable<Long>], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			// !!! Spolocny TYPE je TYPE [Number], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			Constable											returnValue=CGenericsMethodTypeInference.GenericsMethod("TIMMY",12l,false);

			System.out.printf("(\"TIMMY\",12l) - RETURN VALUE [%s].\n",returnValue);
		}

		PrintSeparator();
		
		{
			// !!! TYPE [String] je DERIVED z TYPE [Object] a implementuje INTERFACE [Serializable], INTERFACE [Comparable<String>], INTERFACE [CharSequence], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			// !!! TYPE [Long] je DERIVED z TYPE [Object] a implementuje INTERFACE [Comparable<Long>], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			// !!! Spolocny TYPE je TYPE [Number], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			ConstantDesc										returnValue=CGenericsMethodTypeInference.GenericsMethod("TIMMY",12l,false);

			System.out.printf("(\"TIMMY\",12l) - RETURN VALUE [%s].\n",returnValue);
		}
		
		PrintSeparator();
		
		{
			// !!! TYPE [Integer] je DERIVED z TYPE [Object] a implementuje INTERFACE [Comparable<Integer>], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			// !!! TYPE [Long] je DERIVED z TYPE [Object] a implementuje INTERFACE [Comparable<Long>], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			// !!! Spolocny TYPE je TYPE [Number], INTERFACE [Constable] a INTERFACE [ConstantDesc].
			Number												returnValue=CGenericsMethodTypeInference.GenericsMethod(150,12l,false);

			System.out.printf("(150,12l) - RETURN VALUE [%s].\n",returnValue);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericsMethodDiamondOperator()
	{
		// !!! METHOD pouziva DIAMOND OPERATOR.
		CGenericsMethodDiamondOperator<String>					object=CGenericsMethodDiamondOperator.GenericsMethod("TIMMY");
		
		System.out.printf("VALUE [%s].\n",object.getClassValue());
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	/*
	private static void TestTypeErasureOperatorNew()
	{
		CTypeErasureOperatorNew<String>							object=new CTypeErasureOperatorNew<String>();

		String													value=object.CreateNewObject();
		
		System.out.printf("VALUE [%s].\n",value);
	}
	*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	/*
	private static void TestTypeErasureOperatorInstanceOf()
	{
		Object													object=new CGenericsClass<String,Long>("TIMMY",12l);

		// !!! JAVA NEUMOZNUJE pouzitie OPERATOR [instanceof] pre GENERICS TYPES.
		if ((object instanceof CGenericsClass<String,Long>)==true)
		{
			CGenericsClass<String,Long>							typedObject=(CGenericsClass<String,Long>) object;

			System.out.printf("OBJECT - VALUE 1 [%s] VALUE 2 [%s].\n",typedObject.getValue1(),typedObject.getValue2());
		}
		else
		{
			System.out.printf("INVALID TYPE.\n");
		}
	}
	*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestTypeErasureTypeCasting()
	{
		{
			Object												object=new CGenericsClass<String,Long>("TIMMY",12l);
			
			// !!! JAVA UMOZNUJE CONVERSION na GENERICS TYPE.
			// !!!!! COMPILER hodi WARNING.
			CGenericsClass<String,Long>							typedObject=(CGenericsClass<String,Long>) object;
			
			System.out.printf("OBJECT - VALUE 1 [%s] VALUE 2 [%s].\n",typedObject.getValue1(),typedObject.getValue2());
		}
		
		/*
		PrintSeparator();
		
		{
			CGenericsClass<String,Long>							object=new CGenericsClass<String,Long>("TIMMY",12l);
	
			// !!! TYPE CASTING pre GENERICS TYPES nie je mozny.
			CGenericsClass<Object,Object>						typedObject=(CGenericsClass<Object,Object>) object;
			
			System.out.printf("OBJECT - VALUE 1 [%s] VALUE 2 [%s].\n",typedObject.getValue1(),typedObject.getValue2());
		}
		*/
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestTypeErasureClassKeyword()
	{
		{
			// !!! JAVA UMOZNUJE pouzit KEYWORD [class] pre GENERICS TYPES ak NIE su pouzite TYPE PARAMETERS.
			// !!!!! COMPILER hodi WARNING.
			Class<CGenericsClass>								classObject=CGenericsClass.class;
		
			System.out.printf("CLASS NAME [%s].\n",classObject.getName());
		}
		
		/*
		PrintSeparator();
		
		{
			// !!! JAVA NEUMOZNUJE pouzit KEYWORD [class] pre GENERICS TYPES.
			Class<CGenericsClass<String,Long>>					classObject=CGenericsClass<String,Long>.class;
			
			System.out.printf("CLASS NAME [%s].\n",classObject.getName());
		}
		*/
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	/*
	private static void TestTypeErasureGenericsException()
	{
		try
		{
			Exception											exception=new CTypeErasureGenericsException<Long>();
			
			throw(exception);
		}
		catch(CTypeErasureGenericsException<Long> E)
		{
			System.out.printf("EXCEPTION [%s].\n",E.getMessage());
		}
		catch(CTypeErasureGenericsException<String> E)
		{
			System.out.printf("EXCEPTION [%s].\n",E.getMessage());
		}
		catch(Exception E)
		{
			System.out.printf("EXCEPTION [%s].\n",E.getMessage());
		}
	}
	*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	/*
	private static void TestTypeErasureStaticMembers()
	{
		// !!! JAVA neumoznuje deklarovanie STATIC METHODS.
		Object													object=CTypeErasureStaticMembers.GetStaticField();

		System.out.printf("VALUE [%s].\n",object);
		
		// !!! JAVA neumoznuje deklarovanie STATIC METHODS.
		CTypeErasureStaticMembers.SetStaticField("TIMMY");
	}
	*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestTypeErasureMethodOverloadingInGenericClass()
	{
		{
			CTypeErasureMethodOverloadingInGenericClass<String>	object=new CTypeErasureMethodOverloadingInGenericClass<String>();
			
			object.OverloadedMethod("TIMMY");
		}

		PrintSeparator();
		
		{
			CTypeErasureMethodOverloadingInGenericClass<String>	object=new CTypeErasureMethodOverloadingInGenericClass<String>();
			
			object.OverloadedMethod(12);
		}

		PrintSeparator();
		
		{
			CTypeErasureMethodOverloadingInGenericClass<String>	object=new CTypeErasureMethodOverloadingInGenericClass<String>();
			
			object.OverloadedMethod(12l);
		}
		
		/*
		PrintSeparator();
		
		{
			CTypeErasureMethodOverloadingInGenericClass<Long>	object=new CTypeErasureMethodOverloadingInGenericClass<Long>();
		
			// !!! JAVA hodi ERROR, pretoze CLASS obsahuje OVERLOADED METHOD pre TYPE [Long] 
			object.OverloadedMethod(12l);
		}
		*/
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	/*
	// !!! JAVA NEUMOZNUJE METHOD OVERLOADING na zaklade GENERIC TYPES.
	private static void TypeErasureMethodOverloadingByGenericType(CGenericsClass<String,Integer> value)
	{
		System.out.printf("CGenericsClass<String,Integer> - VALUE 1 [%s] VALUE 2 [%s].\n",value.getValue1(),value.getValue2());
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! JAVA NEUMOZNUJE METHOD OVERLOADING na zaklade GENERIC TYPES.
	private static void TypeErasureMethodOverloadingByGenericType(CGenericsClass<String,Long> value)
	{
		System.out.printf("CGenericsClass<String,Long> - VALUE 1 [%s] VALUE 2 [%s].\n",value.getValue1(),value.getValue2());
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestTypeErasureMethodOverloadingByGenericType()
	{
		TypeErasureMethodOverloadingByGenericType(new CGenericsClass<String,Integer>("TIMMY",12));
		
		TypeErasureMethodOverloadingByGenericType(new CGenericsClass<String,Long>("TIMMY",12l));
	}
	*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TypeErasureGenericsArrays()
	{
		{
			// !!! JAVA umoznuje definovat ARRAYS pre GENERICS TYPES, ak sa pouzije RAW GENERICS TYPE.
			CTypeErasureGenericsArrays<String>[]				array=new CTypeErasureGenericsArrays[2];
			
			array[0]=new CTypeErasureGenericsArrays<String>("TIMMY");
			array[1]=new CTypeErasureGenericsArrays<String>("JENNY");
			
			for(CTypeErasureGenericsArrays<String> item : array)
			{
				System.out.printf("RAW GENERICS TYPE ARRAY ITEM - VALUE [%s].\n",item.getField());
			}
		}

		/*
		PrintSeparator();

		{
			// !!! JAVA NEUMOZNUJE definovat ARRAYS pre GENERICS TYPES, ak sa pouzije GENERICS TYPE s definovanymi TYPE ARGUMENTS.
			CTypeErasureGenericsArrays<String>[]				array=new CTypeErasureGenericsArrays<String>[2];
			
			array[0]=new CTypeErasureGenericsArrays<String>("TIMMY");
			array[1]=new CTypeErasureGenericsArrays<String>("JENNY");
			
			for(CTypeErasureGenericsArrays<String> item : array)
			{
				System.out.printf("RAW GENERICS TYPE ARRAY ITEM - VALUE [%s].\n",item.getField());
			}
		}
		*/
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestRawGenericsTypes()
	{
		// !!! JAVA umoznuje pouzitie GENERICS TYPE ako RAW TYPES, ked TYPE nema definovane TYPE ARGUMENTS.
		// !!!!! COMPILER hodi WARNING.
		CGenericsClass											genericsClass=new CGenericsClass("TIMMY",12l);

		String													value1=(String) genericsClass.getValue1();
		Long													value2=(Long) genericsClass.getValue2();
	
		System.out.printf("RAW TYPE - VALUE 1 [%s] VALUE 2 [%s].\n",value1,value2);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestRawGenericsTypesConversions()
	{
		{
			CGenericsClass										rawType=new CGenericsClass("TIMMY",12l);
			
			// !!! JAVA vykonava implicitnu CONVERSION z RAW TYPE na GENERICS TYPE.
			CGenericsClass<String,Long>							genericsType=rawType;

			String												value1=(String) genericsType.getValue1();
			Long												value2=(Long) genericsType.getValue2();

			System.out.printf("RAW TYPE - VALUE 1 [%s] VALUE 2 [%s].\n",value1,value2);
		}

		PrintSeparator();
		
		{
			CGenericsClass										rawType=new CGenericsClass("TIMMY",12l);
			
			// !!! JAVA vykonava implicitnu CONVERSION z RAW TYPE na GENERICS TYPE.
			// !!!!! CONVERSION je CHYBNA.
			CGenericsClass<String,Integer>						genericsType=rawType;

			try
			{
				String											value1=(String) genericsType.getValue1();
				// !!! Dojde k vzniku EXCEPTION.
				Integer											value2=(Integer) genericsType.getValue2();

				System.out.printf("RAW TYPE - VALUE 1 [%s] VALUE 2 [%s].\n",value1,value2);
			}
			catch(ClassCastException E)
			{
				System.out.printf("EXCEPTION [%s].\n",E.getMessage());
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION potlaca COMPILER WARNINGS.
	@SuppressWarnings("unchecked")
	private static <TType> TType TestGenericsCasting(Object value)
	{
		// !!! JAVA umoznuje EXPLICIT CONVERSION na TYPE PARAMETERS, ale COMPILER hodi WARNING. 
		TType													typedValue=(TType) value;
		
		return(typedValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericsCasting()
	{
		String													value1="TIMMY";
		
		String													value2=TestGenericsCasting(value1);

		System.out.printf("VALUE [%s].\n",value2);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static <TType extends CBoundsClassBase1<String>> String GenericsBoundsMethod(TType value)
	{
		String													innerValue=value.getValueClass();
		
		return(innerValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	private static <TType extends Comparable<TType>> String GenericsBoundsMethodRecursive(TType value1, TType value2)
	{
		// !!! BOUND umoznuje vyuzit METHODS BOUND TYPES.
		int														Result=value1.compareTo(value2);
		
		if (Result<0)
		{
			return("LOWER");
		}
		else if (Result>0)
		{
			return("HIGHER");
		}
		else
		{
			return("EQUAL");
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericsBounds()
	{
		{
			CGenericsClassWithBounds1<CBoundsClassDerived1<String>,CBoundsImplementingInterface1<Integer>,CBoundsImplementingInterface2<Long>>	object=new CGenericsClassWithBounds1<>(new CBoundsClassDerived1<String>("TIMMY"),new CBoundsImplementingInterface1<Integer>(12),new CBoundsImplementingInterface2<Long>(13l));

			object.Print();
		}

		PrintSeparator();
		
		{
			CGenericsClassWithBounds2<CBoundsClassDerivedMulti>	object=new CGenericsClassWithBounds2<>(new CBoundsClassDerivedMulti("TIMMY",12,13l));

			object.Print();
		}

		PrintSeparator();
		
		{
			CGenericsClassWithBounds3<CBoundsClassDerived2Recursive,CBoundsClassInterface1Recursive,CBoundsClassInterface2Recursive>	object=new CGenericsClassWithBounds3<>(new CBoundsClassDerived2Recursive("TIMMY"),new CBoundsClassInterface1Recursive(12),new CBoundsClassInterface2Recursive(13l));

			object.Print();
		}

		PrintSeparator();
		
		{
			String												result=GenericsBoundsMethod(new CBoundsClassDerived1<>("TIMMY"));
			
			System.out.printf("RESULT [%s].\n",result);
		}
		
		PrintSeparator();
		
		{
			String												result1=GenericsBoundsMethodRecursive(10l,100l);
			String												result2=GenericsBoundsMethodRecursive(100l,10l);
			String												result3=GenericsBoundsMethodRecursive(100l,100l);
			
			System.out.printf("RESULT 1 [%s] RESULT 2 [%s] RESULT 3 [%s].\n",result1,result2,result3);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericsThrowsClause()
	{
		{
			CThrowsClauseAllExceptionsChecked					object=new CThrowsClauseAllExceptionsChecked();
			
			try
			{
				// !!! Kedze METHOD hadze CHECKED EXCEPTION, MUSI by uzavoreny do TRY-CATCH BLOCK. 
				object.ThrowException(true);
			}
			catch(Exception e)
			{
				System.out.printf("EXCEPTION TYPE [%s] MESSAGE [%s].\n",e.getClass(),e.getMessage());
			}
		}
	
		PrintSeparator();
		
		{
			CThrowsClauseAllExceptionsUnchecked					object=new CThrowsClauseAllExceptionsUnchecked();
			
			try
			{
				// !!! Kedze METHOD hadze UNCHECKED EXCEPTION, NEMUSI by uzavoreny do TRY-CATCH BLOCK. 
				object.ThrowException(true);
			}
			catch(Exception e)
			{
				System.out.printf("EXCEPTION TYPE [%s] MESSAGE [%s].\n",e.getClass(),e.getMessage());
			}
		}

		PrintSeparator();
		
		{
			CThrowsClauseUncheckedExceptions					object=new CThrowsClauseUncheckedExceptions();
			
			try
			{
				// !!! Kedze METHOD hadze UNCHECKED EXCEPTION, NEMUSI by uzavoreny do TRY-CATCH BLOCK. 
				object.ThrowException(true);
			}
			catch(Exception e)
			{
				System.out.printf("EXCEPTION TYPE [%s] MESSAGE [%s].\n",e.getClass(),e.getMessage());
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestCovarianceInvariance()
	{
		{
			// !!!!! ARRAYS v JAVE su COVARIANT.
			CBaseType[]											myArray=new CDerivedType[3];
			
			myArray[0]=new CDerivedType();
			myArray[1]=new CDerivedType();
			
			try
			{
				// !!!!!! CODE hodi EXCEPTION, pretoze sa ARRAY TYPE je [CDerivedType[]] a do ITEMS nie je mozne priradit instancie BASE TYPE [CBaseType].
				myArray[2]=new CBaseType();
			}
			catch(Exception e)
			{
				System.out.printf("EXCEPTION TYPE [%s] MESSAGE [%s].\n",e.getClass(),e.getMessage());
			}
			
			for(int index=0;index<myArray.length;index++)
			{
				CBaseType										object=myArray[index];
				
				if (object!=null)
				{
					System.out.printf("ITEM [%d] VALUE [%s].\n",index,object.MyMethod());
				}
				else
				{
					System.out.printf("ITEM [%d] VALUE [NULL].\n",index);
				}
			}
		}
		
		/*
		PrintSeparator();
		
		{
			// !!!!! GENERICS v JAVE su INVARIANT. Preto tento CODE sposobi COMPILATION ERROR.
			List<CBaseType>										myCollection=new ArrayList<CDerivedType>();
			
			myCollection.add(new CDerivedType());
			myCollection.add(new CDerivedType());
			
			
			for(int index=0;index<myCollection.size();index++)
			{
				CBaseType										object=myCollection.get(index);
				
				if (object!=null)
				{
					System.out.printf("ITEM [%d] VALUE [%s].\n",index,object.MyMethod());
				}
				else
				{
					System.out.printf("ITEM [%d] VALUE [NULL].\n",index);
				}
			}
		}
		*/
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! GENERICS TYPES mozu pouzivat WILDCARDS.
	private static void MethodGenericsWildcard1(CGenericsWildcard<?,?> value)
	{
		int														nonGenericsValue=value.getNonGenericsValue();
		
		// !!! Pre WILDCARD TYPES je mozne volat READ METHODS, ktore vracaju TYPE PARAMETERS ako RETURN VALUE, ale TYPE PARAMETERS su nahradene TYPE [Object].
		Object													genericsValue1=value.getGenericsValue1();
		
		// !!! Pre WILDCARD TYPES je mozne volat READ METHODS, ktore vracaju TYPE PARAMETERS ako RETURN VALUE, ale TYPE PARAMETERS su nahradene TYPE [Object].
		Object													genericsValue2=value.getGenericsValue2();
		
		System.out.printf("NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,genericsValue2);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! GENERICS TYPES mozu pouzivat WILDCARDS.
	private static void MethodGenericsWildcard2(CGenericsWildcard<?,?> value)
	{
		{
			int													nonGenericsValue=value.getNonGenericsValue();
			
			// !!! Pre WILDCARD TYPES je mozne volat READ METHODS, ktore vracaju TYPE PARAMETERS ako RETURN VALUE, ale TYPE PARAMETERS su nahradene TYPE [Object].
			Object												genericsValue1=value.getGenericsValue1();
			
			// !!! Pre WILDCARD TYPES je mozne volat READ METHODS, ktore vracaju TYPE PARAMETERS ako RETURN VALUE, ale TYPE PARAMETERS su nahradene TYPE [Object].
			Object												genericsValue2=value.getGenericsValue2();
			
			System.out.printf("BEFORE WRITE - NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,genericsValue2);
		}

		{
			value.setNonGenericsValue(999);
			
			/*
			// !!!!! Pre WILDCARD TYPES NIE je mozne volat WRITE METHODS, ktore maju TYPE PARAMETERS ako METHOD PARAMETERS, ale TYPE PARAMETERS su nahradene TYPE [Object].
			value.setGenericsValue1("JENNY");
			
			// !!!!! Pre WILDCARD TYPES NIE je mozne volat WRITE METHODS, ktore maju TYPE PARAMETERS ako METHOD PARAMETERS, ale TYPE PARAMETERS su nahradene TYPE [Object].
			value.setGenericsValue2(13);
			*/
		}
		
		{
			int													nonGenericsValue=value.getNonGenericsValue();
			
			// !!! Pre WILDCARD TYPES je mozne volat READ METHODS, ktore vracaju TYPE PARAMETERS ako RETURN VALUE, ale TYPE PARAMETERS su nahradene TYPE [Object].
			Object												genericsValue1=value.getGenericsValue1();
			
			// !!! Pre WILDCARD TYPES je mozne volat READ METHODS, ktore vracaju TYPE PARAMETERS ako RETURN VALUE, ale TYPE PARAMETERS su nahradene TYPE [Object].
			Object												genericsValue2=value.getGenericsValue2();
			
			System.out.printf("AFTER WRITE - NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,genericsValue2);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericsWildcard()
	{
		{
			CGenericsWildcard<String,Integer>					object=new CGenericsWildcard<String,Integer>(100,"TIMMY",12);
			
			MethodGenericsWildcard1(object);
		}

		PrintSeparator();
		
		{
			CGenericsWildcard<String,Double>					object=new CGenericsWildcard<String,Double>(200,"TIMMY",12.13);
			
			MethodGenericsWildcard1(object);
		}

		PrintSeparator();
		
		{
			// !!! WILDCARDS je mozne pouzit aj pri definicii VARIABLE daneho TYPE.
			CGenericsWildcard<String,?>							object=new CGenericsWildcard<String,Double>(300,"TIMMY",12.14);
			
			MethodGenericsWildcard1(object);
		}

		PrintSeparator();
		
		{
			CGenericsWildcard<String,Integer>					object=new CGenericsWildcard<String,Integer>(400,"TIMMY",12);
			
			MethodGenericsWildcard2(object);
		}
		
		PrintSeparator();
		
		{
			CGenericsWildcard<?,?>								object1=new CGenericsWildcard<String,Integer>(100,"TIMMY",12);
			CGenericsWildcard<String,Double>					object2=new CGenericsWildcard<String,Double>(200,"TIMMY",12.13);

			System.out.printf("OBJECT 1 - NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",object1.getNonGenericsValue(),object1.getGenericsValue1(),object1.getGenericsValue2());
			System.out.printf("OBJECT 2 - NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",object2.getNonGenericsValue(),object2.getGenericsValue1(),object2.getGenericsValue2());
			
			CGenericsWildcard<?,?>								object3=object2;

			System.out.printf("OBJECT 3 - NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",object3.getNonGenericsValue(),object3.getGenericsValue1(),object3.getGenericsValue2());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! BOUNDS je mozne aplikovat aj na WILDCARD TYPE PARAMETERS. UPPER BOUND urcuje TYPE, ktory musi TYPE PARAMETER implementovat.
	// !!!!! JAVA NEUMOZNUJE definovat VIACERO BOUNDS pre WILDCARD TYPE PARAMETERS.
	private static void MethodGenericsWildcardUpperBounds1(CGenericsWildcard<String,? extends CClassBaseMyInterface1MyInterface2> value)
	{
		int														nonGenericsValue=value.getNonGenericsValue();
		
		String													genericsValue1=value.getGenericsValue1();
		
		// !!! WILDCARD TYPES, ktore maju aplikovany UPPER BOUND mozu volat READ METHODS, ktorych RETURN TYPE moze byt konvertovany na dany BOUND TYPE.
		CClassBaseMyInterface1MyInterface2						genericsValue2=value.getGenericsValue2();

		/*
		// !!!!! TENTO CODE hodi COMPILATION ERROR
		// !!! WILDCARD TYPES, ktore maju aplikovany UPPER BOUND NEMOZU volat WRITE METHODS, pretoze METHOD PARAMETERS daneho TYPE PARAMETER moze byt lubovolny TYPE, ktory implementuje dany BOUND TYPE. Pri povoleni volania takychto METHOD by doslo k naruseniu TYPE SAFETY.
		value.setGenericsValue2(genericsValue2);
		*/
		
		System.out.printf("NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,genericsValue2.getBaseClassValue());
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! BOUNDS je mozne aplikovat aj na WILDCARD TYPE PARAMETERS. UPPER BOUND urcuje TYPE, ktory musi TYPE PARAMETER implementovat.
	// !!!!! JAVA NEUMOZNUJE definovat VIACERO BOUNDS pre WILDCARD TYPE PARAMETERS.
	private static void MethodGenericsWildcardUpperBounds2(CGenericsWildcard<String,? extends IMyInterface1> value)
	{
		int														nonGenericsValue=value.getNonGenericsValue();
		
		String													genericsValue1=value.getGenericsValue1();
		
		// !!! WILDCARD TYPES, ktore maju aplikovany UPPER BOUND mozu volat READ METHODS, ktorych RETURN TYPE moze byt konvertovany na dany BOUND TYPE.
		IMyInterface1											genericsValue2=value.getGenericsValue2();

		/*
		// !!!!! TENTO CODE hodi COMPILATION ERROR
		// !!! WILDCARD TYPES, ktore maju aplikovany UPPER BOUND NEMOZU volat WRITE METHODS, pretoze METHOD PARAMETERS daneho TYPE PARAMETER moze byt lubovolny TYPE, ktory implementuje dany BOUND TYPE. Pri povoleni volania takychto METHOD by doslo k naruseniu TYPE SAFETY.
		value.setGenericsValue2(genericsValue2);
		*/
		
		System.out.printf("NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,genericsValue2.getInterfaceValue1());
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! BOUNDS je mozne aplikovat aj na WILDCARD TYPE PARAMETERS. UPPER BOUND urcuje TYPE, ktory musi TYPE PARAMETER implementovat.
	// !!!!! JAVA NEUMOZNUJE definovat VIACERO BOUNDS pre WILDCARD TYPE PARAMETERS.
	private static void MethodGenericsWildcardUpperBounds3(CGenericsWildcard<String,? extends IMyInterface2> value)
	{
		int														nonGenericsValue=value.getNonGenericsValue();
		
		String													genericsValue1=value.getGenericsValue1();
		
		// !!! WILDCARD TYPES, ktore maju aplikovany UPPER BOUND mozu volat READ METHODS, ktorych RETURN TYPE moze byt konvertovany na dany BOUND TYPE.
		IMyInterface2											genericsValue2=value.getGenericsValue2();

		/*
		// !!!!! TENTO CODE hodi COMPILATION ERROR
		// !!! WILDCARD TYPES, ktore maju aplikovany UPPER BOUND NEMOZU volat WRITE METHODS, pretoze METHOD PARAMETERS daneho TYPE PARAMETER moze byt lubovolny TYPE, ktory implementuje dany BOUND TYPE. Pri povoleni volania takychto METHOD by doslo k naruseniu TYPE SAFETY.
		value.setGenericsValue2(genericsValue2);
		*/
		
		System.out.printf("NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,genericsValue2.getInterfaceValue2());
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericsWildcardUpperBounds()
	{
		{
			CClassDerivedMyInterface1MyInterface2				innerObject=new CClassDerivedMyInterface1MyInterface2("AAA","BBB","CCC");
			CGenericsWildcard<String,CClassDerivedMyInterface1MyInterface2>	object=new CGenericsWildcard<String,CClassDerivedMyInterface1MyInterface2>(100,"TIMMY",innerObject);
			
			MethodGenericsWildcardUpperBounds1(object);
		}

		PrintSeparator();
		
		{
			CClassDerivedMyInterface1MyInterface2				innerObject=new CClassDerivedMyInterface1MyInterface2("AAA","BBB","CCC");
			CGenericsWildcard<String,CClassDerivedMyInterface1MyInterface2>	object=new CGenericsWildcard<String,CClassDerivedMyInterface1MyInterface2>(100,"TIMMY",innerObject);
			
			MethodGenericsWildcardUpperBounds2(object);
		}

		PrintSeparator();
		
		{
			CClassDerivedMyInterface1MyInterface2				innerObject=new CClassDerivedMyInterface1MyInterface2("AAA","BBB","CCC");
			CGenericsWildcard<String,CClassDerivedMyInterface1MyInterface2>	object=new CGenericsWildcard<String,CClassDerivedMyInterface1MyInterface2>(100,"TIMMY",innerObject);
			
			MethodGenericsWildcardUpperBounds3(object);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! BOUNDS je mozne aplikovat aj na WILDCARD TYPE PARAMETERS. LOWER BOUND urcuje TYPE, pricom TYPE PARAMETER musi byt daneho TYPE, alebo niektory z jeho BASE TYPES.
	// !!!!! JAVA NEUMOZNUJE definovat VIACERO BOUNDS pre WILDCARD TYPE PARAMETERS.
	private static void MethodGenericsWildcardLowerBounds1(CGenericsWildcard<String,? super CClassDerivedMyInterface1MyInterface2> value)
	{
		int														nonGenericsValue=value.getNonGenericsValue();
		
		String													genericsValue1=value.getGenericsValue1();

		// !!!!! WILDCARD TYPES, ktore maju aplikovany LOWER BOUND mozu volat READ METHODS, ktorych RETURN VALUE TYPE je TYPE PARAMETER ktory bol nahradeny WILDCARD TYPE. No TYPE PARAMETER je nahradeny TYPE [Object], pretoze COMPILER nema informaciu o tom akeho skutocneho TYPE je dany TYPE PARAMETER. 
		Object													genericsValue2=value.getGenericsValue2();

		System.out.printf("BEFORE SET - NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,genericsValue2);
		
		/*
		// !!!!! TENTO CODE hodi COMPILATION ERROR
		// !!! WILDCARD TYPES, ktore maju aplikovany LOWER BOUND NEMOZU volat WRITE METHODS ak TYPE PARAMETER nie je zhodny s BOUND TYPE, pretoze METHOD PARAMETERS daneho TYPE PARAMETER moze byt lubovolny TYPE, ktory implementuje dany BOUND TYPE. Pri povoleni volania takychto METHOD by doslo k naruseniu TYPE SAFETY.
		value.setGenericsValue2(genericsValue2);
		
		System.out.printf("AFTER SET - NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,value.getGenericsValue2());
		*/
		
		/*
		// !!!!! TENTO CODE hodi COMPILATION ERROR
		// !!! WILDCARD TYPES, ktore maju aplikovany LOWER BOUND NEMOZU volat WRITE METHODS ak TYPE PARAMETER nie je zhodny s BOUND TYPE, pretoze METHOD PARAMETERS daneho TYPE PARAMETER moze byt lubovolny TYPE, ktory implementuje dany BOUND TYPE. Pri povoleni volania takychto METHOD by doslo k naruseniu TYPE SAFETY.
		value.setGenericsValue2(new CClassBaseMyInterface1MyInterface2("XXX"));
		
		System.out.printf("AFTER SET - NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,value.getGenericsValue2());
		*/
		
		// !!!!! TENTO CODE hodi COMPILATION ERROR
		// !!!!! WILDCARD TYPES, ktore maju aplikovany LOWER BOUND MOZU volat WRITE METHODS ak TYPE PARAMETER je zhodny s BOUND TYPE.
		value.setGenericsValue2(new CClassDerivedMyInterface1MyInterface2("XXX","YYY","ZZZ"));
		
		System.out.printf("AFTER SET - NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,value.getGenericsValue2());
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! BOUNDS je mozne aplikovat aj na WILDCARD TYPE PARAMETERS. LOWER BOUND urcuje TYPE, pricom TYPE PARAMETER musi byt daneho TYPE, alebo niektory z jeho BASE TYPES.
	// !!!!! JAVA NEUMOZNUJE definovat VIACERO BOUNDS pre WILDCARD TYPE PARAMETERS.
	private static void MethodGenericsWildcardLowerBounds2(CGenericsWildcard<String,? super IMyInterface1> value)
	{
		int														nonGenericsValue=value.getNonGenericsValue();
		
		String													genericsValue1=value.getGenericsValue1();

		// !!!!! WILDCARD TYPES, ktore maju aplikovany LOWER BOUND mozu volat READ METHODS, ktorych RETURN VALUE TYPE je TYPE PARAMETER ktory bol nahradeny WILDCARD TYPE. No TYPE PARAMETER je nahradeny TYPE [Object], pretoze COMPILER nema informaciu o tom akeho skutocneho TYPE je dany TYPE PARAMETER. 
		Object													genericsValue2=value.getGenericsValue2();

		/*
		// !!!!! TENTO CODE hodi COMPILATION ERROR
		// !!! WILDCARD TYPES, ktore maju aplikovany LOWER BOUND NEMOZU volat WRITE METHODS, pretoze METHOD PARAMETERS daneho TYPE PARAMETER moze byt lubovolny TYPE, ktory implementuje dany BOUND TYPE. Pri povoleni volania takychto METHOD by doslo k naruseniu TYPE SAFETY.
		value.setGenericsValue2(genericsValue2);
		*/
		
		System.out.printf("NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,genericsValue2);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! BOUNDS je mozne aplikovat aj na WILDCARD TYPE PARAMETERS. LOWER BOUND urcuje TYPE, pricom TYPE PARAMETER musi byt daneho TYPE, alebo niektory z jeho BASE TYPES.
	// !!!!! JAVA NEUMOZNUJE definovat VIACERO BOUNDS pre WILDCARD TYPE PARAMETERS.
	private static void MethodGenericsWildcardLowerBounds3(CGenericsWildcard<String,? super IMyInterface2> value)
	{
		int														nonGenericsValue=value.getNonGenericsValue();
		
		String													genericsValue1=value.getGenericsValue1();

		// !!!!! WILDCARD TYPES, ktore maju aplikovany LOWER BOUND mozu volat READ METHODS, ktorych RETURN VALUE TYPE je TYPE PARAMETER ktory bol nahradeny WILDCARD TYPE. No TYPE PARAMETER je nahradeny TYPE [Object], pretoze COMPILER nema informaciu o tom akeho skutocneho TYPE je dany TYPE PARAMETER. 
		Object													genericsValue2=value.getGenericsValue2();
		
		/*
		// !!!!! TENTO CODE hodi COMPILATION ERROR
		// !!! WILDCARD TYPES, ktore maju aplikovany LOWER BOUND NEMOZU volat WRITE METHODS, pretoze METHOD PARAMETERS daneho TYPE PARAMETER moze byt lubovolny TYPE, ktory implementuje dany BOUND TYPE. Pri povoleni volania takychto METHOD by doslo k naruseniu TYPE SAFETY.
		value.setGenericsValue2(genericsValue2);
		*/
		
		System.out.printf("NON GENERICS VALUE [%s] GENERICS VALUE 1 [%s] GENERICS VALUE 2 [%s].\n",nonGenericsValue,genericsValue1,genericsValue2);
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericsWildcardLowerBounds()
	{
		{
			CClassDerivedMyInterface1MyInterface2				innerObject=new CClassDerivedMyInterface1MyInterface2("AAA","BBB","CCC");
			
			// !!! Pri LOWER BOUND moze TYPE PARAMETER reprezentovat BOUND TYPE, alebo ktorykolvek jeho BASE TYPE.
			CGenericsWildcard<String,CClassDerivedMyInterface1MyInterface2>	object=new CGenericsWildcard<String,CClassDerivedMyInterface1MyInterface2>(100,"TIMMY",innerObject);
			
			MethodGenericsWildcardLowerBounds1(object);
		}
		
		PrintSeparator();
		
		{
			CClassBaseMyInterface1MyInterface2					innerObject=new CClassBaseMyInterface1MyInterface2("AAA");
			
			// !!! Pri LOWER BOUND moze TYPE PARAMETER reprezentovat BOUND TYPE, alebo ktorykolvek jeho BASE TYPE.
			CGenericsWildcard<String,CClassBaseMyInterface1MyInterface2>	object=new CGenericsWildcard<String,CClassBaseMyInterface1MyInterface2>(100,"TIMMY",innerObject);
			
			MethodGenericsWildcardLowerBounds1(object);
		}

		PrintSeparator();
		
		{
			CClassDerivedMyInterface1MyInterface2				innerObject=new CClassDerivedMyInterface1MyInterface2("AAA","BBB","CCC");
			
			// !!! Pri LOWER BOUND moze TYPE PARAMETER reprezentovat BOUND TYPE, alebo ktorykolvek jeho BASE TYPE.
			CGenericsWildcard<String,IMyInterface1>				object=new CGenericsWildcard<String,IMyInterface1>(100,"TIMMY",innerObject);
			
			MethodGenericsWildcardLowerBounds2(object);
		}

		PrintSeparator();
		
		{
			CClassDerivedMyInterface1MyInterface2				innerObject=new CClassDerivedMyInterface1MyInterface2("AAA","BBB","CCC");
			
			// !!! Pri LOWER BOUND moze TYPE PARAMETER reprezentovat BOUND TYPE, alebo ktorykolvek jeho BASE TYPE.
			CGenericsWildcard<String,IMyInterface2>				object=new CGenericsWildcard<String,IMyInterface2>(100,"TIMMY",innerObject);
			
			MethodGenericsWildcardLowerBounds3(object);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void MethodTestGenericsWildcardBoundsReadMethods(CList<? extends CNumber> list)
	{
		System.out.printf("READ METHOD - TYPE [%s].\n",list.getClass());
		
		for(int index=0;index<list.Size();index++)
		{
			// !!! Vola sa READ METHOD pre TYPE PARAMETER, ktory bol nahradeny WILDCARD PARAMETER na ktory je aplikovany UPPER BOUND.
			CNumber												number=list.GetItem(index);

			System.out.printf("READ METHOD - ITEM [%s] VALUE [%s].\n",(index+1),number);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void MethodTestGenericsWildcardBoundsWriteMethods(CList<? super CInteger> list, CInteger itemToAdd)
	{
		System.out.printf("WRITE METHOD - TYPE [%s].\n",list.getClass());
		
		// !!! Vola sa WRITE METHOD pre TYPE PARAMETER, ktory bol nahradeny WILDCARD PARAMETER na ktory je aplikovany LOWER BOUND.
		list.AddItem(itemToAdd);
		
		for(int index=0;index<list.Size();index++)
		{
			// !!! Vola sa READ METHOD pre TYPE PARAMETER, ktory bol nahradeny WILDCARD PARAMETER na ktory je aplikovany LOWER BOUND. Je TYPE je TYPE [Object].
			Object												number=list.GetItem(index);

			System.out.printf("WRITE METHOD - ITEM [%s] VALUE [%s].\n",(index+1),number);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD nepouziva WILDCARD BOUNDS, ale klasicky TYPE PARAMETER BOUND.
	private static <TItem extends CNumber> void MethodTestGenericsNoWildcards(CList<TItem> list)
	{
		System.out.printf("NO WILDCARD METHOD - TYPE [%s].\n",list.getClass());
		
		for(int index=0;index<list.Size();index++)
		{
			CNumber												number=list.GetItem(index);

			System.out.printf("NO WILDCARD METHOD - ITEM [%s] VALUE [%s].\n",(index+1),number);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericsWildcardBounds()
	{
		{
			CList<CNumber>										list=new CList<CNumber>();
			
			list.AddItem(new CInteger(100));
			list.AddItem(new CInteger(200));
			list.AddItem(new CInteger(300));

			// !!! TYPE [CNumber] je akcpetovatelny TYPE ARGUMENT, pretoze na TYPE je aplikovany UPPER BOUND [CNumber].
			MethodTestGenericsWildcardBoundsReadMethods(list);
		}

		PrintSeparator();
		
		{
			CList<CInteger>										list=new CList<CInteger>();
			
			list.AddItem(new CInteger(100));
			list.AddItem(new CInteger(200));
			list.AddItem(new CInteger(300));

			// !!! TYPE [CInteger] je akcpetovatelny TYPE ARGUMENT, pretoze na TYPE je aplikovany UPPER BOUND [CNumber] a TYPE [CInteger] je DERIVED z TYPE [CNumber].
			MethodTestGenericsWildcardBoundsReadMethods(list);
		}

		PrintSeparator();
		
		{
			CList<CDouble>										list=new CList<CDouble>();
			
			list.AddItem(new CDouble(100.111));
			list.AddItem(new CDouble(200.222));
			list.AddItem(new CDouble(300.333));
			
			// !!! TYPE [CDouble] je akcpetovatelny TYPE ARGUMENT, pretoze na TYPE je aplikovany UPPER BOUND [CNumber] a TYPE [CDouble] je DERIVED z TYPE [CNumber].
			MethodTestGenericsWildcardBoundsReadMethods(list);
		}
		
		PrintSeparator();

		{
			CList<CInteger>										list=new CList<CInteger>();
			CInteger											itemToAdd=new CInteger(400);
			
			list.AddItem(new CInteger(100));
			list.AddItem(new CInteger(200));
			list.AddItem(new CInteger(300));
			
			// !!!!! TYPE [CInteger] je akcpetovatelny TYPE ARGUMENT, pretoze na TYPE je aplikovany LOWER BOUND [CInteger].
			MethodTestGenericsWildcardBoundsWriteMethods(list,itemToAdd);
		}
		
		PrintSeparator();

		{
			CList<CNumber>										list=new CList<CNumber>();
			CInteger											itemToAdd=new CInteger(400);
			
			list.AddItem(new CInteger(100));
			list.AddItem(new CInteger(200));
			list.AddItem(new CInteger(300));
			
			// !!!!! TYPE [CNumber] je akcpetovatelny TYPE ARGUMENT, pretoze na TYPE je aplikovany LOWER BOUND [CInteger] a TYPE [CNumber] je BASE CLASS TYPE [CInteger].
			// !!!!! Toto pouzitie ukazuje vyznam LOWER BOUND. LOWER BOUND umoznuje do METHOD poslat GENERICS TYPE, ktory ma TYPE ARGUMENT BASE CLASS definovaneho LOWER BOUND TYPE. Toto je povolene, pretoze do OBJECT TYPE [CList<CNumber>] je mozne vkladat ITEMS TYPE [CInteger], kdeze TYPE [CInteger] je DERIVED TYPE z TYPE [CNumber]. 
			MethodTestGenericsWildcardBoundsWriteMethods(list,itemToAdd);
		}
		
		PrintSeparator();

		{
			CList<Object>										list=new CList<Object>();
			CInteger											itemToAdd=new CInteger(400);
			
			list.AddItem(new CInteger(100));
			list.AddItem(new CInteger(200));
			list.AddItem(new CInteger(300));
			
			// !!!!! TYPE [Object] je akcpetovatelny TYPE ARGUMENT, pretoze na TYPE je aplikovany LOWER BOUND [CInteger] a TYPE [Object] je BASE CLASS TYPE [CInteger].
			// !!!!! Toto pouzitie ukazuje vyznam LOWER BOUND. LOWER BOUND umoznuje do METHOD poslat GENERICS TYPE, ktory ma TYPE ARGUMENT BASE CLASS definovaneho LOWER BOUND TYPE. Toto je povolene, pretoze do OBJECT TYPE [CList<Object>] je mozne vkladat ITEMS TYPE [CInteger], kdeze TYPE [CInteger] je DERIVED TYPE z TYPE [Object]. 
			MethodTestGenericsWildcardBoundsWriteMethods(list,itemToAdd);
		}
		
		PrintSeparator();
		
		{
			CList<CDouble>										list=new CList<CDouble>();
			
			list.AddItem(new CDouble(100.111));
			list.AddItem(new CDouble(200.222));
			list.AddItem(new CDouble(300.333));
			
			MethodTestGenericsNoWildcards(list);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! PARAMETER [producerList] vola iba READ METHODS, a preto sa nan aplikuje UPPER BOUND.
	// !!! PARAMETER [consumerList] vola iba WRITE METHODS, a preto sa nan aplikuje LOWER BOUND.
	private static void MethodProducerExtendsConsumerSuperPrinciple(CList<? extends CNumber> producerList, CList<? super CNumber> consumerList)
	{
		for(int index=0;index<producerList.Size();index++)
		{
			// !!!!! Vola sa READ METHOD. Je to mozne, pretoze na WILDCARD TYPE PARAMETER sa aplikuje UPPER BOUND.
			CNumber												listItem=producerList.GetItem(index);

			// !!!!! Vola sa WRITE METHOD. Je to mozne, pretoze na WILDCARD TYPE PARAMETER sa aplikuje LOWER BOUND.
			consumerList.AddItem(listItem);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestProducerExtendsConsumerSuperPrinciple()
	{
		{
			CList<CInteger>										producerList=new CList<CInteger>();
			CList<CNumber>										consumerList=new CList<CNumber>();
			
			producerList.AddItem(new CInteger(100));
			producerList.AddItem(new CInteger(200));
			producerList.AddItem(new CInteger(300));
		
			MethodProducerExtendsConsumerSuperPrinciple(producerList,consumerList);
			
			for(int index=0;index<consumerList.Size();index++)
			{
				CNumber											number=consumerList.GetItem(index);
				
				System.out.printf("CList<CInteger> - ITEM [%s] VALUE [%s].\n",(index+1),number);
			}
		}

		PrintSeparator();
		
		{
			CList<CNumber>										producerList=new CList<CNumber>();
			CList<CNumber>										consumerList=new CList<CNumber>();
			
			producerList.AddItem(new CInteger(100));
			producerList.AddItem(new CInteger(200));
			producerList.AddItem(new CInteger(300));
		
			MethodProducerExtendsConsumerSuperPrinciple(producerList,consumerList);
			
			for(int index=0;index<consumerList.Size();index++)
			{
				CNumber											number=consumerList.GetItem(index);
				
				System.out.printf("CList<CNumber> - ITEM [%s] VALUE [%s].\n",(index+1),number);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestTypeTokens()
	{
		// !!! Ziskanie TYPE TOKEN pomocou KEYWORD [class].
		Class<String>											token1=String.class;
		
		//!! !!! Ziskanie TYPE TOKEN pomocou METHOD [Class<?> Object.getClass()]. RETURN VALUE TYPE je mozne IMPLICITNE pretypovat na TYPE [Class<? extends TYPE>], kde VALUE [TYPE] je TYPE daneho OBJECT.
		Class<? extends String>									token2="TIMMY".getClass();

		if (token1.equals(token2)==true)
		{
			System.out.println("TOKENS are SAME.");
		}
		else
		{
			System.out.println("TOKENS are DIFFERENT.");
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static <TType> TType MethodCreateTypeParameterInstance(Class<TType> classObject) throws NoSuchMethodException, InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException
	{
		// !!! Ziska sa CONSTRUCTOR.
		Constructor<TType>										constructor=classObject.getConstructor();
		
		// !!! Vytvori sa instancia TYPE PARAMETER.
		TType													object=constructor.newInstance();
		
		return(object);
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestCreateTypeParameterInstance()
	{
		try
		{
			Class<CInteger>										token=CInteger.class;
			CInteger											newObject=MethodCreateTypeParameterInstance(token);
			
			newObject.setValue(123);
			
			System.out.printf("VALUE [%s].\n",newObject.getValue());
		}
		catch(Exception e)
		{
			System.out.printf("EXCEPTION [%s].\n",e.getMessage());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void TestGenericsTypeInfer()
	{
		{
			// !!! Vytvri sa ANONYMOUS CLASS.
			CGenericsTypeInferClass<CList<CInteger>>			object=new CGenericsTypeInferClass<CList<CInteger>>(){};
			Type												type=object.GetGenericsTypeTypeInformation();
		
			System.out.printf("TYPE [%s].\n",type.getTypeName());
		}

		PrintSeparator();
		
		{
			// !!! Vytvri sa ANONYMOUS CLASS.
			CGenericsTypeInferClass<CGenericsClass<String,Long>>	object=new CGenericsTypeInferClass<CGenericsClass<String,Long>>(){};
			Type												type=object.GetGenericsTypeTypeInformation();
		
			System.out.printf("TYPE [%s].\n",type.getTypeName());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	/*
	private static <TType> TType[] CreateTypeParameterArraysOperatorNew(int length)
	{
		// !!!!! JAVA NEUMOZNUJE vytvarat ARRAYS pre TYPE PARAMETERS pomocou OPERATOR [OPERATOR new].
		TType[]													array=new TType[length];

		return(array);
	}
	*/
//----------------------------------------------------------------------------------------------------------------------
	private static <TType> TType[] CreateTypeParameterArraysReflection(Class<TType> classObject, int length)
	{
		// !!!!! JAVA UMOZNUJE vytvarat ARRAYS pre TYPE PARAMETERS pomocou REFLECTION.
		TType[]													array=(TType[]) Array.newInstance(classObject,length);

		return(array);
	}
//----------------------------------------------------------------------------------------------------------------------
	private static void TestTypeParameterArrays()
	{
		/*
		{
			CInteger[]											array=GenericsApplication.<CInteger>CreateTypeParameterArraysOperatorNew(2);

			array[0]=new CInteger(100);
			array[1]=new CInteger(200);
		
			for(int index=0;index<array.length;index++)
			{
				CInteger										value=array[index];
				
				System.out.printf("ITEM [%s] VALUE [%s].\n",(index+1),value);
			}
		}
		*/

		{
			CInteger[]											array=GenericsApplication.<CInteger>CreateTypeParameterArraysReflection(CInteger.class,2);

			array[0]=new CInteger(100);
			array[1]=new CInteger(200);
			
			for(int index=0;index<array.length;index++)
			{
				CInteger										value=array[index];
				
				System.out.printf("ITEM [%s] VALUE [%s].\n",(index+1),value);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public static void main(String[] args)
	{
		PrintSeparator();

		//TestTypeCastException();
		//TestGenericClass();
		//TestGenericInterfaces();
		//TestGenericRecord();
		//TestNestedGenericTypes();
		//TestArraysAsTypeArguments();
		//TestDiamondOperator();
		//TestGenericsClassGenericsMethods();
		//TestNonGenericsClassGenericsMethods();
		//TestGenericsMethodTypeInference();
		//TestGenericsMethodDiamondOperator();
		//TestTypeErasureOperatorNew();
		//TestTypeErasureOperatorInstanceOf();
		//TestTypeErasureTypeCasting();
		//TestTypeErasureClassKeyword();
		//TestTypeErasureGenericsException();
		//TestTypeErasureStaticMembers();
		//TestTypeErasureMethodOverloadingInGenericClass();
		//TestTypeErasureMethodOverloadingByGenericType();
		//TestTypeErasureMethodOverloadingByGenericType();
		//TypeErasureGenericsArrays();
		//TestRawGenericsTypes();
		//TestRawGenericsTypesConversions();
		//TestGenericsCasting();
		//TestGenericsBounds();
		//TestGenericsThrowsClause();
		//TestCovarianceInvariance();
		//TestGenericsWildcard();
		//TestGenericsWildcardUpperBounds();
		//TestGenericsWildcardLowerBounds();
		//TestGenericsWildcardBounds();
		//TestProducerExtendsConsumerSuperPrinciple();
		//TestTypeTokens();
		//TestCreateTypeParameterInstance();
		//TestGenericsTypeInfer();
		TestTypeParameterArrays();
		
		PrintSeparator();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------