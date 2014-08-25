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

    protected void checkHandleState() throws SqliteException {
        if (!isValid()) throw new SqliteException("Native handle already invalid");
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

    public void exec(String sql, SqlExecCallback callback) throws SqliteException {
        checkHandleState();
        sqlite3_exec(sqlite3Handle, sql, callback);
    }

    public void exec(String sql) throws SqliteException {
        exec(sql, null);
    }

    public int getRowChanges() throws SqliteException {
        checkHandleState();
        return sqlite3_changes(sqlite3Handle);
    }

    public long getLastInsertRowid() throws SqliteException {
        checkHandleState();
        return sqlite3_last_insert_rowid(sqlite3Handle);
    }

    private static native long sqlite3_last_insert_rowid(long handle);
    private static native int sqlite3_changes(long handle);
    private static native void sqlite3_exec(long handle, String sql, SqlExecCallback callback) throws SqliteException;
    private static native void sqlite3_close(long handle) throws SqliteException;
}
