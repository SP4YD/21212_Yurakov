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

//        System.out.println("[0] = " + bitSet.get(0));
//        System.out.println("[1] = " + bitSet.get(1));

        return buf;
    }

    public static Message FromByteBuffer(ByteBuffer buffer, int length) {
        byte[] buf = new byte[length - 1];
        buffer.get(buf);
        BitField bitField = new BitField(BitSet.valueOf(buf));

//        System.out.println("Устанавливаем битполе: " + Arrays.toString(bitField.bitSet.toByteArray()));
//        System.out.println("[0] = " + bitField.bitSet.get(0));
//        System.out.println("[1] = " + bitField.bitSet.get(1));

        return bitField;
    }

    public BitSet getBitSet() {
        return bitSet;
    }
}
