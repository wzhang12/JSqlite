package com.baidu.javalite;

/**
 * Created by clark on 14-8-25.
 */
public class PrepareStmt implements Closeable {
    private long handle;
    private DBConnection connection;

    protected PrepareStmt(DBConnection conn, long handle) throws SqliteException {
        if (handle == 0) {
            throw new SqliteException("Native handle is NULL!");
        }
        this.connection = conn;
        this.handle = handle;
    }

    public boolean isValid() {
        return handle != 0;
    }

    protected void checkHandleState() throws SqliteException {
        if (!isValid()) throw new SqliteException("Native handle already invalid");
    }

    public DBConnection getConnection() {
        return connection;
    }

    public boolean step() throws SqliteException {
        checkHandleState();
        return sqlite3_step(handle);
    }

    @Override
    public void close() throws SqliteException {
        _close();
        if (isValid()) {
            connection.removeStmt(this);
        }
    }

    protected void _close() throws SqliteException {
        if (isValid()) {
            sqlite3_finalize(handle);
            handle = 0;
        }
    }

    public void reset() throws SqliteException {
        checkHandleState();
        sqlite3_reset(handle);
    }

    public int getColumnCount() throws SqliteException {
        checkHandleState();
        return sqlite3_column_count(handle);
    }

    public String getColumnName(int column) throws SqliteException {
        checkHandleState();
        return sqlite3_column_name(handle, column);
    }

    public String getColumnDatabaseName(int column) throws SqliteException {
        checkHandleState();
        return sqlite3_column_database_name(handle, column);
    }

    public String getColumnTableName(int column) throws SqliteException {
        checkHandleState();
        return sqlite3_column_table_name(handle, column);
    }

    public String getColumnOriginName(int column) throws SqliteException {
        checkHandleState();
        return sqlite3_column_origin_name(handle, column);
    }

    public String getColumnDecltype(int column) throws SqliteException {
        checkHandleState();
        return sqlite3_column_decltype(handle, column);
    }

    public int getDataCount() throws SqliteException {
        checkHandleState();
        return sqlite3_data_count(handle);
    }

    public byte[] getColumnBlob(int column) throws SqliteException {
        checkHandleState();
        return sqlite3_column_blob(handle, column);
    }

    public double getColumnDouble(int column) throws SqliteException {
        checkHandleState();
        return sqlite3_column_double(handle, column);
    }

    public int getColumnInt(int column) throws SqliteException {
        checkHandleState();
        return sqlite3_column_int(handle, column);
    }

    public long getColumnInt64(int column) throws SqliteException {
        checkHandleState();
        return sqlite3_column_int64(handle, column);
    }

    public String getColumnText(int column) throws SqliteException {
        checkHandleState();
        return sqlite3_column_text(handle, column);
    }

    public int getColumnType(int column) throws SqliteException {
        checkHandleState();
        return sqlite3_column_type(handle, column);
    }

    public void bindBlob(int column, byte[] value) throws SqliteException {
        if (value == null) {
            bindNull(column);
            return;
        }

        checkHandleState();
        sqlite3_bind_blob(handle, column, value);
    }

    public void bindDouble(int column, double value) throws SqliteException {
        checkHandleState();
        sqlite3_bind_double(handle, column, value);
    }

    public void bindInt(int column, int value) throws SqliteException {
        checkHandleState();
        sqlite3_bind_int(handle, column, value);
    }

    public void bindInt64(int column, long value) throws SqliteException {
        checkHandleState();
        sqlite3_bind_int64(handle, column, value);
    }

    public void bindNull(int column) throws SqliteException {
        checkHandleState();
        sqlite3_bind_null(handle, column);
    }

    public void bindText(int column, String value) throws SqliteException {
        if (value == null) {
            bindNull(column);
            return;
        }

        checkHandleState();
        sqlite3_bind_text(handle, column, value);
    }

    public void clearBinding() throws SqliteException {
        checkHandleState();
        sqlite3_clear_bindings(handle);
    }

    public int getBindParameterIndex(String name) throws SqliteException {
        checkHandleState();
        return sqlite3_bind_parameter_index(handle, name);
    }

    public String getBindParameterName(int index) throws SqliteException {
        checkHandleState();
        return sqlite3_bind_parameter_name(handle, index);
    }

    public int getBindParameterCount() throws SqliteException {
        checkHandleState();
        return sqlite3_bind_parameter_count(handle);
    }

    public boolean isBusy() throws SqliteException {
        checkHandleState();
        return sqlite3_stmt_busy(handle);
    }

    public boolean isReadOnly() throws SqliteException {
        checkHandleState();
        return sqlite3_stmt_readonly(handle);
    }

    public String getSql() throws SqliteException {
        checkHandleState();
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
}
