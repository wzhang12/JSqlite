package com.baidu.javalite;

import java.io.IOException;
import java.io.InputStream;

/**
 * Created by clark on 14-9-1.
 */
public class BlobInputStream extends InputStream {
    private Blob blob;

    protected BlobInputStream(Blob blob) {
        this.blob = blob;
    }

    @Override
    public int read() throws IOException {
        return 0;
    }

}
