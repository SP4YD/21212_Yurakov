package ru.nsu.yurakov.Torrent.Sender;

import ru.nsu.yurakov.Torrent.Message.Message;
import ru.nsu.yurakov.Torrent.Peer.Peer;

public class Sender implements Runnable {

        private Message message;
        private Peer peer;

        @Override
        public void run() {
            Message.SendMessage(message, peer.getChannel());
        }

        public Sender (Message message, Peer peer) {
            this.peer = peer;
            this.message = message;
        }
}
