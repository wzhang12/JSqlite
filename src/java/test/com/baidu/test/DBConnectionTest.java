package com.baidu.test;

import com.baidu.javalite.DBConnection;
import com.baidu.javalite.Database;
import com.baidu.javalite.SqlExecCallback;
import com.baidu.javalite.SqliteException;
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
    private int count;

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

    @Test
    public void testSqlExecCallback() {
        try {
            // 可以执行多条 sql 语句，这里只执行了一句
            conn.exec("SELECT count(*) FROM sqlite_master where type='table' AND name='test_tb';"
                    , new SqlExecCallback() {
                @Override
                public int callback(int ncols, String[] values, String[] headers) {
                    Assert.assertTrue("测试 SqlExecCallback 成功！", true);
                    return 1; // cause SqliteException，返回非 0 值终止多条 sql 的执行
                }
            });
            Assert.assertTrue("测试 SqlExecCallback 失败！", false);
        } catch (SqliteException e) {
            System.out.println(e);
            Assert.assertTrue("测试 SqlExecCallback 失败！", true);
        }
    }

    @Test
    public void testMultiSqlExec() {
        count = 0;
        String sql = "SELECT count(*) FROM sqlite_master where type='table' AND name='test_tb';" +
                "DROP TABLE IF EXISTS test_tb;" +
                "CREATE TABLE test_tb (id INTEGER PRIMARY KEY, name TEXT);" +
                "SELECT count(*) FROM sqlite_master where type='table' AND name='test_tb';";
        try {
            conn.exec(sql, new SqlExecCallback() {
                @Override
                public int callback(int ncols, String[] values, String[] headers) {
                    count++;
                    return 0;
                }
            });

            Assert.assertTrue("Create Table 语句不执行回调！", count == 2);
        } catch (SqliteException e) {
            Assert.assertTrue("测试执行多条 sql 语句失败！" +
                    "\n" + e, false);
        }
    }
}
