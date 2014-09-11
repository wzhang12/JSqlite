package com.baidu.javalite;

/**
 * Created by clark on 14-9-11.
 */
public interface ProfileListener {

    void profile(DBConnection conn, String msg, long time);

}
