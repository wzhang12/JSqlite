package com.baidu.scalalite

import java.io.File

import com.baidu.javalite.Database

/**
 * Created by clark on 14-11-12.
 */
class SqliteDatabase private(file: File) {
  private[this] val db = new Database(file)

  private def this(path: String) = this(new File(path))

  def open(op: (Connection) => Unit): Unit = {
    if (op != null) {
      val conn = db.open()
      try op(new Connection(conn)) finally closeQuietly(conn)
    }
  }

  def open(flags: Int)(op: (Connection) => Unit): Unit = {
    if (op != null) {
      val conn = db.open(flags)
      try op(new Connection(conn)) finally closeQuietly(conn)
    }
  }
}

object SqliteDatabase {
  def apply(file: File) = new SqliteDatabase(file)

  def apply(path: String) = new SqliteDatabase(path)

  @inline def isCompiledThreadsafe = Database.isCompiledThreadsafe

  @inline def threadmodeConfig(ops: Int) = Database.threadmodeConfig(ops)

  @inline def initializeLibrary = Database.initializeLibrary()

  @inline def shutdownLibrary = Database.shutdownLibrary()

  @inline def getLibraryVersion = Database.getLibraryVersion

  @inline def getLibrarySourceId = Database.getLibrarySourceId

  @inline def getLibraryVersionNumber = Database.getLibraryVersionNumber

  @inline def isSqlComplete(sql: String) = Database.isSqlComplete(sql)
}
