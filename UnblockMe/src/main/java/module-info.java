module com.example.unblockme {
    requires javafx.controls;
    requires javafx.fxml;
            
                            
    opens com.example.unblockme to javafx.fxml;
    exports com.example.unblockme;
}