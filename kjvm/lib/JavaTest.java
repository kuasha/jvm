
public class JavaTest extends Test implements ITest, ITest2, ITest3, ITest4
{
	public String name2;
	public int a2, b2, c2, d2, e2, f2;
	public static int p = 0;


	public JavaTest()
	{
	}
	/*
	public int Entry()
	{
		//a2 = 1;
		//b2 = 5;
		Test[] t = new Test[6];
		int[] ai = new int[6];
		name2 = "In Recursion\n";
		long l = 10;

		for (int i = 0; i < 6; i++)
		{
			t[i] = new Test();
			
			t[i].Print(name2);
			l++;
		}
		return c = add(ai[3], ai[5]);
	}
	*/

	public native int addn(int a, int b);
	

	public int recur(int p)
	{
		//Print(name2);
		if (p == 0) return 0;
		return p+recur(p - 1);
	}
	public int add(int a, int b)
	{		
		int i = 0;
		Test t = new Test();
		do
		{
			//t.Print(name2);
			a += 1;
			i++;
		} while (i < b);

		return a + recur(10) ;
	}

	public int Sub(int a, int b)
	{
		return mul(a,b) - b;
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