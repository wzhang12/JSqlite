package com.baidu.test;

import com.baidu.javalite.DBConnection;
import com.baidu.javalite.Database;
import com.baidu.javalite.SqliteException;

import java.io.File;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class DatabaseTester {

    public static void main(String[] args) throws SqliteException {
        Database database = new Database(new File("a.db"));
        DBConnection conn = database.open();
        conn.exec("CREATE TABLE crashs (id INTEGER primary key, name TEXT)");
        conn.exec("INSERT INTO crashs (id, name) values (1, 'Clark')");
        conn.close();
    }
}
