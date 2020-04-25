package java.lang;

public class String
{
	private int pNativeString;
	
	public static native String valueOf(boolean b);
	public static native String valueOf(char c);	
	public static native String valueOf(int i);
	public static native String valueOf(float f);
	public static native String valueOf(long l);
	public static native String valueOf(double d);
	public static native String valueOf(Object obj);	
	
	public String toString()
	{
		return this;
	}	
}