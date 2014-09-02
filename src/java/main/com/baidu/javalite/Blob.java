package com.baidu.javalite;

import java.io.InputStream;
import java.io.OutputStream;

/**
 * Created by clark on 14-9-1.
 */
public class Blob implements Closeable, Validable {
    private long handle;
    private final int flags;

    protected Blob(DBConnection connection,
                   String dbName,
                   String tbName,
                   String colName,
                   long rowId,
                   int flags) throws SqliteException {
        if (connection == null) {
            throw new SqliteException("DBConnection is null!");
        }

        if (dbName == null) {
            throw new SqliteException("There must be a database name. ie. \"main\"");
        }

        if (tbName == null) {
            throw new SqliteException("There must be a table name.");
        }

        if (colName == null) {
            throw new SqliteException("There must be a column name.");
        }

        this.flags = flags;
        handle = sqlite3_blob_open(connection.getNativeHandle(),
                dbName, tbName, colName, rowId, flags);
    }

    @Override
    public boolean isValid() {
        return handle != 0;
    }

    @Override
    public void close() throws SqliteException {
        if (isValid()) {
            sqlite3_blob_close(handle);
            handle = 0;
        }
    }

    public void reopen(long newRowId) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_blob_reopen(handle, newRowId);
    }

    public boolean isReadWriteBlob() {
        return flags != 0;
    }

    public boolean isOnlyReadBlob() {
        return flags == 0;
    }

    public InputStream newInputStream() throws SqliteException {
        return new BlobInputStream(this);
    }

    public OutputStream newOutputStream() throws SqliteException {
        if (isOnlyReadBlob()) {
            throw new SqliteException("It's a only read blob!");
        }
        return new BlobOutputStream(this);
    }

    public int size() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_blob_bytes(handle);
    }

    protected void read(byte[] buf, int offset, int length, int bOffset) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_blob_read(handle, buf, offset, length, bOffset);
    }

    protected void write(byte[] buf, int offset, int length, int bOffset) throws SqliteException {
        DBHelper.checkValidable(this);
        sqlite3_blob_write(handle, buf, offset, length, bOffset);
    }

    private static native long sqlite3_blob_open(long connHandle,
                                                 String zDb,
                                                 String zTable,
                                                 String zColumn,
                                                 long rowId,
                                                 int flags) throws SqliteException;

    private static native void sqlite3_blob_reopen(long handle, long newRowId) throws SqliteException;

    private static native void sqlite3_blob_close(long handle) throws SqliteException;

    private static native int sqlite3_blob_bytes(long handle) throws SqliteException;

    private static native void sqlite3_blob_read(long handle, byte[] buf,
                                                 int offset, int length, int blobOffset) throws SqliteException;

    private static native void sqlite3_blob_write(long handle, byte[] buf,
                                                  int offset, int length, int blobOffset) throws SqliteException;
}
