package ru.nsu.yurakov.Torrent.Peer;

import ru.nsu.yurakov.Torrent.ParserTorrent.TorrentInfo;

import java.nio.channels.SocketChannel;
import java.util.BitSet;

import static ru.nsu.yurakov.Torrent.Peer.Peer.Status.*;

public class Peer {
    private SocketChannel channel;
    private TorrentInfo info;
    private BitSet bitSet;
    private int CountRequests;
    public Status status;

    public enum Status {
        CONNECTION_IS_ESTABLISHED,
        SENT_HANDSHAKE,
        HANDSHAKE_RECEIVED,
        WAITING_FOR_BITSET,
        SENDING_FILE,
        RECEIVING_FILE
    }

    public Peer (SocketChannel channel, TorrentInfo info) {
        this.channel = channel;
        this.info = info;
        CountRequests = 0;
        status = CONNECTION_IS_ESTABLISHED;
    }

    public TorrentInfo getInfo() {
        return info;
    }

    public SocketChannel getChannel() { return channel; }

    public BitSet getBitSet() {
        return bitSet;
    }

    public int getCountRequests() { return CountRequests; }

    public void setBitSet(BitSet bitSet) {
        this.bitSet = bitSet;
    }

    public void IncreasingCountRequests() {
        if (CountRequests < 3) {
            ++CountRequests;
        }
    }

    public void ReducingCountRequests() {
        if (CountRequests > 0) {
            --CountRequests;
        }
    }

    public boolean PossibleMakeRequest() {
        return CountRequests < 3;
    }
}
