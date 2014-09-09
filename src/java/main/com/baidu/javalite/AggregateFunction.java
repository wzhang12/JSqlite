package com.baidu.javalite;

/**
 * Created by clark on 14-9-4.
 */
public interface AggregateFunction extends ScalarFunction {
    void xStep(Context context, Value[] values) throws SqliteException;

    void xFinal(Context context) throws SqliteException;
}
