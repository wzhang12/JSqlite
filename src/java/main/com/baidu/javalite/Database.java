package com.baidu.javalite;

import java.io.File;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class Database {
    static {
        NativeRuntime.getInstance().load();
    }

    private File dbFile;

    public Database(File dbFile) {
        this.dbFile = dbFile;
    }

    public Database(String filepath) {
        this.dbFile = new File(filepath);
    }

    private DBConnection open(int flags, String zVfs) throws SqliteException {
        long handle = sqlite3_open_v2(dbFile.getAbsolutePath(), flags, zVfs);
        return new DBConnection(handle);
    }

    public DBConnection open(int flags) throws SqliteException {
        return open(flags, null);
    }

    public DBConnection open() throws SqliteException {
        return open(Flags.SQLITE_OPEN_READWRITE | Flags.SQLITE_OPEN_CREATE);
    }

    public static boolean isCompiledThreadsafe() {
        return sqlite3_threadsafe();
    }

    public static synchronized void threadmodeConfig(int option) throws SqliteException {
        sqlite3_threadmode_config(option);
    }

    public static void initializeLibrary() throws SqliteException {
        sqlite3_initialize();
    }

    public static synchronized void shutdownLibrary() throws SqliteException {
        sqlite3_shutdown();
    }

    public static String getLibraryVersion() {
        return sqlite3_libversion();
    }

    public static String getLibrarySourceId() {
        return sqlite3_sourceid();
    }

    public static int getLibraryVersionNumber() {
        return sqlite3_libversion_number();
    }

    public static boolean isSqlComplete(String sql) throws SqliteException {
        return sqlite3_complete(sql);
    }

    private static native long sqlite3_open_v2(String filename, int flags, String zVfs) throws SqliteException;

    private static native boolean sqlite3_threadsafe();

    private static native void sqlite3_threadmode_config(int option) throws SqliteException;

    private static native void sqlite3_initialize() throws SqliteException;

    private static native void sqlite3_shutdown() throws SqliteException;

    private static native String sqlite3_libversion();

    private static native String sqlite3_sourceid();

    private static native int sqlite3_libversion_number();

    private static native boolean sqlite3_complete(String sql) throws SqliteException;
}
