package ru.nsu.yurakov.Torrent.Message;

import ru.nsu.yurakov.Torrent.ParserTorrent.TorrentInfo;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Random;

public class HandShake {
    public static void Send(SocketChannel socket, TorrentInfo info) throws IOException {
        ByteArrayOutputStream out = new ByteArrayOutputStream();

        out.write((byte) 19);
        out.write("BitTorrent protocol".getBytes());
        for (int i = 0; i < 8; ++i) {
            out.write((byte) 0x00);
        }
        out.write(info.hashInfo);
        out.write(GeneratorID());

        socket.write(ByteBuffer.allocate(68).put(out.toByteArray()).flip());
    }

    public static byte[] Read(SocketChannel channel) throws IOException {
        ByteBuffer buffer = ByteBuffer.allocate(68);
        while (buffer.hasRemaining()) {
            channel.read(buffer);
        }

        return buffer.array();
    }

    public static int VerificationClient(SocketChannel channel, TorrentInfo info) throws IOException {
        byte[] handshake = Read(channel);

        if (handshake.length != 68) {
            return -1;
        }

        int lenHandshake = handshake[0];
        if (lenHandshake != 19) {
            return -1;
        }

        String str = ConvertByteToString(handshake, 1, 20);

        if (!str.equals("BitTorrent protocol")) {
            return -1;
        }

        for (int i = 28; i < 48; ++i) {
            if (info.hashInfo[i - 28] != handshake[i]) {
                return -1;
            }
        }

        return 0;
    }

    public static String VerificationServer(SocketChannel channel) throws IOException {
        byte[] handshake = Read(channel);

        if (handshake.length != 68) {
            return null;
        }

        int lenHandshake = handshake[0];
        if (lenHandshake != 19) {
            return null;
        }

        String str = ConvertByteToString(handshake, 1, 20);

        if (!str.equals("BitTorrent protocol")) {
            return null;
        }

        byte[] hashInfo = Arrays.copyOfRange(handshake, 28, 48);

        return FindTorrentFile(hashInfo);
    }

    private static byte[] GeneratorID() throws IOException {
        try (ByteArrayOutputStream out = new ByteArrayOutputStream()) {
            String ID = "SP4YD-";
            out.write(ID.getBytes());
            Random random = new Random();
            for (int i = 0 ; i < 14; ++i) {
                out.write ((byte) random.nextInt(256));
            }

            return out.toByteArray();
        }
    }

    public static String ConvertByteToString(byte[] arr, int begin, int end) {
        String str = "";

        for (int i = begin; i < end; ++i) {
            str += (char) arr[i];
        }

        return str;
    }

    private static String FindTorrentFile(byte[] handshakeHash) {
        String path = "./TorrentFiles";
        File folder = new File(path);

        if (folder.exists() && folder.isDirectory()) {
            File[] files = folder.listFiles();

            if (files != null) {
                for (File file : files) {
                    if (file.isFile()) {
                        if (CheckingHashInfo(file, handshakeHash)) {
                            return file.getName();
                        }
                    }
                }
            }
        }

        return null;
    }

    private static boolean CheckingHashInfo(File file, byte[] handshakeHash) {
        byte[] hashInfo;
        try (FileInputStream fileInputStream = new FileInputStream(file)) {
            byte[] allBytesTorrent = fileInputStream.readAllBytes();
            int infoStart = (new String(allBytesTorrent).indexOf("4:info")) + 6;

            MessageDigest md = MessageDigest.getInstance("SHA-1");
            byte[] infoData = Arrays.copyOfRange(allBytesTorrent, infoStart, allBytesTorrent.length - 1);
            hashInfo = md.digest(infoData);

            for (int i = 0; i < 20; i++) {
                if (hashInfo[i] != handshakeHash[i]) {
                    return false;
                }
            }
        } catch (IOException | NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }

        return true;
    }
}
