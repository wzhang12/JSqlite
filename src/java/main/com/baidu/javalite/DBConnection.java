package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class DBConnection implements Closeable, Validable {
    private long handle;

    protected DBConnection(long handle) throws SqliteException {
        if (handle == 0) {
            throw new SqliteException("Native handle is NULL!");
        }
        this.handle = handle;
    }

    protected long getNativeHandle() {
        return handle;
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
            sqlite3_close(handle);
            handle = 0;
        }
    }

    @Override
    public boolean isValid() {
        return handle != 0;
    }

    public void exec(String sql, SqlExecCallback callback) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_exec(handle, sql, callback);
    }

    public void exec(String sql) throws SqliteException {
        exec(sql, null);
    }

    public int getRowChanges() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_changes(handle);
    }

    public int getTotalRowChanges() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_total_changes(handle);
    }

    public long getLastInsertRowid() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_last_insert_rowid(handle);
    }

    public TableResult getTable(String sql) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_get_table(handle, sql);
    }

    public PrepareStmt prepare(String sql) throws SqliteException {
        DBHelper.checkValidable(this);
        PrepareStmt prepareStmt = new PrepareStmt(this, sqlite3_prepare_v2(handle, sql));
        return prepareStmt;
    }

    public Transaction newTransaction() {
        return new Transaction(this);
    }

    public void setBusyHandler(BusyHandler handler) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_busy_handler(handle, handler);
    }

    public void setBusyTimeout(int ms) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_busy_timeout(handle, ms);
    }

    public void setCommitHook(CommitHook hook, Object arg) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_commit_hook(handle, hook, arg);
    }

    public void setRollbackHook(RollbackHook hook, Object arg) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_rollback_hook(handle, hook, arg);
    }

    public Blob getReadWriteBlob(String dbName,
                                 String tbName,
                                 String colName,
                                 long rowId) throws SqliteException {
        return new Blob(this, dbName, tbName, colName, rowId, 1);
    }

    public Blob getReadOnlyBlob(String dbName,
                                String tbName,
                                String colName,
                                long rowId) throws SqliteException {
        return new Blob(this, dbName, tbName, colName, rowId, 0);
    }

    public void createFunction(String funcName, int nArgs, Object app, ScalarFunction callbacks) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_create_function_v2(handle, funcName, nArgs, app, callbacks);
    }

    public int releaseDbMemory() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_db_release_memory(handle);
    }

    private static native long sqlite3_prepare_v2(long handle, String sql) throws SqliteException;

    private static native TableResult sqlite3_get_table(long handle, String sql) throws SqliteException;

    private static native long sqlite3_last_insert_rowid(long handle) throws SqliteException;

    private static native int sqlite3_changes(long handle) throws SqliteException;

    private static native int sqlite3_total_changes(long handle) throws SqliteException;

    private static native void sqlite3_exec(long handle, String sql, SqlExecCallback callback) throws SqliteException;

    private static native void sqlite3_close(long handle) throws SqliteException;

    private static native void sqlite3_busy_handler(long handle, BusyHandler handler) throws SqliteException;

    private static native void sqlite3_busy_timeout(long handle, int ms) throws SqliteException;

    private static native void sqlite3_commit_hook(long handle, CommitHook hook, Object arg) throws SqliteException;

    private static native void sqlite3_rollback_hook(long handle, RollbackHook hook, Object arg) throws SqliteException;

    private static native void sqlite3_create_function_v2(long handle, String funcName, int nArgs, Object app, ScalarFunction callbacks) throws SqliteException;

    private static native int sqlite3_db_release_memory(long handle) throws SqliteException;
}
