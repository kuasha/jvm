import java.lang.invoke.*;

public class LookupTest {
    public static void main(String[] args) {
        MethodHandles.Lookup lookup = MethodHandles.lookup();
        Class thisClass = lookup.lookupClass();  // (who am I?)
        System.out.println(thisClass);
    }
}
