package com.baidu.javalite;

/**
 * Created by clark on 14-9-4.
 */
public class Context implements Closeable {
    static {
        NativeRuntime.getInstance().load();
    }

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

    public void setResultError(String msg, int code) throws SqliteException {
        sqlite3_result_error(handle, msg, code);
    }

    public void setResultErrorTooBig() throws SqliteException {
        sqlite3_result_error_toobig(handle);
    }

    public void setResultErrorNoMem() throws SqliteException {
        sqlite3_result_error_nomem(handle);
    }

    public void setResultErrorCode(int code) throws SqliteException {
        sqlite3_result_error_code(handle, code);
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

    private static native void sqlite3_result_error(long handle, String msg, int code) throws SqliteException;

    private static native void sqlite3_result_error_toobig(long handle) throws SqliteException;

    private static native void sqlite3_result_error_nomem(long handle) throws SqliteException;

    private static native void sqlite3_result_error_code(long handle, int code) throws SqliteException;
}
