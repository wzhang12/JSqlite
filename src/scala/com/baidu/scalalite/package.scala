package com.baidu

import com.baidu.javalite.Closeable

/**
 * Created by clark on 14-11-12.
 */
package object scalalite {
  def closeQuietly(closeable: Closeable): Unit = {
    if (closeable != null) {
      try closeable.close() catch {
        case _ =>
      }
    }
  }

  val SQLITE_OPEN_READONLY = 0x00000001
  val SQLITE_OPEN_READWRITE = 0x00000002
  val SQLITE_OPEN_CREATE = 0x00000004
  val SQLITE_OPEN_DELETEONCLOSE = 0x00000008
  val SQLITE_OPEN_EXCLUSIVE = 0x00000010
  val SQLITE_OPEN_AUTOPROXY = 0x00000020
  val SQLITE_OPEN_URI = 0x00000040
  val SQLITE_OPEN_MEMORY = 0x00000080
  val SQLITE_OPEN_MAIN_DB = 0x00000100
  val SQLITE_OPEN_TEMP_DB = 0x00000200
  val SQLITE_OPEN_TRANSIENT_DB = 0x00000400
  val SQLITE_OPEN_MAIN_JOURNAL = 0x00000800
  val SQLITE_OPEN_TEMP_JOURNAL = 0x00001000
  val SQLITE_OPEN_SUBJOURNAL = 0x00002000
  val SQLITE_OPEN_MASTER_JOURNAL = 0x00004000
  val SQLITE_OPEN_NOMUTEX = 0x00008000
  val SQLITE_OPEN_FULLMUTEX = 0x00010000
  val SQLITE_OPEN_SHAREDCACHE = 0x00020000
  val SQLITE_OPEN_PRIVATECACHE = 0x00040000
  val SQLITE_OPEN_WAL = 0x00080000

  val SQLITE_INTEGER = 1
  val SQLITE_FLOAT = 2
  val SQLITE_TEXT = 3
  val SQLITE_BLOB = 4
  val SQLITE_NULL = 5

  val SQLITE_CONFIG_SINGLETHREAD = 1
  val SQLITE_CONFIG_MULTITHREAD = 2
  val SQLITE_CONFIG_SERIALIZED = 3

  val SQLITE_LIMIT_LENGTH = 0
  val SQLITE_LIMIT_SQL_LENGTH = 1
  val SQLITE_LIMIT_COLUMN = 2
  val SQLITE_LIMIT_EXPR_DEPTH = 3
  val SQLITE_LIMIT_COMPOUND_SELECT = 4
  val SQLITE_LIMIT_VDBE_OP = 5
  val SQLITE_LIMIT_FUNCTION_ARG = 6
  val SQLITE_LIMIT_ATTACHED = 7
  val SQLITE_LIMIT_LIKE_PATTERN_LENGTH = 8
  val SQLITE_LIMIT_VARIABLE_NUMBER = 9
  val SQLITE_LIMIT_TRIGGER_DEPTH = 10

  val SQLITE_COPY = 0
  val SQLITE_CREATE_INDEX = 1
  val SQLITE_CREATE_TABLE = 2
  val SQLITE_CREATE_TEMP_INDEX = 3
  val SQLITE_CREATE_TEMP_TABLE = 4
  val SQLITE_CREATE_TEMP_TRIGGER = 5
  val SQLITE_CREATE_TEMP_VIEW = 6
  val SQLITE_CREATE_TRIGGER = 7
  val SQLITE_CREATE_VIEW = 8
  val SQLITE_DELETE = 9
  val SQLITE_DROP_INDEX = 10
  val SQLITE_DROP_TABLE = 11
  val SQLITE_DROP_TEMP_INDEX = 12
  val SQLITE_DROP_TEMP_TABLE = 13
  val SQLITE_DROP_TEMP_TRIGGER = 14
  val SQLITE_DROP_TEMP_VIEW = 15
  val SQLITE_DROP_TRIGGER = 16
  val SQLITE_DROP_VIEW = 17
  val SQLITE_INSERT = 18
  val SQLITE_PRAGMA = 19
  val SQLITE_READ = 20
  val SQLITE_SELECT = 21
  val SQLITE_TRANSACTION = 22
  val SQLITE_UPDATE = 23
  val SQLITE_ATTACH = 24
  val SQLITE_DETACH = 25
  val SQLITE_ALTER_TABLE = 26
  val SQLITE_REINDEX = 27
  val SQLITE_ANALYZE = 28
  val SQLITE_CREATE_VTABLE = 29
  val SQLITE_DROP_VTABLE = 30
  val SQLITE_FUNCTION = 31
  val SQLITE_SAVEPOINT = 32
  val SQLITE_RECURSIVE = 33
}
