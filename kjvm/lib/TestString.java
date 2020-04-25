

public class TestString
{
	public String str1;
	public TestString()
	{
		String snum;		
		str1="Hello";
		str1=str1+" World";
		int i=100;
		boolean b = false;
		char c = 'k';
		float f= 1.0f;
		double d= 1.0;
		long l=58;
		Object o= new Object();
		snum= str1+i+b+c+f+o+d+l;		
	}
}