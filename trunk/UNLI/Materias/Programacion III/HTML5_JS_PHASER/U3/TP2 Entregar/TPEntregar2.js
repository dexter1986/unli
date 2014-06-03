var game = new Phaser.Game(800,600,Phaser.AUTO,'',{
	preload: preload,
	create: create,
	update: update,
	render: render});

var personaje;
var diamante;

var cursors;

var velX_floor = 300;
var velX_air = 200;
var velY = -1250;
	
function preload()
{
	game.load.atlas('personaje','spritesheet.png','sprites.json');
	game.load.image('diamante','diamond.png');
	
	cursors = game.input.keyboard.createCursorKeys();
}

function create()
{
	diamante = game.add.sprite(game.world.randomX,game.world.randomY,'diamante');
	personaje = game.add.sprite(200,200,'personaje');
	var _run = Phaser.Animation.generateFrameNames('run_', 0, 5, '', 2);
	var _jump = Phaser.Animation.generateFrameNames('jump_', 0, 4, '', 2);
	var _idle = Phaser.Animation.generateFrameNames('idle_', 0, 3, '', 2); 
	personaje.animations.add('run',_run , 10, true);
	personaje.animations.add('jump',_jump , 10, false);
	personaje.animations.add('idle',_idle , 10, false);
	
	personaje.scale.set(1.5,1.5);
    personaje.anchor.set(0.5,0.5);
	
	personaje.animations.play('idle');
	
	game.physics.startSystem(Phaser.Physics.ARCADE);
	game.physics.arcade.gravity.y = 800;
	game.physics.enable( personaje);
	personaje.body.collideWorldBounds = true;
	personaje.body.gravity.y = 500;
}

function update()
{
	CheckColision();
	if (personaje.body.onFloor())
	{ 
		if(cursors.up.isDown)
		{
			personaje.body.velocity.y = velY;  
			personaje.animations.stop();
			personaje.animations.play('jump');
		}
		else if (cursors.left.isDown)
		{ 
			personaje.body.velocity.x = -velX_floor;
			
			if(personaje.scale.x>=0)
			{
				personaje.scale.x*=-1;
			}
			
			personaje.animations.play('run');			
		}
		else if (cursors.right.isDown)
		{ 
			personaje.body.velocity.x = velX_floor;
			
			if(personaje.scale.x<=0)
			{			
				personaje.scale.x*=-1;
			}
			
			personaje.animations.play('run');
		}
		else
		{
			if(personaje.body.velocity.x != 0)
			{
				if(personaje.body.velocity.x > 0)
				{
					personaje.body.velocity.x -= 10;
				}
				else
				{
					personaje.body.velocity.x += 10;
				}
				personaje.animations.play('run');
			}
			else
			{
				personaje.animations.play('idle');
			}
		}	
	}
	else
	{
		if (cursors.left.isDown)
		{ 
			personaje.body.velocity.x = -velX_air;
			
			if(personaje.scale.x>=0)
			{
				personaje.scale.x*=-1;
			}
		}
		else if (cursors.right.isDown)
		{ 
			personaje.body.velocity.x = velX_air;
			
			if(personaje.scale.x<=0)
			{
				personaje.scale.x*=-1;
			}	
		}		
	}
}

function render()
{

}

function CheckColision()
{
	var pb = personaje.getBounds();
	var db = diamante.getBounds();
	
	if(Phaser.Rectangle.intersects(pb,db))
	{
		diamante.x=game.world.randomX;
		diamante.y=game.world.randomY;
	}
}
	