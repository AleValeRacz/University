module com.example.guiproject {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens com.example.guiproject to javafx.fxml;
    exports com.example.guiproject;
}