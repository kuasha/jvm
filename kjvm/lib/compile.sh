javac --patch-module java.base=. java/lang/invoke/CallSite.java 
javac --patch-module java.base=. java/lang/invoke/MethodHandle.java
javac --patch-module java.base=. java/lang/invoke/MethodType.java 
javac --patch-module java.base=. java/lang/invoke/MutableCallSite.java 
javac --patch-module java.base=. java/lang/invoke/StringConcatException.java 
javac --patch-module java.base=. java/lang/invoke/MethodHandleHelper.java
javac --patch-module java.base=. java/lang/invoke/StringConcatFactory.java 
javac --patch-module java.base=. java/lang/invoke/StringConcatHelper.java
javac --patch-module java.base=. java/lang/invoke/ConstantCallSite.java