package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-9-18
 */
public interface UpdateHook {

    void hook(DBConnection conn, int action, String dbname, String tbname, long rowid) throws SqliteException;

}
