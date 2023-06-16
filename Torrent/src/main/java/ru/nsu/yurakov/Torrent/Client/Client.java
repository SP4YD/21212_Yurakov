package ru.nsu.yurakov.Torrent.Client;

import ru.nsu.yurakov.Torrent.ConnecterToChannels.ConnecterToChannels;
import ru.nsu.yurakov.Torrent.Handler.Handler;
import ru.nsu.yurakov.Torrent.Message.HandShake;
import ru.nsu.yurakov.Torrent.Message.Message;
import ru.nsu.yurakov.Torrent.Message.Piece;
import ru.nsu.yurakov.Torrent.Message.Request;
import ru.nsu.yurakov.Torrent.ParserTorrent.ParserTorrent;
import ru.nsu.yurakov.Torrent.ParserTorrent.TorrentInfo;
import ru.nsu.yurakov.Torrent.Peer.Peer;
import ru.nsu.yurakov.Torrent.PiecesManager.PiecesManager;
import ru.nsu.yurakov.Torrent.Sender.Sender;

import java.io.File;
import java.io.IOException;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static ru.nsu.yurakov.Torrent.Peer.Peer.Status.*;

public class Client {
    public Client () throws IOException {
        Run();
    }

    public void Run() throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter torrent file name: ");
        TorrentFile = scanner.nextLine();

        ParserTorrent parser = new ParserTorrent();
        File torrent = new File(PATH_TO_TORRENTS + TorrentFile);
        if (!torrent.isFile()) {
            System.out.println("Client: There is no such file (" + PATH_TO_TORRENTS + TorrentFile + ")");
            return;
        }

        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        INFO = parser.getInfo(PATH_TO_TORRENTS + TorrentFile);
        Peers = new HashMap<>();
        piecesManager = new PiecesManager(INFO, new File(PATH_TO_FILES + INFO.nameFile));

        Selector selector = Selector.open();

        ConnecterToChannels connecterToChannels = new ConnecterToChannels(new File("./ListIP.txt"));

        boolean isFileUploaded = false;

        while (!isFileUploaded) {
            connecterToChannels.UpdatingConnections(selector);
            selector.select(150);
            Set<SelectionKey> selectedKeys = selector.selectedKeys();
            Iterator<SelectionKey> iterator = selectedKeys.iterator();

            while (iterator.hasNext()) {
                SelectionKey key = iterator.next();
                iterator.remove();
                SocketChannel channel = (SocketChannel) key.channel();

                try {
                    if (key.isConnectable()) {
                        if (channel.finishConnect()) {
                            System.out.println("Connect to " + ((SocketChannel) key.channel()).getRemoteAddress() + " success");
                            key.interestOps(SelectionKey.OP_READ | SelectionKey.OP_WRITE);
                            Peers.put(channel, new Peer(channel, INFO));
                            Peers.get(channel).status = CONNECTION_IS_ESTABLISHED;
                        }
                    } else {
                        Peer peer = Peers.get(channel);

                        if (key.isReadable()) {
                            switch (peer.status) {
                                case SENT_HANDSHAKE -> {
                                    if (HandShake.VerificationClient(channel, INFO) == 0) {
                                        peer.status = WAITING_FOR_BITSET;
                                    }
                                }

                                case WAITING_FOR_BITSET -> {
                                    Message message = Message.RecvMessage(channel);
                                    if (message.getType() == 5) {
                                        Message.HandleMessage(message, Peers.get(channel));

                                        peer.status = RECEIVING_FILE;
                                    } else {
                                        throw new IOException();
                                    }
                                }

                                case RECEIVING_FILE -> {
                                    Message message = Message.RecvMessage(channel);

                                    if (message.getType() == 7) {
                                        Piece piece = (Piece) message;

                                        if (!piecesManager.getWhatHave().get(piece.getIndex())) {
                                            executor.submit(new Handler(message, peer));
                                            piecesManager.setPieceReceived(piece.getIndex());

                                            System.out.println("Loaded: " + (int) ((piecesManager.alreadyDownloaded() / (double) piecesManager.getCountPieces()) * 100) + "%");
                                        }

                                        peer.ReducingCountRequests();
                                    } else {
                                        throw new IOException();
                                    }
                                }
                            }
                        }

                        if (key.isWritable()) {
                            switch (peer.status) {
                                case CONNECTION_IS_ESTABLISHED -> {
                                    HandShake.Send(channel, INFO);
                                    peer.status = SENT_HANDSHAKE;
                                }

                                case RECEIVING_FILE -> {
                                    int indexNeedPiece = piecesManager.getIndexPiece(peer);

                                    if (indexNeedPiece >= 0) {
                                        if (peer.PossibleMakeRequest()) {
                                            long sizePiece = piecesManager.getSizePiece(indexNeedPiece);
                                            Request request = new Request(indexNeedPiece, 0, sizePiece);

                                            peer.IncreasingCountRequests();
                                            executor.submit(new Sender(request, peer));
                                            try {
                                                Thread.sleep(200);
                                            } catch (InterruptedException e) {
                                                throw new RuntimeException(e);
                                            }
                                        }
                                    } else if (piecesManager.isFileUploaded()) {
                                        isFileUploaded = true;
                                        Peers.remove(peer.getChannel());
                                        channel.close();
                                        key.cancel();
                                    }
                                }
                            }
                        }
                    }
                } catch (IOException e) {
                    if (key.isValid()) {
                        System.out.println("Client: The connection to the server " + channel.socket().getRemoteSocketAddress() + " was lost");
                    }

                    connecterToChannels.DeleteConnection(channel);
                    channel.close();
                    key.cancel();
                }
            }
        }

        System.out.println("Client: File uploaded successfully");
        System.out.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }

    private final ExecutorService executor = Executors.newFixedThreadPool(2);
    private static final String PATH_TO_TORRENTS = "./TorrentFiles/";
    private static final String PATH_TO_FILES = "./Files/";
    private static String TorrentFile;
    private static TorrentInfo INFO = null;
    private static PiecesManager piecesManager;
    private static Map<SocketChannel, Peer> Peers;
}