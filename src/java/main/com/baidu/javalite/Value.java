package com.baidu.javalite;

/**
 * Created by clark on 14-9-4.
 */
public class Value {
    private long handle;

    protected Value(long handle) {
        this.handle = handle;
    }

    private static native byte[] sqlite3_value_blob(long handle) throws SqliteException;

    private static native double sqlite3_value_double(long handle) throws SqliteException;

    private static native int sqlite3_value_int(long handle) throws SqliteException;

    private static native long sqlite3_value_int64(long handle) throws SqliteException;

    private static native String sqlite3_value_text(long handle) throws SqliteException;

    private static native int sqlite3_value_type(long handle) throws SqliteException;

    private static native int sqlite3_value_numeric_type(long handle) throws SqliteException;
}
