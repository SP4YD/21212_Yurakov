package com.example.unblockme;

import javafx.animation.AnimationTimer;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.canvas.Canvas;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.TimeUnit;

import static java.lang.Math.*;

public class GameWindowController {

    public GameWindowController() {
    }
    public void CreateGameWindow(Stage stage, File level, String nameLvl) throws Exception {
        stageNow = stage;
        nameLevel = nameLvl;

        UnblockMe = new Model();
        InputStream LevelStream = new FileInputStream(level);
        UnblockMe.LoadLevel(LevelStream, nameLevel);

        View = new GameWindowView(nameLevel, UnblockMe);
        View.start(stageNow);
        View.updateScene(UnblockMe.getBlocks(), UnblockMe.getMainBlock(), tmpXSelectedBlock, tmpYSelectedBlock);

        Canvas canvas = View.getCanvas();
        int BLOCK_SIZE = View.BLOCK_SIZE;
        int BORDER_FIELD = View.BORDER_FIELD;

        countSteps = 0;

        stopwatch = new Stopwatch();
        stopwatch.start();

        File leaderBoard = new File("src/main/resources/LeaderBoard.txt");
        oldTime = View.drawLeaderBoard(leaderBoard);

        timer = new AnimationTimer() {
            @Override
            public void handle(long now) {
            if (stopwatch.isRunning()) {
                View.drawNumOfSteps(countSteps);
                View.drawTime(stopwatch.getTime());
            }
            }
        };

        timer.start();

        canvas.setOnMousePressed(new EventHandler<MouseEvent>() { public void handle(MouseEvent event) {
            double x = event.getX();
            double y = event.getY();
            selectedBlock = UnblockMe.BlockSelection((int) x / BLOCK_SIZE, (int) y / BLOCK_SIZE);
            if (selectedBlock != null) {
                differenceX = x - selectedBlock.GetX() * BLOCK_SIZE;
                differenceY = y - selectedBlock.GetY() * BLOCK_SIZE;
            }
        }});

        canvas.setOnMouseDragged(new EventHandler<MouseEvent>() { public void handle(MouseEvent event) {
            double x = event.getX();
            double y = event.getY();
            if (CalculatingNewCoords(x - differenceX, y - differenceY, BLOCK_SIZE, BORDER_FIELD)) {
                View.updateScene(UnblockMe.getBlocks(), UnblockMe.getMainBlock(), tmpXSelectedBlock, tmpYSelectedBlock);
            }
        }});

        canvas.setOnMouseReleased(new EventHandler<MouseEvent>() { public void handle(MouseEvent event) {
            if (stopwatch.isRunning()) {
                if (FixingTheBlock(BLOCK_SIZE, BORDER_FIELD)) {
                    View.updateScene(UnblockMe.getBlocks(), UnblockMe.getMainBlock(), tmpXSelectedBlock, tmpYSelectedBlock);
                }
            }

            if (UnblockMe.MainBlockIsOut()) {
                FinishGame(leaderBoard);
            }
        }});

        stageNow.setOnCloseRequest(new EventHandler<WindowEvent>() {
            public void handle(WindowEvent we) {
                LevelSelectionController controller = new LevelSelectionController();
                controller.CloseAllWindow();
            }
        });
    }

