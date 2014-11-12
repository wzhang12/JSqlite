package com.baidu.scalalite

import com.baidu.javalite.{Value, Context}

/**
 * Created by clark on 14-11-12.
 */
class SqliteContext protected[scalalite](private[this] val context: Context) {
  @inline def getUserData = context.getUserData

  @inline def getConnection = new Connection(context.getConnection)

  @inline def setAggregateContext(value: AnyRef) = context.setAggregateContext(value)

  @inline def getAggregateContext = context.getAggregateContext

  @inline def setResultDouble(result: Double) = context.setResultDouble(result)

  @inline def setResultInt(result: Int) = context.setResultInt(result)

  @inline def setResultInt64(result: Long) = context.setResultInt64(result)

  @inline def setResultNull() = context.setResultNull()

  @inline def setResultText(result: String) = context.setResultText(result)

  @inline def setResultBlob(result: Array[Byte]) = context.setResultBlob(result)

  @inline def setResultZeroBlob(size: Int) = context.setResultZeroBlob(size)

  @inline def setResultValue(value: Value) = context.setResultValue(value)

  @inline def setResultError(msg: String, code: Int) = context.setResultError(msg, code)

  @inline def setResultErrorTooBig() = context.setResultErrorTooBig()

  @inline def setResultErrorNoMem() = context.setResultErrorNoMem()

  @inline def setResultErrorCode(code: Int) = context.setResultErrorCode(code)
}
