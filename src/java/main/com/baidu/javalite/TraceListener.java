package com.baidu.javalite;

/**
 * Created by clark on 14-9-11.
 */
public interface TraceListener {

    void trace(DBConnection conn, String msg) throws SqliteException;

}
