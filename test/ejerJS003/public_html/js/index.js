var game = new Phaser.Game(800, 600, Phaser.AUTO, '', { preload: preload, create: create, update: update, render: render });

function preload() {


    game.load.spritesheet('border', 'js/assets/border.png', 10, 10);    
    game.load.tilemap('map', 'js/assets/level2.json', null, Phaser.Tilemap.TILED_JSON);
    game.load.image('background', 'js/assets/fase_1_backgorund.png');
    game.load.spritesheet('character', 'js/assets/character.png', 30, 48);

}

var cursors;
var map;
var limits;

var layer;
var sprite;

function create() {

    map = game.add.tilemap('map');
    map.addTilesetImage('background');
    map.setCollisionBetween(1, 12);

    layer = map.createLayer('mainLayer');
    layer.resizeWorld();

    game.physics.startSystem(Phaser.Physics.ARCADE);

    limits = game.add.group();
    limits.enableBody = true;

    //  And now we convert all of the Tiled objects with an ID of 34 into sprites within the coins group
    map.createFromObjects('Limites', 1, 'lim', 0, true, false, limits);

    sprite = game.add.sprit(100, 500, 'character');
    sprite.anchor.set(0.5);

    game.physics.arcade.enable(sprite);

    //  This adjusts the collision body size.
    sprite.body.setSize(32, 32, 16, 16);

    //  We'll set a lower max angular velocity here to keep it from going totally nuts
    sprite.body.maxAngular = 500;

    //  Apply a drag otherwise the sprite will just spin and never slow down
    sprite.body.angularDrag = 50;

    game.camera.follow(sprite);

    cursors = game.input.keyboard.createCursorKeys();

}

function update() {

    game.physics.arcade.collide(sprite, layer);
    game.physics.arcade.overlap(sprite, coins, collectCoin, null, this);

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

    game.debug.body(sprite);

}