    private boolean CalculatingNewCoords(double x, double y, int BLOCK_SIZE, int BORDER_FIELD) {
        if (selectedBlock != null) {
            if (tmpXSelectedBlock == -1 && tmpYSelectedBlock == -1) {
                tmpXSelectedBlock = selectedBlock.GetX();
                tmpYSelectedBlock = selectedBlock.GetY();
            }

            double newX = tmpXSelectedBlock * BLOCK_SIZE;
            double newY = tmpYSelectedBlock * BLOCK_SIZE;
            int lenX = selectedBlock.GetLenX() * BLOCK_SIZE;
            int lenY = selectedBlock.GetLenY() * BLOCK_SIZE;

            if (lenX > lenY && x > 0 && (x + lenX) < BORDER_FIELD) {
                newX = x;
            }

            if (lenY > lenX && y > 0 && (y + lenY) < BORDER_FIELD) {
                newY = y;
            }

            Block tmpBlock = new Block((int) (newX / BLOCK_SIZE), (int) (newY / BLOCK_SIZE), lenX / BLOCK_SIZE, lenY / BLOCK_SIZE);
            boolean isIntersect = false;
            for (Block block : UnblockMe.getBlocks()) {
                if (!block.equals(selectedBlock) && UnblockMe.Intersects(newX, newY, lenX, lenY, block, BLOCK_SIZE)) {
                    isIntersect = true;
                    break;
                }
            }

            if (!isIntersect) {
                if (abs(tmpBlock.GetX() - tmpXSelectedBlock) >= 1.5 || abs(tmpBlock.GetY() - tmpYSelectedBlock) >= 1.5) {
                    return false;
                } else {
                    tmpXSelectedBlock = newX / BLOCK_SIZE;
                    tmpYSelectedBlock = newY / BLOCK_SIZE;
                }
                if (lenY > lenX) {
                    if (y < newY) {
                        while (!isIntersect && newY > 0) {
                            --newY;
                            for (Block block : UnblockMe.getBlocks()) {
                                if (!block.equals(selectedBlock) && UnblockMe.Intersects(newX, newY, lenX, lenY, block, BLOCK_SIZE)) {
                                    isIntersect = true;
                                    break;
                                }
                            }
                        }
                    } else if (y > newY) {
                        while (!isIntersect && (newY + lenY) < BORDER_FIELD) {
                            ++newY;
                            for (Block block : UnblockMe.getBlocks()) {
                                if (!block.equals(selectedBlock) && UnblockMe.Intersects(newX, newY, lenX, lenY, block, BLOCK_SIZE)) {
                                    isIntersect = true;
                                    break;
                                }
                            }
                        }
                    }
                    tmpXSelectedBlock = newX / BLOCK_SIZE;
                    tmpYSelectedBlock = newY / BLOCK_SIZE;
                }

                if (lenX > lenY) {
                    if (x < newX) {
                        while (!isIntersect && newX > 0) {
                            --newX;
                            for (Block block : UnblockMe.getBlocks()) {
                                if (!block.equals(selectedBlock) && UnblockMe.Intersects(newX, newY, lenX, lenY, block, BLOCK_SIZE)) {
                                    isIntersect = true;
                                    break;
                                }
                            }
                        }
                    } else if (x > newX) {
                        while (!isIntersect && (newX + lenX) < BORDER_FIELD) {
                            ++newX;
                            for (Block block : UnblockMe.getBlocks()) {
                                if (!block.equals(selectedBlock) && UnblockMe.Intersects(newX, newY, lenX, lenY, block, BLOCK_SIZE)) {
                                    isIntersect = true;
                                    break;
                                }
                            }
                        }
                    }
                    tmpXSelectedBlock = newX / BLOCK_SIZE;
                    tmpYSelectedBlock = newY / BLOCK_SIZE;
                }

                return true;
            }
        }
        return false;
    }

