package ru.nsu.yurakov.Torrent.Handler;

import ru.nsu.yurakov.Torrent.Message.Message;
import ru.nsu.yurakov.Torrent.Peer.Peer;

public class Handler implements Runnable {

    private Message message;
    private Peer peer;

    @Override
    public void run() {
        Message.HandleMessage(message, peer);
    }

    public Handler (Message message, Peer peer) {
        this.peer = peer;
        this.message = message;
    }
}
