package java.lang.invoke;

public class StringConcatHelper implements MethodHandleHelper {
    private String template;
    public StringConcatHelper(String template) {
        this.template = template;
    }

    //public native String makeConcatWithConstants(String a, long b);
    public String makeConcatWithConstants(String a, long b) {
        return "Hello";
    }

    public MethodHandle asType(MethodType newType) {
        return null;
    }
}
