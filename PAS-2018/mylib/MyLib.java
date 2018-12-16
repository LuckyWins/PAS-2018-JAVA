package mylib;

public class MyLib {
   	/** return rounded pow of int */
   	public static int pow(int n) {
   		Double d = Math.pow(Double.valueOf(n),2);
   		//int i = d.intValue();
    	return d.intValue(); 
   	}

   	/** return rounded sqrt of int **/
   	public static int sqrt(int n) {
   		Double d = Math.sqrt(Double.valueOf(n));
   		return d.intValue();
   	}
}