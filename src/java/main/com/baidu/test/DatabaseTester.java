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
        conn.exec("select * from crashs;", new SqlExecCallback() {
            @Override
            public int callback(int ncols, String[] values, String[] headers) {
                for (int i = 0; i < ncols; ++i) {
                    System.out.print(headers[i]);
                    System.out.print("\t");
                }
                System.out.println();

                for (int i = 0; i < ncols; ++i) {
                    System.out.print(values[i]);
                    System.out.print("\t");
                }
                System.out.println();
                return 0;
            }
        });

        TableResult result = conn.getTable("select * from crashs;");
        for (TableResult.Cell cell : result) {
            System.out.println(cell);
        }

        int rowCount = result.getRowNums();
        int colCount = result.getColNums();
        for (int i = 0; i < rowCount; ++i) {
            for (int j = 0; j < colCount; ++j) {
                System.out.print(result.getCellData(i, j));
                System.out.print(j == colCount - 1 ? "\n" : "\t");
            }
        }
        conn.close();
    }
}
