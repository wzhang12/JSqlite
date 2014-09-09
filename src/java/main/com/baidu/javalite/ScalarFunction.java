package com.baidu.javalite;

/**
 * Created by clark on 14-9-4.
 */
public interface ScalarFunction {
    void xFunc(Context context, Value[] values) throws SqliteException;
}
