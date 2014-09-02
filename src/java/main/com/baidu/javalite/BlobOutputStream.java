package com.baidu.javalite;

import java.io.IOException;
import java.io.OutputStream;

/**
 * Created by clark on 14-9-1.
 */
public class BlobOutputStream extends OutputStream {
    private static final int DEFAULT_BUFFER_SIZE = 8192;
    private Blob blob;

    private int offset;
    private int count;
    private int nativeOffset;
    private byte[] buffer;

    private final int TOTAL_SIZE;

    protected BlobOutputStream(Blob blob) throws SqliteException {
        this.blob = blob;

        this.offset = 0;
        this.count = 0;
        nativeOffset = 0;
        TOTAL_SIZE = blob.size();   // Blob 中可以存储的最大字节数
        buffer = new byte[DEFAULT_BUFFER_SIZE < TOTAL_SIZE ? DEFAULT_BUFFER_SIZE : TOTAL_SIZE];
    }

    @Override
    public void write(int b) throws IOException {
        if (count > TOTAL_SIZE) {
            throw new SqliteException("Index out of Blob bounds, size: " + TOTAL_SIZE);
        }

        buffer[offset++] = (byte) b;
        count++;
        if (offset == buffer.length) {
            blob.write(buffer, 0, offset, nativeOffset);
            nativeOffset += offset;
            offset = 0;
        }
    }

    @Override
    public void flush() throws IOException {
        if (offset > 0) {
            blob.write(buffer, 0, offset, nativeOffset);
            nativeOffset += offset;
            offset = 0;
        }
        super.flush();
    }

    @Override
    public void close() throws IOException {
        flush();
        super.close();
    }
}
