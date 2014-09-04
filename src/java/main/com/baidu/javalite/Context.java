package com.baidu.javalite;

/**
 * Created by clark on 14-9-4.
 */
public class Context implements Closeable {
    private long handle;
    private boolean isAggregateContextFreed;

    protected Context(long handle) {
        this.handle = handle;
    }

    public Object getUserData() throws SqliteException {
        return sqlite3_user_data(handle);
    }

    public DBConnection getConnection() throws SqliteException {
        return new DBConnection(sqlite3_context_db_handle(handle));
    }

    public void setAggregateContext(Object value) throws SqliteException {
        sqlite3_aggregate_context(handle, value);
    }

    public Object getAggregateContext() throws SqliteException {
        return sqlite3_aggregate_context(handle);
    }

    @Override
    public void close() throws SqliteException {
        if (!isAggregateContextFreed) {
            isAggregateContextFreed = true;
            sqlite3_aggregate_context_free(handle);
        }
    }

    private static native Object sqlite3_user_data(long handle) throws SqliteException;

    private static native long sqlite3_context_db_handle(long handle) throws SqliteException;

    private static native void sqlite3_aggregate_context(long handle, Object value) throws SqliteException;

    private static native Object sqlite3_aggregate_context(long handle) throws SqliteException;

    private static native void sqlite3_aggregate_context_free(long handle) throws SqliteException;
}
