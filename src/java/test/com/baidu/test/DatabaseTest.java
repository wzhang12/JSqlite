package com.baidu.test;

import com.baidu.javalite.DBConnection;
import com.baidu.javalite.Database;
import org.junit.Assert;
import org.junit.Test;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-28
 */
public class DatabaseTest {

    @Test
    public void testOpenClose() throws Throwable {
        Database database = new Database("resource/test/testOpenClose.dbt");
        DBConnection conn = database.open();
        Assert.assertTrue(conn.isValid());
        conn.close();
        Assert.assertTrue(!conn.isValid());
    }

}
