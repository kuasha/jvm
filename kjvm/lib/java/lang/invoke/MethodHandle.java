package java.lang.invoke;

public class MethodHandle {
    private MethodType methodType;
    public MethodHandle() {

    }
    
    public MethodHandle asType(MethodType newType) {
        this.methodType = newType;
        return this;
    }

    public Object invoke(Object... args) {
        return "String from MethodHandle.invoke";
    }

    public Object invokeExact(Object... args) {
        return null;
    }

    public MethodType type() {
        return methodType;
    }

    class Lookup {
        
    }
}