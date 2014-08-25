package com.baidu.javalite;

/**
 * Created by clark on 14-8-25.
 */
public class PrepareStmt {
    private long handle;
    private DBConnection connection;

    protected PrepareStmt(DBConnection conn, long handle) throws SqliteException {
        if (handle == 0) {
            throw new SqliteException("Native handle is NULL!");
        }
        this.connection = conn;
        this.handle = handle;
    }

    public boolean isValid() {
        return handle != 0;
    }

    protected void checkHandleState() throws SqliteException {
        if (!isValid()) throw new SqliteException("Native handle already invalid");
    }

    public DBConnection getConnection() {
        return connection;
    }

    public boolean step() throws SqliteException {
        checkHandleState();
        return sqlite3_step(handle);
    }

    public void close() throws SqliteException {
        if (isValid()) {
            sqlite3_finalize(handle);
            handle = 0;
        }
    }

    public void reset() throws SqliteException {
        checkHandleState();
        sqlite3_reset(handle);
    }

    private static native boolean sqlite3_step(long handle) throws SqliteException;

    private static native void sqlite3_finalize(long handle) throws SqliteException;

    private static native void sqlite3_reset(long handle) throws SqliteException;
}