    private boolean FixingTheBlock(int BLOCK_SIZE, int BORDER_FIELD) {
        boolean res = false;

        if (selectedBlock != null && tmpXSelectedBlock >= 0 && tmpYSelectedBlock >= 0) {
            double x = tmpXSelectedBlock * BLOCK_SIZE;
            double y = tmpYSelectedBlock * BLOCK_SIZE;
            int lenX = selectedBlock.GetLenX() * BLOCK_SIZE;
            int lenY = selectedBlock.GetLenY() * BLOCK_SIZE;

            if (lenX > lenY) {
                x = max(0, x);
                x = min(x, BORDER_FIELD - lenX);
                double remains = x % BLOCK_SIZE;
                x -= remains;
                if (remains > (double) BLOCK_SIZE / 2) {
                    x += BLOCK_SIZE;
                }
            }

            if (lenX < lenY) {
                y = max(0, y);
                y = min(y, BORDER_FIELD - lenY);
                double remains = y % BLOCK_SIZE;
                y -= remains;
                if (remains > (double) BLOCK_SIZE / 2) {
                    y += BLOCK_SIZE;
                }
            }

            Block tmpBlock = new Block((int) (x / BLOCK_SIZE), (int) (y / BLOCK_SIZE), lenX / BLOCK_SIZE, lenY / BLOCK_SIZE);
            boolean isIntersect = false;
            for (Block block : UnblockMe.getBlocks()) {
                if (!block.equals(selectedBlock) && UnblockMe.Intersects(x, y, lenX, lenY, block, BLOCK_SIZE)) {
                    isIntersect = true;
                    break;
                }
            }

            if (!isIntersect && abs(tmpBlock.GetX() * BLOCK_SIZE - x) < (BLOCK_SIZE * 1.5) && abs(tmpBlock.GetY() * BLOCK_SIZE - y) < (BLOCK_SIZE * 1.5)) {
                if (selectedBlock.GetX() != x / BLOCK_SIZE || selectedBlock.GetY() != y / BLOCK_SIZE) {
                    ++countSteps;
                }
                selectedBlock.SetX((int) (x / BLOCK_SIZE));
                selectedBlock.SetY((int) (y / BLOCK_SIZE));
                res = true;
            }
        }

        selectedBlock = null;
        UnblockMe.ZeroingSelectedBlock();
        tmpYSelectedBlock = -1;
        tmpXSelectedBlock = -1;
        return res;
    }

    private void FinishGame(File leaderBoard) {
        String time = stopwatch.stop();
        timer.stop();
        View.drawTime(time);

        String[] oldTimes = oldTime.split(":");
        String[] newTimes = time.split(":");

        int i = 0;
        while (i < 3 && Integer.valueOf(oldTimes[i]).equals(Integer.valueOf(newTimes[i]))) {
            ++i;
        }
        View.drawTime(time);
        if (Integer.parseInt(oldTimes[i]) > Integer.parseInt(newTimes[i])) {
            oldTime = time;
            View.drawTime(time);

            AskNickname askWindow = new AskNickname(oldTime);
            try {
                askWindow.start(stageNow);
                View.drawLeaderBoard(leaderBoard);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            View.drawLeaderBoard(leaderBoard);
        }

        try {
            stopwatch.reset();
            TimeUnit.MILLISECONDS.sleep(1500);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        LevelSelectionView newWindow = new LevelSelectionView();
        try {
            newWindow.start(stageNow);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void ExitFromLevel(ActionEvent actionEvent) {
        LevelSelectionView newWindow = new LevelSelectionView();
        try {
            newWindow.start(GameWindowView.getStageNow());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void RestartLevel(ActionEvent actionEvent) throws Exception {
        nameLevel = GameWindowView.getNameLevel();
        Stage stage = GameWindowView.getStageNow();
        File level = new File(path + nameLevel);
        CreateGameWindow(stage, level, nameLevel);
    }

    public void CreateWindowWithRules(ActionEvent actionEvent) throws IOException {
        LevelSelectionController rules = new LevelSelectionController();
        rules.CreateWindowWithRules(null);
    }

    public void CreateWindowWithLeaderBoard(ActionEvent actionEvent) throws IOException {
        LevelSelectionController rules = new LevelSelectionController();
        rules.CreateWindowWithLeaderBoard(null);
    }

    private Stage stageNow = null;
    private GameWindowView View = null;
    private AnimationTimer timer = null;
    private String nameLevel = null;
    private Model UnblockMe = null;
    private Block selectedBlock = null;
    private double differenceX = 0;
    private double differenceY = 0;
    private double tmpXSelectedBlock = -1;
    private double tmpYSelectedBlock = -1;
    private int countSteps = 0;
    private Stopwatch stopwatch;
    private String oldTime = null;
    private final String path = "src/main/resources/com/example/unblockme/Levels/";
}