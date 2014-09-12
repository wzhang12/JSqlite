package com.baidu.test;

import com.baidu.javalite.*;
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

    @Test
    public void testCreateFunction() {
        try {
            conn.createFunction("test", 0, null, new ScalarFunction() {
                @Override
                public void xFunc(Context context, Value[] values) {
                    System.out.println("len of Value[]is " + values.length);
                    for (Value v : values) {
                        try {
                            System.out.println(v.getType());
                        } catch (SqliteException e) {
                            e.printStackTrace();
                        }
                    }

                    try {
                        context.setResultText("Hello World!!!");
                    } catch (SqliteException e) {
                        e.printStackTrace();
                    }
                }
            });

            conn.exec("select test(*), * from sqlite_master;", new SqlExecCallback() {
                @Override
                public int callback(int ncols, String[] values, String[] headers) {
                    for (String h : headers) {
                        System.out.println(h);
                    }
                    System.out.println();

                    for (String v : values) {
                        System.out.println(v);
                    }
                    System.out.println();
                    return 0;
                }
            });
        } catch (SqliteException e) {
            Assert.assertTrue("测试创建函数失败!", false);
        }
    }

    @Test
    public void testLimit() {
        try {
            System.out.println("BLOB or TEXT MAX length is " + conn.limit(Flags.SQLITE_LIMIT_LENGTH, -1) + " bytes");;
            System.out.println("SELECT MAX column is " + conn.limit(Flags.SQLITE_LIMIT_COLUMN, -1));
            System.out.println("SQL MAX length is " + conn.limit(Flags.SQLITE_LIMIT_SQL_LENGTH, -1) + " bytes");
        } catch (SqliteException e) {
            Assert.assertTrue("测试 limit 函数失败!", false);
        }
    }

    @Test
    public void testRollbackHook() {
        try {
            conn.setRollbackHook(new RollbackHook() {
                @Override
                public void callback(DBConnection conn) {
                    System.out.println(conn);
                    System.out.println("success to rollback!");
                }
            });

            Transaction transaction = conn.newTransaction();
            transaction.begin();
            conn.exec("INSERT OR REPLACE INTO test_tb (id, name) values (10, 'Clark');");
            transaction.rollback();
        } catch (SqliteException e) {
            Assert.assertTrue("测试 setRollbackHook 函数失败!", false);
        }
    }

    @Test
    public void testCommitHook() {
        try {
            conn.setCommitHook(new CommitHook() {
                @Override
                public int callback(DBConnection conn) {
                    System.out.println(conn);
                    System.out.println("success to commit!");
                    return 0;
                }
            });

            Transaction transaction = conn.newTransaction();
            transaction.begin();
            conn.exec("INSERT OR REPLACE INTO test_tb (id, name) values (10, 'Clark');");
            transaction.commit();
        } catch (SqliteException e) {
            Assert.assertTrue("测试 setRollbackHook 函数失败!", false);
        }
    }
}
