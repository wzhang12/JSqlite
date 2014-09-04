package com.baidu.javalite;

/**
 * Created by clark on 14-9-4.
 */
public interface AggregateFunction extends ScalarFunction {
    void xStep(Context context, Value[] values);

    void xFinal(Context context);
}
