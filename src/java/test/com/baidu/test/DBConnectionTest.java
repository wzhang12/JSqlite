package com.baidu.test;

import com.baidu.javalite.DBConnection;
import com.baidu.javalite.Database;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-28
 */
public class DBConnectionTest {
    private DBConnection conn;

    @Before
    public void setup() throws Throwable {
        conn = new Database("resource/test/testConn.dbt").open();
    }

    @After
    public void tearDown() throws Throwable {
        conn.close();
        conn = null;
    }

    @Test
    public void testIsValid() {
        Assert.assertTrue("isValid 方法测试失败！", conn.isValid());
    }
}
