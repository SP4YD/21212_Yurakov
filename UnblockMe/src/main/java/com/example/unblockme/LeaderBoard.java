package com.example.unblockme;

import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;
import javafx.scene.layout.BorderPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.TextAlignment;
import javafx.stage.Stage;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class LeaderBoard {

    public Stage Init() {
        Canvas canvas = new Canvas(800, 768);
        GraphicsContext Painter = canvas.getGraphicsContext2D();
        BorderPane root = new BorderPane(canvas);
        Scene scene = new Scene(root);
        Stage stage = new Stage();
        stage.setScene(scene);
        stage.setResizable(false);
        stage.setTitle("Leaderboard");

        Painter.setFill(Color.WHITE);
        Painter.setFont(Font.font("Arial", FontWeight.BOLD, 22));
        Painter.setTextAlign(TextAlignment.LEFT);

        File leaderBoard = new File("src/main/resources/LeaderBoard.txt");
        Scanner scanner = null;
        try {
            scanner = new Scanner(leaderBoard);
        } catch (FileNotFoundException e) {
            System.out.println("LeaderBoard not found\n");
            throw new RuntimeException();
        }

        Image background = new Image("NFS_LB.jpg");

        Painter.drawImage(background, 0, 0, 800, 768);

        String Result = scanner.nextLine();
        Result = Result.substring(Result.split(" ")[0].length());
        Painter.fillText("Level 1" + Result, 425, 64);

        Result = scanner.nextLine();
        Result = Result.substring(Result.split(" ")[0].length());
        Painter.fillText("Level 2" + Result, 425, 134);

        Result = scanner.nextLine();
        Result = Result.substring(Result.split(" ")[0].length());
        Painter.fillText("Level 3" + Result, 425, 204);

        Result = scanner.nextLine();
        Result = Result.substring(Result.split(" ")[0].length());
        Painter.fillText("Level 4" + Result, 425, 274);

        Result = scanner.nextLine();
        Result = Result.substring(Result.split(" ")[0].length());
        Painter.fillText("Level 5" + Result, 425, 344);

        Result = scanner.nextLine();
        Result = Result.substring(Result.split(" ")[0].length());
        Painter.fillText("Level 6" + Result, 425, 414);

        Result = scanner.nextLine();
        Result = Result.substring(Result.split(" ")[0].length());
        Painter.fillText("Level 7" + Result, 425, 484);

        Result = scanner.nextLine();
        Result = Result.substring(Result.split(" ")[0].length());
        Painter.fillText("Level 8" + Result, 425, 554);

        Result = scanner.nextLine();
        Result = Result.substring(Result.split(" ")[0].length());
        Painter.fillText("Level 9" + Result, 425, 624);

        Result = scanner.nextLine();
        Result = Result.substring(Result.split(" ")[0].length());
        Painter.fillText("Level 10" + Result, 425, 694);

        return stage;
    }
}
