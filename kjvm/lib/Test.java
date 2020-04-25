
public class Test implements ITest, ITest2, ITest3, ITest4
{
	public String name;
	public int a, b, c, d, e, f;


	public Test()
	{
		
	}
	public native void Print(String p);
	public int Entry()
	{		
		long i=10L;
		//String str=String.valueOf(i);
		name = "Super Class Method OK";
		//name += " StringBuilder Test "+i;
		Print(name);
		return 2;
	}
	public int add(int a, int b)
	{
		try
		{
			return a + b;
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
		return 0;
	}
	public int Sub(int a, int b)
	{
		return a - b;
	}
	public int mul(int a, int b)
	{
		return a * b;
	}
	public int div(int a, int b)
	{
		return a / b;
	}
}