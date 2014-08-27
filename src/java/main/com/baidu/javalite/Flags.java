package com.baidu.javalite;

/**
 * Created with IntelliJ IDEA.
 * Date: 14-8-25
 */
public final class Flags {
    /**
     * <pre>
     *     #define SQLITE_OPEN_READONLY         0x00000001  Ok for sqlite3_open_v2()
     *     #define SQLITE_OPEN_READWRITE        0x00000002  Ok for sqlite3_open_v2()
     *     #define SQLITE_OPEN_CREATE           0x00000004  Ok for sqlite3_open_v2()
     *     #define SQLITE_OPEN_DELETEONCLOSE    0x00000008  VFS only
     *     #define SQLITE_OPEN_EXCLUSIVE        0x00000010  VFS only
     *     #define SQLITE_OPEN_AUTOPROXY        0x00000020  VFS only
     *     #define SQLITE_OPEN_URI              0x00000040  Ok for sqlite3_open_v2()
     *     #define SQLITE_OPEN_MEMORY           0x00000080  Ok for sqlite3_open_v2()
     *     #define SQLITE_OPEN_MAIN_DB          0x00000100  VFS only
     *     #define SQLITE_OPEN_TEMP_DB          0x00000200  VFS only
     *     #define SQLITE_OPEN_TRANSIENT_DB     0x00000400  VFS only
     *     #define SQLITE_OPEN_MAIN_JOURNAL     0x00000800  VFS only
     *     #define SQLITE_OPEN_TEMP_JOURNAL     0x00001000  VFS only
     *     #define SQLITE_OPEN_SUBJOURNAL       0x00002000  VFS only
     *     #define SQLITE_OPEN_MASTER_JOURNAL   0x00004000  VFS only
     *     #define SQLITE_OPEN_NOMUTEX          0x00008000  Ok for sqlite3_open_v2()
     *     #define SQLITE_OPEN_FULLMUTEX        0x00010000  Ok for sqlite3_open_v2()
     *     #define SQLITE_OPEN_SHAREDCACHE      0x00020000  Ok for sqlite3_open_v2()
     *     #define SQLITE_OPEN_PRIVATECACHE     0x00040000  Ok for sqlite3_open_v2()
     *     #define SQLITE_OPEN_WAL              0x00080000  VFS only
     * </pre>
     */
    public static final int SQLITE_OPEN_READONLY = 0x00000001;
    public static final int SQLITE_OPEN_READWRITE = 0x00000002;
    public static final int SQLITE_OPEN_CREATE = 0x00000004;

    public static final int SQLITE_OPEN_DELETEONCLOSE = 0x00000008;
    public static final int SQLITE_OPEN_EXCLUSIVE = 0x00000010;
    public static final int SQLITE_OPEN_AUTOPROXY = 0x00000020;

    public static final int SQLITE_OPEN_URI = 0x00000040;
    public static final int SQLITE_OPEN_MEMORY = 0x00000080;

    public static final int SQLITE_OPEN_MAIN_DB = 0x00000100;
    public static final int SQLITE_OPEN_TEMP_DB = 0x00000200;
    public static final int SQLITE_OPEN_TRANSIENT_DB = 0x00000400;
    public static final int SQLITE_OPEN_MAIN_JOURNAL = 0x00000800;
    public static final int SQLITE_OPEN_TEMP_JOURNAL = 0x00001000;
    public static final int SQLITE_OPEN_SUBJOURNAL = 0x00002000;
    public static final int SQLITE_OPEN_MASTER_JOURNAL = 0x00004000;

    public static final int SQLITE_OPEN_NOMUTEX = 0x00008000;
    public static final int SQLITE_OPEN_FULLMUTEX = 0x00010000;
    public static final int SQLITE_OPEN_SHAREDCACHE = 0x00020000;
    public static final int SQLITE_OPEN_PRIVATECACHE = 0x00040000;

    public static final int SQLITE_OPEN_WAL = 0x00080000;

    /**
     * CAPI3REF: Fundamental Datatypes
     * KEYWORDS: SQLITE_TEXT
     * <p/>
     * (Every value in SQLite has one of five fundamental datatypes:
     * <ul>
     * <li> 64-bit signed integer
     * <li> 64-bit IEEE floating point number
     * <li> string
     * <li> BLOB
     * <li> NULL
     * </ul>)
     * <p/>
     * These constants are codes for each of those types.
     * <p/>
     * Note that the SQLITE_TEXT constant was also used in SQLite version 2
     * for a completely different meaning.  Software that links against both
     * SQLite version 2 and SQLite version 3 should use SQLITE3_TEXT, not
     * SQLITE_TEXT.
     */
    public static final int SQLITE_INTEGER = 1;
    public static final int SQLITE_FLOAT = 2;
    public static final int SQLITE_TEXT = 3;
    public static final int SQLITE_BLOB = 4;
    public static final int SQLITE_NULL = 5;

    /**
     * {@link com.baidu.javalite.Database#threadmodeConfig(int)} 的参数选项
     */
    public static final int SQLITE_CONFIG_SINGLETHREAD = 1;
    public static final int SQLITE_CONFIG_MULTITHREAD = 2;
    public static final int SQLITE_CONFIG_SERIALIZED = 3;
}
