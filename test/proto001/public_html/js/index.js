var game;
var player1;
var land1;
var cursors;

var PLAYER_SCALE = 1.8;

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
    player1.scale.setTo(PLAYER_SCALE, PLAYER_SCALE);
    player1.anchor.setTo(0.5, 0.5);
    player1.animations.add('walking', [0, 1, 2, 3], 10, true);
    player1.animations.add('stop', [4, 5, 6, 7], 8, true);
    
    game.physics.enable(player1, Phaser.Physics.ARCADE);
    player1.body.drag.set(0.2);
    player1.body.maxVelocity.setTo(400, 400);
    player1.body.collideWorldBounds = true;

    
    game.camera.deadzone = new Phaser.Rectangle(10, 10, 800, 600);
    game.camera.x = (game.world.width - game.camera.width) / 2;

    cursors = game.input.keyboard.createCursorKeys();    
}


function update() {
    player1.body.velocity.x = 0;
    player1.body.velocity.y = 0;
    
    // CAMERA    
    if (Math.abs(game.camera.x-player1.x) <= Math.abs(player1.width) )
    {
        game.camera.x -= 5;
    }
    else if (Math.abs(Math.abs((game.camera.x-player1.x)) - game.camera.width) <= Math.abs(player1.width) )
    {
        game.camera.x += 5;
    }
    
    // MOVEMENTS
    if (cursors.down.isDown && cursors.right.isDown)
    {
        console.log("Down && Right cursor presed"); 
        player1.body.velocity.x = 150;
        player1.body.velocity.y = 150;
        player1.animations.play('walking');
    }
    if (cursors.down.isDown && cursors.left.isDown)
    {
        console.log("Down && Left cursor presed"); 
        player1.body.velocity.x = -150;
        player1.body.velocity.y = 150;
        player1.animations.play('walking');
    }
    if (cursors.up.isDown && cursors.right.isDown)
    {
        console.log("Up && Right cursor presed"); 
        player1.body.velocity.x = 150;
        player1.body.velocity.y = -150;
        player1.animations.play('walking');
    }
    if (cursors.up.isDown && cursors.left.isDown)
    {
        console.log("Up && Left cursor presed"); 
        player1.body.velocity.x = -150;
        player1.body.velocity.y = -150;
        player1.animations.play('walking');
    }
    else if (cursors.right.isDown)
    {
        console.log("Right cursor presed");        
        player1.body.velocity.x = 150;
        player1.scale.x = PLAYER_SCALE;
        player1.animations.play('walking');
    }
    else if (cursors.left.isDown)
    {
        console.log("Right cursor presed");        
        player1.body.velocity.x = -150;
        player1.scale.x = -PLAYER_SCALE;
        player1.animations.play('walking');
    }
    else if (cursors.up.isDown)
    {
        console.log("Up cursor presed");        
        player1.body.velocity.y = -150;
        player1.animations.play('walking');
    }
    else if (cursors.down.isDown)
    {
        console.log("Down cursor presed");        
        player1.body.velocity.y = 150;
        player1.animations.play('walking');
    }        
    else
        player1.animations.play('stop');
}

function render() {

    game.debug.cameraInfo(game.camera, 32, 32);
    game.debug.spriteCoords(player1, 32, 200);    
}