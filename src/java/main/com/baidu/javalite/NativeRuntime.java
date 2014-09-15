package com.baidu.javalite;

import java.io.File;
import java.net.URISyntaxException;

/**
 * Created by clark on 14-9-15.
 */
public class NativeRuntime {

    public static final String J_SQLITE_LIB_NAME = "JSqlite";
    private boolean inited;  // init with false

    private NativeRuntime() {}

    public void load() {
        if (!inited) {
            if (!findNativeLibPath()) {
                System.loadLibrary(J_SQLITE_LIB_NAME);
            }
            inited = true;
        }
    }

    private boolean findNativeLibPath() {
        try {
            File jar = new File(NativeRuntime.class.getProtectionDomain().getCodeSource().getLocation().toURI());
            String parent = jar.getParent();
            String libfileName = System.mapLibraryName(J_SQLITE_LIB_NAME);
            System.load(new File(parent, libfileName).getAbsolutePath());
            return true;
        } catch (URISyntaxException e) {
        }

        return false;
    }

    private static class Holder {
        private static final NativeRuntime NATIVE_RUNTIME = new NativeRuntime();
    }

    public static NativeRuntime getInstance() {
        return Holder.NATIVE_RUNTIME;
    }

}
