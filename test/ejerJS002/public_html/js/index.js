var game = new Phaser.Game(800, 600, Phaser.AUTO, 'phaser-example', { preload: preload, create: create, update: update, render: render });

var mapa, imagen, player1, cursors;
var PLAYER_SCALE = 0.4;

function preload() {
    game.load.tilemap('map', 'js/assets/nivel_1.json', null, Phaser.Tilemap.TILED_JSON);
    game.load.image('background', 'js/assets/fase_1_backgorund.png');
    game.load.atlas('petaxMovements', 'js/assets/petaxMovements.png', 'js/assets/petaxMovements.json');
}

function create() {            
    backGround = game.add.tileSprite(0, 0, 1679, 600, 'BackGroundImage');
    game.world.setBounds(0, 0, 1679, 600); 
    
    game.physics.startSystem(Phaser.Physics.P2JS);

    game.stage.backgroundColor = '#2d2d2d';

    mapa = game.add.tilemap('map');
    
    game.add.tileSprite(0, 0, 1679, 600, 'background');

    layer = mapa.createLayer('PatternLayer');

    layer.resizeWorld();

    var a = game.physics.p2.convertCollisionObjects(mapa, "ObjectLayer");

    player1 = game.add.sprite(500, 520, 'petaxMovements');
    game.physics.p2.enable(player1);
    player1.scale.setTo(PLAYER_SCALE, PLAYER_SCALE);
    player1.anchor.setTo(0.5, 0.5);
    player1.animations.add('walking', [0, 1, 2, 3], 10, true);
    player1.animations.add('stop', [4, 5, 6, 7], 8, true);    

    game.camera.follow(player1);

    game.physics.p2.setPostBroadphaseCallback(collideCallBack, this);

    cursors = game.input.keyboard.createCursorKeys();

}

function update() {

    player1.body.setZeroVelocity();

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
        player1.animations.play('stop');

}  

function collideCallBack(body1, body2) {
    return true;
} 

function render() {

}
