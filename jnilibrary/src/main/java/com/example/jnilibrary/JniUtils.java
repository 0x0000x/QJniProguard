package com.example.jnilibrary;

public class JniUtils {

    // Used to load the 'native-lib' library.
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public static native String stringFromJNI();

    public static native int calculateByJNI(int count);
}
