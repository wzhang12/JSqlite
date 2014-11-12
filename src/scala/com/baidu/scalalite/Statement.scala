package com.baidu.scalalite

import com.baidu.javalite.PrepareStmt

/**
 * Created by clark on 14-11-12.
 */
class Statement protected[scalalite](protected[scalalite] val stmt: PrepareStmt) {
  @inline def getConnection = new Connection(stmt.getConnection)

  @inline def step() = stmt.step()

  @inline def reset() = stmt.reset()

  @inline def query(op: => Unit): Unit = {
    while (stmt.step()) {
      op
    }
  }

  @inline def commit(op: => Unit): Unit = {
    op
    stmt.step()
    stmt.reset()
    stmt.clearBinding()
  }

  @inline def getColumnCount = stmt.getColumnCount

  @inline def getColumnName(column: Int) = stmt.getColumnName(column)

  @inline def getColumnDatabaseName(column: Int) = stmt.getColumnDatabaseName(column)

  @inline def getColumnTableName(column: Int) = stmt.getColumnTableName(column)

  @inline def getColumnOriginName(column: Int) = stmt.getColumnOriginName(column)

  @inline def getColumnDecltype(column: Int) = stmt.getColumnDecltype(column)

  @inline def getDataCount = stmt.getDataCount

  @inline def getColumnBlob(column: Int) = stmt.getColumnBlob(column)

  @inline def getColumnDouble(column: Int) = stmt.getColumnDouble(column)

  @inline def getColumnInt(column: Int) = stmt.getColumnInt(column)

  @inline def getColumnInt64(column: Int) = stmt.getColumnInt64(column)

  @inline def getColumnText(column: Int) = stmt.getColumnText(column)

  @inline def getColumnType(column: Int) = stmt.getColumnType(column)

  @inline def bindBlob(column: Int, value: Array[Byte]) = stmt.bindBlob(column, value)

  @inline def bindBlob(name: String, value: Array[Byte]) = stmt.bindBlob(name, value)

  @inline def bindDouble(column: Int, value: Double) = stmt.bindDouble(column, value)

  @inline def bindDouble(name: String, value: Double) = stmt.bindDouble(name, value)

  @inline def bindInt(column: Int, value: Int) = stmt.bindInt(column, value)

  @inline def bindInt(name: String, value: Int) = stmt.bindInt(name, value)

  @inline def bindInt64(column: Int, value: Long) = stmt.bindInt64(column, value)

  @inline def bindInt64(name: String, value: Long) = stmt.bindInt64(name, value)

  @inline def bindNull(column: Int) = stmt.bindNull(column)

  @inline def bindNull(name: String) = stmt.bindNull(name)

  @inline def bindText(column: Int, value: String) = stmt.bindText(column, value)

  @inline def bindText(name: String, value: String) = stmt.bindText(name, value)

  @inline def bindZeroBlob(column: Int, size: Int) = stmt.bindZeroBlob(column, size)

  @inline def bindZeroBlob(name: String, size: Int) = stmt.bindZeroBlob(name, size)

  @inline def clearBinding() = stmt.clearBinding()

  @inline def getBindParameterIndex(name: String) = stmt.getBindParameterIndex(name)

  @inline def getBindParameterName(index: Int) = stmt.getBindParameterName(index)

  @inline def getBindParameterCount = stmt.getBindParameterCount

  @inline def isBusy = stmt.isBusy

  @inline def isReadOnly = stmt.isReadOnly

  @inline def getSql = stmt.getSql
}
