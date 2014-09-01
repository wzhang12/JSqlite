package com.baidu.javalite;

import java.io.IOException;
import java.io.OutputStream;

/**
 * Created by clark on 14-9-1.
 */
public class BlobOutputStream extends OutputStream {
    private Blob blob;

    protected BlobOutputStream(Blob blob) {
        this.blob = blob;
    }

    @Override
    public void write(int b) throws IOException {

    }
}
