class MenuScene extends Phaser.Scene {
    constructor() {
        super("MenuScene");
    }

    create() {
        this.add.text(350, 200, "Bunny Maze Game", { fontSize: "32px", fill: "#fff" });

        let startBtn = this.add.text(400, 350, "START", {
            fontSize: "28px",
            fill: "#0f0",
            backgroundColor: "#000"
        }).setInteractive();

        startBtn.on("pointerdown", () => {
            this.scene.start("GameScene");
        });
    }
}