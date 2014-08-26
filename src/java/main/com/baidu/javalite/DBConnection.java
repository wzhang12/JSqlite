package com.baidu.javalite;

import java.util.HashSet;
import java.util.Set;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class DBConnection implements Closeable {
    private long sqlite3Handle;
    private Set<PrepareStmt> prepareStmtSet = new HashSet<PrepareStmt>();

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

    protected void removeStmt(PrepareStmt stmt) {
        prepareStmtSet.remove(stmt);
    }

    @Override
    protected void finalize() throws Throwable {
        try {
            safeClose();
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

    public void closeAllStmt() throws SqliteException {
        if (isValid()) {
            for (PrepareStmt stmt : prepareStmtSet) {
                stmt._close();
            }
            prepareStmtSet.clear();
        }
    }

    public void safeClose() throws SqliteException {
        closeAllStmt();
        close();
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

    public TableResult getTable(String sql) throws SqliteException {
        checkHandleState();
        return sqlite3_get_table(sqlite3Handle, sql);
    }

    public PrepareStmt prepare(String sql) throws SqliteException {
        checkHandleState();
        PrepareStmt prepareStmt = new PrepareStmt(this, sqlite3_prepare_v2(sqlite3Handle, sql));
        prepareStmtSet.add(prepareStmt);
        return prepareStmt;
    }

    public void beginTransaction() throws SqliteException {
        exec("begin;");
    }

    public void endTransaction() throws SqliteException {
        exec("commit;");
    }

    public void rollback() throws SqliteException {
        exec("rollback;");
    }

    public void savepoint(String point) throws SqliteException {
        exec(String.format("savepoint %s;", point));
    }

    public void rollbackTo(String point) throws SqliteException {
        exec(String.format("rollback to %s;", point));
    }

    private static native long sqlite3_prepare_v2(long handle, String sql) throws SqliteException;

    private static native TableResult sqlite3_get_table(long handle, String sql) throws SqliteException;

    private static native long sqlite3_last_insert_rowid(long handle);

    private static native int sqlite3_changes(long handle);

    private static native void sqlite3_exec(long handle, String sql, SqlExecCallback callback) throws SqliteException;

    private static native void sqlite3_close(long handle) throws SqliteException;
}
