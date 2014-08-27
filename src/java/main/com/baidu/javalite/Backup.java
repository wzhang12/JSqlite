package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-27
 */
public class Backup implements Closeable, Validable {
    private long handle;

    public static Backup create(DBConnection dst, String dstDbName, DBConnection src, String srcDbName) throws SqliteException {
        return new Backup(sqlite3_backup_init(
                dst.getNativeHandle(), dstDbName, src.getNativeHandle(), srcDbName
        ));
    }

    public static Backup create(DBConnection dst, DBConnection src) throws SqliteException {
        return create(dst, "main", src, "main");
    }

    protected Backup(long handle) throws SqliteException {
        if (handle == 0) {
            throw new SqliteException("Native handle is NULL");
        }
        this.handle = handle;
    }

    @Override
    public void close() throws SqliteException {
        if (isValid()) {
            sqlite3_backup_finish(handle);
            handle = 0;
        }
    }

    public boolean step(int nPage) throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_backup_step(handle, nPage);
    }

    public int remaining() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_backup_remaining(handle);
    }

    public int getPageCount() throws SqliteException {
        DBHelper.checkValidable(this);
        return sqlite3_backup_pagecount(handle);
    }

    @Override
    public boolean isValid() {
        return handle != 0;
    }

    private static native long sqlite3_backup_init(long dst, String dstName, long src, String srcName) throws SqliteException;

    private static native boolean sqlite3_backup_step(long handle, int nPage) throws SqliteException;

    private static native void sqlite3_backup_finish(long handle) throws SqliteException;

    private static native int sqlite3_backup_remaining(long handle) throws SqliteException;

    private static native int sqlite3_backup_pagecount(long handle) throws SqliteException;
}
