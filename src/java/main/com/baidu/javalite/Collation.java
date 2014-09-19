package com.baidu.javalite;

/**
 * Created by clark on 14-9-19.
 */
public interface Collation {
    int xCompare(DBConnection conn, byte[] a, byte[] b) throws SqliteException;

    void xDestroy(DBConnection conn) throws SqliteException;
}
