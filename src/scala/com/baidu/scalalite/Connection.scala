package com.baidu.scalalite

import com.baidu.javalite.{Context, Authorizer, ProfileListener, TraceListener, Collation, AggregateFunction, ScalarFunction, Value, UpdateHook, RollbackHook, BusyHandler, CommitHook, DBConnection, SqlExecCallback}

/**
 * Created by clark on 14-11-12.
 */
class Connection protected[scalalite](protected[scalalite] val conn: DBConnection) {
  @inline def exec(sql: String)(cb: (Int, Array[String], Array[String]) => Int) =
    conn.exec(sql,
      if (cb == null) null
      else new SqlExecCallback {
        override def callback(ncols: Int, values: Array[String], headers: Array[String]): Int =
          cb(ncols, values, headers)
      })

  @inline def exec(sql: String) = conn.exec(sql)

  @inline def transaction(op: (Connection) => Unit): Unit = {
    val transaction = conn.newTransaction()
    transaction.begin()
    try {
      op(this)
      transaction.commit()
    } catch {
      case _ => transaction.rollback()
    }
  }

  @inline def getRowChanges = conn.getRowChanges

  @inline def getTotalRowChanges = conn.getTotalRowChanges

  @inline def getLastInsertRowid = conn.getLastInsertRowid

  @inline def getTable(sql: String) = conn.getTable(sql)

  @inline def prepare(sql: String)(op: (Statement) => Unit): Unit = {
    if (op != null) {
      val stmt = conn.prepare(sql)
      try op(new Statement(stmt)) finally closeQuietly(stmt)
    }
  }

  @inline def setBusyHandler(handler: (Int) => Int) =
    conn.setBusyHandler(
      if (handler == null) null
      else new BusyHandler {
        override def handle(times: Int): Int = handler(times)
      })

  @inline def setBusyTimeout(ms: Int) = conn.setBusyTimeout(ms)

  @inline def setCommitHook(hook: (Connection) => Int) =
    conn.setCommitHook(
      if (hook == null) null
      else new CommitHook {
        override def callback(dbConn: DBConnection): Int = hook(new Connection(dbConn))
      })

  @inline def setRollbackHook(hook: (Connection) => Unit) =
    conn.setRollbackHook(
      if (hook == null) null
      else new RollbackHook {
        override def callback(conn: DBConnection): Unit = hook(new Connection(conn))
      })

  @inline def setUpdateHook(hk: (Connection, Int, String, String, Long) => Unit) =
    conn.setUpdateHook(
      if (hk == null) null
      else new UpdateHook {
        override def hook(conn: DBConnection, action: Int, dbname: String, tbname: String, rowid: Long): Unit =
          hk(new Connection(conn), action, dbname, tbname, rowid)
      })

  @inline def getReadWriteBlob(dbName: String, tbName: String, colName: String, rowId: Long) =
    conn.getReadWriteBlob(dbName, tbName, colName, rowId)

  @inline def getReadOnlyBlob(dbName: String, tbName: String, colName: String, rowId: Long) =
    conn.getReadOnlyBlob(dbName, tbName, colName, rowId)

  @inline def createFunction(funcName: String, nArgs: Int, app: Any)(func: (SqliteContext, Array[Value]) => Unit) =
    conn.createFunction(funcName, nArgs, app,
      if (func == null) null
      else new ScalarFunction {
        override def xFunc(context: Context, values: Array[Value]): Unit = func(new SqliteContext(context), values)
      })

  @inline def createAggregate(funcName: String, nArgs: Int, app: Any)
                             (func: (SqliteContext, Array[Value]) => Unit)
                             (step: (SqliteContext, Array[Value]) => Unit)
                             (finl: (SqliteContext) => Unit) =
    conn.createFunction(funcName, nArgs, app, new AggregateFunction {
      override def xFinal(context: Context): Unit = if (finl != null) finl(new SqliteContext(context))

      override def xStep(context: Context, values: Array[Value]): Unit = if (step != null) step(new SqliteContext(context), values)

      override def xFunc(context: Context, values: Array[Value]): Unit = if (func != null) func(new SqliteContext(context), values)
    })

  @inline def createCollation(name: String)
                             (cmp: (Connection, Array[Byte], Array[Byte]) => Int)
                             (dsy: (Connection) => Unit) =
    conn.createCollation(name, new Collation {
      override def xCompare(conn: DBConnection, a: Array[Byte], b: Array[Byte]): Int =
        if (cmp != null) cmp(new Connection(conn), a, b) else 0

      override def xDestroy(conn: DBConnection): Unit = if (dsy != null) dsy(new Connection(conn))
    })

  @inline def releaseDbMemory = conn.releaseDbMemory()

  @inline def limit(id: Int, newVal: Int) = conn.limit(id, newVal)

  @inline def nextStmt(old: Statement) = new Statement(conn.nextStmt(old.stmt))

  @inline def setOnTraceListener(lsn: (Connection, String) => Unit) =
    conn.setOnTraceListener(
      if (lsn == null) null
      else new TraceListener {
        override def trace(conn: DBConnection, msg: String): Unit = lsn(new Connection(conn), msg)
      })

  @inline def setOnProfileListener(pf: (Connection, String, Long) => Unit) =
    conn.setOnProfileListener(
      if (pf == null) null
      else new ProfileListener {
        override def profile(conn: DBConnection, msg: String, time: Long): Unit = pf(new Connection(conn), msg, time)
      })

  @inline def setAuthorizer(auth: (Connection, Int, String, String, String, String) => Int) =
    conn.setAuthorizer(
      if (auth == null) null
      else new Authorizer {
        override def xAuth(conn: DBConnection, action: Int, s1: String, s2: String, s3: String, s4: String): Int =
          auth(new Connection(conn), action, s1, s2, s3, s4)
      })
}
