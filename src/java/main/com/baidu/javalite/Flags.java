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

    /**
     * <pre>
     *      #define SQLITE_LIMIT_LENGTH                    0
     *          The maximum size of any string or BLOB or table row, in bytes.
     *      #define SQLITE_LIMIT_SQL_LENGTH                1
     *          The maximum length of an SQL statement, in bytes.
     *      #define SQLITE_LIMIT_COLUMN                    2
     *          The maximum number of columns in a table definition or in the result set of a SELECT or the maximum number of columns in an index or in an ORDER BY or GROUP BY clause.
     *      #define SQLITE_LIMIT_EXPR_DEPTH                3
     *          The maximum depth of the parse tree on any expression.
     *      #define SQLITE_LIMIT_COMPOUND_SELECT           4
     *          The maximum number of terms in a compound SELECT statement.
     *      #define SQLITE_LIMIT_VDBE_OP                   5
     *          The maximum number of instructions in a virtual machine program used to implement an SQL statement. This limit is not currently enforced, though that might be added in some future release of SQLite.
     *      #define SQLITE_LIMIT_FUNCTION_ARG              6
     *          The maximum number of arguments on a function.
     *      #define SQLITE_LIMIT_ATTACHED                  7
     *          The maximum number of attached databases.
     *      #define SQLITE_LIMIT_LIKE_PATTERN_LENGTH       8
     *          The maximum length of the pattern argument to the LIKE or GLOB operators.
     *      #define SQLITE_LIMIT_VARIABLE_NUMBER           9
     *          The maximum index number of any parameter in an SQL statement.
     *      #define SQLITE_LIMIT_TRIGGER_DEPTH            10
     *          The maximum depth of recursion for triggers.
     * </pre>
     */
    public static final int SQLITE_LIMIT_LENGTH = 0;
    public static final int SQLITE_LIMIT_SQL_LENGTH = 1;
    public static final int SQLITE_LIMIT_COLUMN = 2;
    public static final int SQLITE_LIMIT_EXPR_DEPTH = 3;
    public static final int SQLITE_LIMIT_COMPOUND_SELECT = 4;
    public static final int SQLITE_LIMIT_VDBE_OP = 5;
    public static final int SQLITE_LIMIT_FUNCTION_ARG = 6;
    public static final int SQLITE_LIMIT_ATTACHED = 7;
    public static final int SQLITE_LIMIT_LIKE_PATTERN_LENGTH = 8;
    public static final int SQLITE_LIMIT_VARIABLE_NUMBER = 9;
    public static final int SQLITE_LIMIT_TRIGGER_DEPTH = 10;

    /**
     * <pre>
     *      #define SQLITE_CREATE_INDEX          1
            #define SQLITE_CREATE_TABLE          2
            #define SQLITE_CREATE_TEMP_INDEX     3
            #define SQLITE_CREATE_TEMP_TABLE     4
            #define SQLITE_CREATE_TEMP_TRIGGER   5
            #define SQLITE_CREATE_TEMP_VIEW      6
            #define SQLITE_CREATE_TRIGGER        7
            #define SQLITE_CREATE_VIEW           8
            #define SQLITE_DELETE                9
            #define SQLITE_DROP_INDEX           10
            #define SQLITE_DROP_TABLE           11
            #define SQLITE_DROP_TEMP_INDEX      12
            #define SQLITE_DROP_TEMP_TABLE      13
            #define SQLITE_DROP_TEMP_TRIGGER    14
            #define SQLITE_DROP_TEMP_VIEW       15
            #define SQLITE_DROP_TRIGGER         16
            #define SQLITE_DROP_VIEW            17
            #define SQLITE_INSERT               18
            #define SQLITE_PRAGMA               19
            #define SQLITE_READ                 20
            #define SQLITE_SELECT               21
            #define SQLITE_TRANSACTION          22
            #define SQLITE_UPDATE               23
            #define SQLITE_ATTACH               24
            #define SQLITE_DETACH               25
            #define SQLITE_ALTER_TABLE          26
            #define SQLITE_REINDEX              27
            #define SQLITE_ANALYZE              28
            #define SQLITE_CREATE_VTABLE        29
            #define SQLITE_DROP_VTABLE          30
            #define SQLITE_FUNCTION             31
            #define SQLITE_SAVEPOINT            32
            #define SQLITE_COPY                  0
            #define SQLITE_RECURSIVE            33
     * </pre>
     */
    public static final int SQLITE_COPY = 0;
    public static final int SQLITE_CREATE_INDEX = 1;
    public static final int SQLITE_CREATE_TABLE = 2;
    public static final int SQLITE_CREATE_TEMP_INDEX = 3;
    public static final int SQLITE_CREATE_TEMP_TABLE = 4;
    public static final int SQLITE_CREATE_TEMP_TRIGGER = 5;
    public static final int SQLITE_CREATE_TEMP_VIEW = 6;
    public static final int SQLITE_CREATE_TRIGGER = 7;
    public static final int SQLITE_CREATE_VIEW = 8;
    public static final int SQLITE_DELETE = 9;
    public static final int SQLITE_DROP_INDEX = 10;
    public static final int SQLITE_DROP_TABLE = 11;
    public static final int SQLITE_DROP_TEMP_INDEX = 12;
    public static final int SQLITE_DROP_TEMP_TABLE = 13;
    public static final int SQLITE_DROP_TEMP_TRIGGER = 14;
    public static final int SQLITE_DROP_TEMP_VIEW = 15;
    public static final int SQLITE_DROP_TRIGGER = 16;
    public static final int SQLITE_DROP_VIEW = 17;
    public static final int SQLITE_INSERT = 18;
    public static final int SQLITE_PRAGMA = 19;
    public static final int SQLITE_READ = 20;
    public static final int SQLITE_SELECT = 21;
    public static final int SQLITE_TRANSACTION = 22;
    public static final int SQLITE_UPDATE = 23;
    public static final int SQLITE_ATTACH = 24;
    public static final int SQLITE_DETACH = 25;
    public static final int SQLITE_ALTER_TABLE = 26;
    public static final int SQLITE_REINDEX = 27;
    public static final int SQLITE_ANALYZE = 28;
    public static final int SQLITE_CREATE_VTABLE = 29;
    public static final int SQLITE_DROP_VTABLE = 30;
    public static final int SQLITE_FUNCTION = 31;
    public static final int SQLITE_SAVEPOINT = 32;
    public static final int SQLITE_RECURSIVE = 33;
}
