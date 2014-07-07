
var game;
var player1;
var land1;

$(document).ready(function() {
   console.log("Begin Proto GAME 1");
   game = new Phaser.Game(800, 600, Phaser.AUTO, '', { preload: preload, create: create, update: update });            
});

function preload() {
    game.load.atlas('petaxMovements', 'assets/petaxMovements.png', 'assets/petaxMovements.json');
    game.load.image('landPhase1', 'assets/bg/fase_1_background.png');
}
 
function create() {
    game.world.setBounds(-1000, -1000, 2000, 2000);
    land1 = game.add.tileSprite(0, 0, 800, 600, 'landPhase1');
    land1.fixedToCamera = true;
    
    player1 = game.add.sprite(0, 0, 'petaxMovements');
    player1.anchor.setTo(0.5, 0.5);
    player1.animations.add('stop', [0, 1, 2, 3], 20, true);
    player1.animations.add('walking', [4, 5, 6, 7], 20, true);
    
    game.physics.enable(player1, Phaser.Physics.ARCADE);
    player1.body.drag.set(0.2);
    player1.body.maxVelocity.setTo(400, 400);
    player1.body.collideWorldBounds = true;
    
    game.camera.follow(tank);
    game.camera.deadzone = new Phaser.Rectangle(150, 150, 500, 300);
    game.camera.focusOnXY(0, 0);

    cursors = game.input.keyboard.createCursorKeys();    
}
 
function update() {
    if (cursors.right.isDown)
    {
        player.body.velocity.x = 150;
        player.animations.play('walking');
    }
    else
    {
        player.animations.stop();
        player.animations.play('stop');
        player.frame = 4;
    }
    
}
