package com.baidu.javalite;

import java.io.IOException;
import java.io.InputStream;

/**
 * Created by clark on 14-9-1.
 */
public class BlobInputStream extends InputStream {
    private static final int DEFAULT_BUFFER_SIZE = 8192;
    private Blob blob;

    private int offset;
    private int offsetMax;
    private int nativeOffset;
    private int totalReads;
    private byte[] buffer;

    private final int TOTAL_SIZE;

    protected BlobInputStream(Blob blob) throws SqliteException {
        this.blob = blob;

        this.offset = 0;
        this.offsetMax = 0;
        nativeOffset = 0;
        totalReads = 0;
        TOTAL_SIZE = blob.size();   // Blob 中可以存储的最大字节数
        buffer = new byte[DEFAULT_BUFFER_SIZE < TOTAL_SIZE ? DEFAULT_BUFFER_SIZE : TOTAL_SIZE];
    }

    @Override
    public int read() throws IOException {
        if (offset == offsetMax || offset == 0) {
            if (nativeOffset == TOTAL_SIZE) {
                return -1;
            }

            final int buflen = buffer.length;
            if (nativeOffset + buflen <= TOTAL_SIZE) {
                offsetMax = buflen;
            } else {
                offsetMax = TOTAL_SIZE - nativeOffset;
            }
            blob.read(buffer, 0, offsetMax, nativeOffset);
            nativeOffset += offsetMax;
            offset = 0;         // 重读 buffer 的第一个
        }

        totalReads++;
        return buffer[offset++];
    }

    @Override
    public int available() throws IOException {
        return TOTAL_SIZE - totalReads;
    }
}
