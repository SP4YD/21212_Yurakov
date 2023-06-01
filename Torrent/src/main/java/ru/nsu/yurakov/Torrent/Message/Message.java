package ru.nsu.yurakov.Torrent.Message;

import ru.nsu.yurakov.Torrent.ParserTorrent.TorrentInfo;
import ru.nsu.yurakov.Torrent.Peer.Peer;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public abstract class Message {
    private static final String PATH_TO_READ = "./Files/"; //   "./src/main/resources/DistributedFiles/"
    private static final String PATH_TO_WRITE = "./Files/"; //"./src/main/resources/UploadedFiles/"
    int len;
    byte type;
    public abstract ByteBuffer ToByteBuffer();

    private static Message fromBytes(byte[] array) {
        ByteBuffer buffer = ByteBuffer.wrap(array);
        int len = buffer.getInt();
        byte type = buffer.get();

        if (type == 5) {
            return BitField.FromByteBuffer(buffer, len);
        }
        if (type == 6) {
            return Request.FromByteBuffer(buffer, len);
        }
        if (type == 7) {
            return Piece.FromByteBuffer(buffer, len);
        }

        return null;
    }

    public static void SendMessage(Message msg, SocketChannel channel) {
        ByteBuffer buf = msg.ToByteBuffer();
        buf.flip();
        //System.out.println("SendMessage - " + Arrays.toString(buf.array()));

        while (buf.hasRemaining()) {
            try {
                channel.write(buf);
            } catch (IOException e) {
                try {
                    channel.close();
                } catch (IOException ex) {
                    System.out.println("Socket close exception!");
                }

            }

        }
    }

    public static Message RecvMessage(SocketChannel channel) throws IOException {
        ByteBuffer lenBuf = ByteBuffer.allocate(4);
        while (lenBuf.hasRemaining()) {
            channel.read(lenBuf);
            //System.out.println("RecvMessage - " + Arrays.toString(lenBuf.array()));
        }
        lenBuf.flip();

        int lenMsg = lenBuf.getInt();

        ByteBuffer byteBuffer = ByteBuffer.allocate(lenMsg + 4);
        lenBuf.flip();
        byteBuffer.put(lenBuf);

        while(byteBuffer.hasRemaining()) {
            channel.read(byteBuffer);
        }

        return Message.fromBytes(byteBuffer.flip().array());
    }

    public static Message HandleMessage(Message msg, Peer peer) {
        byte Type = msg.type;

        if (Type == 5) {
            BitField bitField = (BitField) msg;
            peer.setBitSet(bitField.bitSet);
        }

        if (Type == 6) {
            Request req = (Request) msg;
            TorrentInfo info = peer.getInfo();
            File f = new File(PATH_TO_READ + info.nameFile);
            try (RandomAccessFile file = new RandomAccessFile(f, "rw")) {
                file.seek((long) req.index * info.sizePiece + req.offset);

                byte[] data = new byte[req.size];
                file.read(data);

                SendMessage(new Piece(req.index, data), peer.getChannel());
            } catch (IOException e) {
                System.err.println("HandleMessage: Error in file reader!");
            }
        }

        if (Type == 7) {
            Piece piece = (Piece) msg;
            TorrentInfo info = peer.getInfo();
            File file = new File(PATH_TO_WRITE + info.nameFile);
            if (file.isFile()) {
                try (RandomAccessFile fileRA = new RandomAccessFile(file, "rw")) {
                    fileRA.seek((long) piece.getIndex() * info.sizePiece);

                    if (PieceVerification(info, piece.getIndex(), piece.getData())) {
                        fileRA.write(piece.getData());
                    } else {
                        System.err.println("Problem with hash piece");
                    }


                } catch (IOException e) {
                    System.err.println("HandleMessage: Error in file reader! Error: " + e.getMessage());
                }
            } else {
                System.out.println("FILE IS NOT EXIST " + PATH_TO_WRITE + info.nameFile);
            }
        }

        return null;
    }

    private static boolean PieceVerification(TorrentInfo info, int pieceNumber, byte[] piece) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-1");
            byte[] realHash = md.digest(piece);

            for (int i = 0; i < 20; ++i) {
                if (realHash[i] != info.pieces[pieceNumber * 20 + i]) {
                    return false;
                }
            }
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }

        return true;
    }

    public byte getType() {
        return type;
    }
}