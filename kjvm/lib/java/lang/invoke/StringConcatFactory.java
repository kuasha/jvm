package java.lang.invoke;

public class StringConcatFactory {
    public static CallSite makeConcatWithConstants​(MethodHandles.Lookup lookup,
                                               String name,
                                               MethodType concatType,
                                               String recipe,
                                               Object... constants)
                                        throws StringConcatException {
        MethodHandle handler = new StringConcatHelper(recipe).asType((concatType));
        return new ConstantCallSite(handler);
    }  
}
