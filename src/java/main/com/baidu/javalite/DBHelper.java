package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-26
 */
public final class DBHelper {

    public static void closeQuietly(Closeable... closeables) {
        if (closeables == null) {
            return;
        }

        for (Closeable c : closeables) {
            if (c == null) continue;
            try {
                c.close();
            } catch (SqliteException e) {
            }
        }
    }

    public static void checkValidable(Validable validable) throws SqliteException {
        if (validable == null || !validable.isValid()) {
            throw new SqliteException("Native handle has been invalid");
        }
    }

}
