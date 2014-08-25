package com.baidu.javalite;

import java.io.File;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class Database {
    static {
        System.loadLibrary("JSqlite");
    }

    private File dbFile;

    public Database(File dbFile) {
        if (!dbFile.isFile()) {
            throw new IllegalArgumentException(dbFile.getName() + " isn't a file!");
        }

        this.dbFile = dbFile;
    }

    public DBConnection open(int flags, String zVfs) throws SqliteException {
        long handle = sqlite3_open_v2(dbFile.getAbsolutePath(), flags, zVfs);
        return new DBConnection(handle);
    }

    public DBConnection open(int flags) throws SqliteException {
        return open(flags, null);
    }

    public DBConnection open() throws SqliteException {
        return open(Flags.SQLITE_OPEN_READWRITE | Flags.SQLITE_OPEN_CREATE);
    }

    private static native long sqlite3_open_v2(String filename, int flags, String zVfs) throws SqliteException;
}
