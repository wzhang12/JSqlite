package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class DBConnection implements Closeable, Validable {
    static {
        NativeRuntime.getInstance().load();
    }

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
        return new PrepareStmt(this, sqlite3_prepare_v2(handle, sql));
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

    public void setCommitHook(CommitHook hook) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_commit_hook(handle, hook);
    }

    public void setRollbackHook(RollbackHook hook) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_rollback_hook(handle, hook);
    }

    public void setUpdateHook(UpdateHook hook) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_update_hook(handle, hook);
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

    public int limit(int id, int newVal) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_limit(handle, id, newVal);
    }

    public PrepareStmt nextStmt(PrepareStmt old) throws SqliteException {
        DBHelper.checkValidable(this);
        long newStmtHandle;
        if (old != null && old.isValid()) {
            newStmtHandle = sqlite3_next_stmt(handle, old.getHandle());
        } else {
            newStmtHandle = sqlite3_next_stmt(handle, 0);
        }
        return new PrepareStmt(this, newStmtHandle);
    }

    public void setOnTraceListener(TraceListener listener) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_trace(handle, listener);
    }

    public void setOnProfileListener(ProfileListener listener) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_profile(handle, listener);
    }

    public void setAuthorizer(Authorizer authorizer) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_set_authorizer(handle, authorizer);
    }

    public void createCollation(String name, Collation collation) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_create_collation_v2(handle, name, collation);
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

    private static native void sqlite3_commit_hook(long handle, CommitHook hook) throws SqliteException;

    private static native void sqlite3_rollback_hook(long handle, RollbackHook hook) throws SqliteException;

    private static native void sqlite3_create_function_v2(long handle, String funcName, int nArgs, Object app, ScalarFunction callbacks) throws SqliteException;

    private static native int sqlite3_db_release_memory(long handle) throws SqliteException;

    private static native int sqlite3_limit(long handle, int id, int newVal) throws SqliteException;

    private static native long sqlite3_next_stmt(long conn, long stmt) throws SqliteException;

    private static native void sqlite3_trace(long conn, TraceListener listener) throws SqliteException;

    private static native void sqlite3_profile(long conn, ProfileListener listener) throws SqliteException;

    private static native void sqlite3_update_hook(long conn, UpdateHook hook) throws SqliteException;

    private static native void sqlite3_set_authorizer(long conn, Authorizer authorizer) throws SqliteException;

    private static native void sqlite3_create_collation_v2(long conn, String name, Collation collation) throws SqliteException;
}
