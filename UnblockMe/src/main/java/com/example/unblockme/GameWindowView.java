package com.example.unblockme;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.TextAlignment;
import javafx.stage.Stage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class GameWindowView extends Application {
    public GameWindowView(String NameLevel, Model model) {
        nameLevel = NameLevel;
        UnblockMe = model;
        BOARD_SIZE = UnblockMe.BOARD_SIZE;
        BORDER_FIELD = BLOCK_SIZE * BOARD_SIZE;
    }

    @Override
    public void start(Stage stage) throws Exception {
        stageNow = stage;
        CreateWindow(stageNow);
    }

    private void CreateWindow(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(LevelSelectionView.class.getResource("gameWindow.fxml"));

        Scene scene = new Scene(fxmlLoader.load(), BLOCK_SIZE * BOARD_SIZE + BLOCK_SIZE * 2, BLOCK_SIZE * BOARD_SIZE + 30);
        stage.setScene(scene);
        stage.setTitle(nameLevel.toUpperCase());
        stage.show();

        canvas = (Canvas)fxmlLoader.getNamespace().get("canvas");
        Painter = getCanvas().getGraphicsContext2D();
    }

    public void updateScene(ArrayList<Block> blocks, Block mainBlock, double XSelectedBlock, double YSelectedBlock) {
        Painter.setFill(Color.rgb(80,80,96));
        Painter.fillRect(0, 0, BLOCK_SIZE * BOARD_SIZE, BLOCK_SIZE * BOARD_SIZE);
        for (Block block : blocks) {
            Image needCar = null;
            if (block.equals(mainBlock)) {
                needCar = carR;
            } else {
                if (block.GetLenX() > block.GetLenY()) {
                    if (block.GetLenX() == 3) {
                        needCar = car3h;
                    } else if (block.GetLenX() == 2) {
                        needCar = car2h;
                    }
                } else {
                    if (block.GetLenY() == 3) {
                        needCar = car3v;
                    } else if (block.GetLenY() == 2) {
                        needCar = car2v;
                    }
                }
            }

            double x = block.GetX();
            double y = block.GetY();
            int lenX = block.GetLenX();
            int lenY = block.GetLenY();
            if (block.equals(UnblockMe.getSelectedBlock())) {
                x = XSelectedBlock;
                y = YSelectedBlock;
            }
            Painter.drawImage(needCar, x * BLOCK_SIZE, y * BLOCK_SIZE, lenX * BLOCK_SIZE, lenY * BLOCK_SIZE);
        }
    }

    public void drawTime(String time) {
        Painter.clearRect(BLOCK_SIZE * BOARD_SIZE, (double) (BLOCK_SIZE * BOARD_SIZE) / 3, BLOCK_SIZE * 2, (double) (BLOCK_SIZE * BOARD_SIZE) / 3);
        Painter.setFill(Color.BLACK);
        Painter.setFont(Font.font("Arial", (double) BLOCK_SIZE /5));
        Painter.setTextAlign(TextAlignment.CENTER);
        Painter.fillText(time, BLOCK_SIZE * BOARD_SIZE + BLOCK_SIZE, (double) (BLOCK_SIZE * BOARD_SIZE) / 2);
    }

    public void drawNumOfSteps(int countSteps) {
        Painter.clearRect(BLOCK_SIZE * BOARD_SIZE, 0, BLOCK_SIZE * 2, (double) (BLOCK_SIZE * BOARD_SIZE) / 3);
        Painter.setFill(Color.BLACK);
        Painter.setFont(Font.font("Arial", (double) BLOCK_SIZE / 5));
        Painter.setTextAlign(TextAlignment.CENTER);
        Painter.fillText("Steps: " + countSteps, BLOCK_SIZE * BOARD_SIZE + BLOCK_SIZE, (double) (BLOCK_SIZE * BOARD_SIZE) / 4);
    }

    public String drawLeaderBoard(File leaderBoard) {
        Scanner scanner = null;
        try {
            scanner = new Scanner(leaderBoard);
        } catch (FileNotFoundException e) {
            System.out.println("LeaderBoard not found\n");
            throw new RuntimeException();
        }

        String line = scanner.nextLine();
        while (!line.split(" ")[0].equals(UnblockMe.getNameLevel())) {
            line = scanner.nextLine();
        }

        Painter.setFill(Color.BLACK);
        Painter.setFont(Font.font("Arial", (double) BLOCK_SIZE /5));
        Painter.setTextAlign(TextAlignment.CENTER);
        Painter.fillText(line.substring(UnblockMe.getNameLevel().length()), BLOCK_SIZE * BOARD_SIZE + BLOCK_SIZE, (double) 3 * (BLOCK_SIZE * BOARD_SIZE) / 4);

        return line.split(" ")[2];
    }

    public static Stage getStageNow() {
        return stageNow;
    }

    public static String getNameLevel () {
        return nameLevel;
    }

    public Canvas getCanvas() { return canvas;}

    public final int BLOCK_SIZE = 120;
    private Canvas canvas = null;
    private final Image carR = new Image("redcar.png");
    private final Image car2h = new Image("car2h.png");
    private final Image car2v = new Image("car2v.png");
    private final Image car3h = new Image("car3h.png");
    private final Image car3v = new Image("car3v.png");
    private static String nameLevel = null;
    private GraphicsContext Painter = null;
    private static Stage stageNow = null;
    private final int BOARD_SIZE;
    private Model UnblockMe = null;
    public final int BORDER_FIELD;
}
