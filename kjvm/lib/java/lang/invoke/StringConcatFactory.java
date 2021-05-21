package java.lang.invoke;

public class StringConcatFactory {
    public native static CallSite makeConcatWithConstants​(MethodHandles.Lookup lookup,
                                               String name,
                                               MethodType concatType,
                                               String recipe,
                                               Object... constants)
                                        throws StringConcatException;
}
