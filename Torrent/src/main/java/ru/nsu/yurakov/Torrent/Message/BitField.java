package ru.nsu.yurakov.Torrent.Message;

import java.nio.ByteBuffer;
import java.util.BitSet;

public class BitField extends Message {
    BitSet bitSet;

    public BitField(BitSet  bitSet) {
        this.bitSet = bitSet;
        this.type = 5;
        this.len =  1 + (bitSet.length() + 7) / 8;
    }

    @Override
    public ByteBuffer ToByteBuffer() {
        ByteBuffer buf = ByteBuffer.allocate(len + 4);
        buf.putInt(len);
        buf.put(getType());
        buf.put(bitSet.toByteArray());

        return buf;
    }

    public static Message FromByteBuffer(ByteBuffer buffer, int length) {
        byte[] buf = new byte[length - 1];
        buffer.get(buf);

        return new BitField(BitSet.valueOf(buf));
    }

    public BitSet getBitSet() {
        return bitSet;
    }
}
