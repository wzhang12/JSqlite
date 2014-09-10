package com.baidu.javalite;

/**
 * Created by clark on 14-8-25.
 */
public class PrepareStmt implements Closeable, Validable {
    private long handle;
    private DBConnection connection;

    protected PrepareStmt(DBConnection conn, long handle) throws SqliteException {
        if (handle == 0) {
            throw new SqliteException("Native handle is NULL!");
        }
        this.connection = conn;
        this.handle = handle;
    }

    @Override
    public boolean isValid() {
        return handle != 0;
    }

    public DBConnection getConnection() {
        return connection;
    }

    public boolean step() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_step(handle);
    }

    @Override
    public void close() throws SqliteException {
        if (isValid()) {
            sqlite3_finalize(handle);
            handle = 0;
        }
    }

    public void reset() throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_reset(handle);
    }

    public int getColumnCount() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_count(handle);
    }

    public String getColumnName(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_name(handle, column);
    }

    public String getColumnDatabaseName(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_database_name(handle, column);
    }

    public String getColumnTableName(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_table_name(handle, column);
    }

    public String getColumnOriginName(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_origin_name(handle, column);
    }

    public String getColumnDecltype(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_decltype(handle, column);
    }

    public int getDataCount() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_data_count(handle);
    }

    public byte[] getColumnBlob(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_blob(handle, column);
    }

    public double getColumnDouble(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_double(handle, column);
    }

    public int getColumnInt(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_int(handle, column);
    }

    public long getColumnInt64(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_int64(handle, column);
    }

    public String getColumnText(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_text(handle, column);
    }

    public int getColumnType(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_column_type(handle, column);
    }

    public void bindBlob(int column, byte[] value) throws SqliteException {
        if (value == null) {
            bindNull(column);
        } else {
            DBHelper.checkValidable(this);
            sqlite3_bind_blob(handle, column, value);
        }
    }

    public void bindBlob(String name, byte[] value) throws SqliteException {
        DBHelper.checkValidable(this);
        int index = sqlite3_bind_parameter_index(handle, name);
        bindBlob(index, value);
    }

    public void bindDouble(int column, double value) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_bind_double(handle, column, value);
    }

    public void bindDouble(String name, double value) throws SqliteException {
        DBHelper.checkValidable(this);
        int index = sqlite3_bind_parameter_index(handle, name);
        bindDouble(index, value);
    }

    public void bindInt(int column, int value) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_bind_int(handle, column, value);
    }

    public void bindInt(String name, int value) throws SqliteException {
        DBHelper.checkValidable(this);
        int index = sqlite3_bind_parameter_index(handle, name);
        bindInt(index, value);
    }

    public void bindInt64(int column, long value) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_bind_int64(handle, column, value);
    }

    public void bindInt64(String name, long value) throws SqliteException {
        DBHelper.checkValidable(this);
        int index = sqlite3_bind_parameter_index(handle, name);
        bindInt64(index, value);
    }

    public void bindNull(int column) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_bind_null(handle, column);
    }

    public void bindNull(String name) throws SqliteException {
        DBHelper.checkValidable(this);
        int index = sqlite3_bind_parameter_index(handle, name);
        sqlite3_bind_null(handle, index);
    }

    public void bindText(int column, String value) throws SqliteException {
        if (value == null) {
            bindNull(column);
        } else {
            DBHelper.checkValidable(this);
            sqlite3_bind_text(handle, column, value);
        }
    }

    public void bindText(String name, String value) throws SqliteException {
        DBHelper.checkValidable(this);
        int index = sqlite3_bind_parameter_index(handle, name);
        bindText(index, value);
    }

    public void bindZeroBlob(int column, int bytes) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_bind_zeroblob(handle, column, bytes);
    }

    public void bindZeroBlob(String name, int bytes) throws SqliteException {
        DBHelper.checkValidable(this);
        int index = sqlite3_bind_parameter_index(handle, name);
        bindZeroBlob(index, bytes);
    }

    public void clearBinding() throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_clear_bindings(handle);
    }

    public int getBindParameterIndex(String name) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_bind_parameter_index(handle, name);
    }

    public String getBindParameterName(int index) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_bind_parameter_name(handle, index);
    }

    public int getBindParameterCount() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_bind_parameter_count(handle);
    }

    public boolean isBusy() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_stmt_busy(handle);
    }

    public boolean isReadOnly() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_stmt_readonly(handle);
    }

    public String getSql() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_sql(handle);
    }

    private static native String sqlite3_sql(long handle) throws SqliteException;

    private static native boolean sqlite3_stmt_readonly(long handle) throws SqliteException;

    private static native boolean sqlite3_stmt_busy(long handle) throws SqliteException;

    private static native int sqlite3_bind_parameter_count(long handle) throws SqliteException;

    private static native String sqlite3_bind_parameter_name(long handle, int index) throws SqliteException;

    private static native int sqlite3_bind_parameter_index(long handle, String zName) throws SqliteException;

    private static native void sqlite3_clear_bindings(long handle) throws SqliteException;

    private static native void sqlite3_bind_text(long handle, int column, String value) throws SqliteException;

    private static native void sqlite3_bind_null(long handle, int column) throws SqliteException;

    private static native void sqlite3_bind_int64(long handle, int column, long value) throws SqliteException;

    private static native void sqlite3_bind_int(long handle, int column, int value) throws SqliteException;

    private static native void sqlite3_bind_double(long handle, int column, double value) throws SqliteException;

    private static native void sqlite3_bind_blob(long handle, int column, byte[] blob) throws SqliteException;

    private static native int sqlite3_column_type(long handle, int column) throws SqliteException;

    private static native String sqlite3_column_text(long handle, int column) throws SqliteException;

    private static native long sqlite3_column_int64(long handle, int column) throws SqliteException;

    private static native int sqlite3_column_int(long handle, int column) throws SqliteException;

    private static native double sqlite3_column_double(long handle, int column) throws SqliteException;

    private static native byte[] sqlite3_column_blob(long handle, int column) throws SqliteException;

    private static native int sqlite3_data_count(long handle) throws SqliteException;

    private static native String sqlite3_column_decltype(long handle, int column) throws SqliteException;

    private static native String sqlite3_column_origin_name(long handle, int column) throws SqliteException;

    private static native String sqlite3_column_table_name(long handle, int column) throws SqliteException;

    private static native String sqlite3_column_database_name(long handle, int column) throws SqliteException;

    private static native String sqlite3_column_name(long handle, int column) throws SqliteException;

    private static native int sqlite3_column_count(long handle) throws SqliteException;

    private static native boolean sqlite3_step(long handle) throws SqliteException;

    private static native void sqlite3_finalize(long handle) throws SqliteException;

    private static native void sqlite3_reset(long handle) throws SqliteException;

    private static native void sqlite3_bind_zeroblob(long handle, int column, int bytes) throws SqliteException;
}
