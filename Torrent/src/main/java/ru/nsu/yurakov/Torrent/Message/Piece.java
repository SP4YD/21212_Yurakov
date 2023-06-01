package ru.nsu.yurakov.Torrent.Message;

import java.nio.ByteBuffer;

public class Piece extends Message {
    private int index;
    private byte[] data;

    Piece (int index, byte[] data) {
        this.index = index;
        this.data = data;
        this.len = 4 + 1 + data.length;
        this.type = 7;
    }

    @Override
    public ByteBuffer ToByteBuffer() {
        ByteBuffer buf = ByteBuffer.allocate(len + 4);
        buf.putInt(len);
        buf.put(getType());
        buf.putInt(index);
        buf.put(data);

        return buf;
    }

    public static Message FromByteBuffer(ByteBuffer buffer, int length) {
        int index = buffer.getInt();
        byte[] data = new byte[length - 1 - 4];
        buffer.get(data);

        Piece piece = new Piece(index, data);

        return piece;
    }

    public int getIndex() {
        return index;
    }

    public byte[] getData() {
        return data;
    }
}
