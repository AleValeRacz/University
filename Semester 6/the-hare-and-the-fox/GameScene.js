class GameScene extends Phaser.Scene {
    constructor() {
        super("GameScene");
        this.tileSize = 50;
        this.playerSpeed = 100;

        this.map = [
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1],
            [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1],
            [1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1],
            [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1],
            [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1],
            [1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1],
            [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1],
            [1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
        ];
        this.score1 = 0;
        this.score2 = 0;
        this.lives1 = 3;
        this.lives2 = 3;
    }

    preload() {
        this.load.spritesheet('p1', 'assets/Hare1.png', {
            frameWidth: 32,
            frameHeight: 32
        });
        this.load.image('wall', 'assets/Tree_Medium.png');
        this.load.image('carrot', 'assets/carrot.png');
        this.load.spritesheet('fox', 'assets/fox.png', {
            frameWidth: 32,
            frameHeight: 32
        });
        this.load.image('ground', 'assets/Ground.png');

    }
    create() {
        let pauseText = this.add.text(10, 10, "PAUSE", {
            fontSize: "20px",
            fill: "#fff",
            backgroundColor: "#000"
        }).setInteractive();

        pauseText.on("pointerdown", () => {
            this.scene.pause();
            this.scene.launch("PauseScene");
        });
        this.input.keyboard.on("keydown-ESC", () => {
            this.scene.pause();
            this.scene.launch("PauseScene");
        });

        this.uiText = this.add.text(20, 50, "", {
            fontSize: "20px",
            fill: "#ffffff",
            backgroundColor: "#000000"
        }).setDepth(1000);

        this.updateUI();

        const mapWidth = this.map[0].length * this.tileSize;
        const mapHeight = this.map.length * this.tileSize;

        this.offsetX = (this.sys.game.config.width - mapWidth) / 2;
        this.offsetY = (this.sys.game.config.height - mapHeight) / 2;

        this.walls = this.physics.add.staticGroup();

        for (let row = 0; row < this.map.length; row++) {
            for (let col = 0; col < this.map[row].length; col++) {

                if (this.map[row][col] === 0) {
                    let ground = this.add.image(
                        this.offsetX + col * this.tileSize + this.tileSize / 2,
                        this.offsetY + row * this.tileSize + this.tileSize / 2,
                        'ground'
                    );
                    ground.setDisplaySize(this.tileSize, this.tileSize);
                }
                else {
                    let wall = this.walls.create(
                        this.offsetX + col * this.tileSize + this.tileSize / 2,
                        this.offsetY + row * this.tileSize + this.tileSize / 2,
                        'wall'
                    );

                    wall.setDisplaySize(this.tileSize, this.tileSize);
                    wall.refreshBody();
                }
            }
        }
        this.anims.create({
            key: 'p1-down',
            frames: this.anims.generateFrameNumbers('p1', { start: 0, end: 5 }),
            frameRate: 8,
            repeat: -1
        });

        this.anims.create({
            key: 'p1-up',
            frames: this.anims.generateFrameNumbers('p1', { start: 6, end: 11 }),
            frameRate: 8,
            repeat: -1
        });

        this.anims.create({
            key: 'p1-left',
            frames: this.anims.generateFrameNumbers('p1', { start: 12, end: 17 }),
            frameRate: 8,
            repeat: -1
        });

        this.anims.create({
            key: 'p1-right',
            frames: this.anims.generateFrameNumbers('p1', { start: 18, end: 23 }),
            frameRate: 8,
            repeat: -1
        });
        this.idleFrames = {
            down: 1,
            up: 7,
            left: 13,
            right: 19
        };
        this.anims.create({
            key: 'fox-down',
            frames: this.anims.generateFrameNumbers('fox', { start: 0, end: 5 }),
            frameRate: 8,
            repeat: -1
        });

        this.anims.create({
            key: 'fox-up',
            frames: this.anims.generateFrameNumbers('fox', { start: 6, end: 11 }),
            frameRate: 8,
            repeat: -1
        });

        this.anims.create({
            key: 'fox-right',
            frames: this.anims.generateFrameNumbers('fox', { start: 12, end: 17 }),
            frameRate: 8,
            repeat: -1
        });

        this.anims.create({
            key: 'fox-left',
            frames: this.anims.generateFrameNumbers('fox', { start: 18, end: 23 }),
            frameRate: 8,
            repeat: -1
        });
        //players
        this.player1 = this.physics.add.sprite(
            this.offsetX + this.tileSize * 1.5,
            this.offsetY + this.tileSize * 1.5,
            'p1'
        ).setDisplaySize(50, 50).setCollideWorldBounds(true);

        this.player2 = this.physics.add.sprite(
            this.offsetX + this.tileSize * 15.5,
            this.offsetY + this.tileSize * 13.5,
            'p1'
        ).setDisplaySize(50, 50).setCollideWorldBounds(true);
        this.player2.baseTint = 0xCCCCFF;
        this.player2.setTint(this.player2.baseTint);

        this.player1.body.setSize(20, 20);
        this.player2.body.setSize(20, 20);

        this.cursors = this.input.keyboard.createCursorKeys();
        this.keys = this.input.keyboard.addKeys({
            up: 'W',
            down: 'S',
            left: 'A',
            right: 'D'
        });

        this.physics.add.collider(this.player1, this.walls);
        this.physics.add.collider(this.player2, this.walls);

        this.spawn1 = { x: this.player1.x, y: this.player1.y };
        this.spawn2 = { x: this.player2.x, y: this.player2.y };
        this.player1.isImmune = false;
        this.player2.isImmune = false;

        //  carrots
        this.carrots = this.physics.add.group();

        for (let row = 0; row < this.map.length; row++) {
            for (let col = 0; col < this.map[row].length; col++) {

                if (this.map[row][col] === 0 && Math.random() < 0.5) {
                    let carrot = this.carrots.create(
                        this.offsetX + col * this.tileSize + this.tileSize / 2,
                        this.offsetY + row * this.tileSize + this.tileSize / 2,
                        'carrot'
                    );
                    carrot.setDisplaySize(25, 25);
                }
            }
        }

        this.physics.add.overlap(this.player1, this.carrots, this.collectCarrot, null, this);
        this.physics.add.overlap(this.player2, this.carrots, this.collectCarrot, null, this);

        this.totalCarrots = this.carrots.countActive(true);

        // foxes
        this.foxes = this.physics.add.group();

        const maxFoxes = 4;
        let spawned = 0;

        while (spawned < maxFoxes) {
            const row = Phaser.Math.Between(0, this.map.length - 1);
            const col = Phaser.Math.Between(0, this.map[0].length - 1);
            if (this.map[row][col] === 0) {
                const x = this.offsetX + col * this.tileSize + this.tileSize / 2;
                const y = this.offsetY + row * this.tileSize + this.tileSize / 2;

                if (!this.isFarFromPlayers(x, y)) continue;

                const fox = this.foxes.create(x, y, 'fox');
                fox.setDisplaySize(40, 40);
                fox.setCollideWorldBounds(true);
                fox.setBounce(1);

                fox.state = "patrol";
                fox.direction = Phaser.Math.Between(0, 3);
                fox.speed = 50;
                fox.target = null;

                spawned++;
            }
        }

        this.physics.add.collider(this.foxes, this.walls);
        this.physics.add.overlap(this.player1, this.foxes, this.hitByFox, null, this);
        this.physics.add.overlap(this.player2, this.foxes, this.hitByFox, null, this);

        this.foxes.children.iterate((fox) => {
            fox.state = "patrol";
            fox.direction = Phaser.Math.Between(0, 3);
            fox.speed = 50;
        });
    }

    update() {
        const speed = this.playerSpeed;

        // player 1
        this.player1.setVelocity(0);

        if (this.keys.left.isDown) {
            this.player1.setVelocityX(-speed);
            this.player1.anims.play('p1-left', true);
            this.player1.lastDir = 'left';

        } else if (this.keys.right.isDown) {
            this.player1.setVelocityX(speed);
            this.player1.anims.play('p1-right', true);
            this.player1.lastDir = 'right';

        } else if (this.keys.up.isDown) {
            this.player1.setVelocityY(-speed);
            this.player1.anims.play('p1-up', true);
            this.player1.lastDir = 'up';

        } else if (this.keys.down.isDown) {
            this.player1.setVelocityY(speed);
            this.player1.anims.play('p1-down', true);
            this.player1.lastDir = 'down';

        } else {
            this.player1.anims.stop();
            this.player1.setFrame(this.idleFrames[this.player1.lastDir] || 0);
        }

        // player 2
        this.player2.setVelocity(0);
        if (this.cursors.left.isDown) {
            this.player2.setVelocityX(-speed);
            this.player2.anims.play('p1-left', true);
            this.player2.lastDir = 'left';

        } else if (this.cursors.right.isDown) {
            this.player2.setVelocityX(speed);
            this.player2.anims.play('p1-right', true);
            this.player2.lastDir = 'right';

        } else if (this.cursors.up.isDown) {
            this.player2.setVelocityY(-speed);
            this.player2.anims.play('p1-up', true);
            this.player2.lastDir = 'up';

        } else if (this.cursors.down.isDown) {
            this.player2.setVelocityY(speed);
            this.player2.anims.play('p1-down', true);
            this.player2.lastDir = 'down';

        } else {
            this.player2.anims.stop();
            this.player2.setFrame(this.idleFrames[this.player2.lastDir] || 0);
        }

        // foxes
        this.foxes.children.iterate((fox) => {
            if (!fox) return;

            if (fox.state === "patrol") {
                this.patrolFox(fox);
                if (this.canSeePlayer(fox, this.player1)) this.startChase(fox, this.player1);
                else if (this.canSeePlayer(fox, this.player2)) this.startChase(fox, this.player2);

            } else if (fox.state === "chase") {
                this.chasePlayer(fox);
            }

            const vx = fox.body.velocity.x;
            const vy = fox.body.velocity.y;

            if (Math.abs(vx) > Math.abs(vy)) {
                if (vx > 0) fox.anims.play('fox-right', true);
                else fox.anims.play('fox-left', true);
            } else if (Math.abs(vy) > 0) {
                if (vy > 0) fox.anims.play('fox-down', true);
                else fox.anims.play('fox-up', true);
            }
        });
    }

    

    collectCarrot(player, carrot) {
        carrot.destroy();

        if (player === this.player1) {
            this.score1++;
        } else if (player === this.player2) {
            this.score2++;
        }

        this.totalCarrots--;
        this.updateUI();

        this.checkGameEnd();
    }

    hitByFox(player, fox) {
        if (player.isImmune) return;

        if (player === this.player1) {
            this.lives1--;
            if (this.lives1 <= 0) {
                player.disableBody(true, true);
            } else {
                player.setPosition(this.spawn1.x, this.spawn1.y);
            }
        } else {
            this.lives2--;
            if (this.lives2 <= 0) {
                player.disableBody(true, true);
            } else {
                player.setPosition(this.spawn2.x, this.spawn2.y);
            }
        }

        player.isImmune = true;
        player.setTint(0x00ffff);

        this.time.delayedCall(5000, () => {
            player.isImmune = false;
            player.setTint(player.baseTint || 0xffffff);
        });

        this.updateUI();

        this.checkGameEnd();

    }

    updateUI() {
        this.uiText.setText(
            `P1 Score: ${this.score1}\nP1 Lives: ${this.lives1}\nP2 Score: ${this.score2}\nP2 Lives: ${this.lives2}`
        );
        this.uiText.setScrollFactor(0);
    }

    patrolFox(fox) {
        const speed = fox.speed;
        let vx = 0, vy = 0;
        switch (fox.direction) {
            case 0: vy = -speed; break;
            case 1: vy = speed; break;
            case 2: vx = -speed; break;
            case 3: vx = speed; break;
        }
        fox.setVelocity(vx, vy);
        let touching = fox.body.blocked;
        if (touching.up || touching.down || touching.left || touching.right) {
            fox.direction = Phaser.Math.Between(0, 3);
        }
    }

    canSeePlayer(fox, player) {
         if (!player.active) return false; 
        const tolerance = 10;
        const inLineX = Math.abs(fox.y - player.y) < tolerance;
        const inLineY = Math.abs(fox.x - player.x) < tolerance;

        if (!inLineX && !inLineY) return false;
        const ray = new Phaser.Geom.Line(fox.x, fox.y, player.x, player.y);
        let blocked = false;
        this.walls.children.iterate((wall) => {
            if (Phaser.Geom.Intersects.LineToRectangle(ray, wall.getBounds())) blocked = true;
        });

        return !blocked;
    }

    startChase(fox, player) {
        fox.state = "chase";
        fox.target = player;
    }

    chasePlayer(fox) {
        if (!fox.target) {
            fox.state = "patrol";
            return;
        }

        const target = fox.target;
        const angle = Phaser.Math.Angle.Between(fox.x, fox.y, target.x, target.y);
        fox.setVelocity(Math.cos(angle) * 100, Math.sin(angle) * 100);

        if (!this.canSeePlayer(fox, target) && this.isAtIntersection(fox)) {
            fox.state = "patrol";
            fox.target = null;
            fox.direction = Phaser.Math.Between(0, 3);
        }
    }
    isAtIntersection(fox) {
        let openDirs = 0;
        const tolerance = 5;
        this.walls.children.iterate((wall) => {
            if (Math.abs(wall.x - fox.x) < tolerance || Math.abs(wall.y - fox.y) < tolerance) openDirs++;
        });
        return openDirs >= 2;
    }

    checkGameEnd() {

        if (this.totalCarrots <= 0) {

            let winnerText = "";

            if (this.score1 > this.score2) winnerText = "Player 1 Wins!";
            else if (this.score2 > this.score1) winnerText = "Player 2 Wins!";
            else winnerText = "It's a Tie!";

            this.endGame(winnerText);
        }

        else if (this.lives1 <= 0 && this.lives2 <= 0)
            this.endGame("Game Over!");

    }

    endGame(text) {
        this.add.rectangle(475, 350, 950, 700, 0x000000, 0.7).setDepth(2000);
        this.add.text(350, 300, text, {
            fontSize: "32px",
            fill: "#fff"
        }).setDepth(2001);

        this.add.text(350, 380, "Refresh to Restart", {
            fontSize: "20px",
            fill: "#fff"
        }).setDepth(2001);

        this.scene.pause();
    }

    isFarFromPlayers(x, y) {
        const safeDistance = this.tileSize * 3;
        const dx1 = Math.abs(x - this.spawn1.x);
        const dy1 = Math.abs(y - this.spawn1.y);
        const dx2 = Math.abs(x - this.spawn2.x);
        const dy2 = Math.abs(y - this.spawn2.y);

        return (dx1 >= safeDistance || dy1 >= safeDistance) &&
            (dx2 >= safeDistance || dy2 >= safeDistance);
    }
}