var game = new Phaser.Game(800, 600, Phaser.AUTO, 'phaser-example', { preload: preload, create: create, update: update, render: render });

var mapa, imagen, player1, cursors;
var PLAYER_SCALE = 0.4;

function preload() {
    game.load.tilemap('TiledMap', 'js/assets/level_1.json', null, Phaser.Tilemap.TILED_JSON);
    game.load.image('BackGroundImage', 'js/assets/level_1_backgorund.png');    
    game.load.spritesheet('LimitPointsImage', 'js/assets/border.png', 10, 10);
    game.load.atlas('Player1Movements', 'js/assets/petaxMovements.png', 'js/assets/petaxMovements.json');
}

var map;
var limitPoints;
var player1; 
var cursors; 
var backGround;
var PLAYER_SCALE = 1.2;

function create() {            
    backGround = game.add.tileSprite(0, 0, 1679, 600, 'BackGroundImage');
    game.world.setBounds(0, 0, 1679, 600); 
    
    map = game.add.tilemap('TiledMap');
    map.setCollisionBetween(1, 12);
    
    layer = map.createLayer('PatternLayer');
    layer.resizeWorld();
    
    game.physics.startSystem(Phaser.Physics.ARCADE);    
    
    limitPoints = game.add.group();
    limitPoints.enableBody = true;
    map.createFromObjects('ObjectsLayer', 1, 'LimitPointsImage', 0, true, false, limitPoints);
    
    player1 = game.add.sprite(((game.world.width - game.camera.width) / 2)+100, game.world.height, 'Player1Movements');
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

    game.physics.arcade.collide(player1, layer);
    game.physics.arcade.overlap(player1, limitPoints, collideCallback, processCallback, this);

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
        player1.body.velocity.x = 150;
        player1.body.velocity.y = 150;
        player1.animations.play('walking');
    }
    if (cursors.down.isDown && cursors.left.isDown)
    {
        player1.body.velocity.x = -150;
        player1.body.velocity.y = 150;
        player1.animations.play('walking');
    }
    if (cursors.up.isDown && cursors.right.isDown)
    {
        player1.body.velocity.x = 150;
        player1.body.velocity.y = -150;
        player1.animations.play('walking');
    }
    if (cursors.up.isDown && cursors.left.isDown)
    {
        player1.body.velocity.x = -150;
        player1.body.velocity.y = -150;
        player1.animations.play('walking');
    }
    else if (cursors.right.isDown)
    {
        player1.body.velocity.x = 150;
        player1.scale.x = PLAYER_SCALE;
        player1.animations.play('walking');
    }
    else if (cursors.left.isDown)
    {
        player1.body.velocity.x = -150;
        player1.scale.x = -PLAYER_SCALE;
        player1.animations.play('walking');
    }
    else if (cursors.up.isDown)
    {
        player1.body.velocity.y = -150;
        player1.animations.play('walking');
    }
    else if (cursors.down.isDown)
    {
        player1.body.velocity.y = 150;
        player1.animations.play('walking');
    }        
    else
        player1.animations.play('stop')

}  

function collideCallback(body1, body2)
{
}

function processCallback(body1, body2)
{
    return true;
} 

function render() {

}
