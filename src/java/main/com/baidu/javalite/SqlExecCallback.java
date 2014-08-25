package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public interface SqlExecCallback {

    int callback(int ncols, String[] values, String[] headers);

}
