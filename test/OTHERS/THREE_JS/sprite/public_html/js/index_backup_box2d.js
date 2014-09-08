var scene, camera, renderer;
var geometry, material, mesh;
var world, square, ground, bounds;
var bodies = [];
var ZERO = new Box2D.b2Vec2(0.0, 0.0);
var lastTime = 0;
var PTM = 32;
var stats;

$(document).ready(function() {
    initGL();
    initPhysics();
    render();
});

function initPhysics() {
    world = new Box2D.b2World(new Box2D.b2Vec2(0.0, 0.0));

    createDynBox();
    createGround();
}

function createGround() {
    var bd_ground = new Box2D.b2BodyDef();
    var ground = world.CreateBody(bd_ground);
    var shape0 = new Box2D.b2EdgeShape();
    shape0.Set(new Box2D.b2Vec2(-400.0, -400.0), new Box2D.b2Vec2(400.0, -400.0));
    ground.CreateFixture(shape0, 0.0);
}

function createDynBox() {
    var shapeR = new Box2D.b2PolygonShape();
    shapeR.SetAsBox(20, 20);
    var fdR = new Box2D.b2FixtureDef();
    fdR.set_shape(shapeR);
    fdR.set_density(1.0);
    fdR.set_friction(0.0);
    fdR.set_restitution(0.0);

    var bdR = new Box2D.b2BodyDef();
    bdR.set_type(Box2D.b2_dynamicBody);
    bdR.set_position(0, 0);

    var bodyR = world.CreateBody(bdR);
    bodyR.CreateFixture(fdR);
    
    bodies.push(bodyR);
    
}

function initGL() {
    scene = new THREE.Scene();

    camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 1, 10000);
    camera.position.z = 1000;

    geometry = new THREE.BoxGeometry(200, 200, 0);
    material = new THREE.MeshBasicMaterial({
        map: THREE.ImageUtils.loadTexture('img/test_1.png'),
        transparent: true
    });
    mesh = new THREE.Mesh(geometry, material);
    mesh.position.set(0, 0, 0);
    //mesh.scale.set( 0.99, 0.99, 0 );
    // Clipping image, it means, render a part of image
    //http://solutiondesign.com/webgl-and-three-js-texture-mapping/

    var groundGeometry = new THREE.BoxGeometry(1200, 20, 0);
    var groundMaterial = new THREE.MeshBasicMaterial({color: 0x00ff00});
    var groundMesh = new THREE.Mesh(groundGeometry, groundMaterial);
    groundMesh.position.set(-600, -400, 0);

    scene.add(mesh);
    scene.add(groundMesh);

    renderer = new THREE.WebGLRenderer();
    renderer.setSize(window.innerWidth, window.innerHeight);

    container = document.createElement('div');
    document.body.appendChild(container);
    document.body.appendChild(renderer.domElement);
    stats = new Stats();
    container.appendChild(stats.domElement);

}

function render() {
    requestAnimationFrame(render);
    update();
    renderer.render(scene, camera);
    stats.update();
}

function update() {
    world.Step(1 / 60, 3, 2);
    var x = bodies[0].GetPosition().get_x();
    var y = bodies[0].GetPosition().get_y();
    mesh.position.set(x, y, 0)
    bodies[0].SetLinearVelocity(0, 10.5);
}
