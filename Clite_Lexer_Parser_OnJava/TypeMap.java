import java.util.*;

public class TypeMap extends HashMap<Variable, Type> { 

// TypeMap is implemented as a Java HashMap.  
// Plus a 'display' method to facilitate experimentation.
	public void display(){
		TypeMap tm = (TypeMap) super.clone();
		for(Map.Entry<Variable, Type> each_item : tm.entrySet())
			System.out.print("<" + each_item.getKey() + ", " + each_item.getValue() + "> ");
		System.out.println();
	}
}
