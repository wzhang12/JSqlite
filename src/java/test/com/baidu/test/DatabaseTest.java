package com.baidu.test;

import com.baidu.javalite.*;
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
            conn = null;
            conn = database.open(Flags.SQLITE_OPEN_READONLY);
            Assert.assertTrue("如果数据库文件不存在，那么使用 SQLITE_OPEN_READONLY 打开数据库会抛出异常!", false);
        } catch (SqliteException e) {
            Assert.assertTrue(true);
        } finally {
            DBHelper.closeQuietly(conn);
        }

        // 如果数据库不存在，那么使用 SQLITE_OPEN_READWRITE 打开数据库会抛出异常
        try {
            conn = null;
            conn = database.open(Flags.SQLITE_OPEN_READWRITE);
            Assert.assertTrue("如果数据库不存在，那么使用 SQLITE_OPEN_READWRITE 打开数据库会抛出异常!", false);
        } catch (SqliteException e) {
            Assert.assertTrue(true);
        } finally {
            DBHelper.closeQuietly(conn);
        }
    }

    @Test
    public void testIsCompiledThreadsafe() {
        try {
            Database.isCompiledThreadsafe();
            Assert.assertTrue(true);
        } catch (Exception e) {
            Assert.assertTrue("isCompiledThreadsafe() 方法调用失败！", false);
        }
    }

    @Test
    public void testInitializeLibrary() {
        try {
            Database.initializeLibrary();
            Assert.assertTrue(true);
        } catch (SqliteException e) {
            Assert.assertTrue("initializeLibrary() 方法调用失败！", false);
        }
    }

    @Test
    public void testShutdownLibrary() {
        try {
            Database.shutdownLibrary();
            Assert.assertTrue(true);
        } catch (SqliteException e) {
            Assert.assertTrue("shutdownLibrary() 方法调用失败！", false);
        }
    }

    @Test
    public void testVersionApi() {
        try {
            Assert.assertTrue("getLibrarySourceId() 方法调用失败！", Database.getLibrarySourceId() != null);
            Assert.assertTrue("getLibraryVersion() 方法调用失败！", Database.getLibraryVersion() != null);
            Assert.assertTrue("getLibraryVersionNumber() 方法调用失败！", Database.getLibraryVersionNumber() != 0);
        } catch (Exception e) {
            Assert.assertTrue("getLibraryXXX() 方法调用失败！", false);
        }
    }
}
