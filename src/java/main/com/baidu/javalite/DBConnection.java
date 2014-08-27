package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class DBConnection implements Closeable, Validable {
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

    @Override
    protected void finalize() throws Throwable {
        try {
            close();
        } finally {
            super.finalize();
        }
    }

    @Override
    public void close() throws SqliteException {
        if (isValid()) {
            sqlite3_close(sqlite3Handle);
            sqlite3Handle = 0;
        }
    }

    @Override
    public boolean isValid() {
        return sqlite3Handle != 0;
    }

    public void exec(String sql, SqlExecCallback callback) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_exec(sqlite3Handle, sql, callback);
    }

    public void exec(String sql) throws SqliteException {
        exec(sql, null);
    }

    public int getRowChanges() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_changes(sqlite3Handle);
    }

    public int getTotalRowChanges() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_total_changes(sqlite3Handle);
    }

    public long getLastInsertRowid() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_last_insert_rowid(sqlite3Handle);
    }

    public TableResult getTable(String sql) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_get_table(sqlite3Handle, sql);
    }

    public PrepareStmt prepare(String sql) throws SqliteException {
        DBHelper.checkValidable(this);
        PrepareStmt prepareStmt = new PrepareStmt(this, sqlite3_prepare_v2(sqlite3Handle, sql));
        return prepareStmt;
    }

    public Transaction newTransaction() {
        return new Transaction(this);
    }

    private static native long sqlite3_prepare_v2(long handle, String sql) throws SqliteException;

    private static native TableResult sqlite3_get_table(long handle, String sql) throws SqliteException;

    private static native long sqlite3_last_insert_rowid(long handle) throws SqliteException;

    private static native int sqlite3_changes(long handle) throws SqliteException;

    private static native int sqlite3_total_changes(long handle) throws SqliteException;

    private static native void sqlite3_exec(long handle, String sql, SqlExecCallback callback) throws SqliteException;

    private static native void sqlite3_close(long handle) throws SqliteException;
}
