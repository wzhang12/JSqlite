package com.baidu.javalite;

/**
 * Created by clark on 14-8-25.
 */
public class PrepareStmt {
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

    public void close() throws SqliteException {
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
