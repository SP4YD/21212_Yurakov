package com.example.unblockme;

public class Block {
    private int x;
    private int y;
    private final int lenX;
    private final int lenY;

    public Block(int x, int y, int lenX, int lenY) {
        this.x = x;
        this.y = y;
        this.lenX = lenX;
        this.lenY = lenY;
    }

    public void SetX(int x) {
        this.x = x;
    }

    public void SetY(int y) {
        this.y = y;
    }

    public int GetX() {
        return x;
    }

    public int GetY() {
        return y;
    }

    public int GetLenX() {
        return lenX;
    }

    public int GetLenY() {
        return lenY;
    }

    public boolean Contains(int x, int y) {
        return (this.x <= x) && (x < this.x + lenX) && (this.y == y) || (this.y <= y) && (y < this.y + lenY) && (this.x == x);
    }
}
