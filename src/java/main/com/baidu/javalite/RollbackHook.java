package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-28
 */
public interface RollbackHook {

    public void callback(DBConnection conn);

}
