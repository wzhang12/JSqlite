package com.baidu.javalite;

/**
 * Created by clark on 14-9-15.
 */
public class NativeRuntime {

    private boolean inited;  // init with false

    private NativeRuntime() {}

    public void load() {
        if (!inited) {
            System.loadLibrary("JSqlite");
            inited = true;
        }
    }

    private static class Holder {
        private static final NativeRuntime NATIVE_RUNTIME = new NativeRuntime();
    }

    public static NativeRuntime getInstance() {
        return Holder.NATIVE_RUNTIME;
    }

}
