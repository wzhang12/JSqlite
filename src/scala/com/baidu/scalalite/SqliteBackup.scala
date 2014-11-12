package com.baidu.scalalite

import com.baidu.javalite.Backup

/**
 * Created by clark on 14-11-12.
 */
class SqliteBackup private(val backup: Backup) {
  def doBackup(): Unit = {
    try {
      do {
        backup.step(5)
      } while (backup.remaining() > 0)
    }
    finally {
      backup.close()
    }
  }

  @inline def step(nPage: Int) = backup.step(nPage)

  @inline def remaining = backup.remaining()

  @inline def getPageCount = backup.getPageCount

  @inline def close() = backup.close()
}

object SqliteBackup {
  def apply(dst: Connection, src: Connection) = new SqliteBackup(Backup.create(dst.conn, src.conn))

  def apply(dstConn: Connection, dstName: String, srcConn: Connection, srcName: String) =
    new SqliteBackup(Backup.create(dstConn.conn, dstName, srcConn.conn, srcName))
}
