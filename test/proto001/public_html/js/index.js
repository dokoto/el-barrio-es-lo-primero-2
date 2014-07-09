var game;
var player1;
var land1;
var cursors;

$(document).ready(function() {
   console.log("Begin Proto GAME 1");
   game = new Phaser.Game(800, 600, Phaser.AUTO, '', { preload: preload, create: create, update: update, render: render });            
});

function preload() {
    game.load.atlas('petaxMovements', 'js/assets/petaxMovements.png', 'js/assets/petaxMovements.json');
    game.load.image('landPhase1', 'js/assets/bg/fase_1_background.png');
}
 
function create() {
    land1 = game.add.tileSprite(0, 0, 1679, 600, 'landPhase1');
    game.world.setBounds(0, 0, 1679, 600);    
    
    player1 = game.add.sprite(((game.world.width - game.camera.width) / 2)+100, game.world.height, 'petaxMovements');
    player1.scale.setTo(2.2, 2.2);
    player1.anchor.setTo(0.5, 0.5);
    player1.animations.add('walking', [0, 1, 2, 3], 10, true);
    player1.animations.add('stop', [4, 5, 6, 7], 8, true);
    // Mirroring
    //player1.scale.x = -1;
    
    game.physics.enable(player1, Phaser.Physics.ARCADE);
    player1.body.drag.set(0.2);
    player1.body.maxVelocity.setTo(400, 400);
    player1.body.gravity.y = 300;
    player1.body.collideWorldBounds = true;

    
    game.camera.deadzone = new Phaser.Rectangle(10, 10, 800, 600);
    game.camera.x = (game.world.width - game.camera.width) / 2;
    //game.camera.follow(player1);

    cursors = game.input.keyboard.createCursorKeys();    
}


function update() {
    player1.body.velocity.x = 0;
    if (Math.abs(game.camera.x-player1.x) <= player1.width)
    {
        game.camera.x -= 4;
    }
    else if (Math.abs(Math.abs((game.camera.x-player1.x)) - game.camera.width) <= player1.width)
    {
        game.camera.x += 4;
    }
    if (cursors.right.isDown)
    {
        console.log("Right cursor presed");
        //player1.animations.stop();
        player1.body.velocity.x = 150;
        player1.animations.play('walking');
    }
    else if (cursors.left.isDown)
    {
        console.log("Right cursor presed");
        //player1.animations.stop();
        player1.body.velocity.x = -150;
        player1.animations.play('walking');
    }
    else
        player1.animations.play('stop');
}

function render() {

    game.debug.cameraInfo(game.camera, 32, 32);
    game.debug.spriteCoords(player1, 32, 200);    
}