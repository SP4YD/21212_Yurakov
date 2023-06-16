package ru.nsu.yurakov.Torrent.Message;

import java.nio.ByteBuffer;

public class Request extends Message {
    int index;
    int offset;
    int size;

    public Request(int index, int offset, long size) {
        this.index = index;
        this.offset = offset;
        this.size = (int) size;
        this.len = 1 + 4 + 4 + 4;
        this.type = 6;
    }

    @Override
    public ByteBuffer ToByteBuffer() {
        ByteBuffer buf = ByteBuffer.allocate(len + 4);
        buf.putInt(len);
        buf.put(getType());
        buf.putInt(index);
        buf.putInt(offset);
        buf.putInt(size);

        return buf;
    }

    public static Message FromByteBuffer(ByteBuffer buffer, int length) {
        int index = buffer.getInt();
        int offset = buffer.getInt();
        int size = buffer.getInt();
        Request req = new Request(index, offset, size);
        req.len = length;

        return req;
    }

    public int getIndex() {
        return index;
    }
}
