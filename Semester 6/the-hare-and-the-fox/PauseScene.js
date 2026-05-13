class PauseScene extends Phaser.Scene {
    constructor() {
        super("PauseScene");
    }

    create() {
        this.add.rectangle(475, 350, 1200, 700, 0x000000, 0.7);

        let resume = this.add.text(400, 300, "RESUME", {
            fontSize: "28px",
            fill: "#fff"
        }).setInteractive();

        resume.on("pointerdown", () => {
            this.scene.stop();
            this.scene.resume("GameScene");
        });
    }
}