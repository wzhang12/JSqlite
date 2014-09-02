package com.baidu.javalite;

import java.io.IOException;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class SqliteException extends IOException {
    private int errorCode = -255;     // 自定义错误

    public SqliteException() {
    }

    public SqliteException(String message) {
        super(message);
    }

    public SqliteException(String message, Throwable cause) {
        super(message, cause);
    }

    public SqliteException(Throwable cause) {
        super(cause);
    }

    public SqliteException(int errorCode) {
        super("Error code: " + errorCode);
        this.errorCode = errorCode;
    }

    public SqliteException(String message, int errorCode) {
        super(message.length() == 0 ? "Error code: " + errorCode : message + " [Error code: " + errorCode + "]");
        this.errorCode = errorCode;
    }

    public SqliteException(String message, Throwable cause, int errorCode) {
        super(message.length() == 0 ? "Error code: " + errorCode : message + " [Error code: " + errorCode + "]",
                cause);
        this.errorCode = errorCode;
    }

    public SqliteException(Throwable cause, int errorCode) {
        super("Error code: " + errorCode, cause);
        this.errorCode = errorCode;
    }

    public int getErrorCode() {
        return errorCode;
    }

}
