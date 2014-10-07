package com.baidu.javalite;

import java.io.File;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by clark on 14-9-15.
 */
public class NativeRuntime implements NativeLoadPolicy {

    public static final String J_SQLITE_LIB_NAME = "JSqlite";
    private boolean inited;  // init with false

    private List<NativeLoadPolicy> nativeLoadPolicies = new LinkedList<NativeLoadPolicy>();

    private NativeRuntime() {
        nativeLoadPolicies.add(new CommonLoadPolicy());
        nativeLoadPolicies.add(new JarDirLoadPolicy());
        nativeLoadPolicies.add(new JarParentLoadPolicy());
        nativeLoadPolicies.add(new LibDirLoadPolicy("libs"));
        nativeLoadPolicies.add(new LibDirLoadPolicy("lib"));
        nativeLoadPolicies.add(new ParentLibDirLoadPolicy("libs"));
        nativeLoadPolicies.add(new ParentLibDirLoadPolicy("lib"));
    }

    public synchronized void load() {
        if (!inited) {
            inited = findNativeLibPath();
        }
    }

    /**
     * 在 jar 包所在目录下查找动态链接库文件
     * @return
     */
    public boolean findNativeLibPath() {
        for (NativeLoadPolicy policy : nativeLoadPolicies) {
            if (policy.findNativeLibPath()) {
                return true;
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

interface NativeLoadPolicy {
    boolean findNativeLibPath();
}

class CommonLoadPolicy implements NativeLoadPolicy {
    @Override
    public boolean findNativeLibPath() {
        try {
            System.loadLibrary(NativeRuntime.J_SQLITE_LIB_NAME);
            return true;
        } catch (Throwable e) {
            return false;
        }
    }
}

class JarDirLoadPolicy implements NativeLoadPolicy {
    @Override
    public boolean findNativeLibPath() {
        try {
            File jar = new File(JarDirLoadPolicy.class.getProtectionDomain().getCodeSource().getLocation().toURI());
            String parent = jar.getParent();
            String libfileName = System.mapLibraryName(NativeRuntime.J_SQLITE_LIB_NAME);
            File libFile = new File(parent, libfileName);
            if (libFile.isFile()) {
                System.load(libFile.getAbsolutePath());
                return true;
            }
        } catch (Throwable e) {
        }
        return false;
    }
}

class JarParentLoadPolicy implements NativeLoadPolicy {
    @Override
    public boolean findNativeLibPath() {
        try {
            File jar = new File(JarDirLoadPolicy.class.getProtectionDomain().getCodeSource().getLocation().toURI());
            String parent = jar.getParentFile().getParent();
            String libfileName = System.mapLibraryName(NativeRuntime.J_SQLITE_LIB_NAME);
            File libFile = new File(parent, libfileName);
            if (libFile.isFile()) {
                System.load(libFile.getAbsolutePath());
                return true;
            }
        } catch (Throwable e) {
        }
        return false;
    }
}

class LibDirLoadPolicy implements NativeLoadPolicy {
    private String dirName;

    LibDirLoadPolicy(String dirName) {
        this.dirName = dirName;
    }

    @Override
    public boolean findNativeLibPath() {
        try {
            File jar = new File(JarDirLoadPolicy.class.getProtectionDomain().getCodeSource().getLocation().toURI());
            String parent = jar.getParent();
            String libfileName = System.mapLibraryName(NativeRuntime.J_SQLITE_LIB_NAME);
            File libFile = new File(new File(parent, dirName), libfileName);
            if (libFile.isFile()) {
                System.load(libFile.getAbsolutePath());
                return true;
            }
        } catch (Throwable e) {
        }
        return false;
    }
}

class ParentLibDirLoadPolicy implements NativeLoadPolicy {
    private String dirName;

    ParentLibDirLoadPolicy(String dirName) {
        this.dirName = dirName;
    }

    @Override
    public boolean findNativeLibPath() {
        try {
            File jar = new File(JarDirLoadPolicy.class.getProtectionDomain().getCodeSource().getLocation().toURI());
            String parent = jar.getParentFile().getParent();
            String libfileName = System.mapLibraryName(NativeRuntime.J_SQLITE_LIB_NAME);
            File libFile = new File(new File(parent, dirName), libfileName);
            if (libFile.isFile()) {
                System.load(libFile.getAbsolutePath());
                return true;
            }
        } catch (Throwable e) {
        }
        return false;
    }
}