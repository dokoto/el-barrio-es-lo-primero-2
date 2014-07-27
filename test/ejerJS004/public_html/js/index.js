
var game = new Phaser.Game(800, 600, Phaser.AUTO, 'phaser-example', {preload: preload, create: create, update: update, render: render});

var mapa, imagen, pj, cursors;
function preload() {
    game.load.tilemap('fondo', 'js/assets/poligono.json', null, Phaser.Tilemap.TILED_JSON);
    game.load.image('base', "js/assets/bloque.png");
    game.load.image('gemaBlue', "js/assets/gemaBlue.png");
    game.load.image("extra", "js/assets/alien.png")
    game.load.image("path", "js/assets/path.png")

}
;

function create() {
    game.physics.startSystem(Phaser.Physics.P2JS);

    game.stage.backgroundColor = '#2d2d2d';

    mapa = game.add.tilemap('fondo');

    mapa.addTilesetImage('base');
    mapa.addTilesetImage('gemaBlue');
    mapa.addTilesetImage('path');


    layer = mapa.createLayer('Capa');

    layer.resizeWorld();

    var a = game.physics.p2.convertCollisionObjects(mapa, "capa objeto")

    pj = game.add.sprite(200, 220, "extra")
    game.physics.p2.enable(pj);

    game.camera.follow(pj);

    game.physics.p2.setPostBroadphaseCallback(collideCallBack, this);

    cursors = game.input.keyboard.createCursorKeys();

}

function update() {

    pj.body.setZeroVelocity();

    if (cursors.left.isDown)
    {
        //pj.body.moveLeft(400);

        pj.body.rotateLeft(100);
    }
    else if (cursors.right.isDown)
    {

        pj.body.rotateRight(100);
    }
    else
    {
        pj.body.setZeroRotation();
    }

    if (cursors.up.isDown)
    {
        pj.body.thrust(10000);
    }
    else if (cursors.down.isDown)
    {
        pj.body.reverse(10000);
    }

}

function collideCallBack(body1, body2) {
    return true;
} 

function render() {
    game.debug.text("SENNIN LABS - PHASER JS ", 32, 32);
}
;