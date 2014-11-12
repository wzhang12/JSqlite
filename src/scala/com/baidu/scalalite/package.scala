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
}
