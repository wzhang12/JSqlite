package com.baidu.javalite;

import java.io.File;

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

    /**
     * 在 jar 包所在目录下查找动态链接库文件
     * @return
     */
    private boolean findNativeLibPath() {
        try {
            System.loadLibrary(J_SQLITE_LIB_NAME);
            return true;
        } catch (Throwable e) {
            try {
                File jar = new File(NativeRuntime.class.getProtectionDomain().getCodeSource().getLocation().toURI());
                String parent = jar.getParent();
                String libfileName = System.mapLibraryName(J_SQLITE_LIB_NAME);
                File libFile = new File(parent, libfileName);
                if (libFile.isFile()) {
                    System.load(libFile.getAbsolutePath());
                    return true;
                }
            } catch (Throwable tr) {
            }
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
