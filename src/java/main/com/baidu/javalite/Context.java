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

    public void setResultDouble(double rs) throws SqliteException {
        sqlite3_result_double(handle, rs);
    }

    public void setResultInt(int rs) throws SqliteException {
        sqlite3_result_int(handle, rs);
    }

    public void setResultInt64(long rs) throws SqliteException {
        sqlite3_result_int64(handle, rs);
    }

    public void setResultNull() throws SqliteException {
        sqlite3_result_null(handle);
    }

    public void setResultText(String rs) throws SqliteException {
        sqlite3_result_text(handle, rs);
    }

    public void setResultBlob(byte[] rs) throws SqliteException {
        sqlite3_result_blob(handle, rs);
    }

    public void setResultZeroBlob(int size) throws SqliteException {
        sqlite3_result_zeroblob(handle, size);
    }

    public void setResultValue(Value rs) throws SqliteException {
        sqlite3_result_value(handle, rs.getHandle());
    }

    private static native Object sqlite3_user_data(long handle) throws SqliteException;

    private static native long sqlite3_context_db_handle(long handle) throws SqliteException;

    private static native void sqlite3_aggregate_context(long handle, Object value) throws SqliteException;

    private static native Object sqlite3_aggregate_context(long handle) throws SqliteException;

    private static native void sqlite3_aggregate_context_free(long handle) throws SqliteException;

    private static native void sqlite3_result_double(long handle, double value) throws SqliteException;

    private static native void sqlite3_result_int(long handle, int value) throws SqliteException;

    private static native void sqlite3_result_int64(long handle, long value) throws SqliteException;

    private static native void sqlite3_result_null(long handle) throws SqliteException;

    private static native void sqlite3_result_text(long handle, String value) throws SqliteException;

    private static native void sqlite3_result_blob(long handle, byte[] value) throws SqliteException;

    private static native void sqlite3_result_zeroblob(long handle, int size) throws SqliteException;

    private static native void sqlite3_result_value(long handle, long valueHandle) throws SqliteException;
}
