package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public class SqliteException extends Exception {
    private int errorCode;

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

    public SqliteException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }

    public SqliteException(int errorCode) {
        this.errorCode = errorCode;
    }

    public SqliteException(String message, int errorCode) {
        super(message);
        this.errorCode = errorCode;
    }

    public SqliteException(String message, Throwable cause, int errorCode) {
        super(message, cause);
        this.errorCode = errorCode;
    }

    public SqliteException(Throwable cause, int errorCode) {
        super(cause);
        this.errorCode = errorCode;
    }

    public SqliteException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace, int errorCode) {
        super(message, cause, enableSuppression, writableStackTrace);
        this.errorCode = errorCode;
    }

    public int getErrorCode() {
        return errorCode;
    }

    public void setErrorCode(int errorCode) {
        this.errorCode = errorCode;
    }
}
