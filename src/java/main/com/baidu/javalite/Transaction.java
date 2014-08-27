package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-27
 */
public class Transaction {
    private DBConnection connection;
    private boolean inTransaction;

    protected Transaction(DBConnection connection) {
        if (connection == null) {
            throw new NullPointerException();
        }
        this.connection = connection;
    }

    public void begin() throws SqliteException {
        connection.exec("begin;");
        inTransaction = true;
    }

    public void commit() throws SqliteException {
        connection.exec("commit;");
        inTransaction = false;
    }

    public void rollback() throws SqliteException {
        connection.exec("rollback;");
        inTransaction = false;
    }

    public boolean inTransaction() {
        return inTransaction;
    }

    public void savepoint(String point) throws SqliteException {
        connection.exec(String.format("savepoint %s;", point));
    }

    public void rollbackTo(String point) throws SqliteException {
        connection.exec(String.format("rollback to %s;", point));
    }
}
