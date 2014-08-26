package com.baidu.test;

import com.baidu.javalite.*;

import java.io.File;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class DatabaseTester {

    public static void main(String[] args) throws SqliteException {
        Database database = new Database(new File("a.db"));
        DBConnection conn = database.open();
//        conn.exec("CREATE TABLE crashs (id INTEGER primary key, name TEXT)");
//        conn.exec("INSERT INTO crashs (id, name) values (1, 'Clark')");

        // 测试 exec
//        System.out.println("测试 exec");
//        conn.exec("select * from crashs;", new SqlExecCallback() {
//            @Override
//            public int callback(int ncols, String[] values, String[] headers) {
//                for (int i = 0; i < ncols; ++i) {
//                    System.out.print(headers[i]);
//                    System.out.print("\t");
//                }
//                System.out.println();
//
//                for (int i = 0; i < ncols; ++i) {
//                    System.out.print(values[i]);
//                    System.out.print("\t");
//                }
//                System.out.println();
//                return 0;
//            }
//        });

        // 测试 get_table
//        System.out.println("\n测试 get_table");
//        TableResult result = conn.getTable("select * from crashs;");
//        for (TableResult.Cell cell : result) {
//            System.out.println(cell);
//        }
//
//        int rowCount = result.getRowNums();
//        int colCount = result.getColNums();
//        for (int i = 0; i < rowCount; ++i) {
//            for (int j = 0; j < colCount; ++j) {
//                System.out.print(result.getCellData(i, j));
//                System.out.print(j == colCount - 1 ? "\n" : "\t");
//            }
//        }

        // 测试 prepare
//        System.out.println("\n测试 prepare");
//        PrepareStmt stmt = conn.prepare("select * from crashs;");
//        while (stmt.step()) {
//            final int count = stmt.getColumnCount(); // 列数
//            for (int i = 0; i < count; ++i) {
//                System.out.print(stmt.getColumnName(i));
//                System.out.print(i == count - 1 ? "\n" : "\t");
//            }
//
//            for (int i = 0; i < count; ++i) {
//                System.out.print(stmt.getColumnText(i));
//                System.out.print(i == count - 1 ? "\n" : "\t");
//            }
//        }
//        stmt.close();

//        PrepareStmt stmt = conn.prepare("SELECT * FROM sqlite_master;");
//        while (stmt.step()) {
//            final int count = stmt.getColumnCount(); // 列数
//            for (int i = 0; i < count; ++i) {
//                System.out.print(stmt.getColumnName(i));
//                System.out.print(i == count - 1 ? "\n" : "\t");
//            }
//
//            for (int i = 0; i < count; ++i) {
//                System.out.print(stmt.getColumnText(i));
//                System.out.print(i == count - 1 ? "\n" : "\t");
//            }
//        }

        makesureTableExist(conn, "a");

        conn.safeClose();
    }

    private static boolean makesureTableExist(DBConnection connection, String tbname) throws SqliteException {
        PrepareStmt stmt = connection.prepare("SELECT count(*) FROM sqlite_master WHERE type='table' AND name=?;");
        stmt.bindText(1, tbname);
//        boolean rc = stmt.step();

        while (stmt.step()) {
            final int count = stmt.getColumnCount(); // 列数
            for (int i = 0; i < count; ++i) {
                System.out.print(stmt.getColumnName(i));
                System.out.print(i == count - 1 ? "\n" : "\t");
            }

            for (int i = 0; i < count; ++i) {
                System.out.print(stmt.getColumnText(i));
                System.out.print(i == count - 1 ? "\n" : "\t");
            }
        }

        stmt.close();
//        return rc;
        return true;
    }
}
