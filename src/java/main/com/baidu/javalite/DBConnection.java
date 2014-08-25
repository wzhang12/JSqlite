package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class DBConnection {
    private long sqlite3Handle;

    protected DBConnection(long handle) throws SqliteException {
        if (handle == 0) {
            throw new SqliteException("Native handle is NULL!");
        }
        sqlite3Handle = handle;
    }

    protected long getNativeHandle() {
        return sqlite3Handle;
    }

    public void close() throws SqliteException {
        if (isValid()) {
            sqlite3_close(sqlite3Handle);
            sqlite3Handle = 0;
        }
    }

    public boolean isValid() {
        return sqlite3Handle != 0;
    }

    private static native void sqlite3_close(long handle) throws SqliteException;
}
