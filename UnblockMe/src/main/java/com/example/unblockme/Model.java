package com.example.unblockme;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.Scanner;

public class Model {
    public void LoadLevel (InputStream level, String nameLevel) {
        this.nameLevel = nameLevel;
        blocks = new ArrayList<Block>();

        try (Scanner scanner = new Scanner(level)){
            if (scanner.hasNextLine()) {
                scanner.nextLine();
            }

            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] data = line.split(" ");
                for (String block : data) {
                    int height = 1;
                    int width = 1;
                    int x;
                    int y;

                    if (block.length() == 4) {
                        if (block.charAt(0) == 'v') {
                            height = Character.digit(block.charAt(3), 10);
                        }
                        else {
                            width = Character.digit(block.charAt(3), 10);
                        }

                        x = Character.digit(block.charAt(1), 10);
                        y = Character.digit(block.charAt(2), 10);
                        getBlocks().add(new Block(x, y, width, height));
                    }
                    else {
                        x = Character.digit(block.charAt(1), 10);
                        y = (BOARD_SIZE - 1)/2;
                        width = 2;
                        mainBlock = new Block(x, y, width, height);
                        getBlocks().add(getMainBlock());
                    }
                }
            }
        }
    }

    public Block BlockSelection(int x, int y) {
        for (Block block : getBlocks()) {
            if (block.Contains(x, y)) {
                selectedBlock = block;
                return getSelectedBlock();
            }
        }
        return null;
    }

    public boolean Intersects(double x, double y, int lenX, int lenY, Block block, int BLOCK_SIZE) {
        double X1 = x;
        double X2 = x + (double) lenX / 2;
        double X3 = x + lenX;
        double otherX1 = block.GetX() * BLOCK_SIZE;
        double otherX2 = otherX1 + (double) block.GetLenX() * BLOCK_SIZE / 2;
        double otherX3 = otherX1 + block.GetLenX() * BLOCK_SIZE;

        double Y1 = y;
        double Y2 = y + (double) lenY / 2;
        double Y3 = y + lenY;
        double otherY1 = block.GetY() * BLOCK_SIZE;
        double otherY2 = otherY1 + (double) block.GetLenY() * BLOCK_SIZE / 2;
        double otherY3 = otherY1 + block.GetLenY() * BLOCK_SIZE;

        if ((otherY1 < Y2 && Y2 < otherY3) && ((otherX1 < X1 && X1 < otherX3) || (X1 <= otherX1 && otherX3 <= X3) ||  (otherX1 < X3 && X3 < otherX3))) {
            return true;
        }

        if ((Y1 < otherY2 && otherY2 < Y3) && ((X1 < otherX1 && otherX1 < X3) || (otherX1 <= X1 && X3 <= otherX3) || (X1 < otherX3 && otherX3 < X3))) {
            return true;
        }

        if ((X1 < otherX2 && otherX2 < X3) && ((Y1 < otherY3 && otherY3 < Y3) || (otherY1 <= Y1 && Y3 <= otherY3) || (Y1 < otherY1 && otherY1 < Y3))) {
            return true;
        }

        if ((otherX1 < X2 && X2 < otherX3) && ((otherY1 < Y3 && Y3 < otherY3) || (Y1 <= otherY1 && otherY3 <= Y3) ||(otherY1 < Y1 && Y1 < otherY3))) {
            return true;
        }

        return false;
    }

    public boolean MainBlockIsOut() {
        return ((getMainBlock().GetX() + getMainBlock().GetLenX()) >= BOARD_SIZE);
    }

    public void ZeroingSelectedBlock() {
        selectedBlock = null;
    }

    public String getNameLevel() {
        return nameLevel;
    }

    public ArrayList<Block> getBlocks() {
        return blocks;
    }

    public Block getSelectedBlock() {
        return selectedBlock;
    }

    public Block getMainBlock() {
        return mainBlock;
    }

    public final int BOARD_SIZE = 6;
    private Block mainBlock = null;
    private Block selectedBlock = null;
    private ArrayList<Block> blocks = null;
    private String nameLevel = null;
}
