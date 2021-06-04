package java.lang.invoke;

public class ConstantCallSite extends CallSite {
    MethodHandle target;
    
    public ConstantCallSite(MethodHandle target) {
        this.target = target;
    }    

    public MethodHandle dynamicInvoker() {
        return target;
    }

    public MethodHandle getTarget() {
        return target;
    }

    public void setTarget(MethodHandle ignore) {
        throw new UnsupportedOperationException();
    }
}