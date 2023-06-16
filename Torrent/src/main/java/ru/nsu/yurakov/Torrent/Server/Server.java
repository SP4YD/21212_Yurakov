package ru.nsu.yurakov.Torrent.Server;

import ru.nsu.yurakov.Torrent.Handler.Handler;
import ru.nsu.yurakov.Torrent.Message.*;
import ru.nsu.yurakov.Torrent.ParserTorrent.ParserTorrent;
import ru.nsu.yurakov.Torrent.ParserTorrent.TorrentInfo;
import ru.nsu.yurakov.Torrent.Peer.Peer;
import ru.nsu.yurakov.Torrent.PiecesManager.PiecesManager;
import ru.nsu.yurakov.Torrent.Sender.Sender;

import java.io.File;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static ru.nsu.yurakov.Torrent.Peer.Peer.Status.*;

public class Server {
    public Server (String args) throws IOException {
        Run(args);
    }

    public void Run(String port) {
        System.out.println("My port = (" + port + ")");
        CONNECTION_PORT = Integer.parseInt(port);

        try (ServerSocketChannel serverSocket = ServerSocketChannel.open()) {
            Selector selector = Selector.open();
            serverSocket.bind(new InetSocketAddress("localhost", CONNECTION_PORT));
            serverSocket.configureBlocking(false);
            serverSocket.register(selector, SelectionKey.OP_ACCEPT);

            Peers = new HashMap<>();

            while (true) {
                selector.select(50);
                Set<SelectionKey> selectedKeys = selector.selectedKeys();
                Iterator<SelectionKey> iterator = selectedKeys.iterator();

                while (iterator.hasNext()) {
                    SelectionKey key = iterator.next();
                    iterator.remove();

                    try {
                        if (key.isAcceptable()) {
                            SocketChannel client = serverSocket.accept();
                            client.configureBlocking(false);
                            client.register(selector, SelectionKey.OP_READ | SelectionKey.OP_WRITE);

                            Peer peer = new Peer(client, null);
                            peer.status = CONNECTION_IS_ESTABLISHED;
                            Peers.put(client, peer);
                        } else {
                            SocketChannel channel = (SocketChannel) key.channel();
                            if (!channel.isConnected()) {
                                channel.close();
                                key.cancel();
                                continue;
                            }
                            Peer peer = Peers.get(channel);

                            if (key.isReadable()) {
                                switch (peer.status) {
                                    case CONNECTION_IS_ESTABLISHED -> {
                                        TorrentFile = HandShake.VerificationServer(channel);
                                        if (TorrentFile != null) {
                                            ParserTorrent parser = new ParserTorrent();
                                            File torrent = new File(PATH_TO_TORRENTS + TorrentFile);
                                            if (!torrent.isFile()) {
                                                throw new IOException();
                                            }

                                            INFO = parser.getInfo(PATH_TO_TORRENTS + TorrentFile);
                                            peer = new Peer(channel, INFO);
                                            Peers.remove(channel);
                                            Peers.put(channel, peer);

                                            peer.status = HANDSHAKE_RECEIVED;
                                        } else {
                                            throw new IOException();
                                        }
                                    }

                                    case SENDING_FILE -> {
                                        Request req = (Request) Message.RecvMessage(channel);
                                        executor.submit(new Handler(req, Peers.get(channel)));
                                    }
                                }
                            }
                            if (key.isWritable()) {
                                switch (peer.status) {
                                    case HANDSHAKE_RECEIVED -> {
                                        HandShake.Send(channel, INFO);
                                        peer.status = SENT_HANDSHAKE;
                                    }

                                    case SENT_HANDSHAKE -> {
                                        PiecesManager piecesManager = new PiecesManager(INFO, new File(PATH_TO_FILES + INFO.nameFile));
                                        System.out.println("Server: I have "+ piecesManager.getWhatHave());
                                        BitField bitField = new BitField(piecesManager.getWhatHave());
                                        executor.submit(new Sender(bitField, Peers.get(channel)));

                                        peer.status = SENDING_FILE;
                                    }
                                }
                            }
                        }
                    } catch (IOException e) {
                        SocketChannel channel = (SocketChannel) key.channel();
                        System.out.println("Sever: The connection was interrupted with someone ");
                        channel.close();
                        key.cancel();
                    }
                }
            }
        } catch (Exception e) {
            System.err.println("Server: Died");
        }
    }

    private final ExecutorService executor = Executors.newFixedThreadPool(2);
    private int CONNECTION_PORT = 3333;
    private final String PATH_TO_TORRENTS = "./TorrentFiles/";
    private final String PATH_TO_FILES = "./Files/";
    private String TorrentFile;
    private TorrentInfo INFO;
    private Map<SocketChannel, Peer> Peers;
}

//String ClientIP = socket.getInetAddress().getHostAddress();
