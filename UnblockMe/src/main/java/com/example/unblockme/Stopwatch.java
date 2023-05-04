package com.example.unblockme;

public class Stopwatch {
    private long startTime = 0;
    private boolean running;

    private String oldTime;

    public void start() {
        running = true;
        startTime = System.currentTimeMillis();
    }

    public String getTime() {
        if (running) {
            long milliseconds = System.currentTimeMillis() - startTime;
            long seconds = (milliseconds / 1000);
            long minutes = seconds / 60;
            seconds = seconds % 60;
            milliseconds = milliseconds % 1000;
            oldTime = String.format("%02d:%02d:%03d", minutes, seconds, milliseconds);
        }

        return oldTime;
    }

    public String stop() {
        String time = getTime();
        running = false;
        return time;
    }

    @Override
    public String toString() {
        return getTime();
    }

    public void reset() {
        startTime = System.currentTimeMillis();
    }

    public boolean isRunning() {
        return running;
    }
}
