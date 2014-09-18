package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-9-19
 */
public interface Authorizer {

    int xAuth(DBConnection conn, int action, String s1, String s2, String s3, String s4) throws SqliteException;

}
