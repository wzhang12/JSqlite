package com.baidu.test;

import com.baidu.javalite.DBConnection;
import com.baidu.javalite.Database;
import com.baidu.javalite.Flags;
import com.baidu.javalite.SqliteException;
import org.junit.Assert;
import org.junit.Test;

import java.io.File;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-28
 */
public class DatabaseTest {

    @Test
    public void testOpenClose() throws Throwable {
        File file = new File("resource/test/testOpenClose.dbt");
        Database database = new Database(file);

        // 测试 open() 方法
        DBConnection conn = database.open();
        Assert.assertTrue("open() 方法返回的 DBConnection 对象不可用！", conn.isValid());
        Assert.assertTrue("open() 方法调用以后没有创建数据库文件！", file.isFile());
        conn.close();
        Assert.assertTrue("close() 方法调用后 DBConnection 对象仍然可用！", !conn.isValid());

        // 删除文件
        file.delete();
        Assert.assertTrue("删除测试数据库文件失败！", !file.exists());

        // 如果数据库文件不存在，那么使用 SQLITE_OPEN_READONLY 打开数据库会抛出异常
        try {
            database.open(Flags.SQLITE_OPEN_READONLY);
            Assert.assertTrue(false);
        } catch (SqliteException e) {
            Assert.assertTrue("如果数据库文件不存在，那么使用 SQLITE_OPEN_READONLY 打开数据库会抛出异常!", true);
        }

        // 如果数据库不存在，那么使用 SQLITE_OPEN_READWRITE 打开数据库会抛出异常
        try {
            database.open(Flags.SQLITE_OPEN_READWRITE);
            Assert.assertTrue(false);
        } catch (SqliteException e) {
            Assert.assertTrue("如果数据库不存在，那么使用 SQLITE_OPEN_READWRITE 打开数据库会抛出异常!", true);
        }


    }

}
