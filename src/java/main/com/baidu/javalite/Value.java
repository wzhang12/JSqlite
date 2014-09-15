package com.baidu.javalite;

/**
 * Created by clark on 14-9-4.
 */
public class Value {
    static {
        NativeRuntime.getInstance().load();
    }

    private long handle;

    protected Value(long handle) {
        this.handle = handle;
    }

    protected long getHandle() {
        return handle;
    }

    public int getType() throws SqliteException {
        return sqlite3_value_type(handle);
    }

    public int getNumericType() throws SqliteException {
        return sqlite3_value_numeric_type(handle);
    }

    public byte[] getBlob() throws SqliteException {
        return sqlite3_value_blob(handle);
    }

    public double getDouble() throws SqliteException {
        return sqlite3_value_double(handle);
    }

    public int getInt() throws SqliteException {
        return sqlite3_value_int(handle);
    }

    public long getInt64() throws SqliteException {
        return sqlite3_value_int64(handle);
    }

    public String getText() throws SqliteException {
        return sqlite3_value_text(handle);
    }

    private static native byte[] sqlite3_value_blob(long handle) throws SqliteException;

    private static native double sqlite3_value_double(long handle) throws SqliteException;

    private static native int sqlite3_value_int(long handle) throws SqliteException;

    private static native long sqlite3_value_int64(long handle) throws SqliteException;

    private static native String sqlite3_value_text(long handle) throws SqliteException;

    private static native int sqlite3_value_type(long handle) throws SqliteException;

    private static native int sqlite3_value_numeric_type(long handle) throws SqliteException;
}
